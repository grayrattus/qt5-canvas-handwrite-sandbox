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
    mainCanvasImage->fill(QColor(255,255,255));
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
    if (words.size() > 0){
        for (auto word : words) {
            int maxWidthWithColoredPixels = getFarestPixel(*word);
            //int minWidthWithColoredPixels = getFirstPixel(*word);
            uint pixelOffset = 2;
            QRect croppFrame(0 + pixelOffset ,0,maxWidthWithColoredPixels + pixelOffset, word->height());
            QImage croppedImage = word->copy(croppFrame);
            croppedWords.push_back(croppedImage);
        }
    }
    words.clear();

    int currentWordsWidthLevel = 0;
    int currentWordsHeightLevel = 0;
    for (auto croppedWord : croppedWords) {
        if (currentWordsWidthLevel >= this->width()) {
           currentWordsHeightLevel+= croppedWord.height();
           currentWordsWidthLevel = 0;
        }
        painter.drawImage(QRect(currentWordsWidthLevel,currentWordsHeightLevel,croppedWord.width(),croppedWord.height()),croppedWord);
        currentWordsWidthLevel += croppedWord.width();
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
    words.push_back(word);
    update();
}

int MainCanvas::getFarestPixel(QImage image) {
    int imageWight = image.width();
    int imageHeight = image.height();
    int farestPixel = 0;
    for (int heigh = 1; heigh < imageHeight; heigh++ ) {
        for (int width = 1; width < imageWight; width++ ) {
            if (image.pixelColor(width, heigh) != QColor(255,255,255,100) && width > farestPixel) {
               farestPixel = width;
            }
        }
    }
    return farestPixel;
}

int MainCanvas::getFirstPixel(QImage image) {
    int imageWight = image.width();
    int imageHeight = image.height();
    int firstPixel = 0;
    for (int heigh = 1; heigh < imageHeight; heigh++ ) {
        for (int width = 1; width < imageWight; width++ ) {
            if (image.pixelColor(width, heigh) != QColor(255,255,255) && width < firstPixel) {
               firstPixel = width;
            }
        }
    }
    return firstPixel;
}
