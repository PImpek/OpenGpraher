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
#include "csvimporttool.h"

CsvImportTool::CsvImportTool(QObject *parent) :
    ITool(parent)
{
    this->setIcon(QIcon(":/Resources/text-csv.png"));
    this->setToolTip("Import curve from CVS file...");
}

void CsvImportTool::actionHandler()
{
    auto dial = new AddCurveDialog(dynamic_cast<QWidget *>(this->parent()));
    dial->setModal(true);
    dial->exec();

    auto curve = dial->getCurve();
    if (dial->result() == QDialog::Accepted && curve != nullptr)
    {
       std::vector<Curve*> * crvs = ServicesProvider::getInstance()->getService<IProjectManager>()->getProject()->getCurves();
       crvs->push_back(curve);
       ServicesProvider::getInstance()->getService<IProjectManager>()->projectSetUnSaved();
       ServicesProvider::getInstance()->getService<ICurvesManager>()->setSelectionId(crvs->size()-1);
    }
}
