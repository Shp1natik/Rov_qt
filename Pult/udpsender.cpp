#include "udpsender.h"


UdpSender::UdpSender(QObject *prt):QObject(prt)
{
    //создаем сокеты
    m_socket = new QUdpSocket(this);

    qDebug()<<m_socket->bind(QHostAddress::LocalHost,13041);
    qDebug()<<m_socket->errorString();

    //[2] - добавляем сокет под приём
    m_receiveSocket = new QUdpSocket(this);

    qDebug()<<m_receiveSocket->bind(QHostAddress::LocalHost,13044);
    qDebug()<<m_receiveSocket->errorString();

    //[3] соединяем слот, который считывает данные из порта с сигналом
    //о том, что пришли новые сообщения readyRead()
    connect(m_receiveSocket,SIGNAL(readyRead()),this,SLOT(readData()));

}
void UdpSender::send(double U1, double U2)
{
    sendData.Upsi=U1;
    sendData.UMarsh=U2;
    m_socket->writeDatagram((char*)&sendData,sizeof (sendData),QHostAddress::LocalHost,13042);
    //qDebug()<<"send";
}

void UdpSender::readData()
{
    while (m_receiveSocket->hasPendingDatagrams()){
        m_receiveSocket->readDatagram((char*)&receivedData,sizeof(receivedData));
        //qDebug()<<"received";
    }
}
