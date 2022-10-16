#include "messageprocesshandler.h"
#include <QRegularExpression>

MessageProcessHandler::MessageProcessHandler(QObject *parent) : QObject{parent} {

}

void MessageProcessHandler::processMessage(QString message) {
    /*
     * type:uniqueID;payLoad:5555
     * type:newLobbyCreated;payLoad:1111
     * type:joinSuccess;payLoad:1111
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
        if(separated.first().contains("payLoad:")) {
            QString newLobbyID{separated.first()};
            newLobbyID = newLobbyID.remove("payLoad:");
            emit newLobby(newLobbyID);
        }
    }
}
