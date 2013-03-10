/* Copyright (c) 2013, Bartosz Foder, (bartosz@foder.pl)
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
#include "actionloader.h"
#include "ui_mainwindow.h"

#include "Modules/csv_import/csvimporttool.h"

ActionLoader::ActionLoader(QMainWindow *par):
    parent(par)
{
    //intiialize toolboxes
    auto newToolbar = new QToolBar("New curve toolbar",this->parent);
    this->initializeNewToolBar(newToolbar);

    parent->addToolBar(Qt::TopToolBarArea,newToolbar);
    ((MainWindow *)parent)->ui->menu_Window->addAction(newToolbar->toggleViewAction());

    auto editToolbar = new QToolBar("Edit curve toolbar",this->parent);
    this->initializeEditToolBar(editToolbar);

    parent->addToolBar(editToolbar);
    ((MainWindow *)parent)->ui->menu_Window->addAction(editToolbar->toggleViewAction());
}

void ActionLoader::initializeNewToolBar(QToolBar *tb)
{
    this->addTool(new CsvImportTool(this->parent),tb);
}

void ActionLoader::initializeEditToolBar(QToolBar *tb)
{
}

void ActionLoader::addTool(ITool *tool,QToolBar *tb)
{
    tb->addAction(tool);
    tool->connect(tool,SIGNAL(triggered()),tool,SLOT(actionHandler()));
}
