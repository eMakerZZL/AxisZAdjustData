#ifndef _SAVEADJUSTDATA_H
#define _SAVEADJUSTDATA_H

#include <stdlib.h>

#define SAVE_AXIX_Z_ADJUST_DATA_BUF_LENTH   (1024 * 40)
#define MAX_AXIS_Z_ADJUST_DATA_BUF_SIZE     (SAVE_AXIX_Z_ADJUST_DATA_BUF_LENTH / 4)

/*! \struct _AxisZAdjustData_t 
 *  \brief Brief struct description
 *
 *  Detailed description
 */
typedef struct _AxisZAdjustFileHeader_t {
    unsigned int FileNo;
    unsigned int Result;
    unsigned int DataHeaderSum;
} AxisZAdjustFileHeader_t;
#define SIZE_OF_Z_ADJUST_FILE_HEADER 3

/*! \struct _AxisZAdjustDataHeader_t 
 *  \brief Brief struct description
 *
 *  Detailed description
 */
typedef struct _AxisZAdjustDataHeader_t {
    unsigned int StartIndex;
    unsigned int EndIndex;
    unsigned int DataSum;
} AxisZAdjustDataHeader_t;
#define SIZE_OF_Z_ADJUST_DATA_HEADER 3

/*! \struct _AdjustOperator_t 
 *  \brief Brief struct description
 *
 *  Detailed description
 */
typedef struct _AxisZAdjustDataBuf_t{
    AxisZAdjustFileHeader_t *pAdjustFileHeader;
    AxisZAdjustDataHeader_t *pAdjustDataHeader;
    unsigned int *pvalue;
    unsigned int length;
} AxisZAdjustDataBuf_t;

void* init_AxixZAdjustDataBuf(void);

void create_AxisZAdjustFileHeader(unsigned int FileNo);
void create_AxisZAdjustDataHeader(unsigned int start,unsigned int end);
unsigned int get_AxisZAdjustBufLength(void);
void insert_AxisZAdjustData(int data);
void set_AxisZAdjustResult(unsigned int result);
unsigned int get_AxisZAdjustResult(void);

#endif // _SAVEADJUSTDATA_H
