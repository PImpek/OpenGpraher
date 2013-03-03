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
#include "mainwindow.h"

#include "ui_mainwindow.h"
#include "version.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    adict(new ActionsDict())
{
    ServicesProvider::getInstance()->registerService<IMainWindow>(this);

    ui->setupUi(this);

    this->initModules();
    this->initActions();
    this->connectUiElements();

    this->updateWindowTitle();
    this->updateStatusBar(std::string("Welcome in OpenGrapher")+ogGetVersion(),10000);
}

std::string MainWindow::getName()
{
    return std::string("MainWindowService");
}

void MainWindow::_show()
{
    this->show();
}

void MainWindow::updateStatusBar(std::string msg, int timeout)
{
    this->ui->statusBar->showMessage(QString(msg.c_str()),timeout);
}

ActionsDict *MainWindow::getActions()
{
    return this->adict;
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *ev)
{
    auto pm = ServicesProvider::getInstance()->getService<IProjectManager>();
    QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.setInformativeText("Do you want to save your changes?");

    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();

    ev->ignore();
    switch (ret) {
    case QMessageBox::Save:
        if (this->saveProject()) ev->accept();
        break;
    case QMessageBox::Discard:
        ev->accept();
        break;
    case QMessageBox::Cancel:
        break;
    default:
        // should never be reached
        break;
    }
}

void MainWindow::updateWindowTitle()
{
    IProjectManager *pm = ServicesProvider::getInstance()->getService<IProjectManager>();

    this->setWindowTitle(QString(std::string("Open Grapher-"+ogGetVersion()+" : "+
                                             pm->getProject()->getName()+
                                             ((pm->getProject()->isSaved())?"":"*")+
                                             " ["+pm->getProjectPath()+"]").c_str()));
}

bool MainWindow::saveProject()
{
    if (ServicesProvider::getInstance()->getService<IProjectManager>()->getProjectPath() == "")
        return this->saveProjectAs();

    ServicesProvider::getInstance()->getService<IProjectManager>()->saveProject();
    return true;
}

bool MainWindow::saveProjectAs()
{
    IProjectManager *pm = ServicesProvider::getInstance()->getService<IProjectManager>();
    QString fname =  QFileDialog::getSaveFileName(this,"Open Project from file",
                                                  QString(pm->getProjectPath().c_str()),
                                                  "OpenGrapherXML (*.ogx)");

    if (!fname.isNull())
    {
        pm->saveProject(fname.toUtf8().constData());
        return true;
    }
    return false;
}

void MainWindow::newProject()
{
    IProjectManager *pm = ServicesProvider::getInstance()->getService<IProjectManager>();
    if (!pm->getProject()->isSaved())
    {
        QMessageBox msgBox;
        msgBox.setText("The document has been modified.");
        msgBox.setInformativeText("Do you want to save your changes?");

        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();

        switch (ret) {
        case QMessageBox::Save:
            this->saveProject();
            break;
        case QMessageBox::Discard:
            break;
        case QMessageBox::Cancel:
            return;
            break;
        default:
            // should never be reached
            break;
        }
    }
    pm->newProject();
}

void MainWindow::openProject()
{
    QString fname;
    IProjectManager *pm = ServicesProvider::getInstance()->getService<IProjectManager>();
    if (!pm->getProject()->isSaved())
    {
        QMessageBox msgBox;
        msgBox.setText("Project has been modified.");
        msgBox.setInformativeText("Do you want to save your changes?");

        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();

        switch (ret) {
        case QMessageBox::Save:
            this->saveProject();
            break;
        case QMessageBox::Discard:
            break;
        case QMessageBox::Cancel:
            return;
            break;
        default:
            // should never be reached
            break;
        }
    }
    fname  = QFileDialog::getOpenFileName(this,"Open Project",QString(),
                                          "OpenGrapherXML (*.ogx)");
    if (!fname.isNull())
        pm->loadProject(fname.toUtf8().constData());
}


void MainWindow::initModules()
{
    auto cm = new CurvesManager(this);
    this->addDockWidget(Qt::RightDockWidgetArea,cm);

    auto cp = new CurveProperties(this);
    this->addDockWidget(Qt::RightDockWidgetArea,cp);

    auto go = new GraphOptions(this);
    this->addDockWidget(Qt::LeftDockWidgetArea,go);

}

