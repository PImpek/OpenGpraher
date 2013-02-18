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
#include "projectmanager.h"


void ProjectManager::writeCurve(Curve* c, QXmlStreamWriter* xw)
{
    xw->writeStartElement("curve");

    xw->writeAttribute("label",c->getLabel().c_str());
    xw->writeAttribute("comment",c->getComment().c_str());

    xw->writeAttribute("style",QString::number(c->getStyle()));
    xw->writeAttribute("width",QString::number(c->getWidth()));
    xw->writeAttribute("color",c->getColor().c_str());

    xw->writeAttribute("xaxisid",QString::number(c->getXAxisId()));
    xw->writeAttribute("yaxisid",QString::number(c->getYAxisId()));
    {
        xw->writeStartElement("datas");
        std::for_each(c->getData()->begin(),c->getData()->end(),[xw](std::tuple< double, double, std::vector< double > > data){
            xw->writeStartElement("data");
            xw->writeAttribute("Y",QString::number(std::get<0>(data)));
            xw->writeAttribute("X",QString::number(std::get<1>(data)));
            {
                xw->writeStartElement("measurements");
                auto additional = std::get<2>(data);
                std::for_each(additional.begin(), additional.end(),[xw](double n){

                    xw->writeStartElement("measurement");
                    xw->writeAttribute("value",QString::number(n));
                    xw->writeEndElement();

                });
                xw->writeEndElement();
            }
            xw->writeEndElement();
        });
        xw->writeEndElement();
    }{
        xw->writeStartElement("dataLabels");

        xw->writeAttribute("Y",std::get<0>((*c->getDataLabels())).c_str());
        xw->writeAttribute("X",std::get<1>((*c->getDataLabels())).c_str());
        {
            xw->writeStartElement("labels");
            auto additional = std::get<2>((*c->getDataLabels()));
            std::for_each(additional.begin(), additional.end(),[xw](std::string str){

                xw->writeStartElement("label");
                xw->writeAttribute("value",str.c_str());
                xw->writeEndElement();

            });
            xw->writeEndElement();
        }
        xw->writeEndElement();
    };
    xw->writeEndElement();
}

void ProjectManager::writeGraphOpts(GraphOpts *go, QXmlStreamWriter *xw)
{
    xw->writeStartElement("graphopts");

    xw->writeAttribute("title",go->getTitle().c_str());

    xw->writeAttribute("titlesize",QString::number(go->getTitleSize()));
    xw->writeAttribute("curvelabelsize",QString::number(go->getCurveLabelSize()));

    xw->writeAttribute("showlegend",(go->isShowLegend())?"1":"0");
    xw->writeAttribute("legendsize",QString::number(go->getLegendSize()));

    xw->writeAttribute("legend_x",QString::number(std::get<0>(go->getLegendPosition())));
    xw->writeAttribute("legend_y",QString::number(std::get<1>(go->getLegendPosition())));

    xw->writeStartElement("xaxes");
    std::for_each(go->getXAxes()->begin(),go->getXAxes()->end(),[xw,this] (Axis *axis){
        this->writeAxis(axis,xw);
    });
    xw->writeEndElement();

    xw->writeStartElement("yaxes");
    std::for_each(go->getYAxes()->begin(),go->getYAxes()->end(),[xw,this] (Axis *axis){
        this->writeAxis(axis,xw);
    });
    xw->writeEndElement();

    xw->writeEndElement();
}

void ProjectManager::writeAxis(Axis *axis, QXmlStreamWriter *xw)
{
    xw->writeStartElement("axis");

    xw->writeAttribute("min",QString::number(std::get<0>((*axis))));
    xw->writeAttribute("max",QString::number(std::get<1>((*axis))));

    xw->writeAttribute("label",std::get<2>((*axis)).c_str());

    xw->writeAttribute("logarithmic",(std::get<3>((*axis)))?"1":"0");
    xw->writeAttribute("side",(std::get<3>((*axis)))?"1":"0");

    xw->writeEndElement();
}

