#ifndef GAMELOBBYHANDLER_H
#define GAMELOBBYHANDLER_H

#include <QObject>
#include <QMap>

class GameLobbyHandler : public QObject {
    Q_OBJECT
public:
    explicit GameLobbyHandler(QString lobbyID, QObject *parent = nullptr);
    void addClient(QString clientID);
    QString clientsInLobby();
    QStringList clientsInLobbyList();
    void userReadyToPlay(QString clientID);
    QString whoIsReady();
    void newDrawingData(QString fileData, QString clientID);
    void newSecondDrawingData(QString fileData, QString clientID);
    void choosePrompt();
    QString prompt();
    void newVote(QString vote, QString clientID);

signals:
    void userReadyListChanged();
    void gameReadyToBegin();
    void allDrawingsRecieved(QMap<QString, QString> newMap);
    void allSecondDrawingsRecieved(QMap<QString, QString> newMap);
    void winnerChosen(QString winner);

private:
    QStringList prompts;
    QString selectedPrompt;
    QList<QString> gameClientList;
    QString lobbyID;
    QMap<QString, bool> clientReadyList;
    QMap<QString, QString> clientDrawingData;
    QMap<QString, QString> clientSecondDrawingData;
    QList<QString> clientsWhoVoted;
    QMap<QString, int> voteResults;
};

#endif // GAMELOBBYHANDLER_H
