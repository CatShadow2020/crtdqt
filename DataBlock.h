#pragma "$Id$"
// DataBlock.h: interface for the CDataBlock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATABLOCK_H__F0C2AFB6_FD5A_11D2_8661_4CAE18000000__INCLUDED_)
#define AFX_DATABLOCK_H__F0C2AFB6_FD5A_11D2_8661_4CAE18000000__INCLUDED_


#include "platform.h"

class CDataBlock  
{
public:
	CDataBlock();
	virtual ~CDataBlock();
    void PutData(int n, INT32 *plData);
	void PutData(int n, UINT8 *uint8data);

public:
    char   sname[32];			   /* station name                     */
    float  lat;                    /* latitutude                       */
    float  lon;                    /* longitude                        */
    float  elev;                   /* elevation                        */
    float  depth;                  /* sensor depth                     */
    char   cname[32];			   /* channel name                     */
    float  sint;                   /* nominal sample interval, sec     */
    double beg;                    /* time of first sample in packet   */
    double end;                    /* time of last  sample in packet   */
    int    tear;                   /* if set, there was a time tear    */
    long   nsamp;                  /* number of samples                */
    long   *data;                  /* raw data storage (if required)   */
	};

#endif // !defined(AFX_DATABLOCK_H__F0C2AFB6_FD5A_11D2_8661_4CAE18000000__INCLUDED_)
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