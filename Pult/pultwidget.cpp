#include "pultwidget.h"
#include <cmath>

PultWidget::PultWidget(QWidget *parent) : QWidget(parent)
{
    setupUi(this);
    //
    desiredYaw=0;
    desiredRoll=0;
    desiredPitch=0;
    //
    //----
    //
    desiredMarsh=0;
    desiredLag=0;
    desiredGlub=0;
    //
    //----
    //
    Vx=0;
    Vy=0;
    Vz=0;
    //
    sceneYaw = new QGraphicsScene (ViewYaw);
    sceneRoll = new QGraphicsScene (ViewRoll);
    scenePitch = new QGraphicsScene (ViewPitch);
    //
    ViewYaw->setScene(sceneYaw);
    ViewRoll->setScene(sceneRoll);
    ViewPitch->setScene(scenePitch);
    //
    //ViewYaw->setStyleSheet("background: blue");
    ViewYaw->setRenderHint(QPainter::Antialiasing);
    //
    picYawPointer = sceneYaw->addPixmap(QPixmap(":/comp/yawPointer.png"));
    picYawScale = sceneYaw->addPixmap(QPixmap(":/comp/yawScale.png"));
    picRollPointer = sceneRoll->addPixmap(QPixmap(":/comp/rollPointer.png"));
    picRollScale = sceneRoll->addPixmap(QPixmap(":/comp/rollScale.png"));
    picPitchPointer = scenePitch->addPixmap(QPixmap(":/comp/pitchPointer.png"));
    picPitchScale = scenePitch->addPixmap(QPixmap(":/comp/pitchScale.png"));
    //Установим точку в середину стрелки
    picYawPointer->setTransformOriginPoint(picYawPointer->pixmap().width()/2,picYawPointer->pixmap().height()/2);
    picRollPointer->setTransformOriginPoint(picRollPointer->pixmap().width()/2,picRollPointer->pixmap().height()/2);
    picPitchPointer->setTransformOriginPoint(picPitchPointer->pixmap().width()/2,picPitchPointer->pixmap().height()/2);
    //
    for (int i = 0; i<tblPaPostion->rowCount();++i)
        for (int j = 0; j<tblPaPostion->columnCount(); ++j)
        {
            if (tblPaPostion->item(i,j)==0)
            {
                tblPaPostion->setItem(i,j,new QTableWidgetItem());
                tblPaPostion->item(i,j)->setTextAlignment(Qt::AlignCenter);
                tblPaPostion->item(i,j)->setText(QString::number(0));
            }
        }
    //Соединение сигналов и слотов;
    //Таймер
    connect(&Timer,SIGNAL(timeout()),SLOT(tick()));
    Timer.start(10);
    //Тумблеры углов
    connect(dial_yaw,SIGNAL(valueChanged(int)),this,SLOT(setYaw(int)));
    connect(dial_roll,SIGNAL(valueChanged(int)),this,SLOT(setRoll(int)));
    connect(dial_pitch,SIGNAL(valueChanged(int)),this,SLOT(setPitch(int)));
    //Сбросы углов
    connect(resetYawBtn,SIGNAL(clicked(bool)),this,SLOT(resetYaw(bool)));
    connect(resetRollBtn,SIGNAL(clicked(bool)),this,SLOT(resetRoll(bool)));
    connect(resetPitchBtn,SIGNAL(clicked(bool)),this,SLOT(resetPitch(bool)));
    //Кнопки +/-
    connect(marshPlusBtn,SIGNAL(clicked(bool)),this,SLOT(addMarsh(bool)));
    connect(lagPlusBtn,SIGNAL(clicked(bool)),this,SLOT(addLag(bool)));
    connect(glubPlusBtn,SIGNAL(clicked(bool)),this,SLOT(addGlub(bool)));
    connect(marshMinusBtn,SIGNAL(clicked(bool)),this,SLOT(decreaseMarsh(bool)));
    connect(lagMinusBtn,SIGNAL(clicked(bool)),this,SLOT(decreaseLag(bool)));
    connect(glubMinusBtn,SIGNAL(clicked(bool)),this,SLOT(decreaseGlub(bool)));
    //Кнопки сброса
    connect(resetMarshBtn,SIGNAL(clicked(bool)),this,SLOT(resetMarsh(bool)));
    connect(resetLagBtn,SIGNAL(clicked(bool)),this,SLOT(resetLag(bool)));
    connect(resetGlubBtn,SIGNAL(clicked(bool)),this,SLOT(resetGlub(bool)));
    //Кнопки ввода скорости
    connect(speedMarshEnter,SIGNAL(clicked(bool)),this,SLOT(speedMarshChanged(bool)));
    connect(speedLagEnter,SIGNAL(clicked(bool)),this,SLOT(speedLagChanged(bool)));
    connect(speedGlubEnter,SIGNAL(clicked(bool)),this,SLOT(speedGlubChanged(bool)));
}
PultWidget::~PultWidget()
{

}

void PultWidget::tick()
{
    rov.setPsiDesired(desiredYaw);
    rov.setMarshDesired(desiredMarsh);

    rov.Regulyator();
    double MC = rov.getMarshCurrent();
    currentMarshChanged(MC);
    double PC = rov.getPsiCurrent();
    currentYawchanged(PC);
    double dM = rov.getdMarshCurrent();
    currentVxChanged(dM);

}
/*{
    rov.Regulyator();
    double MC = rov.getMarshCurrent();
    currentMarshChanged(MC);
    double PC = rov.getPsiCurrent();
    currentYawchanged(PC);
    double dM = rov.getdMarshCurrent();
    currentVxChanged(dM);
}*/

