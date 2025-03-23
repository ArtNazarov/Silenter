#include <QObject>
#include "worker.h"
#include <QProcess>

Worker::Worker(QString anArgument){
    this->argument = anArgument;
}

void Worker::runCommand() {
        // Create a QProcess instance
        QProcess process;

        // Set the command and arguments
        QString program = "pkill";
        QStringList arguments;
        arguments << argument;

        // Start the process
        process.start(program, arguments);

        // Wait for the process to finish
        if (!process.waitForFinished()) {
            qWarning("Failed to execute command: %s", qPrintable(process.errorString()));
        } else {
            qDebug("Command executed successfully.");
        }
    }
