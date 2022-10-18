#include "gamemanager.h"
#include "libs/uuid.h"

GameManager::GameManager(QObject *parent) : QObject{parent} {
    socketHandler  =  new WebSocketHandler{this};
    messageProcessHandler = new MessageProcessorHandler{this};

    connect(socketHandler, &WebSocketHandler::newMesssageToProcess, messageProcessHandler, &MessageProcessorHandler::processMessage);
    connect(messageProcessHandler, &MessageProcessorHandler::createGameRequest, this, &GameManager::createGameLobbyRequest);
    connect(messageProcessHandler, &MessageProcessorHandler::joinGameLobbyRequest, this, &GameManager::joinGameLobbyRequest);
    connect(messageProcessHandler, &MessageProcessorHandler::messageLobbyRequest, this, &GameManager::messageLobbyRequest);
}


GameManager::~GameManager() {
    socketHandler->deleteLater();
}

void GameManager::createGameLobbyRequest(QString uuid) {
    QString newLobbyID{ QString::fromStdString(uuid::generateUUId()) };
    GameLobbyHandler* newGameLobby = new GameLobbyHandler(newLobbyID, this);
    newGameLobby->addClient(uuid);
    gameLobbyMap[newLobbyID] = newGameLobby;
    qDebug() << ":: Server: New game lobby created - ID: " << newLobbyID  << Qt::endl;
    socketHandler->sendTextMessageToClient("type:newLobbyCreated;payLoad:" + newLobbyID + ";clientList:" + newGameLobby->clientsInLobby(), uuid);
}

void GameManager::joinGameLobbyRequest(QString lobbyID, QString uuid) {
    if(gameLobbyMap.contains(lobbyID)) {
        GameLobbyHandler* existingLobby = gameLobbyMap[lobbyID];
        existingLobby->addClient(uuid);
        socketHandler->sendTextMessageToMultipleClients("type:updatedClientList;payLoad:" + existingLobby->clientsInLobby(), existingLobby->clientsInLobbyList());
        socketHandler->sendTextMessageToClient("type:joinSuccess;payLoad:" + lobbyID + ";clientList:" + existingLobby->clientsInLobby(), uuid);
    } else {
       socketHandler->sendTextMessageToClient("type:joinError;payload:DNE", uuid);
    }
}

void GameManager::messageLobbyRequest(QString message, QString lobbyID, QString senderID) {
    if(gameLobbyMap.contains(lobbyID)) {
       GameLobbyHandler* existingLobby = gameLobbyMap[lobbyID];
       socketHandler->sendTextMessageToMultipleClients("type:lobbyMessage;payLoad:" + message + ";sender:" + senderID, existingLobby->clientsInLobbyList());
    }
}
