#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <qvariant.h>
#include <qmainwindow.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qaction.h>
#include <qmenubar.h>
#include <QMenu>
#include <QCloseEvent>
#include <qtoolbar.h>
#include <qimage.h>
#include <qpixmap.h>
#include <qstatusbar.h> 
#include <qmessagebox.h>
#include "RTDisplay.h"
#include "Preview.h"
#include "QmyToolBar.h"
// #include "qcustomevent.h"


class MainFrame : public QMainWindow
{
    Q_OBJECT

public:
    MainFrame( QWidget * parent = 0);
    virtual ~MainFrame();

    QmyToolBar *toolBar;
	CRTDisplay *pDisplay;
	CPreview   *pPreview;


    const static QEvent::Type STOP				=	static_cast<QEvent::Type>(QEvent::User+1);
    const static QEvent::Type SETTEXT			=	static_cast<QEvent::Type>(QEvent::User+2);
    const static QEvent::Type ExpandVert		=	static_cast<QEvent::Type>(QEvent::User+3);
    const static QEvent::Type ContractVert	    =	static_cast<QEvent::Type>(QEvent::User+4);
    const static QEvent::Type ShiftUp			=	static_cast<QEvent::Type>(QEvent::User+5);
    const static QEvent::Type ShiftDown		    =	static_cast<QEvent::Type>(QEvent::User+6);


	void  SetTextToStatusbar(const char *pText);
private:
	int nTimerCount;
	int nPreviewHeight;

signals:
    void drawPreviewSignal();
    void autoScaleSignal(int);
    void contractVertSignal();
    void expandVertSignal();
    void shiftUpDownSignal(int );


public slots:
    virtual void helpIndex();
    virtual void helpContents();
    virtual void helpAbout();
    virtual void configButton_clicked();
    virtual void newSlot();
    virtual void runButton_clicked();
	virtual void autoButton_clicked();
	virtual void autoButton1_clicked();
    virtual void autoButton2_clicked();
	virtual void expandButton_clicked();
	virtual void contractButton_clicked();
	virtual void upButton_clicked();
	virtual void downButton_clicked();
	virtual void exitButton_clicked();
	virtual void stopButton_clicked();
	virtual void aboutButton_clicked();
    virtual void disableToolbarSlot(bool);
    virtual void SetTextToStatusbarSlot(QString s);
    virtual void drawPreviewSlot();
    virtual void stopSlot();
    virtual void beforeQuitCRTD();

protected:
    virtual void  resizeEvent( QResizeEvent * );
    bool eventFilter(QObject *obj, QEvent *event);
    void mousePressEvent ( QMouseEvent * e );

protected slots:
    virtual void languageChange();

};

#endif // MAINFRAME_H
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
