#ifndef WEBSOCKETHANDLER_H
#define WEBSOCKETHANDLER_H

#include <QObject>
#include <QtWebSockets/qwebsocket.h>
#include "controllers/messageprocesshandler.h"

class WebSocketHandler : public QObject {
    Q_OBJECT
public:
    explicit WebSocketHandler(QObject *parent = nullptr);
    ~WebSocketHandler();
    Q_INVOKABLE void connectToServer(QString hostAddress);
    Q_INVOKABLE void createGameRequest();

signals:

public slots:
    void onConnected();
    void onTextMessageRecieved(QString message);
    void registerID(QString id);


private:
    QWebSocket* webSocket;
    QString clientID;
    MessageProcessHandler* messageProcessor;

};

#endif // WEBSOCKETHANDLER_H
