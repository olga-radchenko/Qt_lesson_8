#ifndef FINDFILETHREAD_H
#define FINDFILETHREAD_H

#include <QDir>
#include <QDialog>
#include <QObject>

class FindFileThread : public QObject
{
    Q_OBJECT

public:
    explicit FindFileThread(QObject *parent = nullptr);
    QDialog *dlg{nullptr};

public slots:
    void findFile(QString path, QString name);

signals:
    void filesFound(QStringList fileList);
};

#endif // FINDFILETHREAD_H
