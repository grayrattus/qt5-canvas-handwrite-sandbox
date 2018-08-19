#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <WriteWidget.h>
#include <PenOptions.h>
#include <maincanvas.h>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
private:
    Ui::MainWindow *ui;
    WriteWidget* writeWidget;
    MainCanvas* mainCanvas;
    PenOptions* penOptions;
};

#endif // MAINWINDOW_H
