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
#include <QtWidgets/QLabel>
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
    QWidget *top_menubar;
    QHBoxLayout *horizontalLayout_5;
    QLabel *labelUserName;
    QWidget *horizontalWidget;
    QHBoxLayout *submit_btn_layout;
    QLabel *label;
    QPushButton *submitButton;
    QScrollArea *quizScrollArea;
    QWidget *quizContentWidget;
    QVBoxLayout *verticalLayout_3;

    void setupUi(QWidget *QuizScreen)
    {
        if (QuizScreen->objectName().isEmpty())
            QuizScreen->setObjectName("QuizScreen");
        QuizScreen->resize(1080, 720);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QuizScreen->sizePolicy().hasHeightForWidth());
        QuizScreen->setSizePolicy(sizePolicy);
        QuizScreen->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout = new QHBoxLayout(QuizScreen);
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(8);
        verticalLayout->setObjectName("verticalLayout");
        top_menubar = new QWidget(QuizScreen);
        top_menubar->setObjectName("top_menubar");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(top_menubar->sizePolicy().hasHeightForWidth());
        top_menubar->setSizePolicy(sizePolicy1);
        top_menubar->setMinimumSize(QSize(1000, 56));
        top_menubar->setMaximumSize(QSize(1080, 56));
        top_menubar->setStyleSheet(QString::fromUtf8("background-color: rgba(120, 101, 200, 100);\n"
"border-radius: 28px;"));
        horizontalLayout_5 = new QHBoxLayout(top_menubar);
        horizontalLayout_5->setSpacing(200);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        labelUserName = new QLabel(top_menubar);
        labelUserName->setObjectName("labelUserName");
        sizePolicy1.setHeightForWidth(labelUserName->sizePolicy().hasHeightForWidth());
        labelUserName->setSizePolicy(sizePolicy1);
        labelUserName->setMinimumSize(QSize(200, 40));
        labelUserName->setMaximumSize(QSize(400, 40));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        labelUserName->setFont(font);
        labelUserName->setStyleSheet(QString::fromUtf8("padding: 5px;\n"
"color: #ffffff;\n"
"background-color: rgba(0,0,0,0);"));
        labelUserName->setWordWrap(false);

        horizontalLayout_5->addWidget(labelUserName, 0, Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);


        verticalLayout->addWidget(top_menubar);

        horizontalWidget = new QWidget(QuizScreen);
        horizontalWidget->setObjectName("horizontalWidget");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(horizontalWidget->sizePolicy().hasHeightForWidth());
        horizontalWidget->setSizePolicy(sizePolicy2);
        horizontalWidget->setMinimumSize(QSize(1000, 30));
        horizontalWidget->setMaximumSize(QSize(1000, 40));
        horizontalWidget->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        horizontalWidget->setStyleSheet(QString::fromUtf8(""));
        submit_btn_layout = new QHBoxLayout(horizontalWidget);
        submit_btn_layout->setSpacing(1);
        submit_btn_layout->setObjectName("submit_btn_layout");
        submit_btn_layout->setContentsMargins(1, 1, 1, 1);
        label = new QLabel(horizontalWidget);
        label->setObjectName("label");
        label->setMinimumSize(QSize(120, 40));
        label->setMaximumSize(QSize(120, 40));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        label->setFont(font1);
        label->setStyleSheet(QString::fromUtf8("padding-left: 10px; \n"
"padding-right:10px;\n"
"background-color: #7865c8;\n"
"border-radius: 5px;\n"
"color: #ffffff;"));

        submit_btn_layout->addWidget(label, 0, Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        submitButton = new QPushButton(horizontalWidget);
        submitButton->setObjectName("submitButton");
        submitButton->setEnabled(true);
        QSizePolicy sizePolicy3(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(submitButton->sizePolicy().hasHeightForWidth());
        submitButton->setSizePolicy(sizePolicy3);
        submitButton->setMaximumSize(QSize(100, 40));
        submitButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        submit_btn_layout->addWidget(submitButton);


        verticalLayout->addWidget(horizontalWidget, 0, Qt::AlignmentFlag::AlignHCenter);

        quizScrollArea = new QScrollArea(QuizScreen);
        quizScrollArea->setObjectName("quizScrollArea");
        sizePolicy2.setHeightForWidth(quizScrollArea->sizePolicy().hasHeightForWidth());
        quizScrollArea->setSizePolicy(sizePolicy2);
        quizScrollArea->setMinimumSize(QSize(1024, 450));
        quizScrollArea->setMaximumSize(QSize(1024, 600));
        quizScrollArea->setStyleSheet(QString::fromUtf8(""));
        quizScrollArea->setFrameShadow(QFrame::Shadow::Raised);
        quizScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        quizScrollArea->setWidgetResizable(true);
        quizContentWidget = new QWidget();
        quizContentWidget->setObjectName("quizContentWidget");
        quizContentWidget->setGeometry(QRect(0, 0, 1000, 582));
        sizePolicy.setHeightForWidth(quizContentWidget->sizePolicy().hasHeightForWidth());
        quizContentWidget->setSizePolicy(sizePolicy);
        quizContentWidget->setMinimumSize(QSize(500, 500));
        quizContentWidget->setMaximumSize(QSize(1000, 1000));
        quizContentWidget->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_3 = new QVBoxLayout(quizContentWidget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        quizScrollArea->setWidget(quizContentWidget);

        verticalLayout->addWidget(quizScrollArea, 0, Qt::AlignmentFlag::AlignHCenter);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(QuizScreen);

        QMetaObject::connectSlotsByName(QuizScreen);
    } // setupUi

    void retranslateUi(QWidget *QuizScreen)
    {
        QuizScreen->setWindowTitle(QCoreApplication::translate("QuizScreen", "Form", nullptr));
        labelUserName->setText(QCoreApplication::translate("QuizScreen", "Welcome, John Doe!", nullptr));
        label->setText(QCoreApplication::translate("QuizScreen", "10 Questions", nullptr));
        submitButton->setText(QCoreApplication::translate("QuizScreen", "Submit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QuizScreen: public Ui_QuizScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUIZ_SCREEN_H
