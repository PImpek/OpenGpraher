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
#include "curveproperties.h"
#include "ui_curveproperties.h"

#include "Interfaces/imainwindow.h"

CurveProperties::CurveProperties(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::CurveProperties)
{
    ui->setupUi(this);

    QStringList styles;
    styles << "No line"<<"Points olny"<<"--line"<<"- line"<<". line"<<"-. line"<<"-.. line";
    this->ui->style->insertItems(0,styles);

    this->connect(this->ui->label,SIGNAL(editingFinished()),this,SLOT(labelChnged()));
    this->connect(this->ui->comment,SIGNAL(textChanged()),this,SLOT(commentChanged()));

    this->connect(this->ui->style,SIGNAL(currentIndexChanged(int)),this,SLOT(styleChanged(int)));
    this->connect(this->ui->colorbtn,SIGNAL(clicked()),this,SLOT(colorChange()));

    this->connect(this->ui->xaxis,SIGNAL(currentIndexChanged(int)),this,SLOT(xAxisIdChanged(int)));
    this->connect(this->ui->yaxis,SIGNAL(currentIndexChanged(int)),this,SLOT(yAxisIdChanged(int)));

    this->connect(this->ui->width,SIGNAL(valueChanged(double)),this,SLOT(widthChanged(double)));
    this->reloadData();

    ServicesProvider::getInstance()->registerService<ICurveProperties>(this);
}

CurveProperties::~CurveProperties()
{
    delete ui;
}

std::string CurveProperties::getName()
{
    return "ICurveProperties";
}

void CurveProperties::currentCurveIndexChanged(int id)
{
    this->reloadData(id);
}

void CurveProperties::labelChnged()
{
    if (this->c == nullptr || this->c->getLabel() == std::string(this->ui->label->text().toUtf8().constData())) return;
    this->c->setLabel(std::string(this->ui->label->text().toUtf8().constData()));

    ServicesProvider::getInstance()->getService<IProjectManager>()->projectSetUnSaved();
}

void CurveProperties::commentChanged()
{
    if (this->c == nullptr || this->c->getComment() == std::string(this->ui->comment->document()->toPlainText().toUtf8().constData())) return;
    this->c->setComment((std::string(this->ui->comment->document()->toPlainText().toUtf8().constData())));

    ServicesProvider::getInstance()->getService<IProjectManager>()->projectSetUnSaved();
}

void CurveProperties::styleChanged(int id)
{
    if (this->c == nullptr || this->c->getStyle() == id) return;
    this->c->setStyle(static_cast<Curve::LineStyles>(id));

    ServicesProvider::getInstance()->getService<IProjectManager>()->projectSetUnSaved();
}

void CurveProperties::xAxisIdChanged(int id)
{
    if (this->c == nullptr || this->c->getXAxisId() == id - 1) return;
    this->c->setXAxisId(id-1);

    ServicesProvider::getInstance()->getService<IProjectManager>()->projectSetUnSaved();
}

void CurveProperties::yAxisIdChanged(int id)
{
    if (this->c == nullptr || this->c->getYAxisId() == id - 1) return;
    this->c->setYAxisId(id-1);

    ServicesProvider::getInstance()->getService<IProjectManager>()->projectSetUnSaved();
}

void CurveProperties::colorChange()
{
    if (this->c == nullptr) return;
    auto color = QColorDialog::getColor(QColor(this->ui->color->text()),this);
    if (color.isValid() || QColor(this->ui->color->text()) == color) {

        this->c->setColor(std::string(color.name().toUtf8().constData()));
        this->ui->color->setText(c->getColor().c_str());

        ServicesProvider::getInstance()->getService<IProjectManager>()->projectSetUnSaved();
    }
}

void CurveProperties::widthChanged(double w)
{
    if (this->c == nullptr || this->c->getWidth() == w) return;
    this->c->setWidth(this->ui->width->value());

    ServicesProvider::getInstance()->getService<IProjectManager>()->projectSetUnSaved();
}

void CurveProperties::loadCurve(Curve *c){
    this->c = c;
    auto pm = ServicesProvider::getInstance()->getService<IProjectManager>();

    this->ui->label->setText(c->getLabel().c_str());
    this->ui->comment->setText(c->getComment().c_str());

    this->ui->style->setCurrentIndex(static_cast<int>(c->getStyle()));
    this->ui->width->setValue(c->getWidth());
    this->ui->color->setText(c->getColor().c_str());

    this->disconnect(this->ui->xaxis,SIGNAL(currentIndexChanged(int)),this,SLOT(xAxisIdChanged(int)));
    this->reloadAxis(this->ui->xaxis,pm->getProject()->getGraphOpts()->getXAxes());
    this->connect(this->ui->xaxis,SIGNAL(currentIndexChanged(int)),this,SLOT(xAxisIdChanged(int)));

    this->disconnect(this->ui->yaxis,SIGNAL(currentIndexChanged(int)),this,SLOT(yAxisIdChanged(int)));
    this->reloadAxis(this->ui->yaxis,pm->getProject()->getGraphOpts()->getYAxes());
    this->connect(this->ui->yaxis,SIGNAL(currentIndexChanged(int)),this,SLOT(yAxisIdChanged(int)));

    this->ui->xaxis->setCurrentIndex(c->getXAxisId()+1);
    this->ui->yaxis->setCurrentIndex(c->getYAxisId()+1);
}

void CurveProperties::reloadAxis(QComboBox *cb, Axes *a)
{
    cb->clear();
    cb->insertItem(0,"");

    std::for_each(a->begin(),a->end(),[cb] (Axis *ax){
        cb->insertItem(cb->count(),std::get<2>((*ax)).c_str());
    });
}

void CurveProperties::reloadData(int curveId)
{
    auto pm = ServicesProvider::getInstance()->getService<IProjectManager>();

    if (curveId == -1){
        this->setDisabled(true);
        this->c = nullptr;
        return;
    } else if (curveId < pm->getProject()->getCurves()->size()){
        this->setEnabled(true);

        this->loadCurve(pm->getProject()->getCurves()->at(curveId));
    } else {
        QMessageBox::warning(dynamic_cast<QWidget*>(ServicesProvider::getInstance()->getService<IMainWindow>()),
                             "OpenGrapher : Warning","Selected curve not exists",QMessageBox::Ok);

    }
}
