#ifndef INITGAME_H
#define INITGAME_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class InitGame;
}

class InitGame : public QDialog
{
    Q_OBJECT
    
public:
    explicit InitGame(QWidget *parent = 0);
    ~InitGame();
    QList<QString> getPieces();
    int getNBPlayer();
    
private slots:
    void on_cb_NumberPlayer_currentIndexChanged(const QString &arg1);

    void on_buttonBox_accepted();

    void on_cb_Player1Piece_currentIndexChanged(const QString &arg1);

    void on_cb_Player2Piece_currentIndexChanged(const QString &arg1);

    void on_cb_Player3Piece_currentIndexChanged(const QString &arg1);

    void on_cb_Player4Piece_currentIndexChanged(const QString &arg1);

private:
    Ui::InitGame *ui;
    int nbPlayer;
    QList<QString> pieces;
    bool isLoaded;
    bool CheckExisted();
};

#endif // INITGAME_H
