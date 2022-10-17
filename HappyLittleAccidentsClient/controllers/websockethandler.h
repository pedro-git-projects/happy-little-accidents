#ifndef WEBSOCKETHANDLER_H
#define WEBSOCKETHANDLER_H

#include <QObject>
#include <QtWebSockets/qwebsocket.h>

class WebSocketHandler : public QObject {
    Q_OBJECT
public:
    explicit WebSocketHandler(QObject *parent = nullptr);
    ~WebSocketHandler();
    Q_INVOKABLE void connectToServer(QString hostAddress);

signals:
    void newMessageReadyForProcessing(QString message);

public slots:
    void onConnected();
    void onTextMessageRecieved(QString message);
    void sendMessageToSever(QString message);

private:
    QWebSocket* webSocket;
};

#endif // WEBSOCKETHANDLER_H
