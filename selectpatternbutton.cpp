#include "selectpatternbutton.h"


selectPatternButton::selectPatternButton(int value,QWidget* parent)
{
    this->number = value;
    btn = new QPushButton(parent);
}

int selectPatternButton::getNumber() const
{
    return number;
}

void selectPatternButton::setNumber(int value)
{
    number = value;
}
