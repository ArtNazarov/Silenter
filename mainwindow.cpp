#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "launcher.h"

#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QCloseEvent>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

        // Create the tray icon
    trayIcon = new QSystemTrayIcon(this);
    (*trayIcon).setIcon(QIcon(":/icons/app_icon.png"));
    (*trayIcon).setToolTip("My Application");

    // Create the tray menu
    trayMenu = new QMenu(this);
    restoreAction = new QAction("Restore", this);
    quitAction = new QAction("Quit", this);
    trayMenu->addAction(restoreAction);
    trayMenu->addAction(quitAction);
    trayIcon->setContextMenu(trayMenu);

    // Connect signals
    connect(trayIcon, &QSystemTrayIcon::activated, this, [this](QSystemTrayIcon::ActivationReason reason) {
        if (reason == QSystemTrayIcon::Trigger) {
            this->show();
        }
    });
    connect(restoreAction, &QAction::triggered, this, [this]() {
        this->show();
        this->setWindowState(Qt::WindowActive);
    });
    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);

    // Show the tray icon
    trayIcon->show();


    ui->setupUi(this);
    this->l = new launcher();
}

MainWindow::~MainWindow()
{
    free(l);
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

void MainWindow::closeEvent(QCloseEvent *event)   {
    if (trayIcon->isVisible()) {
        hide();
        event->ignore();
    } else {
        event->accept();
    }
}

void MainWindow::openFile() {
    // Open a file dialog to select a .txt file
    QString fileName = QFileDialog::getOpenFileName(this, "Open Text File", "", "Text Files (*.txt)");

    if (!fileName.isEmpty()) {
        QFile file(fileName);

        // Open the file in read-only mode
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);

            // Read the entire content of the file
            QString content = in.readAll();

            // Set the content to the QTextEdit
            this->ui->qteBlockedAppsProcessNames->setText(content);

            // Close the file
            file.close();
        } else {
            // Handle the error if the file couldn't be opened
            // textEdit->setText("Could not open the file.");
        }
    }
}


void MainWindow::on_qpbOpenFile_clicked()
{
    this->openFile();
}

