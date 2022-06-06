#ifndef FILE_VIEWER_H
#define FILE_VIEWER_H

#include <QUrl>
#include <QDebug>
#include <QWidget>
#include <QThread>
#include <QStringList>
#include <QTableWidget>
#include <QFileSystemModel>
#include <QDesktopServices>
#include <QTableWidgetItem>

#include "ui_file_viewer.h"
#include "find_file_thread.h"

namespace Ui {
class FileViewer;
}

class FileViewer : public QWidget
{
    Q_OBJECT

public:
    explicit FileViewer(QWidget *parent = nullptr);
            ~FileViewer();

    void switchLanguage();

private:
    Ui::FileViewer *ui;
    QThread findFileThread;
    FindFileThread* fft{nullptr};
    QFileSystemModel* fsModel{nullptr};

    void showFolder();
    void showLoupePic();
    void customizeTableWidget();

private slots:
    void onTreeViewClicked(const QModelIndex &index);
    void onTreeViewDoubleClicked(const QModelIndex &index);
    void on_openBtn_clicked();
    void on_dirLineEdit_editingFinished();
    void on_upBtn_clicked();
    void on_backBtn_clicked();
    void getDirAddr();
    void showFiles(QStringList files);
    void openFileOfItem(int row, int col);

signals:
    void findFile(QString path, QString name);
};

#endif // FILE_VIEWER_H
