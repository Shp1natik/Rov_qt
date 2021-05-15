#ifndef UDPSENDER_H
#define UDPSENDER_H
#include <QUdpSocket>


//структура данных, отправляемая в модель
struct ToMatlab{
    ToMatlab(){Upsi=0;UMarsh=0;}
    double Upsi; //это управляющий сигнал по курсу
    double UMarsh;//это управляющий сигнал по маршу
};
//[1] = структура данных, принятых от модели в Matlab
struct FromMatlab{
    FromMatlab(){Psi=0;dPsi=0;Marsh=0;dMarsh=0;}
    double Psi;//курс
    double dPsi;//угловая скорость по курсу
    double Marsh;//марш
    double dMarsh;//линейная скорость по маршу
};

class UdpSender:public QObject
{
    Q_OBJECT
public:
    UdpSender(QObject *prt = nullptr);
private:
    //данные для отпаврки и приема
    ToMatlab sendData;
    FromMatlab receivedData;

    QUdpSocket *m_socket;
    QUdpSocket *m_receiveSocket;

public slots:
    //метод, который отправляет сообщение с новыми управляющими сигналами U
    void send(double U1, double U2);
    void readData();

public:
    FromMatlab getData(){return receivedData;}

};
#endif // UDPSENDER_H
