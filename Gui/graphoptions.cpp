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
#include "graphoptions.h"
#include "ui_graphoptions.h"

GraphOptions::GraphOptions(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::GraphOptions)
{
    ui->setupUi(this);
    connect(this->ui->title,SIGNAL(editingFinished()),this,SLOT(titleChanged()));
    connect(this->ui->titlesize,SIGNAL(valueChanged(int)),this,SLOT(titleSizeChanged(int)));

    connect(this->ui->showlegend,SIGNAL(toggled(bool)),this,SLOT(showLegendChanged(bool)));
    connect(this->ui->legendsize,SIGNAL(valueChanged(int)),this, SLOT(legendSizeChanged(int)));
    connect(this->ui->curvessize,SIGNAL(valueChanged(int)),this,SLOT(curvesSizeChanged(int)));

    this->refreshContent();

    ServicesProvider::getInstance()->registerService<IGraphOptions>(this);
}

GraphOptions::~GraphOptions()
{
    delete ui;
}

std::string GraphOptions::getName()
{
    return std::string("IGraphOptions");
}

void GraphOptions::refreshContent()
{
    Project *pro = ServicesProvider::getInstance()->getService<IProjectManager>()->getProject();

    this->ui->title->setText(pro->getGraphOpts()->getTitle().c_str());
    this->ui->titlesize->setValue(pro->getGraphOpts()->getTitleSize());
    this->ui->showlegend->setChecked(pro->getGraphOpts()->isShowLegend());

    this->ui->legendsize->setValue(pro->getGraphOpts()->getLegendSize());
    this->ui->curvessize->setValue(pro->getGraphOpts()->getCurveLabelSize());

    this->ui->xaxes->setAxes(pro->getGraphOpts()->getXAxes());
    this->ui->yaxes->setAxes(pro->getGraphOpts()->getYAxes());

}

void GraphOptions::refresh()
{
    this->refreshContent();
}

void GraphOptions::titleChanged()
{
    ServicesProvider::getInstance()->getService<IProjectManager>()->getProject()->getGraphOpts()->setTitle(
                this->ui->title->text().toUtf8().constData());
    ServicesProvider::getInstance()->getService<IProjectManager>()->projectSetUnSaved();
}

void GraphOptions::titleSizeChanged(int s)
{
    ServicesProvider::getInstance()->getService<IProjectManager>()->getProject()->getGraphOpts()->setTitleSize(s);
    ServicesProvider::getInstance()->getService<IProjectManager>()->projectSetUnSaved();
}

void GraphOptions::showLegendChanged(bool s)
{
    ServicesProvider::getInstance()->getService<IProjectManager>()->getProject()->getGraphOpts()->setShowLegend(s);
    ServicesProvider::getInstance()->getService<IProjectManager>()->projectSetUnSaved();
}

void GraphOptions::legendSizeChanged(int s)
{
    ServicesProvider::getInstance()->getService<IProjectManager>()->getProject()->getGraphOpts()->setLegendSize(s);
    ServicesProvider::getInstance()->getService<IProjectManager>()->projectSetUnSaved();
}

void GraphOptions::curvesSizeChanged(int s)
{
    ServicesProvider::getInstance()->getService<IProjectManager>()->getProject()->getGraphOpts()->setCurveLabelSize(s);
    ServicesProvider::getInstance()->getService<IProjectManager>()->projectSetUnSaved();
}

