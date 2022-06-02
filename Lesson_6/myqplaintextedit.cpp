#include "myqplaintextedit.h"

MyQPlainTextEdit::~MyQPlainTextEdit()
{
    delete this;
}

void MyQPlainTextEdit::translateStandardContextMenuActions()
{
    QList<QAction*> listOfActions = menu->actions();

    foreach (QAction *action, listOfActions)
    {
       QString actionText = action->text();

       if (actionText.contains("Undo"))
       {
           actionText.replace("Undo", tr("Отменить"));
           action->setText(actionText);
       }
       else if (actionText.contains("Redo"))
       {
           actionText.replace("Redo", tr("Вернуть"));
           action->setText(actionText);
       }
       else if (actionText.contains("Cu&t"))
       {
           actionText.replace("Cu&t", tr("Вырезать"));
           action->setText(actionText);
       }
       else if (actionText.contains("Copy"))
       {
           actionText.replace("Copy", tr("Копировать"));
           action->setText(actionText);
       }
       else if (actionText.contains("Paste"))
       {
           actionText.replace("Paste", tr("Вставить"));
           action->setText(actionText);
       }
       else if (actionText.contains("Delete"))
       {
           actionText.replace("Delete", tr("Удалить"));
           action->setText(actionText);
       }
       else if (actionText.contains("Select All"))
       {
           actionText.replace("Select All", tr("Выделить все"));
           action->setText(actionText);
       }
    }
}

void MyQPlainTextEdit::connectCustomizedActions()
{
    connect(choseColor_act,  SIGNAL(triggered()), this, SLOT(choseColor()));
    connect(getFormat_act,   SIGNAL(triggered()), this, SLOT(getFormat()));
    connect(setFormat_act,   SIGNAL(triggered()), this, SLOT(setFormat()));
    connect(choseFormat_act, SIGNAL(triggered()), this, SLOT(choseFormat()));
    connect(pasteDateTime_act, SIGNAL(triggered()), this, SLOT(pasteDateTime()));

    connect(alignCenter_act, SIGNAL(triggered()), this, SLOT(setAlignCenter()));
    connect(alignLeft_act,   SIGNAL(triggered()), this, SLOT(setAlignLeft()));
    connect(alignRight_act,  SIGNAL(triggered()), this, SLOT(setAlignRight()));
}

void MyQPlainTextEdit::disconnectCustomizedActions()
{
    disconnect(choseColor_act,  SIGNAL(triggered()), this, SLOT(choseColor()));
    disconnect(getFormat_act,   SIGNAL(triggered()), this, SLOT(getFormat()));
    disconnect(setFormat_act,   SIGNAL(triggered()), this, SLOT(setFormat()));
    disconnect(choseFormat_act, SIGNAL(triggered()), this, SLOT(choseFormat()));
    disconnect(pasteDateTime_act, SIGNAL(triggered()), this, SLOT(pasteDateTime()));

    disconnect(alignCenter_act, SIGNAL(triggered()), this, SLOT(setAlignCenter()));
    disconnect(alignLeft_act,   SIGNAL(triggered()), this, SLOT(setAlignLeft()));
    disconnect(alignRight_act,  SIGNAL(triggered()), this, SLOT(setAlignRight()));
}


void MyQPlainTextEdit::contextMenuEvent(QContextMenuEvent *event)
{
    Q_UNUSED(event);

    menu = createStandardContextMenu();
    QMenu* submenu = menu->addMenu(tr("Выровнять"));

    translateStandardContextMenuActions();

    getFormat_act   = new QAction(tr("Копировать формат"));
    setFormat_act   = new QAction(tr("Применить формат"));
    choseColor_act  = new QAction(tr("Цвет..."));
    choseFormat_act = new QAction(tr("Формат..."));
    alignCenter_act = new QAction(tr("по центру"));
    alignRight_act  = new QAction(tr("по правому краю"));
    alignLeft_act   = new QAction(tr("по левому краю"));
    pasteDateTime_act = new QAction(tr("Вставить дату и время"));

    menu->addAction(getFormat_act);
    menu->addAction(setFormat_act);
    menu->addAction(choseColor_act);
    menu->addAction(choseFormat_act);
    menu->addAction(pasteDateTime_act);

    submenu->addAction(alignCenter_act);
    submenu->addAction(alignLeft_act);
    submenu->addAction(alignRight_act);

    QTextCursor cursor = textCursor();

    if (cursor.selectedText().isEmpty())
    {
        getFormat_act->setEnabled(false);
        setFormat_act->setEnabled(false);
        choseFormat_act->setEnabled(false);
        choseColor_act->setEnabled(false);
        submenu->setEnabled(false);
    }

    connectCustomizedActions();

    menu->exec(QCursor::pos());

    disconnectCustomizedActions();

    delete menu;
}

void MyQPlainTextEdit::pasteDateTime()
{
    QDateTime dateTime = QDateTime::currentDateTime();
    QString format = "MM/dd/yyyy  HH:mm";
    QTextCursor cursor(textCursor());
    cursor.insertText(dateTime.toString(format));
}

void MyQPlainTextEdit::setAlignCenter()
{
    QTextCursor cursor = textCursor();
    QTextBlockFormat textBlockFormat = cursor.blockFormat();
    textBlockFormat.setAlignment(Qt::AlignCenter);
    cursor.mergeBlockFormat(textBlockFormat);
    setTextCursor(cursor);
}

void MyQPlainTextEdit::setAlignLeft()
{
    QTextCursor cursor = textCursor();
    QTextBlockFormat textBlockFormat = cursor.blockFormat();
    textBlockFormat.setAlignment(Qt::AlignLeft);
    cursor.mergeBlockFormat(textBlockFormat);
    setTextCursor(cursor);
}

void MyQPlainTextEdit::setAlignRight()
{
    QTextCursor cursor = textCursor();
    QTextBlockFormat textBlockFormat = cursor.blockFormat();
    textBlockFormat.setAlignment(Qt::AlignRight);
    cursor.mergeBlockFormat(textBlockFormat);
    setTextCursor(cursor);
}

void MyQPlainTextEdit::choseColor()
{
    QColor color = QColorDialog::getColor();
    if (!color.isValid())
    {
        return;
    }

    QFont font = textCursor().charFormat().font();
    QTextCharFormat charFormat = textCursor().charFormat();
    charFormat.setForeground(QBrush{color});
    charFormat.setFont(font);
    textCursor().setCharFormat(charFormat);
}

void MyQPlainTextEdit::choseFormat()
{
    QFont font = textCursor().charFormat().font();
    QFontDialog fdlg(font, this);

    bool isOk(false);
    auto newFont{fdlg.getFont(&isOk)};

    if (isOk)
    {
        auto charFormat{textCursor().charFormat()};
        charFormat.setFont(newFont);
        textCursor().setCharFormat(charFormat);
    }
}

void MyQPlainTextEdit::getFormat()
{
    savedFormat = textCursor().charFormat();
}

void MyQPlainTextEdit::setFormat()
{
    textCursor().setCharFormat(savedFormat);
}

