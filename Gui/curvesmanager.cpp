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
#include "curvesmanager.h"
#include "ui_curvesmanager.h"

#include <QVariant>

CurvesManager::CurvesManager(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::CurvesManager)
{
    ui->setupUi(this);
    this->connect(this->ui->curvesList,SIGNAL(currentRowChanged(int)),this,SLOT(listSelectionChanged(int)));
    this->refreshCurves();

    ServicesProvider::getInstance()->registerService<ICurvesManager>(this);
}

CurvesManager::~CurvesManager()
{
    delete ui;
}

std::string CurvesManager::getName()
{
    return std::string("ICurvesManager");
}

void CurvesManager::refreshCurves()
{
    auto pm = ServicesProvider::getInstance()->getService<IProjectManager>();
    auto curves = pm->getProject()->getCurves();

    if (curves->size() != this->ui->curvesList->count())
    {
        this->ui->curvesList->clear();
        std::for_each(curves->begin(),curves->end(),[this] (Curve *c){

            auto item = new QListWidgetItem(c->getLabel().c_str());

            item->setData(Qt::UserRole,QVariant::fromValue<void *>(c));
            item->setData(Qt::DecorationRole,QColor(c->getColor().c_str()));

            this->ui->curvesList->addItem(item);
        });
    } else {
        for (int i = 0 ; i < this->ui->curvesList->count();i++){
            if (curves->at(i) != (Curve *)(this->ui->curvesList->item(i)->data(Qt::UserRole).value<void *>()))
            {
                //clear list on ui and invoke this method again
                this->ui->curvesList->clear();
                this->refreshCurves();
                return;
            } else {
                this->ui->curvesList->item(i)->setText(curves->at(i)->getLabel().c_str());
                this->ui->curvesList->item(i)->setData(Qt::DecorationRole,QColor(curves->at(i)->getColor().c_str()));
            }
        }


    }

}

int CurvesManager::getSelectionId()
{
    return this->ui->curvesList->currentRow();
}


void CurvesManager::listSelectionChanged(int id)
{
    emit selectionChanged(id);
}


void CurvesManager::refresh()
{
    this->refreshCurves();
}
