#ifndef SELECTPATTERNBUTTON_H
#define SELECTPATTERNBUTTON_H

#include <QPushButton>

class selectPatternButton:public QPushButton
{
    Q_OBJECT
public:
    selectPatternButton(int value,QWidget* parent=nullptr){this->number = value;
                                                           btn = new QPushButton(parent);};
    selectPatternButton(int value,QPushButton* BTN){this->number = value;
                                                   btn = BTN;};
    int getNumber() const{return number;};
    void setNumber(int value){number = value;};

private:
    int number;
    QPushButton* btn;
};
#endif // SELECTPATTERNBUTTON_H
