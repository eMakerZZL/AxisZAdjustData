#include "unity.h"
#include "SaveAdjustData.h"

void* pdata = 0;

void setUp(void)
{
    pdata = init_AxixZAdjustDataBuf();

    create_AxisZAdjustFileHeader(0);
}

void tearDown(void)
{
    free(pdata);
}

void test_SaveAdjustData_CreateFileHeaderWasOk(void)
{
    TEST_ASSERT_EQUAL_UINT32(0,*((unsigned int *)pdata + 0));
    TEST_ASSERT_EQUAL_UINT32(0,*((unsigned int *)pdata + 1));
    TEST_ASSERT_EQUAL_UINT32(0,*((unsigned int *)pdata + 2));
    TEST_ASSERT_EQUAL_UINT32(3,get_AxisZAdjustBufLength());
}

void test_SaveAdjustData_CreateDataHeaderWasOk(void)
{
    create_AxisZAdjustDataHeader(1,2);

    TEST_ASSERT_EQUAL_UINT32(1,*((unsigned int *)pdata + 3));
    TEST_ASSERT_EQUAL_UINT32(2,*((unsigned int *)pdata + 4));
    TEST_ASSERT_EQUAL_UINT32(0,*((unsigned int *)pdata + 5));
    TEST_ASSERT_EQUAL_UINT32(6,get_AxisZAdjustBufLength());
}

void test_SaveAdjustData_InserOneLineData(void)
{
    create_AxisZAdjustDataHeader(1,2);
    insert_AxisZAdjustData(1000);
    insert_AxisZAdjustData(2000);

    TEST_ASSERT_EQUAL_UINT32(1,*((unsigned int *)pdata + 3));
    TEST_ASSERT_EQUAL_UINT32(2,*((unsigned int *)pdata + 4));
    TEST_ASSERT_EQUAL_UINT32(2,*((unsigned int *)pdata + 5));

    TEST_ASSERT_EQUAL_INT32(1000,*((unsigned int *)pdata + 6));
    TEST_ASSERT_EQUAL_INT32(2000,*((unsigned int *)pdata + 7));
    TEST_ASSERT_EQUAL_UINT32(8,get_AxisZAdjustBufLength());
}

void test_SaveAdjustData_InsertMultLineData(void)
{
    unsigned int i = 0;
    
    create_AxisZAdjustDataHeader(1,2);
    insert_AxisZAdjustData(1000);
    insert_AxisZAdjustData(2000);

    create_AxisZAdjustDataHeader(3,4);
    insert_AxisZAdjustData(3000);
    insert_AxisZAdjustData(4000);

    create_AxisZAdjustDataHeader(5,6);
    insert_AxisZAdjustData(-5000);
    insert_AxisZAdjustData(6000);

    TEST_ASSERT_EQUAL_UINT32(0,*((unsigned int *)pdata + i++));
    TEST_ASSERT_EQUAL_UINT32(0,*((unsigned int *)pdata + i++));
    TEST_ASSERT_EQUAL_UINT32(3,*((unsigned int *)pdata + i++));

    TEST_ASSERT_EQUAL_UINT32(1,*((unsigned int *)pdata + i++));
    TEST_ASSERT_EQUAL_UINT32(2,*((unsigned int *)pdata + i++));
    TEST_ASSERT_EQUAL_UINT32(2,*((unsigned int *)pdata + i++));
    TEST_ASSERT_EQUAL_INT32(1000,*((unsigned int *)pdata + i++));
    TEST_ASSERT_EQUAL_INT32(2000,*((unsigned int *)pdata + i++));

    TEST_ASSERT_EQUAL_UINT32(3,*((unsigned int *)pdata + i++));
    TEST_ASSERT_EQUAL_UINT32(4,*((unsigned int *)pdata + i++));
    TEST_ASSERT_EQUAL_UINT32(2,*((unsigned int *)pdata + i++));
    TEST_ASSERT_EQUAL_INT32(3000,*((unsigned int *)pdata + i++));
    TEST_ASSERT_EQUAL_INT32(4000,*((unsigned int *)pdata + i++));

    TEST_ASSERT_EQUAL_UINT32(5,*((unsigned int *)pdata + i++));
    TEST_ASSERT_EQUAL_UINT32(6,*((unsigned int *)pdata + i++));
    TEST_ASSERT_EQUAL_UINT32(2,*((unsigned int *)pdata + i++));
    TEST_ASSERT_EQUAL_INT32(-5000,*((unsigned int *)pdata + i++));
    TEST_ASSERT_EQUAL_INT32(6000,*((unsigned int *)pdata + i++));

    TEST_ASSERT_EQUAL_UINT32(18,get_AxisZAdjustBufLength());
}

