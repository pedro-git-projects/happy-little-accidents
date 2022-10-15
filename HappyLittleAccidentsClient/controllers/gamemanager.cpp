#include "gamemanager.h"
#include <QDebug>

GameManager::GameManager(QObject *parent) : QObject{parent}, lobbyRoomCode(QString()), clientID{QString{}} {

    messageProcessHandler = new MessageProcessHandler{this};

    connect(messageProcessHandler, &MessageProcessHandler::uniqueIDRegistration, this, &GameManager::registerUUID);
    connect(messageProcessHandler, &MessageProcessHandler::newLobby, this, &GameManager::joinedLobby);
}

GameManager::~GameManager() {
    messageProcessHandler->deleteLater();
}

QString GameManager::getLobbyRoomCode() {
    return lobbyRoomCode;
}

void GameManager::setLobbyRoomCode(QString lobbyCode) {
    if(this->lobbyRoomCode != lobbyCode) {
       this->lobbyRoomCode = lobbyCode;
       emit lobbyRoomCodeChanged();
    }
}

void GameManager::procssSocketMessage(QString message) {
    messageProcessHandler->processMessage(message);
}

void GameManager::registerUUID(QString uuid) {
    qDebug() << ":: Client: UUID recieved " + uuid;
    clientID = uuid;
}

void GameManager::joinedLobby(QString lobbyID) {
    setLobbyRoomCode(lobbyID);
    emit inGameLobby();
}

void GameManager::createGameRequest() {
   // "type:createGame;payLoad:0;sender:" + clientID
    emit readyToSendNewMessage("type:createGame;payLoad:0;sender:" + clientID);
}
