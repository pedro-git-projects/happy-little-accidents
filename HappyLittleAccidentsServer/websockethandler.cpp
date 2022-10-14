#include "websockethandler.h"
#include <QDebug>
#include <QString>
#include <random>
#include "libs/uuid.h"

WebSocketHandler::WebSocketHandler(QObject *parent) : QObject{parent} {
    socketServer = new QWebSocketServer("HappyLittleAccidentsServer", QWebSocketServer::NonSecureMode, this);
    connect(socketServer, &QWebSocketServer::newConnection, this, &WebSocketHandler::onNewSocketConnection);

    if(socketServer->listen(QHostAddress::Any, 8585)){
       qDebug() << "Server is up!";
    } else {
       qDebug() << "Failed to start server";
    }
}

WebSocketHandler::~WebSocketHandler() {
    socketServer->deleteLater();
}

void WebSocketHandler::onNewSocketConnection() {
    qDebug() << ":: Server: New client connected";

    QString newClientID = QString::fromStdString(uuid::generateUUId());

    auto nextClient = socketServer->nextPendingConnection();
    nextClient->setParent(this);

    connect(nextClient, &QWebSocket::textMessageReceived, this, &WebSocketHandler::onTextMessageRecieved);
    connect(nextClient, &QWebSocket::disconnected, this, &WebSocketHandler::onSocketDisconnected);

    nextClient->sendTextMessage("type:uniqueID;payLoad:" + newClientID);

    clientList[newClientID] = nextClient;
}

void WebSocketHandler::onTextMessageRecieved(QString message) {
    qDebug() << ":: Server recieved: " << message;
    emit newMesssageToProcess(message);
}

void WebSocketHandler::sendTextMessageToClient(QString message, QString clientID) {
    if(clientList.contains(clientID)) {
        QWebSocket* existingClient = clientList[clientID];
        existingClient->sendTextMessage(message);

    }
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
