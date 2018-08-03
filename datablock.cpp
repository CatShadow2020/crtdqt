#pragma "$Id$"
// DataBlock.cpp: implementation of the CDataBlock class.
//
//////////////////////////////////////////////////////////////////////

#include "DataBlock.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDataBlock::CDataBlock()
	{
	data = NULL;
	}

CDataBlock::~CDataBlock()
	{
	if(data!=NULL) delete[] data;
	data=NULL;
	}

void CDataBlock::PutData(int n, INT32 *plData)
	{
	data=new long[n];
	if(data!=NULL)
		{
		for(int i=0; i<n; ++i)
			{
			data[i] = plData[i];
			}
		}
	}

void CDataBlock::PutData(int n, UINT8 *uint8data)
	{
	data=new long[n];
	if(data!=NULL)
		{
		for(int i=0; i<n; ++i)
			{
			data[i] = uint8data[i];
			}
		}
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
