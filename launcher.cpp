#include "launcher.h"
#include <QThread>
#include <QTimer>
launcher::launcher() {
    // создаем список процессов
    this->appsToBlock = new QStringList();
}

launcher::~launcher() {
    // освобождаем список процессов
    free(this->appsToBlock);
}

void launcher::addApp(QString processName){
    // добавляем новый
    (*appsToBlock) << processName;
}

void launcher::launchBlock(){


    for (auto psName : (*appsToBlock)){
        QThread *thread;
        Worker* worker = new Worker(psName);
        thread = new QThread();
        QTimer *timer = new QTimer;
        worker->moveToThread(thread);
        QObject::connect(thread, &QThread::started, worker, &Worker::runCommand); // Run once on thread start
        QObject::connect(timer, &QTimer::timeout, worker, &Worker::runCommand);   // Run periodically
        //QObject::connect(worker, &Worker::finished, thread, &QThread::quit);
        QObject::connect(thread, &QThread::finished, worker, &Worker::deleteLater);
        QObject::connect(thread, &QThread::finished, thread, &QThread::deleteLater);

        thread->start(); timer->start(10000);
    }
}
