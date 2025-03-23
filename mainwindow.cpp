#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "launcher.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->l = new launcher();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    QString text = this->ui->qteBlockedAppsProcessNames->toPlainText();
    QStringList lines = text.split('\n');
    for (const QString &line : lines) {
        (*l).addApp(line);
    }
    (*l).launchBlock();
}

