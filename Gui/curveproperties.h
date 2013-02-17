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
#ifndef CURVEPROPERTIES_H
#define CURVEPROPERTIES_H

#include <QDockWidget>
#include <QMessageBox>
#include <QComboBox>
#include <QColorDialog>

#include "Data/project.h"
#include "Data/curve.h"

#include "Interfaces/icurveproperties.h"
#include "Interfaces/iprojectmanager.h"
#include "Interfaces/icurvesmanager.h"

#include "servicesprovider.h"

namespace Ui {
class CurveProperties;
}

class CurveProperties : public QDockWidget, public ICurveProperties
{
    Q_OBJECT
    Q_INTERFACES(ICurveProperties)
    
public:
    explicit CurveProperties(QWidget *parent = 0);
    ~CurveProperties();

    std::string getName();

public slots:
    void currentCurveIndexChanged(int id);

private slots:  
    void labelChnged();

    void commentChanged();
    void styleChanged(int id);

    void xAxisIdChanged(int id);
    void yAxisIdChanged(int id);

    void colorChange();
    void widthChanged(double w);

private:
    Ui::CurveProperties *ui;
    Curve *c;

    //-1 means no curve selected
    void reloadData(int curveId = -1);
    void loadCurve(Curve *c);
    void reloadAxis(QComboBox *cb,Axes *a);
};

#endif // CURVEPROPERTIES_H
