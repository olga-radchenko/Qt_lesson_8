#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include "mainwindow.h"
#include "file_viewer.h"

#include <QMainWindow>

namespace Ui {
class MyMainWindow;
}

class MyMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyMainWindow(QWidget *parent = nullptr);
            ~MyMainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    MainWindow* textEdit{nullptr};
    FileViewer* fileViewer{nullptr};
    Ui::MyMainWindow *ui;
};

#endif // MYMAINWINDOW_H
