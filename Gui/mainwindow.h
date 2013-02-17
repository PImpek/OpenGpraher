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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QFileDialog>

#include "Interfaces/imainwindow.h"
#include "Interfaces/icurvesmanager.h"
#include "Interfaces/icurveproperties.h"

#include "Gui/curvesmanager.h"
#include "Gui/curveproperties.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public IMainWindow
{
    Q_OBJECT
    Q_INTERFACES(IMainWindow)
    
public:
    explicit MainWindow(QWidget *parent = 0);

    std::string getName();
    void _show();

    void updateStatusBar(std::string msg, int timeout = 0);
    ActionsDict *getActions();

    ~MainWindow();

public slots:
    void updateWindowTitle();
    void saveProject();
    void saveProjectAs();

    void newProject();
    void openProject();

    void closeApp();

private:
    Ui::MainWindow *ui;
    ActionsDict *adict;

    void initModules();
    void initActions();

    void connectUiElements();
};

#endif // MAINWINDOW_H
