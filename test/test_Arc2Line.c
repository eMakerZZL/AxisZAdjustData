#include "unity.h"
#include "Arc2Line.h"
#include "SaveAdjustData.h"

static  StartPoint_T Line1_StartPoint = {11,12,13,14,15,16,17,18,19,110,111,112,113,114,{115,115,115,115},116,117};
static  MidPoint_T   ArcMidPoint      = {21,22,23,24,25,26,27,28,29,210};
static  EndPoint_T   Line2_EndPoint   = {31,32,33,34,35,36,37,38,39,310,311,312,{313,313,313,313},314,315};

const StartPoint_T line1_start_point = {11,12,13,14,15,16,17,18,19,110,111,112,113,114,{115,115,115,115},116,117};
const EndPoint_T   line1_end_point   = {21,22,23,24,25,26,27,28,29,0,0,113,{0,0,0,0},210,0 };
const StartPoint_T line2_start_point = {21,22,23,24,25,26,27,28,29,110,111,0,113,0,{0,0,0,0},116,210};
const EndPoint_T   line2_end_point   = {31,32,33,34,35,36,37,38,39,310,311,312,{313,313,313,313},314,315};

const StartPoint_T arc_start_point   = {11,12,13,14,15,16,17,18,19,110,111,112,113,114,{115,115,115,115},116,117};
const MidPoint_T   arc_mid_point     = {21,22,23,24,25,26,27,28,29,210};
const EndPoint_T   arc_end_point     = {31,32,33,34,35,36,37,38,39,310,311,312,{313,313,313,313},314,315};

static void* pdata = 0;

void setUp(void)
{
    CopyArcStartPoint(&Line1_StartPoint);

    pdata = init_AxixZAdjustDataBuf();

    memset(pdata,0,(sizeof(char)*SAVE_AXIX_Z_ADJUST_DATA_BUF_LENTH));

    create_AxisZAdjustFileHeader(0);

    IsAlreadyHasLineDataBuf = 0;
}

void tearDown(void)
{
    free(pdata);
}

void test_Arc2Line_ArcMidToLine1EndPoint(void)
{
    EndPoint_T convert_point;

    const EndPoint_T compare_point = { 21,22,23,24,25,26,27,28,29,0,0,113,{0,0,0,0},210,0 };
    
    ArcMidToLine1EndPoint(&ArcMidPoint,&convert_point);

    TEST_ASSERT_EQUAL_MEMORY(&compare_point,&compare_point,sizeof(EndPoint_T));
}

void test_Arc2Line_ArcMidToLine2StartPoint(void)
{
    StartPoint_T convert_point; 

    const StartPoint_T compare_point = {21,22,23,24,25,26,27,28,29,110,111,0,113,0,{0,0,0,0},116,210};
    
    ArcMidToLine2StartPoint(&ArcMidPoint,&convert_point);

    TEST_ASSERT_EQUAL_MEMORY(&compare_point,&compare_point,sizeof(StartPoint_T));
}

void test_Arc2Line_ConvertArcOrderToLineOrder(void)
{
    TEST_ASSERT_EQUAL_UINT32(ORDER_LINE_START,ConvertArcOrderToLineOrder(ORDER_ARC_START));
    TEST_ASSERT_EQUAL_UINT32(ORDER_LINE_END  ,ConvertArcOrderToLineOrder(ORDER_ARC_MID));
    TEST_ASSERT_EQUAL_UINT32(ORDER_LINE_START,ConvertArcOrderToLineOrder(ORDER_ARC_MID));
    TEST_ASSERT_EQUAL_UINT32(ORDER_LINE_END  ,ConvertArcOrderToLineOrder(ORDER_ARC_END));
}

void test_Arc2Line_MultArcMidOrderWasOk(void)
{
    TEST_ASSERT_EQUAL_UINT32(ORDER_LINE_END  ,ConvertArcOrderToLineOrder(ORDER_ARC_MID));
    TEST_ASSERT_EQUAL_UINT32(ORDER_LINE_START,ConvertArcOrderToLineOrder(ORDER_ARC_MID));
    TEST_ASSERT_EQUAL_UINT32(ORDER_LINE_END  ,ConvertArcOrderToLineOrder(ORDER_ARC_MID));
    TEST_ASSERT_EQUAL_UINT32(ORDER_LINE_START,ConvertArcOrderToLineOrder(ORDER_ARC_MID));
    TEST_ASSERT_EQUAL_UINT32(ORDER_LINE_END  ,ConvertArcOrderToLineOrder(ORDER_ARC_MID));
    TEST_ASSERT_EQUAL_UINT32(ORDER_LINE_START,ConvertArcOrderToLineOrder(ORDER_ARC_MID));
    TEST_ASSERT_EQUAL_UINT32(ORDER_LINE_END  ,ConvertArcOrderToLineOrder(ORDER_ARC_MID));
    TEST_ASSERT_EQUAL_UINT32(ORDER_LINE_START,ConvertArcOrderToLineOrder(ORDER_ARC_MID));
}

