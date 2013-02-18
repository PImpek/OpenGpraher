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
