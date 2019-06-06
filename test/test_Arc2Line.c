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

    /** TEST_ASSERT_EQUAL_UINT32(compare_point.wOrder      , convert_point.wOrder); */
    /** TEST_ASSERT_EQUAL_UINT32(compare_point.wComConfig  , convert_point.wComConfig); */
    /** TEST_ASSERT_EQUAL_UINT32(compare_point.wX          , convert_point.wX); */
    /** TEST_ASSERT_EQUAL_UINT32(compare_point.wY          , convert_point.wY); */
    /** TEST_ASSERT_EQUAL_UINT32(compare_point.wZ          , convert_point.wZ); */
    /** TEST_ASSERT_EQUAL_INT32 (compare_point.iR          , convert_point.iR); */
    /** TEST_ASSERT_EQUAL_INT32 (compare_point.iA          , convert_point.iA); */
    /** TEST_ASSERT_EQUAL_INT32 (compare_point.iB          , convert_point.iB); */
    /** TEST_ASSERT_EQUAL_UINT32(compare_point.wId         , convert_point.wId); */
    /** TEST_ASSERT_EQUAL_UINT32(compare_point.wUpDistance , convert_point.wUpDistance); */
    /** TEST_ASSERT_EQUAL_INT32 (compare_point.iDelay      , convert_point.iDelay); */
    /** TEST_ASSERT_EQUAL_UINT32(compare_point.wGlue       , convert_point.wGlue); */
    /** TEST_ASSERT_EQUAL_UINT32(compare_point.wName[0]    , convert_point.wName[0]); */
    /** TEST_ASSERT_EQUAL_UINT32(compare_point.wName[1]    , convert_point.wName[1]); */
    /** TEST_ASSERT_EQUAL_UINT32(compare_point.wName[2]    , convert_point.wName[2]); */
    /** TEST_ASSERT_EQUAL_UINT32(compare_point.wName[3]    , convert_point.wName[3]); */
    /** TEST_ASSERT_EQUAL_UINT32(compare_point.wWorkAdjCfg , convert_point.wWorkAdjCfg); */
    /** TEST_ASSERT_EQUAL_UINT32(compare_point.wRev        , convert_point.wRev); */
}

void test_Arc2Line_ArcMidToLine2StartPoint(void)
{
    StartPoint_T convert_point; 

    const StartPoint_T compare_point = {21,22,23,24,25,26,27,28,29,110,111,0,113,0,{0,0,0,0},116,210};
    
    ArcMidToLine2StartPoint(&ArcMidPoint,&convert_point);

    TEST_ASSERT_EQUAL_MEMORY(&compare_point,&compare_point,sizeof(StartPoint_T));

    /** TEST_ASSERT_EQUAL_UINT32(compare_point.wOrder      , convert_point.wOrder); */
    /** TEST_ASSERT_EQUAL_UINT32(compare_point.wComConfig  , convert_point.wComConfig); */
    /** TEST_ASSERT_EQUAL_UINT32(compare_point.wX          , convert_point.wX); */
    /** TEST_ASSERT_EQUAL_UINT32(compare_point.wY          , convert_point.wY); */
    /** TEST_ASSERT_EQUAL_UINT32(compare_point.wZ          , convert_point.wZ); */
    /** TEST_ASSERT_EQUAL_INT32 (compare_point.iR          , convert_point.iR); */
    /** TEST_ASSERT_EQUAL_INT32 (compare_point.iA          , convert_point.iA); */
    /** TEST_ASSERT_EQUAL_INT32 (compare_point.iB          , convert_point.iB); */
    /** TEST_ASSERT_EQUAL_UINT32(compare_point.wId         , convert_point.wId); */
    /** TEST_ASSERT_EQUAL_UINT32(compare_point.wBlankSpeed , convert_point.wBlankSpeed); */
    /** TEST_ASSERT_EQUAL_UINT32(compare_point.wWorkSpeed  , convert_point.wWorkSpeed); */
    /** TEST_ASSERT_EQUAL_INT32 (compare_point.iDelay      , convert_point.iDelay); */
    /** TEST_ASSERT_EQUAL_UINT32(compare_point.wGlue       , convert_point.wGlue); */
    /** TEST_ASSERT_EQUAL_UINT32(compare_point.wJobConfig  , convert_point.wJobConfig); */
    /** TEST_ASSERT_EQUAL_UINT32(compare_point.wName[0]    , convert_point.wName[0]); */
    /** TEST_ASSERT_EQUAL_UINT32(compare_point.wName[1]    , convert_point.wName[1]); */
    /** TEST_ASSERT_EQUAL_UINT32(compare_point.wName[2]    , convert_point.wName[2]); */
    /** TEST_ASSERT_EQUAL_UINT32(compare_point.wName[3]    , convert_point.wName[3]); */
    /** TEST_ASSERT_EQUAL_UINT32(compare_point.wData       , convert_point.wData); */
    /** TEST_ASSERT_EQUAL_UINT32(compare_point.wWorkAdjCfg , convert_point.wWorkAdjCfg); */
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

    InitStartPointDataBuf(&start_point);

    TEST_ASSERT_EQUAL_UINT32(15  ,*((unsigned int *)pdata + 3));
    TEST_ASSERT_EQUAL_UINT32(16  ,*((unsigned int *)pdata + 4));
    TEST_ASSERT_EQUAL_UINT32(0   ,*((unsigned int *)pdata + 5));
    TEST_ASSERT_EQUAL_UINT32(6,get_AxisZAdjustBufLength());
}

