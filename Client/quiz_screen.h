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

namespace Ui {
class QuizScreen; // Make sure this matches the name in the .ui file
}

class QuizScreen : public QWidget
{
    Q_OBJECT

public:
    explicit QuizScreen(QWidget *parent = nullptr);
    ~QuizScreen();

    void loadQuestionsFromCSV(const QString &csvFilePath);

private slots:
    void onSubmitClicked();

private:
    Ui::QuizScreen *ui;  // This matches the class name defined in the .ui file
    QVBoxLayout *questionsLayout;
    QVector<QButtonGroup*> buttonGroups;
};

#endif // QUIZSCREEN_H
