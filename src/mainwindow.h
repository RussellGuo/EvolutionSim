#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class TEcosystem;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_speedSlider_valueChanged(int value);

    void on_pushButton_clicked();

    void on_ExitPushButton_clicked();

private:
    Ui::MainWindow *ui;
    QTimer timer;
    class TEcosystem *ecosystem;
};

#endif // MAINWINDOW_H
