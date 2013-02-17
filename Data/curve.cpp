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
#include "curve.h"

Curve::Curve()
{
    this->data = new CurveData();
    this->label = new std::string("unnamed");
    this->comment = new std::string("");
    this->color = new std::string("#000000");

    this->width =1.;
    this->xAxisId=-1;
    this->yAxisId=-1;
    this->style = Curve::SolidLine;
    this->dataLabels = new CurveLabels(std::make_tuple(std::string(""),std::string(""),std::vector<std::string>()));

}

Curve::~Curve()
{
    delete this->label;
    delete this->color;

    this->data->erase(this->data->begin(),this->data->end());
    delete this->data;
}


CurveData *Curve::getData()
{
    return this->data;
}

Curve::LineStyles Curve::getStyle()
{
    return this->style;
}

void Curve::setStyle(Curve::LineStyles s)
{
    this->style = s;
}

double Curve::getWidth()
{
    return this->width;
}

void Curve::setWidth(double w)
{
    this->width = w;
}

std::string Curve::getColor()
{
    return (*this->color);
}

void Curve::setColor(std::string c)
{
    delete this->color;
    this->color = new std::string(c);
}

int Curve::getYAxisId()
{
    return this->yAxisId;
}

void Curve::setYAxisId(int id)
{
    this->yAxisId = id;
}

int Curve::getXAxisId()
{
    return this->xAxisId;
}

void Curve::setXAxisId(int id)
{
    this->xAxisId = id;
}

CurveLabels *Curve::getDataLabels()
{
    return this->dataLabels;
}

void Curve::setDataLabels(CurveLabels* cls)
{
    delete this->dataLabels;
    this-> dataLabels = cls;
}


void Curve::setLabel(std::string l)
{
    delete this->label;
    this->label = new std::string(l);
}

std::string Curve::getLabel()
{
    return (*this->label);
}

std::string Curve::getComment()
{
    return (*this->comment);
}

void Curve::setComment(std::string c)
{
    delete this->comment;
    this->comment = new std::string(c);
}
