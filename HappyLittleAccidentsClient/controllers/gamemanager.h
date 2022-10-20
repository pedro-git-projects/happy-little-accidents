#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include "controllers/messageprocesshandler.h"

class GameManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString lobbyRoomCode READ getLobbyRoomCode WRITE setLobbyRoomCode NOTIFY lobbyRoomCodeChanged)
    Q_PROPERTY(QStringList clientsInLobby READ getClientsInLobby WRITE setClientsInLobby NOTIFY clientsInLobbyChanged)
public:
    explicit GameManager(QObject *parent = nullptr);
    ~GameManager();
    Q_INVOKABLE QString getLobbyRoomCode();
    Q_INVOKABLE void createGameRequest();
    Q_INVOKABLE QStringList getClientsInLobby();
    Q_INVOKABLE void joinLobbyRequest(QString lobbyID);
    Q_INVOKABLE void sendMessageToLobby(QString message);
    Q_INVOKABLE bool isClientReady(QString clientID);
    Q_INVOKABLE void readyToPlay();

public slots:
    void setLobbyRoomCode(QString lobbyCode);
    void procssSocketMessage(QString message);
    void registerUUID(QString uuid);
    void joinedLobby(QString lobbyID, QStringList clients);
    void setClientsInLobby(QStringList clientList);
    void newClientReadyList(QStringList readyClients);

signals:
    void lobbyRoomCodeChanged();
    void readyToSendNewMessage(QString message);
    void inGameLobby();
    void clientsInLobbyChanged();
    void newLobbyMessage(QString message);
    void readyListChanged();

private:
    QString clientID;
    QString lobbyRoomCode;
    MessageProcessHandler* messageProcessHandler;
    QStringList clientsInLobby;
    QStringList readyClientsList;

};

#endif // GAMEMANAGER_H
