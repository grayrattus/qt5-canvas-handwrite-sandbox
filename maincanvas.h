#ifndef MAINCANVAS_H
#define MAINCANVAS_H

#include <QWidget>
#include <QPaintEvent>
#include <QImage>
#include <QMouseEvent>
#include <QPaintEvent>

#include <vector>

namespace Ui {
class MainCanvas;
}

class MainCanvas : public QWidget
{
    Q_OBJECT

public:
    explicit MainCanvas(QWidget *parent = 0);
    ~MainCanvas();
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    int getFirstPixel(QImage image);
public slots:
    void addWord(QImage*);

private:
    void drawLineTo(const QPoint &endPoint);
    int getFarestPixel(QImage image);
    Ui::MainCanvas *ui;
    QImage* mainCanvasImage;
    std::vector<QImage*> words;
    std::vector<QImage> croppedWords;
    bool modified;
    bool scribbling;
    QImage* image;
    QPoint lastPoint;
};

#endif // MAINCANVAS_H
