/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPlainTextEdit *plainTextEdit;
    QTextBrowser *textBrowser_2;
    QLabel *label_2;
    QLabel *label_3;
    QTextBrowser *textBrowser;
    QTextBrowser *textBrowser_3;
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *inputButton;
    QPushButton *testButton;
    QLCDNumber *validNumber;
    QLCDNumber *invalidNumber;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_2;
    QLineEdit *mean_lineEdit;
    QRadioButton *Button99;
    QLineEdit *var_lineEdit;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_6;
    QRadioButton *Button95;
    QLineEdit *std_lineEdit;
    QLabel *label;
    QLabel *label_9;
    QLabel *label_13;
    QLabel *label_14;
    QHBoxLayout *horizontalLayout;
    QLabel *label_10;
    QLineEdit *conl_lineEdit;
    QLineEdit *conr_lineEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_11;
    QCheckBox *acc_checkBox;
    QLabel *label_12;
    QCheckBox *per_checkBox;
    QVBoxLayout *verticalLayout_2;
    QTextBrowser *outputBox;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(800, 600);
        gridLayoutWidget = new QWidget(Widget);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(20, 20, 383, 571));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        plainTextEdit = new QPlainTextEdit(gridLayoutWidget);
        plainTextEdit->setObjectName("plainTextEdit");

        gridLayout->addWidget(plainTextEdit, 1, 0, 1, 1);

        textBrowser_2 = new QTextBrowser(gridLayoutWidget);
        textBrowser_2->setObjectName("textBrowser_2");

        gridLayout->addWidget(textBrowser_2, 1, 2, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 0, 1, 1, 1);

        textBrowser = new QTextBrowser(gridLayoutWidget);
        textBrowser->setObjectName("textBrowser");

        gridLayout->addWidget(textBrowser, 1, 1, 1, 1);

        textBrowser_3 = new QTextBrowser(gridLayoutWidget);
        textBrowser_3->setObjectName("textBrowser_3");

        gridLayout->addWidget(textBrowser_3, 1, 3, 1, 1);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 0, 2, 1, 1);

        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName("label_5");

        gridLayout->addWidget(label_5, 0, 3, 1, 1);

        inputButton = new QPushButton(gridLayoutWidget);
        inputButton->setObjectName("inputButton");

        gridLayout->addWidget(inputButton, 2, 0, 1, 1);

        testButton = new QPushButton(gridLayoutWidget);
        testButton->setObjectName("testButton");

        gridLayout->addWidget(testButton, 2, 1, 1, 1);

        validNumber = new QLCDNumber(gridLayoutWidget);
        validNumber->setObjectName("validNumber");
        validNumber->setDigitCount(5);
        validNumber->setSegmentStyle(QLCDNumber::Filled);

        gridLayout->addWidget(validNumber, 2, 2, 1, 1);

        invalidNumber = new QLCDNumber(gridLayoutWidget);
        invalidNumber->setObjectName("invalidNumber");
        invalidNumber->setDigitCount(5);

        gridLayout->addWidget(invalidNumber, 2, 3, 1, 1);

        verticalLayoutWidget = new QWidget(Widget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(420, 20, 351, 571));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        mean_lineEdit = new QLineEdit(verticalLayoutWidget);
        mean_lineEdit->setObjectName("mean_lineEdit");

        gridLayout_2->addWidget(mean_lineEdit, 0, 3, 1, 1);

        Button99 = new QRadioButton(verticalLayoutWidget);
        Button99->setObjectName("Button99");

        gridLayout_2->addWidget(Button99, 2, 0, 1, 1);

        var_lineEdit = new QLineEdit(verticalLayoutWidget);
        var_lineEdit->setObjectName("var_lineEdit");

        gridLayout_2->addWidget(var_lineEdit, 1, 3, 1, 1);

        label_7 = new QLabel(verticalLayoutWidget);
        label_7->setObjectName("label_7");

        gridLayout_2->addWidget(label_7, 1, 2, 1, 1);

        label_8 = new QLabel(verticalLayoutWidget);
        label_8->setObjectName("label_8");

        gridLayout_2->addWidget(label_8, 2, 2, 1, 1);

        label_6 = new QLabel(verticalLayoutWidget);
        label_6->setObjectName("label_6");

        gridLayout_2->addWidget(label_6, 0, 2, 1, 1);

        Button95 = new QRadioButton(verticalLayoutWidget);
        Button95->setObjectName("Button95");
        Button95->setEnabled(true);
        Button95->setChecked(true);
        Button95->setAutoExclusive(true);

        gridLayout_2->addWidget(Button95, 1, 0, 1, 1);

        std_lineEdit = new QLineEdit(verticalLayoutWidget);
        std_lineEdit->setObjectName("std_lineEdit");

        gridLayout_2->addWidget(std_lineEdit, 2, 3, 1, 1);

        label = new QLabel(verticalLayoutWidget);
        label->setObjectName("label");

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        label_9 = new QLabel(verticalLayoutWidget);
        label_9->setObjectName("label_9");

        gridLayout_2->addWidget(label_9, 0, 1, 1, 1);

        label_13 = new QLabel(verticalLayoutWidget);
        label_13->setObjectName("label_13");

        gridLayout_2->addWidget(label_13, 1, 1, 1, 1);

        label_14 = new QLabel(verticalLayoutWidget);
        label_14->setObjectName("label_14");

        gridLayout_2->addWidget(label_14, 2, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_10 = new QLabel(verticalLayoutWidget);
        label_10->setObjectName("label_10");

        horizontalLayout->addWidget(label_10);

        conl_lineEdit = new QLineEdit(verticalLayoutWidget);
        conl_lineEdit->setObjectName("conl_lineEdit");

        horizontalLayout->addWidget(conl_lineEdit);

        conr_lineEdit = new QLineEdit(verticalLayoutWidget);
        conr_lineEdit->setObjectName("conr_lineEdit");

        horizontalLayout->addWidget(conr_lineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_11 = new QLabel(verticalLayoutWidget);
        label_11->setObjectName("label_11");

        horizontalLayout_2->addWidget(label_11);

        acc_checkBox = new QCheckBox(verticalLayoutWidget);
        acc_checkBox->setObjectName("acc_checkBox");
        acc_checkBox->setCheckable(true);
        acc_checkBox->setChecked(false);

        horizontalLayout_2->addWidget(acc_checkBox);

        label_12 = new QLabel(verticalLayoutWidget);
        label_12->setObjectName("label_12");

        horizontalLayout_2->addWidget(label_12);

        per_checkBox = new QCheckBox(verticalLayoutWidget);
        per_checkBox->setObjectName("per_checkBox");
        per_checkBox->setCheckable(true);

        horizontalLayout_2->addWidget(per_checkBox);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        outputBox = new QTextBrowser(verticalLayoutWidget);
        outputBox->setObjectName("outputBox");

        verticalLayout_2->addWidget(outputBox);


        verticalLayout->addLayout(verticalLayout_2);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "\350\276\223\345\205\245\346\225\260\346\215\256", nullptr));
        label_3->setText(QCoreApplication::translate("Widget", "\346\217\220\345\217\226\346\225\260\346\215\256", nullptr));
        label_4->setText(QCoreApplication::translate("Widget", "\346\234\211\346\225\210\346\225\260\346\215\256", nullptr));
        label_5->setText(QCoreApplication::translate("Widget", "\346\227\240\346\225\210\346\225\260\346\215\256", nullptr));
        inputButton->setText(QCoreApplication::translate("Widget", "\350\276\223\345\205\245\346\225\260\346\215\256", nullptr));
        testButton->setText(QCoreApplication::translate("Widget", "\345\217\202\350\200\203\346\225\260\346\215\256", nullptr));
        Button99->setText(QCoreApplication::translate("Widget", "99%", nullptr));
        label_7->setText(QCoreApplication::translate("Widget", "\346\226\271\345\267\256", nullptr));
        label_8->setText(QCoreApplication::translate("Widget", "\346\240\207\345\207\206\345\267\256", nullptr));
        label_6->setText(QCoreApplication::translate("Widget", "\345\271\263\345\235\207\345\200\274", nullptr));
        Button95->setText(QCoreApplication::translate("Widget", "95%", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\347\275\256\344\277\241\346\246\202\347\216\207", nullptr));
        label_9->setText(QString());
        label_13->setText(QString());
        label_14->setText(QString());
        label_10->setText(QCoreApplication::translate("Widget", "\347\275\256\344\277\241\345\214\272\351\227\264", nullptr));
        label_11->setText(QCoreApplication::translate("Widget", "\347\264\257\350\277\233\346\200\247\350\257\257\345\267\256", nullptr));
        acc_checkBox->setText(QString());
        label_12->setText(QCoreApplication::translate("Widget", "\345\221\250\346\234\237\346\200\247\350\257\257\345\267\256", nullptr));
        per_checkBox->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
