#pragma "$Id$"

// QmyToolBar.cpp: implementation of the QmyToolBar class.
//
//////////////////////////////////////////////////////////////////////

#include <qtooltip.h>
#include "QmyToolBar.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

QmyToolBar::QmyToolBar(QWidget * parent ):QToolBar( parent )
	{
    qDebug("QmyToolBar::QmyToolBar");

    this->setStyleSheet("QToolBar {background-color: lightgray;}");

    setFloatable(true);
//    QAction     *m_ActionConfigButton;
//    QAction     *m_ActionStopButton;



    runButton = new QToolButton( this );
    runButton->setIcon( QIcon( ":/images/run.ico" ) );
    runButton->setFixedSize( 48, 48 );
    m_ActionRunButton = addWidget( runButton );

    stopButton = new QToolButton( this );
    stopButton->setFixedSize( 48, 48 );
    stopButton->setIcon( QIcon( ":/images/stop.ico" ) );
    m_ActionStopButton = addWidget( stopButton );


    configButton = new QToolButton( this);
    configButton->setIcon( QPixmap( ":/images/tool.ico" ) );
    configButton->setFixedSize( 48, 48 );
    m_ActionConfigButton = addWidget( configButton );


    autoButton = new QToolButton( this );
    autoButton->setFixedSize( 48, 48 );
    autoButton->setIcon( QPixmap( ":/images/fit.png" ) );
    m_ActionAutoButton = addWidget( autoButton );

    autoButton1 = new QToolButton( this );
    autoButton1->setFixedSize( 48, 48 );
    autoButton1->setIcon( QPixmap( ":/images/autoscale1.bmp" ) );
    m_ActionAutoButton1 = addWidget( autoButton1 );

    autoButton2 = new QToolButton( this );
    autoButton2->setFixedSize( 48, 48 );
    autoButton2->setCheckable(true);
    autoButton2->setChecked(true);
    autoButton2->setIcon( QPixmap( ":/images/autofit.ico" ) );
    m_ActionAutoFitButton = addWidget( autoButton2 );

    expandButton = new QToolButton( this );
    expandButton->setFixedSize( 48, 48 );
    expandButton->setIcon( QPixmap( ":/images/zoom_in.ico" ) );
    m_ActionExpandButton = addWidget(expandButton);
	
    contractButton = new QToolButton( this );
    contractButton->setFixedSize( 48, 48);
    contractButton->setIcon( QPixmap( ":/images/zoom_out.ico" ) );
    m_ActionContractButton = addWidget( contractButton );


    upButton = new QToolButton( this );
    upButton->setFixedSize( 48, 48);
    upButton->setIcon( QPixmap( ":/images/up.ico" ) );
    m_ActionUpButton = addWidget( upButton );
	
    downButton = new QToolButton( this );
    downButton->setFixedSize( 48, 48);
    downButton->setIcon( QPixmap( ":/images/down.ico" ) );
    m_ActionDownButton = addWidget( downButton );


    aboutButton = new QToolButton( this );
    aboutButton->setFixedSize( 48, 48);
    aboutButton->setIcon( QPixmap( ":/images/info.ico" ) );
    m_ActionAboutButton = addWidget( aboutButton );



    connect( configButton, SIGNAL( clicked() ), parent, SLOT( configButton_clicked() ) );
    connect( runButton, SIGNAL( clicked() ), parent, SLOT( runButton_clicked() ) );
	connect( autoButton, SIGNAL( clicked() ), parent, SLOT( autoButton_clicked() ) );
    connect( autoButton1, SIGNAL( clicked() ), parent, SLOT( autoButton1_clicked() ) );
    connect( autoButton2, SIGNAL( clicked() ), parent, SLOT( autoButton2_clicked() ) );

	connect( expandButton, SIGNAL( clicked() ), parent, SLOT( expandButton_clicked() ) );
	connect( contractButton, SIGNAL( clicked() ), parent, SLOT( contractButton_clicked() ) );
	connect( upButton, SIGNAL( clicked() ), parent, SLOT( upButton_clicked() ) );
	connect( downButton, SIGNAL( clicked() ), parent, SLOT( downButton_clicked() ) );
	connect( stopButton, SIGNAL( clicked() ), parent, SLOT( stopButton_clicked() ) );
	connect( aboutButton, SIGNAL( clicked() ), parent, SLOT( aboutButton_clicked() ) );

	}

QmyToolBar::~QmyToolBar()
	{

	}
void QmyToolBar::SetToolbarState(int nState)
	{
	if(nState==0)
    {
        m_ActionRunButton->setVisible(true);
        m_ActionConfigButton->setVisible(true);
        m_ActionStopButton->setVisible(false);
        m_ActionAboutButton->setVisible(true);

        m_ActionAutoButton->setVisible(false);
        m_ActionAutoButton1->setVisible(false);
        m_ActionAutoFitButton->setVisible(false);
        m_ActionStopButton->setVisible(false);
        m_ActionExpandButton->setVisible(false);
        m_ActionContractButton->setVisible(false);
        m_ActionUpButton->setVisible(false);
        m_ActionDownButton->setVisible(false);
		adjustSize ();
		return;
    }

	if(nState==1)
    {
        m_ActionRunButton->setVisible(false);
        m_ActionConfigButton->setVisible(false);
        m_ActionStopButton->setVisible(true);

        m_ActionAboutButton->setVisible(false);

        m_ActionAutoButton->setVisible(true);
        m_ActionAutoButton1->setVisible(true);
        m_ActionAutoFitButton->setVisible(true);
        m_ActionStopButton->setVisible(true);
        m_ActionExpandButton->setVisible(true);
        m_ActionContractButton->setVisible(true);
        m_ActionUpButton->setVisible(true);
        m_ActionDownButton->setVisible(true);

        adjustSize();
		return;
    }

	if(nState==2)
    {
        m_ActionRunButton->setVisible(false);
        m_ActionConfigButton->setVisible(false);
        m_ActionStopButton->setVisible(false);
		autoButton->hide();
		autoButton1->hide();
		stopButton->hide();
        m_ActionAutoFitButton->setVisible(false);
		expandButton->hide();
		contractButton->hide();
		upButton->hide();
		downButton->hide();
		adjustSize();
		return;
    }

}
void QmyToolBar::languageChange()
	{
//   setLabel( tr( "Tools" ) );
    setToolTip("Tools");
    runButton->setText( QString::null );
    runButton->setToolTip( tr( "Run", "Run" ) );
    configButton->setText( QString::null );
    configButton->setToolTip( tr( "Config", "Config" ) );
    aboutButton->setText( QString::null );
    autoButton->setToolTip( tr( "Fit displayed signal data to window", "Fit displayed signal data to window" ) );
    aboutButton->setToolTip( tr( "About", "About" ) );
    autoButton1->setToolTip( tr("Fit buffered signal data to window","Fit buffered signal data to window"));
    autoButton2->setToolTip( tr("Auto scale","Auto scale"));

    expandButton->setToolTip( tr( "Expand vertical", "Expand vertical" ) );
    contractButton->setToolTip( tr( "Contract vertical", "Contract vertical" ) );
    contractButton->setToolTip( tr( "Contract vertical", "Contract vertical" ) );
    downButton->setToolTip( tr( "Shift graph down", "Shift graph down" ) );
    upButton->setToolTip( tr( "Shift graph up", "Shift graph up" ) );
    stopButton->setToolTip( tr( "Stop", "Stop" ) );
	
	
	}
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
	
