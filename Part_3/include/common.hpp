//
// Created by liuky on 2020-07-30.
//

#ifndef NNIE_TUTORIAL_COMMON_HPP
#define NNIE_TUTORIAL_COMMON_HPP

#ifdef NDEBUG
#define DEBUG_LOG(msg, ...) void(0)
#else
#define DEBUG_LOG(msg, ...) printf("%s:%d\t" msg "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#define QUEUE_EMPTY -2
#define QUEUE_FULL -3
#define PAS 0
#define ERR -1

#define SDC_IN
#define SDC_OUT
#define SDC_IN_OUT

#define SAMPLE_SVP_COORDI_NUM                     4        /*num of coordinates*/
#define SAMPLE_SVP_PROPOSAL_WIDTH                 6        /*the width of each proposal array*/
#define SAMPLE_SVP_QUANT_BASE                     4096     /*the basic quantity*/
#define SAMPLE_SVP_NNIE_MAX_SOFTWARE_MEM_NUM      4
#define SAMPLE_SVP_NNIE_SSD_REPORT_NODE_NUM       12
#define SAMPLE_SVP_NNIE_SSD_PRIORBOX_NUM          6
#define SAMPLE_SVP_NNIE_SSD_SOFTMAX_NUM           6
#define SAMPLE_SVP_NNIE_SSD_ASPECT_RATIO_NUM      6
#define SAMPLE_SVP_NNIE_YOLOV1_WIDTH_GRID_NUM     7
#define SAMPLE_SVP_NNIE_YOLOV1_HEIGHT_GRID_NUM    7
#define SAMPLE_SVP_NNIE_EACH_SEG_STEP_ADDR_NUM    2
#define SAMPLE_SVP_NNIE_MAX_CLASS_NUM             30
#define SAMPLE_SVP_NNIE_MAX_ROI_NUM_OF_CLASS      50
#define SAMPLE_SVP_NNIE_REPORT_NAME_LENGTH        64

#include <stdio.h>
#include <fcntl.h>
#include <cstdlib>

typedef enum
{
    SAMPLE_SVP_ERR_LEVEL_DEBUG	 = 0x0,    /* debug-level								   */
    SAMPLE_SVP_ERR_LEVEL_INFO	 = 0x1,    /* informational 							   */
    SAMPLE_SVP_ERR_LEVEL_NOTICE  = 0x2,    /* normal but significant condition			   */
    SAMPLE_SVP_ERR_LEVEL_WARNING = 0x3,    /* warning conditions						   */
    SAMPLE_SVP_ERR_LEVEL_ERROR	 = 0x4,    /* error conditions							   */
    SAMPLE_SVP_ERR_LEVEL_CRIT	 = 0x5,    /* critical conditions						   */
    SAMPLE_SVP_ERR_LEVEL_ALERT	 = 0x6,    /* action must be taken immediately			   */
    SAMPLE_SVP_ERR_LEVEL_FATAL	= 0x7,	   /* just for compatibility with previous version */

    SAMPLE_SVP_ERR_LEVEL_BUTT
}SAMPLE_SVP_ERR_LEVEL_E;

#define SAMPLE_SVP_PRINTF(LevelStr,Msg, ...) do { fprintf(stderr,"[Level]:%s,[Func]:%s [Line]:%d [Info]:" Msg, LevelStr, __FUNCTION__, __LINE__,## __VA_ARGS__); } while (0)
#define SAMPLE_SVP_PRINTF_RED(LevelStr,Msg, ...) do { fprintf(stderr,"\033[0;31m [Level]:%s,[Func]:%s [Line]:%d [Info]:" Msg "\033[0;39m\n", LevelStr, __FUNCTION__, __LINE__,## __VA_ARGS__); } while (0)