void test_SaveAdjustData_InsertOneArcData(void)
{
    create_AxisZAdjustDataHeader(1,2);
    insert_AxisZAdjustData(1000);
    insert_AxisZAdjustData(2000);
    insert_AxisZAdjustData(3000);
    insert_AxisZAdjustData(4000);
    insert_AxisZAdjustData(5000);
    insert_AxisZAdjustData(6000);
    insert_AxisZAdjustData(7000);
    insert_AxisZAdjustData(8000);
    insert_AxisZAdjustData(9000);
    insert_AxisZAdjustData(   0);
    insert_AxisZAdjustData(1000);
    insert_AxisZAdjustData(2000);

    TEST_ASSERT_EQUAL_UINT32(0,*((unsigned int *)pdata + 0));
    TEST_ASSERT_EQUAL_UINT32(0,*((unsigned int *)pdata + 1));
    TEST_ASSERT_EQUAL_UINT32(1,*((unsigned int *)pdata + 2));

    TEST_ASSERT_EQUAL_UINT32(1 ,*((unsigned int *)pdata + 3));
    TEST_ASSERT_EQUAL_UINT32(2 ,*((unsigned int *)pdata + 4));
    TEST_ASSERT_EQUAL_UINT32(12,*((unsigned int *)pdata + 5));

    TEST_ASSERT_EQUAL_INT32(1000,*((unsigned int *)pdata + 6));
    TEST_ASSERT_EQUAL_INT32(2000,*((unsigned int *)pdata + 7));
    TEST_ASSERT_EQUAL_INT32(3000,*((unsigned int *)pdata + 8));
    TEST_ASSERT_EQUAL_INT32(4000,*((unsigned int *)pdata + 9));
    TEST_ASSERT_EQUAL_INT32(5000,*((unsigned int *)pdata + 10));
    TEST_ASSERT_EQUAL_INT32(6000,*((unsigned int *)pdata + 11));
    TEST_ASSERT_EQUAL_INT32(7000,*((unsigned int *)pdata + 12));
    TEST_ASSERT_EQUAL_INT32(8000,*((unsigned int *)pdata + 13));
    TEST_ASSERT_EQUAL_INT32(9000,*((unsigned int *)pdata + 14));
    TEST_ASSERT_EQUAL_INT32(   0,*((unsigned int *)pdata + 15));
    TEST_ASSERT_EQUAL_INT32(1000,*((unsigned int *)pdata + 16));
    TEST_ASSERT_EQUAL_INT32(2000,*((unsigned int *)pdata + 17));
    TEST_ASSERT_EQUAL_UINT32(18,get_AxisZAdjustBufLength());
}

