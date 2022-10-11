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

public slots:
    void onConnected();
    void onTextMessageRecieved(QString message);


private:
    QWebSocket* webSocket;

};

#endif // WEBSOCKETHANDLER_H
