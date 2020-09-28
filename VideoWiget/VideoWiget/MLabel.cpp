#include "MLabel.h"

MLabel::MLabel(QWidget *parent) : QLabel(parent)
{
    this->resize(140,200);      //大小
    this->setCursor(Qt::PointingHandCursor);       //鼠标“手”型
    this->setStyleSheet("background:transparent;border:1px solid black;");  //加上边框

}
void MLabel::mouseReleaseEvent(QMouseEvent * ev)
{
    emit clicked();
}

void MLabel::setPicture(QString path){

    QPixmap pix;
    QImage image(path);                      //加入图片
    this->setPixmap(pix.fromImage(image));     //label上加入图片
    this->setScaledContents(true);             //图片自适应



}
