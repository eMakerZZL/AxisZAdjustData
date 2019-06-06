#include "SaveAdjustData.h"


static unsigned int *pdata = 0;
static AxisZAdjustDataBuf_t AxisZAdjustDataBuf = {0,0,0};

void* init_AxixZAdjustDataBuf(void)
{
    pdata = malloc(sizeof(char)*SAVE_AXIX_Z_ADJUST_DATA_BUF_LENTH);
    
    AxisZAdjustDataBuf.pAdjustFileHeader = (AxisZAdjustFileHeader_t *)(pdata);
    AxisZAdjustDataBuf.pAdjustDataHeader = 0;
    AxisZAdjustDataBuf.pvalue            = (unsigned int*)(pdata);
    AxisZAdjustDataBuf.length            = 0;

    return (void*)pdata;
}

void create_AxisZAdjustFileHeader(unsigned int FileNo)
{
    AxisZAdjustFileHeader_t *pFileHeader = AxisZAdjustDataBuf.pAdjustFileHeader;

    pFileHeader->FileNo = FileNo;
    pFileHeader->Result = 0;
    pFileHeader->DataHeaderSum = 0; 
    
    AxisZAdjustDataBuf.length += SIZE_OF_Z_ADJUST_FILE_HEADER;
}

unsigned int get_AxisZAdjustBufLength(void)
{
    return AxisZAdjustDataBuf.length;
}

void set_AxisZAdjustResult(unsigned int result)
{
    AxisZAdjustFileHeader_t *pFileHeader = AxisZAdjustDataBuf.pAdjustFileHeader;

    pFileHeader->Result = result;
}

unsigned int get_AxisZAdjustResult(void)
{
    AxisZAdjustFileHeader_t *pFileHeader = AxisZAdjustDataBuf.pAdjustFileHeader;

    return pFileHeader->Result; 
}

void create_AxisZAdjustDataHeader(unsigned int start,unsigned int end)
{
    AxisZAdjustDataBuf.pAdjustDataHeader   = (AxisZAdjustDataHeader_t *)(AxisZAdjustDataBuf.pvalue + AxisZAdjustDataBuf.length);

    AxisZAdjustDataHeader_t *pDataHeader = AxisZAdjustDataBuf.pAdjustDataHeader;
    AxisZAdjustFileHeader_t *pFileHeader = AxisZAdjustDataBuf.pAdjustFileHeader;

    pDataHeader->StartIndex = start;
    pDataHeader->EndIndex   = end;
    pDataHeader->DataSum    = 0;

    pFileHeader->DataHeaderSum++;
    
    AxisZAdjustDataBuf.length += SIZE_OF_Z_ADJUST_DATA_HEADER;
}

void insert_AxisZAdjustData(int data)
{
    AxisZAdjustDataHeader_t *pDataHeader = AxisZAdjustDataBuf.pAdjustDataHeader;

    *(AxisZAdjustDataBuf.pvalue + AxisZAdjustDataBuf.length) = (unsigned int)data;
    AxisZAdjustDataBuf.length++;
    pDataHeader->DataSum++;
}
