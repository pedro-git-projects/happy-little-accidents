#ifndef GAMELOBBYHANDLER_H
#define GAMELOBBYHANDLER_H

#include <QObject>

class GameLobbyHandler : public QObject {
    Q_OBJECT
public:
    explicit GameLobbyHandler(QString lobbyID, QObject *parent = nullptr);
    void addClient(QString clientID);

signals:

private:
    QList<QString> gameClientList;
    QString lobbyID;

};

#endif // GAMELOBBYHANDLER_H
