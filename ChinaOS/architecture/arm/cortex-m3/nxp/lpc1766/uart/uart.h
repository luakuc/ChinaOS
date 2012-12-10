/******************************************************Copyright (c)**************************************************
**                                              胆怯是阻止一切可能的根本缘由
**
**                                             E-Mail: ChinaFengliang@163.com
**
**---------File Information-------------------------------------------------------------------------------------------
** File name:            uart.h
** Last version:         V1.00
** Descriptions:         uart0头文件.
** Hardware platform:    lpc17xx
** SoftWare platform:
**
**--------------------------------------------------------------------------------------------------------------------
** Created by:           Fengliang
** Created date:         2010年9月25日  14:27:37
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
#ifndef __UART_H_
#define __UART_H_

#ifdef __cplusplus
extern "C" {
#endif                                                                      /* __cplusplus                          */

/*********************************************************************************************************************
                                                    头文件区
*********************************************************************************************************************/
#include    <include/types.h>

/*********************************************************************************************************************
                                                    宏定义区
*********************************************************************************************************************/
/* 宏段名 ----------------------------------------------------------------------------------------------------------*/


/*********************************************************************************************************************
                                                    类型定义区
*********************************************************************************************************************/
/* 特征清单类型 ----------------------------------------------------------------------------------------------------*/
struct __uart_info
{
    INT32U          BaseAddress;                                            /* 寄存器基址                           */
    int             Priority;                                               /* 中断向量号                           */
};
typedef struct __uart_info                          UART_INFO;              /* 串口设备特征清单类型                 */

/* uart配置类型 ----------------------------------------------------------------------------------------------------*/
struct uart_config
{
	int             BaudRate;												/* 波特率								*/
	
	/*
	 * {5,6,7,8}
	 */
	char 			DataBit;												/* 数据位								*/

	/*
	 * {1, 1.5, 2}
	 */
	char 			StopBit;												/* 停止位								*/
	
	char			ParityBit;												/* 校验位								*/
	char			StreamControl;											/* 流控制								*/
};

/* 设备功能类型 ----------------------------------------------------------------------------------------------------*/
struct __class_uart
{
    int             (*setup)(void);                                    		/* 安装串口设备                         */
    STATUS          (*cleanup)(void);                                       /* 卸装串口设备                         */
    INT32S          (*send)(char *pBuffer, int Size);                       /* 发送字符                             */
    INT32S          (*recv)(char *pBuffer, int Size);                       /* 接收字符                             */
};
typedef struct __class_uart                         CLASS_UART;             /* 串口设备类型                         */

/*********************************************************************************************************************
** Function name:           uart_setup
** Descriptions:            安装uart0设备
** Input parameters:
** Output parameters:
** Returned value:
**--------------------------------------------------------------------------------------------------------------------
** Created by:              Fengliang
** Created Date:            2010-9-25  13:49:39
** Test recorde:
**--------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Test recorde:
*********************************************************************************************************************/
extern STATUS  uart_setup(const UART_INFO *This, int Speed);

/*********************************************************************************************************************
** Function name:           uart_cleanup
** Descriptions:            卸载uart0设备
** Input parameters:
** Output parameters:
** Returned value:
**--------------------------------------------------------------------------------------------------------------------
** Created by:              Fengliang
** Created Date:            2010-9-25  13:49:39
** Test recorde:
**--------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Test recorde:
*********************************************************************************************************************/
extern void uart_cleanup(const UART_INFO *This);

/*********************************************************************************************************************
** Function name:           uart_recv
** Descriptions:            接收字符
** Input parameters:        
** Output parameters:       
** Returned value:          接收字符数目
**--------------------------------------------------------------------------------------------------------------------
** Created by:              Fengliang
** Created Date:            2010-12-9  10:58:4
** Test recorde:            
**--------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Test recorde: 
*********************************************************************************************************************/
INT32S uart_recv(const UART_INFO *This, char *pBuffer, int Size);

/*********************************************************************************************************************
** Function name:           uart_send
** Descriptions:            输出字符
** Input parameters:        Char    : 输出字符
** Output parameters:       
** Returned value:          ==OS_OK : 操作成功
**                          !=OS_OK : 操作失败(包含出错信息)
**--------------------------------------------------------------------------------------------------------------------
** Created by:              Fengliang
** Created Date:            2010-12-9  10:53:33
** Test recorde:            
**--------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Test recorde: 
*********************************************************************************************************************/
INT32S uart_send(const UART_INFO *This, char *pBuffer, int Size);

/*********************************************************************************************************************
** Function name:           uart_print
** Descriptions:
** Input parameters:
** Output parameters:
** Returned value:          ==OS_OK : 操作成功
**                          !=OS_OK : 操作失败(包含出错信息)
**--------------------------------------------------------------------------------------------------------------------
** Created by:              Fengliang
** Created Date:            2010-9-25  13:49:48
** Test recorde:
**--------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Test recorde:
*********************************************************************************************************************/
extern int uart_prints(const char *pString);


#ifdef __cplusplus
}
#endif                                                                      /* __cplusplus                          */

#endif                                                                      /* end of __UART_H_                     */
/*********************************************************************************************************************
                                                    END OF FILE
*********************************************************************************************************************/

