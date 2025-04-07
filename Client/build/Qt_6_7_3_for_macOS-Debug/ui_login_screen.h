/********************************************************************************
** Form generated from reading UI file 'login_screen.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_SCREEN_H
#define UI_LOGIN_SCREEN_H

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
    QFrame *body_container;
    QHBoxLayout *horizontalLayout;
    QLabel *Logo;
    QFrame *frame;
    QVBoxLayout *LoginForm;
    QLabel *slogan_label;
    QFrame *verticalFrame;
    QVBoxLayout *verticalLayout_2;
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
        MainWindow->setStyleSheet(QString::fromUtf8("border-radius: 35px;"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setEnabled(true);
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(15);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(30, -1, 30, -1);
        body_container = new QFrame(centralwidget);
        body_container->setObjectName("body_container");
        body_container->setMinimumSize(QSize(1000, 500));
        body_container->setMaximumSize(QSize(1116, 500));
        body_container->setStyleSheet(QString::fromUtf8("background-color: #e8dfec;"));
        horizontalLayout = new QHBoxLayout(body_container);
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        Logo = new QLabel(body_container);
        Logo->setObjectName("Logo");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(Logo->sizePolicy().hasHeightForWidth());
        Logo->setSizePolicy(sizePolicy1);
        Logo->setMinimumSize(QSize(200, 200));
        Logo->setMaximumSize(QSize(200, 200));
        Logo->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        Logo->setStyleSheet(QString::fromUtf8("border-radius: 18px;"));
        Logo->setScaledContents(true);
        Logo->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout->addWidget(Logo, 0, Qt::AlignmentFlag::AlignHCenter);

        frame = new QFrame(body_container);
        frame->setObjectName("frame");
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setMinimumSize(QSize(500, 500));
        frame->setMaximumSize(QSize(550, 500));
        frame->setStyleSheet(QString::fromUtf8("background-color: #ffffff;\n"
"border-top-left-radius: 0;\n"
"border-bottom-left-radius: 0;\n"
""));
        LoginForm = new QVBoxLayout(frame);
        LoginForm->setSpacing(0);
        LoginForm->setObjectName("LoginForm");
        LoginForm->setSizeConstraint(QLayout::SizeConstraint::SetMaximumSize);
        LoginForm->setContentsMargins(0, 50, 0, 50);
        slogan_label = new QLabel(frame);
        slogan_label->setObjectName("slogan_label");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(slogan_label->sizePolicy().hasHeightForWidth());
        slogan_label->setSizePolicy(sizePolicy2);
        slogan_label->setMinimumSize(QSize(250, 40));
        slogan_label->setMaximumSize(QSize(250, 60));
        QFont font;
        font.setFamilies({QString::fromUtf8("Cambria")});
        font.setPointSize(22);
        font.setBold(false);
        slogan_label->setFont(font);
        slogan_label->setStyleSheet(QString::fromUtf8("color: #3E2B56;"));
        slogan_label->setLineWidth(1);
        slogan_label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        slogan_label->setWordWrap(true);

        LoginForm->addWidget(slogan_label, 0, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignVCenter);

        verticalFrame = new QFrame(frame);
        verticalFrame->setObjectName("verticalFrame");
        sizePolicy2.setHeightForWidth(verticalFrame->sizePolicy().hasHeightForWidth());
        verticalFrame->setSizePolicy(sizePolicy2);
        verticalFrame->setMinimumSize(QSize(250, 240));
        verticalFrame->setMaximumSize(QSize(250, 240));
        verticalLayout_2 = new QVBoxLayout(verticalFrame);
        verticalLayout_2->setSpacing(20);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 30, 0, 30);
        User_name_txtfield = new QLineEdit(verticalFrame);
        User_name_txtfield->setObjectName("User_name_txtfield");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(User_name_txtfield->sizePolicy().hasHeightForWidth());
        User_name_txtfield->setSizePolicy(sizePolicy3);
        User_name_txtfield->setMinimumSize(QSize(250, 46));
        User_name_txtfield->setMaximumSize(QSize(250, 46));
        QFont font1;
        font1.setPointSize(12);
        User_name_txtfield->setFont(font1);
        User_name_txtfield->setAutoFillBackground(false);
        User_name_txtfield->setStyleSheet(QString::fromUtf8("border: 1px solid #211726;\n"
"border-radius: 8px;\n"
"padding: 10px;\n"
"margin: 1px;"));
        User_name_txtfield->setFrame(false);
        User_name_txtfield->setCursorPosition(0);

        verticalLayout_2->addWidget(User_name_txtfield, 0, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignVCenter);

        Password_txtfield = new QLineEdit(verticalFrame);
        Password_txtfield->setObjectName("Password_txtfield");
        sizePolicy3.setHeightForWidth(Password_txtfield->sizePolicy().hasHeightForWidth());
        Password_txtfield->setSizePolicy(sizePolicy3);
        Password_txtfield->setMinimumSize(QSize(250, 46));
        Password_txtfield->setMaximumSize(QSize(250, 46));
        Password_txtfield->setFont(font1);
        Password_txtfield->setStyleSheet(QString::fromUtf8("border: 1px solid #211726;\n"
"border-radius: 8px;\n"
"padding: 10px;\n"
"margin: 1px;"));
        Password_txtfield->setEchoMode(QLineEdit::EchoMode::Password);

        verticalLayout_2->addWidget(Password_txtfield, 0, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignVCenter);

        Login_Btn = new QPushButton(verticalFrame);
        Login_Btn->setObjectName("Login_Btn");
        sizePolicy3.setHeightForWidth(Login_Btn->sizePolicy().hasHeightForWidth());
        Login_Btn->setSizePolicy(sizePolicy3);
        Login_Btn->setMinimumSize(QSize(250, 45));
        Login_Btn->setMaximumSize(QSize(250, 45));
        Login_Btn->setSizeIncrement(QSize(0, 0));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Segoe UI")});
        font2.setPointSize(18);
        font2.setBold(false);
        Login_Btn->setFont(font2);
        Login_Btn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        Login_Btn->setFocusPolicy(Qt::FocusPolicy::TabFocus);
        Login_Btn->setAutoFillBackground(false);
        Login_Btn->setStyleSheet(QString::fromUtf8("background-color: #211726;\n"
"border-radius: 8px;\n"
"color: #FAF6F0;"));
        Login_Btn->setFlat(false);

        verticalLayout_2->addWidget(Login_Btn);


        LoginForm->addWidget(verticalFrame, 0, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);


        horizontalLayout->addWidget(frame);


        verticalLayout->addWidget(body_container, 0, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignVCenter);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        Login_Btn->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        Logo->setText(QString());
        slogan_label->setText(QCoreApplication::translate("MainWindow", "Let's Magically turn Notes into Quizzes...", nullptr));
        User_name_txtfield->setPlaceholderText(QCoreApplication::translate("MainWindow", "Username", nullptr));
        Password_txtfield->setPlaceholderText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        Login_Btn->setText(QCoreApplication::translate("MainWindow", "Login", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_SCREEN_H
