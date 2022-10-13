#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include "websockethandler.h"
#include "messageprocessorhandler.h"

class GameManager : public QObject {
    Q_OBJECT
public:
    explicit GameManager(QObject *parent = nullptr);
    ~GameManager();

signals:

private:
    WebSocketHandler* socketHandler;
    MessageProcessorHandler* messageProcessHandler;

};

#endif // GAMEMANAGER_H
