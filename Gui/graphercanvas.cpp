/* Copyright (c) 2012-2013, Bartosz Foder, (bartosz@foder.pl)
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
#include "Gui/graphercanvas.h"


GrapherCanvas::GrapherCanvas(QWidget *parent) :
    QWidget(parent)
{
    ServicesProvider::getInstance()->registerService<IGrapherCanvas>(this);

    this->canvas = new QGraphicsView(this);
    this->canvas->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    this->canvas->setResizeAnchor(QGraphicsView::AnchorViewCenter);

    auto scene = new QGraphicsScene(this->canvas);
    scene->setSceneRect(0,0,this->width(),this->height());
    this->canvas->setBackgroundBrush(QBrush(Qt::white));
    this->canvas->setScene(scene);

    this->setLayout(new QGridLayout);
    this->layout()->addWidget(canvas);

    auto *pm = ServicesProvider::getInstance()->getServiceAsQ<IProjectManager>();
    this->connect(pm,SIGNAL(projectChanged()),this,SLOT(redraw()));
    this->connect(pm,SIGNAL(projectContentChanged()),this,SLOT(redraw()));

}

std::string GrapherCanvas::getName()
{
    return std::string("IGrapherCanvas");
}

void GrapherCanvas::resizeEvent(QResizeEvent *re)
{
    QWidget::resizeEvent(re);
    redraw();
}

void GrapherCanvas::redraw()
{

    int canWidth = this->width()-40;
    canWidth = (canWidth < 640)?640:canWidth;

    int canHeight = this->height()-40;
    canHeight = (canHeight < 480)?480:canHeight;
    //offsets
    int offx=0,offy=0;
    //constant lenght of scales and title
    int scaleSize = 40;
    this->canvas->blockSignals(true);
    this->canvas->setSceneRect(0,0,canWidth,canHeight);
    //qDebug()<<"Canvas size: "<<canWidth<<" x "<<canHeight;

    this->canvas->scene()->clear();
    Project *pro = ServicesProvider::getInstance()->getService<IProjectManager>()->getProject();

    int mainHorSize = (canWidth - (pro->getGraphOpts()->getYAxes()->size() * scaleSize) - 2*offx);
    int mainVerSize = (canHeight - ((pro->getGraphOpts()->getXAxes()->size() +1) * scaleSize) - 2*offy);

    //qDebug()<<"graph size w:"<<mainHorSize<<", h:"<<mainVerSize;

    int mainCanOffVer = 1; //1 item for title, rest are axes
    int mainCanOffHor = 0;

    std::for_each(pro->getGraphOpts()->getXAxes()->begin(),pro->getGraphOpts()->getXAxes()->end(),[&mainCanOffVer](Axis *ax){
        if (std::get<4>((*ax)) == 1)
            mainCanOffVer++;
    });
    std::for_each(pro->getGraphOpts()->getYAxes()->begin(),pro->getGraphOpts()->getYAxes()->end(),[&mainCanOffHor](Axis *ax){
        if (std::get<4>((*ax)) == 0)
            mainCanOffHor++;
    });

    this->canvas->scene()->addItem(new QGraphicsRectItem(offx,offy,canWidth-2*offx,canHeight-2*offx));
    this->canvas->scene()->addItem(new TitleItem(offx+(mainCanOffHor * scaleSize),offy,mainHorSize,scaleSize,pro->getGraphOpts()));

    //qDebug()<<"graph pos x:"<<offx+(mainCanOffHor * scaleSize)<<", y:"<<offy + (mainCanOffVer * scaleSize);
    this->canvas->scene()->addItem(new GrapherItem(offx+(mainCanOffHor * scaleSize),offy + (mainCanOffVer * scaleSize), mainHorSize, mainVerSize, pro));

    int counter1 = 1, counter2 = 0;
    for (int i = 0 ; i < pro->getGraphOpts()->getXAxes()->size() ; i++ )
    {
        if (std::get<4>((*(pro->getGraphOpts()->getXAxes()->at(i)))) == 1)
            this->canvas->scene()->addItem(new ScaleItem(offx+ (mainCanOffHor * scaleSize),
                                                         offy+ (scaleSize * counter1++),
                                                         mainHorSize,
                                                         scaleSize,
                                                         pro->getGraphOpts()->getXAxes()->at(i)));
        else
            this->canvas->scene()->addItem(new ScaleItem(offx + (mainCanOffHor * scaleSize),
                                                         offy + (mainVerSize + (scaleSize * (mainCanOffVer + counter2++))) ,
                                                         mainHorSize,
                                                         scaleSize,
                                                         pro->getGraphOpts()->getXAxes()->at(i)));
    }
   counter1 = 0, counter2 = 0;
    for (int i = 0 ; i < pro->getGraphOpts()->getYAxes()->size() ; i++ )
    {
       if (std::get<4>((*(pro->getGraphOpts()->getYAxes()->at(i)))) == 0)
           this->canvas->scene()->addItem(new ScaleItem(offx + (scaleSize * counter1++),
                                                        offy + (mainCanOffVer * scaleSize),
                                                        scaleSize,
                                                        mainVerSize,pro->getGraphOpts()->getYAxes()->at(i)));
       else
           this->canvas->scene()->addItem(new ScaleItem(offx + (mainHorSize + (scaleSize * (mainCanOffHor + counter2++))),
                                                        offy + (mainCanOffVer * scaleSize),
                                                        scaleSize,
                                                        mainVerSize,
                                                        pro->getGraphOpts()->getYAxes()->at(i)));
    }
    this->canvas->blockSignals(false);
}
