#ifndef LAUNCHER_H
#define LAUNCHER_H
#include <worker.h>
#include <QString>
#include <QStringList>
// класс хранит список блокируемых процессов
class launcher
{
public:
    QStringList* appsToBlock;
    launcher();
    ~launcher();
    void addApp(QString processName);
    void launchBlock();
};

#endif // LAUNCHER_H
