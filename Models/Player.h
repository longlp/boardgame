#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QLabel>
#include <QFrame>
#include <QVBoxLayout>
#include <QPainter>

class Player : public QWidget
{
    Q_OBJECT
public:
    explicit Player(QWidget *parent = 0);
    /**
     * constructor
     * @param pos space position of player, at start (0) initially for all players
     * @param piece color piece of player
     */
    explicit Player(int pos, QString piece,QWidget *parent = 0);
    /**
     * setter method for position
     * @param pos space position of player, at start (0) initially for all players
     */
    void setPos(int pos);
    /**
     * setter method for piece
     * @param piece color piece of player
     */
    void setPiece(QString piece);
    /**
     * getter method for position
     * @return position
     */
    int getPos();
    /**
     * getter method for piece
     * @return piece
     */
    QString getPiece();
    /**
     * method to roll 2 dices,
     * change position of player
     * by adding values of dices to position
     * player loop in in circular spaces
     * @return value of the 2 dices
     */
    int rollDice(bool is2X);
    void setMoney(double money);
    double getMoney();
    void setLostTurn(int lostTurn);
    int getLostTurn();
    void setSpaceName(QString space);
    void leftGame();
    void setTopFrameStyle(int i);
private:
    int pos; //player space position
    QString piece; //piece type
    double money;
    int lostTurn;
    //Display variant
    QLabel *dPiece;
    QLabel *dSpace;
    QLabel *dMoney;
    QFrame *leftFrame;
    QFrame *rightFrame;
    QFrame *topFrame;
    QFrame *botFrame;

    void CreateUI();
    void paintEvent(QPaintEvent *);
};

#endif // PLAYER_H
