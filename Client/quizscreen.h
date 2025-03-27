#ifndef QUIZSCREEN_H
#define QUIZSCREEN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QFile>
#include <QTextStream>
#include <QVector>

struct QuizQuestion {
    QString question;
    QString options[4];
    int correctAnswerIndex;
};

class QuizScreen : public QWidget
{
    Q_OBJECT

public:
    explicit QuizScreen(QWidget *parent = nullptr, QString userName = "");
    ~QuizScreen();

private slots:
    void nextQuestion();
    void submitQuiz();

private:
    void loadQuestionsFromCSV();
    void displayQuestion(int index);

    QString userName;
    QVector<QuizQuestion> questions;
    int currentQuestionIndex;
    int score;

    // UI Elements
    QLabel *labelUserName;
    QLabel *labelQuestion;
    QRadioButton *optionButtons[4];
    QButtonGroup *buttonGroup;
    QPushButton *btnNext;
    QPushButton *btnSubmit;
    QVBoxLayout *mainLayout;
};

#endif // QUIZSCREEN_H
