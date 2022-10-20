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

signals:
    void userReadyListChanged();

private:
    QList<QString> gameClientList;
    QString lobbyID;
    QMap <QString, bool> clientReadyList;

};

#endif // GAMELOBBYHANDLER_H
