#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "ecosystem.h"
#include "EcosystemWidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    ecosystem(new TEcosystem)
{
    ui->setupUi(this);

    new TEcosystemWidget(ecosystem, ui->displayFrame);
    connect (&timer, SIGNAL(timeout()), ecosystem, SLOT(tick()));
    connect(ui->InitBugNumberSpinBox      , SIGNAL(valueChanged(int)), ecosystem, SLOT(setInitBugNumber(int))      );
    connect(ui->InitBacteriumNumberSpinBox, SIGNAL(valueChanged(int)), ecosystem, SLOT(setInitBacteriumNumber(int)));
    connect(ui->EdenRadiusSpinBox         , SIGNAL(valueChanged(int)), ecosystem, SLOT(setEdenRadius(int))         );

    connect(ui->IncreaseBacteriumEachForPoolDoubleSpinBox, SIGNAL(valueChanged(double)), ecosystem, SLOT(setIncreaseBacteriumEachForPool(double)));
    connect(ui->IncreaseBacteriumEachForEdenDoubleSpinBox, SIGNAL(valueChanged(double)), ecosystem, SLOT(setIncreaseBacteriumEachForEden(double)));

    ui->InitBugNumberSpinBox->setValue(10);
    ui->InitBacteriumNumberSpinBox->setValue(2000);
    ui->EdenRadiusSpinBox->setValue(70);
    ui->IncreaseBacteriumEachForPoolDoubleSpinBox->setValue(0.8);
    ui->IncreaseBacteriumEachForEdenDoubleSpinBox->setValue(0.1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_speedSlider_valueChanged(int value)
{
    int msec = 0;
    switch (value) {
    case 0:
        timer.stop();
        return;
    case 1:
        msec = 200;
        break;
    case 2:
        msec = 30;
        break;
    case 3:
        msec = 5;
        break;
    case 4:
        msec = 0;
        break;
    default:
        break;
    }
    timer.start(msec);
}

void MainWindow::on_pushButton_clicked()
{
    ui->MainStackedWidget->setCurrentIndex(1);
    ui->speedSlider->setValue(2);
}

void MainWindow::on_ExitPushButton_clicked()
{
    close();
}
