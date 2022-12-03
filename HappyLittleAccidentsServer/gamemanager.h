#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <QMap>
#include "websockethandler.h"
#include "messageprocessorhandler.h"
#include "gamelobbyhandler.h"

class GameManager : public QObject {
    Q_OBJECT
public:
    explicit GameManager(QObject *parent = nullptr);
    ~GameManager();

public slots:
    void createGameLobbyRequest(QString uuid);
    void joinGameLobbyRequest(QString lobbyID, QString uuid);
    void messageLobbyRequest(QString message, QString lobbyID, QString senderID);
    void userReadyListChanged();
    void userReadyToPlay(QString uuid);
    void gameReadyToBegin();
    void newDrawingDataReady(QString fileData, QString clientID);
    void newSecondDrawingDataReady(QString fileData, QString clientID);
    void allDrawingsInGameLobbyRecieved(QMap<QString, QString> sharedMap);
    void allSecondDrawingsInGameLobbyRecieved(QMap<QString, QString> drawingMap);

signals:

private:
    WebSocketHandler* socketHandler;
    MessageProcessorHandler* messageProcessHandler;
    QMap<QString, GameLobbyHandler*> gameLobbyMap;

};

#endif // GAMEMANAGER_H
