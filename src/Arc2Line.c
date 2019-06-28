#include "Arc2Line.h"

static Line1StartPointElemet_Copy Line1StartPoint_Copy = {0,0,0,0}; 
unsigned int IsAlreadyHasLineDataBuf = 0;

void CopyArcStartPoint(StartPoint_T *ArcStartPoint)
{
     Line1StartPoint_Copy.wBlankSpeed = ArcStartPoint->wBlankSpeed;
     Line1StartPoint_Copy.wWorkSpeed  = ArcStartPoint->wWorkSpeed;  
     Line1StartPoint_Copy.wGlue       = ArcStartPoint->wGlue;       
     Line1StartPoint_Copy.wData       = ArcStartPoint->wData;       
}

void ArcMidToLine1EndPoint(MidPoint_T *ArcMidPoint,EndPoint_T *Line1EndPoint)
{
    /**
     * @brief 拷贝ArcMidPoint的基本参数到Line1EndPoint 
    */
    Line1EndPoint->wOrder      = ArcMidPoint->wOrder;
    Line1EndPoint->wComConfig  = ArcMidPoint->wComConfig;
    Line1EndPoint->wX          = ArcMidPoint->wX;
    Line1EndPoint->wY          = ArcMidPoint->wY;
    Line1EndPoint->wZ          = ArcMidPoint->wZ;
    Line1EndPoint->iR          = ArcMidPoint->iR;
    Line1EndPoint->iA          = ArcMidPoint->iA;
    Line1EndPoint->iB          = ArcMidPoint->iB;
    Line1EndPoint->wId         = ArcMidPoint->wId;
    Line1EndPoint->wWorkAdjCfg = ArcMidPoint->wWorkAdjCfg;

    /**
     * @brief 拷贝Line1StartPoint的胶头到Line1EndPoint
     */
    Line1EndPoint->wGlue       = Line1StartPoint_Copy.wGlue;

    /**
     * @brief 将Line1EndPoint的上抬高度,开胶延时,点标识强制,REV为0
     */
    Line1EndPoint->wUpDistance = 0;
    Line1EndPoint->iDelay      = 0;
    memset(Line1EndPoint->wName,0,sizeof(unsigned int)*4);
    Line1EndPoint->wRev        = 0;
}

void ArcMidToLine2StartPoint(MidPoint_T *ArcMidPoint,StartPoint_T *Line2StartPoint)
{
    /**
     * @brief 拷贝ArcMidPoint的基本参数到Line2StartPoint 
     */
    Line2StartPoint->wOrder      = ArcMidPoint->wOrder;
    Line2StartPoint->wComConfig  = ArcMidPoint->wComConfig;
    Line2StartPoint->wX          = ArcMidPoint->wX;
    Line2StartPoint->wY          = ArcMidPoint->wY;
    Line2StartPoint->wZ          = ArcMidPoint->wZ;
    Line2StartPoint->iR          = ArcMidPoint->iR;
    Line2StartPoint->iA          = ArcMidPoint->iA;
    Line2StartPoint->iB          = ArcMidPoint->iB;
    Line2StartPoint->wId         = ArcMidPoint->wId;
    Line2StartPoint->wWorkAdjCfg = ArcMidPoint->wWorkAdjCfg;

    /**
     * @brief 拷贝Line1StartPoint的空移速度,加工速度,摆抢,胶头到Line2StartPoint
     */
    Line2StartPoint->wBlankSpeed = Line1StartPoint_Copy.wBlankSpeed;
    Line2StartPoint->wWorkSpeed  = Line1StartPoint_Copy.wWorkSpeed;
    Line2StartPoint->wGlue       = Line1StartPoint_Copy.wGlue;
    Line2StartPoint->wData       = Line1StartPoint_Copy.wData;

    /**
     * @brief 将Line2StartPoint的开胶延时,点标识强制,JOB处理为0
     */
    Line2StartPoint->iDelay      = 0;
    Line2StartPoint->wJobConfig  = 0;
    memset(Line2StartPoint->wName,0,sizeof(unsigned int)*4);
}

unsigned int ConvertArcOrderToLineOrder(unsigned int arc_order)
{
    unsigned int line_order;

    static unsigned char cnt = 0;
    if(cnt >= 2)cnt = 0;

    switch (arc_order) {
        case ORDER_ARC_START:
            line_order = ORDER_LINE_START;
            break;
        case ORDER_ARC_MID:
            if(cnt == 0)line_order = ORDER_LINE_END;
            if(cnt == 1)line_order = ORDER_LINE_START;
            cnt++;
            break;
        case ORDER_ARC_END:
            line_order = ORDER_LINE_END;
            break;
        default:
            line_order = 0;
            break;
    }

    return line_order;
}

/**
 * @brief   InitStartPointDataBuf 
 *
 * @param   line_start_point
 * @param   is_arc_point
 */
void InitStartPointDataBuf(StartPoint_T* line_start_point,unsigned int is_arc_point)
{
    unsigned int IsAlreadyAdjust   = (line_start_point->wWorkAdjCfg >> 8) & 0x01;
    unsigned int IsLastAdjustPoint = (line_start_point->wWorkAdjCfg >> 9) & 0x01;
    unsigned int wInstrIndex       =  line_start_point->wComConfig & FILE_INSTR_INDEX_ORIGIN_INDEX_MASK;

    if (IsAlreadyAdjust == 0) {
        if (is_arc_point) {
            if(is_arc_point == LINE1_START_POINT && IsAlreadyHasLineDataBuf++ == 0) create_AxisZAdjustDataHeader(wInstrIndex,wInstrIndex + 2);
            if(is_arc_point == LINE2_START_POINT) return;
        } else {
            if(IsAlreadyHasLineDataBuf++ == 0) create_AxisZAdjustDataHeader(wInstrIndex,wInstrIndex + 1);
        }
        insert_AxisZAdjustData(1000);
    }
}

void InitEndPointDataBuf(EndPoint_T* line_point,unsigned int is_arc_point)
{
    unsigned int IsAlreadyAdjust   = (line_point->wWorkAdjCfg >> 8) & 0x01;
    unsigned int IsLastAdjustPoint = (line_point->wWorkAdjCfg >> 9) & 0x01;
    unsigned int wInstrIndex       =  line_point->wComConfig & FILE_INSTR_INDEX_ORIGIN_INDEX_MASK;

    if (IsAlreadyAdjust == 0) {
        if (is_arc_point) {
           if (is_arc_point == LINE1_END_POINT) ; 
           if (is_arc_point == LINE2_END_POINT && IsLastAdjustPoint) IsAlreadyHasLineDataBuf = 0; 
        } else {
           if (IsAlreadyHasLineDataBuf == 0) create_AxisZAdjustDataHeader(wInstrIndex - 1,wInstrIndex);
           /** else IsAlreadyHasLineDataBuf = 0; */
           else if(IsLastAdjustPoint) IsAlreadyHasLineDataBuf = 0;
        }
        insert_AxisZAdjustData(2000);
    }
    else{
          if (is_arc_point) {
             if (is_arc_point == LINE2_END_POINT && IsLastAdjustPoint) IsAlreadyHasLineDataBuf = 0;
		  }
          else {
              if(IsLastAdjustPoint) IsAlreadyHasLineDataBuf = 0;
          }
    }
}
