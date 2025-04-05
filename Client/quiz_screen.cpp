#include "quiz_screen.h"
#include "ui_quiz_screen.h"
#include <QLabel>
#include <QFileDialog>

QuizScreen::QuizScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuizScreen)
{
    ui->setupUi(this);

    questionsLayout = new QVBoxLayout();
    ui->quizContentWidget->setLayout(questionsLayout);

    connect(ui->submitButton, &QPushButton::clicked, this, &QuizScreen::onSubmitClicked);
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
        QString line = in.readLine();

        if (isHeader) {
            isHeader = false; // Skip header row
            continue;
        }

        QStringList fields = line.split(",");

        if (fields.size() < 6) continue; // Ensure there are enough columns

        QString question = fields[0];
        QStringList options = fields.mid(1, 4);

        // Add question label
        QLabel *questionLabel = new QLabel(question, this);
        questionsLayout->addWidget(questionLabel);

        QButtonGroup *buttonGroup = new QButtonGroup(this);
        buttonGroups.append(buttonGroup);

        for (int i = 0; i < options.size(); ++i) {
            QRadioButton *optionButton = new QRadioButton(options[i], this);
            questionsLayout->addWidget(optionButton);
            buttonGroup->addButton(optionButton, i);
        }
    }

    file.close();
}

void QuizScreen::onSubmitClicked()
{
    QMessageBox::information(this, "Quiz Submission", "Your answers have been submitted.");
}
