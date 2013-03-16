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
#include "axesoptions.h"
#include "ui_axesoptions.h"

AxesOptions::AxesOptions(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AxesOptions)
{
    ui->setupUi(this);
    this->axes = nullptr;

    connect(this->ui->listWidget,SIGNAL(currentRowChanged(int)),this,SLOT(currentAxisChanged(int)));
    connect(this->ui->min,SIGNAL(valueChanged(double)),this,SLOT(minChanged(double)));
    connect(this->ui->max,SIGNAL(valueChanged(double)),this,SLOT(maxChanged(double)));

    connect(this->ui->label,SIGNAL(editingFinished()),this,SLOT(labelChanged()));
    connect(this->ui->log,SIGNAL(toggled(bool)),this,SLOT(logChanged(bool)));
    connect(this->ui->side,SIGNAL(toggled(bool)),this,SLOT(sideChanged(bool)));

    connect(this->ui->addAxis,SIGNAL(clicked()),this,SLOT(addAxis()));
    connect(this->ui->delAxis,SIGNAL(clicked()),this,SLOT(removeAxis()));
}

AxesOptions::~AxesOptions()
{
    delete ui;
}

void AxesOptions::setAxes(Axes *ax)
{
    this->axes = ax;
    this->refreshList();
}

void AxesOptions::refreshList()
{
    if (this->axes == nullptr)
    {
        this->ui->listWidget->clear();
        return;
    }
    if (this->axes->size() != this->ui->listWidget->count())
    {
        this->ui->listWidget->clear();
        std::for_each(axes->begin(),axes->end(),[this](Axis *ax){

            auto item = new QListWidgetItem(std::get<2>((*ax)).c_str());
            item->setData(Qt::UserRole,QVariant::fromValue<void *>(ax));
            this->ui->listWidget->addItem(item);
        });
    } else {
        for(int i = 0 ; i < axes->size() ; i++)
        {
            if(axes->at(i) != this->ui->listWidget->item(i)->data(Qt::UserRole).value<void *>())
            {
                this->ui->listWidget->clear();
                this->refreshList();
                return;
            } else {
                auto item = this->ui->listWidget->item(i);
                auto axis = axes->at(i);
                item->setText(std::get<2>((*axis)).c_str());
            }
        }
    }
}

void AxesOptions::addAxis()
{
    this->axes->push_back(new Axis(0.0,1.0,std::string("unnamed"),false,false));
    this->refreshList();
    this->ui->listWidget->setCurrentRow(axes->size()-1);
    ServicesProvider::getInstance()->getService<IProjectManager>()->projectSetUnSaved();
}

void AxesOptions::removeAxis()
{
    int id = this->ui->listWidget->currentRow();
    if(this->axes->size() <= id || id < 0)
    {
        QMessageBox::warning(static_cast<QWidget*>(ServicesProvider::getInstance()->getServiceAsQ<IMainWindow>()),
                             "OpenGrapher : Warning","Selected Axis not exists.",QMessageBox::Ok);
    } else {
        this->axes->erase(this->axes->begin()+id);
        //repair broken curves
        auto pro = ServicesProvider::getInstance()->getService<IProjectManager>()->getProject();
        bool xaxes = (this->axes == pro->getGraphOpts()->getXAxes());
        std::for_each(pro->getCurves()->begin(),pro->getCurves()->end(),[&id,&xaxes](Curve *c){
            if (xaxes) {
                std::cout<<id<<" "<<c->getXAxisId()<<std::endl;
                c->setXAxisId((c->getXAxisId() == id)? -1 : c->getXAxisId() );
            } else {
                c->setYAxisId((c->getYAxisId() == id)? -1 : c->getYAxisId() );
            }
        });

        this->refreshList();
        this->ui->listWidget->setCurrentRow(-1);
        ServicesProvider::getInstance()->getService<IProjectManager>()->projectSetUnSaved();
    }
}

void AxesOptions::currentAxisChanged(int id)
{
    //block updates in model during refresh
    disconnect(this->ui->min,SIGNAL(valueChanged(double)),this,SLOT(minChanged(double)));
    disconnect(this->ui->max,SIGNAL(valueChanged(double)),this,SLOT(maxChanged(double)));

    disconnect(this->ui->label,SIGNAL(editingFinished()),this,SLOT(labelChanged()));
    disconnect(this->ui->log,SIGNAL(toggled(bool)),this,SLOT(logChanged(bool)));
    disconnect(this->ui->side,SIGNAL(toggled(bool)),this,SLOT(sideChanged(bool)));

    if (id == -1)
    {
        this->ui->widget->setEnabled(false);
    } else {
        this->ui->widget->setEnabled(true);

        auto ax = this->axes->at(id);

        this->ui->min->setValue(std::get<0>((*ax)));
        this->ui->max->setMinimum(std::get<0>((*ax)));

        this->ui->max->setValue(std::get<1>((*ax)));
        this->ui->min->setMaximum(std::get<1>((*ax)));

        QString str = QString(std::get<2>((*ax)).c_str());
        this->ui->label->setText(str);

        this->ui->log->setChecked(std::get<3>((*ax)));
        this->ui->side->setChecked(std::get<4>((*ax)));
    }
    //return to normal
    connect(this->ui->min,SIGNAL(valueChanged(double)),this,SLOT(minChanged(double)));
    connect(this->ui->max,SIGNAL(valueChanged(double)),this,SLOT(maxChanged(double)));

    connect(this->ui->label,SIGNAL(editingFinished()),this,SLOT(labelChanged()));
    connect(this->ui->log,SIGNAL(toggled(bool)),this,SLOT(logChanged(bool)));
    connect(this->ui->side,SIGNAL(toggled(bool)),this,SLOT(sideChanged(bool)));
}

void AxesOptions::minChanged(double val)
{
    auto ax = this->axes->at(this->ui->listWidget->currentRow());
    this->ui->max->setMinimum(val);

    std::get<0>((*ax)) = val;
    ServicesProvider::getInstance()->getService<IProjectManager>()->projectSetUnSaved();
}

void AxesOptions::maxChanged(double val)
{
    auto ax = this->axes->at(this->ui->listWidget->currentRow());
    this->ui->min->setMaximum(val);

    std::get<1>((*ax)) = val;
    ServicesProvider::getInstance()->getService<IProjectManager>()->projectSetUnSaved();
}

void AxesOptions::labelChanged()
{
    auto ax = this->axes->at(this->ui->listWidget->currentRow());
    std::get<2>((*ax)) = std::string(this->ui->label->text().toUtf8().constData());
    ServicesProvider::getInstance()->getService<IProjectManager>()->projectSetUnSaved();
}

void AxesOptions::logChanged(bool val)
{
    auto ax = this->axes->at(this->ui->listWidget->currentRow());
    std::get<3>((*ax)) = val;
    ServicesProvider::getInstance()->getService<IProjectManager>()->projectSetUnSaved();
}

void AxesOptions::sideChanged(bool val)
{
    auto ax = this->axes->at(this->ui->listWidget->currentRow());
    std::get<4>((*ax)) = val;
    ServicesProvider::getInstance()->getService<IProjectManager>()->projectSetUnSaved();
}
