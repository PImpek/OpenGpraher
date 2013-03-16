#ifndef TITLEITEM_H
#define TITLEITEM_H

#include <QPainter>
#include <QTextItem>
#include <QGraphicsItem>

#include "Data/graphopts.h"

class TitleItem : public QGraphicsItem
{
public:
    TitleItem(int x, int y, int wid, int hei, GraphOpts *go, QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    int width, height;
    GraphOpts *graphOpts;
};

#endif // TITLEITEM_H
