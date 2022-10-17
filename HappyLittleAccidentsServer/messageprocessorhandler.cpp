#include "messageprocessorhandler.h"
#include <QDebug>
#include <QRegularExpression>

MessageProcessorHandler::MessageProcessorHandler(QObject *parent) : QObject{parent} {

}

void MessageProcessorHandler::processMessage(QString message) {
    /*
        type:createGame;payLoad:0;sender:5555
        type:joinGame;payLoad:4000;sender:5555
        type:message;payLoad:Message;sender5555
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

    if(separated.first() == "message") qDebug() << ":: Server message request";
}