void test_Arc2Line_LineStartPointNeedAdjust(void)
{
    StartPoint_T start_point;
    start_point.wComConfig  = 15;
    start_point.wWorkAdjCfg = 0;

    InitStartPointDataBuf(&start_point,0);

    TEST_ASSERT_EQUAL_UINT32(15  ,*((unsigned int *)pdata + 3));
    TEST_ASSERT_EQUAL_UINT32(16  ,*((unsigned int *)pdata + 4));
    TEST_ASSERT_EQUAL_UINT32(1   ,*((unsigned int *)pdata + 5));
    TEST_ASSERT_EQUAL_UINT32(1000,*((unsigned int *)pdata + 6));
    TEST_ASSERT_EQUAL_UINT32(7,get_AxisZAdjustBufLength());
}

void test_Arc2Line_LineStartPointNotAdjust(void)
{
    StartPoint_T start_point;
    start_point.wComConfig  = 15;
    start_point.wWorkAdjCfg = 256;

    InitStartPointDataBuf(&start_point,0);

    TEST_ASSERT_EQUAL_UINT32(0,*((unsigned int *)pdata + 3));
    TEST_ASSERT_EQUAL_UINT32(0,*((unsigned int *)pdata + 4));
    TEST_ASSERT_EQUAL_UINT32(0,*((unsigned int *)pdata + 5));
    TEST_ASSERT_EQUAL_UINT32(3,get_AxisZAdjustBufLength());
}

void test_Arc2Line_LineEndPointNeedAdjust(void)
{
    EndPoint_T end_point;
    end_point.wComConfig  = 15;
    end_point.wWorkAdjCfg = 0;

    InitEndPointDataBuf(&end_point,0);

    TEST_ASSERT_EQUAL_UINT32(14  ,*((unsigned int *)pdata + 3));
    TEST_ASSERT_EQUAL_UINT32(15  ,*((unsigned int *)pdata + 4));
    TEST_ASSERT_EQUAL_UINT32(1   ,*((unsigned int *)pdata + 5));
    TEST_ASSERT_EQUAL_UINT32(2000,*((unsigned int *)pdata + 6));
    TEST_ASSERT_EQUAL_UINT32(7,get_AxisZAdjustBufLength());
}

void test_Arc2Line_LineEndPointNotAdjust(void)
{
    EndPoint_T end_point;
    end_point.wComConfig  = 15;
    end_point.wWorkAdjCfg = 256;

    InitEndPointDataBuf(&end_point,0);

    TEST_ASSERT_EQUAL_UINT32(0,*((unsigned int *)pdata + 3));
    TEST_ASSERT_EQUAL_UINT32(0,*((unsigned int *)pdata + 4));
    TEST_ASSERT_EQUAL_UINT32(0,*((unsigned int *)pdata + 5));
    TEST_ASSERT_EQUAL_UINT32(3,get_AxisZAdjustBufLength());
}

void test_Arc2Line_OneLineOnlyNeedEndAdjust(void)
{
    StartPoint_T start_point;
    start_point.wComConfig  = 15;
    start_point.wWorkAdjCfg = 256;

    EndPoint_T end_point;
    end_point.wComConfig  = 16;
    end_point.wWorkAdjCfg = 0;

    InitStartPointDataBuf(&start_point,0);
    InitEndPointDataBuf(&end_point,0);

    TEST_ASSERT_EQUAL_UINT32(15  ,*((unsigned int *)pdata + 3));
    TEST_ASSERT_EQUAL_UINT32(16  ,*((unsigned int *)pdata + 4));
    TEST_ASSERT_EQUAL_UINT32(1   ,*((unsigned int *)pdata + 5));
    TEST_ASSERT_EQUAL_UINT32(2000,*((unsigned int *)pdata + 6));
    TEST_ASSERT_EQUAL_UINT32(7,get_AxisZAdjustBufLength());
}

