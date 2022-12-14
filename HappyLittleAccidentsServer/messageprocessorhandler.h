#ifndef MESSAGEPROCESSORHANDLER_H
#define MESSAGEPROCESSORHANDLER_H

#include <QObject>

class MessageProcessorHandler : public QObject {
    Q_OBJECT
public:
    explicit MessageProcessorHandler(QObject *parent = nullptr);

public slots:
    void processMessage(QString message);

signals:
    void createGameRequest(QString uuid);
    void joinGameLobbyRequest(QString lobbyID, QString uuid);
    void messageLobbyRequest(QString message, QString LobbyID, QString sender);
    void clientReadyToPlay(QString uuid);
    void newDrawingData(QString fileData, QString clientID);
    void newSecondDrawingData(QString fileData, QString clientID);
    void newVote(QString vote, QString clientID);

};

#endif // MESSAGEPROCESSORHANDLER_H
