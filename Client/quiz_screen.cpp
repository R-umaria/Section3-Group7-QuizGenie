#include "quiz_screen.h"
#include "ui_quiz_screen.h"
#include "home_screen.h"  // Include the header for the home screen
#include <QLabel>
#include <QFileDialog>
#include <QRegularExpression>
#include <QGraphicsDropShadowEffect>

QuizScreen::QuizScreen(Client *client, QWidget *parent, QString userName) :
    QWidget(parent),
    ui(new Ui::QuizScreen),
    userName(userName),
    client(client)
{
    ui->setupUi(this);

    // Set user's name from login
    //ui->labelUserName->setText("Welcome, " + userName);

    // Retrieve the layout from the .ui file
    questionsLayout = qobject_cast<QVBoxLayout*>(ui->quizContentWidget->layout());

    if (!questionsLayout) {
        showCustomMessageBox("Error", "Failed to retrieve layout from quizContentWidget.", QMessageBox::Warning);
    }

    connect(ui->submitButton, &QPushButton::clicked, this, &QuizScreen::onSubmitClicked);

    // Apply styling to submit button
    ui->submitButton->setStyleSheet("QPushButton {"
                                    "margin-right: 10px;"
                                    "border: solid 8px #211726;"
                                    "background-color: #8d7cd0;"
                                    "color: white;"
                                    "border-radius: 8px;"
                                    "padding: 5px 12px;"
                                    "font-size: 14px;"
                                    "}"
                                    "QPushButton:hover {"
                                    "background-color: #7865c8;"
                                    "}");

    // Apply styling to quizScrollArea's scrollbar and background
    ui->quizScrollArea->setStyleSheet(
        "QScrollBar:vertical {"
        "    border: none;"
        "    background: #f0f0f0;"
        "    width: 8px;"
        "    margin: 0px 0px 0px 0px;"
        "}"
        "QScrollBar::handle:vertical {"
        "    background: #8d7cd0;"
        "    min-height: 20px;"
        "    border-radius: 4px;"
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "    background: none;"
        "    height: 0px;"
        "}"
        "QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {"
        "    width: 0px;"
        "    height: 0px;"
        "}"
        "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
        "    background: none;"
        "}"
        "QScrollArea {"
        "    background-color: #f4eff5;"
        "}"
        "QWidget {"
        "    background-color: #f4eff5;"
        "}"
        );
}

QuizScreen::~QuizScreen()
{
    delete ui;
    qDeleteAll(buttonGroups);
}

void QuizScreen::loadQuestionsFromCSV(const QString &csvFilePath)
{
    QFile file(csvFilePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        showCustomMessageBox("Error", "Failed to open CSV file.", QMessageBox::Warning);
        return;
    }

    QTextStream in(&file);
    bool isHeader = true;
    int questionNumber = 1;  // Initialize question number

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();

        if (line.isEmpty()) continue;

        if (isHeader) {
            isHeader = false; // Skip the header row
            continue;
        }

        // Split by comma but handle quoted text correctly
        QStringList fields = line.split(QRegularExpression(",(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)"));

        if (fields.size() < 6) continue; // Make sure we have enough columns

        // Remove quotes from each field
        for (int i = 0; i < fields.size(); ++i) {
            fields[i] = fields[i].remove('"').trimmed();
        }

        // Extract question and options
        // Pkt Def: Question,Option1,Option2,Option3,Option4,Answer
        QString question = fields[0];
        QStringList options = fields.mid(1, 4); // Adds answer choices
        correctAnswers.append(fields[5]); // Adds correct answers

        // Create a container for each question and its options
        QWidget *questionWidget = new QWidget(this);
        QVBoxLayout *questionLayout = new QVBoxLayout(questionWidget);

        // Add question label with styling
        //QLabel *questionLabel = new QLabel(question, questionWidget);

        QLabel *questionLabel = new QLabel(QString("%1. %2").arg(questionNumber).arg(question), questionWidget);

        questionLabel->setWordWrap(true);
        questionLabel->setStyleSheet("font-size: 16px; font-weight: bold; margin-bottom: 10px;");
        questionLayout->addWidget(questionLabel);

        QButtonGroup *buttonGroup = new QButtonGroup(this);
        buttonGroups.append(buttonGroup);

        for (int i = 0; i < options.size(); ++i) {
            QString optionText = options[i];
            QRadioButton *optionButton = new QRadioButton(optionText, questionWidget);
            optionButton->setStyleSheet("font-size: 14px; padding: 5px; margin-left: 20px;"); // Add margin-left for padding
            questionLayout->addWidget(optionButton);
            buttonGroup->addButton(optionButton, i);
        }

        questionLayout->setSpacing(10);
        questionLayout->setContentsMargins(0, 0, 0, 20);

        questionsLayout->addWidget(questionWidget);

        questionNumber++;  // Increment question number
    }

    file.close();
}

