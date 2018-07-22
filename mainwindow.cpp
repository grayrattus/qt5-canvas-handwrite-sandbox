#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <WriteWidget.h>
#include <maincanvas.h>
#include <QDebug>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mainCanvas = new MainCanvas(this);
    writeWidget = new WriteWidget(this, mainCanvas);
    ui->imagesLayout->addWidget(writeWidget);
    ui->wordsLayout->addWidget(mainCanvas);
    writeWidget->show();
    mainCanvas->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
