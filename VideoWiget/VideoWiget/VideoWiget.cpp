#include "VideoWiget.h"
#include <QDebug>

VideoWiget::VideoWiget(QString name,QString path,QWidget *parent)
    :QWidget(parent)
{
    this->name = name;
    this->path = path;

    this->setWindowTitle(name);

    this->ui_First();
    this->ui_Second();


    this->connectAll();

}


void VideoWiget::ui_First(){

    this->resize(1400,900);     //整个窗口大小为(1400,900)

    this->nameLabel = new QLabel(name,this);     //定义一个文本框

    this->nameLabel->move(600,20);    //位置(600,50)
    this->nameLabel->resize(200,30);  //大小(200,30)
    this->nameLabel->setStyleSheet("color:red;font-size:30px;font-weight:bold ");   //文字样式


    this->backButton =new QPushButton("返回",this);    //定义一个按钮用来返回
    this->backButton->move(800,20);    //位置(800,50)



}

#define X_VIDEO_SHOW    35
#define Y_VIDEO_SHOW    80

void VideoWiget::ui_Second(){
    QStringList files;
    this->getDirNames(files);
    int number = files.length();


    for (int i = 0;i<number;i++){

        MLabel * label = new MLabel(this);
        label->move(i%8*170+X_VIDEO_SHOW, i/8*270+Y_VIDEO_SHOW);      //移动
        label->setPicture(this->path + "\\" + files[i] + "\\pic.jpg");


        QLabel * name = new QLabel(this);
        name->setStyleSheet("font-size:20px;font-weight:bold ");
        name->resize(140,30);                           //大小
        name->move(i%8*170+X_VIDEO_SHOW, i/8*270+210+Y_VIDEO_SHOW);
        name->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);  //整体居中
        name->setText(files[i]);

        QString newPath = this->path + "\\" + files[i];
        QStringList files;

        getFileNames(newPath, files);

        if(files.length()){

            label->setToolTip(files[0]);
            label->setStyleSheet("QToolTip{background-color:white}");

        }
        connect(label,&MLabel::clicked,[=](){


            if(files.length()){

                QString newnewPath = newPath + "\\" + files[0];
                QUrl url("file:///" +newnewPath);

                QDesktopServices::openUrl(url);

            }
        });

    };

}
void VideoWiget::connectAll(){
    connect(backButton,&QPushButton::clicked,this,&QWidget::close);//按下按钮后就关闭
}


VideoWiget::~VideoWiget()
{


    delete this->nameLabel;
    delete this->backButton;

    QList<MLabel*> lab1 = this->findChildren<MLabel*>();
    foreach(MLabel* lab, lab1)
    {
        delete lab;
    }
    QList<QLabel*> lab2 = this->findChildren<QLabel*>();

    foreach(QLabel* lab, lab2)
    {
        delete lab;
    }

}

void VideoWiget::getDirNames(QStringList &files)
{
    QDir dir(path);
    files = dir.entryList(QDir::NoDotAndDotDot|QDir::AllDirs, QDir::Name);
}

void VideoWiget::getFileNames(QString newpath,QStringList &files)
{
    QDir dir(newpath);
    QStringList nameFilters;
    nameFilters << "*.mp4"<< "*.wmv"<< "*.rmvb"<< "*.avi"<< "*.flv";
    files = dir.entryList(nameFilters,QDir::NoDotAndDotDot|QDir::Files, QDir::Name);
}
