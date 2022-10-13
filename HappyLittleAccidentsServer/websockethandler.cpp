#include "websockethandler.h"
#include <QDebug>
#include <QString>
#include <random>
#include "libs/uuid.h"

WebSocketHandler::WebSocketHandler(QObject *parent) : QObject{parent} {
    socketServer = new QWebSocketServer("HappyLittleAccidentsServer", QWebSocketServer::NonSecureMode, this);
    connect(socketServer, &QWebSocketServer::newConnection, this, &WebSocketHandler::onNewSocketConnection);

    if(socketServer->listen(QHostAddress::Any, 8585)){
       qDebug() << "Server is up!" << Qt::endl;
    } else {
       qDebug() << "Failed to start server" << Qt::endl;
    }
}

WebSocketHandler::~WebSocketHandler() {
    socketServer->deleteLater();
}

void WebSocketHandler::onNewSocketConnection() {
    qDebug() << ":: New client connected" << Qt::endl;

    QString newClientID = QString::fromStdString(uuid::generateUUId());

    auto nextClient = socketServer->nextPendingConnection();
    nextClient->setParent(this);

    connect(nextClient, &QWebSocket::textMessageReceived, this, &WebSocketHandler::onTextMessageRecieved);
    connect(nextClient, &QWebSocket::disconnected, this, &WebSocketHandler::onSocketDisconnected);

    clientList[newClientID] = nextClient;
}

void WebSocketHandler::onTextMessageRecieved(QString message) {
    qDebug() << ":: Recieved: " << message << Qt::endl;
    emit newMesssageToProcess(message);
}

void WebSocketHandler::onSocketDisconnected() {
    auto client = qobject_cast<QWebSocket*>(sender());
    if(client) {
       for(QMap<QString, QWebSocket*>::iterator mapIterator = clientList.begin(); mapIterator != clientList.end(); mapIterator++) {
            if(mapIterator.value() == client) {
                QString uuid = mapIterator.key();
                clientList.remove(uuid);
                client->deleteLater();
            }
       }
    }
}
