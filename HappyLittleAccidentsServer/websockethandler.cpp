#include "websockethandler.h"
#include <QDebug>

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

    auto nextClient = socketServer->nextPendingConnection();
    nextClient->setParent(this);

    connect(nextClient, &QWebSocket::textMessageReceived, this, &WebSocketHandler::onTextMessageRecieved);
    connect(nextClient, &QWebSocket::disconnected, this, &WebSocketHandler::onSocketDisconnected);

    clientList.append(nextClient);
}

void WebSocketHandler::onTextMessageRecieved(QString message) {
    qDebug() << ":: Recieved new client message: " << message << Qt::endl;

}

void WebSocketHandler::onSocketDisconnected() {
    auto client = qobject_cast<QWebSocket*>(sender());
    if(client) clientList.removeAll(client);
}
