#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

struct MainWindowData;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_startPushButton_clicked();
    void on_stopPushButton_clicked();
    void on_clearPushButton_clicked();
    void on_updatePortsPushButton_clicked();
    void onDataReceived(const QByteArray& data);

    void on_sendMsgBtn_clicked();

private:
    Ui::MainWindow *ui;
    MainWindowData* d;
};

#endif // MAINWINDOW_H
