#ifndef SPACE_H
#define SPACE_H

#include <QWidget>
#include <QLabel>
#include <QFrame>
#include <QVBoxLayout>
#include <QPainter>
#include <QDebug>

class Space : public QWidget
{
    Q_OBJECT
public:
    explicit Space(QWidget *parent = 0);
    void setMinimumSize(int minw, int minh);
    void setSizePolicy(QSizePolicy::Policy horizontal, QSizePolicy::Policy vertical);
    void setSpace(QString name,QString price);
    QString getName();
    QString getOwner();
    void setOwner(QString name);
    void setCurrentPlayer(QString name);

    int getPrice();
    void upgrade();
    bool isChance();
    bool isChest();
    bool isPrison();
    bool is2XSpeed();
    bool isPark();
    bool isFree();
    bool isUp();
private:
    QLabel *name;
    QLabel *owner;
    QLabel *price;
    QFrame *border;
    QFrame *flagFrame;
    QFrame *leftFrame;
    QFrame *topFrame;
    QFrame *botFrame;
    QFrame *cPlayer;
    QFrame *cOwner;
    bool up;
    void CreateUI();
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
signals:

public slots:

};

#endif // SPACE_H
