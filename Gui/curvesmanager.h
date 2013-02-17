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
#ifndef CURVESMANAGER_H
#define CURVESMANAGER_H

#include <QDockWidget>

#include "servicesprovider.h"

#include "Interfaces/iprojectmanager.h"
#include "Interfaces/icurvesmanager.h"

#include "Data/project.h"
#include "Data/curve.h"


namespace Ui {
class CurvesManager;
}

class CurvesManager : public QDockWidget, public ICurvesManager
{
    Q_OBJECT
    Q_INTERFACES(ICurvesManager)
    
public:
    explicit CurvesManager(QWidget *parent = 0);
    ~CurvesManager();

    std::string getName();
    void refreshCurves();

    int getSelectionId();

signals:
    void selectionChanged(int id);

public slots:
    void refresh();

private slots:
    void listSelectionChanged(int id);

private:
    Ui::CurvesManager *ui;

};

#endif // CURVESMANAGER_H