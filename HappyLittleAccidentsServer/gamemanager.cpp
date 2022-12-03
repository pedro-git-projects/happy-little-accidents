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
    connect(messageProcessHandler, &MessageProcessorHandler::newDrawingData , this, &GameManager::newDrawingDataReady);
    connect(messageProcessHandler, &MessageProcessorHandler::newSecondDrawingData , this, &GameManager::newSecondDrawingDataReady);
}


GameManager::~GameManager() {
    socketHandler->deleteLater();
}

void GameManager::createGameLobbyRequest(QString uuid) {
    QString newLobbyID{ QString::fromStdString(uuid::generateUUId()) };
    GameLobbyHandler* newGameLobby = new GameLobbyHandler(newLobbyID, this);

    connect(newGameLobby, &GameLobbyHandler::userReadyListChanged, this, &GameManager::userReadyListChanged);
    connect(newGameLobby, &GameLobbyHandler::gameReadyToBegin, this, &GameManager::gameReadyToBegin);
    connect(newGameLobby, &GameLobbyHandler::allDrawingsRecieved, this, &GameManager::allDrawingsInGameLobbyRecieved);
    connect(newGameLobby, &GameLobbyHandler::allSecondDrawingsRecieved, this, &GameManager::allSecondDrawingsInGameLobbyRecieved);

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


void GameManager::newDrawingDataReady(QString fileData, QString clientID) {
    QList<GameLobbyHandler*> gameLobbyList = gameLobbyMap.values();
    foreach(GameLobbyHandler* existingLobby, gameLobbyList) {
       existingLobby->newDrawingData(fileData, clientID);
    }
}

void GameManager::newSecondDrawingDataReady(QString fileData, QString clientID) {
    QList<GameLobbyHandler*> gameLobbyList = gameLobbyMap.values();
    foreach(GameLobbyHandler* existingLobby, gameLobbyList) {
       existingLobby->newSecondDrawingData(fileData, clientID);
    }
}

void GameManager::allDrawingsInGameLobbyRecieved(QMap<QString, QString> sharedMap) {
    GameLobbyHandler* existingLobby{qobject_cast<GameLobbyHandler*>(sender())};
    //type:drawingPrompt;payLoad:drawingData;prompt:dog
    foreach(const QString& client, sharedMap.keys()) {
        QString dataPacket{"type:drawingPrompt;payLoad:" + sharedMap[client] + ";prompt:" + existingLobby->prompt()};
        socketHandler->sendTextMessageToClient(dataPacket, client);
    }
}

void GameManager::allSecondDrawingsInGameLobbyRecieved(QMap<QString, QString> drawingMap) {
    GameLobbyHandler* existingLobby{qobject_cast<GameLobbyHandler*>(sender())};
    //type:gameImages;payLoad:fileData1,fileData2,fileData3;clients:1111,2222,3333
    QString ret{"type:gameImages;payLoad:"};
    QString payLoad{};
    QString clients{};
    for (
         QMap<QString, QString>::iterator mapIterator = drawingMap.begin();
         mapIterator != drawingMap.end();
         mapIterator++
        ) {
        clients.append(mapIterator.key() + ",");
        payLoad.append(mapIterator.value() + ",");
    }
    clients.chop(1);
    payLoad.chop(1);

    ret.append(payLoad + ";clients:" + clients);
    socketHandler->sendTextMessageToMultipleClients(ret, existingLobby->clientsInLobbyList());
}
