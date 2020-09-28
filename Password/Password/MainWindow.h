#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QListWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString path;
    QMap<QString, QString> Data;


    void saveData(QString file,QString key,QString value);
    void readSetting(QString file,QString key,QString &value);

    void saveAllData();
    void deletOneData();
    void refresh();

    void connectAll();

    void writeAllData(QString name);

    void getFileNames(const QString &path,QStringList &files);


private:
    Ui::MainWindow *ui;

    void ui_Init();

};
#endif // MAINWINDOW_H
