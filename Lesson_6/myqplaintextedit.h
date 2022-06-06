#ifndef MYQPLAINTEXTEDIT_H
#define MYQPLAINTEXTEDIT_H

#include <QMenu>
#include <QFont>
#include <QList>
#include <QColor>
#include <QDebug>
#include <QBrush>
#include <QObject>
#include <QWidget>
#include <QAction>
#include <QTextEdit>
#include <QDateTime>
#include <QTextCursor>
#include <QFontDialog>
#include <QColorDialog>
#include <QTextCharFormat>
#include <QTextBlockFormat>

class MyQPlainTextEdit : public QTextEdit
{
    Q_OBJECT

public:
    explicit MyQPlainTextEdit(QWidget *parent = nullptr) : QTextEdit(parent) {};
    explicit MyQPlainTextEdit(const QString &text, QWidget *parent = nullptr) : QTextEdit(text, parent) {};
            ~MyQPlainTextEdit();

private:
    QMenu   *menu{nullptr};
    QAction *getFormat_act{nullptr};
    QAction *setFormat_act{nullptr};
    QAction *choseColor_act{nullptr};
    QAction *choseFormat_act{nullptr};
    QAction *alignCenter_act{nullptr};
    QAction *alignLeft_act{nullptr};
    QAction *alignRight_act{nullptr};
    QAction *pasteDateTime_act{nullptr};
    QTextCharFormat savedFormat;

    void contextMenuEvent(QContextMenuEvent *event) override;
    void translateStandardContextMenuActions();
    void connectCustomizedActions();
    void disconnectCustomizedActions();

private Q_SLOTS:
    void getFormat();
    void setFormat();
    void choseColor();
    void choseFormat();
    void setAlignLeft();
    void pasteDateTime();
    void setAlignRight();
    void setAlignCenter();
};

#endif // MYQPLAINTEXTEDIT_H
