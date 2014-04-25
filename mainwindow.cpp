#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->frame_Mid->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    CreateControls();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::CreateControls()
{
    for (int i = 0; i < 12; i ++)
    {
        Country * c = new Country();
        ui->layoutTop->addWidget(c);
    }
    for (int i = 0; i < 5; i ++)
    {
        Country * c = new Country();
        ui->layoutRight->addWidget(c);
    }
    for (int i = 0; i < 12; i ++)
    {
        Country * c = new Country();
        ui->layoutBot->addWidget(c);
    }
    for (int i = 0; i < 5; i ++)
    {
        Country * c = new Country();
        ui->layoutLeft->addWidget(c);
    }
}