void test_Arc2Line_OneLineOnlyNeedStartAdjust(void)
{
    StartPoint_T start_point;
    start_point.wComConfig  = 15;
    start_point.wWorkAdjCfg = 0;

    EndPoint_T end_point;
    end_point.wComConfig  = 16;
    end_point.wWorkAdjCfg = 256;

    InitStartPointDataBuf(&start_point,0);
    InitEndPointDataBuf(&end_point,0);

    TEST_ASSERT_EQUAL_UINT32(15  ,*((unsigned int *)pdata + 3));
    TEST_ASSERT_EQUAL_UINT32(16  ,*((unsigned int *)pdata + 4));
    TEST_ASSERT_EQUAL_UINT32(1   ,*((unsigned int *)pdata + 5));
    TEST_ASSERT_EQUAL_UINT32(1000,*((unsigned int *)pdata + 6));
    TEST_ASSERT_EQUAL_UINT32(7,get_AxisZAdjustBufLength());
}

void test_Arc2Line_OneLineNeedWholeAdjust(void)
{
    StartPoint_T start_point;
    start_point.wComConfig  = 15;
    start_point.wWorkAdjCfg = 0;

    EndPoint_T end_point;
    end_point.wComConfig  = 16;
    end_point.wWorkAdjCfg = 0;

    InitStartPointDataBuf(&start_point,0);
    InitEndPointDataBuf(&end_point,0);

    TEST_ASSERT_EQUAL_UINT32(15  ,*((unsigned int *)pdata + 3));
    TEST_ASSERT_EQUAL_UINT32(16  ,*((unsigned int *)pdata + 4));
    TEST_ASSERT_EQUAL_UINT32(2   ,*((unsigned int *)pdata + 5));
    TEST_ASSERT_EQUAL_UINT32(1000,*((unsigned int *)pdata + 6));
    TEST_ASSERT_EQUAL_UINT32(2000,*((unsigned int *)pdata + 7));
    TEST_ASSERT_EQUAL_UINT32(8,get_AxisZAdjustBufLength());
}

void test_Arc2Line_MultLineNeedWholeAdjust(void)
{
    StartPoint_T start_point;
    start_point.wComConfig  = 15;
    start_point.wWorkAdjCfg = 0;

    EndPoint_T end_point;
    end_point.wComConfig  = 16;
    end_point.wWorkAdjCfg = 0;

    InitStartPointDataBuf(&start_point,0);
    InitEndPointDataBuf(&end_point,0);

    InitStartPointDataBuf(&start_point,0);
    InitEndPointDataBuf(&end_point,0);

    InitStartPointDataBuf(&start_point,0);
    InitEndPointDataBuf(&end_point,0);

    TEST_ASSERT_EQUAL_UINT32(15  ,*((unsigned int *)pdata + 3));
    TEST_ASSERT_EQUAL_UINT32(16  ,*((unsigned int *)pdata + 4));
    TEST_ASSERT_EQUAL_UINT32(2   ,*((unsigned int *)pdata + 5));
    TEST_ASSERT_EQUAL_UINT32(1000,*((unsigned int *)pdata + 6));
    TEST_ASSERT_EQUAL_UINT32(2000,*((unsigned int *)pdata + 7));
    TEST_ASSERT_EQUAL_UINT32(15  ,*((unsigned int *)pdata + 8));
    TEST_ASSERT_EQUAL_UINT32(16  ,*((unsigned int *)pdata + 9));
    TEST_ASSERT_EQUAL_UINT32(2   ,*((unsigned int *)pdata + 10));
    TEST_ASSERT_EQUAL_UINT32(1000,*((unsigned int *)pdata + 11));
    TEST_ASSERT_EQUAL_UINT32(2000,*((unsigned int *)pdata + 12));
    TEST_ASSERT_EQUAL_UINT32(15  ,*((unsigned int *)pdata + 13));
    TEST_ASSERT_EQUAL_UINT32(16  ,*((unsigned int *)pdata + 14));
    TEST_ASSERT_EQUAL_UINT32(2   ,*((unsigned int *)pdata + 15));
    TEST_ASSERT_EQUAL_UINT32(1000,*((unsigned int *)pdata + 16));
    TEST_ASSERT_EQUAL_UINT32(2000,*((unsigned int *)pdata + 17));
    TEST_ASSERT_EQUAL_UINT32(18,get_AxisZAdjustBufLength());
}

