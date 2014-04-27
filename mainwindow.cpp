#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->frame_Mid->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    this->setWindowTitle("Board game");
    InitSpace();
    InitPlayer();
    start();
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::InitPlayer()
{
    InitGame *init = new InitGame();
    init->exec();
    if(!init->result())
        exit(1);
    int nbPlayer = init->getNBPlayer();
    for (int i = 0; i < nbPlayer; i ++)
    {
        Player *p = new Player(0,init->getPieces()[i]);
        p->setSpaceName(spaces[0]->getName());
        players.append(p);
    }
    delete init;
    PrintPlayer();
}
void MainWindow::InitSpace()
{
    QFile file("spaces.txt");
    QString fileContent;
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        fileContent = file.readAll();
        file.close();
    }
    else
    {
        QMessageBox::critical(this,"Error","Can't load the space file.");
        exit(1);
    }
    QStringList lines = fileContent.split("\n");
    if(lines.size() < 80)
    {
        QMessageBox::critical(this,"Error","The space file is incorect.");
        exit(1);
    }
    for(int i = 0; i < 80; i += 2)
    {
        Space* s = new Space();
        s->setSpace(lines[i],lines[i + 1]);
        spaces.append(s);
    }
    CreateBoard();
}
void MainWindow::CreateBoard()
{    
    int i = 0;
    i = 12;
    while(i > -1)//Add bot
    {
        ui->layoutBot->addWidget(spaces[i]);
        i--;
    }
    i = 13;
    while( i < 20) //Add left
    {
        ui->layoutLeft->addWidget(spaces[i]);
        i++;
    }
    while(i < 33) // Add top
    {
        ui->layoutTop->addWidget(spaces[i]);
        i++;
    }
    while(i < 40)  //Add right
    {
        ui->layoutRight->addWidget(spaces[i]);
        i++;
    }
    ui->frame_Top->setMinimumHeight(70);
    ui->frame_Bot->setMinimumHeight(70);
    ui->frame_Left->setMinimumWidth(70);
    ui->frame_Right->setMinimumWidth(70);
}
void MainWindow::PrintPlayer()
{
    ui->frame_Player->setMinimumHeight(100);
    for(int i = 0; i < players.size(); i ++)
    {
        ui->layout_Player->addWidget(players[i]);        
    }    
}
void MainWindow::PlayerLeft()
{
    ui->txt_Log->appendPlainText("You don't have enough money, you lose");
    players[cPlayer]->leftGame();
    players.removeAt(cPlayer);
    if (players.size() == 1) {
        QMessageBox::information(this,"The champion","The player : " + players[0]->getPiece() + " win this game",QMessageBox::Ok,QMessageBox::NoButton);
        ui->btn_Leave->setEnabled(false);
        ui->btn_Roll->setEnabled(false);
    }
    else
        NextPlayer();
}
void MainWindow::NextPlayer()
{    
    //Update info of player to interface
    if(cPlayer != -1)
    {
        players[cPlayer]->setSpaceName(spaces[players[cPlayer]->getPos()]->getName());
    }
    cPlayer = (cPlayer + 1) % players.size();
    for(int i = 0; i < players.size(); i ++)
    {
        players[i]->setTopFrameStyle(0);
    }
    players[cPlayer]->setTopFrameStyle(1);
    ui->txt_Log->appendHtml("<h3>Now is " + players[cPlayer]->getPiece() + " turn</h3>");
    if (players[cPlayer]->getLostTurn() > 0) {
        ui->txt_Log->appendPlainText(players[cPlayer]->getPiece() + " lost his turn");
        players[cPlayer]->setLostTurn(players[cPlayer]->getLostTurn() - 1);
        ui->btn_Roll->setText("Next player");
        ui->txt_Log->appendPlainText("Next player or leave game");
    }
    else
        ui->txt_Log->appendPlainText("Roll dice or leave game");
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    int w = (width() - 10)/13;
    ui->frame_Left->setMinimumWidth(w);
    ui->frame_Right->setMinimumWidth(w);
}
void MainWindow::start()
{
    cPlayer = -1;
    NextPlayer();
}
void MainWindow::chest(int *i)
{
    int rdm = rand() % 7;
    switch (rdm) {
    case 0:
        QMessageBox::information(this,"Congratulations","Congratulations, you win a case against the bank, take 150$");
        players[*i]->setMoney(players[*i]->getMoney() + 150);
        break;
    case 1:
        QMessageBox::warning(this,"Warning","You throw rubbish in the street, pay 50$ as a penalty$");
        players[*i]->setMoney(players[*i]->getMoney() - 50);
        break;
    case 2:
        QMessageBox::warning(this,"Warning","You have an accident with your car, pay 40$ as a penalty$",QMessageBox::Ok,QMessageBox::NoButton);
        players[*i]->setMoney(players[*i]->getMoney() - 40);
        break;
    case 3:
        QMessageBox::warning(this,"Warning","You try to escape from prison, go to prison now",QMessageBox::Ok,QMessageBox::NoButton);
        players[*i]->setPos(30);
        players[*i]->setLostTurn(players[*i]->getLostTurn() + 1);
        break;
    case 4:
        QMessageBox::warning(this,"Warning","You lost a case, pay 20$ lawyer fees",QMessageBox::Ok,QMessageBox::NoButton);
        players[*i]->setMoney(players[*i]->getMoney() - 20);
        break;
    case 5:
        QMessageBox::information(this,"Congratulations","You win a prize, take 100$",QMessageBox::Ok,QMessageBox::NoButton);
        players[*i]->setMoney(players[*i]->getMoney() + 100);
        break;
    case 6:
        QMessageBox::information(this,"Congratulations","You had been accused, but your innocence appeared, take 200$ as amends",QMessageBox::Ok,QMessageBox::NoButton);
        players[*i]->setMoney(players[*i]->getMoney() + 200);
        break;
    }
    if (players[*i]->getMoney() < 0)
        return PlayerLeft();
}
void MainWindow::chance(int *i)
{
    int rdm = rand() % 7;
    switch (rdm) {
    case 0:
        QMessageBox::warning(this,"Warning","You're very naughty, pay 50$",QMessageBox::Ok,QMessageBox::NoButton);
        players[*i]->setMoney(players[*i]->getMoney() - 50);
        break;
    case 1:
        QMessageBox::information(this,"Congratulations","You win a big prize, take 350$",QMessageBox::Ok,QMessageBox::NoButton);
        players[*i]->setMoney(players[*i]->getMoney() + 350);
        break;
    case 2:
        QMessageBox::information(this,"Congratulations","You've got a new baby take 100$ as a gift",QMessageBox::Ok,QMessageBox::NoButton);
        players[*i]->setMoney(players[*i]->getMoney() + 100);
        break;
    case 3:
        QMessageBox::warning(this,"Warning","You're very kind, you payed 150 for father-less children",QMessageBox::Ok,QMessageBox::NoButton);
        players[*i]->setMoney(players[*i]->getMoney() - 150);
        break;
    case 4:
        QMessageBox::information(this,"Congratulations","It is your birthday take 50 as a gift",QMessageBox::Ok,QMessageBox::NoButton);
        players[*i]->setMoney(players[*i]->getMoney() + 50);
        break;
    case 5:
        QMessageBox::warning(this,"Warning","You pay 25$ each for your four children in school in fees",QMessageBox::Ok,QMessageBox::NoButton);
        players[*i]->setMoney(players[*i]->getMoney() - 100);
        break;
    case 6:
        QMessageBox::warning(this,"Warning","You win a very big prize, but you have to pay 30$ to take it",QMessageBox::Ok,QMessageBox::NoButton);
        players[*i]->setMoney(players[*i]->getMoney() - 30);
        break;
    }
    if (players[*i]->getMoney() < 0) {
        return PlayerLeft();
    }
}

