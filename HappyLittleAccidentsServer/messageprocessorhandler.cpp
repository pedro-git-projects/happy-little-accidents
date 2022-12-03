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
    type:drawingData;payLoad:fileData;sender:clientID
    type:secondDrawingData;payLoad:fileData;sender:clientID
    */

    QStringList separated{ message.split( QRegularExpression(";")) };

    if(separated.first() == "type:createGame") {
        // Create Game
        qDebug() << ":: Server: Create game request";

        separated.pop_front();
        separated.pop_front();
        if(separated.first().contains("sender:")) {
            QString senderID{ separated.first() };
            senderID = senderID.remove("sender:");
            emit createGameRequest(senderID);
        }
    }

    else if(separated.first() == "type:joinGame") {
        // Join Game
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

    else if(separated.first() == "type:message") {
        // message lobby
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
        // ready to play
        if(separated.back().contains("sender:")) {
            QString clientID{separated.back()};
            clientID = clientID.remove("sender:");
            emit clientReadyToPlay(clientID);
        }
    }
    else if(separated.front() == "type:drawingData" || separated.front() == "type:secondDrawingData") {
        /*CLIENT ID IS NULL*/
        qDebug() << ":: Server: recieved data packet";
        QString fileData{};
        QString clientID{};
        QString type{separated.front()};
        type = type.remove("type:");
        qDebug() << "TYPE::" << type << Qt::endl;

        separated.pop_front();
        if(separated.front().contains("payLoad:")) {
           fileData = separated.front();
           fileData = fileData.remove("payLoad:");
        }
        separated.pop_front();

        if(separated.front().contains("sender:")) {
           clientID = separated.front();
           clientID = clientID.remove("sender:");
        }

        qDebug() << "CLIENT ID::" << clientID << Qt::endl;
        qDebug() << "FILE DATA::" << fileData;

        if(fileData != QString{} && clientID != QString{} && type == "drawingData") {
            emit newDrawingData(fileData, clientID);
        } else if(fileData != QString{} && clientID != QString{} && type == "secondDrawingData") {
            qDebug() << ":: Server: recieved second drawing data packet";
            emit newSecondDrawingData(fileData, clientID);
        }
    }
}

