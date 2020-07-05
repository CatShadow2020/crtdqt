#pragma "$Id$"
// MWindowX.h: interface for the CMWindowX class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MWINDOWX_H__1468323A_3808_11D4_8D75_00B0D0233922__INCLUDED_)
#define AFX_MWINDOWX_H__1468323A_3808_11D4_8D75_00B0D0233922__INCLUDED_


class CMWindowX  
{
public:
	int x1,x2,y1,y2;
	int xw1,xw2,yw1,yw2;
	CString StaName;
	CString ChanName;
	CString LCODE;
	double dSpS;
	long amin,amax;

	CMWindowX();
	virtual ~CMWindowX();

};

#endif // !defined(AFX_MWINDOWX_H__1468323A_3808_11D4_8D75_00B0D0233922__INCLUDED_)

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