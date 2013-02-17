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
#ifndef IPROJECTMANAGER_H
#define IPROJECTMANAGER_H

#include <iostream>
#include <QtPlugin>

#include "Interfaces/iservice.h"
#include "Data/project.h"

/*!
 * \brief The IProjectManager class
 *interface of ProjectManager service
 */
class IProjectManager : public IService
{
public:
    /*!
     * \brief getProject
     * this method allow no access to Project
     * \return
     *returns pointer to instance of current project
     */
    virtual Project* getProject() = 0;
    /*!
     * \brief loadProject
     *loads projects stored in .ogx format and emits projectChanged
     * \param fname
     *path to file
     */
    virtual void loadProject(std::string fname) = 0;
    /*!
     * \brief saveProject
     *saves current project at its origin path
     */
    virtual void saveProject() = 0;
    /*!
     * \brief saveProject
     *saves current project at path and emits projectContentSaved
     * \param fname
     *path to file
     */
    virtual void saveProject(std::string fname) = 0;
    /*!
     * \brief getProjectPath
     * getter for path to project
     * \return
     *path to file or "" when paroject was not saved eariel
     */
    virtual std::string getProjectPath() = 0;
    /*!
     * \brief projectSetUnSaved
     *marks project as unsaved and emits projectContentChanged
     */
    virtual void projectSetUnSaved() = 0;
    /*!
     * \brief projectSetSaved
     *marks project as saved and emits projectContentChanged
     */
    virtual void projectSetSaved() = 0;
    virtual void newProject() = 0;
signals:
    /*!
     * \brief projectChanged
     *signal emited after reloading new project
     */
    virtual void projectChanged() = 0;
    /*!
     * \brief projectContentChanged
     *signal emited after changes in project
     */
    virtual void projectContentChanged() = 0;
    /*!
     * \brief projectContentSaved
     *signal emited after saving a project
     */
    virtual void projectContentSaved() = 0;

public slots:

};
Q_DECLARE_INTERFACE(IProjectManager,"og.IProjectManager/1.0")

#endif // IPROJECTMANAGER_H
