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
     * type:drawingPrompt;payLoad:drawingData;prompt:dog
     * type:gameImages;payLoad:fileData1,fileData2,fileData3;clients:1111,2222,3333
     * type:winnerChosen;payLoad:winner
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
    else if(separated.first() == "type:drawingPrompt") {
        qDebug() << ":: Client: recieved drawing prompt";
        QString payLoad{};
        QString drawingPrompt{};

        separated.pop_front();
        if(separated.front().contains("payLoad:")) {
            payLoad = separated.front();
            payLoad = payLoad.remove("payLoad:");
        }

        separated.pop_front();
        if(separated.front().contains("prompt:")) {
            drawingPrompt = separated.front();
            drawingPrompt = drawingPrompt.remove("prompt:");
        }

        if(!payLoad.isEmpty() && !drawingPrompt.isEmpty()) {
            emit drawingAndPromptReady(payLoad, drawingPrompt);
        }
    }
    //type:gameImages;payLoad:fileData1,fileData2,fileData3;clients:1111,2222,3333
    else if(separated.first() == "type:gameImages") {
        separated.pop_front();
        QString payLoad{};
        QString clients{};

        if(separated.first().contains("payLoad:")) {
            payLoad = separated.first();
            payLoad = payLoad.remove("payLoad:");
        }

        separated.pop_front();
        if(separated.first().contains("clients:")) {
            clients = separated.first();
            clients.remove("clients:");
        }

        if(payLoad != QString{} && clients != QString{}) {
            emit gameDrawingsReady(payLoad.split(QRegularExpression(",")), clients.split(QRegularExpression(",")));
        }
    }
    else if (separated.front() == "type:winnerChosen") {
        //type:winnerChosen;payLoad:winner
        QString winner{};

        separated.pop_front();
        if ( separated.front().contains( "payLoad:")) {
            winner = separated.front();
        }

        winner = winner.remove("payLoad:");
        if(winner != QString()) {
            emit winnerChosen( winner );
        }
    }
}
