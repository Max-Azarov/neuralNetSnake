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
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <snake.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *gBoxNN;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *leNumInputNN;
    QLineEdit *leNum1HiddenNN;
    QLineEdit *leNum2HiddenNN;
    QLineEdit *leNumOutputNN;
    QCheckBox *cbNewWeights;
    QLabel *lblAcceptError_2;
    QLineEdit *leNum2HiddenNN_2;
    QGroupBox *gbTrainingSet;
    QHBoxLayout *horizontalLayout_5;
    QLabel *lblA;
    QLineEdit *leA;
    QLabel *lblE;
    QLineEdit *leE;
    QCheckBox *cbNewTrainingData;
    QLabel *lblAcceptError;
    QLineEdit *leAcceptError;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_2;
    QLabel *lblSnakeSpeed;
    QCheckBox *cbSnakeSpeed;
    QLineEdit *leSnakeSpeed;
    QSlider *sldSnakeSpeed;
    Snake *snake;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout;
    QLabel *lblCountOfSetsTitle;
    QLabel *lblCountOfSets;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lblCountOfStepsTitle;
    QLabel *lblCountOfSteps;
    QHBoxLayout *horizontalLayout_4;
    QLabel *lblCountOfEatenFruitsTitle;
    QLabel *lblCountOfEatenFruits;
    QHBoxLayout *horizontalLayout_6;
    QLabel *lblAverageCountOfSetsTitle;
    QLabel *lblAverageCountOfSets;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_9;
    QLabel *lblCountOfErrorHigherTitle;
    QTextEdit *teErrors;
    QLabel *lblErrorTitle;
    QSpacerItem *horizontalSpacer_13;
    QPushButton *btnStart;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(600, 691);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(600, 691));
        MainWindow->setMaximumSize(QSize(600, 691));
        QFont font;
        font.setPointSize(8);
        font.setBold(false);
        font.setWeight(50);
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        centralwidget->setMinimumSize(QSize(600, 650));
        centralwidget->setMaximumSize(QSize(600, 650));
        verticalLayout_4 = new QVBoxLayout(centralwidget);
        verticalLayout_4->setSpacing(4);
        verticalLayout_4->setContentsMargins(6, 6, 6, 6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        gBoxNN = new QGroupBox(centralwidget);
        gBoxNN->setObjectName(QString::fromUtf8("gBoxNN"));
        gBoxNN->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(gBoxNN->sizePolicy().hasHeightForWidth());
        gBoxNN->setSizePolicy(sizePolicy1);
        gBoxNN->setMinimumSize(QSize(0, 55));
        gBoxNN->setMaximumSize(QSize(1000, 80));
        gBoxNN->setFont(font);
        gBoxNN->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        horizontalLayout_3 = new QHBoxLayout(gBoxNN);
        horizontalLayout_3->setSpacing(4);
        horizontalLayout_3->setContentsMargins(6, 6, 6, 6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        leNumInputNN = new QLineEdit(gBoxNN);
        leNumInputNN->setObjectName(QString::fromUtf8("leNumInputNN"));
        leNumInputNN->setEnabled(false);
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(leNumInputNN->sizePolicy().hasHeightForWidth());
        leNumInputNN->setSizePolicy(sizePolicy2);
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

        horizontalLayout_3->addWidget(leNumInputNN);

        leNum1HiddenNN = new QLineEdit(gBoxNN);
        leNum1HiddenNN->setObjectName(QString::fromUtf8("leNum1HiddenNN"));
        leNum1HiddenNN->setMinimumSize(QSize(50, 26));
        leNum1HiddenNN->setMaximumSize(QSize(50, 26));
        leNum1HiddenNN->setFont(font1);
        leNum1HiddenNN->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(leNum1HiddenNN);

        leNum2HiddenNN = new QLineEdit(gBoxNN);
        leNum2HiddenNN->setObjectName(QString::fromUtf8("leNum2HiddenNN"));
        leNum2HiddenNN->setMinimumSize(QSize(50, 26));
        leNum2HiddenNN->setMaximumSize(QSize(50, 26));
        leNum2HiddenNN->setFont(font1);
        leNum2HiddenNN->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(leNum2HiddenNN);

        leNumOutputNN = new QLineEdit(gBoxNN);
        leNumOutputNN->setObjectName(QString::fromUtf8("leNumOutputNN"));
        leNumOutputNN->setEnabled(false);
        leNumOutputNN->setMinimumSize(QSize(50, 26));
        leNumOutputNN->setMaximumSize(QSize(50, 26));
        leNumOutputNN->setFont(font1);
        leNumOutputNN->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(leNumOutputNN);

        cbNewWeights = new QCheckBox(gBoxNN);
        cbNewWeights->setObjectName(QString::fromUtf8("cbNewWeights"));
        cbNewWeights->setMinimumSize(QSize(0, 15));
        cbNewWeights->setMaximumSize(QSize(16666, 15));

        horizontalLayout_3->addWidget(cbNewWeights);

        lblAcceptError_2 = new QLabel(gBoxNN);
        lblAcceptError_2->setObjectName(QString::fromUtf8("lblAcceptError_2"));
        sizePolicy.setHeightForWidth(lblAcceptError_2->sizePolicy().hasHeightForWidth());
        lblAcceptError_2->setSizePolicy(sizePolicy);
        lblAcceptError_2->setMinimumSize(QSize(0, 26));
        lblAcceptError_2->setMaximumSize(QSize(1000, 26));
        QFont font2;
        font2.setPointSize(8);
        lblAcceptError_2->setFont(font2);
        lblAcceptError_2->setContextMenuPolicy(Qt::DefaultContextMenu);
        lblAcceptError_2->setTextFormat(Qt::AutoText);
        lblAcceptError_2->setScaledContents(false);
        lblAcceptError_2->setAlignment(Qt::AlignCenter);
        lblAcceptError_2->setWordWrap(false);
        lblAcceptError_2->setMargin(0);
        lblAcceptError_2->setIndent(-1);
        lblAcceptError_2->setOpenExternalLinks(false);
        lblAcceptError_2->setTextInteractionFlags(Qt::LinksAccessibleByMouse);

        horizontalLayout_3->addWidget(lblAcceptError_2, 0, Qt::AlignRight);

        leNum2HiddenNN_2 = new QLineEdit(gBoxNN);
        leNum2HiddenNN_2->setObjectName(QString::fromUtf8("leNum2HiddenNN_2"));
        leNum2HiddenNN_2->setMinimumSize(QSize(50, 26));
        leNum2HiddenNN_2->setMaximumSize(QSize(50, 26));
        leNum2HiddenNN_2->setFont(font1);
        leNum2HiddenNN_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(leNum2HiddenNN_2);


        verticalLayout_4->addWidget(gBoxNN);

        gbTrainingSet = new QGroupBox(centralwidget);
        gbTrainingSet->setObjectName(QString::fromUtf8("gbTrainingSet"));
        gbTrainingSet->setMinimumSize(QSize(0, 55));
        gbTrainingSet->setMaximumSize(QSize(1000, 80));
        horizontalLayout_5 = new QHBoxLayout(gbTrainingSet);
        horizontalLayout_5->setSpacing(4);
        horizontalLayout_5->setContentsMargins(6, 6, 6, 6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        lblA = new QLabel(gbTrainingSet);
        lblA->setObjectName(QString::fromUtf8("lblA"));
        sizePolicy.setHeightForWidth(lblA->sizePolicy().hasHeightForWidth());
        lblA->setSizePolicy(sizePolicy);
        lblA->setMinimumSize(QSize(50, 26));
        lblA->setMaximumSize(QSize(50, 26));
        lblA->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(lblA);

        leA = new QLineEdit(gbTrainingSet);
        leA->setObjectName(QString::fromUtf8("leA"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(leA->sizePolicy().hasHeightForWidth());
        leA->setSizePolicy(sizePolicy3);
        leA->setMinimumSize(QSize(50, 26));
        leA->setMaximumSize(QSize(50, 26));
        leA->setFont(font1);
        leA->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(leA);

        lblE = new QLabel(gbTrainingSet);
        lblE->setObjectName(QString::fromUtf8("lblE"));
        lblE->setMinimumSize(QSize(50, 26));
        lblE->setMaximumSize(QSize(50, 26));
        lblE->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(lblE);

        leE = new QLineEdit(gbTrainingSet);
        leE->setObjectName(QString::fromUtf8("leE"));
        sizePolicy3.setHeightForWidth(leE->sizePolicy().hasHeightForWidth());
        leE->setSizePolicy(sizePolicy3);
        leE->setMinimumSize(QSize(50, 26));
        leE->setMaximumSize(QSize(50, 26));
        leE->setFont(font1);
        leE->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(leE);

        cbNewTrainingData = new QCheckBox(gbTrainingSet);
        cbNewTrainingData->setObjectName(QString::fromUtf8("cbNewTrainingData"));
        cbNewTrainingData->setMinimumSize(QSize(0, 15));
        cbNewTrainingData->setMaximumSize(QSize(16666, 15));

        horizontalLayout_5->addWidget(cbNewTrainingData);

        lblAcceptError = new QLabel(gbTrainingSet);
        lblAcceptError->setObjectName(QString::fromUtf8("lblAcceptError"));
        sizePolicy.setHeightForWidth(lblAcceptError->sizePolicy().hasHeightForWidth());
        lblAcceptError->setSizePolicy(sizePolicy);
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

        horizontalLayout_5->addWidget(lblAcceptError, 0, Qt::AlignRight);

        leAcceptError = new QLineEdit(gbTrainingSet);
        leAcceptError->setObjectName(QString::fromUtf8("leAcceptError"));
        sizePolicy3.setHeightForWidth(leAcceptError->sizePolicy().hasHeightForWidth());
        leAcceptError->setSizePolicy(sizePolicy3);
        leAcceptError->setMinimumSize(QSize(50, 26));
        leAcceptError->setMaximumSize(QSize(50, 26));
        leAcceptError->setFont(font1);
        leAcceptError->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(leAcceptError);


        verticalLayout_4->addWidget(gbTrainingSet);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(4);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(4);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        lblSnakeSpeed = new QLabel(centralwidget);
        lblSnakeSpeed->setObjectName(QString::fromUtf8("lblSnakeSpeed"));
        sizePolicy.setHeightForWidth(lblSnakeSpeed->sizePolicy().hasHeightForWidth());
        lblSnakeSpeed->setSizePolicy(sizePolicy);
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

        verticalLayout_2->addWidget(lblSnakeSpeed, 0, Qt::AlignHCenter);

        cbSnakeSpeed = new QCheckBox(centralwidget);
        cbSnakeSpeed->setObjectName(QString::fromUtf8("cbSnakeSpeed"));
        cbSnakeSpeed->setEnabled(false);
        sizePolicy.setHeightForWidth(cbSnakeSpeed->sizePolicy().hasHeightForWidth());
        cbSnakeSpeed->setSizePolicy(sizePolicy);
        cbSnakeSpeed->setMaximumSize(QSize(16777215, 26));

        verticalLayout_2->addWidget(cbSnakeSpeed, 0, Qt::AlignHCenter);

        leSnakeSpeed = new QLineEdit(centralwidget);
        leSnakeSpeed->setObjectName(QString::fromUtf8("leSnakeSpeed"));
        sizePolicy.setHeightForWidth(leSnakeSpeed->sizePolicy().hasHeightForWidth());
        leSnakeSpeed->setSizePolicy(sizePolicy);
        leSnakeSpeed->setMinimumSize(QSize(50, 26));
        leSnakeSpeed->setMaximumSize(QSize(50, 26));
        leSnakeSpeed->setFont(font1);
        leSnakeSpeed->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(leSnakeSpeed, 0, Qt::AlignHCenter);

        sldSnakeSpeed = new QSlider(centralwidget);
        sldSnakeSpeed->setObjectName(QString::fromUtf8("sldSnakeSpeed"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(sldSnakeSpeed->sizePolicy().hasHeightForWidth());
        sldSnakeSpeed->setSizePolicy(sizePolicy4);
        sldSnakeSpeed->setMinimumSize(QSize(0, 0));
        sldSnakeSpeed->setMaximumSize(QSize(30, 250));
        sldSnakeSpeed->setMinimum(2);
        sldSnakeSpeed->setMaximum(20);
        sldSnakeSpeed->setPageStep(1);
        sldSnakeSpeed->setValue(10);
        sldSnakeSpeed->setOrientation(Qt::Vertical);

        verticalLayout_2->addWidget(sldSnakeSpeed, 0, Qt::AlignHCenter);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 1);
        verticalLayout_2->setStretch(2, 1);
        verticalLayout_2->setStretch(3, 1);

        horizontalLayout_7->addLayout(verticalLayout_2);

        snake = new Snake(centralwidget);
        snake->setObjectName(QString::fromUtf8("snake"));
        snake->setMinimumSize(QSize(400, 400));
        snake->setMaximumSize(QSize(400, 400));

        horizontalLayout_7->addWidget(snake);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(4);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(4);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lblCountOfSetsTitle = new QLabel(centralwidget);
        lblCountOfSetsTitle->setObjectName(QString::fromUtf8("lblCountOfSetsTitle"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(lblCountOfSetsTitle->sizePolicy().hasHeightForWidth());
        lblCountOfSetsTitle->setSizePolicy(sizePolicy5);
        lblCountOfSetsTitle->setMinimumSize(QSize(0, 0));
        lblCountOfSetsTitle->setMaximumSize(QSize(16777215, 100));
        lblCountOfSetsTitle->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(lblCountOfSetsTitle);

        lblCountOfSets = new QLabel(centralwidget);
        lblCountOfSets->setObjectName(QString::fromUtf8("lblCountOfSets"));
        lblCountOfSets->setMinimumSize(QSize(30, 15));
        lblCountOfSets->setMaximumSize(QSize(30, 20));
        lblCountOfSets->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(lblCountOfSets);


        verticalLayout_7->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(4);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lblCountOfStepsTitle = new QLabel(centralwidget);
        lblCountOfStepsTitle->setObjectName(QString::fromUtf8("lblCountOfStepsTitle"));
        sizePolicy5.setHeightForWidth(lblCountOfStepsTitle->sizePolicy().hasHeightForWidth());
        lblCountOfStepsTitle->setSizePolicy(sizePolicy5);
        lblCountOfStepsTitle->setMinimumSize(QSize(0, 0));
        lblCountOfStepsTitle->setMaximumSize(QSize(16777215, 100));
        lblCountOfStepsTitle->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(lblCountOfStepsTitle);

        lblCountOfSteps = new QLabel(centralwidget);
        lblCountOfSteps->setObjectName(QString::fromUtf8("lblCountOfSteps"));
        lblCountOfSteps->setMinimumSize(QSize(30, 15));
        lblCountOfSteps->setMaximumSize(QSize(30, 20));
        lblCountOfSteps->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(lblCountOfSteps);


        verticalLayout_7->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(4);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        lblCountOfEatenFruitsTitle = new QLabel(centralwidget);
        lblCountOfEatenFruitsTitle->setObjectName(QString::fromUtf8("lblCountOfEatenFruitsTitle"));
        lblCountOfEatenFruitsTitle->setMinimumSize(QSize(0, 0));
        lblCountOfEatenFruitsTitle->setMaximumSize(QSize(16777215, 100));
        lblCountOfEatenFruitsTitle->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(lblCountOfEatenFruitsTitle);

        lblCountOfEatenFruits = new QLabel(centralwidget);
        lblCountOfEatenFruits->setObjectName(QString::fromUtf8("lblCountOfEatenFruits"));
        lblCountOfEatenFruits->setMinimumSize(QSize(30, 15));
        lblCountOfEatenFruits->setMaximumSize(QSize(30, 20));
        lblCountOfEatenFruits->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(lblCountOfEatenFruits);


        verticalLayout_7->addLayout(horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(4);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        lblAverageCountOfSetsTitle = new QLabel(centralwidget);
        lblAverageCountOfSetsTitle->setObjectName(QString::fromUtf8("lblAverageCountOfSetsTitle"));
        lblAverageCountOfSetsTitle->setMinimumSize(QSize(0, 0));
        lblAverageCountOfSetsTitle->setMaximumSize(QSize(16777215, 100));
        lblAverageCountOfSetsTitle->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(lblAverageCountOfSetsTitle);

        lblAverageCountOfSets = new QLabel(centralwidget);
        lblAverageCountOfSets->setObjectName(QString::fromUtf8("lblAverageCountOfSets"));
        lblAverageCountOfSets->setMinimumSize(QSize(30, 15));
        lblAverageCountOfSets->setMaximumSize(QSize(30, 20));
        lblAverageCountOfSets->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(lblAverageCountOfSets);


        verticalLayout_7->addLayout(horizontalLayout_6);


        horizontalLayout_7->addLayout(verticalLayout_7);


        verticalLayout_4->addLayout(horizontalLayout_7);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(4);
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

        verticalLayout_4->addLayout(horizontalLayout_10);

        btnStart = new QPushButton(centralwidget);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));
        QSizePolicy sizePolicy6(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(btnStart->sizePolicy().hasHeightForWidth());
        btnStart->setSizePolicy(sizePolicy6);
        btnStart->setMinimumSize(QSize(0, 0));
        btnStart->setMaximumSize(QSize(150, 30));

        verticalLayout_4->addWidget(btnStart, 0, Qt::AlignHCenter|Qt::AlignTop);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setEnabled(false);
        menubar->setGeometry(QRect(0, 0, 600, 21));
        MainWindow->setMenuBar(menubar);
        QWidget::setTabOrder(leA, leE);
        QWidget::setTabOrder(leE, leAcceptError);
        QWidget::setTabOrder(leAcceptError, teErrors);

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
#if QT_CONFIG(tooltip)
        cbNewWeights->setToolTip(QCoreApplication::translate("MainWindow", "Do need to assign new random weights to synapses", nullptr));
#endif // QT_CONFIG(tooltip)
        cbNewWeights->setText(QCoreApplication::translate("MainWindow", "\320\235\320\276\320\262\321\213\320\265 \320\262\320\265\321\201\320\260 \321\201\320\270\320\275\320\260\320\277\321\201\320\276\320\262", nullptr));
#if QT_CONFIG(tooltip)
        lblAcceptError_2->setToolTip(QCoreApplication::translate("MainWindow", "Acceptable error", nullptr));
#endif // QT_CONFIG(tooltip)
        lblAcceptError_2->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276\n"
"\321\201\320\272\321\200\321\213\321\202\321\213\321\205 \321\201\320\273\320\276\320\265\320\262", nullptr));
#if QT_CONFIG(tooltip)
        leNum2HiddenNN_2->setToolTip(QCoreApplication::translate("MainWindow", "The number of neurons in the third and subsequent hidden layers is equal to the number of neurons in the second hidden layer", nullptr));
#endif // QT_CONFIG(tooltip)
        leNum2HiddenNN_2->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
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
        cbNewTrainingData->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Do need to assign new training data for neural network training (the existing training set is deleted)</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        cbNewTrainingData->setText(QCoreApplication::translate("MainWindow", "\320\235\320\276\320\262\320\260\321\217 \320\276\320\261\321\203\321\207\320\260\321\216\321\211\320\260\321\217 \320\262\321\213\320\261\320\276\321\200\320\272\320\260", nullptr));
#if QT_CONFIG(tooltip)
        lblAcceptError->setToolTip(QCoreApplication::translate("MainWindow", "Acceptable error", nullptr));
#endif // QT_CONFIG(tooltip)
        lblAcceptError->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\277\321\203\321\201\321\202\320\270\320\274\320\260\321\217\n"
"\320\276\321\210\320\270\320\261\320\272\320\260", nullptr));
        leAcceptError->setText(QCoreApplication::translate("MainWindow", "0.02", nullptr));
#if QT_CONFIG(tooltip)
        lblSnakeSpeed->setToolTip(QCoreApplication::translate("MainWindow", "Snake speed in steps per second", nullptr));
#endif // QT_CONFIG(tooltip)
        lblSnakeSpeed->setText(QCoreApplication::translate("MainWindow", "\320\241\320\272\320\276\321\200\320\276\321\201\321\202\321\214\n"
"\320\267\320\274\320\265\320\271\320\272\320\270", nullptr));
        cbSnakeSpeed->setText(QCoreApplication::translate("MainWindow", "\320\234\320\260\320\272\321\201.\n"
"\321\201\320\272\320\276\321\200\320\276\321\201\321\202\321\214", nullptr));
#if QT_CONFIG(tooltip)
        leSnakeSpeed->setToolTip(QCoreApplication::translate("MainWindow", "Snake speed in steps per second", nullptr));
#endif // QT_CONFIG(tooltip)
        leSnakeSpeed->setText(QCoreApplication::translate("MainWindow", "10", nullptr));
#if QT_CONFIG(tooltip)
        lblCountOfSetsTitle->setToolTip(QCoreApplication::translate("MainWindow", "Count of runs contained in the training set", nullptr));
#endif // QT_CONFIG(tooltip)
        lblCountOfSetsTitle->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276\n"
"\320\277\321\203\321\201\320\272\320\276\320\262\n"
"\320\262 \320\276\320\261\321\203\321\207\320\260\321\216\321\211\320\265\320\271\n"
"\320\262\321\213\320\261\320\276\321\200\320\272\320\265", nullptr));
#if QT_CONFIG(tooltip)
        lblCountOfSets->setToolTip(QCoreApplication::translate("MainWindow", "Count of runs contained in the training set", nullptr));
#endif // QT_CONFIG(tooltip)
        lblCountOfSets->setText(QString());
#if QT_CONFIG(tooltip)
        lblCountOfStepsTitle->setToolTip(QCoreApplication::translate("MainWindow", "Number of steps completed by snakes in the current run", nullptr));
#endif // QT_CONFIG(tooltip)
        lblCountOfStepsTitle->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276\n"
"\321\210\320\260\320\263\320\276\320\262\n"
"\320\262 \321\202\320\265\320\272\321\203\321\211\320\265\320\274\n"
"\320\267\320\260\320\277\321\203\321\201\320\272\320\265", nullptr));
#if QT_CONFIG(tooltip)
        lblCountOfSteps->setToolTip(QCoreApplication::translate("MainWindow", "Number of steps completed by snakes in the current run", nullptr));
