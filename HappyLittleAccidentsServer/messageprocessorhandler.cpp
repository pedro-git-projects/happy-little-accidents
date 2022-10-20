#include "messageprocessorhandler.h"
#include <QDebug>
#include <QRegularExpression>

MessageProcessorHandler::MessageProcessorHandler(QObject *parent) : QObject{parent} {

}

void MessageProcessorHandler::processMessage(QString message) {
    /*
    type:createGame;payLoad:0;sender:5555
    type:joinGame;payLoad:4000;sender:5555
    type:message;payLoad:Message;lobbyID:4590;sender5555
    type:readyToPlay;payLoad:1;sender:5555
    */

    QStringList separated = message.split( QRegularExpression(";"));

    if(separated.first() == "type:createGame") {
        qDebug() << ":: Server: Create game request";

        separated.pop_front();
        separated.pop_front();
        if(separated.first().contains("sender:")) {
            QString senderID{ separated.first() };
            senderID = senderID.remove("sender:");
            emit createGameRequest(senderID);
        }
    }

    if(separated.first() == "type:joinGame") {
        qDebug() << ":: Server: Join game request";
        separated.pop_front();
        QString lobbyID{};
        QString senderID{};

        if(separated.first().contains("payLoad:")) {
            lobbyID = separated.first();
            lobbyID = lobbyID.remove("payLoad:");
        }
        separated.pop_front();
        if(separated.front().contains("sender:")){
            senderID = separated.front();
            senderID = senderID.remove("sender:");
        }
        if(lobbyID != QString{} && senderID != QString{}) emit joinGameLobbyRequest(lobbyID, senderID);
    }

    if(separated.first() == "type:message") {
        qDebug() << ":: Server: Lobby message request";
        QString payLoad{};
        QString lobbyID{};
        QString senderID{};

        separated.pop_front();
        if(separated.front().contains("payLoad:")) {
            payLoad = separated.front();
            payLoad = payLoad.remove("payLoad:");
        }

        separated.pop_front();
        if(separated.front().contains("lobbyID:")) {
            lobbyID = separated.front();
            lobbyID = lobbyID.remove("lobbyID:");
        }

        separated.pop_front();
        if(separated.front().contains("sender:")) {
            senderID = separated.front();
            senderID = senderID.remove("sender:");
        }

        if(payLoad != QString{} && lobbyID != QString{} && senderID != QString{}) {
            emit messageLobbyRequest(payLoad, lobbyID, senderID);
        }
    }
    else if(separated.front() == "type:readyToPlay") {
        //type:readyToPlay;payLoad:1;sender:5555
        if(separated.back().contains("sender:")) {
            QString clientID = separated.back();
            clientID = clientID.remove("sender:");
            emit clientReadyToPlay(clientID);
        }
    }
}
