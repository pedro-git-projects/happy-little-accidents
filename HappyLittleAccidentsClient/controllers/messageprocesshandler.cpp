#include "messageprocesshandler.h"
#include <QRegularExpression>

MessageProcessHandler::MessageProcessHandler(QObject *parent) : QObject{parent} {

}

void MessageProcessHandler::processMessage(QString message) {
    //type:uniqueID;payLoad:5555
    QStringList separated{ message.split(QRegularExpression(";")) };
    if(separated.first() == "type:uniqueID") {
        separated.pop_front();
        if(separated.first().contains("payLoad:")) {
            QString newClientID{ separated.first() };
            newClientID = newClientID.remove("payLoad:");
            emit uniqueIDRegistration(newClientID);
        }
    }
}
