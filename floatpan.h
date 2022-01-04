#ifndef FLOATPAN_H
#define FLOATPAN_H

#include <QObject>
#include <QWidget>

namespace  Ui{
class FloatPan;
}

class FloatPan:public QWidget
{
    Q_OBJECT
public:
    explicit FloatPan(QWidget *parent = 0,QString text = "default");
    ~FloatPan();

    void setCustomText(QString text);
private:

    Ui::FloatPan *ui;
};

#endif // FLOATPAN_H
