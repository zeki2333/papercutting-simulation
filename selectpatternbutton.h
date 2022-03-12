#ifndef SELECTPATTERNBUTTON_H
#define SELECTPATTERNBUTTON_H

#include <QPushButton>

class selectPatternButton:public QPushButton
{
    Q_OBJECT
public:
    selectPatternButton(int value,QWidget* parent=nullptr);
    int getNumber() const;
    void setNumber(int value);

private:
    int number;
    QPushButton* btn;
};

#endif // SELECTPATTERNBUTTON_H
