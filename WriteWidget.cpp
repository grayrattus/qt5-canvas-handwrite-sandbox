#include "WriteWidget.h"
#include "ui_WriteWidget.h"


WriteWidget::WriteWidget(QWidget *parent, QWidget *sibling) :
    QWidget(parent),
    ui(new Ui::WriteWidget)
{
    setAttribute(Qt::WA_StaticContents);
    ui->setupUi(this);
    modified = false;
    scribbling = false;
    clearImage();
    timeToDraw = new QTimer(this);

    connect(this, SIGNAL(finishWord(QImage*)), sibling, SLOT(addWord(QImage*)));
}

WriteWidget::~WriteWidget()
{
    delete ui;
}

void WriteWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        scribbling = true;
        timeToDraw->stop();
    }
}

void WriteWidget::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling) {
        drawLineTo(event->pos());
    }
}

void WriteWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling)  {
        drawLineTo(event->pos());
        scribbling = false;
        connect(timeToDraw, SIGNAL(timeout()), this, SLOT(finishWriting()));
        timeToDraw->setInterval(milisecondsToDrawAfterBrake);
        timeToDraw->start();
    }
}



void WriteWidget::paintEvent(QPaintEvent *event)
{
   QPainter painter(this);
   QRect dirtyRect = event->rect();
   painter.drawImage(dirtyRect, *image, dirtyRect);
}

void WriteWidget::finishWriting()
{
        finishWord(image);
        clearImage();
}

void WriteWidget::drawLineTo(const QPoint &endPoint)
{
   QPainter painter(image);
   painter.drawLine(lastPoint, endPoint);
   modified = true;

   int rad = 5;
   update(QRect(lastPoint, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
   lastPoint = endPoint;
}

QImage *WriteWidget::clearImage()
{
    image = new QImage(QSize(this->size().width(), 100), QImage::Format_RGB32);
    image->fill(QColor(255,255,255,0));
    update();
}
