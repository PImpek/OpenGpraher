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

#include "Gui/mainwindow.h"
#include "servicesprovider.h"
#include "projectmanager.h"
#include "Interfaces/imainwindow.h"

#include <QApplication>


void projectmanagertest();

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);


    new ProjectManager();
    projectmanagertest();
    new MainWindow;


    IMainWindow* mw = ServicesProvider::getInstance()->getService<IMainWindow>();
    mw->_show();

    return a.exec();
}

void projectmanagertest(){
    IProjectManager* pm = ServicesProvider::getInstance()->getService<IProjectManager>();

    auto c = new Curve();
    for(int i = 0; i<10 ;i++){
        std::vector<double> v;
        v.push_back(i+1);
        v.push_back(i+2);
        c->getData()->push_back(std::make_tuple(double(i),double(i*i+i),v));
    }
    std::get<2>((*c->getDataLabels())).push_back(std::string("x1"));
    std::get<2>((*c->getDataLabels())).push_back(std::string("x2"));

    pm->getProject()->getCurves()->push_back(c);

    c = new Curve();
    c->setColor(std::string("#00aa00"));
    for(int i = 0; i<10 ;i++){
        std::vector<double> v;
        v.push_back(i+1);
        v.push_back(i+2);
        c->getData()->push_back(std::make_tuple(double(i),double(i*i+i),v));
    }
    pm->getProject()->getCurves()->push_back(c);

    pm->getProject()->getGraphOpts()->getXAxes()->push_back(std::make_tuple(0.0,1.0,std::string("x"),false,false));
    pm->getProject()->getGraphOpts()->getXAxes()->push_back(std::make_tuple(0.0,1.0,std::string("y"),false,false));
    pm->getProject()->getGraphOpts()->getXAxes()->push_back(std::make_tuple(0.0,1.0,std::string("z"),false,false));

    pm->getProject()->getGraphOpts()->getYAxes()->push_back(std::make_tuple(0.0,2.0,std::string("xx"),false,false));
    pm->getProject()->getGraphOpts()->getYAxes()->push_back(std::make_tuple(0.0,2.0,std::string("yy"),false,false));
    pm->getProject()->getGraphOpts()->getYAxes()->push_back(std::make_tuple(0.0,2.0,std::string("zz"),false,false));
    //pm->saveProject(std::string("/home/pimpek/test.ogx"));

    //pm->loadProject(std::string("/home/pimpek/test.ogx"));
    // pm->saveProject();

    // pm->loadProject(std::string("/home/pimpek/test.ogx"));
    // pm->saveProject();

    // pm->loadProject(std::string("/home/pimpek/test.ogx"));
    // pm->saveProject();
}
