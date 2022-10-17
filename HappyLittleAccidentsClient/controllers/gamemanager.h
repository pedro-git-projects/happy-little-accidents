#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include "controllers/messageprocesshandler.h"

class GameManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString lobbyRoomCode)
    Q_PROPERTY(QStringList clientsInLobby)
public:
    explicit GameManager(QObject *parent = nullptr);
    ~GameManager();
    Q_INVOKABLE QString getLobbyRoomCode();
    Q_INVOKABLE void createGameRequest();
    Q_INVOKABLE QStringList getClientsInLobby();

public slots:
    void setLobbyRoomCode(QString lobbyCode);
    void procssSocketMessage(QString message);
    void registerUUID(QString uuid);
    void joinedLobby(QString lobbyID, QStringList clients);
    void setClientsInLobby(QStringList clientList);

signals:
    void lobbyRoomCodeChanged();
    void readyToSendNewMessage(QString message);
    void inGameLobby();
    void clientsInLobbyChanged();

private:
    QString clientID;
    QString lobbyRoomCode;
    MessageProcessHandler* messageProcessHandler;
    QStringList clientsInLobby;

};

#endif // GAMEMANAGER_H
