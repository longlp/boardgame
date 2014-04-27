#include "initgame.h"
#include "ui_initgame.h"

InitGame::InitGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InitGame)
{
    ui->setupUi(this);
    isLoaded = false;
    ui->cb_NumberPlayer->addItem("2");
    ui->cb_NumberPlayer->addItem("3");
    ui->cb_NumberPlayer->addItem("4");
    QStringList _pieces;
    _pieces.append("red");
    _pieces.append("blue");
    _pieces.append("green");
    _pieces.append("magenta");
    _pieces.append("cyan");
    _pieces.append("yellow");
    _pieces.append("orange");
    ui->cb_Player1Piece->addItems(_pieces);
    ui->cb_Player2Piece->addItems(_pieces);
    ui->cb_Player2Piece->setCurrentIndex(1);
    ui->cb_Player3Piece->addItems(_pieces);
    ui->cb_Player3Piece->setCurrentIndex(2);
    ui->cb_Player4Piece->addItems(_pieces);
    ui->cb_Player4Piece->setCurrentIndex(3);
    this->setMaximumHeight(10);
    ui->frame_Player3->hide();
    ui->frame_Player4->hide();
    isLoaded = true;
    this->setWindowTitle("Select players");
    this->adjustSize();
}

InitGame::~InitGame()
{
    delete ui;
}
void InitGame::on_cb_NumberPlayer_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "2")
    {
        ui->frame_Player3->hide();
        ui->frame_Player4->hide();
        this->adjustSize();
    }
    else if(arg1 == "3")
    {
        ui->frame_Player3->show();
        ui->frame_Player4->hide();
        this->adjustSize();
    }
    else if(arg1 == "4")
    {
        ui->frame_Player3->show();
        ui->frame_Player4->show();
    }
}
int InitGame::getNBPlayer()
{
    return nbPlayer;
}
QList<QString> InitGame::getPieces()
{
    return pieces;
}

void InitGame::on_buttonBox_accepted()
{
    if(!CheckExisted())
    {
        QMessageBox::critical(this,"Error","This color have been duplicated, we will reset it by default");
        ui->cb_Player1Piece->setCurrentIndex(0);
        ui->cb_Player2Piece->setCurrentIndex(1);
        ui->cb_Player3Piece->setCurrentIndex(2);
        ui->cb_Player4Piece->setCurrentIndex(3);
    }
    nbPlayer = ui->cb_NumberPlayer->currentIndex() + 2;
    pieces.append(ui->cb_Player1Piece->currentText());
    pieces.append(ui->cb_Player2Piece->currentText());
    pieces.append(ui->cb_Player3Piece->currentText());
    pieces.append(ui->cb_Player4Piece->currentText());
}
bool InitGame::CheckExisted()
{
    if(!isLoaded)
        return true;
    QStringList _pieces;
    if(ui->frame_Player3->isVisible() && ui->frame_Player4->isVisible())
    {
        _pieces.append(ui->cb_Player1Piece->currentText());
        _pieces.append(ui->cb_Player2Piece->currentText());
        _pieces.append(ui->cb_Player3Piece->currentText());
        _pieces.append(ui->cb_Player4Piece->currentText());
    }
    else if(ui->frame_Player3->isVisible())
    {
        _pieces.append(ui->cb_Player1Piece->currentText());
        _pieces.append(ui->cb_Player2Piece->currentText());
        _pieces.append(ui->cb_Player3Piece->currentText());
    }
    else
    {
        _pieces.append(ui->cb_Player1Piece->currentText());
        _pieces.append(ui->cb_Player2Piece->currentText());
    }
    int n = _pieces.size();
    _pieces.removeDuplicates();
    int m = _pieces.size();
    if (m < n)
        return false;
    return true;
}

void InitGame::on_cb_Player1Piece_currentIndexChanged(const QString &arg1)
{
    if(!CheckExisted())
    {
        QMessageBox::critical(this,"Error","This color have been choosen by another player, please select the other.");
        return;
    }
    ui->txt_Color1->setStyleSheet("background-color: " + arg1);
}

void InitGame::on_cb_Player2Piece_currentIndexChanged(const QString &arg1)
{    
    if(!CheckExisted())
    {
        QMessageBox::critical(this,"Error","This color have been choosen by another player, please select the other.");
        return;
    }
    ui->txt_Color2->setStyleSheet("background-color: " + arg1);
}

void InitGame::on_cb_Player3Piece_currentIndexChanged(const QString &arg1)
{
    if(!CheckExisted())
    {
        QMessageBox::critical(this,"Error","This color have been choosen by another player, please select the other.");
        return;
    }
    ui->txt_Color3->setStyleSheet("background-color: " + arg1);
}

void InitGame::on_cb_Player4Piece_currentIndexChanged(const QString &arg1)
{
    if(!CheckExisted())
    {
        QMessageBox::critical(this,"Error","This color have been choosen by another player, please select the other.");
        return;
    }
    ui->txt_Color4->setStyleSheet("background-color: " + arg1);
}
