#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include <QSettings>
#include <QFile>
#include <QMessageBox>
#include <QDir>
#include <QStringList>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui_Init();
    connectAll();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ui_Init(){
    path = QCoreApplication::applicationDirPath();
    this->setWindowTitle("账户管理");
    ui->setupUi(this);

    refresh();

    Data["title"]       = "";
    Data["name"]        = "";
    Data["account"]     = "";
    Data["password"]    = "";
    Data["other"]       = "";


}

void MainWindow::connectAll(){

    connect(ui->pushButton_Save,&QPushButton::clicked,[=](){

        if(ui->lineEdit_Title->text()=="")
        {
            QMessageBox::information(NULL, "错误提示", "平台不能为空，这样不能保存的");
        }
        else
        {
            Data["title"]       = ui->lineEdit_Title->text();
            Data["name"]        = ui->lineEdit_Name->text();
            Data["account"]     = ui->lineEdit_Account->text();
            Data["password"]    = ui->lineEdit_Password->text();
            Data["other"]       = ui->textEdit_Other->toPlainText();

            saveAllData();
        }
    });

    connect(ui->pushButton_Del,&QPushButton::clicked,[=](){
        Data["title"]       = ui->lineEdit_Title->text();

        deletOneData();
    });


    connect(ui->listWidget, &QListWidget::clicked, [=](){

        QString name = ui->listWidget->currentItem()->text();
        writeAllData(name);

    });

}


void MainWindow::writeAllData(QString name){
    QString theNewPath= path+ "/Save/" + name + ".ini";
    this->readSetting(name + ".ini","title",Data["title"]);
    this->readSetting(name + ".ini","name",Data["name"]);
    this->readSetting(name + ".ini","account",Data["account"]);
    this->readSetting(name + ".ini","password",Data["password"]);
    this->readSetting(name + ".ini","other",Data["other"]);


    ui->lineEdit_Title->setText(Data["title"]);
    ui->lineEdit_Name->setText(Data["name"]);
    ui->lineEdit_Account->setText(Data["account"]);
    ui->lineEdit_Password->setText(Data["password"]);
    ui->textEdit_Other->setText(Data["other"]);
}


void MainWindow::saveAllData(){

    this->saveData(Data["title"] + ".ini","title",Data["title"]);
    this->saveData(Data["title"] + ".ini","name",Data["name"]);
    this->saveData(Data["title"] + ".ini","account",Data["account"]);
    this->saveData(Data["title"] + ".ini","password",Data["password"]);
    this->saveData(Data["title"] + ".ini","other",Data["other"]);
    refresh();
    QMessageBox::information(NULL, "提示信息", "当前的信息已经保存");


}

void MainWindow::deletOneData(){

    QString theNewPath= path+ "/Save/" + Data["title"] + ".ini";

    QFile file(theNewPath);

    if (file.exists()){

        file.remove();

        ui->lineEdit_Title->setText("");
        ui->lineEdit_Name->setText("");
        ui->lineEdit_Account->setText("");
        ui->lineEdit_Password->setText("");
        ui->textEdit_Other->setText("");
        refresh();

        QMessageBox::information(NULL, "提示信息", "当前的信息已经删除");


    }
    else{
        QMessageBox::information(NULL, "错误提示", "没有找到当前信息，有可能您没有建立。");

    }

}

void MainWindow::refresh(){

    QStringList files;
    getFileNames(path+ "/Save/",files);

    int counter =ui->listWidget->count();

    for(int i=0;i<counter;i++)
    {
        QListWidgetItem *item = ui->listWidget->takeItem(0);
        delete item;
    }

    counter = files.length();

    for(int i=0;i<counter;i++)
    {

        QStringList list = files[i].split(".");
        ui->listWidget->addItem(list[0]);
    }



}

void MainWindow::getFileNames(const QString &path,QStringList &files)
{
    QDir dir(path);
    files = dir.entryList(QDir::NoDotAndDotDot|QDir::Files, QDir::Name);
}


void MainWindow::saveData(QString file,QString key,QString value){
    QSettings * settings = new QSettings(path+ "/Save/" + file, QSettings::IniFormat, this);
    settings->setIniCodec("UTF-8");
    settings->setValue(key, value);
}

void MainWindow::readSetting(QString file,QString key, QString &value){
    QSettings * settings = new QSettings(path+ "/Save/" + file, QSettings::IniFormat, this);
    settings->setIniCodec("UTF-8");
    value = settings->value(key).toString();
}
