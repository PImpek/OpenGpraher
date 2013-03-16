#include "titleitem.h"

TitleItem::TitleItem(int x, int y, int wid, int hei, GraphOpts *go, QGraphicsItem *parent) :
    QGraphicsItem(parent)
{
    this->setX(x);
    this->setY(y);

    this->width = wid;
    this->height = hei;
    this->graphOpts = go;
}

QRectF TitleItem::boundingRect() const
{
    return QRectF(1,1,this->width-1, this->height-1);
}

void TitleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto font = painter->font();
    painter->setFont(QFont(font.family(),this->graphOpts->getTitleSize()));

    painter->drawText(this->boundingRect(),Qt::AlignCenter,QString(this->graphOpts->getTitle().c_str()));
    painter->setFont(font);
}