void PultWidget::setYaw(int value)
{
    desiredYaw=value;
    //picYawPointer->setRotation(desiredYaw);
    //rov.setPsiDesired(desiredYaw);
    resetYawBtn->setText(QString::number(desiredYaw));
    tblPaPostion->item(0,6)->setText(QString::number(desiredYaw));
}

void PultWidget::setRoll(int value)
{
    desiredRoll=value;
    //picRollPointer->setRotation(currentRoll);
    resetRollBtn->setText(QString::number(desiredRoll));
    tblPaPostion->item(0,7)->setText(QString::number(desiredRoll));
}

void PultWidget::setPitch(int value)
{
    desiredPitch=value;
    //picPitchPointer->setRotation(desiredPitch);
    resetPitchBtn->setText(QString::number(desiredPitch));
    tblPaPostion->item(0,8)->setText(QString::number(desiredPitch));
}

void PultWidget::resetYaw(bool)
{
    desiredYaw=0;
    //rov.setPsiDesired(desiredYaw);
    //picYawPointer->setRotation(currentYaw);
    resetYawBtn->setText(QString::number(desiredYaw));
    dial_yaw->setValue(desiredYaw);
    tblPaPostion->item(0,6)->setText(QString::number(desiredYaw));
}

void PultWidget::resetRoll(bool)
{
    desiredRoll=0;
    //picRollPointer->setRotation(currentRoll);
    resetRollBtn->setText(QString::number(desiredRoll));
    dial_roll->setValue(desiredRoll);
    tblPaPostion->item(0,7)->setText(QString::number(desiredRoll));
}

void PultWidget::resetPitch(bool)
{
    desiredPitch=0;
    //picPitchPointer->setRotation(currentPitch);
    resetPitchBtn->setText(QString::number(desiredPitch));
    dial_pitch->setValue(desiredPitch);
    tblPaPostion->item(0,8)->setText(QString::number(desiredPitch));
}

void PultWidget::addMarsh(bool)
{
    desiredMarsh+=0.1;
    //rov.setMarshDesired(desiredMarsh);
    resetMarshBtn->setText(QString::number(desiredMarsh));
    tblPaPostion->item(0,0)->setText(QString::number(desiredMarsh));
}

void PultWidget::decreaseMarsh(bool)
{
    desiredMarsh-=0.1;
    //rov.setMarshDesired(desiredMarsh);
    resetMarshBtn->setText(QString::number(desiredMarsh));
    tblPaPostion->item(0,0)->setText(QString::number(desiredMarsh));
}

void PultWidget::resetMarsh(bool)
{
    desiredMarsh=0;
    //rov.setMarshDesired(desiredMarsh);
    resetMarshBtn->setText(QString::number(desiredMarsh));
    tblPaPostion->item(0,0)->setText(QString::number(desiredMarsh));
}

void PultWidget::addLag(bool)
{
    desiredLag+=0.1;
    resetLagBtn->setText(QString::number(desiredLag));
    tblPaPostion->item(0,2)->setText(QString::number(desiredLag));
}

void PultWidget::decreaseLag(bool)
{
    desiredLag-=0.1;
    resetLagBtn->setText(QString::number(desiredLag));
    tblPaPostion->item(0,2)->setText(QString::number(desiredLag));
}

void PultWidget::resetLag(bool)
{
    desiredLag=0;
    resetLagBtn->setText(QString::number(desiredLag));
    tblPaPostion->item(0,2)->setText(QString::number(desiredLag));
}

void PultWidget::addGlub(bool)
{
    desiredGlub+=1;
    resetGlubBtn->setText(QString::number(desiredGlub));
    tblPaPostion->item(0,4)->setText(QString::number(desiredGlub));
}

void PultWidget::decreaseGlub(bool)
{
    desiredGlub-=1;
    resetGlubBtn->setText(QString::number(desiredGlub));
    tblPaPostion->item(0,4)->setText(QString::number(desiredGlub));
}

void PultWidget::resetGlub(bool)
{
    desiredGlub=0;
    resetGlubBtn->setText(QString::number(desiredGlub));
    tblPaPostion->item(0,4)->setText(QString::number(desiredGlub));
}

void PultWidget::speedMarshChanged(bool)
{

    if (speedMarsh->text().isEmpty())
    {
        Vx = 0;
        tblPaPostion->item(0,1)->setText(QString());
    }
    else
    {
        Vx = speedMarsh->text().toDouble();
    tblPaPostion->item(0,1)->setText(QString::number(Vx));
    }
}

void PultWidget::speedLagChanged(bool)
{
    if (speedMarsh->text().isEmpty())
    {
        Vz = 0;
        tblPaPostion->item(0,3)->setText(QString());
    }
    else
    {
        Vz = speedLag->text().toDouble();
        tblPaPostion->item(0,3)->setText(QString::number(Vz));
    }
}

void PultWidget::speedGlubChanged(bool)
{
    if (speedGlub->text().isEmpty())
    {
        Vy = 0;
        tblPaPostion->item(0,5)->setText(QString());
    }
    else
    {
        Vy = speedLag->text().toDouble();
        tblPaPostion->item(0,5)->setText(QString::number(Vy));
    }
}

void PultWidget::currentYawchanged(double value)
{
    picYawPointer->setRotation(value);
    tblPaPostion->item(1,6)->setText(QString::number(round(value*10)/10));
}

void PultWidget::currentMarshChanged(double value)
{
    tblPaPostion->item(1,0)->setText(QString::number(round(value*100)/100));
}

void PultWidget::currentVxChanged(double value)
{
    tblPaPostion->item(1,1)->setText(QString::number(round(value*100)/100));
}

