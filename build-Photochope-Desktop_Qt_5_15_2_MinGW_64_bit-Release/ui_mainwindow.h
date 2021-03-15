/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QPushButton *pushButton;
    QLabel *label_2;
    QPushButton *pushButton_6;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton_5;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_8;
    QPushButton *pushButton_7;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton_4;
    QPushButton *pushButton_3;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QPushButton *pushButton_11;
    QPushButton *pushButton_12;
    QPushButton *pushButton_13;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *kernel1;
    QLineEdit *kernel2;
    QLineEdit *kernel3;
    QLineEdit *kernel4;
    QLineEdit *kernel5;
    QLineEdit *kernel6;
    QLineEdit *kernel7;
    QLineEdit *kernel8;
    QLineEdit *kernel9;
    QPushButton *pushButton_14;
    QPushButton *pushButton_15;
    QPushButton *pushButton_16;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QPushButton *pushButton_17;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1292, 725);
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("icon");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        MainWindow->setWindowIcon(icon);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(60, 50, 391, 10));
        label->setMaximumSize(QSize(16777215, 16777215));
        label->setScaledContents(true);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(250, 10, 111, 23));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(490, 50, 371, 10));
        label_2->setMaximumSize(QSize(16777215, 16777215));
        label_2->setScaledContents(true);
        pushButton_6 = new QPushButton(centralwidget);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(620, 10, 111, 23));
        gridLayoutWidget_2 = new QWidget(centralwidget);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(410, 560, 201, 109));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton_5 = new QPushButton(gridLayoutWidget_2);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

        gridLayout_2->addWidget(pushButton_5, 2, 1, 1, 1);

        lineEdit_2 = new QLineEdit(gridLayoutWidget_2);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        gridLayout_2->addWidget(lineEdit_2, 1, 0, 1, 1);

        pushButton_8 = new QPushButton(gridLayoutWidget_2);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));

        gridLayout_2->addWidget(pushButton_8, 1, 1, 1, 1);

        pushButton_7 = new QPushButton(gridLayoutWidget_2);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));

        gridLayout_2->addWidget(pushButton_7, 0, 1, 1, 1);

        lineEdit = new QLineEdit(gridLayoutWidget_2);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout_2->addWidget(lineEdit, 2, 0, 1, 1);

        lineEdit_3 = new QLineEdit(gridLayoutWidget_2);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        gridLayout_2->addWidget(lineEdit_3, 0, 0, 1, 1);

        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(170, 570, 87, 23));
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(50, 580, 86, 23));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(50, 620, 87, 23));
        pushButton_9 = new QPushButton(centralwidget);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setGeometry(QRect(170, 610, 86, 23));
        pushButton_10 = new QPushButton(centralwidget);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));
        pushButton_10->setGeometry(QRect(420, 10, 75, 23));
        pushButton_11 = new QPushButton(centralwidget);
        pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));
        pushButton_11->setGeometry(QRect(270, 570, 75, 23));
        pushButton_12 = new QPushButton(centralwidget);
        pushButton_12->setObjectName(QString::fromUtf8("pushButton_12"));
        pushButton_12->setGeometry(QRect(270, 610, 75, 23));
        pushButton_13 = new QPushButton(centralwidget);
        pushButton_13->setObjectName(QString::fromUtf8("pushButton_13"));
        pushButton_13->setGeometry(QRect(210, 640, 111, 23));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(710, 530, 188, 131));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        kernel1 = new QLineEdit(gridLayoutWidget);
        kernel1->setObjectName(QString::fromUtf8("kernel1"));

        gridLayout->addWidget(kernel1, 0, 0, 1, 1);

        kernel2 = new QLineEdit(gridLayoutWidget);
        kernel2->setObjectName(QString::fromUtf8("kernel2"));

        gridLayout->addWidget(kernel2, 0, 1, 1, 1);

        kernel3 = new QLineEdit(gridLayoutWidget);
        kernel3->setObjectName(QString::fromUtf8("kernel3"));

        gridLayout->addWidget(kernel3, 0, 2, 1, 1);

        kernel4 = new QLineEdit(gridLayoutWidget);
        kernel4->setObjectName(QString::fromUtf8("kernel4"));

        gridLayout->addWidget(kernel4, 1, 0, 1, 1);

        kernel5 = new QLineEdit(gridLayoutWidget);
        kernel5->setObjectName(QString::fromUtf8("kernel5"));

        gridLayout->addWidget(kernel5, 1, 1, 1, 1);

        kernel6 = new QLineEdit(gridLayoutWidget);
        kernel6->setObjectName(QString::fromUtf8("kernel6"));

        gridLayout->addWidget(kernel6, 1, 2, 1, 1);

        kernel7 = new QLineEdit(gridLayoutWidget);
        kernel7->setObjectName(QString::fromUtf8("kernel7"));

        gridLayout->addWidget(kernel7, 2, 0, 1, 1);

        kernel8 = new QLineEdit(gridLayoutWidget);
        kernel8->setObjectName(QString::fromUtf8("kernel8"));

        gridLayout->addWidget(kernel8, 2, 1, 1, 1);

        kernel9 = new QLineEdit(gridLayoutWidget);
        kernel9->setObjectName(QString::fromUtf8("kernel9"));

        gridLayout->addWidget(kernel9, 2, 2, 1, 1);

        pushButton_14 = new QPushButton(centralwidget);
        pushButton_14->setObjectName(QString::fromUtf8("pushButton_14"));
        pushButton_14->setGeometry(QRect(900, 580, 75, 23));
        pushButton_15 = new QPushButton(centralwidget);
        pushButton_15->setObjectName(QString::fromUtf8("pushButton_15"));
        pushButton_15->setGeometry(QRect(50, 650, 91, 23));
        pushButton_16 = new QPushButton(centralwidget);
        pushButton_16->setObjectName(QString::fromUtf8("pushButton_16"));
        pushButton_16->setGeometry(QRect(1190, 550, 75, 23));
        lineEdit_4 = new QLineEdit(centralwidget);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(1060, 540, 118, 20));
        lineEdit_5 = new QLineEdit(centralwidget);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(1060, 570, 118, 20));
        pushButton_17 = new QPushButton(centralwidget);
        pushButton_17->setObjectName(QString::fromUtf8("pushButton_17"));
        pushButton_17->setGeometry(QRect(1190, 620, 75, 23));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1292, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Photochope", nullptr));
