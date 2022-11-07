#include "messageprocesshandler.h"
#include <QRegularExpression>

MessageProcessHandler::MessageProcessHandler(QObject *parent) : QObject{parent} {

}

// TODO: Create function to remove "payLoad" create function for each case
void MessageProcessHandler::processMessage(QString message) {
    /*
     * type:uniqueID;payLoad:5555
     * type:newLobbyCreated;payLoad:1111;clientList:1234,4444,5555
     * type:joinSuccess;payLoad:1111;clientList:1234,4444,5555
     * type:updatedClientList;payLoad:1234,4444,5555
     * type:lobbyMessage;payLoad:message:message;sender:1234;senderID:4444
     * type:readyListChanged;payLoad:;
     * type:gameReadyToBegin;payLoad:0
     *
    */

    QStringList separated{ message.split(QRegularExpression(";")) };
    if(separated.first() == "type:uniqueID") {
        separated.pop_front();
        if(separated.first().contains("payLoad:")) {
            QString newClientID{ separated.first() };
            newClientID = newClientID.remove("payLoad:");
            emit uniqueIDRegistration(newClientID);
        }
    }
    else if (separated.first() == "type:newLobbyCreated" || separated.first() == "type:joinSuccess") {
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
    else if(separated.first() == "type:lobbyMessage") {
        QString newMessage{};
        QString senderID{};
        separated.pop_front();
        if(separated.front().contains("payLoad:")) {
            newMessage = separated.front();
            newMessage = newMessage.remove("payLoad:");
        }
       separated.pop_front();
        if(separated.front().contains("sender:")) {
            senderID = separated.front();
            senderID = senderID.remove("sender:");
        }
        QString displayMessage{senderID + ": " + newMessage};
        emit newLobbyMessage(displayMessage);
    }
    else if(separated.first() == "type:readyListChanged") {
       separated.pop_front();
       QString payLoad{ separated.front() };
       payLoad = payLoad.remove("payLoad:");
       QStringList readyClients = payLoad.split(QRegularExpression(","));
       emit readyListChanged(readyClients);
    }
    else if(separated.first() == "type:gameReadyToBegin") {
        emit gameStarting();
    }

}
