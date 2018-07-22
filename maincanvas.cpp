#include "maincanvas.h"
#include "ui_maincanvas.h"

#include <QPainter>

MainCanvas::MainCanvas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainCanvas)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StaticContents);
    this->mainCanvasImage = new QImage(QSize(1200, 900), QImage::Format_RGB32);
    mainCanvasImage->fill(QColor(255,255,255, 255));
    modified = false;
    scribbling = false;
}

MainCanvas::~MainCanvas()
{
    delete ui;
}
void MainCanvas::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, *mainCanvasImage, dirtyRect);
    int nextWidth = 0;
    if (words.size() > 0){
        for (auto word : words) {
            int maxWidthWithColoredPixels = getFarestPixel(*word);
            QRect croppFrame(0,0,maxWidthWithColoredPixels + 2, word->height());
            QImage croppedImage = word->copy(croppFrame);
            //QImage image = croppedImage.scaledToHeight(80,Qt::FastTransformation);
            //painter.drawImage(QRect(nextWidth,0,image.width(),image.height()),image);
            painter.drawImage(QRect(nextWidth,0,croppedImage.width(),croppedImage.height()),croppedImage);
            nextWidth += croppedImage.width();
        }
    }
}

void MainCanvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        scribbling = true;
    }
}

void MainCanvas::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling) {
        drawLineTo(event->pos());
    }
}

void MainCanvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling)  {
        drawLineTo(event->pos());
        scribbling = false;
    }
}
void MainCanvas::drawLineTo(const QPoint &endPoint)
{
   QPainter painter(mainCanvasImage);
   painter.drawLine(lastPoint, endPoint);
   modified = true;

   int rad = 5;
   update(QRect(lastPoint, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
   lastPoint = endPoint;
}

void MainCanvas::addWord(QImage *word)
{
    //QPixmap wordImage = QPixmap::fromImage(*word);
    //painter.drawPixmap(previousLineWidth,0,word->width(), word->height(), wordImage);
    words.push_back(word);
    update();
}

int MainCanvas::getFarestPixel(QImage image) {
    int imageWight = image.width();
    int imageHeight = image.height();
    int farestPixel = 0;
    for (int heigh = 1; heigh < imageHeight; heigh++ ) {
        for (int width = 1; width < imageWight; width++ ) {
            if (image.pixelColor(width, heigh) == QColor(0,0,0) && width > farestPixel) {
               farestPixel = width;
            }
        }
    }
    return farestPixel;
}
