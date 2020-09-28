#ifndef VIDEOWIGET_H
#define VIDEOWIGET_H

#include <QWidget>
#include <QCoreApplication>
#include <QLabel>
#include <QPushButton>
#include "MLabel.h"
#include <QDir>
#include <QDesktopServices>
#include <QUrl>

class VideoWiget : public QWidget
{
    Q_OBJECT

public:
    VideoWiget(QString name,QString path= QCoreApplication::applicationDirPath(),QWidget *parent = nullptr);
    QString name;
    QString path;
    ~VideoWiget();
private:
    QLabel *nameLabel;
    QPushButton *backButton;

    void ui_First();
    void ui_Second();
    void getDirNames(QStringList &files);
    void getFileNames(QString newpath,QStringList &files);

    void connectAll();
signals:
    void closeTheVideo();

};
#endif // VIDEOWIGET_H
