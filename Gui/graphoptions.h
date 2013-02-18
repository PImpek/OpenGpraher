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
#ifndef GRAPHOPTIONS_H
#define GRAPHOPTIONS_H

#include <QDockWidget>

#include "servicesprovider.h"
#include "Interfaces/igraphoptions.h"
#include "Interfaces/iprojectmanager.h"

namespace Ui {
class GraphOptions;
}

class GraphOptions : public QDockWidget, public IGraphOptions
{
    Q_INTERFACES(IGraphOptions)
    Q_OBJECT
    
public:
    explicit GraphOptions(QWidget *parent = 0);
    ~GraphOptions();
    
    std::string getName();
    void refreshContent();

public slots:
    void refresh();

private slots:
    void titleChanged();
    void titleSizeChanged(int s);

    void showLegendChanged(bool s);
    void legendSizeChanged(int s);

    void curvesSizeChanged(int s);

private:
    Ui::GraphOptions *ui;
};

#endif // GRAPHOPTIONS_H
