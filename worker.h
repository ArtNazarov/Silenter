#ifndef WORKER_H
#define WORKER_H

#include <QObject>

class Worker : public QObject
{
    Q_OBJECT
public:
    QString argument = "";
    Worker(QString anArgument);
public slots:
    void runCommand();
signals:
};

#endif // WORKER_H
