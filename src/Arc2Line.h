#ifndef _ARC2LINE_H
#define _ARC2LINE_H

#include <string.h>
#include "SaveAdjustData.h"

#define ORDER_LINE_START		0x12	/**< 直线起点	*/
#define ORDER_LINE_END			0x14	/**< 直线终点	*/
#define ORDER_ARC_START			0x15	/**< 圆弧起点	*/
#define ORDER_ARC_MID			0x16	/**< 圆弧中点*/
#define ORDER_ARC_END			0x17	/**< 圆弧终点*/
#define FILE_INSTR_INDEX_ORIGIN_INDEX_MASK		0x000007ff 
/** 3.直线起点、圆弧起点、圆起点*/
typedef struct _StartPoint{
	unsigned int wOrder;	/**< 指令标识	Bit31~16--指令0x12/0x15/0x18;Bit15~Bit0指令长度*/
	unsigned int wComConfig;/**< 综合配置，包括指令索引,图形运行中Job.....*/
	unsigned int wX;		/**< X坐标	单位mm*1000*/
	unsigned int wY;		/**< Y坐标	单位mm*1000*/
	unsigned int wZ;		/**< Z坐标	单位mm*1000*/
	int iR;					/**< R坐标	单位mm*1000*/
	int iA;					/**< A坐标	单位mm*1000*/
	int iB;					/**< B坐标	单位mm*1000*/
	unsigned int wId;		/**< 标识,包括各轴坐标选择和空移速度*/
	unsigned int wBlankSpeed;/**< 空移速度---mm/S*/
	unsigned int wWorkSpeed;/**< 加工速度选择---mm/S*/
	int iDelay;	/**< 延时	Bit0~15---开胶延时,单位mS*///M1410252
	unsigned int wGlue;		/**< 胶头	Bit0~7---分别对应8支胶枪开关状态，0关闭*/
	unsigned int wJobConfig;/**< Bit10~0：工作台移动前job号,Bit21~11：运动到当前点过程中Job号,Bit31~22：到达后Job号*/
	unsigned int wName[4];	/**< 点标识*/
	unsigned int wData;		/**< Bit0~7--摆枪参数:0--无；1~8摆枪参,Bit8~10：抛光摇摆轴
                                 0--无，1-X，2-Y，3-Z,Bit11~13：抛光补偿轴                                 
                                 0--无，1-X，2-Y，3-Z, Bit14~bit31保留，后续按位操作 */	//M1507091//M1809115                         
	unsigned int wWorkAdjCfg;/**< 校正索引号*/
}StartPoint_T;
#define SIZE_OF_START_POINT	(sizeof(StartPoint_T) / 4)

/** 4.圆弧中点、整圆中点*/
typedef struct _MidPoint{
	unsigned int wOrder;	/**< 指令标识	Bit31~16--指令0x12/0x15/0x18;Bit15~Bit0指令长度*/
	unsigned int wComConfig;/**< 综合配置，包括指令索引.....*/
	unsigned int wX;		/**< X坐标	单位mm*1000*/
	unsigned int wY;		/**< Y坐标	单位mm*1000*/
	unsigned int wZ;		/**< Z坐标	单位mm*1000*/
	int iR;					/**< R坐标	单位mm*1000*/
	int iA;					/**< A坐标	单位mm*1000*/
	int iB;					/**< B坐标	单位mm*1000*/
	unsigned int wId;		/**< 标识*/
	unsigned int wWorkAdjCfg;/**< 校正索引号*/
}MidPoint_T;
#define SIZE_OF_MID_POINT	(sizeof(MidPoint_T) / 4)

/** 5.直线终点、圆弧终点、整圆终点*/
typedef struct _EndPoint{
	unsigned int wOrder;	/**< 指令标识	Bit31~16---指令0x10/0x11;Bit15~Bit0指令长度*/
	unsigned int wComConfig;/**< 综合配置，包括指令索引,到达后Job.....*/
	unsigned int wX;		/**< X坐标	单位mm*1000*/
	unsigned int wY;		/**< Y坐标	单位mm*1000*/
	unsigned int wZ;		/**< Z坐标	单位mm*1000*/
	int iR;					/**< R坐标	单位mm*1000*/
	int iA;					/**< A坐标	单位mm*1000*/
	int iB;					/**< B坐标	单位mm*1000*/
	unsigned int wId;		/**< 标识*/
	unsigned int wUpDistance;	/**< 上抬高度	 单位mm*1000*/
	int iDelay;				/**< 延时	Bit0~15---关胶延时,单位mS*///M1410202
	unsigned int wGlue;		/**< 胶头	Bit0~7---分别对应8支胶枪开关状态，0关闭*/
	unsigned int wName[4];	/**< 点标识*/
	unsigned int wWorkAdjCfg;/**< 校正索引号*/
	unsigned int wRev;		/**< 保留*/
}EndPoint_T;
#define SIZE_OF_END_POINT	(sizeof(EndPoint_T) / 4)


/*! \struct _Line1StartPointElemet_Copy 
 *  \brief Brief struct description
 *
 *  Detailed description
 */
typedef struct _Line1StartPointElemet_Copy {
	unsigned int wBlankSpeed;
	unsigned int wWorkSpeed;
	unsigned int wGlue;	
	unsigned int wData;
} Line1StartPointElemet_Copy;

extern unsigned int IsAlreadyHasLineDataBuf;

void CopyArcStartPoint(StartPoint_T *ArcStartPoint);
void ArcMidToLine1EndPoint(MidPoint_T *ArcMidPoint,EndPoint_T *Line1EndPoint);
void ArcMidToLine2StartPoint(MidPoint_T *ArcMidPoint,StartPoint_T *Line2StartPoint);
unsigned int ConvertArcOrderToLineOrder(unsigned int arc_order);
void InitStartPointDataBuf(StartPoint_T* line_start_point);
void InitEndPointDataBuf(EndPoint_T* line_point);


#endif // _ARC2LINE_H