bool ProjectManager::readCurve(QXmlStreamReader *xr, Project *pro)
{
    if(xr->tokenType() != QXmlStreamReader::StartElement && xr->name() == "curve") {
        return false;
    }
    auto c = new Curve();
    auto attrs = xr->attributes();

    if(attrs.hasAttribute("label")){
        c->setLabel(attrs.value("label").toUtf8().constData());
    }

    if(attrs.hasAttribute("comment")){
        c->setComment(attrs.value("comment").toUtf8().constData());
    }

    if(attrs.hasAttribute("style")){
        c->setStyle(static_cast<Curve::LineStyles>(attrs.value("style").toUtf8().toInt()));
    }

    if(attrs.hasAttribute("width")){
        c->setWidth(attrs.value("width").toUtf8().toDouble());
    }

    if(attrs.hasAttribute("color")){
        c->setColor(attrs.value("color").toUtf8().constData());
    }

    if(attrs.hasAttribute("xaxisid")){
        c->setXAxisId(attrs.value("xaxisid").toUtf8().toInt());
    }

    if(attrs.hasAttribute("yaxisid")){
        c->setYAxisId(attrs.value("yaxisid").toUtf8().toInt());
    }
    xr->readNext();
    if(xr->readNext() == QXmlStreamReader::StartElement && xr->name() == "datas") {

        while(!(xr->readNext() == QXmlStreamReader::EndElement && xr->name() == "datas")) {
            if(xr->tokenType() == QXmlStreamReader::StartElement && xr->name() == "data"){

                double y,x;
                std::vector<double> ms;
                auto attrs = xr->attributes();

                if(attrs.hasAttribute("Y")){
                    y = attrs.value("Y").toUtf8().toDouble();
                }

                if(attrs.hasAttribute("X")){
                    x = attrs.value("X").toUtf8().toDouble();
                }

                xr->readNext();
                if(xr->readNext() == QXmlStreamReader::StartElement && xr->name() == "measurements"){
                    while(!(xr->readNext() == QXmlStreamReader::EndElement && xr->name() == "measurements")) {
                        if(xr->tokenType() == QXmlStreamReader::StartElement && xr->name() == "measurement"){

                            attrs = xr->attributes();
                            if(attrs.hasAttribute("value")){
                                ms.push_back(attrs.value("value").toUtf8().toDouble());
                            }
                        }
                    }
                }

                c->getData()->push_back(std::make_tuple(y,x,ms));
            }
        }
    }

    xr->readNext();
    if(xr->readNext() == QXmlStreamReader::StartElement && xr->name() == "dataLabels") {

        std::string y,x;
        std::vector<std::string> mls;
        auto attrs = xr->attributes();

        if(attrs.hasAttribute("Y")){
            y = attrs.value("Y").toUtf8().constData();
        }

        if(attrs.hasAttribute("X")){
            x = attrs.value("X").toUtf8().constData();
        }

        xr->readNext();
        if(xr->readNext() == QXmlStreamReader::StartElement && xr->name() == "labels"){
            while(!(xr->readNext() == QXmlStreamReader::EndElement && xr->name() == "labels")) {
                if(xr->tokenType() == QXmlStreamReader::StartElement && xr->name() == "label"){

                    attrs = xr->attributes();
                    if(attrs.hasAttribute("value")){
                        mls.push_back(attrs.value("value").toUtf8().constData());
                    }
                }
            }
        }

        c->setDataLabels(new CurveLabels(std::make_tuple(y,x,mls)));
    }


    pro->getCurves()->push_back(c);

    return true;
}

bool ProjectManager::readGraphOpts(QXmlStreamReader *xr, Project *pro)
{
    if(xr->tokenType() != QXmlStreamReader::StartElement && xr->name() == "graphopts") {
        return false;
    }

    auto attrs = xr->attributes();

    if(attrs.hasAttribute("title")){
        pro->getGraphOpts()->setTitle(attrs.value("title").toUtf8().constData());
    }
    if(attrs.hasAttribute("titlesize")){
        pro->getGraphOpts()->setTitleSize(attrs.value("titlesize").toUtf8().toInt());
    }
    if(attrs.hasAttribute("showlegend")){
        pro->getGraphOpts()->setShowLegend((attrs.value("showlegend").toString() == "1") ? true : false );
    }
    if(attrs.hasAttribute("legendsize")){
        pro->getGraphOpts()->setLegendSize(attrs.value("legendsize").toUtf8().toInt());
    }
    if(attrs.hasAttribute("legend_x") && attrs.hasAttribute("legend_y")){
        pro->getGraphOpts()->setLegendPosition(std::make_tuple(attrs.value("legend_x").toUtf8().toDouble(),
                                                               attrs.value("legend_y").toUtf8().toDouble())
                                               );
    }
    xr->readNext();
    this->readAxis(xr,pro->getGraphOpts()->getXAxes());

    xr->readNext();
    this->readAxis(xr,pro->getGraphOpts()->getYAxes());

    return true;
}

