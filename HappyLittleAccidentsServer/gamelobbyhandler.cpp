#include "gamelobbyhandler.h"
#include <QDebug>

GameLobbyHandler::GameLobbyHandler(QString lobbyID, QObject *parent) : lobbyID{lobbyID} , QObject{parent} {

}

void GameLobbyHandler::addClient(QString clientID) {
    if(!gameClientList.contains(clientID)) {
       gameClientList.append(clientID);
    }
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
