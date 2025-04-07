/********************************************************************************
** Form generated from reading UI file 'home_screen.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOME_SCREEN_H
#define UI_HOME_SCREEN_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HomePage
{
public:
    QHBoxLayout *horizontalLayout_4;
    QWidget *centralvertical;
    QVBoxLayout *verticalLayout_3;
    QWidget *top_menubar;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelUserName;
    QWidget *main_upload_widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QPushButton *btnUploadPDF;
    QLabel *labelPDFStatus;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnGenerateQuiz;
    QLabel *labelLoading;
    QPushButton *btnStartQuiz;

    void setupUi(QWidget *HomePage)
    {
        if (HomePage->objectName().isEmpty())
            HomePage->setObjectName("HomePage");
        HomePage->resize(1080, 720);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(HomePage->sizePolicy().hasHeightForWidth());
        HomePage->setSizePolicy(sizePolicy);
        HomePage->setToolTipDuration(-2);
        HomePage->setStyleSheet(QString::fromUtf8("background-color: #e8dfec;"));
        horizontalLayout_4 = new QHBoxLayout(HomePage);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        centralvertical = new QWidget(HomePage);
        centralvertical->setObjectName("centralvertical");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralvertical->sizePolicy().hasHeightForWidth());
        centralvertical->setSizePolicy(sizePolicy1);
        centralvertical->setMinimumSize(QSize(1040, 500));
        centralvertical->setMaximumSize(QSize(1080, 600));
        centralvertical->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_3 = new QVBoxLayout(centralvertical);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setSizeConstraint(QLayout::SizeConstraint::SetMaximumSize);
        verticalLayout_3->setContentsMargins(-1, 11, -1, 0);
        top_menubar = new QWidget(centralvertical);
        top_menubar->setObjectName("top_menubar");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(top_menubar->sizePolicy().hasHeightForWidth());
        top_menubar->setSizePolicy(sizePolicy2);
        top_menubar->setMinimumSize(QSize(1000, 40));
        top_menubar->setMaximumSize(QSize(1080, 112));
        top_menubar->setStyleSheet(QString::fromUtf8("background-color: rgba(120, 101, 200, 100);\n"
"border-radius: 29px;"));
        horizontalLayout_3 = new QHBoxLayout(top_menubar);
        horizontalLayout_3->setSpacing(200);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        labelUserName = new QLabel(top_menubar);
        labelUserName->setObjectName("labelUserName");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(labelUserName->sizePolicy().hasHeightForWidth());
        labelUserName->setSizePolicy(sizePolicy3);
        labelUserName->setMinimumSize(QSize(200, 40));
        labelUserName->setMaximumSize(QSize(400, 40));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        labelUserName->setFont(font);
        labelUserName->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        labelUserName->setStyleSheet(QString::fromUtf8("padding: 5px;\n"
"color: #ffffff;\n"
"background-color: rgba(0, 0,0,0);"));
        labelUserName->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout_3->addWidget(labelUserName, 0, Qt::AlignmentFlag::AlignLeft);


        verticalLayout_3->addWidget(top_menubar, 0, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);

        main_upload_widget = new QWidget(centralvertical);
        main_upload_widget->setObjectName("main_upload_widget");
        sizePolicy.setHeightForWidth(main_upload_widget->sizePolicy().hasHeightForWidth());
        main_upload_widget->setSizePolicy(sizePolicy);
        main_upload_widget->setMinimumSize(QSize(1000, 300));
        main_upload_widget->setMaximumSize(QSize(1000, 300));
        main_upload_widget->setAcceptDrops(false);
        main_upload_widget->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 1);\n"
"border-radius: 12px;"));
        verticalLayout = new QVBoxLayout(main_upload_widget);
        verticalLayout->setSpacing(1);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(10, 0, 10, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(5);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        horizontalLayout->setContentsMargins(30, 30, 30, 40);
        label_2 = new QLabel(main_upload_widget);
        label_2->setObjectName("label_2");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy4);
        label_2->setMinimumSize(QSize(400, 100));
        label_2->setMaximumSize(QSize(400, 100));
        QFont font1;
        font1.setPointSize(18);
        label_2->setFont(font1);
        label_2->setStyleSheet(QString::fromUtf8("color: #7865c8; background-color: none;"));
        label_2->setLineWidth(0);
        label_2->setScaledContents(false);
        label_2->setWordWrap(true);
        label_2->setIndent(1);

        horizontalLayout->addWidget(label_2);

        btnUploadPDF = new QPushButton(main_upload_widget);
        btnUploadPDF->setObjectName("btnUploadPDF");
        sizePolicy4.setHeightForWidth(btnUploadPDF->sizePolicy().hasHeightForWidth());
        btnUploadPDF->setSizePolicy(sizePolicy4);
        btnUploadPDF->setMinimumSize(QSize(150, 60));
        btnUploadPDF->setMaximumSize(QSize(180, 60));
        QFont font2;
        font2.setPointSize(14);
        font2.setBold(false);
        btnUploadPDF->setFont(font2);
        btnUploadPDF->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnUploadPDF->setAutoFillBackground(false);
        btnUploadPDF->setStyleSheet(QString::fromUtf8("padding: 10px; \n"
"color: #211726;\n"
"border: 2px solid #211726;\n"
"border-radius: 8px;"));
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::DocumentNew));
        btnUploadPDF->setIcon(icon);
        btnUploadPDF->setIconSize(QSize(28, 28));

        horizontalLayout->addWidget(btnUploadPDF, 0, Qt::AlignmentFlag::AlignRight);


        verticalLayout->addLayout(horizontalLayout);

        labelPDFStatus = new QLabel(main_upload_widget);
        labelPDFStatus->setObjectName("labelPDFStatus");
        QSizePolicy sizePolicy5(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Minimum);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(labelPDFStatus->sizePolicy().hasHeightForWidth());
        labelPDFStatus->setSizePolicy(sizePolicy5);
        labelPDFStatus->setMinimumSize(QSize(400, 28));
        labelPDFStatus->setMaximumSize(QSize(400, 28));
        QFont font3;
        font3.setPointSize(12);
        labelPDFStatus->setFont(font3);
        labelPDFStatus->setStyleSheet(QString::fromUtf8("color: #211726;\n"
"padding-right: 20px;\n"
"background-color: none;"));
        labelPDFStatus->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        labelPDFStatus->setWordWrap(true);
        labelPDFStatus->setMargin(0);
        labelPDFStatus->setIndent(0);

        verticalLayout->addWidget(labelPDFStatus, 0, Qt::AlignmentFlag::AlignRight);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(30, 10, 30, 30);
        btnGenerateQuiz = new QPushButton(main_upload_widget);
        btnGenerateQuiz->setObjectName("btnGenerateQuiz");
        sizePolicy4.setHeightForWidth(btnGenerateQuiz->sizePolicy().hasHeightForWidth());
        btnGenerateQuiz->setSizePolicy(sizePolicy4);
        btnGenerateQuiz->setMinimumSize(QSize(180, 50));
        btnGenerateQuiz->setMaximumSize(QSize(180, 50));
        QFont font4;
        font4.setPointSize(12);
        font4.setBold(true);
        btnGenerateQuiz->setFont(font4);
        btnGenerateQuiz->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnGenerateQuiz->setStyleSheet(QString::fromUtf8("background-color: #211726; color: #FAF6F0;"));

        horizontalLayout_2->addWidget(btnGenerateQuiz);

        labelLoading = new QLabel(main_upload_widget);
        labelLoading->setObjectName("labelLoading");
        sizePolicy4.setHeightForWidth(labelLoading->sizePolicy().hasHeightForWidth());
        labelLoading->setSizePolicy(sizePolicy4);
        labelLoading->setMinimumSize(QSize(50, 50));
        labelLoading->setMaximumSize(QSize(50, 50));
        labelLoading->setStyleSheet(QString::fromUtf8("background-color: none;"));

        horizontalLayout_2->addWidget(labelLoading, 0, Qt::AlignmentFlag::AlignLeft);

        btnStartQuiz = new QPushButton(main_upload_widget);
        btnStartQuiz->setObjectName("btnStartQuiz");
        btnStartQuiz->setEnabled(false);
        sizePolicy4.setHeightForWidth(btnStartQuiz->sizePolicy().hasHeightForWidth());
        btnStartQuiz->setSizePolicy(sizePolicy4);
        btnStartQuiz->setMinimumSize(QSize(160, 50));
        btnStartQuiz->setMaximumSize(QSize(160, 50));
        QFont font5;
        font5.setPointSize(14);
        font5.setBold(true);
        btnStartQuiz->setFont(font5);
        btnStartQuiz->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnStartQuiz->setStyleSheet(QString::fromUtf8("background-color: #7865c8;\n"
"color: #FAF6F0;"));
        btnStartQuiz->setAutoRepeat(false);

        horizontalLayout_2->addWidget(btnStartQuiz, 0, Qt::AlignmentFlag::AlignRight);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_3->addWidget(main_upload_widget, 0, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignVCenter);


        horizontalLayout_4->addWidget(centralvertical, 0, Qt::AlignmentFlag::AlignTop);


        retranslateUi(HomePage);

        QMetaObject::connectSlotsByName(HomePage);
    } // setupUi

    void retranslateUi(QWidget *HomePage)
    {
        HomePage->setWindowTitle(QCoreApplication::translate("HomePage", "Form", nullptr));
        labelUserName->setText(QCoreApplication::translate("HomePage", "Hi, John Doe!", nullptr));
        label_2->setText(QCoreApplication::translate("HomePage", "To begin the Quiz, upload pdf of the course material:", nullptr));
        btnUploadPDF->setText(QCoreApplication::translate("HomePage", "Upload PDF", nullptr));
        labelPDFStatus->setText(QCoreApplication::translate("HomePage", "No file selected!", nullptr));
        btnGenerateQuiz->setText(QCoreApplication::translate("HomePage", "Generate Quiz", nullptr));
        labelLoading->setText(QString());
        btnStartQuiz->setText(QCoreApplication::translate("HomePage", "Start Quiz", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HomePage: public Ui_HomePage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOME_SCREEN_H
