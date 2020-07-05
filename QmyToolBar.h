#pragma "$Id$"
// QmyToolBar.h: interface for the QmyToolBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QMYTOOLBAR_H__04886BF5_5119_4557_85D1_F7422A3FB341__INCLUDED_)
#define AFX_QMYTOOLBAR_H__04886BF5_5119_4557_85D1_F7422A3FB341__INCLUDED_

#include <qwidget.h>
#include <qstring.h>
#include <qtoolbar.h>
#include <QPushButton>
#include <QPixmap>
#include <QAction>
#include <QToolButton>

class QmyToolBar : public QToolBar  
{
public:
    QmyToolBar( QWidget * parent );
	virtual ~QmyToolBar();
    QAction     *m_ActionRunButton;
    QAction     *m_ActionConfigButton;
    QAction     *m_ActionStopButton;
    QAction     *m_ActionAutoFitButton;
    QAction     *m_ActionAutoButton;
    QAction     *m_ActionAutoButton1;
    QAction     *m_ActionExpandButton;
    QAction     *m_ActionContractButton;
    QAction     *m_ActionUpButton;
    QAction     *m_ActionDownButton;
    QAction     *m_ActionAboutButton;

    QToolButton * runButton;
    QToolButton * configButton;
    QToolButton * aboutButton;

    QToolButton * autoButton;
    QToolButton * autoButton1;
    QToolButton * autoButton2;
    QToolButton * stopButton;
    QToolButton * expandButton;
    QToolButton * contractButton;
    QToolButton * upButton;
    QToolButton * downButton;
	void SetToolbarState(int nState);
	void languageChange();
    bool isAutofitOn();

};

#endif // !defined(AFX_QMYTOOLBAR_H__04886BF5_5119_4557_85D1_F7422A3FB341__INCLUDED_)
/*-----------------------------------------------------------------------+
 |                                                                       |
 | Copyright (C) 2016 Regents of the University of California            |
 |                                                                       |
 | This software is provided 'as-is', without any express or implied     |
 | warranty.  In no event will the authors be held liable for any        |
 | damages arising from the use of this software.                        |
 |                                                                       |
 | Permission is granted to anyone to use this software for any purpose, |
 | including commercial applications, and to alter it and redistribute   |
 | it freely, subject to the following restrictions:                     |
 |                                                                       |
 | 1. The origin of this software must not be misrepresented; you must   |
 |    not claim that you wrote the original software. If you use this    |
 |    software in a product, an acknowledgment in the product            |
 |    documentation of the contribution by Project IDA, UCSD would be    |
 |    appreciated but is not required.                                   |
 | 2. Altered source versions must be plainly marked as such, and must   |
 |    not be misrepresented as being the original software.              |
 | 3. This notice may not be removed or altered from any source          |
 |    distribution.                                                      |
 |                                                                       |
 +-----------------------------------------------------------------------*/
/* Revision History
 *
 * $Log$
 */
