#ifndef ACCTRESSWIGET_H
#define ACCTRESSWIGET_H

#include <QWidget>
#include <QSettings>
#include <QCoreApplication>
#include <QDebug>
#include <MLabel.h>
#include <QDir>
#include "VideoWiget.h"

class AcctressWiget : public QWidget
{
    Q_OBJECT
public:
    explicit AcctressWiget(QWidget *parent = nullptr);
    ~AcctressWiget();


    QString path;
    void makePictures();
    void getDirNames(QStringList &files);
    VideoWiget *v;


signals:

};

#endif // ACCTRESSWIGET_H
