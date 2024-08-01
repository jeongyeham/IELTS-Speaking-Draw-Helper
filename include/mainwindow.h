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

    static std::variant<QVector<int>, int> generateRandomNumbers(bool iSequence, int minVal, int maxVal, int length);

    static void displayRandomNumbers(const std::variant<QVector<int>, int> &result, Ui::MainWindow *ui);
};


#endif
