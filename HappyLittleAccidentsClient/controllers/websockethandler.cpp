#include "websockethandler.h"
#include <QDebug>

WebSocketHandler::WebSocketHandler(QObject *parent) : QObject{parent}, clientID(QString()) {
    webSocket = new QWebSocket;

    connect(webSocket, &QWebSocket::connected, this, &WebSocketHandler::onConnected);
    connect(webSocket, &QWebSocket::textMessageReceived, this, &WebSocketHandler::onTextMessageRecieved);

    messageProcessor = new MessageProcessHandler(this);
    connect(messageProcessor, &MessageProcessHandler::uniqueIDRegistration, this, &WebSocketHandler::registerID);
}

WebSocketHandler::~WebSocketHandler() {
    webSocket->deleteLater();
}

void WebSocketHandler::onConnected() {
    qDebug() << ":: Client: Connection established";
   // webSocket->sendTextMessage("type:createGame;payload:0");
}

void WebSocketHandler::onTextMessageRecieved(QString message) {
    qDebug() << ":: Client: Recieved message " << message;
    messageProcessor->processMessage(message);

}

void WebSocketHandler::registerID(QString id) {
    clientID = id;
    qDebug() << ":: Client: New Client ID is " + clientID;
}

void WebSocketHandler::connectToServer(QString hostAddress) {
    qDebug() << ":: Client: Conecting to server...";
    webSocket->open(hostAddress);
}
