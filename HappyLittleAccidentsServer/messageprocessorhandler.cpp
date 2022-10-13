#include "messageprocessorhandler.h"
#include <QDebug>

MessageProcessorHandler::MessageProcessorHandler(QObject *parent) : QObject{parent} {

}

void MessageProcessorHandler::processMessage(QString message) {
    qDebug() << ":: Message to process: " << message << Qt::endl;
}
