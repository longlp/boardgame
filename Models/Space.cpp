#include "Space.h"

Space::Space(QWidget *parent) :
    QWidget(parent)
{
    name = new QLabel("Country");
    owner = new QLabel("No One");
    price = new QLabel("0");    
    CreateUI();
}

void Space::CreateUI()
{
    price->setAlignment(Qt::AlignRight);
    boder = new QFrame();
    boder->setFrameShape(QFrame::WinPanel);
    boder->setFrameShadow(QFrame::Raised);
    QVBoxLayout *left = new QVBoxLayout();
    left->addWidget(name);
    left->addWidget(owner);
    left->setContentsMargins(0,0,0,0);
    leftFrame = new QFrame();
    leftFrame->setLayout(left);
    flagFrame =new QFrame();
    flagFrame->setStyleSheet("background-color: red");
    flagFrame->setMinimumSize(20,20);
    QHBoxLayout *top = new QHBoxLayout();
    top->addWidget(leftFrame);
    top->addWidget(flagFrame);
    top->setContentsMargins(0,0,0,0);
    topFrame = new QFrame();
    topFrame->setLayout(top);

    QHBoxLayout *bot = new QHBoxLayout();
    cPlayer = new QFrame();
    cPlayer->setStyleSheet("background-color: red");
    cPlayer->setMinimumSize(10,10);
    cPlayer->setMaximumSize(30,10);
    cOwner = new QFrame();
    cOwner->setMinimumSize(10,10);
    cOwner->setMaximumSize(30,10);
    bot->addWidget(cPlayer);
    bot->addWidget(cOwner);
    bot->addWidget(price);
    bot->setContentsMargins(0,0,0,0);
    botFrame = new QFrame();
    botFrame->setLayout(bot);
    QVBoxLayout *spa = new QVBoxLayout();
    spa->addWidget(topFrame);
    spa->addWidget(botFrame);
    boder->setLayout(spa);
}

void Space::paintEvent(QPaintEvent *)
{
    if(this->layout())
        delete this->layout();
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(boder);
    this->setLayout(layout);
}
void Space::resizeEvent(QResizeEvent *)
{
    qDebug() << this->width() << " x " << this->height();
    if(this->width() < 95)
        flagFrame->hide();
    else
        flagFrame->show();
}

void Space::setMinimumSize(int minw, int minh)
{
    boder->setMinimumSize(minw,minh);
}
void Space::setSizePolicy(QSizePolicy::Policy horizontal, QSizePolicy::Policy vertical)
{
    boder->setSizePolicy(horizontal,vertical);
}
QString Space::getName() {
    return name->text();
}
void Space::setSpace(QString name, QString price)
{
    this->name->setText(name);
    this->price->setText(price);
}

void Space::setOwner(QString name) {
    owner->setText(name);
    cOwner->setStyleSheet("background-color: " + name);
}
int Space::getPrice() {
    return price->text().toInt();
}
bool Space::isChance() {
    return name->text().compare("Chance ") == 0;
}
bool Space::isChest() {
    return name->text().compare("Chest  ") == 0;
}
bool Space::isPrison() {
    return name->text().compare("Prison ") == 0;
}
bool Space::is2XSpeed() {
    return name->text().compare("2XSpeed") == 0;
}
bool Space::isPark() {
    return (name->text().compare("Park   ") == 0 || name->text().compare("Start  ") == 0)
            || is2XSpeed();
}
bool Space::isFree() {
    return owner->text().compare("No One") == 0 && !is2XSpeed();
}
QString Space::getOwner() {
    return owner->text();
}
bool Space::isUp() {
    return up;
}
void Space::upgrade() {
    price->setText(QString::number(price->text().toInt() * 2));
    up = true;
}
