#include "unity.h"
#include "Arc2Line.h"
#include "SaveAdjustData.h"

static void* pdata = 0;

void setUp(void)
{
    pdata = init_AxixZAdjustDataBuf();

    memset(pdata,0,(sizeof(char)*SAVE_AXIX_Z_ADJUST_DATA_BUF_LENTH));

    create_AxisZAdjustFileHeader(0);

    IsAlreadyHasLineDataBuf = 0;

}

void tearDown(void)
{
    free(pdata);
}

void test_OnlyOneLineBreakUnitLine(void)
{
    StartPoint_T start_point;
    EndPoint_T end_point;

    start_point.wComConfig  = 15;
    start_point.wWorkAdjCfg = 0;

    end_point.wComConfig  = 16;
    end_point.wWorkAdjCfg = 256;

    InitStartPointDataBuf(&start_point,0);
    InitEndPointDataBuf(&end_point,0);

    start_point.wComConfig  = 15;
    start_point.wWorkAdjCfg = 0;

    end_point.wComConfig  = 16;
    end_point.wWorkAdjCfg = 256;

    InitStartPointDataBuf(&start_point,0);
    InitEndPointDataBuf(&end_point,0);

    start_point.wComConfig  = 15;
    start_point.wWorkAdjCfg = 512;

    end_point.wComConfig  = 16;
    end_point.wWorkAdjCfg = 512;

    InitStartPointDataBuf(&start_point,0);
    InitEndPointDataBuf(&end_point,0);

    TEST_ASSERT_EQUAL_UINT32(15  ,*((unsigned int *)pdata + 3));
    TEST_ASSERT_EQUAL_UINT32(16  ,*((unsigned int *)pdata + 4));
    TEST_ASSERT_EQUAL_UINT32(4   ,*((unsigned int *)pdata + 5));
    TEST_ASSERT_EQUAL_UINT32(1000,*((unsigned int *)pdata + 6));
    TEST_ASSERT_EQUAL_UINT32(1000,*((unsigned int *)pdata + 7));
    TEST_ASSERT_EQUAL_UINT32(1000,*((unsigned int *)pdata + 8));
    TEST_ASSERT_EQUAL_UINT32(2000,*((unsigned int *)pdata + 9));
    TEST_ASSERT_EQUAL_UINT32(10,get_AxisZAdjustBufLength());
}

void test_OneBreakLineNotAdjust(void)
{
    StartPoint_T start_point;
    EndPoint_T end_point;

    start_point.wComConfig  = 15;
    start_point.wWorkAdjCfg = 768;

    end_point.wComConfig  = 16;
    end_point.wWorkAdjCfg = 768;

    InitStartPointDataBuf(&start_point,0);
    InitEndPointDataBuf(&end_point,0);

    start_point.wComConfig  = 15;
    start_point.wWorkAdjCfg = 768;

    end_point.wComConfig  = 16;
    end_point.wWorkAdjCfg = 768;

    InitStartPointDataBuf(&start_point,0);
    InitEndPointDataBuf(&end_point,0);

    start_point.wComConfig  = 15;
    start_point.wWorkAdjCfg = 768;

    end_point.wComConfig  = 16;
    end_point.wWorkAdjCfg = 768;

    InitStartPointDataBuf(&start_point,0);
    InitEndPointDataBuf(&end_point,0);

    TEST_ASSERT_EQUAL_UINT32(3,get_AxisZAdjustBufLength());
}

