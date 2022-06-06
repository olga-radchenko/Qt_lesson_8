#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    m_dir.cdUp();
    m_dir.cd("Lesson_6");

    m_translator = new QTranslator();

    if (!m_translator->load("Lesson_6_en_US",m_dir.path()))
    {
        qWarning() << "Can't load translation file!";
    }

    QFile file{m_dir.path()+"\\light_theme.qss"};
    file.open(QIODevice::ReadOnly);
    const QString cssStyle{file.readAll()};
    qApp->setStyleSheet(cssStyle);

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_open_act_triggered()
{
    QStringList listOfFiles;
    QFileDialog openFileDialog(this);
    openFileDialog.setFileMode(QFileDialog::ExistingFiles);

    if (openFileDialog.exec())
    {
        listOfFiles = openFileDialog.selectedFiles();

        if (!m_tabWidget)
        {
            makeTabWidget();
        }

        foreach (auto file, listOfFiles)
        {
            QFile f{file};

            if (!f.open(QIODevice::ReadWrite | QIODevice::Text))
                return;

            auto index = m_tabWidget->addTab(new MyQPlainTextEdit(QString::fromUtf8(f.readAll())), QFileInfo{f}.fileName());
            m_tabWidget->setCurrentIndex(index);
        }

        m_tabWidget->show();
    }
}

void MainWindow::makeTabWidget()
{
    m_tabWidget = std::shared_ptr<QTabWidget>(new QTabWidget(ui->centralwidget));
    m_tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
    m_tabWidget->setGeometry(QRect(14, 9, 771, 531));
    m_tabWidget->setTabsClosable(true);
    m_tabWidget->setMovable(true);

    connect(m_tabWidget.get(), SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
    connect(m_tabWidget.get()->tabBar(), SIGNAL(tabBarDoubleClicked(int)), this, SLOT(on_new_act_triggered()));
}

void MainWindow::closeTab(int index)
{
    m_tabWidget->removeTab(index);
}

void MainWindow::on_save_act_triggered()
{
    QString fileName{QFileDialog::getSaveFileName(this, tr("Сохранить"))};

    QFile file{fileName};

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    MyQPlainTextEdit *txtWdgtCh = qobject_cast<MyQPlainTextEdit*>(m_tabWidget->currentWidget());

    file.write(txtWdgtCh->toPlainText().toLocal8Bit());
    file.close();
}

void MainWindow::on_print_act_triggered()
{
    QPrinter printer;
    QPrintDialog dlg(&printer, this);
    dlg.setWindowTitle(tr("Печать"));

    if (dlg.exec() != QDialog::Accepted)
        return;

    auto txtWdgtCh = qobject_cast<MyQPlainTextEdit*>(m_tabWidget->currentWidget());
    txtWdgtCh->print(&printer);
}

void MainWindow::on_new_act_triggered()
{
    QString newFileName{tr("Новый файл ")};

    if (!m_tabWidget)
    {
        makeTabWidget();
    }

    if (m_tabWidget->count() > 0)
    {
        newFileName += QString::number(m_tabWidget->count());
    }

    m_tabWidget->setCurrentIndex(m_tabWidget->addTab(new MyQPlainTextEdit(), newFileName));
    m_tabWidget->show();
}

void MainWindow::on_exit_act_triggered()
{
    delete this;
}

void MainWindow::on_light_act_triggered()
{
    QFile file{m_dir.path()+"\\light_theme.qss"};
    if (file.open(QIODevice::ReadOnly))
    {
        const QString cssStyle{file.readAll()};
        qApp->setStyleSheet(cssStyle);

        ui->light_act->setChecked(true);
        ui->dark_act->setChecked(false);
    }
    else
        qWarning() << "Can't load theme file!";
}

void MainWindow::on_dark_act_triggered()
{
    QFile file{m_dir.path()+"\\dark_theme.qss"};
    if (file.open(QIODevice::ReadOnly))
    {
        const QString cssStyle{file.readAll()};
        qApp->setStyleSheet(cssStyle);

        ui->light_act->setChecked(false);
        ui->dark_act->setChecked(true);
    }
    else
        qWarning() << "Can't load theme file!";
}

void MainWindow::on_en_act_triggered()
{
    qApp->installTranslator(m_translator);
    this->ui->retranslateUi(this);
    ui->en_act->setChecked(true);
    ui->ru_act->setChecked(false);
}

void MainWindow::on_ru_act_triggered()
{
    qApp->removeTranslator(m_translator);
    this->ui->retranslateUi(this);
    ui->en_act->setChecked(false);
    ui->ru_act->setChecked(true);
}

void MainWindow::on_ref_act_triggered()
{
    QFile file{m_dir.path()+"\\help.txt"};
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QString txt{file.readAll()};

    QMessageBox message(QMessageBox::Icon::Information, tr("Справка"), txt, QMessageBox::Ok);

    if (QMessageBox::Ok == message.exec())
    {
        file.close();
    }
}
