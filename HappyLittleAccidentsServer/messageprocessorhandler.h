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

};

#endif // MESSAGEPROCESSORHANDLER_H
