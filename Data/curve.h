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
#ifndef CURVE_H
#define CURVE_H

#include <iostream>
#include <vector>
#include <tuple>

typedef std::vector< std::tuple< double , double, std::vector< double > > > CurveData;
typedef std::tuple< std::string , std::string, std::vector< std::string > > CurveLabels;
/*!
 * \brief The Curve class
 *container for informations about curves
 */
class Curve
{
public:
    /*!
     * \brief The LineStyles enum
     *avaliable line styles
     *- NoLine - no line
     *- PointsOnly - only data points
     *- SolidLine: (-)* line
     *- DashLine: (- )* line
     *- DotLine: (. )* line
     *- DashDotLine: (-.)* line
     *- DashDotDotLine: (-..)* line
     */
    enum LineStyles{
        NoLine,
        PointsOlny,
        SolidLine,
        DashLine,
        DotLine,
        DashDotLine,
        DashDotDotLine
    };

    Curve();
    ~Curve();
    /*!
     * \brief getLabel
     * label property getter
     *\return
     *label of curve
     */
    std::string getLabel();
    void setLabel(std::string l);
    /*!
     * \brief getComment
     * comment property getter
     *\return
     *curve comment
     */
    std::string getComment();
    void setComment(std::string c);
    /*!
     * \brief getData
     * data property getter
     *\return
     *data of curve as pointer to list of std::tuple< double - Y value,
     *                                                double - X value,
     *                                                std::vector< double > - optional measurements >
     */
    CurveData* getData();

    /*!
     * \brief getCo
     * style property getter
     *\return
     *style of curve
     */
    LineStyles getStyle();
    void setStyle(LineStyles s);
    /*!
     * \brief getWidth
     * comment property getter
     *\return
     *width of curve
     */
    double getWidth();
    void setWidth(double w);
    /*!
     * \brief getColor
     *color property getter
     * \return
     *color in HEX format
     */
    std::string getColor();
    void setColor(std::string c);
    /*!
     * \brief getYAxisId
     *yAxisId property getter
     * \return
     *index of Y axis to use or -1 when no axe is tied
     */
    int getYAxisId();

    void setYAxisId(int id);
    /*!
     * \brief getXAxisId
     *xAxisId property getter
     * \return
     *index of X Axis to use or -1 when no axis is tied
     */
    int getXAxisId();
    void setXAxisId(int id);
    /*!
     * \brief getDataLabels
     *dataLabels property getter
     * \return
     * tuple of labels, see getData
     */
    CurveLabels* getDataLabels();
    void setDataLabels(CurveLabels *cls);

private:
    std::string* label;
    std::string* comment;
    CurveData* data;
    CurveLabels* dataLabels;

    int xAxisId;
    int yAxisId;


    LineStyles style;
    double width;
    std::string* color;

};

#endif // CURVE_H
