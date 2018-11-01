/********************************************************************************
** Form generated from reading UI file 'qtguiapplication3.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTGUIAPPLICATION3_H
#define UI_QTGUIAPPLICATION3_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtGuiApplication3Class
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *mainLayout;
    QHBoxLayout *horizontalLayout_2;
    QTreeWidget *treeWidget;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *mylayout;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtGuiApplication3Class)
    {
        if (QtGuiApplication3Class->objectName().isEmpty())
            QtGuiApplication3Class->setObjectName(QStringLiteral("QtGuiApplication3Class"));
        QtGuiApplication3Class->resize(744, 583);
        centralWidget = new QWidget(QtGuiApplication3Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(50, 20, 631, 491));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        mainLayout = new QGridLayout();
        mainLayout->setSpacing(6);
        mainLayout->setObjectName(QStringLiteral("mainLayout"));

        verticalLayout->addLayout(mainLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        treeWidget = new QTreeWidget(layoutWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setMinimumSize(QSize(200, 100));

        horizontalLayout_2->addWidget(treeWidget);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        mylayout = new QVBoxLayout();
        mylayout->setSpacing(0);
        mylayout->setObjectName(QStringLiteral("mylayout"));
        mylayout->setSizeConstraint(QLayout::SetMinimumSize);
        mylayout->setContentsMargins(0, 0, 0, -1);

        horizontalLayout_2->addLayout(mylayout);


        verticalLayout->addLayout(horizontalLayout_2);

        QtGuiApplication3Class->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QtGuiApplication3Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 744, 23));
        QtGuiApplication3Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtGuiApplication3Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QtGuiApplication3Class->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtGuiApplication3Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtGuiApplication3Class->setStatusBar(statusBar);

        retranslateUi(QtGuiApplication3Class);

        QMetaObject::connectSlotsByName(QtGuiApplication3Class);
    } // setupUi

    void retranslateUi(QMainWindow *QtGuiApplication3Class)
    {
        QtGuiApplication3Class->setWindowTitle(QApplication::translate("QtGuiApplication3Class", "QtGuiApplication3", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtGuiApplication3Class: public Ui_QtGuiApplication3Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGUIAPPLICATION3_H
