#include "messageprocesshandler.h"
#include <QRegularExpression>

MessageProcessHandler::MessageProcessHandler(QObject *parent) : QObject{parent} {

}

void MessageProcessHandler::processMessage(QString message) {
    /*
     * type:uniqueID;payLoad:5555
     * type:newLobbyCreated;payLoad:1111;clientList:1234,4444,5555
     * type:joinSuccess;payLoad:1111;clientList:1234,4444,5555
     * type:updatedClientList;payLoad:1234,4444,5555
    */

    QStringList separated{ message.split(QRegularExpression(";")) };
    if(separated.first() == "type:uniqueID") {
        separated.pop_front();
        if(separated.first().contains("payLoad:")) {
            QString newClientID{ separated.first() };
            newClientID = newClientID.remove("payLoad:");
            emit uniqueIDRegistration(newClientID);
        }
    } else if (separated.first() == "type:newLobbyCreated" || separated.first() == "type:joinSuccess") {
        qDebug() << ":: Client: client joined lobby";
        separated.pop_front();
        QString newLobbyID{};
        QStringList lobbyClients{};
        if(separated.first().contains("payLoad:")) {
            newLobbyID = separated.first();
            newLobbyID = newLobbyID.remove("payLoad:");
        }

        separated.pop_front();
        if(separated.first().contains("clientList:")) {
            QString clients{separated.first()};
            clients = clients.remove("clientList:");
            lobbyClients = clients.split(QRegularExpression(","));
        }
        qDebug() << ":: Client: Clients in lobby: " << lobbyClients;

        if(newLobbyID != QString{} && lobbyClients != QStringList{}) {
            emit newLobby(newLobbyID, lobbyClients);
        }
    }
    else if(separated.first() == "type:updatedClientList") {
        qDebug() << ":: Client: Recieved updated client list";
        separated.pop_front();
        QString payLoad{ separated.front() };
        payLoad = payLoad.remove("payLoad:");
        emit lobbyListUpdated(payLoad.split(QRegularExpression(",")));
    }

}
