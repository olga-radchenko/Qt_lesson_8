#include "file_viewer.h"

FileViewer::FileViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileViewer)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnWidth(0,469);

    fft = new FindFileThread;
    fft->moveToThread(&findFileThread);

    fsModel = new QFileSystemModel(this);
    fsModel->setRootPath(QDir::homePath());
    ui->dirLineEdit->setText(QDir::homePath());
    ui->treeView->setModel(fsModel);
    ui->treeView->setRootIndex(fsModel->index(QDir::homePath()));
    ui->treeView->setCurrentIndex(fsModel->index(QDir::homePath()));
    ui->treeView->setObjectName(QString::fromUtf8("treeView"));
    ui->treeView->setGeometry(QRect(20, 40, 571, 251));
    ui->treeView->show();

    showLoupePic();

    connect(ui->findLineEdit, SIGNAL(returnPressed()), this, SLOT(getDirAddr()));   // enter после ввода текста в окно поиска
    connect(this, &FileViewer::findFile, fft, &FindFileThread::findFile);           // передача директории для поиска между двумя обьектами
    connect(fft, &FindFileThread::filesFound, this, &FileViewer::showFiles);        // возврат результата поиска из треда
    connect(ui->treeView,SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onTreeViewDoubleClicked(QModelIndex)));
    connect(ui->treeView,SIGNAL(clicked(QModelIndex)), this, SLOT(onTreeViewClicked(QModelIndex)));

    findFileThread.start();
}

FileViewer::~FileViewer()
{
    findFileThread.quit();
    findFileThread.wait();
    delete ui;
}

void FileViewer::showLoupePic()
{
    QDir currDir{QDir::currentPath()};
    currDir.cd("../Lesson_6");
    QPixmap pm(currDir.path()+"/find.png");
    ui->label->setPixmap(pm);
    ui->label->setScaledContents(true);
}

void FileViewer::showFiles(QStringList files)
{
    ui->tableWidget->clear();
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    disconnect(ui->tableWidget, SIGNAL(cellActivated(int,int)), this, SLOT(openFileOfItem(int,int)));

    ui->label_2->setText(QString::number(files.size())+tr(" файлов найдено"));
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    QDir dir = QDir(ui->dirLineEdit->text());

    for (int i = 0; i < files.size(); ++i)
    {
        QFile file(dir.absoluteFilePath(files[i]));
        qint64 size = QFileInfo(file).size();
        QTableWidgetItem *fileNameItem = new QTableWidgetItem(files[i]);

        fileNameItem->setFlags(fileNameItem->flags() ^ Qt::ItemIsEditable);
        QTableWidgetItem *sizeItem = new QTableWidgetItem(tr("%1 КБ").arg(int((size + 1023) / 1024)));

        sizeItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        sizeItem->setFlags(sizeItem->flags() ^ Qt::ItemIsEditable);

        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row, 0, fileNameItem);
        ui->tableWidget->setItem(row, 1, sizeItem);
    }

    QStringList labels;
    labels << tr("Имя файла") << tr("Размер");
    ui->tableWidget->setHorizontalHeaderLabels(labels);
    connect(ui->tableWidget, SIGNAL(cellActivated(int,int)),this,SLOT(openFileOfItem(int,int)));
}

void FileViewer::openFileOfItem(int row, int col)
{
    Q_UNUSED(col);

    QTableWidgetItem *item =  ui->tableWidget->item(row, 0);
    QDir dir = QDir(ui->dirLineEdit->text());
    QDesktopServices::openUrl(QUrl::fromLocalFile(dir.absoluteFilePath(item->text())));
}

void FileViewer::onTreeViewClicked(const QModelIndex &index)
{
    ui->dirLineEdit->setText(fsModel->filePath(index));
}

void FileViewer::onTreeViewDoubleClicked(const QModelIndex &index)
{
    if(!fsModel->filePath(index).contains(".")) showFolder();
    else QDesktopServices::openUrl(QUrl::fromLocalFile(ui->dirLineEdit->text()));
}

void FileViewer::showFolder()
{
    fsModel->setRootPath(ui->dirLineEdit->text());
    ui->treeView->setRootIndex(fsModel->index(ui->dirLineEdit->text()));
    ui->treeView->setModel(fsModel);
}

void FileViewer::on_openBtn_clicked()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(ui->dirLineEdit->text()));
}

void FileViewer::on_dirLineEdit_editingFinished()
{
    showFolder();
}

void FileViewer::on_upBtn_clicked()
{
    QDir currDir{ui->dirLineEdit->text()};
    currDir.cdUp();
    ui->dirLineEdit->setText(currDir.path());
    fsModel->setRootPath(ui->dirLineEdit->text());
    ui->treeView->setRootIndex(fsModel->index(ui->dirLineEdit->text()));
    ui->treeView->setModel(fsModel);
}

void FileViewer::on_backBtn_clicked()
{
    this->close();
}

void FileViewer::switchLanguage()
{
    this->ui->retranslateUi(this);
}

void FileViewer::getDirAddr()
{
    QString path = ui->dirLineEdit->text();
    QString name = ui->findLineEdit->text();
    emit findFile(path, name);
}