void QuizScreen::showCustomMessageBox(const QString &title, const QString &text, QMessageBox::Icon icon)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(title);
    msgBox.setText(text);
    msgBox.setIcon(icon);

    msgBox.setMinimumSize(350, 250);

    msgBox.setStyleSheet("QMessageBox {"
                         "background-color: #beb4e4;"
                         "color: #7865c8;"
                         "font-size: 16px;"
                         "}"
                         "QMessageBox QLabel {"
                         "color: #FAF6F0;"
                         "}"
                         "QMessageBox QPushButton {"
                         "background-color: #ada1dd;"
                         "border-radius: 5px;"
                         "color: #FAF6F0;"
                         "padding: 5px;"
                         "}"
                         "QMessageBox QPushButton:hover {"
                         "background-color: #7865c8;"
                         "}");

    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(&msgBox);
    shadowEffect->setBlurRadius(20);
    shadowEffect->setXOffset(0);
    shadowEffect->setYOffset(0);
    shadowEffect->setColor(QColor(0, 0, 0, 160));
    msgBox.setGraphicsEffect(shadowEffect);

    msgBox.setAttribute(Qt::WA_StyledBackground);

    // Add "Retake Quiz" button
    QPushButton *retakeButton = msgBox.addButton("Back to HomePage", QMessageBox::ActionRole);
    connect(retakeButton, &QPushButton::clicked, this, &QuizScreen::onRetakeQuizClicked);

    msgBox.exec();
}

void QuizScreen::onSubmitClicked()
{
    showCustomMessageBox("Quiz Submitted", "Your score is now being calculated.", QMessageBox::Information);

    int correctCount = 0;

    // Calculate score
    for (int i = 0; i < buttonGroups.size(); ++i) {
        QAbstractButton *selected = buttonGroups[i]->checkedButton();
        if (!selected) {
            continue; // User didn't select an answer for this question
        }

        QString userAnswer = selected->text().trimmed();
        QString correctAnswer = correctAnswers[i].trimmed();
        // answer debug
        qDebug() << "Q" << i+1 << ": User =" << userAnswer << " | Correct =" << correctAnswer;
        if (userAnswer.compare(correctAnswer, Qt::CaseInsensitive) == 0) {
            correctCount++;
        }
    }

    // Calculate win/lose
    QString title, text;
    if(correctCount < 5) {
        title = "Quiz Failed!";
        text = QString("You failed the quiz! You got %1/%2").arg(correctCount).arg(correctAnswers.size());
    }
    else if (correctCount >= 5) {
        title = "Quiz Passed!";
        text = QString("Good Job! You got %1/%2!").arg(correctCount).arg(correctAnswers.size());
    }
    //showCustomMessageBox("Quiz Results", QString("You got %1 out of %2 correct!").arg(correctCount).arg(correctAnswers.size()), QMessageBox::Information);

    QString score = QString::number(correctCount);
    client->sendScore(score);
    client->showImageInMessageBox(client->receiveImage(), title, text);
}

void QuizScreen::onRetakeQuizClicked()
{
    // Open HomePage and pass the user's name
    HomePage *homePage = new HomePage(client, nullptr, userName);
    homePage->show();
    this->close();  // Close the current quiz screen
}
