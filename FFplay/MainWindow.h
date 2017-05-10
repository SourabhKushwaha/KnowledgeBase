#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = NULL);
    ~MainWindow();

     virtual void closeEvent ( QCloseEvent * event );

public slots:
    void updateImgHandler(QImage img);

private:
    QLabel *qWid;
};

#endif // MAINWINDOW_H