void test_OneBreakLineNotAdjustLastEndPoint(void)
{
    StartPoint_T start_point;
    EndPoint_T end_point;

    start_point.wComConfig  = 15;
    start_point.wWorkAdjCfg = 0;

    end_point.wComConfig  = 16;
    end_point.wWorkAdjCfg = 256;

    InitStartPointDataBuf(&start_point,0);
    InitEndPointDataBuf(&end_point,0);

    start_point.wComConfig  = 15;
    start_point.wWorkAdjCfg = 0;

    end_point.wComConfig  = 16;
    end_point.wWorkAdjCfg = 256;

    InitStartPointDataBuf(&start_point,0);
    InitEndPointDataBuf(&end_point,0);

    start_point.wComConfig  = 15;
    start_point.wWorkAdjCfg = 512;

    end_point.wComConfig  = 16;
    end_point.wWorkAdjCfg = 768;

    InitStartPointDataBuf(&start_point,0);
    InitEndPointDataBuf(&end_point,0);

    TEST_ASSERT_EQUAL_UINT32(15  ,*((unsigned int *)pdata + 3));
    TEST_ASSERT_EQUAL_UINT32(16  ,*((unsigned int *)pdata + 4));
    TEST_ASSERT_EQUAL_UINT32(3   ,*((unsigned int *)pdata + 5));
    TEST_ASSERT_EQUAL_UINT32(1000,*((unsigned int *)pdata + 6));
    TEST_ASSERT_EQUAL_UINT32(1000,*((unsigned int *)pdata + 7));
    TEST_ASSERT_EQUAL_UINT32(1000,*((unsigned int *)pdata + 8));
    TEST_ASSERT_EQUAL_UINT32(9,get_AxisZAdjustBufLength());
}

void test_TwoSerialBreakLineFirstLineNotAdjutEndPoint(void)
{
    StartPoint_T start_point;
    EndPoint_T end_point;

    start_point.wComConfig  = 15;
    start_point.wWorkAdjCfg = 0;

    end_point.wComConfig  = 16;
    end_point.wWorkAdjCfg = 256;

    InitStartPointDataBuf(&start_point,0);
    InitEndPointDataBuf(&end_point,0);

    start_point.wComConfig  = 15;
    start_point.wWorkAdjCfg = 0;

    end_point.wComConfig  = 16;
    end_point.wWorkAdjCfg = 256;

    InitStartPointDataBuf(&start_point,0);
    InitEndPointDataBuf(&end_point,0);

    start_point.wComConfig  = 15;
    start_point.wWorkAdjCfg = 512;

    end_point.wComConfig  = 16;
    end_point.wWorkAdjCfg = 768;

    InitStartPointDataBuf(&start_point,0);
    InitEndPointDataBuf(&end_point,0);

    start_point.wComConfig  = 15;
    start_point.wWorkAdjCfg = 0;

    end_point.wComConfig  = 16;
    end_point.wWorkAdjCfg = 256;

    InitStartPointDataBuf(&start_point,0);
    InitEndPointDataBuf(&end_point,0);

    start_point.wComConfig  = 15;
    start_point.wWorkAdjCfg = 0;

    end_point.wComConfig  = 16;
    end_point.wWorkAdjCfg = 256;

    InitStartPointDataBuf(&start_point,0);
    InitEndPointDataBuf(&end_point,0);

    start_point.wComConfig  = 15;
    start_point.wWorkAdjCfg = 512;

    end_point.wComConfig  = 16;
    end_point.wWorkAdjCfg = 512;

    InitStartPointDataBuf(&start_point,0);
    InitEndPointDataBuf(&end_point,0);

    TEST_ASSERT_EQUAL_UINT32(0   ,*((unsigned int *)pdata + 0));
    TEST_ASSERT_EQUAL_UINT32(0   ,*((unsigned int *)pdata + 1));
    TEST_ASSERT_EQUAL_UINT32(2   ,*((unsigned int *)pdata + 2));
    TEST_ASSERT_EQUAL_UINT32(15  ,*((unsigned int *)pdata + 3));
    TEST_ASSERT_EQUAL_UINT32(16  ,*((unsigned int *)pdata + 4));
    TEST_ASSERT_EQUAL_UINT32(3   ,*((unsigned int *)pdata + 5));
    TEST_ASSERT_EQUAL_UINT32(1000,*((unsigned int *)pdata + 6));
    TEST_ASSERT_EQUAL_UINT32(1000,*((unsigned int *)pdata + 7));
    TEST_ASSERT_EQUAL_UINT32(1000,*((unsigned int *)pdata + 8));
    TEST_ASSERT_EQUAL_UINT32(15  ,*((unsigned int *)pdata + 9));
    TEST_ASSERT_EQUAL_UINT32(16  ,*((unsigned int *)pdata + 10));
    TEST_ASSERT_EQUAL_UINT32(4   ,*((unsigned int *)pdata + 11));
    TEST_ASSERT_EQUAL_UINT32(1000,*((unsigned int *)pdata + 12));
    TEST_ASSERT_EQUAL_UINT32(1000,*((unsigned int *)pdata + 13));
    TEST_ASSERT_EQUAL_UINT32(1000,*((unsigned int *)pdata + 14));
    TEST_ASSERT_EQUAL_UINT32(2000,*((unsigned int *)pdata + 15));
    TEST_ASSERT_EQUAL_UINT32(16,get_AxisZAdjustBufLength());
}

