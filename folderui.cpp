#include "folderui.h"
#include <QGridLayout>
#include <QFileDialog>
#include <QDebug>
folderUI::folderUI(QWidget *parent) : QWidget (parent)
{
    QGridLayout *gridLay = new QGridLayout(this);

    gridLay->addWidget(_filter,0,0);
    gridLay->addWidget(_tree_view, 1,0,4,0);
    gridLay->addWidget(_export_button,5,0);

    setLayout(gridLay);
    setAttribute(Qt::WidgetAttribute::WA_DeleteOnClose);
    setWindowTitle("Sample");

    connect(_filter,SIGNAL(textChanged(QString)),this,SLOT(on_filter_hasChanged(QString)));
    connect(_export_button,SIGNAL(clicked(bool)),this,SLOT(exportToFileCSV()));
}

void folderUI::setNameOfWidget(QString arg)
{
    //принудительное изменения названия окна
    setWindowTitle(arg);
    titleWinEx = true;

}

void folderUI::showMeSome()
{
    //первичный вызов окна
    if (_givenPath.isEmpty()==true){
        qDebug()<<"ERORR! PATH NOT SET!";
        return;
    }
    _model->setRootPath(_givenPath);
    _proxy_model->setSourceModel(_model);
    _tree_view->setModel(_proxy_model);
    _tree_view->setRootIndex(_proxy_model->mapFromSource(_model->index(_givenPath)));
    _tree_view->hideColumn(1);
    _tree_view->hideColumn(2);
    _tree_view->hideColumn(3);

    show();
}

void folderUI::on_filter_hasChanged(QString arg)
{
    //обработка изменения фильтра
    _proxy_model->setRecursiveFilteringEnabled(true);
    _proxy_model->setFilterCaseSensitivity(Qt::CaseInsensitive);
    _proxy_model->setFilterWildcard(arg);
    _proxy_model->setFilterKeyColumn(-1);
    _tree_view->setModel(_proxy_model);
    _tree_view->setRootIndex(_proxy_model->mapFromSource(_model->index(_givenPath)));
    _tree_view->hideColumn(1);
    _tree_view->hideColumn(2);
    _tree_view->hideColumn(3);
}

void folderUI::setPathFolder(QString arg)
{
    //установка пути принудительно
    if (arg.isEmpty()==true){
        qDebug()<<"ERORR! PATH NOT SET!";
        return;
    }
    _givenPath = arg;
    if(titleWinEx == false)
    {
        setWindowTitle(arg);
    }
}

void folderUI::exportToFileCSV()
{
    //сохранения файла
    QString exportFileName = QFileDialog::getSaveFileName(this,tr("Export CSV file"), "C:/", tr( "CSV Files: *.csv" ));
    QFile fileCSV(exportFileName);
    QStringList fileName;
    QStringList filePath;
    QDirIterator flushFile(_givenPath, QDir::NoFilter, QDirIterator::Subdirectories);
    while (flushFile.hasNext()) {
        flushFile.next();
        if( flushFile.fileName().contains(QString (_filter->text()), Qt::CaseInsensitive) == true){
            //qDebug()<<"LOL Yeast";
            fileName.append(flushFile.fileName());
            //qDebug()<< flushFile.fileName()<< "Name";
            filePath.append(flushFile.filePath());
           // qDebug()<< flushFile.filePath()<<"Path";}
    }

    fileCSV.open(QIODevice::WriteOnly);
    int countStrings = fileName.count();
    QTextStream pushIn(&fileCSV);
    QString pushString;
    for(int i = 0; i < countStrings; ++i){
        pushString = fileName[i] + ";" + filePath[i] + "\n";
        pushIn<<pushString;
    }
    fileCSV.close();

}
