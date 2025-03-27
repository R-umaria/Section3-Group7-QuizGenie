#include "quizscreen.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDir>

QuizScreen::QuizScreen(QWidget *parent, QString userName)
    : QWidget(parent), userName(userName), currentQuestionIndex(0), score(0)
{
    // Layout setup
    mainLayout = new QVBoxLayout(this);

    // Title bar with logo and username
    labelUserName = new QLabel("Welcome, " + userName);
    labelUserName->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(labelUserName);

    // Question label
    labelQuestion = new QLabel();
    labelQuestion->setAlignment(Qt::AlignCenter);
    labelQuestion->setWordWrap(true);
    mainLayout->addWidget(labelQuestion);

    // Options buttons
    buttonGroup = new QButtonGroup(this);
    for (int i = 0; i < 4; i++) {
        optionButtons[i] = new QRadioButton();
        buttonGroup->addButton(optionButtons[i], i);
        mainLayout->addWidget(optionButtons[i]);
    }

    // Next Question Button
    btnNext = new QPushButton("Next Question");
    connect(btnNext, &QPushButton::clicked, this, &QuizScreen::nextQuestion);
    mainLayout->addWidget(btnNext);

    // Submit Button
    btnSubmit = new QPushButton("Submit Quiz");
    btnSubmit->setVisible(false);
    connect(btnSubmit, &QPushButton::clicked, this, &QuizScreen::submitQuiz);
    mainLayout->addWidget(btnSubmit);

    // Load questions from CSV
    loadQuestionsFromCSV();

    // Show first question
    if (!questions.isEmpty()) {
        displayQuestion(0);
    }
}

QuizScreen::~QuizScreen() {}

void QuizScreen::loadQuestionsFromCSV()
{
    QString csvPath = "C:/Users/Rishi/source/repos/Project 4/Group Project/QuizGenie/Client/UploadedPDFs/mcq_output.csv";

    qDebug() << "Trying to open file:" << csvPath;
    QFile file(csvPath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Could not open the CSV file.");
        return;
    }

    QTextStream in(&file);
    bool firstLine = true;
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (firstLine) { firstLine = false; continue; } // Skip header

        QStringList fields = line.split(",");
        if (fields.size() < 6) continue;

        QuizQuestion q;
        q.question = fields[0];
        for (int i = 0; i < 4; i++) {
            q.options[i] = fields[i + 1];
        }
        q.correctAnswerIndex = fields[5].toInt(); // Correct Answer Index

        questions.append(q);
    }
    file.close();
}

void QuizScreen::displayQuestion(int index)
{
    if (index >= 0 && index < questions.size()) {
        QuizQuestion q = questions[index];
        labelQuestion->setText(q.question);
        for (int i = 0; i < 4; i++) {
            optionButtons[i]->setText(q.options[i]);
            optionButtons[i]->setChecked(false);
        }
    }

    // Hide the Next button on the last question
    if (index == questions.size() - 1) {
        btnNext->setVisible(false);
        btnSubmit->setVisible(true);
    }
}

void QuizScreen::nextQuestion()
{
    if (buttonGroup->checkedId() == -1) {
        QMessageBox::warning(this, "No Selection", "Please select an answer.");
        return;
    }

    if (questions[currentQuestionIndex].correctAnswerIndex == buttonGroup->checkedId()) {
        score++;
    }

    currentQuestionIndex++;
    if (currentQuestionIndex < questions.size()) {
        displayQuestion(currentQuestionIndex);
    }
}

void QuizScreen::submitQuiz()
{
    if (buttonGroup->checkedId() == -1) {
        QMessageBox::warning(this, "No Selection", "Please select an answer.");
        return;
    }

    if (questions[currentQuestionIndex].correctAnswerIndex == buttonGroup->checkedId()) {
        score++;
    }

    QMessageBox::information(this, "Quiz Completed", "Your score: " + QString::number(score) + "/10");

    // Redirect to HomePage (Assuming HomePage is available)
    close();
}
