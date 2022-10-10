#include "gamemanager.h"

GameManager::GameManager(QObject *parent) : QObject{parent} {
    socketHandler = new WebSocketHandler(this);
}


GameManager::~GameManager() {
    // reduntand because destruction propagates for children objects
    socketHandler->deleteLater();
}
