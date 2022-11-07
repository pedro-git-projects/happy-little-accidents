#include "gamelobbyhandler.h"
#include <QDebug>
#include <random>
#include <QDateTime>

GameLobbyHandler::GameLobbyHandler(QString lobbyID, QObject *parent) : lobbyID{lobbyID} , QObject{parent} {
    clientReadyList.clear();
    clientDrawingData.clear();

    prompts = QStringList() << "dog" << "cat" << "elephant" << "car" << "tree";
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

void GameLobbyHandler::newDrawingData(QString fileData, QString clientID) {
    if(gameClientList.contains(clientID)) {
        clientDrawingData[clientID] = fileData;

        if(clientDrawingData.keys().size() == gameClientList.size()) {
            /* send drawings to other players
             provide a prompt */

            // key = clientID, value = drawing
            QMap<QString, QString> sharedDrawings;
            for(int i = 0; i < gameClientList.size(); i++) {
                QString currentClient{gameClientList.at(i)};
                QString drawing{};

                if(i == gameClientList.size() - 1) {
                    drawing = clientDrawingData[gameClientList.at(0)];
                } else {
                    drawing = clientDrawingData[gameClientList.at(i + 1)];
                }

                sharedDrawings[currentClient] = drawing;
            }
            choosePrompt();

            emit allDrawingsRecieved(sharedDrawings);
        }
    }
}

void GameLobbyHandler::choosePrompt() {
    std::default_random_engine generator;
    generator.seed(QDateTime::currentMSecsSinceEpoch());
    std::uniform_int_distribution<int> promptGenerator(0, prompts.size());
    selectedPrompt = prompts[promptGenerator(generator)];

}

QString GameLobbyHandler::prompt() {
    return selectedPrompt;
}


