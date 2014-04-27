#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Models/Space.h"
#include "Models/Player.h"
#include "initgame.h"
#include "QFile"
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    
private slots:
    void on_btn_Roll_clicked();
    void on_btn_Leave_clicked();

private:
    Ui::MainWindow *ui;
    void resizeEvent(QResizeEvent *);
    void CreateBoard();
    void PrintPlayer();
    void InitSpace();
    void InitPlayer();
    void PlayerLeft();
    void NextPlayer();

    int cPlayer;//Store turn of player
    /**
     *game loop
     *loop through player
     *each player roll dice and move to his new position
     */
    void start();
    void chest(int* i);
    void chance(int* i);
    //players in the game
    QList<Player*> players;
    //spaces in the board
    QList<Space*> spaces;
    //available pieces for players
    QList<QString> pieces;
};

#endif // MAINWINDOW_H
