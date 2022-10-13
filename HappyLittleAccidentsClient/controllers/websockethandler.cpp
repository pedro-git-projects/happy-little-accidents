#include "websockethandler.h"
#include <QDebug>

WebSocketHandler::WebSocketHandler(QObject *parent) : QObject{parent} {
    webSocket = new QWebSocket;

    connect(webSocket, &QWebSocket::connected, this, &WebSocketHandler::onConnected);
    connect(webSocket, &QWebSocket::textMessageReceived, this, &WebSocketHandler::onTextMessageRecieved);

}

WebSocketHandler::~WebSocketHandler() {
    webSocket->deleteLater();
}

void WebSocketHandler::onConnected() {
    qDebug() << ":: Client: Connection established";
    webSocket->sendTextMessage("type:createGame");
}

void WebSocketHandler::onTextMessageRecieved(QString message) {
    qDebug() << ":: Client: Recieved message " << message;

}

void WebSocketHandler::connectToServer(QString hostAddress) {
    qDebug() << ":: Client: Conecting to server...";
    webSocket->open(hostAddress);
}