void test_SaveAdjustData_InsertMultArcData(void)
{
    unsigned int i = 0;

    create_AxisZAdjustDataHeader(1,2);
    insert_AxisZAdjustData(1000);
    insert_AxisZAdjustData(2000);
    insert_AxisZAdjustData(3000);
    insert_AxisZAdjustData(4000);
    insert_AxisZAdjustData(5000);
    insert_AxisZAdjustData(6000);
    insert_AxisZAdjustData(7000);
    insert_AxisZAdjustData(8000);
    insert_AxisZAdjustData(9000);
    insert_AxisZAdjustData(   0);

    create_AxisZAdjustDataHeader(3,4);
    insert_AxisZAdjustData(1000);
    insert_AxisZAdjustData(2000);
    insert_AxisZAdjustData(3000);
    insert_AxisZAdjustData(4000);
    insert_AxisZAdjustData(5000);

    create_AxisZAdjustDataHeader(5,6);
    insert_AxisZAdjustData(1000);
    insert_AxisZAdjustData(2000);
    insert_AxisZAdjustData(3000);

    TEST_ASSERT_EQUAL_UINT32(0  ,*((unsigned int *)pdata + i++));
    TEST_ASSERT_EQUAL_UINT32(0  ,*((unsigned int *)pdata + i++));
    TEST_ASSERT_EQUAL_UINT32(3  ,*((unsigned int *)pdata + i++));

    TEST_ASSERT_EQUAL_UINT32(1  ,*((unsigned int *)pdata + i++));
    TEST_ASSERT_EQUAL_UINT32(2  ,*((unsigned int *)pdata + i++));
    TEST_ASSERT_EQUAL_UINT32(10 ,*((unsigned int *)pdata + i++));
    TEST_ASSERT_EQUAL_INT32(1000,*((unsigned int *)pdata + i++));
    TEST_ASSERT_EQUAL_INT32(2000,*((unsigned int *)pdata + i++));
    TEST_ASSERT_EQUAL_INT32(3000,*((unsigned int *)pdata + i++));
    TEST_ASSERT_EQUAL_INT32(4000,*((unsigned int *)pdata + i++));
    TEST_ASSERT_EQUAL_INT32(5000,*((unsigned int *)pdata + i++));
    TEST_ASSERT_EQUAL_INT32(6000,*((unsigned int *)pdata + i++));
    TEST_ASSERT_EQUAL_INT32(7000,*((unsigned int *)pdata + i++));
    TEST_ASSERT_EQUAL_INT32(8000,*((unsigned int *)pdata + i++));
    TEST_ASSERT_EQUAL_INT32(9000,*((unsigned int *)pdata + i++));
    TEST_ASSERT_EQUAL_INT32(   0,*((unsigned int *)pdata + i++));

    TEST_ASSERT_EQUAL_UINT32(3  ,*((unsigned int *)pdata + i++));
    TEST_ASSERT_EQUAL_UINT32(4  ,*((unsigned int *)pdata + i++));
    TEST_ASSERT_EQUAL_UINT32(5  ,*((unsigned int *)pdata + i++));
    TEST_ASSERT_EQUAL_INT32(1000,*((unsigned int *)pdata + i++));
    TEST_ASSERT_EQUAL_INT32(2000,*((unsigned int *)pdata + i++));
    TEST_ASSERT_EQUAL_INT32(3000,*((unsigned int *)pdata + i++));
    TEST_ASSERT_EQUAL_INT32(4000,*((unsigned int *)pdata + i++));
    TEST_ASSERT_EQUAL_INT32(5000,*((unsigned int *)pdata + i++));

    TEST_ASSERT_EQUAL_UINT32(5  ,*((unsigned int *)pdata + i++));
    TEST_ASSERT_EQUAL_UINT32(6  ,*((unsigned int *)pdata + i++));
    TEST_ASSERT_EQUAL_UINT32(3  ,*((unsigned int *)pdata + i++));
    TEST_ASSERT_EQUAL_INT32(1000,*((unsigned int *)pdata + i++));
    TEST_ASSERT_EQUAL_INT32(2000,*((unsigned int *)pdata + i++));
    TEST_ASSERT_EQUAL_INT32(3000,*((unsigned int *)pdata + i++));

    TEST_ASSERT_EQUAL_UINT32(i,get_AxisZAdjustBufLength());
}

void test_SaveAdjustData_SendError(void)
{
    set_AxisZAdjustResult(1);

    TEST_ASSERT_EQUAL_UINT32(1,get_AxisZAdjustResult());
}
