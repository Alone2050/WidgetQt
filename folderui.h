#ifndef FOLDERUI_H
#define FOLDERUI_H

#include <QWidget>
#include <QFileSystemModel>
#include <QSortFilterProxyModel>
#include <QTreeView>
#include <QPushButton>
#include <QLineEdit>

class folderUI : public QWidget
{
    Q_OBJECT

public:
    explicit folderUI(QWidget * parent = 0);
private:

    QString _givenPath;

    QFileSystemModel *_model = new QFileSystemModel;

    QSortFilterProxyModel *_proxy_model = new QSortFilterProxyModel;

    QString _proxyString;

    bool titleWinEx = false;

public:

    QTreeView *_tree_view = new QTreeView;

    QPushButton *_export_button = new QPushButton ("Export to CSV");

    QLineEdit *_filter = new QLineEdit;

    QString nameWindow;

    void setNameOfWidget (QString arg);

    void setGivenPath(QString _givenPath);

    void showMeSome();

    void setPathFolder(QString arg);

public slots:

    void on_filter_hasChanged(QString);

    void exportToFileCSV();

};

#endif // FOLDERUI_H
