#include "gamelobbyhandler.h"

GameLobbyHandler::GameLobbyHandler(QObject *parent) : QObject{parent} {

}

void GameLobbyHandler::addClient(QString clientID) {
    if(!gameClientList.contains(clientID)) {
       gameClientList.append(clientID);
    }
}
