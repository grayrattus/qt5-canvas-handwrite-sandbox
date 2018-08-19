#ifndef PENOPTIONS_H
#define PENOPTIONS_H

#include <QDialog>
#include <WriteWidget.h>

namespace Ui {
class PenOptions;
}

class PenOptions : public QDialog
{
    Q_OBJECT

public:
    explicit PenOptions(QWidget *parent = 0, const WriteWidget *writeWidgetInstance = 0);
    ~PenOptions();
public slots:
    void changeChangeColorButtonColor(const QColor &color);
private:
    Ui::PenOptions *ui;
};

#endif // PENOPTIONS_H
