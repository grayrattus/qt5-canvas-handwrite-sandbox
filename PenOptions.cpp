#include "PenOptions.h"
#include "ui_PenOptions.h"

#include <QDebug>

PenOptions::PenOptions(QWidget *parent, const WriteWidget *writeWidgetInstance):
    QDialog(parent),
    ui(new Ui::PenOptions)
{
    ui->setupUi(this);
    connect(this->ui->penSizeSlider, SIGNAL(sliderMoved(int)), writeWidgetInstance, SLOT(resizePen(const int)));
    connect(this->ui->changeColorButton, SIGNAL(clicked(bool)), writeWidgetInstance, SLOT(changePenColor(bool)));
    connect(writeWidgetInstance, &WriteWidget::emitColorChange, this, &PenOptions::changeChangeColorButtonColor);
}


PenOptions::~PenOptions()
{
    delete ui;
}

void PenOptions::changeChangeColorButtonColor(const QColor &color)
{
    QPalette pal = this->ui->changeColorButton->palette();
    pal.setColor(QPalette::Button, color);
    this->ui->changeColorButton->setAutoFillBackground(true);
    this->ui->changeColorButton->setPalette(pal);
    this->ui->changeColorButton->update();

}
