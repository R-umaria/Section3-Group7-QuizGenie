/********************************************************************************
** Form generated from reading UI file 'quizscreen.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUIZSCREEN_H
#define UI_QUIZSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *top_titlebar;
    QLabel *horizontal_logo;
    QLabel *user_name;
    QLabel *question_label;
    QRadioButton *option1;
    QRadioButton *option2;
    QRadioButton *option3;
    QRadioButton *option4;
    QHBoxLayout *horizontalLayout;
    QPushButton *submit_quiz_button;
    QPushButton *next_quiz_button;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName("Form");
        Form->resize(1080, 720);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Form->sizePolicy().hasHeightForWidth());
        Form->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(Form);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        top_titlebar = new QHBoxLayout();
        top_titlebar->setObjectName("top_titlebar");
        horizontal_logo = new QLabel(Form);
        horizontal_logo->setObjectName("horizontal_logo");

        top_titlebar->addWidget(horizontal_logo);

        user_name = new QLabel(Form);
        user_name->setObjectName("user_name");

        top_titlebar->addWidget(user_name);


        verticalLayout_3->addLayout(top_titlebar);

        question_label = new QLabel(Form);
        question_label->setObjectName("question_label");

        verticalLayout_3->addWidget(question_label);

        option1 = new QRadioButton(Form);
        option1->setObjectName("option1");

        verticalLayout_3->addWidget(option1);

        option2 = new QRadioButton(Form);
        option2->setObjectName("option2");

        verticalLayout_3->addWidget(option2);

        option3 = new QRadioButton(Form);
        option3->setObjectName("option3");

        verticalLayout_3->addWidget(option3);

        option4 = new QRadioButton(Form);
        option4->setObjectName("option4");

        verticalLayout_3->addWidget(option4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        submit_quiz_button = new QPushButton(Form);
        submit_quiz_button->setObjectName("submit_quiz_button");

        horizontalLayout->addWidget(submit_quiz_button);

        next_quiz_button = new QPushButton(Form);
        next_quiz_button->setObjectName("next_quiz_button");

        horizontalLayout->addWidget(next_quiz_button);


        verticalLayout_3->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout_3);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        horizontal_logo->setText(QCoreApplication::translate("Form", "TextLabel", nullptr));
        user_name->setText(QCoreApplication::translate("Form", "TextLabel", nullptr));
        question_label->setText(QCoreApplication::translate("Form", "TextLabel", nullptr));
        option1->setText(QCoreApplication::translate("Form", "RadioButton", nullptr));
        option2->setText(QCoreApplication::translate("Form", "RadioButton", nullptr));
        option3->setText(QCoreApplication::translate("Form", "RadioButton", nullptr));
        option4->setText(QCoreApplication::translate("Form", "RadioButton", nullptr));
        submit_quiz_button->setText(QCoreApplication::translate("Form", "PushButton", nullptr));
        next_quiz_button->setText(QCoreApplication::translate("Form", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUIZSCREEN_H
