/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *Logo;
    QFrame *frame;
    QVBoxLayout *LoginForm;
    QLabel *login_label;
    QLineEdit *User_name_txtfield;
    QLineEdit *Password_txtfield;
    QPushButton *Login_Btn;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1080, 720);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: #FAF6F0;"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setEnabled(true);
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(15);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(30, -1, 30, -1);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(14);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, -1, -1, -1);
        Logo = new QLabel(centralwidget);
        Logo->setObjectName("Logo");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(Logo->sizePolicy().hasHeightForWidth());
        Logo->setSizePolicy(sizePolicy1);
        Logo->setMinimumSize(QSize(400, 400));
        Logo->setMaximumSize(QSize(400, 400));
        Logo->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        Logo->setStyleSheet(QString::fromUtf8("border-radius: 18px;"));
        Logo->setScaledContents(true);
        Logo->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout->addWidget(Logo, 0, Qt::AlignmentFlag::AlignRight);

        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setMinimumSize(QSize(450, 400));
        frame->setMaximumSize(QSize(550, 320));
        frame->setStyleSheet(QString::fromUtf8("background-color: #91818A;\n"
"border-radius: 14px;"));
        LoginForm = new QVBoxLayout(frame);
        LoginForm->setSpacing(2);
        LoginForm->setObjectName("LoginForm");
        LoginForm->setSizeConstraint(QLayout::SizeConstraint::SetMaximumSize);
        login_label = new QLabel(frame);
        login_label->setObjectName("login_label");
        sizePolicy1.setHeightForWidth(login_label->sizePolicy().hasHeightForWidth());
        login_label->setSizePolicy(sizePolicy1);
        login_label->setMinimumSize(QSize(60, 40));
        login_label->setMaximumSize(QSize(500, 100));
        QFont font;
        font.setPointSize(32);
        font.setBold(true);
        login_label->setFont(font);
        login_label->setStyleSheet(QString::fromUtf8("color: #FAF6F0;"));
        login_label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        LoginForm->addWidget(login_label, 0, Qt::AlignmentFlag::AlignHCenter);

        User_name_txtfield = new QLineEdit(frame);
        User_name_txtfield->setObjectName("User_name_txtfield");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(User_name_txtfield->sizePolicy().hasHeightForWidth());
        User_name_txtfield->setSizePolicy(sizePolicy2);
        User_name_txtfield->setMinimumSize(QSize(280, 38));
        User_name_txtfield->setMaximumSize(QSize(280, 40));
        QFont font1;
        font1.setPointSize(12);
        User_name_txtfield->setFont(font1);
        User_name_txtfield->setStyleSheet(QString::fromUtf8("background-color: #FAF6F0;\n"
"border-radius: 8px;\n"
"padding: 10px;"));
        User_name_txtfield->setFrame(false);
        User_name_txtfield->setCursorPosition(0);

        LoginForm->addWidget(User_name_txtfield, 0, Qt::AlignmentFlag::AlignHCenter);

        Password_txtfield = new QLineEdit(frame);
        Password_txtfield->setObjectName("Password_txtfield");
        sizePolicy2.setHeightForWidth(Password_txtfield->sizePolicy().hasHeightForWidth());
        Password_txtfield->setSizePolicy(sizePolicy2);
        Password_txtfield->setMinimumSize(QSize(280, 38));
        Password_txtfield->setMaximumSize(QSize(280, 40));
        Password_txtfield->setFont(font1);
        Password_txtfield->setStyleSheet(QString::fromUtf8("background-color: #FAF6F0;\n"
"border-radius: 8px;\n"
"padding: 10px;"));
        Password_txtfield->setEchoMode(QLineEdit::EchoMode::Password);

        LoginForm->addWidget(Password_txtfield, 0, Qt::AlignmentFlag::AlignHCenter);

        Login_Btn = new QPushButton(frame);
        Login_Btn->setObjectName("Login_Btn");
        sizePolicy2.setHeightForWidth(Login_Btn->sizePolicy().hasHeightForWidth());
        Login_Btn->setSizePolicy(sizePolicy2);
        Login_Btn->setMinimumSize(QSize(170, 20));
        Login_Btn->setMaximumSize(QSize(170, 40));
        Login_Btn->setSizeIncrement(QSize(0, 0));
        QFont font2;
        font2.setPointSize(14);
        font2.setBold(true);
        Login_Btn->setFont(font2);
        Login_Btn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        Login_Btn->setFocusPolicy(Qt::FocusPolicy::TabFocus);
        Login_Btn->setAutoFillBackground(false);
        Login_Btn->setStyleSheet(QString::fromUtf8("background-color: #00BBF9;\n"
"border-radius: 8px;\n"
"color: #FAF6F0;"));
        Login_Btn->setFlat(false);

        LoginForm->addWidget(Login_Btn, 0, Qt::AlignmentFlag::AlignHCenter);


        horizontalLayout->addWidget(frame, 0, Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);


        verticalLayout->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        Login_Btn->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        Logo->setText(QString());
        login_label->setText(QCoreApplication::translate("MainWindow", "Login", nullptr));
        User_name_txtfield->setPlaceholderText(QCoreApplication::translate("MainWindow", "Username", nullptr));
        Password_txtfield->setPlaceholderText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        Login_Btn->setText(QCoreApplication::translate("MainWindow", "LOGIN", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