void test_Arc2Line_LineStartPointNotAdjust(void)
{
    StartPoint_T start_point;
    start_point.wComConfig  = 15;
    start_point.wWorkAdjCfg = 256;

    InitStartPointDataBuf(&start_point);

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

    InitEndPointDataBuf(&end_point);

    TEST_ASSERT_EQUAL_UINT32(15  ,*((unsigned int *)pdata + 3));
    TEST_ASSERT_EQUAL_UINT32(16  ,*((unsigned int *)pdata + 4));
    TEST_ASSERT_EQUAL_UINT32(0   ,*((unsigned int *)pdata + 5));
    TEST_ASSERT_EQUAL_UINT32(6,get_AxisZAdjustBufLength());
}

void test_Arc2Line_LineEndPointNotAdjust(void)
{
    EndPoint_T end_point;
    end_point.wComConfig  = 15;
    end_point.wWorkAdjCfg = 256;

    InitEndPointDataBuf(&end_point);

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
    end_point.wComConfig  = 15;
    end_point.wWorkAdjCfg = 0;

    InitStartPointDataBuf(&start_point);
    InitEndPointDataBuf(&end_point);

    TEST_ASSERT_EQUAL_UINT32(15  ,*((unsigned int *)pdata + 3));
    TEST_ASSERT_EQUAL_UINT32(16  ,*((unsigned int *)pdata + 4));
    TEST_ASSERT_EQUAL_UINT32(0   ,*((unsigned int *)pdata + 5));
    TEST_ASSERT_EQUAL_UINT32(6,get_AxisZAdjustBufLength());
}

void test_Arc2Line_OneLineOnlyNeedStartAdjust(void)
{
    StartPoint_T start_point;
    start_point.wComConfig  = 15;
    start_point.wWorkAdjCfg = 0;

    EndPoint_T end_point;
    end_point.wComConfig  = 15;
    end_point.wWorkAdjCfg = 256;

    InitStartPointDataBuf(&start_point);
    InitEndPointDataBuf(&end_point);

    TEST_ASSERT_EQUAL_UINT32(15  ,*((unsigned int *)pdata + 3));
    TEST_ASSERT_EQUAL_UINT32(16  ,*((unsigned int *)pdata + 4));
    TEST_ASSERT_EQUAL_UINT32(0   ,*((unsigned int *)pdata + 5));
    TEST_ASSERT_EQUAL_UINT32(6,get_AxisZAdjustBufLength());
}

