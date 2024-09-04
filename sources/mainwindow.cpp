#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include <unordered_set>

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QMetaObject::Connection pushButtonConnection = connect(this->ui->pushButton, &QPushButton::clicked, this,
                                                           &MainWindow::onGenerateClicked);
    if (!pushButtonConnection) {
        qDebug() << "Failed to connect to the clicked signal of the push button.";
    } else {
        qDebug() << "Connected to the clicked signal of the push button.";
    }

    QMetaObject::Connection actionExitConnection = connect(this->ui->actionExit, &QAction::triggered, this,
                                                           &MainWindow::close);
    if (!actionExitConnection) {
        qDebug() << "Failed to connect to the triggered signal of the action exit.";
    } else {
        qDebug() << "Connected to the triggered signal of the action exit.";
    }

    if (!initializeClassDirectory()) { // 文件夹初始化检查
        QMessageBox::information(this, "Information", "Please set up your class directory correctly.");
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

bool MainWindow::initializeClassDirectory() {
    QDir exeDir = QCoreApplication::applicationDirPath();
    QDir classDir(exeDir.filePath("class"));

    if (!classDir.exists()) {
        ui->comboBox->setPlaceholderText("No class folder");
        ui->resultTextEdit->setPlaceholderText(
                "Please new class folder\nThis is only a recommendation\nYou can still use generator");
        return false;
    }

    QStringList filters;
    filters << "*.txt";
    QStringList txtFiles = classDir.entryList(filters);

    if (txtFiles.isEmpty()) {
        ui->comboBox->setPlaceholderText("No class file(s)");
        ui->resultTextEdit->setPlaceholderText(
                "Please new class file(s)\nThis is only a recommendation\nYou can still use generator");
        return false;
    }

    Q_FOREACH(const QString &fileName, txtFiles) {
            QString baseName = QFileInfo(fileName).baseName();
            ui->comboBox->addItem(baseName);
        }
    return true;
}

void MainWindow::onGenerateClicked() {
    ui->resultTextEdit->clear();

    bool ok;
    qint64 minVal = ui->minEdit->toPlainText().toInt(&ok);
    if (!ok || minVal > 1000) { // 假设输入上限为1000，具体值根据实际情况调整
        QMessageBox::warning(this, "Warning", "Please enter a valid minimum value.");
        return;
    }

    qint64 maxVal = ui->maxEdit->toPlainText().toInt(&ok);
    if (!ok || maxVal < 0 || maxVal < minVal) {
        QMessageBox::warning(this, "Warning", "Please enter a valid maximum value greater than the minimum value.");
        return;
    }

    qint64 length = ui->lengthEdit->toPlainText().toInt(&ok);
    if (!ok || length <= 0) {
        QMessageBox::warning(this, "Warning", "Please enter a valid positive length.");
        return;
    }

    bool isSequence = (length > 1);
    bool allowDuplicates = ui->duplicateCheckBox->isChecked();

    auto result = generateRandomNumbers(isSequence, allowDuplicates, minVal, maxVal, length);
    displayRandomNumbers(result, this->ui);
}


std::variant<QVector<qint64>, qint64>
MainWindow::generateRandomNumbers(bool isSequence, bool allowDuplicates, qint64 minVal, qint64 maxVal, qint64 length) {
    QRandomGenerator64 *generator = QRandomGenerator64::global();

    if (isSequence) {
        QVector<qint64> sequence;
        try {
            if (allowDuplicates) {
                sequence.reserve(length);
                for (qint64 i = 0; i < length; ++i) {
                    sequence.push_back(generator->bounded(minVal, maxVal + 1));
                }
            }
        } catch (const std::exception &e) {
            // 理论上，这里的异常应该很少见，但为了代码健壮性，最好进行处理
            qDebug() << "Exception in generating random sequence numbers:" << e.what();
            return QVector<qint64>(); // 返回空的sequence
        }
        return sequence;
    } else {
        qint64 randomNumber = 0;
        try {
            randomNumber = generator->bounded(minVal, maxVal + 1);
        } catch (const std::exception &e) {
            qDebug() << "Exception in generating random number:" << e.what();
            return randomNumber; // 返回空的sequence
        }
        return randomNumber;
    }
}


void MainWindow::displayRandomNumbers(const std::variant<QVector<qint64>, qint64> &result, Ui::MainWindow *ui) {
    QString displayText;

    if (std::holds_alternative<QVector<qint64>>(result)) {
        QVector<qint64> sequence = std::get<QVector<qint64>>(result);
        for (qint64 i = 0; i < sequence.size(); ++i) {
            displayText += QString::number(sequence[i]);
            if (i < sequence.size() - 1) {
                displayText += ", ";
            }
        }
    } else {
        qint64 randomNumber = std::get<qint64>(result);
        displayText = QString::number(randomNumber);
    }

    ui->resultTextEdit->append(displayText);
}
