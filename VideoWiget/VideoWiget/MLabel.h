#ifndef MLABEL_H
#define MLABEL_H

#include <QLabel>

class MLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MLabel(QWidget *parent = nullptr);
    virtual void mouseReleaseEvent(QMouseEvent * ev);

    void setPicture(QString path);

signals:
    void clicked();//添加点击信号

};

#endif // MLABEL_H
