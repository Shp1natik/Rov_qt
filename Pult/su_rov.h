#ifndef SU_ROV_H
#define SU_ROV_H

#include <QObject>
#include <QTimer>
#include "udpsender.h"
#include "ui_pultform.h"

class SU_ROV : public QObject
{
    Q_OBJECT
public:
    explicit SU_ROV(QObject *parent = 0);

    void setPsiDesired(double input);
    void setMarshDesired(double input);
    //
    double getPsiCurrent();
    double getMarshCurrent();
    double getdMarshCurrent();

    void Regulyator();

signals:

public slots:
    //void tick();

private:
    QTimer timer;
    //класс под прием и отправку
    UdpSender udp;
    //заданный, текущий курс и угловая скорость по курсу
    double psiDesired,psiCurrent,dPsi;
    //заданное, текущее положение по маршу и скорость по маршу
    double marshDesired,marshCurrent,dMarsh;
    //коэффициенты K1m,K2m
    double K1m,K2m;
    //коэффициенты K1psi,K2psi
    double K1psi,K2psi;
    //управляющие сигнал
    double Upsi;
    double UMarsh;
};

#endif // SU_ROV_H
