/********************************************************************************
** Form generated from reading UI file 'quiz_screen.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUIZ_SCREEN_H
#define UI_QUIZ_SCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QuizScreen
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QScrollArea *quizScrollArea;
    QWidget *quizContentWidget;
    QVBoxLayout *verticalLayout_3;
    QPushButton *submitButton;

    void setupUi(QWidget *QuizScreen)
    {
        if (QuizScreen->objectName().isEmpty())
            QuizScreen->setObjectName("QuizScreen");
        QuizScreen->resize(1080, 720);
        QSizePolicy sizePolicy(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QuizScreen->sizePolicy().hasHeightForWidth());
        QuizScreen->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(QuizScreen);
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        quizScrollArea = new QScrollArea(QuizScreen);
        quizScrollArea->setObjectName("quizScrollArea");
        quizScrollArea->setMinimumSize(QSize(500, 500));
        quizScrollArea->setMaximumSize(QSize(1000, 1000));
        quizScrollArea->setFrameShadow(QFrame::Shadow::Raised);
        quizScrollArea->setWidgetResizable(true);
        quizContentWidget = new QWidget();
        quizContentWidget->setObjectName("quizContentWidget");
        quizContentWidget->setGeometry(QRect(0, 0, 998, 658));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(quizContentWidget->sizePolicy().hasHeightForWidth());
        quizContentWidget->setSizePolicy(sizePolicy1);
        quizContentWidget->setMinimumSize(QSize(500, 500));
        quizContentWidget->setMaximumSize(QSize(1000, 1000));
        verticalLayout_3 = new QVBoxLayout(quizContentWidget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        quizScrollArea->setWidget(quizContentWidget);

        verticalLayout->addWidget(quizScrollArea);

        submitButton = new QPushButton(QuizScreen);
        submitButton->setObjectName("submitButton");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(submitButton->sizePolicy().hasHeightForWidth());
        submitButton->setSizePolicy(sizePolicy2);
        submitButton->setMaximumSize(QSize(100, 40));

        verticalLayout->addWidget(submitButton, 0, Qt::AlignmentFlag::AlignRight);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(QuizScreen);

        QMetaObject::connectSlotsByName(QuizScreen);
    } // setupUi

    void retranslateUi(QWidget *QuizScreen)
    {
        QuizScreen->setWindowTitle(QCoreApplication::translate("QuizScreen", "Form", nullptr));
        submitButton->setText(QCoreApplication::translate("QuizScreen", "Submit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QuizScreen: public Ui_QuizScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUIZ_SCREEN_H