void test_TwoBreakLinePartAdjustLastOne(void)
{
    StartPoint_T start_point;
    EndPoint_T end_point;

    start_point.wComConfig  = 15;
    start_point.wWorkAdjCfg = 256;

    end_point.wComConfig  = 16;
    end_point.wWorkAdjCfg = 256;

    InitStartPointDataBuf(&start_point,0);
    InitEndPointDataBuf(&end_point,0);

    start_point.wComConfig  = 15;
    start_point.wWorkAdjCfg = 256;

    end_point.wComConfig  = 16;
    end_point.wWorkAdjCfg = 256;

    InitStartPointDataBuf(&start_point,0);
    InitEndPointDataBuf(&end_point,0);

    start_point.wComConfig  = 15;
    start_point.wWorkAdjCfg = 768;

    end_point.wComConfig  = 16;
    end_point.wWorkAdjCfg = 768;

    InitStartPointDataBuf(&start_point,0);
    InitEndPointDataBuf(&end_point,0);

    start_point.wComConfig  = 17;
    start_point.wWorkAdjCfg = 0;

    end_point.wComConfig  = 18;
    end_point.wWorkAdjCfg = 256;

    InitStartPointDataBuf(&start_point,0);
    InitEndPointDataBuf(&end_point,0);

    start_point.wComConfig  = 15;
    start_point.wWorkAdjCfg = 0;

    end_point.wComConfig  = 16;
    end_point.wWorkAdjCfg = 256;

    InitStartPointDataBuf(&start_point,0);
    InitEndPointDataBuf(&end_point,0);

    start_point.wComConfig  = 15;
    start_point.wWorkAdjCfg = 512;

    end_point.wComConfig  = 16;
    end_point.wWorkAdjCfg = 512;

    InitStartPointDataBuf(&start_point,0);
    InitEndPointDataBuf(&end_point,0);

    TEST_ASSERT_EQUAL_UINT32(0   ,*((unsigned int *)pdata + 0));
    TEST_ASSERT_EQUAL_UINT32(0   ,*((unsigned int *)pdata + 1));
    TEST_ASSERT_EQUAL_UINT32(1   ,*((unsigned int *)pdata + 2));
    TEST_ASSERT_EQUAL_UINT32(17  ,*((unsigned int *)pdata + 3));
    TEST_ASSERT_EQUAL_UINT32(18  ,*((unsigned int *)pdata + 4));
    TEST_ASSERT_EQUAL_UINT32(4   ,*((unsigned int *)pdata + 5));
    TEST_ASSERT_EQUAL_UINT32(1000,*((unsigned int *)pdata + 6));
    TEST_ASSERT_EQUAL_UINT32(1000,*((unsigned int *)pdata + 7));
    TEST_ASSERT_EQUAL_UINT32(1000,*((unsigned int *)pdata + 8));
    TEST_ASSERT_EQUAL_UINT32(2000,*((unsigned int *)pdata + 9));
    TEST_ASSERT_EQUAL_UINT32(10,get_AxisZAdjustBufLength());

}

