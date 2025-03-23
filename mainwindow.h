#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QAction>
#include "launcher.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QMenu *trayMenu = nullptr;
    QSystemTrayIcon* trayIcon = nullptr;
    QAction* restoreAction = nullptr;
    QAction*  quitAction = nullptr;
    launcher* l = nullptr;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void openFile();
private slots:
    void on_pushButton_clicked();

    void on_qpbOpenFile_clicked();

protected:
    void closeEvent(QCloseEvent *event) override;
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
