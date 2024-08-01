//
// Created by jeong on 2024/7/1.
//


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileInfo>


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(this->ui->pushButton, &QPushButton::clicked, this, &MainWindow::onGenerateClicked);
    connect(this->ui->actionExit, &QAction::triggered, this, &MainWindow::close);

    QDir exeDir = QCoreApplication::applicationDirPath();

    QDir classDir(exeDir.filePath("class"));

    if (!classDir.exists()) {
        ui->comboBox->setPlaceholderText("No class folder");
        ui->resultTextEdit->setPlaceholderText(
                "Please new class folder\nThis is only a recommendation\nYou can still use generator");
        return;
    }

    QStringList filters;
    filters << "*.txt";
    QStringList txtFiles = classDir.entryList(filters);

    if (txtFiles.isEmpty()) {
        ui->comboBox->setPlaceholderText("No class file(s)");
        ui->resultTextEdit->setPlaceholderText(
                "Please new class file(s)\nThis is only a recommendation\nYou can still use generator");
        return;
    }

    Q_FOREACH(const QString &fileName, txtFiles) {
            QString baseName = QFileInfo(fileName).baseName();
            ui->comboBox->addItem(baseName);
        }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onGenerateClicked() {
    ui->resultTextEdit->clear();

    int minVal = ui->minEdit->toPlainText().toInt();
    int maxVal = ui->maxEdit->toPlainText().toInt();
    int length = ui->lengthEdit->toPlainText().toInt();

    bool isSequence = true;
    auto result = generateRandomNumbers(isSequence, minVal, maxVal, length);
    displayRandomNumbers(result, this->ui);

}

std::variant<QVector<int>, int>
MainWindow::generateRandomNumbers(bool isSequence, int minVal = 0, int maxVal = 100, int length = 0) {
    QRandomGenerator generator;

    if (isSequence) {
        // 如果 isSequence 为 true，生成一个数列
        QVector<int> sequence;
        if (length > 0) {
            sequence.reserve(length); // 预分配空间以提高性能
            for (int i = 0; i < length; ++i) {
                int randomNumber = minVal + generator.bounded(minVal, maxVal + 1) - minVal;
                sequence.append(randomNumber);
            }
        }
        return sequence;
    } else {
        // 如果 isSequence 为 false，只生成一个随机数
        int randomNumber = minVal + generator.bounded(minVal, maxVal + 1) - minVal;
        return randomNumber;
    }
}

void MainWindow::displayRandomNumbers(const std::variant<QVector<int>, int> &result, Ui::MainWindow *ui) {
    QString displayText;

    if (std::holds_alternative<QVector<int>>(result)) {
        // 如果结果是 QVector<int>
        QVector<int> sequence = std::get<QVector<int>>(result);
        for (int i = 0; i < sequence.size(); ++i) {
            displayText += QString::number(sequence[i]);
            if (i < sequence.size() - 1) {
                displayText += ", ";  // 在数列元素之间添加逗号和空格
            }
        }
    } else {
        // 如果结果是 int
        int randomNumber = std::get<int>(result);
        displayText = QString::number(randomNumber);
    }

    // 将最终的字符串添加到 QTextEdit 中
    ui->resultTextEdit->append(displayText);
}