#endif // QT_CONFIG(tooltip)
        lblCountOfSteps->setText(QString());
#if QT_CONFIG(tooltip)
        lblCountOfEatenFruitsTitle->setToolTip(QCoreApplication::translate("MainWindow", "The number of fruits eaten in the current run", nullptr));
#endif // QT_CONFIG(tooltip)
        lblCountOfEatenFruitsTitle->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276\n"
"\321\201\321\212\320\265\320\264\320\265\320\275\320\275\321\213\321\205\n"
"\321\204\321\200\321\203\320\272\321\202\320\276\320\262\n"
"\320\262 \321\202\320\265\320\272\321\203\321\211\320\265\320\274\n"
"\320\267\320\260\320\277\321\203\321\201\320\272\320\265", nullptr));
#if QT_CONFIG(tooltip)
        lblCountOfEatenFruits->setToolTip(QCoreApplication::translate("MainWindow", "The number of fruits eaten in the current run", nullptr));
#endif // QT_CONFIG(tooltip)
        lblCountOfEatenFruits->setText(QString());
#if QT_CONFIG(tooltip)
        lblAverageCountOfSetsTitle->setToolTip(QCoreApplication::translate("MainWindow", "The average number of steps of the snake, starting with waking up", nullptr));
#endif // QT_CONFIG(tooltip)
        lblAverageCountOfSetsTitle->setText(QCoreApplication::translate("MainWindow", "\320\241\321\200\320\265\320\264\320\275\320\265\320\265\n"
"\320\272\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276\n"
"\321\210\320\260\320\263\320\276\320\262 \320\277\320\276\321\201\320\273\320\265\n"
"\320\277\321\200\320\276\320\261\321\203\320\266\320\264\320\265\320\275\320\270\321\217", nullptr));
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
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
