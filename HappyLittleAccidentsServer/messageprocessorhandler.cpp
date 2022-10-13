#include "messageprocessorhandler.h"
#include <QDebug>
#include <QRegularExpression>

MessageProcessorHandler::MessageProcessorHandler(QObject *parent) : QObject{parent} {

}

void MessageProcessorHandler::processMessage(QString message) {
    //qDebug() << ":: Message to process: " << message << Qt::endl;
    /*
        type:createGame;payLoad:0;sender:5555
        type:joinGame;payLoad:4000;sender:5555
        type:message;payLoad:Message;sender5555
    */

    QStringList separated = message.split( QRegularExpression(";"));
    if(separated.first() == "type:createGame") qDebug() << ":: Server: Create game request";
    if(separated.first() == "type:joinGame") qDebug() << ":: Server: type:joinGame";
    if(separated.first() == "message") qDebug() << ":: Server message request";
}
