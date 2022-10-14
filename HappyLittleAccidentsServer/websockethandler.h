#ifndef WEBSOCKETHANDLER_H
#define WEBSOCKETHANDLER_H

#include <QObject>
#include <QMap>
#include <QtWebSockets/QWebSocketServer>
#include <QtWebSockets/QWebSocket>

class WebSocketHandler : public QObject {
    Q_OBJECT
public:
    explicit WebSocketHandler(QObject *parent = nullptr);
    ~WebSocketHandler();
    void sendTextMessageToClient(QString message, QString clientID);

signals:
    void newMesssageToProcess(QString message);

public slots:
    void onNewSocketConnection();
    void onTextMessageRecieved(QString);
    void onSocketDisconnected();

private:
    QWebSocketServer* socketServer;
    QMap<QString, QWebSocket*> clientList;

};

#endif // WEBSOCKETHANDLER_H
