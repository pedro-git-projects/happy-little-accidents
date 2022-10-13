#include "gamemanager.h"

GameManager::GameManager(QObject *parent) : QObject{parent} {
    socketHandler = new WebSocketHandler(this);
    messageProcessHandler = new MessageProcessorHandler(this);

    connect(socketHandler, &WebSocketHandler::newMesssageToProcess, messageProcessHandler, &MessageProcessorHandler::processMessage);
}


GameManager::~GameManager() {
    socketHandler->deleteLater();
}
