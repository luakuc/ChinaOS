/******************************************************Copyright (c)**************************************************
**
**                              Copyright (c) 2009,2011 Fengliang And His Friends Corporation.
**
**                                             E-Mail: ChinaFengliang@163.com
**
**
**---------File Information-------------------------------------------------------------------------------------------
** File name:            uart1.h
** Last version:         V1.00
** Descriptions:         uart1驱动头文件.
** Hardware platform:    
** SoftWare platform:
**
**--------------------------------------------------------------------------------------------------------------------
** Created by:           FengLiang
** Created date:         2011年2月19日  21:24:27
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
#ifndef __UART1_H
#define __UART1_H

#ifdef __cplusplus
extern "C" {
#endif                                                                      /* __cplusplus                          */

/*********************************************************************************************************************
                                                    头文件区
*********************************************************************************************************************/
#include    "../../../include/OS_macro.h"
#include    "../../../include/OS_type.h"
#include    "../../device_config.h"
#include    "../uart.h"

/*********************************************************************************************************************
                                                    宏定义区
*********************************************************************************************************************/
/* uart1设备配置 ---------------------------------------------------------------------------------------------------*/
#define     DEVICE_UART1_EN							0						/* 设备配置(0:禁能; 1:使能)             */


/*********************************************************************************************************************
                                                    类型定义区
*********************************************************************************************************************/
/* 基本类型 --------------------------------------------------------------------------------------------------------*/


/*********************************************************************************************************************
                                                    接口申明区
*********************************************************************************************************************/
#if (DEVICE_UART1_EN == 1)
extern const CLASS_UART        uart1;                                       /* 设备: uart1                          */
#endif


#ifdef __cplusplus
}
#endif                                                                      /* __cplusplus                          */

#endif                                                                      /* end of __UART1_H                     */

/*********************************************************************************************************************
                                                    END OF FILE
*********************************************************************************************************************/