void MainWindow::on_btn_Roll_clicked()
{
    if(ui->btn_Roll->text() == "Next player")
    {
        NextPlayer();
        ui->btn_Roll->setText("Roll");
        return;
    }
    int oldPos = players[cPlayer]->getPos();
    if(spaces[oldPos]->is2XSpeed())
        ui->txt_Log->appendPlainText("2XSpeed, hurry up!!!!\nYour roll dive result is: " + QString::number(players[cPlayer]->rollDice(spaces[oldPos]->is2XSpeed())));
    else
        ui->txt_Log->appendPlainText("Your roll dive result is: " + QString::number(players[cPlayer]->rollDice(spaces[oldPos]->is2XSpeed())));
    int newPos = players[cPlayer]->getPos();
    if (newPos < oldPos) {
        ui->txt_Log->appendPlainText(players[cPlayer]->getPiece() + " complete new round, take new 350$");
        players[cPlayer]->setMoney(players[cPlayer]->getMoney() + 350);
    }
    if (spaces[newPos]->isChance())
    {
        chance(&cPlayer);
    }
    else if (spaces[newPos]->isChest())
    {
        chest(&cPlayer);
    }
    else if (spaces[newPos]->isPrison())
    {
        if (players[cPlayer]->getMoney() >= 50) {
            ui->txt_Log->appendPlainText(players[cPlayer]->getPiece() + " fall in prison, you have to pay 50$");
            players[cPlayer]->setMoney(players[cPlayer]->getMoney() - 50);
        } else {
            ui->txt_Log->appendPlainText(players[cPlayer]->getPiece() + " fall in prison, you lost the next turn");
            players[cPlayer]->setLostTurn(players[cPlayer]->getLostTurn() + 1);
        }
    }
    else if (!spaces[newPos]->isPark())
    {
        if (spaces[newPos]->isFree() && players[cPlayer]->getMoney() >= spaces[newPos]->getPrice())
        {
            if (QMessageBox::question(this,"Buy a park", "Would you like to buy " + spaces[newPos]->getName(),
                                      QMessageBox::Yes,QMessageBox::No) == QMessageBox::Yes)
            {
                spaces[newPos]->setOwner(players[cPlayer]->getPiece());
                players[cPlayer]->setMoney(
                        players[cPlayer]->getMoney()
                                - spaces[newPos]->getPrice());
                if (!spaces[newPos]->isUp() && players[cPlayer]->getMoney() >= spaces[newPos]->getPrice())
                {
                    if (QMessageBox::question(this,"Upgrade", "Would you like to upgrade " + spaces[newPos]->getName() +
                                              ", it'll double price and fees too",
                                              QMessageBox::Yes,QMessageBox::No) == QMessageBox::Yes)
                    {
                        players[cPlayer]->setMoney(
                                players[cPlayer]->getMoney()
                                        - spaces[newPos]->getPrice());
                        spaces[newPos]->upgrade();
                    }
                }
            }
        }
        else
        {
            if (spaces[newPos]->getOwner().compare( players[cPlayer]->getPiece()) == 0)
            {
                if (!spaces[newPos]->isUp()
                        && players[cPlayer]->getMoney()
                                >= spaces[newPos]->getPrice()) {
                    if (QMessageBox::question(this,"Upgrade", "Would you like to upgrade " + spaces[newPos]->getName() +
                                              ", it'll double price and fees too",
                                              QMessageBox::Yes,QMessageBox::No) == QMessageBox::Yes)
                    {
                        players[cPlayer]->setMoney(
                                players[cPlayer]->getMoney()
                                        - spaces[newPos]->getPrice());
                        spaces[newPos]->upgrade();
                    }
                }
                if (QMessageBox::question(this,"Sell", "Would you like to sell " + spaces[newPos]->getName() +
                                          ", to bank",
                                          QMessageBox::Yes,QMessageBox::No) == QMessageBox::Yes)
                {
                    players[cPlayer]->setMoney(
                            players[cPlayer]->getMoney()
                                    + spaces[newPos]->getPrice());
                    spaces[newPos]->setOwner("No One");
                }
            }
            else
            {
                for (int l = 0; l < players.size(); ++l) {
                    if (l != cPlayer) {
                        if (players[l]->getPiece().compare(
                                spaces[newPos]->getOwner()) == 0) {
                            QMessageBox::information(this,"Notice", "You have to pay "
                                    + (QString::number(spaces[newPos]->getPrice()/ 10))
                                    + "$ to " + players[l]->getPiece()
                                    + "player\n",QMessageBox::Ok);
                            if (players[cPlayer]->getMoney()
                                    >= spaces[newPos]->getPrice()
                                            / 10) {
                                players[cPlayer]->setMoney(
                                        players[cPlayer]->getMoney()
                                                - (spaces[newPos]->getPrice()
                                                        / 10));
                                players[l]->setMoney(
                                        players[l]->getMoney()
                                                + (spaces[newPos]->getPrice()
                                                        / 10));
                            }
                            else
                            {
                                return PlayerLeft();
                            }
                        }
                    }
                }
            }
        }
    }
    NextPlayer();
}
void MainWindow::on_btn_Leave_clicked()
{
    ui->txt_Log->appendPlainText(players[cPlayer]->getPiece() + " leave game");
    for (int i = 0; i < spaces.size(); i++) {
        if (spaces[i]->getOwner().compare(players[cPlayer]->getPiece()) == 0)
            spaces[i]->setOwner("No One");
    }
    players[cPlayer]->leftGame();
    players.removeAt(cPlayer);
    if (players.size() == 1) {
        QMessageBox::information(this,"The champion","The player : " + players[0]->getPiece() + " win this game",QMessageBox::Ok,QMessageBox::NoButton);
        ui->btn_Leave->setEnabled(false);
        ui->btn_Roll->setEnabled(false);
    }
}