bool ProjectManager::readAxis(QXmlStreamReader *xr, Axes *ax)
{
    if(xr->readNext() == QXmlStreamReader::StartElement && xr->name() == "yaxes") {
        while(!(xr->readNext() == QXmlStreamReader::EndElement && xr->name() == "yaxes")) {

            if(xr->tokenType() == QXmlStreamReader::StartElement && xr->name() == "axis"){
                auto attrs = xr->attributes();

                if (attrs.hasAttribute("min") &&
                        attrs.hasAttribute("max") &&
                        attrs.hasAttribute("label") &&
                        attrs.hasAttribute("logarithmic") &&
                        attrs.hasAttribute("side")){

                    ax->push_back(new Axis(attrs.value("min").toUtf8().toDouble(),
                                                  attrs.value("max").toUtf8().toDouble(),
                                                  std::string(attrs.value("label").toUtf8().constData()),
                                                  (attrs.value("logarithmic").toString() == "1") ? true : false,
                                                  (attrs.value("side").toString() == "1") ? true : false));
                }
            }
        }
        return true;
    } else {
        return false;
    }
}


ProjectManager::ProjectManager(QObject *parent) : QObject(parent)
{
    ServicesProvider::getInstance()->registerService<IProjectManager>(this);
    this->project= new Project();
    this->projectPath = new std::string("");
}

ProjectManager::~ProjectManager()
{
    delete this->project;
    delete this->projectPath;
}

Project *ProjectManager::getProject()
{
    return this->project;
}

void ProjectManager::loadProject(std::string fname)
{
    auto pro = new Project();

    auto file = new QFile(QString(fname.c_str()));

    if(!file->open(QIODevice::ReadOnly|QIODevice::Text)) {
        QMessageBox::critical(dynamic_cast<QWidget*>(ServicesProvider::getInstance()->getService<IMainWindow>()),
                              "OpenGrapher : Read error",file->fileName()+ " - file is unreadable",QMessageBox::Ok);
    } else {

        auto xr = new QXmlStreamReader(file);

        while(!xr->atEnd() && !xr->hasError()) {
            auto token = xr->readNext();

            if(token == QXmlStreamReader::StartDocument) {
                continue;
            }

            if(token == QXmlStreamReader::StartElement) {

                if(xr->name() == "OpenGrapherProject"){
                    auto attrs = xr->attributes();

                    if(attrs.hasAttribute("name")) {
                        pro->setName(attrs.value("name").toUtf8().constData());
                    }
                    if(attrs.hasAttribute("version")) {
                        //TODO: in future : make use of version attribure
                    }
                }
                if(xr->name() == "curves") {
                }
                if(xr->name() == "curve") {
                    this->readCurve(xr,pro);
                }
                if(xr->name() == "graphopts") {
                    this->readGraphOpts(xr,pro);
                }
            }

        }

        delete xr;
        this->setProjectPath(fname);
        this->setProject(pro);
    }
    file->close();
    delete file;
    emit projectChanged();
}

void ProjectManager::saveProject()
{
    this->saveProject((*this->projectPath));
}

void ProjectManager::saveProject(std::string fname)
{
    auto file = new QFile(QString(fname.c_str()));

    if(!file->open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(0, "OpenGrapher : Write error ", file->fileName()+"file is in read only mode");
        qDebug()<<file->fileName()<<" - file is in read only mode";
    } else {
        auto xw = new QXmlStreamWriter();
        xw->setDevice(file);

        xw->setAutoFormatting(true);
        xw->setAutoFormattingIndent(1);

        xw->writeStartDocument();
        {
            xw->writeStartElement(QString("OpenGrapherProject"));

            xw->writeAttribute("name",this->getProject()->getName().c_str());
            xw->writeAttribute("version",ogGetVersion().c_str());
            {
                xw->writeStartElement("curves");
                std::for_each(this->getProject()->getCurves()->begin(),this->getProject()->getCurves()->end(),[xw,this] (Curve* c){
                    this->writeCurve(c,xw);
                });
                xw->writeEndElement();
            }
            this->writeGraphOpts(this->getProject()->getGraphOpts(),xw);
            xw->writeEndElement();
        }
        xw->writeEndDocument();
        delete xw;
    }
    file->close();
    delete file;

    this->setProjectPath(fname);
    emit projectChanged();

}

void ProjectManager::projectSetUnSaved()
{
    this->getProject()->setSaved(false);
    emit projectContentChanged();
}

void ProjectManager::projectSetSaved()
{
    this->getProject()->setSaved(true);
    emit projectContentSaved();
}

std::string ProjectManager::getProjectPath()
{
    return (*this->projectPath);
}

std::string ProjectManager::getName()
{
    return std::string("IProjectManager");
}

void ProjectManager::newProject()
{
    delete this->project;
    this->setProjectPath("");
    this->project = new Project();
    emit projectChanged();
}

void ProjectManager::setProjectPath(std::string s)
{
    delete this->projectPath;
    this->projectPath = new std::string(s);
}

void ProjectManager::setProject(Project *p)
{
    delete this->project;
    this->project = p;
}
