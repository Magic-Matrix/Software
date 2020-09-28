#include "AcctressWiget.h"
#include "VideoWiget.h"

void readSetting(QString path,QString key, QString &value){
    QSettings * settings = new QSettings(QCoreApplication::applicationDirPath()+ "/Save/" + path, QSettings::IniFormat);
    settings->setIniCodec("UTF-8");
    value = settings->value(key).toString();
}




AcctressWiget::AcctressWiget(QWidget *parent) : QWidget(parent)
{
    this->resize(1400,900);     //整个窗口大小为(1400,900)
    this->setWindowTitle("播放管理");

    readSetting("Path.ini","path",path);
    makePictures();

}

AcctressWiget::~AcctressWiget()
{
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


#define X_VIDEO_SHOW    35
#define Y_VIDEO_SHOW    40



void AcctressWiget::makePictures(){
    QStringList files;
    this->getDirNames(files);
    int number = files.length();



    for (int i = 0;i<number;i++){

        MLabel * label = new MLabel(this);
        label->move(i%8*170+X_VIDEO_SHOW, i/8*270+Y_VIDEO_SHOW);      //移动
        label->setPicture(this->path + "\\" + files[i] + "\\pic.jpg");

        QString newPath = path+"\\"+files[i]+"\\pic.jpg";   //制作新的地址

        QPixmap pix;
        QImage image(newPath);                      //加入图片
        label->setPixmap(pix.fromImage(image));     //label上加入图片
        label->setScaledContents(true);             //图片自适应

        QLabel * name = new QLabel(this);
        name->setStyleSheet("font-size:20px;font-weight:bold ");
        name->resize(140,30);                           //大小
        name->move(i%8*170+X_VIDEO_SHOW, i/8*270+210+Y_VIDEO_SHOW);
        name->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);  //整体居中
        name->setText(files[i]);

        label->setToolTip(files[i]);
        label->setStyleSheet("QToolTip{background-color:white}");

        connect(label,&MLabel::clicked,[=](){

            v =new VideoWiget(files[i],this->path + "\\" + files[i]);
            v->show();


        });

    };

}

void AcctressWiget::getDirNames(QStringList &files)
{
    QDir dir(path);
    files = dir.entryList(QDir::NoDotAndDotDot|QDir::AllDirs, QDir::Name);
}
