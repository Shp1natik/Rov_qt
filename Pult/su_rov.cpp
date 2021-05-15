#include "su_rov.h"

SU_ROV::SU_ROV(QObject *parent) : QObject(parent)
{
    //курс
    psiDesired = 0;
    psiCurrent =0;
    K1psi=0.5;
    K2psi=0.345;
    dPsi = 0;
    Upsi = 0;
    //марш
    marshDesired = 0;
    marshCurrent = 0;
    K1m=31;
    K2m=21.65;
    dMarsh =0;
    UMarsh =0;

    //connect (&timer,SIGNAL(timeout()),SLOT(tick()));
    //timer.start(100);
}

void SU_ROV::setPsiDesired(double input)
{
    psiDesired=input;
}

void SU_ROV::setMarshDesired(double input)
{
    marshDesired=input;
}

double SU_ROV::getPsiCurrent()
{
    double v = udp.getData().Psi;
    return(v);
}

double SU_ROV::getMarshCurrent()
{
    double v = udp.getData().Marsh;
    return(v);
}

double SU_ROV::getdMarshCurrent()
{
    double v = udp.getData().dMarsh;
    return(v);
}

void SU_ROV::Regulyator()
{
    marshCurrent=udp.getData().Marsh;
    psiCurrent=udp.getData().Psi;
    dMarsh=udp.getData().dMarsh;
    dPsi=udp.getData().dPsi;
    //marshDesired = 1;
    //psiDesired=1;
    Upsi = (psiDesired-psiCurrent)*K1psi-(K2psi*dPsi);
    UMarsh = (marshDesired-marshCurrent)*K1m-(K2m*dMarsh);

    udp.send(Upsi,UMarsh);
}

/*void SU_ROV::tick()
{
    Regulyator();
    double MC = udp.getData().Marsh;
    PultWidget().currentMarshChanged(MC);
    double PC = udp.getData().Psi;
    PultWidget().currentYawchanged(PC);
    double dM = udp.getData().dMarsh;
    PultWidget().currentVxChanged(dM);
}*/
