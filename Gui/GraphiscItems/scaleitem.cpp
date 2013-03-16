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
    //painter->drawRect(this->boundingRect());
    //painter->drawEllipse(this->boundingRect());

    bool side = std::get<4>((*this->axis));
    const char *label = std::get<2>((*this->axis)).c_str();

    if (this->orient == Qt::Horizontal) //x
    {
        painter->drawLine(QLineF(1,(side)?this->slenght-1:1,this->mlenght-1,(side)?this->slenght-1:1));
        for(int i = 0 ; i < 11 ; i++)
        {
            painter->drawLine(QLineF((this->mlenght/10)*i,
                                     this->slenght/((i%2==0)?2.:(!side)?4.:1.33),
                                     (this->mlenght/10)*i,
                                     (side)?this->slenght-1:1));
        }
        painter->drawText(this->boundingRect(),Qt::AlignCenter,label);

    } else { //y
        painter->drawLine(QLineF((!side)?this->slenght-1:1,1,(!side)?this->slenght-1:1,this->mlenght));
        for(int i = 0 ; i < 11 ; i++)
        {
            painter->drawLine(QLineF(this->slenght/((i%2==0)?2.:(side)?4.:1.33),
                                     (this->mlenght/10)*i,
                                     (!side)?this->slenght-1:1,
                                     (this->mlenght/10)*i));
        }
        painter->translate(0,this->mlenght);
        painter->rotate(270);
        painter->drawText(QRectF(1,1,(orient != Qt::Vertical)?slenght-1:mlenght-1, (orient != Qt::Horizontal)?slenght-1:mlenght-1),Qt::AlignCenter,label);
    }
}
