#include <qapplication.h>
//#include <qvariant.h>
//#include <qpushbutton.h>
//#include <qlayout.h>
//#include <qtooltip.h>
//#include <qwhatsthis.h>
//#include <qaction.h>
//#include <qmenubar.h>
//#include <QMenu>
//#include <qtoolbar.h>
//#include <qimage.h>
//#include <qpixmap.h>
//#include <qstatusbar.h>
//#include <qmessagebox.h>
//#include <qfont.h>
//#include <QMouseEvent>
#include "set_all_parameters.h"
#include "CRTDglob.h"
#include "MainFrame.h"


void StartAcquisition(MainFrame *p);

/*
 *  Constructs a MainFrame as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 */
MainFrame::MainFrame( QWidget* parent) : QMainWindow( parent)
{
    (void)statusBar();

    setWindowFlags(Qt::Window | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint| Qt::WindowCloseButtonHint);

    nPreviewHeight = 35;

    // toolbars
    toolBar = new QmyToolBar( this);
    toolBar->setWindowFlags(Qt::Tool | Qt::WindowCloseButtonHint); toolBar->show();
    //    toolBar->setMovingEnabled( FALSE );
    toolBar->addSeparator();
    //    toolBar->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);

    pDisplay = new CRTDisplay(this);
    pDisplay->show();

    pPreview = new CPreview(pDisplay, this);
    pPreview->show();

    connect(this, SIGNAL(drawPreviewSignal()), pPreview, SLOT(drawPreviewSlot()) );
    connect(this, SIGNAL(autoScaleSignal(int )), pDisplay, SLOT(autoScaleSlot(int )) );
    connect(this, SIGNAL(contractVertSignal()), pDisplay, SLOT(contractVertSlot()) );
    connect(this, SIGNAL(expandVertSignal()), pDisplay, SLOT(expandVertSlot()) );
    connect(this, SIGNAL(shiftUpDownSignal(int )), pDisplay, SLOT(shiftUpDownSlot(int )) );

    toolBar->SetToolbarState(0);
    languageChange();
    resize( QSize(600, 480).expandedTo(minimumSizeHint()) );
    installEventFilter(this);
    pDisplay->installEventFilter(this);
    setMouseTracking(true);
}

/*
 *  Destroys the object and frees any allocated resources
 */
MainFrame::~MainFrame()
{
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void MainFrame::languageChange()
{
    this->setWindowTitle(tr( "CRTD QT(ISI)" ));
    toolBar->languageChange();
}

void MainFrame::helpIndex()
{
}

void MainFrame::helpContents()
{
}

void MainFrame::helpAbout()
{
}

void MainFrame::configButton_clicked()
{
    Set_All_Parameters SAL(this);
    SAL.exec();
}

void MainFrame::newSlot()
{
}


void MainFrame::runButton_clicked()
{
    if(NrtsInfo.GetSelectedChanNumber()==0)
    {
        QMessageBox mb("ERROR","No channels selected",QMessageBox::Critical, QMessageBox::Ok, int(NULL), int(NULL));
        mb.exec();
        return;
    }
    toolBar->SetToolbarState(1);
    pDisplay->Run();
    StartAcquisition(this);
    nTimerCount=0;
}

void MainFrame::autoButton_clicked()
{
    emit autoScaleSignal(0);
}

void MainFrame::autoButton1_clicked()
{
    autoScaleSignal(1);
}

void MainFrame::autoButton2_clicked()
{
    bool b = toolBar->autoButton2->isChecked();
    pDisplay->setAutoScaleFlag(b);
}

void MainFrame::expandButton_clicked()
{
    emit expandVertSignal();
}

void MainFrame::contractButton_clicked()
{
    emit contractVertSignal();
}

void MainFrame::upButton_clicked()
{
    emit shiftUpDownSignal(0);
}

void MainFrame::downButton_clicked()
{
    emit shiftUpDownSignal(1);
}

void MainFrame::aboutButton_clicked()
{
    QMessageBox::about(this,"About CRTDQT(ISI)","CRTD Version 1.0.1. Project IDA\nBuild 2018-08-02\nCopyright (C) 2016, 2017, 2018 University of California, San Diego");
}

void  MainFrame::resizeEvent( QResizeEvent *q )
{
    QStatusBar *pStatusB;
    QRect qzt, qzs, qz, rc;
    int sbH, tbH;

    rc = rect();

    qzt=toolBar->frameGeometry();
    pStatusB = statusBar();

    qzs=pStatusB->frameGeometry();

    sbH=qzs.height();
    //	tbH=qzt.height();
    tbH = 0;

    qz = rc;
    qz.setTop(tbH+1);
    qz.setBottom(rc.bottom()-sbH-nPreviewHeight);
    pDisplay->setGeometry(qz);

    qz.setTop(rc.bottom()-sbH-nPreviewHeight);
    qz.setBottom(rc.bottom()-sbH);
    pPreview->setGeometry(qz);

}

void  MainFrame::SetTextToStatusbar(const char *pText)
{
    QStatusBar *pStatusB;
    pStatusB = statusBar();
    pStatusB->showMessage(pText);
}

void MainFrame::exitButton_clicked()
{
    QApplication::exit();
}

void StopAcquisition(MainFrame *p);

void MainFrame::stopButton_clicked()
{
    StopAcquisition(this);
}

bool MainFrame::eventFilter(QObject *obj, QEvent *event)
{
    if(pDisplay == obj)
    {
        if(event->type()==QEvent::MouseButtonPress)
        {
            QMouseEvent *me = static_cast<QMouseEvent *>(event);
            if(me->button()==Qt::RightButton)
            {
                if(toolBar->isVisible()) toolBar->hide(); else toolBar->show();
            }

        }
        return false;
    }

    return false;

}

void MainFrame::mousePressEvent( QMouseEvent * e )
{
    if( e->button()==Qt::RightButton)
    {
        if(toolBar->isVisible()) toolBar->hide(); else toolBar->show();
    }
}

void MainFrame::disableToolbarSlot(bool b)
{
    toolBar->setDisabled(b);
}

void MainFrame::SetTextToStatusbarSlot(QString s)
{
    SetTextToStatusbar( s.toLatin1().data());
}

void MainFrame::drawPreviewSlot()
{
    emit drawPreviewSignal();
}

void MainFrame::stopSlot()
{
    pPreview->Stop();
    pDisplay->Stop();
    toolBar->SetToolbarState(0);
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