void test_Arc2Line_OneLineWholeDontAdjust(void)
{
    StartPoint_T start_point;
    start_point.wComConfig  = 15;
    start_point.wWorkAdjCfg = 256;

    EndPoint_T end_point;
    end_point.wComConfig  = 15;
    end_point.wWorkAdjCfg = 256;

    InitStartPointDataBuf(&start_point,0);
    InitEndPointDataBuf(&end_point,0);

    TEST_ASSERT_EQUAL_UINT32(0,*((unsigned int *)pdata + 3));
    TEST_ASSERT_EQUAL_UINT32(0,*((unsigned int *)pdata + 4));
    TEST_ASSERT_EQUAL_UINT32(0,*((unsigned int *)pdata + 5));
    TEST_ASSERT_EQUAL_UINT32(3,get_AxisZAdjustBufLength());
}

void test_Arc2Line_OneArcNeedWholeAdjust(void)
{
    StartPoint_T arc_start_point;    
    MidPoint_T   arc_mid_point;    
    EndPoint_T   arc_end_point;    

    EndPoint_T   arc_line1_end_point;
    StartPoint_T arc_line2_start_point;

    arc_start_point.wComConfig  = 15;
    arc_start_point.wWorkAdjCfg = 0;

    arc_mid_point.wComConfig  = 16;
    arc_mid_point.wWorkAdjCfg = 0;

    arc_end_point.wComConfig  = 17;
    arc_end_point.wWorkAdjCfg = 0;

    ArcMidToLine1EndPoint(&arc_mid_point,&arc_line1_end_point);
    ArcMidToLine2StartPoint(&arc_mid_point,&arc_line2_start_point);
    
    InitStartPointDataBuf(&arc_start_point,1);
    InitEndPointDataBuf(&arc_line1_end_point,2);

    InitStartPointDataBuf(&arc_line2_start_point,3);
    InitEndPointDataBuf(&arc_end_point,4);

    TEST_ASSERT_EQUAL_UINT32(15,*((unsigned int *)pdata + 3));
    TEST_ASSERT_EQUAL_UINT32(17,*((unsigned int *)pdata + 4));
    TEST_ASSERT_EQUAL_UINT32(3 ,*((unsigned int *)pdata + 5));
    TEST_ASSERT_EQUAL_UINT32(1000,*((unsigned int *)pdata + 6));
    TEST_ASSERT_EQUAL_UINT32(2000,*((unsigned int *)pdata + 7));
    TEST_ASSERT_EQUAL_UINT32(2000,*((unsigned int *)pdata + 8));
    TEST_ASSERT_EQUAL_UINT32(9 ,get_AxisZAdjustBufLength());
}

void test_Arc2Line_OneArcNeedStartAndMidAdjust(void)
{
    StartPoint_T arc_start_point;    
    MidPoint_T   arc_mid_point;    
    EndPoint_T   arc_end_point;    

    EndPoint_T   arc_line1_end_point;
    StartPoint_T arc_line2_start_point;

    arc_start_point.wComConfig  = 15;
    arc_start_point.wWorkAdjCfg = 0;

    arc_mid_point.wComConfig  = 16;
    arc_mid_point.wWorkAdjCfg = 0;

    arc_end_point.wComConfig  = 17;
    arc_end_point.wWorkAdjCfg = 256;

    ArcMidToLine1EndPoint(&arc_mid_point,&arc_line1_end_point);
    ArcMidToLine2StartPoint(&arc_mid_point,&arc_line2_start_point);
    
    InitStartPointDataBuf(&arc_start_point,1);
    InitEndPointDataBuf(&arc_line1_end_point,2);

    InitStartPointDataBuf(&arc_line2_start_point,3);
    InitEndPointDataBuf(&arc_end_point,4);

    TEST_ASSERT_EQUAL_UINT32(15,*((unsigned int *)pdata + 3));
    TEST_ASSERT_EQUAL_UINT32(17,*((unsigned int *)pdata + 4));
    TEST_ASSERT_EQUAL_UINT32(2 ,*((unsigned int *)pdata + 5));
    TEST_ASSERT_EQUAL_UINT32(1000,*((unsigned int *)pdata + 6));
    TEST_ASSERT_EQUAL_UINT32(2000,*((unsigned int *)pdata + 7));
    TEST_ASSERT_EQUAL_UINT32(8 ,get_AxisZAdjustBufLength());

}

