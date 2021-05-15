#ifndef PULTWIDGET_H
#define PULTWIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include "su_rov.h"
#include "ui_pultform.h"

class PultWidget : public QWidget, Ui::Form
{
    Q_OBJECT
public:
    /*explicit*/ PultWidget(QWidget *parent = 0);
    ~PultWidget();
    SU_ROV rov;
    QTimer Timer;

private:
    double desiredYaw, desiredRoll, desiredPitch, desiredMarsh, desiredLag, desiredGlub;
    double Vx,Vy,Vz;

    QGraphicsScene *sceneYaw; //указатель на объект сцены Yaw
    QGraphicsScene *sceneRoll; //указатель на объект сцены Roll
    QGraphicsScene *scenePitch; //указатель на объект сцены Pitch
    //
    QGraphicsPixmapItem *picYawPointer;
    QGraphicsPixmapItem *picYawScale;
    //
    QGraphicsPixmapItem *picRollPointer;
    QGraphicsPixmapItem *picRollScale;
    //
    QGraphicsPixmapItem *picPitchPointer;
    QGraphicsPixmapItem *picPitchScale;
    //
public slots:
    void tick();

    void setYaw(int value);
    void setRoll(int value);
    void setPitch(int value);
    //------
    void resetYaw(bool);
    void resetRoll(bool);
    void resetPitch(bool);
    //------
    void addMarsh (bool);
    void decreaseMarsh (bool);
    void resetMarsh(bool);
    //------
    void addLag (bool);
    void decreaseLag (bool);
    void resetLag(bool);
    //------
    void addGlub (bool);
    void decreaseGlub (bool);
    void resetGlub(bool);
    //------
    void speedMarshChanged(bool);
    void speedLagChanged(bool);
    void speedGlubChanged(bool);
    //------
    void currentYawchanged (double value);
    void currentMarshChanged (double value);
    void currentVxChanged (double value);

};

#endif // PULTWIDGET_H
