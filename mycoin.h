#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>

class myCoin : public QWidget
{
    Q_OBJECT
public:
//    explicit myCoin(QWidget *parent = nullptr);

    //参数代表是银币还是金币
       myCoin(QString btnImg);
signals:

};

#endif // MYCOIN_H
