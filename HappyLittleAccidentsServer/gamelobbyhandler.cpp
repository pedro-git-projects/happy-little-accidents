#include "gamelobbyhandler.h"
#include <QDebug>

GameLobbyHandler::GameLobbyHandler(QString lobbyID, QObject *parent) : lobbyID{lobbyID} , QObject{parent} {
    clientReadyList.clear();
}

void GameLobbyHandler::addClient(QString clientID) {
    if(!gameClientList.contains(clientID)) {
       gameClientList.append(clientID);
    }
    clientReadyList.clear();
    foreach(const QString& client, gameClientList) {
        clientReadyList[client] = false;
    }
    emit userReadyListChanged();
}

QString GameLobbyHandler::clientsInLobby() {
    QString ret{};
    foreach (const QString& client, gameClientList) {
        ret.append(client + ",");
    }
    ret.chop(1);
    return ret;
}

QStringList GameLobbyHandler::clientsInLobbyList() {
    return gameClientList;
}

void GameLobbyHandler::userReadyToPlay(QString clientID) {
    if(this->gameClientList.contains(clientID)) {
       this->clientReadyList[clientID] = true;
        emit userReadyListChanged();
        bool notReady{false};
        foreach(const QString& clientID, this->clientReadyList.keys()) {
            if(!this->clientReadyList[clientID]) {
                notReady = true;
            }

        }
       if(!notReady) {
               emit gameReadyToBegin();
       }
    }

}

QString GameLobbyHandler::whoIsReady() {
    QString returnValue{};
    foreach(const QString& clientID, this->clientReadyList.keys()) {
        if(clientReadyList[clientID]) {
            returnValue.append(clientID + ",");
         }
    }
    if(returnValue != QString{}) { returnValue.chop(1); }
    return returnValue;
}
