#include "Player.h"

Player::Player(QWidget *parent) :
    QWidget(parent)
{
    pos = 0;
    piece = "";
    money = 1200;
    lostTurn = 0;
    CreateUI();
}

Player::Player(int pos, QString piece, QWidget *parent):
    QWidget(parent)
{
//    srand(time(NULL));
    this->pos = pos;
    this->piece = piece;
    money = 1200;
    lostTurn = 0;
    CreateUI();
}
void Player::CreateUI()
{
    QLabel *t1 = new QLabel("Player: ");
    QLabel *t2 = new QLabel("Curent space: ");
    QLabel *t3 = new QLabel("Money: ");
    t1->setAlignment(Qt::AlignRight);
    t2->setAlignment(Qt::AlignRight);
    t3->setAlignment(Qt::AlignRight);

    dPiece = new QLabel(this->piece);
    dSpace = new QLabel("");
    dMoney = new QLabel(QString::number(money));
    dPiece->setAlignment(Qt::AlignLeft);
    dSpace->setAlignment(Qt::AlignLeft);
    dMoney->setAlignment(Qt::AlignLeft);

    QVBoxLayout *left = new QVBoxLayout();
    QVBoxLayout *right = new QVBoxLayout();
    left->setContentsMargins(0,0,0,0);
    right->setContentsMargins(0,0,0,0);
    left->addWidget(t1);
    left->addWidget(t2);
    left->addWidget(t3);
    right->addWidget(dPiece);
    right->addWidget(dSpace);
    right->addWidget(dMoney);

    leftFrame = new QFrame();
    rightFrame  = new QFrame();
    topFrame = new QFrame();
    botFrame = new QFrame();
    leftFrame->setLayout(left);
    rightFrame->setLayout(right);
    QHBoxLayout *top = new QHBoxLayout();
    top->addWidget(leftFrame);
    top->addWidget(rightFrame);
    topFrame->setLayout(top);
    botFrame->setStyleSheet("background-color: " + this->piece);
    topFrame->setFrameShape(QFrame::WinPanel);
    topFrame->setFrameShadow(QFrame::Sunken);
    botFrame->setFrameShape(QFrame::WinPanel);
    botFrame->setFrameShadow(QFrame::Raised);
    topFrame->setMinimumSize(100,100);
    botFrame->setMinimumSize(100,20);

}
void Player::paintEvent(QPaintEvent *)
{
    if(this->layout())
        delete this->layout();
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(topFrame);
    layout->addWidget(botFrame);
    this->setLayout(layout);
}

void Player::setPos(int pos) {
    emit changePost(this->pos,pos);
    this->pos = pos;
}
void Player::setPiece(QString piece) {
    this->piece = piece;
}
int Player::getPos() {
    return pos;
}
QString Player::getPiece() {
    return piece;
}
int Player::rollDice(bool is2X) {
    int old = this->pos;
    int dice1 = rand() % 6 + 1;
    if (is2X) {
        pos = (pos + (dice1 * 2)) % 40;
    } else
        pos = (pos + (dice1)) % 40;
    emit changePost(old,pos);
    return dice1;
}

void Player::setMoney(double money) {
    this->money = money;
    dMoney->setText(QString::number(money));
}
double Player::getMoney() {
    return money;
}
void Player::setLostTurn(int lostTurn) {
    this->lostTurn = lostTurn;
}
int Player::getLostTurn() {
    return lostTurn;
}
void Player::setSpaceName(QString space)
{
    dSpace->setText(space);
}
void Player::leftGame()
{
    botFrame->setStyleSheet("");
    dSpace->setText("-----");
}
void Player::setTopFrameStyle(int i)
{
    if(i)
        topFrame->setFrameShadow(QFrame::Raised);
    else
        topFrame->setFrameShadow(QFrame::Sunken);
}
