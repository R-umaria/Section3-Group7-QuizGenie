#ifndef QUIZSCREEN_H
#define QUIZSCREEN_H

#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QLabel>
#include "client.h"

namespace Ui {
class QuizScreen; // Make sure this matches the name in the .ui file
}

class QuizScreen : public QWidget
{
    Q_OBJECT

public:
    explicit QuizScreen(Client * client, QWidget *parent = nullptr, QString userName = "");
    ~QuizScreen();

    void loadQuestionsFromCSV(const QString &csvFilePath);

private slots:
    void onSubmitClicked();
    void onRetakeQuizClicked();  // Add the slot for the "Retake Quiz" button

private:
    Ui::QuizScreen *ui;  // This matches the class name defined in the .ui file
    QVBoxLayout *questionsLayout;
    QVector<QButtonGroup*> buttonGroups;
    QVector<QString> correctAnswers;
    QString userName;
    Client *client;
    void showCustomMessageBox(const QString &title, const QString &text, QMessageBox::Icon icon);
    void showScoreMessageBox(const QString &title, const QString &text, const QPixmap &image);
};

#endif // QUIZSCREEN_H
