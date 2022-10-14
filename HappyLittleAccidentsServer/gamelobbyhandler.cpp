#include "gamelobbyhandler.h"

GameLobbyHandler::GameLobbyHandler(QString lobbyID, QObject *parent) : lobbyID{lobbyID} , QObject{parent} {

}

void GameLobbyHandler::addClient(QString clientID) {
    if(!gameClientList.contains(clientID)) {
       gameClientList.append(clientID);
    }
}
