#include "mymainwindow.h"
#include "ui_mymainwindow.h"

MyMainWindow::MyMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyMainWindow)
{
    ui->setupUi(this);
}

MyMainWindow::~MyMainWindow()
{
    delete ui;
}

void MyMainWindow::on_pushButton_clicked()
{
     if(textEdit == nullptr)
         textEdit = new MainWindow(this);
     textEdit->show();
}

void MyMainWindow::on_pushButton_2_clicked()
{
    if(fileViewer == nullptr)
        fileViewer = new FileViewer(this);

    resize(fileViewer->size());
    fileViewer->show();
}