void test_Arc2Line_OneArcDontNeedAdjust(void)
{
    StartPoint_T arc_start_point;    
    MidPoint_T   arc_mid_point;    
    EndPoint_T   arc_end_point;    

    EndPoint_T   arc_line1_end_point;
    StartPoint_T arc_line2_start_point;

    arc_start_point.wComConfig  = 15;
    arc_start_point.wWorkAdjCfg = 768;

    arc_mid_point.wComConfig  = 16;
    arc_mid_point.wWorkAdjCfg = 768;

    arc_end_point.wComConfig  = 17;
    arc_end_point.wWorkAdjCfg = 768;

    ArcMidToLine1EndPoint(&arc_mid_point,&arc_line1_end_point);
    ArcMidToLine2StartPoint(&arc_mid_point,&arc_line2_start_point);
    
    InitStartPointDataBuf(&arc_start_point,1);
    InitEndPointDataBuf(&arc_line1_end_point,2);

    InitStartPointDataBuf(&arc_line2_start_point,3);
    InitEndPointDataBuf(&arc_end_point,4);

    TEST_ASSERT_EQUAL_UINT32(0,*((unsigned int *)pdata + 3));
    TEST_ASSERT_EQUAL_UINT32(0,*((unsigned int *)pdata + 4));
    TEST_ASSERT_EQUAL_UINT32(0,*((unsigned int *)pdata + 5));
    TEST_ASSERT_EQUAL_UINT32(3,get_AxisZAdjustBufLength());
}

void test_Arc2Line_MultArcNeedWholeAdjust(void)
{
    StartPoint_T arc_start_point;    
    MidPoint_T   arc_mid_point;    
    EndPoint_T   arc_end_point;    

    EndPoint_T   arc_line1_end_point;
    StartPoint_T arc_line2_start_point;

    arc_start_point.wComConfig  = 15;
    arc_start_point.wWorkAdjCfg = 512;

    arc_mid_point.wComConfig  = 16;
    arc_mid_point.wWorkAdjCfg = 512;

    arc_end_point.wComConfig  = 17;
    arc_end_point.wWorkAdjCfg = 512;

    ArcMidToLine1EndPoint(&arc_mid_point,&arc_line1_end_point);
    ArcMidToLine2StartPoint(&arc_mid_point,&arc_line2_start_point);
    
    InitStartPointDataBuf(&arc_start_point,1);
    InitEndPointDataBuf(&arc_line1_end_point,2);

    InitStartPointDataBuf(&arc_line2_start_point,3);
    InitEndPointDataBuf(&arc_end_point,4);

    arc_start_point.wComConfig  = 18;
    arc_start_point.wWorkAdjCfg = 512;

    arc_mid_point.wComConfig  = 19;
    arc_mid_point.wWorkAdjCfg = 512;

    arc_end_point.wComConfig  = 20;
    arc_end_point.wWorkAdjCfg = 512;

    ArcMidToLine1EndPoint(&arc_mid_point,&arc_line1_end_point);
    ArcMidToLine2StartPoint(&arc_mid_point,&arc_line2_start_point);
    
    InitStartPointDataBuf(&arc_start_point,1);
    InitEndPointDataBuf(&arc_line1_end_point,2);

    InitStartPointDataBuf(&arc_line2_start_point,3);
    InitEndPointDataBuf(&arc_end_point,4);

    TEST_ASSERT_EQUAL_UINT32(2,*((unsigned int *)pdata + 2));
    TEST_ASSERT_EQUAL_UINT32(15,*((unsigned int *)pdata + 3));
    TEST_ASSERT_EQUAL_UINT32(17,*((unsigned int *)pdata + 4));
    TEST_ASSERT_EQUAL_UINT32(3 ,*((unsigned int *)pdata + 5));
    TEST_ASSERT_EQUAL_UINT32(1000,*((unsigned int *)pdata + 6));
    TEST_ASSERT_EQUAL_UINT32(2000,*((unsigned int *)pdata + 7));
    TEST_ASSERT_EQUAL_UINT32(2000,*((unsigned int *)pdata + 8));
    TEST_ASSERT_EQUAL_UINT32(18,*((unsigned int *)pdata + 9));
    TEST_ASSERT_EQUAL_UINT32(20,*((unsigned int *)pdata + 10));
    TEST_ASSERT_EQUAL_UINT32(3 ,*((unsigned int *)pdata + 11));
    TEST_ASSERT_EQUAL_UINT32(1000,*((unsigned int *)pdata + 12));
    TEST_ASSERT_EQUAL_UINT32(2000,*((unsigned int *)pdata + 13));
    TEST_ASSERT_EQUAL_UINT32(2000,*((unsigned int *)pdata + 14));
    TEST_ASSERT_EQUAL_UINT32(15 ,get_AxisZAdjustBufLength());
}

