#include "country.h"

Country::Country(QWidget *parent) :
    QWidget(parent)
{
    name = new QLabel("Contry");
    belong = new QLabel("No one");
    price = new QLabel("0");
    price->setAlignment(Qt::AlignRight);
    boder = new QFrame();
    boder->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    boder->setFrameShape(QFrame::WinPanel);
    boder->setFrameShadow(QFrame::Raised);
    QVBoxLayout *layout1 = new QVBoxLayout();
    layout1->addWidget(name);
    layout1->addWidget(belong);
    layout1->addWidget(price);
    boder->setLayout(layout1);
    boder->setMinimumSize(80,80);
}
void Country::paintEvent(QPaintEvent *)
{
    if(this->layout())
        delete this->layout();
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(boder);
    this->setLayout(layout);
}
