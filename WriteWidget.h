#ifndef WRITEWIDGET_H
#define WRITEWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QPainter>
#include <QImage>
#include <QTimer>

namespace Ui {
class WriteWidget;
}

class WriteWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WriteWidget(QWidget *parent = 0, QWidget *sibling= 0);
    ~WriteWidget();

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
signals:
    void finishWord(QImage*);
    void emitColorChange(const QColor&);
public slots:
    void finishWriting();
    void resizePen(const int newPenSize);
    void changePenColor(bool clicked);
private:
    Ui::WriteWidget *ui;
    void drawLineTo(const QPoint &endPoint);
    bool modified;
    bool scribbling;
    QImage* image;
    QPoint lastPoint;
    int penSize = 5;
    QColor penColor = Qt::black;
    const uint milisecondsToDrawAfterBrake = 2000;
    const uint maxDrawAreaHeight = 100;
    QTimer* timeToDraw;

    QImage* clearImage();
};

#endif // WRITEWIDGET_H
