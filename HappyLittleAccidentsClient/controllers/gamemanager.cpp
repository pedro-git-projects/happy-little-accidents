#include "gamemanager.h"
#include <QDebug>

GameManager::GameManager(QObject *parent) :
    QObject{parent},
    lobbyRoomCode(QString()),
    clientID{QString{}},
    clientsInLobby(QStringList())
{

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

QStringList GameManager::getClientsInLobby() {
    return clientsInLobby;
}

void GameManager::joinLobbyRequest(QString lobbyID) {
    //type:joinGame;payLoad:4000;sender:5555
    emit readyToSendNewMessage("type:joinGame;payLoad:"+lobbyID+";sender:"+clientID);
}

void GameManager::setClientsInLobby(QStringList clients) {
   if(clientsInLobby != clients) {
       clientsInLobby = clients;
       emit clientsInLobbyChanged();
   }
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

void GameManager::joinedLobby(QString lobbyID, QStringList clients) {
    setLobbyRoomCode(lobbyID);
    setClientsInLobby(clients);
    emit inGameLobby();
}

void GameManager::createGameRequest() {
   // "type:createGame;payLoad:0;sender:" + clientID
    emit readyToSendNewMessage("type:createGame;payLoad:0;sender:" + clientID);
}
