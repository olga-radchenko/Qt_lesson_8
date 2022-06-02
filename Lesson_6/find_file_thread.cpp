#include "find_file_thread.h"

FindFileThread::FindFileThread(QObject *parent) : QObject(parent)
{

}

void FindFileThread::findFile(QString path, QString name)
{
    dlg = new QDialog();
    QDir currentDir = QDir(path);
    QStringList files;

    if (name.isEmpty())
             name = "*";

    files = currentDir.entryList(QStringList(name),
                                 QDir::Files | QDir::NoSymLinks);

    emit filesFound(files);
}
