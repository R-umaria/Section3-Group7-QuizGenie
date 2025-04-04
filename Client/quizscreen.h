#ifndef QUIZSCREEN_H
#define QUIZSCREEN_H

#include <QWidget>
#include <QVector>
#include "ui_quizscreen.h"

namespace Ui {
class QuizScreen;
}
QT_END_NAMESPACE

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

    Ui::Form *ui;
};

#endif // QUIZSCREEN_H
