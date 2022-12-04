#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include "controllers/messageprocesshandler.h"

class GameManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString lobbyRoomCode READ getLobbyRoomCode WRITE setLobbyRoomCode NOTIFY lobbyRoomCodeChanged)
    Q_PROPERTY(QStringList clientsInLobby READ getClientsInLobby WRITE setClientsInLobby NOTIFY clientsInLobbyChanged)
    Q_PROPERTY(QString drawingPrompt READ getDrawingPrompt WRITE setDrawingPrompt NOTIFY drawingPromptChanged)
    Q_PROPERTY(QStringList drawingList READ getDrawingList WRITE setDrawingList NOTIFY drawingListChanged);
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
    Q_INVOKABLE void drawingFinished();
    Q_INVOKABLE QString getDrawingPrompt();
    Q_INVOKABLE QString drawingFilePath();
    Q_INVOKABLE QStringList getDrawingList();
    Q_INVOKABLE void castVote(QString imagURL);

public slots:
    void setLobbyRoomCode(QString lobbyCode);
    void procssSocketMessage(QString message);
    void registerUUID(QString uuid);
    void joinedLobby(QString lobbyID, QStringList clients);
    void setClientsInLobby(QStringList clientList);
    void newClientReadyList(QStringList readyClients);
    void drawingAndPromptReady(QString data, QString prompt);
    void setDrawingPrompt(QString prompt);
    void gameDrawingsReady(QStringList images, QStringList clients);
    void setDrawingList(QStringList newList);

signals:
    void lobbyRoomCodeChanged();
    void readyToSendNewMessage(QString message);
    void inGameLobby();
    void clientsInLobbyChanged();
    void newLobbyMessage(QString message);
    void readyListChanged();
    void gameStarting();
    void drawingPromptChanged();
    void drawPromptTime();
    void drawingListChanged();
    void votingTime();

private:
    QString clientID;
    QString lobbyRoomCode;
    QString drawingPrompt;
    MessageProcessHandler* messageProcessHandler;
    QStringList clientsInLobby;
    QStringList readyClientsList;
    bool isSecondDrawing;
    QStringList drawingList;

};

#endif // GAMEMANAGER_H