void test_Arc2Line_DontAdjutEndArcAndOneWholeArc(void)
{
    StartPoint_T arc_start_point;    
    MidPoint_T   arc_mid_point;    
    EndPoint_T   arc_end_point;    

    EndPoint_T   arc_line1_end_point;
    StartPoint_T arc_line2_start_point;

    arc_start_point.wComConfig  = 15;
    arc_start_point.wWorkAdjCfg = 0;

    arc_mid_point.wComConfig  = 16;
    arc_mid_point.wWorkAdjCfg = 0;

    arc_end_point.wComConfig  = 17;
    arc_end_point.wWorkAdjCfg = 256;

    ArcMidToLine1EndPoint(&arc_mid_point,&arc_line1_end_point);
    ArcMidToLine2StartPoint(&arc_mid_point,&arc_line2_start_point);
    
    InitStartPointDataBuf(&arc_start_point,1);
    InitEndPointDataBuf(&arc_line1_end_point,2);

    InitStartPointDataBuf(&arc_line2_start_point,3);
    InitEndPointDataBuf(&arc_end_point,LINE2_END_POINT);

    arc_start_point.wComConfig  = 18;
    arc_start_point.wWorkAdjCfg = 512;

    arc_mid_point.wComConfig  = 19;
    arc_mid_point.wWorkAdjCfg = 512;

    arc_end_point.wComConfig  = 20;
    arc_end_point.wWorkAdjCfg = 512;

    ArcMidToLine1EndPoint(&arc_mid_point,&arc_line1_end_point);
    ArcMidToLine2StartPoint(&arc_mid_point,&arc_line2_start_point);
    
    InitStartPointDataBuf(&arc_start_point,1);
    InitEndPointDataBuf(&arc_line1_end_point,2);

    InitStartPointDataBuf(&arc_line2_start_point,3);
    InitEndPointDataBuf(&arc_end_point,4);

    TEST_ASSERT_EQUAL_UINT32(15,*((unsigned int *)pdata + 3));
    TEST_ASSERT_EQUAL_UINT32(17,*((unsigned int *)pdata + 4));
    TEST_ASSERT_EQUAL_UINT32(5 ,*((unsigned int *)pdata + 5));
    TEST_ASSERT_EQUAL_UINT32(1000,*((unsigned int *)pdata + 6));
    TEST_ASSERT_EQUAL_UINT32(2000,*((unsigned int *)pdata + 7));
    TEST_ASSERT_EQUAL_UINT32(1000,*((unsigned int *)pdata + 8));
    TEST_ASSERT_EQUAL_UINT32(2000,*((unsigned int *)pdata + 9));
    TEST_ASSERT_EQUAL_UINT32(2000,*((unsigned int *)pdata + 10));
    TEST_ASSERT_EQUAL_UINT32(11 ,get_AxisZAdjustBufLength());
}

