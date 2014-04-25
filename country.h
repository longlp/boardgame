#ifndef COUNTRY_H
#define COUNTRY_H

#include <QWidget>
#include <QLabel>
#include <QFrame>
#include <QVBoxLayout>
#include <QPainter>

class Country : public QWidget
{
    Q_OBJECT
public:
    explicit Country(QWidget *parent = 0);    
private:
    QLabel *name;
    QLabel *belong;
    QLabel *price;
    QFrame *boder;

    void paintEvent(QPaintEvent *);
signals:
    
public slots:
    
};

#endif // COUNTRY_H