#define SAMPLE_SVP_CHECK_EXPR_RET(Expr,Ret,Level,Msg, ...)
/* system is unusable	*/
#define SAMPLE_SVP_TRACE_FATAL(Msg,...)   SAMPLE_SVP_PRINTF_RED("Fatal",Msg,##__VA_ARGS__)
/* action must be taken immediately */
#define SAMPLE_SVP_TRACE_ALERT(Msg,...)   SAMPLE_SVP_PRINTF_RED("Alert",Msg,##__VA_ARGS__)
/* critical conditions */
#define SAMPLE_SVP_TRACE_CRIT(Msg,...)    SAMPLE_SVP_PRINTF_RED("Critical",Msg,##__VA_ARGS__)
/* error conditions */
#define SAMPLE_SVP_TRACE_ERR(Msg,...)     SAMPLE_SVP_PRINTF_RED("Error",Msg,##__VA_ARGS__)
/* warning conditions */
#define SAMPLE_SVP_TRACE_WARN(Msg,...)    SAMPLE_SVP_PRINTF("Warning",Msg,##__VA_ARGS__)
/* normal but significant condition  */
#define SAMPLE_SVP_TRACE_NOTICE(Msg,...)  SAMPLE_SVP_PRINTF("Notice",Msg,##__VA_ARGS__)
/* informational */
#define SAMPLE_SVP_TRACE_INFO(Msg,...)    SAMPLE_SVP_PRINTF("Info",Msg,##__VA_ARGS__)
/* debug-level messages  */
#define SAMPLE_SVP_TRACE_DEBUG(Msg, ...)  SAMPLE_SVP_PRINTF("Debug",Msg,##__VA_ARGS__)

#define SAMPLE_SVP_TRACE(Level,Msg, ...)\
do\
{\
	switch(Level){\
		case SAMPLE_SVP_ERR_LEVEL_DEBUG:\
		    SAMPLE_SVP_TRACE_DEBUG(Msg,##__VA_ARGS__);\
			break;\
		case SAMPLE_SVP_ERR_LEVEL_INFO:\
		    SAMPLE_SVP_TRACE_INFO(Msg,##__VA_ARGS__);\
			break;\
		case SAMPLE_SVP_ERR_LEVEL_NOTICE:\
		    SAMPLE_SVP_TRACE_NOTICE(Msg,##__VA_ARGS__);\
			break;\
		case SAMPLE_SVP_ERR_LEVEL_WARNING:\
		    SAMPLE_SVP_TRACE_WARN(Msg,##__VA_ARGS__);\
			break;\
		case SAMPLE_SVP_ERR_LEVEL_ERROR:\
			SAMPLE_SVP_TRACE_ERR(Msg,##__VA_ARGS__);\
			break;\
		case SAMPLE_SVP_ERR_LEVEL_CRIT:\
			SAMPLE_SVP_TRACE_CRIT(Msg,##__VA_ARGS__);\
			break;\
		case SAMPLE_SVP_ERR_LEVEL_ALERT:\
			SAMPLE_SVP_TRACE_ALERT(Msg,##__VA_ARGS__);\
			break;\
		case SAMPLE_SVP_ERR_LEVEL_FATAL:\
			SAMPLE_SVP_TRACE_FATAL(Msg,##__VA_ARGS__);\
			break;\
		default:\
			break;\
		}\
}while(0)


#define SAMPLE_SVP_CHECK_EXPR_TRACE(Expr,Level,Msg, ...)						 \
do{                                                                              \
	if(Expr)                                                                     \
	{                                                                            \
	   SAMPLE_SVP_TRACE(Level,Msg, ##__VA_ARGS__);                               \
	}                                                                            \
}while(0)


#define SAMPLE_SVP_CHECK_EXPR_GOTO(Expr, Label,Level,Msg, ...)                    \
do{																				  \
	if(Expr)                                                                      \
	{                                                                             \
		SAMPLE_SVP_TRACE(Level,Msg,## __VA_ARGS__);                               \
		goto Label;                                                               \
	}                                                                             \
}while(0)


#endif //NNIE_TUTORIAL_COMMON_HPP
