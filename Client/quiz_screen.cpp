#include "quiz_screen.h"
#include "ui_quiz_screen.h"
#include "home_screen.h"  // Include the header for the home screen
#include <QLabel>
#include <QFileDialog>
#include <QRegularExpression>
#include <QGraphicsDropShadowEffect>
#include <QMessageBox>
#include <QCoreApplication>
#include <QApplication>  // For qApp

QuizScreen::QuizScreen(Client *client, QWidget *parent, QString userName) :
    QWidget(parent),
    ui(new Ui::QuizScreen),
    userName(userName),
    client(client)
{
    ui->setupUi(this);

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
        QStringList options = fields.mid(1, 4); // Answer choices
        correctAnswers.append(fields[5]); // Correct answer

        // Create a container for each question and its options
        QWidget *questionWidget = new QWidget(this);
        QVBoxLayout *questionLayout = new QVBoxLayout(questionWidget);

        QLabel *questionLabel = new QLabel(QString("%1. %2").arg(questionNumber).arg(question), questionWidget);
        questionLabel->setWordWrap(true);
        questionLabel->setStyleSheet("font-size: 16px; font-weight: bold; margin-bottom: 10px;");
        questionLayout->addWidget(questionLabel);

        QButtonGroup *buttonGroup = new QButtonGroup(this);
        buttonGroups.append(buttonGroup);

        for (int i = 0; i < options.size(); ++i) {
            QString optionText = options[i];
            QRadioButton *optionButton = new QRadioButton(optionText, questionWidget);
            optionButton->setStyleSheet("font-size: 14px; padding: 5px; margin-left: 20px;");
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

//
// Modified onSubmitClicked:
// 1. First, show an informational pop-up with only an "OK" button.
// 2. Then, calculate the score and show a second message box that displays the score (with an image)
//    that has two buttons: one to return to home screen and one to close the application.
//
void QuizScreen::onSubmitClicked()
{
    // --- First pop-up: Informational only ---
    QMessageBox infoBox;
    infoBox.setWindowTitle("Quiz Submitted");
    infoBox.setText("Your score is now being calculated.");
    infoBox.setIcon(QMessageBox::Information);
    infoBox.setStandardButtons(QMessageBox::Ok);
    infoBox.exec();

    // --- Calculate score ---
    int correctCount = 0;
    for (int i = 0; i < buttonGroups.size(); ++i) {
        QAbstractButton *selected = buttonGroups[i]->checkedButton();
        if (!selected) {
            continue; // User didn't select an answer for this question
        }
        QString userAnswer = selected->text().trimmed();
        QString correctAnswer = correctAnswers[i].trimmed();
        qDebug() << "Q" << i + 1 << ": User =" << userAnswer << " | Correct =" << correctAnswer;
        if (userAnswer.compare(correctAnswer, Qt::CaseInsensitive) == 0) {
            correctCount++;
        }
    }

    // Determine outcome and message text
    QString title, text;
    if (correctCount < 5) {
        title = "Quiz Failed!";
        text = QString("You failed the quiz! You got %1/%2").arg(correctCount).arg(correctAnswers.size());
    } else {
        title = "Quiz Passed!";
        text = QString("Good Job! You got %1/%2!").arg(correctCount).arg(correctAnswers.size());
    }

    // Send the score via your client (if needed)
    QString score = QString::number(correctCount);
    client->sendScore(score);

    // Receive image from the client (assuming it returns a QPixmap)
    QPixmap scoreImage = client->receiveImage();

    // --- Second pop-up: Display score with image and two action buttons ---
    showScoreMessageBox(title, text, scoreImage);
}

//
// New function: showScoreMessageBox
// Displays a message box that shows the given image, title and text.
// It also adds two buttons: one to navigate back to HomePage and one to close the application.
//
void QuizScreen::showScoreMessageBox(const QString &title, const QString &text, const QPixmap &image)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(title);
    msgBox.setText(text);

    // Scale the image: adjust w, h to your desired max width/height.
    QPixmap scaledImage = image.scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    msgBox.setIconPixmap(scaledImage);

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

    // Add "Back to HomePage" button
    QPushButton *homeButton = msgBox.addButton("Back to HomePage", QMessageBox::ActionRole);
    connect(homeButton, &QPushButton::clicked, [this](){
        this->onRetakeQuizClicked();
    });

    // Add "Close Application" button
    QPushButton *closeButton = msgBox.addButton("Close Application", QMessageBox::ActionRole);
    connect(closeButton, &QPushButton::clicked, qApp, &QCoreApplication::quit);

    msgBox.exec();
}

void QuizScreen::onRetakeQuizClicked()
{
    // Open HomePage and pass the user's name
    HomePage *homePage = new HomePage(client, nullptr, userName);
    homePage->show();
    this->close();  // Close the current quiz screen
}

//
// Optionally, you can leave showCustomMessageBox as-is for any generic messages elsewhere.
// (It is no longer used in onSubmitClicked.)
//
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

    // This version adds a default "Back to HomePage" button.
    QPushButton *retakeButton = msgBox.addButton("Back to HomePage", QMessageBox::ActionRole);
    connect(retakeButton, &QPushButton::clicked, this, &QuizScreen::onRetakeQuizClicked);

    msgBox.exec();
}