void test_Arc2Line_OneLineNeedWholeAdjust(void)
{
    StartPoint_T start_point;
    start_point.wComConfig  = 15;
    start_point.wWorkAdjCfg = 0;

    EndPoint_T end_point;
    end_point.wComConfig  = 15;
    end_point.wWorkAdjCfg = 0;

    InitStartPointDataBuf(&start_point);
    InitEndPointDataBuf(&end_point);

    TEST_ASSERT_EQUAL_UINT32(15  ,*((unsigned int *)pdata + 3));
    TEST_ASSERT_EQUAL_UINT32(16  ,*((unsigned int *)pdata + 4));
    TEST_ASSERT_EQUAL_UINT32(0   ,*((unsigned int *)pdata + 5));
    TEST_ASSERT_EQUAL_UINT32(6,get_AxisZAdjustBufLength());
}

void test_Arc2Line_MultLineNeedWholeAdjust(void)
{
    StartPoint_T start_point;
    start_point.wComConfig  = 15;
    start_point.wWorkAdjCfg = 0;

    EndPoint_T end_point;
    end_point.wComConfig  = 15;
    end_point.wWorkAdjCfg = 0;

    InitStartPointDataBuf(&start_point);
    InitEndPointDataBuf(&end_point);

    InitStartPointDataBuf(&start_point);
    InitEndPointDataBuf(&end_point);

    InitStartPointDataBuf(&start_point);
    InitEndPointDataBuf(&end_point);

    TEST_ASSERT_EQUAL_UINT32(15  ,*((unsigned int *)pdata + 3));
    TEST_ASSERT_EQUAL_UINT32(16  ,*((unsigned int *)pdata + 4));
    TEST_ASSERT_EQUAL_UINT32(0   ,*((unsigned int *)pdata + 5));
    TEST_ASSERT_EQUAL_UINT32(15  ,*((unsigned int *)pdata + 6));
    TEST_ASSERT_EQUAL_UINT32(16  ,*((unsigned int *)pdata + 7));
    TEST_ASSERT_EQUAL_UINT32(0   ,*((unsigned int *)pdata + 8));
    TEST_ASSERT_EQUAL_UINT32(12,get_AxisZAdjustBufLength());
}

void test_Arc2Line_OneLineWholeDontAdjust(void)
{
    StartPoint_T start_point;
    start_point.wComConfig  = 15;
    start_point.wWorkAdjCfg = 256;

    EndPoint_T end_point;
    end_point.wComConfig  = 15;
    end_point.wWorkAdjCfg = 256;

    InitStartPointDataBuf(&start_point);
    InitEndPointDataBuf(&end_point);

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

    StartPoint_T arc_line1_end_point;
    EndPoint_T   arc_line2_start_point;

    arc_start_point.wComConfig  = 15;
    arc_start_point.wWorkAdjCfg = 0;

    arc_mid_point.wComConfig  = 16;
    arc_mid_point.wWorkAdjCfg = 0;

    arc_end_point.wComConfig  = 17;
    arc_end_point.wWorkAdjCfg = 0;

    ArcMidToLine1EndPoint(&arc_mid_point,&arc_line1_end_point);
    ArcMidToLine1EndPoint(&arc_mid_point,&arc_line2_start_point);
    
    InitStartPointDataBuf(&arc_start_point);
    InitEndPointDataBuf(&arc_line1_end_point);

    InitStartPointDataBuf(&arc_line2_start_point);
    InitEndPointDataBuf(&arc_end_point);

    TEST_ASSERT_EQUAL_UINT32(15,*((unsigned int *)pdata + 3));
    TEST_ASSERT_EQUAL_UINT32(17,*((unsigned int *)pdata + 4));
    TEST_ASSERT_EQUAL_UINT32(0 ,*((unsigned int *)pdata + 5));
    TEST_ASSERT_EQUAL_UINT32(6 ,get_AxisZAdjustBufLength());
}
