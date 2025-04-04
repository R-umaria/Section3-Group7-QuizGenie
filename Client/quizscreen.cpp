#include "quizscreen.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QDebug>

QuizScreen::QuizScreen(QWidget *parent, QString userName)
    : QWidget(parent), userName(userName), currentQuestionIndex(0), score(0), ui(new Ui::Form)
{
    ui->setupUi(this);
    qDebug() << "QuizScreen UI setup completed";

    // Set user name
    ui->user_name->setText("Welcome, " + userName);
    qDebug() << "User name set";

    // Connect buttons
    connect(ui->next_quiz_button, &QPushButton::clicked, this, &QuizScreen::nextQuestion);
    connect(ui->submit_quiz_button, &QPushButton::clicked, this, &QuizScreen::submitQuiz);
    qDebug() << "Buttons connected";

    // Load questions from CSV
    loadQuestionsFromCSV();
    qDebug() << "Questions loaded from CSV";

    // Show first question
    if (!questions.isEmpty()) {
        displayQuestion(0);
        qDebug() << "First question displayed";
    } else {
        qDebug() << "No questions available";
    }

    // Check widget visibility
    qDebug() << "User name label visible:" << ui->user_name->isVisible();
    qDebug() << "Question label visible:" << ui->question_label->isVisible();
    qDebug() << "Option 1 visible:" << ui->option1->isVisible();
    qDebug() << "Option 2 visible:" << ui->option2->isVisible();
    qDebug() << "Option 3 visible:" << ui->option3->isVisible();
    qDebug() << "Option 4 visible:" << ui->option4->isVisible();
    qDebug() << "Next button visible:" << ui->next_quiz_button->isVisible();
    qDebug() << "Submit button visible:" << ui->submit_quiz_button->isVisible();
}

QuizScreen::~QuizScreen()
{
    delete ui;
}

void QuizScreen::loadQuestionsFromCSV()
{
    QString csvPath = ":/UploadedPDFs/mcq_output.csv"; // Correct resource path
    QFile file(csvPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error: Could not open the CSV file!";
        QMessageBox::warning(this, "Error", "Could not open the CSV file.");
        return;
    }
    qDebug() << "CSV file opened successfully!";
    QTextStream in(&file);
    bool firstLine = true;
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (firstLine) { firstLine = false; continue; } // Skip header
        QStringList fields = line.split(",");
        if (fields.size() < 6) continue; // Ensure at least a question + 4 options + correct answer index
        QuizQuestion q;
        q.question = fields[0];
        for (int i = 0; i < 4; i++) { // Only take 4 options
            q.options[i] = fields[i + 1];
        }
        q.correctAnswerIndex = fields[5].toInt() - 1; // Ensure valid integer conversion and adjust for 0-based index
        questions.append(q);
    }
    file.close();
}

void QuizScreen::displayQuestion(int index)
{
    if (index >= 0 && index < questions.size()) {
        QuizQuestion q = questions[index];
        ui->question_label->setText(q.question);
        ui->option1->setText(q.options[0]);
        ui->option2->setText(q.options[1]);
        ui->option3->setText(q.options[2]);
        ui->option4->setText(q.options[3]);
        ui->option1->setChecked(false);
        ui->option2->setChecked(false);
        ui->option3->setChecked(false);
        ui->option4->setChecked(false);
    }
    // Hide the Next button on the last question
    if (index == questions.size() - 1) {
        ui->next_quiz_button->setVisible(false);
        ui->submit_quiz_button->setVisible(true);
    }
}

void QuizScreen::nextQuestion()
{
    if (ui->option1->isChecked() == false && ui->option2->isChecked() == false &&
        ui->option3->isChecked() == false && ui->option4->isChecked() == false) {
        QMessageBox::warning(this, "No Selection", "Please select an answer.");
        return;
    }
    if (currentQuestionIndex < questions.size() &&
        questions[currentQuestionIndex].correctAnswerIndex == (ui->option1->isChecked() ? 0 :
                                                                   ui->option2->isChecked() ? 1 :
                                                                   ui->option3->isChecked() ? 2 : 3)) {
        score++;
    }
    currentQuestionIndex++;
    if (currentQuestionIndex < questions.size()) {
        displayQuestion(currentQuestionIndex);
    } else {
        submitQuiz();
    }
}

void QuizScreen::submitQuiz()
{
    if (ui->option1->isChecked() == false && ui->option2->isChecked() == false &&
        ui->option3->isChecked() == false && ui->option4->isChecked() == false) {
        QMessageBox::warning(this, "No Selection", "Please select an answer.");
        return;
    }
    if (questions[currentQuestionIndex].correctAnswerIndex == (ui->option1->isChecked() ? 0 :
                                                                   ui->option2->isChecked() ? 1 :
                                                                   ui->option3->isChecked() ? 2 : 3)) {
        score++;
    }
    QMessageBox::information(this, "Quiz Completed", "Your score: " + QString::number(score) + "/10");
    // Redirect to HomePage (Assuming HomePage is available)
    close();
}


