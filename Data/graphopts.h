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
#ifndef GRAPHOPTS_H
#define GRAPHOPTS_H

#include <iostream>
#include <vector>
#include <tuple>

typedef std::tuple< double, double > Point;
//tuple contains axis description : min, max, label,logarithmic, side(0-left/down, 1-right/up)
typedef std::tuple< double, double, std::string, bool, bool > Axis;
typedef std::vector< Axis *> Axes;
class GraphOpts
{
public:
    GraphOpts();
    ~GraphOpts();

    std::string getTitle();
    void setTitle(std::string t);

    bool isShowLegend();
    void setShowLegend(bool s);

    int getTitleSize();
    void setTitleSize(int s);

    int getCurveLabelSize();
    void setCurveLabelSize(int s);

    int getLegendSize();
    void setLegendSize(int s);

    Point getLegendPosition();
    void setLegendPosition(Point p);

    Axes* getXAxes();
    Axes* getYAxes();
private:
    std::string* title;
    bool showLegend;

    Point* legendPosition;
    int titleSize;
    int curveLabelSize;
    int legendSize;
    Axes* XAxes;
    Axes* YAxes;
};

#endif // GRAPHOPTS_H
