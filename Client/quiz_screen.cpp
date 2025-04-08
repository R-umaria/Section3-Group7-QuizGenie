#include "quiz_screen.h"
#include "ui_quiz_screen.h"
#include <QLabel>
#include <QFileDialog>
#include <QRegularExpression>
#include <QGraphicsDropShadowEffect>

QuizScreen::QuizScreen(QWidget *parent, QString userName) :
    QWidget(parent),
    ui(new Ui::QuizScreen),
    userName(userName)
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
                                    "padding: 8px 16px;"
                                    "font-size: 14px;"
                                    "}"
                                    "QPushButton:hover {"
                                    "background-color: #7865c8;"
                                    "}");
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
        QString question = fields[0];
        QStringList options = fields.mid(1, 4);

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

void QuizScreen::onSubmitClicked()
{
    QMessageBox::information(this, "Quiz Submission", "Your answers have been submitted.");
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
                         "background-color: #8d7cd0;"
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

    msgBox.exec();
}

