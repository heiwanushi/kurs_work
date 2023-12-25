/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSave;
    QAction *actionLoad;
    QWidget *centralwidget;
    QFormLayout *formLayout_2;
    QGraphicsView *graphView;
    QFrame *line;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QSpinBox *sizeSpinBox;
    QLabel *label_2;
    QDoubleSpinBox *densitySpinBox;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *generateButton;
    QPushButton *generateEulerButton;
    QPushButton *manualInputButton;
    QSpacerItem *horizontalSpacer;
    QTextEdit *matrixTextEdit;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *findEulerianButton;
    QSpacerItem *horizontalSpacer_4;
    QTextEdit *eulerianPathTextEdit;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(658, 490);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName("actionSave");
        actionLoad = new QAction(MainWindow);
        actionLoad->setObjectName("actionLoad");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        formLayout_2 = new QFormLayout(centralwidget);
        formLayout_2->setObjectName("formLayout_2");
        graphView = new QGraphicsView(centralwidget);
        graphView->setObjectName("graphView");
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(graphView->sizePolicy().hasHeightForWidth());
        graphView->setSizePolicy(sizePolicy1);
        graphView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, graphView);

        line = new QFrame(centralwidget);
        line->setObjectName("line");
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, line);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        formLayout->setLabelAlignment(Qt::AlignCenter);
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        formLayout->setWidget(1, QFormLayout::LabelRole, label);

        sizeSpinBox = new QSpinBox(centralwidget);
        sizeSpinBox->setObjectName("sizeSpinBox");
        sizeSpinBox->setMaximum(20);

        formLayout->setWidget(1, QFormLayout::FieldRole, sizeSpinBox);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        formLayout->setWidget(3, QFormLayout::LabelRole, label_2);

        densitySpinBox = new QDoubleSpinBox(centralwidget);
        densitySpinBox->setObjectName("densitySpinBox");
        densitySpinBox->setMaximum(1.000000000000000);
        densitySpinBox->setSingleStep(0.100000000000000);

        formLayout->setWidget(3, QFormLayout::FieldRole, densitySpinBox);


        verticalLayout->addLayout(formLayout);

        horizontalSpacer_2 = new QSpacerItem(40, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer_2);

        generateButton = new QPushButton(centralwidget);
        generateButton->setObjectName("generateButton");
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(generateButton->sizePolicy().hasHeightForWidth());
        generateButton->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(generateButton);

        generateEulerButton = new QPushButton(centralwidget);
        generateEulerButton->setObjectName("generateEulerButton");
        sizePolicy2.setHeightForWidth(generateEulerButton->sizePolicy().hasHeightForWidth());
        generateEulerButton->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(generateEulerButton);

        manualInputButton = new QPushButton(centralwidget);
        manualInputButton->setObjectName("manualInputButton");

        verticalLayout->addWidget(manualInputButton);

        horizontalSpacer = new QSpacerItem(40, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer);

        matrixTextEdit = new QTextEdit(centralwidget);
        matrixTextEdit->setObjectName("matrixTextEdit");
        sizePolicy1.setHeightForWidth(matrixTextEdit->sizePolicy().hasHeightForWidth());
        matrixTextEdit->setSizePolicy(sizePolicy1);
        matrixTextEdit->setMaximumSize(QSize(16777215, 16777215));
        matrixTextEdit->setReadOnly(true);

        verticalLayout->addWidget(matrixTextEdit);

        horizontalSpacer_3 = new QSpacerItem(40, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer_3);

        findEulerianButton = new QPushButton(centralwidget);
        findEulerianButton->setObjectName("findEulerianButton");
        sizePolicy2.setHeightForWidth(findEulerianButton->sizePolicy().hasHeightForWidth());
        findEulerianButton->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(findEulerianButton);

        horizontalSpacer_4 = new QSpacerItem(40, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer_4);

        eulerianPathTextEdit = new QTextEdit(centralwidget);
        eulerianPathTextEdit->setObjectName("eulerianPathTextEdit");
        sizePolicy1.setHeightForWidth(eulerianPathTextEdit->sizePolicy().hasHeightForWidth());
        eulerianPathTextEdit->setSizePolicy(sizePolicy1);
        eulerianPathTextEdit->setReadOnly(true);

        verticalLayout->addWidget(eulerianPathTextEdit);


        formLayout_2->setLayout(2, QFormLayout::LabelRole, verticalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 658, 21));
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Ignored);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(statusbar->sizePolicy().hasHeightForWidth());
        statusbar->setSizePolicy(sizePolicy3);
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menu->addAction(actionSave);
        menu->addAction(actionLoad);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Graph Matrix Generator", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        actionLoad->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Size:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Density:", nullptr));
        generateButton->setText(QCoreApplication::translate("MainWindow", "Generate Matrix", nullptr));
        generateEulerButton->setText(QCoreApplication::translate("MainWindow", "Generate Eulerian Matrix", nullptr));
        manualInputButton->setText(QCoreApplication::translate("MainWindow", "Input matrix", nullptr));
        findEulerianButton->setText(QCoreApplication::translate("MainWindow", "Find Eulerian Path", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
