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
#ifndef ICURVESMANAGER_H
#define ICURVESMANAGER_H

#include <QtPlugin>

#include "Interfaces/iservice.h"
/*!
 * \brief The ICurvesManager class
 *interface for curves list dock
 */
class ICurvesManager : public IService
{
public:
    /*!
     * \brief refreshCurves
     *realoads list
     */
    virtual void refreshCurves() = 0;
    /*!
     * \brief getSelectionId
     * gets index of selected curve
     * \return
     *index of selected curve or -1 when no curve is selected
     */
    virtual int getSelectionId() = 0;

signals:
    /*!
     * \brief selectionChanged
     *sends a signal when new curve was selected
     * \param id
     *index of selected curve or -1 when no curve is selected
     */
    virtual void selectionChanged(int id) = 0;

public slots:
    /*!
     * \brief refresh
     *this slot handles update ui request
     */
    virtual void refresh() = 0;

};
Q_DECLARE_INTERFACE(ICurvesManager,"og.ICurvesManager/1.0")

#endif // ICURVESMANAGER_H
