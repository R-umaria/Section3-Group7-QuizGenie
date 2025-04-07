#include "quiz_screen.h"
#include "ui_quiz_screen.h"
#include <QLabel>
#include <QFileDialog>
#include <QRegularExpression>

QuizScreen::QuizScreen(QWidget *parent, QString userName) :
    QWidget(parent),
    ui(new Ui::QuizScreen),
    userName(userName)
{
    ui->setupUi(this);
    QPixmap pix(":/assets/logo_horizontal.png");
    ui->logo_horizontal->setPixmap(pix.scaled(ui->logo_horizontal->width(), ui->logo_horizontal->height(), Qt::KeepAspectRatio));

    // Set user's name from login
    ui->labelUserName->setText("Welcome, " + userName);

    // Retrieve the layout from the .ui file
    questionsLayout = qobject_cast<QVBoxLayout*>(ui->quizContentWidget->layout());

    if (!questionsLayout) {
        QMessageBox::warning(this, "Error", "Failed to retrieve layout from quizContentWidget.");
    }

    connect(ui->submitButton, &QPushButton::clicked, this, &QuizScreen::onSubmitClicked);

    // Apply styling to submit button
    ui->submitButton->setStyleSheet("QPushButton {"
                                    "background-color: #007bff;"
                                    "color: white;"
                                    "border-radius: 8px;"
                                    "padding: 8px 16px;"
                                    "font-size: 14px;"
                                    "}"
                                    "QPushButton:hover {"
                                    "background-color: #0056b3;"
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
        QMessageBox::warning(this, "Error", "Failed to open CSV file.");
        return;
    }

    QTextStream in(&file);
    bool isHeader = true;

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
        QLabel *questionLabel = new QLabel(question, questionWidget);
        questionLabel->setWordWrap(true);
        questionLabel->setStyleSheet("font-size: 16px; font-weight: bold; margin-bottom: 10px;");
        questionLayout->addWidget(questionLabel);

        QButtonGroup *buttonGroup = new QButtonGroup(this);
        buttonGroups.append(buttonGroup);

        for (int i = 0; i < options.size(); ++i) {
            QString optionText = options[i];
            QRadioButton *optionButton = new QRadioButton(optionText, questionWidget);
            optionButton->setStyleSheet("font-size: 14px; padding: 5px;");
            questionLayout->addWidget(optionButton);
            buttonGroup->addButton(optionButton, i);
        }

        questionLayout->setSpacing(10);
        questionLayout->setContentsMargins(0, 0, 0, 20);

        questionsLayout->addWidget(questionWidget);
    }

    file.close();
}



void QuizScreen::onSubmitClicked()
{
    QMessageBox::information(this, "Quiz Submission", "Your answers have been submitted.");
}
