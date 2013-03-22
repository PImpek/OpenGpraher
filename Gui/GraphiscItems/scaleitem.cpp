/* Copyright (c) 2013, Bartosz Foder, (bartosz@foder.pl)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "scaleitem.h"

ScaleItem::ScaleItem(int x, int y, int width, int height, Axis *ax, QGraphicsItem *parent) : QGraphicsItem(parent)
{
    this->axis = ax;

    if (height > width)
    {
        mlenght = height;
        slenght = width;
        orient = Qt::Vertical;
    } else {
        mlenght = width;
        slenght = height;
        orient = Qt::Horizontal;
    }

    this->setX(x);
    this->setY(y);
}


QRectF ScaleItem::boundingRect() const
{
    return QRectF(1,1,(orient == Qt::Vertical)?slenght-1:mlenght-1, (orient == Qt::Horizontal)?slenght-1:mlenght-1);
}

void ScaleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (this->orient == Qt::Horizontal)
        this->paintHorizontal(painter, option, widget);
    else
        this->paintVertical(painter, option, widget);

}

void ScaleItem::paintHorizontal(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    double min = std::get<0>((*this->axis));
    double max = std::get<1>((*this->axis));
    //if this is default scale we need to find maximum and minimum in curves tied with this scalee
    if (min == 0. && max == 1.)
    {
        min = 100000.;
        max = -100000.;
        Axes *xa = ServicesProvider::getInstance()->getService<IProjectManager>()->getProject()->getGraphOpts()->getXAxes();

        auto it = std::find(xa->begin(),xa->end(),this->axis);
        int id = std::distance(xa->begin(),it);
        if(id < xa->size())
        {
            std::vector<Curve *> *crvs = ServicesProvider::getInstance()->getService<IProjectManager>()->getProject()->getCurves();
            std::for_each(crvs->begin(),crvs->end(),[&min,&max,&id](Curve *c){
                if(c->getXAxisId() == id)
                {
                    std::for_each(c->getData()->begin(),c->getData()->end(),[&min,&max](std::tuple< double , double, std::vector< double > > row){
                        double x = std::get<1>(row);
                        if (x < min)
                            min = x;
                        else if (x > max)
                            max = x;
                    });
                }
            });
        }
        if (min > max)
        {
            min = 0.;
            max = 1.;
        }
    }
    QString label = QString(std::get<2>((*this->axis)).c_str());

    bool side = std::get<4>((*this->axis));
    bool logarithmic = std::get<3>((*this->axis));

    painter->drawLine(QLineF(1,(side)?this->slenght-1:1,this->mlenght-1,(side)?this->slenght-1:1));

    if(logarithmic)
    {
        if (min <=0. || max <=0.)
        {
            painter->drawText(this->boundingRect(),Qt::AlignCenter,"!!! logharithmic scale presents only positive values !!!\n"+QString(label));
            return;
        }
        double lmin = log10(min);
        double lmax = log10(max);
        int dl = (int)lmax - (int)lmin + 1;

        for(int i = 0 ; i <= dl ; i++)
        {
            painter->drawLine(QLineF((this->mlenght/dl)*i,
                                     this->slenght/((side)?1.5:3),
                                     (this->mlenght/dl)*i,
                                     (side)?this->slenght-1:1));

            auto txt = QString::number(pow(10,((int)lmin+i)));
            int tw = painter->fontMetrics().width(txt);
            int th = painter->fontMetrics().height();
            painter->drawText(QPointF((this->mlenght/dl)*i - tw/2,(side)?1+th:this->slenght-1),txt);

        }
    } else {
        for(int i = 0 ; i <= 10 ; i++)
        {
            painter->drawLine(QLineF((this->mlenght/10.)*i,
                                     this->slenght/((i%2==0)?2.:(!side)?4.:1.33),
                                     (this->mlenght/10.)*i,
                                     (side)?this->slenght-1:1));
            if (i%2 == 0){
                auto txt = QString::number(min + i*(max - min)/10);
                int tw = painter->fontMetrics().width(txt);
                int th = painter->fontMetrics().height();
                painter->drawText(QPointF((this->mlenght/10.)*i - tw/2,
                                          (side)?1+th:this->slenght-1),
                                  txt);
            }
        }
    }
    int tw = painter->fontMetrics().width(label);
    painter->drawText(QPointF(this->mlenght/2 - tw/2,this->slenght/2),label);
}

void ScaleItem::paintVertical(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->translate(this->slenght,0.);
    painter->rotate(90);
    this->paintHorizontal(painter,option,widget);
}
