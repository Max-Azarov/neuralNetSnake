/********************************************************************************
** Form generated from reading UI file 'mainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "snake.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QGroupBox *gBoxNN;
    QHBoxLayout *horizontalLayout;
    QLineEdit *leNumInputNN;
    QLineEdit *leNum1HiddenNN;
    QLineEdit *leNum2HiddenNN;
    QLineEdit *leNumOutputNN;
    QHBoxLayout *horizontalLayout_7;
    QGroupBox *gbTrainingSet;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lblA;
    QLineEdit *leA;
    QLabel *lblE;
    QLineEdit *leE;
    QSpacerItem *horizontalSpacer;
    QLabel *lblAcceptError;
    QLineEdit *leAcceptError;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *cbNewWeights;
    QCheckBox *cbNewTrainingData;
    QHBoxLayout *layoutSnakeSpeed;
    QSpacerItem *horizontalSpacer_3;
    QSlider *sldSnakeSpeed;
    QSpacerItem *horizontalSpacer_2;
    QLabel *lblSnakeSpeed;
    QLineEdit *leSnakeSpeed;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_6;
    Snake *snakeWindow;
    QHBoxLayout *horizontalLayout_12;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_11;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_11;
    QVBoxLayout *verticalLayout_3;
    QLabel *lblCountOfSetsTitle;
    QLabel *lblCountOfSets;
    QSpacerItem *horizontalSpacer_8;
    QVBoxLayout *verticalLayout_4;
    QLabel *lblCountOfStepsTitle;
    QLabel *lblCountOfSteps;
    QVBoxLayout *verticalLayout_5;
    QLabel *lblCountOfEatenFruitsTitle;
    QLabel *lblCountOfEatenFruits;
    QSpacerItem *horizontalSpacer_10;
    QVBoxLayout *verticalLayout_6;
    QLabel *lblAverageCountOfSetsTitle;
    QLabel *lblAverageCountOfSets;
    QSpacerItem *horizontalSpacer_12;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_9;
    QLabel *lblCountOfErrorHigherTitle;
    QTextEdit *teErrors;
    QLabel *lblErrorTitle;
    QSpacerItem *horizontalSpacer_13;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *btnStart;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *btnStop;
    QSpacerItem *horizontalSpacer_7;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(500, 840);
        MainWindow->setMinimumSize(QSize(500, 840));
        MainWindow->setMaximumSize(QSize(500, 840));
        QFont font;
        font.setPointSize(8);
        font.setBold(false);
        font.setWeight(50);
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_7 = new QVBoxLayout(centralwidget);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, -1, -1, 0);
        gBoxNN = new QGroupBox(centralwidget);
        gBoxNN->setObjectName(QString::fromUtf8("gBoxNN"));
        gBoxNN->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(gBoxNN->sizePolicy().hasHeightForWidth());
        gBoxNN->setSizePolicy(sizePolicy);
        gBoxNN->setMinimumSize(QSize(300, 52));
        gBoxNN->setMaximumSize(QSize(300, 52));
        gBoxNN->setFont(font);
        gBoxNN->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        horizontalLayout = new QHBoxLayout(gBoxNN);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
        leNumInputNN = new QLineEdit(gBoxNN);
        leNumInputNN->setObjectName(QString::fromUtf8("leNumInputNN"));
        leNumInputNN->setEnabled(false);
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(leNumInputNN->sizePolicy().hasHeightForWidth());
        leNumInputNN->setSizePolicy(sizePolicy1);
        leNumInputNN->setMinimumSize(QSize(50, 26));
        leNumInputNN->setMaximumSize(QSize(50, 26));
        leNumInputNN->setSizeIncrement(QSize(0, 0));
        leNumInputNN->setBaseSize(QSize(0, 0));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(false);
        font1.setWeight(50);
        leNumInputNN->setFont(font1);
        leNumInputNN->setAlignment(Qt::AlignCenter);
        leNumInputNN->setReadOnly(false);

        horizontalLayout->addWidget(leNumInputNN);

        leNum1HiddenNN = new QLineEdit(gBoxNN);
        leNum1HiddenNN->setObjectName(QString::fromUtf8("leNum1HiddenNN"));
        leNum1HiddenNN->setMinimumSize(QSize(50, 26));
        leNum1HiddenNN->setMaximumSize(QSize(50, 26));
        leNum1HiddenNN->setFont(font1);
        leNum1HiddenNN->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(leNum1HiddenNN);

        leNum2HiddenNN = new QLineEdit(gBoxNN);
        leNum2HiddenNN->setObjectName(QString::fromUtf8("leNum2HiddenNN"));
        leNum2HiddenNN->setMinimumSize(QSize(50, 26));
        leNum2HiddenNN->setMaximumSize(QSize(50, 26));
        leNum2HiddenNN->setFont(font1);
        leNum2HiddenNN->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(leNum2HiddenNN);

        leNumOutputNN = new QLineEdit(gBoxNN);
        leNumOutputNN->setObjectName(QString::fromUtf8("leNumOutputNN"));
        leNumOutputNN->setEnabled(false);
        leNumOutputNN->setMinimumSize(QSize(50, 26));
        leNumOutputNN->setMaximumSize(QSize(50, 26));
        leNumOutputNN->setFont(font1);
        leNumOutputNN->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(leNumOutputNN);


        horizontalLayout_5->addWidget(gBoxNN);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        gbTrainingSet = new QGroupBox(centralwidget);
        gbTrainingSet->setObjectName(QString::fromUtf8("gbTrainingSet"));
        gbTrainingSet->setMinimumSize(QSize(450, 90));
        gbTrainingSet->setMaximumSize(QSize(450, 90));
        horizontalLayout_2 = new QHBoxLayout(gbTrainingSet);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        lblA = new QLabel(gbTrainingSet);
        lblA->setObjectName(QString::fromUtf8("lblA"));
        lblA->setMinimumSize(QSize(50, 26));
        lblA->setMaximumSize(QSize(50, 26));
        lblA->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(lblA);

        leA = new QLineEdit(gbTrainingSet);
        leA->setObjectName(QString::fromUtf8("leA"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(leA->sizePolicy().hasHeightForWidth());
        leA->setSizePolicy(sizePolicy2);
        leA->setMinimumSize(QSize(50, 26));
        leA->setMaximumSize(QSize(50, 26));
        leA->setFont(font1);
        leA->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(leA);

        lblE = new QLabel(gbTrainingSet);
        lblE->setObjectName(QString::fromUtf8("lblE"));
        lblE->setMinimumSize(QSize(50, 26));
        lblE->setMaximumSize(QSize(50, 26));
        lblE->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(lblE);

        leE = new QLineEdit(gbTrainingSet);
        leE->setObjectName(QString::fromUtf8("leE"));
        sizePolicy2.setHeightForWidth(leE->sizePolicy().hasHeightForWidth());
        leE->setSizePolicy(sizePolicy2);
        leE->setMinimumSize(QSize(50, 26));
        leE->setMaximumSize(QSize(50, 26));
        leE->setFont(font1);
        leE->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(leE);

        horizontalSpacer = new QSpacerItem(110, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        lblAcceptError = new QLabel(gbTrainingSet);
        lblAcceptError->setObjectName(QString::fromUtf8("lblAcceptError"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(lblAcceptError->sizePolicy().hasHeightForWidth());
        lblAcceptError->setSizePolicy(sizePolicy3);
        lblAcceptError->setMinimumSize(QSize(0, 26));
        lblAcceptError->setMaximumSize(QSize(36667, 26));
        lblAcceptError->setContextMenuPolicy(Qt::DefaultContextMenu);
        lblAcceptError->setTextFormat(Qt::AutoText);
        lblAcceptError->setScaledContents(false);
        lblAcceptError->setAlignment(Qt::AlignCenter);
        lblAcceptError->setWordWrap(false);
        lblAcceptError->setMargin(0);
        lblAcceptError->setIndent(-1);
        lblAcceptError->setOpenExternalLinks(false);
        lblAcceptError->setTextInteractionFlags(Qt::LinksAccessibleByMouse);

        horizontalLayout_3->addWidget(lblAcceptError);

        leAcceptError = new QLineEdit(gbTrainingSet);
        leAcceptError->setObjectName(QString::fromUtf8("leAcceptError"));
        sizePolicy2.setHeightForWidth(leAcceptError->sizePolicy().hasHeightForWidth());
        leAcceptError->setSizePolicy(sizePolicy2);
        leAcceptError->setMinimumSize(QSize(50, 26));
        leAcceptError->setMaximumSize(QSize(50, 26));
        leAcceptError->setFont(font1);
        leAcceptError->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(leAcceptError);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        cbNewWeights = new QCheckBox(gbTrainingSet);
        cbNewWeights->setObjectName(QString::fromUtf8("cbNewWeights"));
        cbNewWeights->setMinimumSize(QSize(0, 15));
        cbNewWeights->setMaximumSize(QSize(36667, 15));

        horizontalLayout_4->addWidget(cbNewWeights);

        cbNewTrainingData = new QCheckBox(gbTrainingSet);
        cbNewTrainingData->setObjectName(QString::fromUtf8("cbNewTrainingData"));
        cbNewTrainingData->setMinimumSize(QSize(0, 15));
        cbNewTrainingData->setMaximumSize(QSize(36667, 15));

        horizontalLayout_4->addWidget(cbNewTrainingData);


        verticalLayout->addLayout(horizontalLayout_4);


        horizontalLayout_2->addLayout(verticalLayout);


        horizontalLayout_7->addWidget(gbTrainingSet);


        verticalLayout_2->addLayout(horizontalLayout_7);

        layoutSnakeSpeed = new QHBoxLayout();
        layoutSnakeSpeed->setSpacing(5);
        layoutSnakeSpeed->setObjectName(QString::fromUtf8("layoutSnakeSpeed"));
        layoutSnakeSpeed->setSizeConstraint(QLayout::SetFixedSize);
        layoutSnakeSpeed->setContentsMargins(5, 5, 5, 5);
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        layoutSnakeSpeed->addItem(horizontalSpacer_3);

        sldSnakeSpeed = new QSlider(centralwidget);
        sldSnakeSpeed->setObjectName(QString::fromUtf8("sldSnakeSpeed"));
        sldSnakeSpeed->setMinimumSize(QSize(200, 26));
        sldSnakeSpeed->setMaximumSize(QSize(200, 26));
        sldSnakeSpeed->setMinimum(1);
        sldSnakeSpeed->setMaximum(100);
        sldSnakeSpeed->setValue(10);
        sldSnakeSpeed->setOrientation(Qt::Horizontal);

        layoutSnakeSpeed->addWidget(sldSnakeSpeed);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        layoutSnakeSpeed->addItem(horizontalSpacer_2);

        lblSnakeSpeed = new QLabel(centralwidget);
        lblSnakeSpeed->setObjectName(QString::fromUtf8("lblSnakeSpeed"));
        sizePolicy3.setHeightForWidth(lblSnakeSpeed->sizePolicy().hasHeightForWidth());
        lblSnakeSpeed->setSizePolicy(sizePolicy3);
        lblSnakeSpeed->setMinimumSize(QSize(0, 26));
        lblSnakeSpeed->setMaximumSize(QSize(36667, 26));
        lblSnakeSpeed->setContextMenuPolicy(Qt::DefaultContextMenu);
        lblSnakeSpeed->setTextFormat(Qt::AutoText);
        lblSnakeSpeed->setScaledContents(false);
        lblSnakeSpeed->setAlignment(Qt::AlignCenter);
        lblSnakeSpeed->setWordWrap(false);
        lblSnakeSpeed->setMargin(0);
        lblSnakeSpeed->setIndent(-1);
        lblSnakeSpeed->setOpenExternalLinks(false);
        lblSnakeSpeed->setTextInteractionFlags(Qt::LinksAccessibleByMouse);

        layoutSnakeSpeed->addWidget(lblSnakeSpeed);

        leSnakeSpeed = new QLineEdit(centralwidget);
        leSnakeSpeed->setObjectName(QString::fromUtf8("leSnakeSpeed"));
        sizePolicy2.setHeightForWidth(leSnakeSpeed->sizePolicy().hasHeightForWidth());
        leSnakeSpeed->setSizePolicy(sizePolicy2);
        leSnakeSpeed->setMinimumSize(QSize(50, 26));
        leSnakeSpeed->setMaximumSize(QSize(50, 26));
        leSnakeSpeed->setFont(font1);
        leSnakeSpeed->setAlignment(Qt::AlignCenter);

        layoutSnakeSpeed->addWidget(leSnakeSpeed);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        layoutSnakeSpeed->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(layoutSnakeSpeed);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setSizeConstraint(QLayout::SetMinimumSize);
        snakeWindow = new Snake(centralwidget);
        snakeWindow->setObjectName(QString::fromUtf8("snakeWindow"));
        snakeWindow->setMinimumSize(QSize(400, 400));
        snakeWindow->setMaximumSize(QSize(400, 400));

        horizontalLayout_6->addWidget(snakeWindow);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(0);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        horizontalLayout_12->setSizeConstraint(QLayout::SetFixedSize);
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy4);
        groupBox->setMinimumSize(QSize(0, 70));
        groupBox->setMaximumSize(QSize(16777215, 70));
        horizontalLayout_11 = new QHBoxLayout(groupBox);
        horizontalLayout_11->setSpacing(0);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalLayout_11->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalLayout_11->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_11);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        lblCountOfSetsTitle = new QLabel(groupBox);
        lblCountOfSetsTitle->setObjectName(QString::fromUtf8("lblCountOfSetsTitle"));
        lblCountOfSetsTitle->setMinimumSize(QSize(0, 40));
        lblCountOfSetsTitle->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        verticalLayout_3->addWidget(lblCountOfSetsTitle);

        lblCountOfSets = new QLabel(groupBox);
        lblCountOfSets->setObjectName(QString::fromUtf8("lblCountOfSets"));
        lblCountOfSets->setMinimumSize(QSize(0, 15));
        lblCountOfSets->setMaximumSize(QSize(16777215, 20));
        lblCountOfSets->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(lblCountOfSets);


        horizontalLayout_9->addLayout(verticalLayout_3);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_8);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(2);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        lblCountOfStepsTitle = new QLabel(groupBox);
        lblCountOfStepsTitle->setObjectName(QString::fromUtf8("lblCountOfStepsTitle"));
        lblCountOfStepsTitle->setMinimumSize(QSize(0, 40));
        lblCountOfStepsTitle->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        verticalLayout_4->addWidget(lblCountOfStepsTitle);

        lblCountOfSteps = new QLabel(groupBox);
        lblCountOfSteps->setObjectName(QString::fromUtf8("lblCountOfSteps"));
        lblCountOfSteps->setMinimumSize(QSize(0, 15));
        lblCountOfSteps->setMaximumSize(QSize(16777215, 20));
        lblCountOfSteps->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(lblCountOfSteps);


        horizontalLayout_9->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(2);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        lblCountOfEatenFruitsTitle = new QLabel(groupBox);
        lblCountOfEatenFruitsTitle->setObjectName(QString::fromUtf8("lblCountOfEatenFruitsTitle"));
        lblCountOfEatenFruitsTitle->setMinimumSize(QSize(0, 40));
        lblCountOfEatenFruitsTitle->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        verticalLayout_5->addWidget(lblCountOfEatenFruitsTitle);

        lblCountOfEatenFruits = new QLabel(groupBox);
        lblCountOfEatenFruits->setObjectName(QString::fromUtf8("lblCountOfEatenFruits"));
        lblCountOfEatenFruits->setMinimumSize(QSize(0, 15));
        lblCountOfEatenFruits->setMaximumSize(QSize(16777215, 20));
        lblCountOfEatenFruits->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(lblCountOfEatenFruits);


        horizontalLayout_9->addLayout(verticalLayout_5);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_10);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(2);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        lblAverageCountOfSetsTitle = new QLabel(groupBox);
        lblAverageCountOfSetsTitle->setObjectName(QString::fromUtf8("lblAverageCountOfSetsTitle"));
        lblAverageCountOfSetsTitle->setMinimumSize(QSize(0, 40));
        lblAverageCountOfSetsTitle->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        verticalLayout_6->addWidget(lblAverageCountOfSetsTitle);

        lblAverageCountOfSets = new QLabel(groupBox);
        lblAverageCountOfSets->setObjectName(QString::fromUtf8("lblAverageCountOfSets"));
        lblAverageCountOfSets->setMinimumSize(QSize(0, 15));
        lblAverageCountOfSets->setMaximumSize(QSize(16777215, 20));
        lblAverageCountOfSets->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(lblAverageCountOfSets);


        horizontalLayout_9->addLayout(verticalLayout_6);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_12);

        horizontalLayout_9->setStretch(0, 1);
        horizontalLayout_9->setStretch(1, 5);
        horizontalLayout_9->setStretch(2, 1);
        horizontalLayout_9->setStretch(3, 5);
        horizontalLayout_9->setStretch(4, 5);
        horizontalLayout_9->setStretch(5, 1);
        horizontalLayout_9->setStretch(6, 5);
        horizontalLayout_9->setStretch(7, 1);

        horizontalLayout_11->addLayout(horizontalLayout_9);


        horizontalLayout_12->addWidget(groupBox);


        verticalLayout_2->addLayout(horizontalLayout_12);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_9);

        lblCountOfErrorHigherTitle = new QLabel(centralwidget);
        lblCountOfErrorHigherTitle->setObjectName(QString::fromUtf8("lblCountOfErrorHigherTitle"));
        lblCountOfErrorHigherTitle->setMaximumSize(QSize(16777215, 80));
        lblCountOfErrorHigherTitle->setAlignment(Qt::AlignCenter);

        horizontalLayout_10->addWidget(lblCountOfErrorHigherTitle);

        teErrors = new QTextEdit(centralwidget);
        teErrors->setObjectName(QString::fromUtf8("teErrors"));
        teErrors->setMaximumSize(QSize(16777215, 60));
        teErrors->setReadOnly(true);

        horizontalLayout_10->addWidget(teErrors);

        lblErrorTitle = new QLabel(centralwidget);
        lblErrorTitle->setObjectName(QString::fromUtf8("lblErrorTitle"));
        lblErrorTitle->setMaximumSize(QSize(16777215, 80));
        lblErrorTitle->setAlignment(Qt::AlignCenter);

        horizontalLayout_10->addWidget(lblErrorTitle);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_13);

        horizontalLayout_10->setStretch(0, 1);
        horizontalLayout_10->setStretch(1, 1);
        horizontalLayout_10->setStretch(2, 5);
        horizontalLayout_10->setStretch(3, 1);
        horizontalLayout_10->setStretch(4, 1);

        verticalLayout_2->addLayout(horizontalLayout_10);

        verticalSpacer = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_6);

        btnStart = new QPushButton(centralwidget);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(btnStart->sizePolicy().hasHeightForWidth());
        btnStart->setSizePolicy(sizePolicy5);
        btnStart->setMinimumSize(QSize(0, 0));
        btnStart->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_8->addWidget(btnStart);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_5);

        btnStop = new QPushButton(centralwidget);
        btnStop->setObjectName(QString::fromUtf8("btnStop"));
        btnStop->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_8->addWidget(btnStop);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_7);

        horizontalLayout_8->setStretch(0, 1);
        horizontalLayout_8->setStretch(1, 1);
        horizontalLayout_8->setStretch(2, 1);
        horizontalLayout_8->setStretch(3, 1);
        horizontalLayout_8->setStretch(4, 1);

        verticalLayout_2->addLayout(horizontalLayout_8);


        verticalLayout_7->addLayout(verticalLayout_2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setEnabled(false);
        menubar->setGeometry(QRect(0, 0, 500, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        statusbar->setEnabled(false);
        MainWindow->setStatusBar(statusbar);
        QWidget::setTabOrder(btnStart, btnStop);
        QWidget::setTabOrder(btnStop, sldSnakeSpeed);
        QWidget::setTabOrder(sldSnakeSpeed, leSnakeSpeed);
        QWidget::setTabOrder(leSnakeSpeed, leNum1HiddenNN);
        QWidget::setTabOrder(leNum1HiddenNN, leNum2HiddenNN);
        QWidget::setTabOrder(leNum2HiddenNN, leA);
        QWidget::setTabOrder(leA, leE);
        QWidget::setTabOrder(leE, leAcceptError);
        QWidget::setTabOrder(leAcceptError, cbNewWeights);
        QWidget::setTabOrder(cbNewWeights, cbNewTrainingData);
        QWidget::setTabOrder(cbNewTrainingData, leNumInputNN);
        QWidget::setTabOrder(leNumInputNN, leNumOutputNN);
        QWidget::setTabOrder(leNumOutputNN, teErrors);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "smartSnake", nullptr));
#if QT_CONFIG(tooltip)
        gBoxNN->setToolTip(QCoreApplication::translate("MainWindow", "Neural net parameters", nullptr));
#endif // QT_CONFIG(tooltip)
        gBoxNN->setTitle(QCoreApplication::translate("MainWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \320\275\320\265\320\271\321\200\320\276\321\201\320\265\321\202\320\270", nullptr));
#if QT_CONFIG(tooltip)
        leNumInputNN->setToolTip(QCoreApplication::translate("MainWindow", "Count of inputs neural net (equal to the number of cells on the screen)", nullptr));
#endif // QT_CONFIG(tooltip)
        leNumInputNN->setText(QCoreApplication::translate("MainWindow", "100", nullptr));
#if QT_CONFIG(tooltip)
        leNum1HiddenNN->setToolTip(QCoreApplication::translate("MainWindow", "Count of neurons in the first hidden layer", nullptr));
#endif // QT_CONFIG(tooltip)
        leNum1HiddenNN->setText(QCoreApplication::translate("MainWindow", "100", nullptr));
#if QT_CONFIG(tooltip)
        leNum2HiddenNN->setToolTip(QCoreApplication::translate("MainWindow", "Count of neurons in the second hidden layer", nullptr));
#endif // QT_CONFIG(tooltip)
        leNum2HiddenNN->setText(QCoreApplication::translate("MainWindow", "200", nullptr));
#if QT_CONFIG(tooltip)
        leNumOutputNN->setToolTip(QCoreApplication::translate("MainWindow", "Count of outputs neural net (equal to the number of possible directions: right, left, up, down)", nullptr));
#endif // QT_CONFIG(tooltip)
        leNumOutputNN->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        gbTrainingSet->setTitle(QCoreApplication::translate("MainWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \320\276\320\261\321\203\321\207\320\265\320\275\320\270\321\217", nullptr));
#if QT_CONFIG(tooltip)
        lblA->setToolTip(QCoreApplication::translate("MainWindow", "The learning rate of the neural network", nullptr));
#endif // QT_CONFIG(tooltip)
        lblA->setText(QCoreApplication::translate("MainWindow", "A = ", nullptr));
#if QT_CONFIG(tooltip)
        leA->setToolTip(QCoreApplication::translate("MainWindow", "The learning rate of the neural network", nullptr));
#endif // QT_CONFIG(tooltip)
        leA->setText(QCoreApplication::translate("MainWindow", "0.1", nullptr));
#if QT_CONFIG(tooltip)
        lblE->setToolTip(QCoreApplication::translate("MainWindow", "The learning moment of the neural network", nullptr));
#endif // QT_CONFIG(tooltip)
        lblE->setText(QCoreApplication::translate("MainWindow", "E = ", nullptr));
#if QT_CONFIG(tooltip)
        leE->setToolTip(QCoreApplication::translate("MainWindow", "The learning moment of the neural network", nullptr));
#endif // QT_CONFIG(tooltip)
        leE->setText(QCoreApplication::translate("MainWindow", "0.05", nullptr));
#if QT_CONFIG(tooltip)
        lblAcceptError->setToolTip(QCoreApplication::translate("MainWindow", "Acceptable error", nullptr));
#endif // QT_CONFIG(tooltip)
        lblAcceptError->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\277\321\203\321\201\321\202\320\270\320\274\320\260\321\217\n"
"\320\276\321\210\320\270\320\261\320\272\320\260", nullptr));
        leAcceptError->setText(QCoreApplication::translate("MainWindow", "0.02", nullptr));
#if QT_CONFIG(tooltip)
        cbNewWeights->setToolTip(QCoreApplication::translate("MainWindow", "Do need to assign new random weights to synapses", nullptr));
#endif // QT_CONFIG(tooltip)
        cbNewWeights->setText(QCoreApplication::translate("MainWindow", "\320\235\320\276\320\262\321\213\320\265 \320\262\320\265\321\201\320\260 \321\201\320\270\320\275\320\260\320\277\321\201\320\276\320\262", nullptr));
#if QT_CONFIG(tooltip)
        cbNewTrainingData->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Do need to assign new training data for neural network training (the existing training set is deleted)</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        cbNewTrainingData->setText(QCoreApplication::translate("MainWindow", "\320\235\320\276\320\262\320\260\321\217 \320\276\320\261\321\203\321\207\320\260\321\216\321\211\320\260\321\217 \320\262\321\213\320\261\320\276\321\200\320\272\320\260", nullptr));
#if QT_CONFIG(tooltip)
        lblSnakeSpeed->setToolTip(QCoreApplication::translate("MainWindow", "Snake speed in steps per second", nullptr));
#endif // QT_CONFIG(tooltip)
        lblSnakeSpeed->setText(QCoreApplication::translate("MainWindow", "\320\241\320\272\320\276\321\200\320\276\321\201\321\202\321\214\n"
"\320\267\320\274\320\265\320\271\320\272\320\270", nullptr));
#if QT_CONFIG(tooltip)
        leSnakeSpeed->setToolTip(QCoreApplication::translate("MainWindow", "Snake speed in steps per second", nullptr));
#endif // QT_CONFIG(tooltip)
        leSnakeSpeed->setText(QCoreApplication::translate("MainWindow", "10", nullptr));
        groupBox->setTitle(QString());
#if QT_CONFIG(tooltip)
        lblCountOfSetsTitle->setToolTip(QCoreApplication::translate("MainWindow", "Count of runs contained in the training set", nullptr));
#endif // QT_CONFIG(tooltip)
        lblCountOfSetsTitle->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276\n"
"\320\277\321\203\321\201\320\272\320\276\320\262", nullptr));
#if QT_CONFIG(tooltip)
        lblCountOfSets->setToolTip(QCoreApplication::translate("MainWindow", "Count of runs contained in the training set", nullptr));
#endif // QT_CONFIG(tooltip)
        lblCountOfSets->setText(QString());
#if QT_CONFIG(tooltip)
        lblCountOfStepsTitle->setToolTip(QCoreApplication::translate("MainWindow", "Number of steps completed by snakes in the current run", nullptr));
#endif // QT_CONFIG(tooltip)
        lblCountOfStepsTitle->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276\n"
"\321\210\320\260\320\263\320\276\320\262", nullptr));
#if QT_CONFIG(tooltip)
        lblCountOfSteps->setToolTip(QCoreApplication::translate("MainWindow", "Number of steps completed by snakes in the current run", nullptr));
#endif // QT_CONFIG(tooltip)
        lblCountOfSteps->setText(QString());
#if QT_CONFIG(tooltip)
        lblCountOfEatenFruitsTitle->setToolTip(QCoreApplication::translate("MainWindow", "The number of fruits eaten in the current run", nullptr));
#endif // QT_CONFIG(tooltip)
        lblCountOfEatenFruitsTitle->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276\n"
"\321\201\321\212\320\265\320\264\320\265\320\275\320\275\321\213\321\205\n"
"\321\204\321\200\321\203\320\272\321\202\320\276\320\262", nullptr));
#if QT_CONFIG(tooltip)
        lblCountOfEatenFruits->setToolTip(QCoreApplication::translate("MainWindow", "The number of fruits eaten in the current run", nullptr));
#endif // QT_CONFIG(tooltip)
        lblCountOfEatenFruits->setText(QString());
#if QT_CONFIG(tooltip)
        lblAverageCountOfSetsTitle->setToolTip(QCoreApplication::translate("MainWindow", "The average number of steps of the snake, starting with waking up", nullptr));
#endif // QT_CONFIG(tooltip)
        lblAverageCountOfSetsTitle->setText(QCoreApplication::translate("MainWindow", "\320\241\321\200\320\265\320\264\320\275\320\265\320\265\n"
"\320\272\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276\n"
"\321\210\320\260\320\263\320\276\320\262", nullptr));
#if QT_CONFIG(tooltip)
        lblAverageCountOfSets->setToolTip(QCoreApplication::translate("MainWindow", "The average number of steps of the snake, starting with waking up", nullptr));
#endif // QT_CONFIG(tooltip)
        lblAverageCountOfSets->setText(QString());
#if QT_CONFIG(tooltip)
        lblCountOfErrorHigherTitle->setToolTip(QCoreApplication::translate("MainWindow", "Count of runs contained in the training set", nullptr));
#endif // QT_CONFIG(tooltip)
        lblCountOfErrorHigherTitle->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276\n"
"\321\201\320\273\321\203\321\207\320\260\320\265\320\262\n"
"\321\201 \320\277\321\200\320\265\320\262\321\213\321\210\320\265\320\275\320\270\320\265\320\274\n"
"\320\264\320\276\320\277\321\203\321\201\321\202\320\270\320\274\320\276\320\271\n"
"\320\276\321\210\320\270\320\261\320\272\320\270", nullptr));
#if QT_CONFIG(tooltip)
        lblErrorTitle->setToolTip(QCoreApplication::translate("MainWindow", "Count of runs contained in the training set", nullptr));
#endif // QT_CONFIG(tooltip)
        lblErrorTitle->setText(QCoreApplication::translate("MainWindow", "\320\227\320\275\320\260\321\207\320\265\320\275\320\270\320\265\n"
"\320\276\321\210\320\270\320\261\320\272\320\270\n"
"\320\267\320\260 \321\202\320\265\320\272\321\203\321\211\321\203\321\216\n"
"\321\215\320\277\320\276\321\205\321\203", nullptr));
        btnStart->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\260\321\200\321\202", nullptr));
        btnStop->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\276\320\277", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
