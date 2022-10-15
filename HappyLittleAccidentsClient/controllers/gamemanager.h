#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include "controllers/messageprocesshandler.h"

class GameManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString lobbyRoomCode)
public:
    explicit GameManager(QObject *parent = nullptr);
    ~GameManager();
    Q_INVOKABLE QString getLobbyRoomCode();
    Q_INVOKABLE void createGameRequest();

public slots:
    void setLobbyRoomCode(QString lobbyCode);
    void procssSocketMessage(QString message);
    void registerUUID(QString uuid);
    void joinedLobby(QString lobbyID);

signals:
    void lobbyRoomCodeChanged();
    void readyToSendNewMessage(QString message);
    void inGameLobby();

private:
    QString clientID;
    QString lobbyRoomCode;
    MessageProcessHandler* messageProcessHandler;

};

#endif // GAMEMANAGER_H