void MainWindow::initActions()
{

    //file
    auto newFile = new QAction("New Project ...",this);
    newFile->setShortcutContext(Qt::ApplicationShortcut);
    newFile->setShortcut(QKeySequence("Ctrl+N"));

    this->ui->menu_File->addAction(newFile);
    this->getActions()->insert(ActionDictEntry("newProject", newFile));
    this->connect(newFile,SIGNAL(triggered()),this,SLOT(newProject()));

    auto openFile = new QAction("Open Project ...",this);
    openFile->setShortcutContext(Qt::ApplicationShortcut);
    openFile->setShortcut(QKeySequence("Ctrl+O"));

    this->ui->menu_File->addAction(openFile);
    this->getActions()->insert(ActionDictEntry("openProject", openFile));
    this->connect(openFile,SIGNAL(triggered()),this,SLOT(openProject()));

    this->ui->menu_File->addSeparator();

    auto saveFile = new QAction("Save Project ...",this);
    saveFile->setShortcutContext(Qt::ApplicationShortcut);
    saveFile->setShortcut(QKeySequence("Ctrl+S"));

    this->ui->menu_File->addAction(saveFile);
    this->getActions()->insert(ActionDictEntry("saveProject", saveFile));
    this->connect(saveFile,SIGNAL(triggered()),this,SLOT(saveProject()));

    auto saveFileAs = new QAction("Save Project as ...",this);
    saveFileAs->setShortcutContext(Qt::ApplicationShortcut);
    saveFileAs->setShortcut(QKeySequence("Ctrl+Shift+S"));

    this->ui->menu_File->addAction(saveFileAs);
    this->getActions()->insert(ActionDictEntry("saveProjectAs", saveFileAs));
    this->connect(saveFileAs,SIGNAL(triggered()),this,SLOT(saveProjectAs()));

    this->ui->menu_File->addSeparator();

    auto exit = new QAction("Close",this);
    this->ui->menu_File->addAction(exit);

    this->getActions()->insert(ActionDictEntry("exit", exit));
    this->connect(exit,SIGNAL(triggered()),this,SLOT(close()));




    //edit
    //tools
    //window
    auto cm = dynamic_cast<QDockWidget *>(ServicesProvider::getInstance()->getServiceAsQ<ICurvesManager>());
    this->ui->menu_Window->addAction(cm->toggleViewAction());
    this->getActions()->insert(ActionDictEntry("CurvesManager", cm->toggleViewAction()));

    auto cp = dynamic_cast<QDockWidget *>(ServicesProvider::getInstance()->getServiceAsQ<ICurveProperties>());
    this->ui->menu_Window->addAction(cp->toggleViewAction());

    this->getActions()->insert(ActionDictEntry("CurveProperties", cp->toggleViewAction()));

    auto go = dynamic_cast<QDockWidget *>(ServicesProvider::getInstance()->getServiceAsQ<IGraphOptions>());
    this->ui->menu_Window->addAction(go->toggleViewAction());
    this->getActions()->insert(ActionDictEntry("GraphOptions", go->toggleViewAction()));


    //about
}

void MainWindow::connectUiElements()
{
    auto pm = ServicesProvider::getInstance()->getServiceAsQ<IProjectManager>();
    auto cm = ServicesProvider::getInstance()->getServiceAsQ<ICurvesManager>();

    auto cp = ServicesProvider::getInstance()->getServiceAsQ<ICurveProperties>();
    auto go = ServicesProvider::getInstance()->getServiceAsQ<IGraphOptions>();
    // after reloading or editing project, refresh view
    this->connect(pm,SIGNAL(projectChanged()),cm,SLOT(refresh()));
    this->connect(pm,SIGNAL(projectContentChanged()),cm,SLOT(refresh()));
    this->connect(pm,SIGNAL(projectContentChanged()),go,SLOT(refresh()));
    this->connect(pm,SIGNAL(projectChanged()),go,SLOT(refresh()));
    // after changing selected curve on curvesamanager, rebind new curve;
    this->connect(cm,SIGNAL(selectionChanged(int)),cp,SLOT(currentCurveIndexChanged(int)));
    // after reloading or editing project, update title in main window
    this->connect(pm,SIGNAL(projectChanged()),this,SLOT(updateWindowTitle()));
    this->connect(pm,SIGNAL(projectContentChanged()),this,SLOT(updateWindowTitle()));

}
