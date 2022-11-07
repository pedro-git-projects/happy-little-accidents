#include "gamemanager.h"
#include "libs/uuid.h"

GameManager::GameManager(QObject *parent) : QObject{parent} {
    socketHandler  =  new WebSocketHandler{this};
    messageProcessHandler = new MessageProcessorHandler{this};

    connect(socketHandler, &WebSocketHandler::newMesssageToProcess, messageProcessHandler, &MessageProcessorHandler::processMessage);
    connect(messageProcessHandler, &MessageProcessorHandler::createGameRequest, this, &GameManager::createGameLobbyRequest);
    connect(messageProcessHandler, &MessageProcessorHandler::joinGameLobbyRequest, this, &GameManager::joinGameLobbyRequest);
    connect(messageProcessHandler, &MessageProcessorHandler::messageLobbyRequest, this, &GameManager::messageLobbyRequest);
    connect(messageProcessHandler, &MessageProcessorHandler::clientReadyToPlay, this, &GameManager::userReadyToPlay);
}


GameManager::~GameManager() {
    socketHandler->deleteLater();
}

void GameManager::createGameLobbyRequest(QString uuid) {
    QString newLobbyID{ QString::fromStdString(uuid::generateUUId()) };
    GameLobbyHandler* newGameLobby = new GameLobbyHandler(newLobbyID, this);

    connect(newGameLobby, &GameLobbyHandler::userReadyListChanged, this, &GameManager::userReadyListChanged);
    connect(newGameLobby, &GameLobbyHandler::gameReadyToBegin, this, &GameManager::gameReadyToBegin);

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


void GameManager::userReadyListChanged() {
    GameLobbyHandler* existingLobby = qobject_cast<GameLobbyHandler*>(sender());
    socketHandler->sendTextMessageToMultipleClients("type:readyListChanged;payLoad:" + existingLobby->whoIsReady(), existingLobby->clientsInLobbyList());
}

void GameManager::userReadyToPlay(QString uuid) {
    qDebug() << "::Server: User is ready: " << uuid;
    QList<GameLobbyHandler*> gameLobbyList = gameLobbyMap.values();
    foreach(GameLobbyHandler* existingLobby, gameLobbyList) {
        existingLobby->userReadyToPlay(uuid);
    }
}

void GameManager::gameReadyToBegin() {
    GameLobbyHandler* existingLobby = qobject_cast<GameLobbyHandler*>(sender());
    // type:gameReadyToBegin;payLoad:0
    socketHandler->sendTextMessageToMultipleClients("type:gameReadyToBegin;payLoad:0", existingLobby->clientsInLobbyList());
}