void test_Arc2Line_SerialArc(void)
{
    StartPoint_T arc_start_point;    
    MidPoint_T   arc_mid_point;    
    EndPoint_T   arc_end_point;    

    EndPoint_T   arc_line1_end_point;
    StartPoint_T arc_line2_start_point;

    arc_start_point.wComConfig  = 15;
    arc_start_point.wWorkAdjCfg = 0;

    arc_mid_point.wComConfig  = 16;
    arc_mid_point.wWorkAdjCfg = 0;

    arc_end_point.wComConfig  = 17;
    arc_end_point.wWorkAdjCfg = 256;

    ArcMidToLine1EndPoint(&arc_mid_point,&arc_line1_end_point);
    ArcMidToLine2StartPoint(&arc_mid_point,&arc_line2_start_point);
    
    InitStartPointDataBuf(&arc_start_point,1);
    InitEndPointDataBuf(&arc_line1_end_point,2);

    InitStartPointDataBuf(&arc_line2_start_point,3);
    InitEndPointDataBuf(&arc_end_point,4);

    arc_start_point.wComConfig  = 18;
    arc_start_point.wWorkAdjCfg = 0;

    arc_mid_point.wComConfig  = 19;
    arc_mid_point.wWorkAdjCfg = 0;

    arc_end_point.wComConfig  = 20;
    arc_end_point.wWorkAdjCfg = 256;

    ArcMidToLine1EndPoint(&arc_mid_point,&arc_line1_end_point);
    ArcMidToLine2StartPoint(&arc_mid_point,&arc_line2_start_point);
    
    InitStartPointDataBuf(&arc_start_point,1);
    InitEndPointDataBuf(&arc_line1_end_point,2);

    InitStartPointDataBuf(&arc_line2_start_point,3);
    InitEndPointDataBuf(&arc_end_point,4);

    arc_start_point.wComConfig  = 21;
    arc_start_point.wWorkAdjCfg = 512;

    arc_mid_point.wComConfig  = 22;
    arc_mid_point.wWorkAdjCfg = 512;

    arc_end_point.wComConfig  = 23;
    arc_end_point.wWorkAdjCfg = 512;

    ArcMidToLine1EndPoint(&arc_mid_point,&arc_line1_end_point);
    ArcMidToLine2StartPoint(&arc_mid_point,&arc_line2_start_point);
    
    InitStartPointDataBuf(&arc_start_point,1);
    InitEndPointDataBuf(&arc_line1_end_point,2);

    InitStartPointDataBuf(&arc_line2_start_point,3);
    InitEndPointDataBuf(&arc_end_point,4);

    TEST_ASSERT_EQUAL_UINT32(15,*((unsigned int *)pdata + 3));
    TEST_ASSERT_EQUAL_UINT32(17,*((unsigned int *)pdata + 4));
    TEST_ASSERT_EQUAL_UINT32(7 ,*((unsigned int *)pdata + 5));
    TEST_ASSERT_EQUAL_UINT32(1000,*((unsigned int *)pdata + 6));
    TEST_ASSERT_EQUAL_UINT32(2000,*((unsigned int *)pdata + 7));
    TEST_ASSERT_EQUAL_UINT32(1000,*((unsigned int *)pdata + 8));
    TEST_ASSERT_EQUAL_UINT32(2000,*((unsigned int *)pdata + 9));
    TEST_ASSERT_EQUAL_UINT32(1000,*((unsigned int *)pdata + 10));
    TEST_ASSERT_EQUAL_UINT32(2000,*((unsigned int *)pdata + 11));
    TEST_ASSERT_EQUAL_UINT32(2000,*((unsigned int *)pdata + 12));
    TEST_ASSERT_EQUAL_UINT32(13 ,get_AxisZAdjustBufLength());
}

void test_Arc2Line_LastPointNotAdjust(void)
{
    StartPoint_T arc_start_point;    
    MidPoint_T   arc_mid_point;    
    EndPoint_T   arc_end_point;    

    EndPoint_T   arc_line1_end_point;
    StartPoint_T arc_line2_start_point;

    arc_start_point.wComConfig  = 15;
    arc_start_point.wWorkAdjCfg = 0;

    arc_mid_point.wComConfig  = 16;
    arc_mid_point.wWorkAdjCfg = 0;

    arc_end_point.wComConfig  = 17;
    arc_end_point.wWorkAdjCfg = 256;

    ArcMidToLine1EndPoint(&arc_mid_point,&arc_line1_end_point);
    ArcMidToLine2StartPoint(&arc_mid_point,&arc_line2_start_point);
    
    InitStartPointDataBuf(&arc_start_point,1);
    InitEndPointDataBuf(&arc_line1_end_point,2);

    InitStartPointDataBuf(&arc_line2_start_point,3);
    InitEndPointDataBuf(&arc_end_point,4);

    arc_start_point.wComConfig  = 18;
    arc_start_point.wWorkAdjCfg = 0;

    arc_mid_point.wComConfig  = 19;
    arc_mid_point.wWorkAdjCfg = 0;

    arc_end_point.wComConfig  = 20;
    arc_end_point.wWorkAdjCfg = 256;

    ArcMidToLine1EndPoint(&arc_mid_point,&arc_line1_end_point);
    ArcMidToLine2StartPoint(&arc_mid_point,&arc_line2_start_point);
    
    InitStartPointDataBuf(&arc_start_point,1);
    InitEndPointDataBuf(&arc_line1_end_point,2);

    InitStartPointDataBuf(&arc_line2_start_point,3);
    InitEndPointDataBuf(&arc_end_point,4);

    arc_start_point.wComConfig  = 21;
    arc_start_point.wWorkAdjCfg = 512;

    arc_mid_point.wComConfig  = 22;
    arc_mid_point.wWorkAdjCfg = 512;

    arc_end_point.wComConfig  = 23;
    arc_end_point.wWorkAdjCfg = 768;

    ArcMidToLine1EndPoint(&arc_mid_point,&arc_line1_end_point);
    ArcMidToLine2StartPoint(&arc_mid_point,&arc_line2_start_point);
    
    InitStartPointDataBuf(&arc_start_point,1);
    InitEndPointDataBuf(&arc_line1_end_point,2);

    InitStartPointDataBuf(&arc_line2_start_point,3);
    InitEndPointDataBuf(&arc_end_point,4);

    TEST_ASSERT_EQUAL_UINT32(15,*((unsigned int *)pdata + 3));
    TEST_ASSERT_EQUAL_UINT32(17,*((unsigned int *)pdata + 4));
    TEST_ASSERT_EQUAL_UINT32(6 ,*((unsigned int *)pdata + 5));

    TEST_ASSERT_EQUAL_UINT32(1000,*((unsigned int *)pdata + 6));
    TEST_ASSERT_EQUAL_UINT32(2000,*((unsigned int *)pdata + 7));

    TEST_ASSERT_EQUAL_UINT32(1000,*((unsigned int *)pdata + 8));
    TEST_ASSERT_EQUAL_UINT32(2000,*((unsigned int *)pdata + 9));

    TEST_ASSERT_EQUAL_UINT32(1000,*((unsigned int *)pdata + 10));
    TEST_ASSERT_EQUAL_UINT32(2000,*((unsigned int *)pdata + 11));

    TEST_ASSERT_EQUAL_UINT32(12 ,get_AxisZAdjustBufLength());
}

