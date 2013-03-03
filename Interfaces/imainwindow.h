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
#ifndef IMAINWINDOW_H
#define IMAINWINDOW_H

#include <QtPlugin>
#include <QAction>

#include <map>
#include "iservice.h"

typedef std::map<std::string,QAction *> ActionsDict;
typedef std::pair<std::string,QAction *> ActionDictEntry;
/*!
 * \brief The IMainWindow class
 *interface for MainWindow as service
 */
class IMainWindow : public IService
{
public:
    /*!
     * \brief _show
     *shows main window
     */
    virtual void _show() = 0;
    /*!
     * \brief updateStatusBar
     *displays message in status bar
     * \param msg
     *message string
     * \param timeout
     *optional timeout in [ms]
     */
    virtual void updateStatusBar(std::string msg, int timeout = 0) = 0;
    /*!
     * \brief getActions
     *accessor for dictionary of actions (buttons, toggles, actions visible in menu, etc.)
     * \return
     *return dictionary of dctions
     */
    virtual ActionsDict *getActions() = 0;

signals:

public slots:
    /*!
     * \brief updateWindowTitle
     *updates windows caption
     */
    virtual void updateWindowTitle() = 0;

    virtual bool saveProject() = 0;
    virtual bool saveProjectAs() = 0;

    virtual void newProject() = 0;
    virtual void openProject() = 0;

};
Q_DECLARE_INTERFACE(IMainWindow,"og.IMainWindow/1.0")

#endif // IMAINWINDOW_H
