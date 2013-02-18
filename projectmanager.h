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
#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <iostream>
#include <tuple>

#include <QObject>
#include <QtDebug>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QFile>
#include <QMessageBox>

#include "Interfaces/iprojectmanager.h"
#include "Interfaces/imainwindow.h"

#include "Data/project.h"
#include "Data/curve.h"

#include "servicesprovider.h"

extern std::string ogGetVersion();

class ProjectManager : public QObject,public IProjectManager
{
    Q_OBJECT
    Q_INTERFACES(IProjectManager)
public:
    ProjectManager(QObject *parent = 0);
    ~ProjectManager();

    Project* getProject();
    void loadProject(std::string fname);

    void saveProject();
    void saveProject(std::string fname);

    void projectSetUnSaved();
    void projectSetSaved();

    std::string getProjectPath();
    std::string getName();

    void newProject();
signals:
    void projectChanged();
    void projectContentChanged();
    void projectContentSaved();
private:
    std::string* projectPath;
    Project* project;

    void setProjectPath(std::string s);
    void setProject(Project *p);

    void writeCurve(Curve *c, QXmlStreamWriter *xw);
    void writeGraphOpts(GraphOpts *go, QXmlStreamWriter *xw);
    void writeAxis(Axis *axis, QXmlStreamWriter *xw);

    bool readCurve(QXmlStreamReader *xr, Project *pro);
    bool readGraphOpts(QXmlStreamReader *xr, Project *pro);
    bool readAxis(QXmlStreamReader *xr, Axes *ax);

};

#endif // PROJECTMANAGER_H