void test_Arc2Line_PartAdjust(void)
{
    StartPoint_T arc_start_point;    
    MidPoint_T   arc_mid_point;    
    EndPoint_T   arc_end_point;    

    EndPoint_T   arc_line1_end_point;
    StartPoint_T arc_line2_start_point;

    arc_start_point.wComConfig  = 15;
    arc_start_point.wWorkAdjCfg = 768;

    arc_mid_point.wComConfig  = 16;
    arc_mid_point.wWorkAdjCfg = 768;

    arc_end_point.wComConfig  = 17;
    arc_end_point.wWorkAdjCfg = 768;

    ArcMidToLine1EndPoint(&arc_mid_point,&arc_line1_end_point);
    ArcMidToLine2StartPoint(&arc_mid_point,&arc_line2_start_point);
    
    InitStartPointDataBuf(&arc_start_point,1);
    InitEndPointDataBuf(&arc_line1_end_point,2);

    InitStartPointDataBuf(&arc_line2_start_point,3);
    InitEndPointDataBuf(&arc_end_point,4);

    arc_start_point.wComConfig  = 18;
    arc_start_point.wWorkAdjCfg = 512;

    arc_mid_point.wComConfig  = 19;
    arc_mid_point.wWorkAdjCfg = 512;

    arc_end_point.wComConfig  = 20;
    arc_end_point.wWorkAdjCfg = 512;

    ArcMidToLine1EndPoint(&arc_mid_point,&arc_line1_end_point);
    ArcMidToLine2StartPoint(&arc_mid_point,&arc_line2_start_point);
    
    InitStartPointDataBuf(&arc_start_point,1);
    InitEndPointDataBuf(&arc_line1_end_point,2);

    InitStartPointDataBuf(&arc_line2_start_point,3);
    InitEndPointDataBuf(&arc_end_point,4);

    arc_start_point.wComConfig  = 21;
    arc_start_point.wWorkAdjCfg = 768;

    arc_mid_point.wComConfig  = 22;
    arc_mid_point.wWorkAdjCfg = 768;

    arc_end_point.wComConfig  = 23;
    arc_end_point.wWorkAdjCfg = 768;

    ArcMidToLine1EndPoint(&arc_mid_point,&arc_line1_end_point);
    ArcMidToLine2StartPoint(&arc_mid_point,&arc_line2_start_point);
    
    InitStartPointDataBuf(&arc_start_point,1);
    InitEndPointDataBuf(&arc_line1_end_point,2);

    InitStartPointDataBuf(&arc_line2_start_point,3);
    InitEndPointDataBuf(&arc_end_point,4);

    TEST_ASSERT_EQUAL_UINT32(18,*((unsigned int *)pdata + 3));
    TEST_ASSERT_EQUAL_UINT32(20,*((unsigned int *)pdata + 4));
    TEST_ASSERT_EQUAL_UINT32( 3,*((unsigned int *)pdata + 5));

    TEST_ASSERT_EQUAL_UINT32(1000,*((unsigned int *)pdata + 6));
    TEST_ASSERT_EQUAL_UINT32(2000,*((unsigned int *)pdata + 7));
    TEST_ASSERT_EQUAL_UINT32(2000,*((unsigned int *)pdata + 8));

    TEST_ASSERT_EQUAL_UINT32(9,get_AxisZAdjustBufLength());

}

