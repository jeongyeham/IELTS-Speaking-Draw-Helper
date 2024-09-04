#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow {
public:
    QAction *actionPreferances;
    QAction *actionExit;
    QWidget *centralwidget;
    QPushButton *pushButton;
    QPlainTextEdit *minEdit;
    QPlainTextEdit *maxEdit;
    QPlainTextEdit *lengthEdit;
    QTextEdit *resultTextEdit;
    QComboBox *comboBox;
    QCheckBox *duplicateCheckBox;
    QMenuBar *menubar;
    QMenu *menuMode;
    QMenu *menuAbout;

    void setupUi(QMainWindow *MainWindow) {

        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(400, 296);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Random.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QString::fromUtf8(""));


        actionPreferances = new QAction(MainWindow);
        actionPreferances->setObjectName("actionPreferances");
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");


        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(200, 150, 171, 61));
        pushButton->setAutoFillBackground(false);
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
                                                    "    border: 1px solid #3498db; \n"
                                                    "    border-radius: 15px; \n"
                                                    "    background-color: #ecf0f1; \n"
                                                    "    color: #2c3e50; \n"
                                                    "    padding: 10px;\n"
                                                    "    font-weight: bold; \n"
                                                    "}\n"
                                                    "\n"
                                                    "QPushButton:hover {\n"
                                                    "    background-color: #3498db; \n"
                                                    "    color: #ecf0f1;\n"
                                                    "}\n"
                                                    "QPushButton:pressed {\n"
                                                    "    background-color: #439843; \n"
                                                    "    color: #2c3e50; \n"
                                                    "}\n"
                                                    ""));

        minEdit = new QPlainTextEdit(centralwidget);
        minEdit->setObjectName("minEdit");
        minEdit->setGeometry(QRect(60, 10, 91, 31));
        maxEdit = new QPlainTextEdit(centralwidget);
        maxEdit->setObjectName("maxEdit");
        maxEdit->setGeometry(QRect(60, 50, 91, 31));
        lengthEdit = new QPlainTextEdit(centralwidget);
        lengthEdit->setObjectName("lengthEdit");
        lengthEdit->setGeometry(QRect(60, 90, 91, 31));
        resultTextEdit = new QTextEdit(centralwidget);
        resultTextEdit->setObjectName("resultTextEdit");
        resultTextEdit->setGeometry(QRect(200, 20, 181, 101));
        resultTextEdit->setReadOnly(1);

        duplicateCheckBox = new QCheckBox(centralwidget);
        duplicateCheckBox->setObjectName("duplicateCheckBox");
        duplicateCheckBox->setGeometry(QRect(60, 170, 91, 31));
        duplicateCheckBox->setChecked(false);

        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(40, 140, 121, 22));
        MainWindow->setCentralWidget(centralwidget);


        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 400, 33));
        menuMode = new QMenu(menubar);
        menuMode->setObjectName("menuMode");
        menuAbout = new QMenu(menubar);
        menuAbout->setObjectName("menuAbout");
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuMode->menuAction());
        menubar->addAction(menuAbout->menuAction());
        menuMode->addAction(actionPreferances);
        menuMode->addAction(actionExit);

        setUiText(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void setUiText(QMainWindow *MainWindow) const {
        MainWindow->setWindowTitle("RandomGenerator");
        actionPreferances->setText("Preferences");
        actionExit->setText("Exit");

        pushButton->setText("Boom!");
        minEdit->setPlaceholderText("Min num");
        maxEdit->setPlaceholderText("Max num");
        lengthEdit->setPlaceholderText("Num");
        resultTextEdit->setPlaceholderText("Result is HERE!!!!");
        duplicateCheckBox->setText("Duplicate");

        comboBox->setPlaceholderText("Select class");
        menuMode->setTitle("Menu");
        menuAbout->setTitle("About");
    }
};

namespace Ui {
    class MainWindow : public Ui_MainWindow {
    };
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