#if QT_CONFIG(tooltip)
        MainWindow->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        label->setText(QString());
        pushButton->setText(QCoreApplication::translate("MainWindow", "Select image", nullptr));
        label_2->setText(QString());
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "Save JPEG", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Quantization", nullptr));
#if QT_CONFIG(tooltip)
        lineEdit_2->setToolTip(QCoreApplication::translate("MainWindow", "a", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "Contrast", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "Brightness", nullptr));
#if QT_CONFIG(tooltip)
        lineEdit->setToolTip(QCoreApplication::translate("MainWindow", "a", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        lineEdit_3->setToolTip(QCoreApplication::translate("MainWindow", "a", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Grey", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Flip Vertically", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Flip Horizontally", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "Negative", nullptr));
        pushButton_10->setText(QCoreApplication::translate("MainWindow", "Copy image", nullptr));
        pushButton_11->setText(QCoreApplication::translate("MainWindow", "Histogram", nullptr));
        pushButton_12->setText(QCoreApplication::translate("MainWindow", "Equalization", nullptr));
        pushButton_13->setText(QCoreApplication::translate("MainWindow", "Histogram Matching", nullptr));
#if QT_CONFIG(tooltip)
        kernel1->setToolTip(QCoreApplication::translate("MainWindow", "a", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        kernel2->setToolTip(QCoreApplication::translate("MainWindow", "a", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        kernel3->setToolTip(QCoreApplication::translate("MainWindow", "a", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        kernel4->setToolTip(QCoreApplication::translate("MainWindow", "a", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        kernel5->setToolTip(QCoreApplication::translate("MainWindow", "a", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        kernel6->setToolTip(QCoreApplication::translate("MainWindow", "a", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        kernel7->setToolTip(QCoreApplication::translate("MainWindow", "a", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        kernel8->setToolTip(QCoreApplication::translate("MainWindow", "a", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        kernel9->setToolTip(QCoreApplication::translate("MainWindow", "a", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_14->setText(QCoreApplication::translate("MainWindow", "Convolution", nullptr));
        pushButton_15->setText(QCoreApplication::translate("MainWindow", "Turn 90 Degrees", nullptr));
        pushButton_16->setText(QCoreApplication::translate("MainWindow", "Zoom Out", nullptr));
#if QT_CONFIG(tooltip)
        lineEdit_4->setToolTip(QCoreApplication::translate("MainWindow", "a", nullptr));
#endif // QT_CONFIG(tooltip)
        lineEdit_4->setPlaceholderText(QCoreApplication::translate("MainWindow", "Sx", nullptr));
#if QT_CONFIG(tooltip)
        lineEdit_5->setToolTip(QCoreApplication::translate("MainWindow", "a", nullptr));
#endif // QT_CONFIG(tooltip)
        lineEdit_5->setPlaceholderText(QCoreApplication::translate("MainWindow", "Sy", nullptr));
        pushButton_17->setText(QCoreApplication::translate("MainWindow", "Zoom In", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
