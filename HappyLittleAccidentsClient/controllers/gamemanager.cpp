#include "gamemanager.h"
#include <QDebug>
#include <QFile>
#include <QDir>

GameManager::GameManager(QObject *parent) :
    QObject{ parent },
    lobbyRoomCode{QString{}},
    clientID{QString{}},
    clientsInLobby{QStringList{}},
    readyClientsList{QStringList{}},
    drawingPrompt{QString{}}
{

    messageProcessHandler = new MessageProcessHandler{this};

    connect(messageProcessHandler, &MessageProcessHandler::uniqueIDRegistration, this, &GameManager::registerUUID);
    connect(messageProcessHandler, &MessageProcessHandler::newLobby, this, &GameManager::joinedLobby);
    connect(messageProcessHandler, &MessageProcessHandler::lobbyListUpdated, this, &GameManager::setClientsInLobby);
    connect(messageProcessHandler, &MessageProcessHandler::newLobbyMessage, this, &GameManager::newLobbyMessage);
    connect(messageProcessHandler, &MessageProcessHandler::readyListChanged, this, &GameManager::newClientReadyList);
    connect(messageProcessHandler, &MessageProcessHandler::gameStarting, this, &GameManager::gameStarting);
    connect(messageProcessHandler, &MessageProcessHandler::drawingAndPromptReady, this, &GameManager::drawingAndPromptReady);
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
    // type:joinGame;payLoad:4000;sender:5555
    emit readyToSendNewMessage("type:joinGame;payLoad:"+lobbyID+";sender:"+clientID);
}

void GameManager::sendMessageToLobby(QString message) {
   // type:message;payLoad:Message;lobbyID:4590;sender5555
    emit readyToSendNewMessage("type:message;payLoad:" + message + ";lobbyID:" + lobbyRoomCode + ";sender:" + clientID);
}

bool GameManager::isClientReady(QString clientID) {
    return this->readyClientsList.contains(clientID);
}

void GameManager::readyToPlay() {
    //type:readyToPlay;payLoad:1;sender:5555
    emit readyToSendNewMessage("type:readyToPlay;payLoad:1;sender:" + clientID);
}

void GameManager::drawingFinished() {
    /*
       open the canvas png
       load the data into a qbyte array
       create a packet
       send packet to server
    */

    QFile imageFile{ "temp.png" };
    if(!imageFile.open(QIODevice::ReadOnly)) return;

    QByteArray fileData{ imageFile.readAll() };
    imageFile.close();

    // type:drawingData;payLoad:fileData;sender:clientID
    QString dataPacket{ "type:drawingData;payLoad:" + fileData.toHex() + ";sender:" + clientID };
    emit readyToSendNewMessage(dataPacket);
}

QString GameManager::getDrawingPrompt() {
    return drawingPrompt;
}

QString GameManager::drawingFilePath() {
    QString localPath{QDir::currentPath()};
    QString ret{"file:///"+ localPath + QDir::separator() + clientID  + ".png"};
    return ret;
}

void GameManager::setClientsInLobby(QStringList clients) {
   if(clientsInLobby != clients) {
       clientsInLobby = clients;
       emit clientsInLobbyChanged();
   }
}

void GameManager::newClientReadyList(QStringList readyClients) {
    if(readyClientsList != readyClients) {
        readyClientsList = readyClients;
        emit readyListChanged();
    }
}

void GameManager::drawingAndPromptReady(QString data, QString prompt) {
    setDrawingPrompt(prompt);
    QFile tempImage{clientID + ".png"};

    if(!tempImage.open(QIODevice::WriteOnly)) {
        qDebug() << ":: Client: failed to open image";
        return;
    }

    QByteArray fileContents{QByteArray::fromHex(data.toLocal8Bit())};
    tempImage.write(fileContents);
    tempImage.flush();
    tempImage.close();

    emit drawPromptTime();
}

void GameManager::setDrawingPrompt(QString prompt) {
    if(drawingPrompt != prompt) {
       drawingPrompt = prompt;
       emit drawingPromptChanged();
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
