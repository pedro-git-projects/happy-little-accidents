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
    if(gameClientList.contains(clientID)) {
       clientReadyList[clientID] = true;
       emit userReadyListChanged();
    }

}

QString GameLobbyHandler::whoIsReady() {
    QString returnValue{};
    QStringList clientsReadyList = clientReadyList.keys();
    for(int index = 0; index < clientsReadyList.size(); index++) {
        QString clientID = clientsReadyList[index];
        if(this->clientReadyList[clientID]) {
            returnValue.append(clientID + ",");
        }
    }

    if(returnValue != QString{}) returnValue.chop(1);
    return returnValue;
}
