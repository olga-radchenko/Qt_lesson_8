#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDate>
#include <QFile>
#include <memory>
#include <QDebug>
#include <QTabBar>
#include <QPainter>
#include <iostream>
#include <QMainWindow>
#include <QMessageBox>
#include <QTranslator>
#include <QFileDialog>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>

#include "myqplaintextedit.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
   ~MainWindow();

private:
    QDir m_dir;
    Ui::MainWindow *ui{nullptr};
    std::shared_ptr<QTabWidget> m_tabWidget{nullptr};
    QTranslator* m_translator{nullptr};

    void makeTabWidget();

private Q_SLOTS:
    void closeTab(int index);
    void on_save_act_triggered();
    void on_print_act_triggered();
    void on_new_act_triggered();
    void on_exit_act_triggered();
    void on_light_act_triggered();
    void on_dark_act_triggered();
    void on_en_act_triggered();
    void on_ru_act_triggered();
    void on_ref_act_triggered();
    void on_open_act_triggered();
};
#endif // MAINWINDOW_H
