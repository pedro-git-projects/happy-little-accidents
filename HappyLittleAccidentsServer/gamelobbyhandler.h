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

signals:
    void userReadyListChanged();
    void gameReadyToBegin();
    void allDrawingsRecieved(QMap<QString, QString> newMap);
    void allSecondDrawingsRecieved(QMap<QString, QString> newMap);

private:
    QStringList prompts;
    QString selectedPrompt;
    QList<QString> gameClientList;
    QString lobbyID;
    QMap<QString, bool> clientReadyList;
    QMap<QString, QString> clientDrawingData;
    QMap<QString, QString> clientSecondDrawingData;

};

#endif // GAMELOBBYHANDLER_H
