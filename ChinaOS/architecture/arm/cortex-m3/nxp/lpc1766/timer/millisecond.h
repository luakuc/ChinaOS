/******************************************************Copyright (c)**************************************************
**                                              胆怯是阻止一切可能的根本缘由
**
**                                             E-Mail: ChinaFengliang@163.com
**
**---------File Information-------------------------------------------------------------------------------------------
** File name:            millisecond.h
** Last version:         V1.00
** Descriptions:         毫秒定时器文件.
** Hardware platform:    
** SoftWare platform:    ChinaOS
**
**--------------------------------------------------------------------------------------------------------------------
** Created by:           Feng Liang
** Created date:         2012年2月9日  23:35:47
** Version:              V1.00
** Descriptions:         The original version
**
**--------------------------------------------------------------------------------------------------------------------
** Modified by: 
** Modified date:
** Version:
** Descriptions:
**
*********************************************************************************************************************/
#ifndef __MILLISECOND_H_
#define __MILLISECOND_H_

#ifdef __cplusplus
extern "C" {
#endif                                                                      /* __cplusplus                          */

/*********************************************************************************************************************
                                                    头文件区
*********************************************************************************************************************/
#include    <include/macro.h>
#include    <include/types.h>
#include    "./timer.h"

/*********************************************************************************************************************
                                                    设备定义区
*********************************************************************************************************************/
#if (DEVICE_MTIMER_EN == 1)
extern struct timer_t mtimer;
#endif


#ifdef __cplusplus
}
#endif                                                                      /* __cplusplus                          */

#endif                                                                      /* end of __MILLISECOND_H_              */
/*********************************************************************************************************************
                                                    END OF FILE
*********************************************************************************************************************/

