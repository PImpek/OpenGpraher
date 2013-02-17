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
#include "graphopts.h"

GraphOpts::GraphOpts()
{
    this->title = new std::string("unnamed project");
    this->showLegend = false;
    this->legendPosition = new Point(0.5,0.5);

    this->titleSize = 20;
    this->legendSize = 12;
    this->curveLabelSize = 12;

    this->XAxes = new Axes();
    this->YAxes = new Axes();
}

GraphOpts::~GraphOpts()
{
    delete this->title;
    delete this->legendPosition;

    this->XAxes->erase(this->XAxes->begin(), this->XAxes->end());
    this->YAxes->erase(this->YAxes->begin(), this->YAxes->end());

    delete this->XAxes;
    delete this->YAxes;

}

std::string GraphOpts::getTitle()
{
    return (*this->title);
}

void GraphOpts::setTitle(std::string t)
{
    delete this->title;
    this->title = new std::string(t);
}

bool GraphOpts::isShowLegend()
{
    return this->showLegend;
}

void GraphOpts::setShowLegend(bool s)
{
    this->showLegend = s;
}

int GraphOpts::getTitleSize()
{
    return this->titleSize;
}

void GraphOpts::setTitleSize(int s)
{
    this->titleSize =s;
}

int GraphOpts::getCurveLabelSize()
{
    return this->curveLabelSize;
}


void GraphOpts::setCurveLabelSize(int s)
{
    this->curveLabelSize = s;
}

int GraphOpts::getLegendSize()
{
    return this->legendSize;
}

void GraphOpts::setLegendSize(int s)
{
    this->legendSize = s;
}

Point GraphOpts::getLegendPosition()
{
    return (*this->legendPosition);
}

void GraphOpts::setLegendPosition(Point p)
{
    std::get<0>((*this->legendPosition)) = std::get<0>(p);
    std::get<1>((*this->legendPosition)) = std::get<1>(p);

}

Axes *GraphOpts::getXAxes()
{
    return this->XAxes;
}

Axes *GraphOpts::getYAxes()
{
    return this->YAxes;
}
