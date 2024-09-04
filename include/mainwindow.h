//
// Created by jeong on 2024/7/1.
//

#ifndef RANDOMGENERATOR_MAINWINDOW_H
#define RANDOMGENERATOR_MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <variant>
#include <QRandomGenerator64>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private slots:

    void onGenerateClicked();

private:

    Ui::MainWindow *ui;

    static std::variant<QVector<qint64>, qint64>
    generateRandomNumbers(bool iSequence, bool allowDuplicates, qint64 minVal, qint64 maxVal, qint64 length);

    static void displayRandomNumbers(const std::variant<QVector<qint64>, qint64> &result, Ui::MainWindow *ui);

    bool initializeClassDirectory();
};


#endif
