/******************************************************Copyright (c)**************************************************
**                                              胆怯是阻止一切可能的根本缘由
**
**                                             E-Mail: ChinaFengliang@163.com
**
**---------File Infomation--------------------------------------------------------------------------------------------
** File name:            OS_kernel.h
** Last version:         V1.00
** Descriptions:         系统之内核管理头文件.
** Hardware platform:    ARM7系列、ARM9系列
** SoftWare platform:
**
**--------------------------------------------------------------------------------------------------------------------
** Created by:           Fengliang
** Created date:         2010年9月2日  15:2:53
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
#ifndef __OS_KERNEL_H_
#define __OS_KERNEL_H_

#ifdef __cplusplus
extern "C" {
#endif                                                                      /* __cplusplus                          */

/*********************************************************************************************************************
                                                    头文件区
*********************************************************************************************************************/
#include    <include/macro.h>
#include    <include/types.h>
#include    <ticker/ticker.h>
#include    <library/link/list.h>

/*********************************************************************************************************************
                                                    宏定义区
*********************************************************************************************************************/
/* 宏段名 ----------------------------------------------------------------------------------------------------------*/


/*********************************************************************************************************************
                                                    类型定义区
*********************************************************************************************************************/
/* 线程控制表 ------------------------------------------------------------------------------------------------------*/
struct __thread_t
{
    REGISTER           *pStackTop;                                          /* 线程栈顶指针(要求: 结构体第一元素)   */
    REGISTER           *pStackBottom;                                       /* 线程栈底指针                         */
    INT32U              Priority;                                           /* 线程优先权                           */
    const char         *pName;                                              /* 线程名称                             */
    struct __thread_t  *pLive;                                              /* 激活线程链表                         */
    
    TIMER               Timer;                                              /* 线程定时器                           */
    struct list_head    Node;

    void               *pAttachment;                                        /* 额外数据挂载点                       */
    void               (*pExit)(INT32S);                                    /* 线程退出回调函数                     */
    void               (*pKill)(void);                                      /* 线程杀死回调函数                     */
};
typedef struct __thread_t               THREAD;                             /* 线程控制表类型                       */

/*********************************************************************************************************************
                                                  全局变量定义区
*********************************************************************************************************************/
extern THREAD              *OS_LiveList;                                    /* 激活线程链表                         */
extern INT32U               OS_ActivePrio;                                  /* 激活的优先级标志                     */
extern struct list_head     OS_ActiveProc[33];                              /* 激活的线程队列                       */
extern THREAD              *OS_This;                                        /* 当前线程                             */

/*********************************************************************************************************************
** Function name:           labour
** Descriptions:            派生线程
** Input parameters:        pName       : 线程名称
**                          pProcess    : 线程函数名
**                          pOption     : 参数
**                          StackDepth  : 栈深度
**                          Priority    : 优先权[0, 31]
** Output parameters:
** Returned value:          !=NULL      : 线程ID
**                          ==NULL      : 操作失败(包含出错信息)
**--------------------------------------------------------------------------------------------------------------------
** Created by:              Fengliang
** Created Date:            2010-8-26  8:50:3
** Test recorde:
**--------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Test recorde:
*********************************************************************************************************************/
INT32S labour(const char   *pName,
              int         (*pProcess)(void *),
              void         *pOption,
              INT32U        StackDepth,
              INT32U        Priority);


/*********************************************************************************************************************
** Function name:           kill
** Descriptions:            杀死指定线程
** Input parameters:        Id : 线程ID号
** Output parameters:       None
** Returned value:          None
**--------------------------------------------------------------------------------------------------------------------
** Created by:              Fengliang
** Created Date:            2010-8-27  11:42:14
** Test recorde:
**--------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Test recorde:
*********************************************************************************************************************/
STATUS kill(INT32S Id);

/*********************************************************************************************************************
** Function name:           signal
** Descriptions:            注册信号事件
** Input parameters:        SigNum     : 事件信号
**                          pFunction  : 处理函数
** Output parameters:       None
** Returned value:          ==OS_OK : 操作成功
**                          !=OS_OK : 操作失败(包含出错信息)
**--------------------------------------------------------------------------------------------------------------------
** Created by:              Fengliang
** Created Date:            2010-8-25  16:20:32
** Test recorde:
**--------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Test recorde:
*********************************************************************************************************************/
INT32S signal(INT32S SigNum, void *pFunction);

/*********************************************************************************************************************
** Function name:           getid
** Descriptions:            获得当前线程ID
** Input parameters:
** Output parameters:
** Returned value:          ==OS_OK : 操作成功
**                          !=OS_OK : 操作失败(包含出错信息)
**--------------------------------------------------------------------------------------------------------------------
** Created by:              Fengliang
** Created Date:            2010-8-30  9:23:9
** Test recorde:
**--------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Test recorde:
*********************************************************************************************************************/
INT32S getid(void);

/*********************************************************************************************************************
** Function name:           scheduler
** Descriptions:            调度算法
** Input parameters:        
** Output parameters:       
** Returned value:          
**--------------------------------------------------------------------------------------------------------------------
** Created by:              Fengliang
** Created Date:            2011-3-4  18:22:40
** Test recorde:            
**--------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Test recorde: 
*********************************************************************************************************************/
void scheduler(void);

/*********************************************************************************************************************
** Function name:           change_priority
** Descriptions:            id       : 线程ID
**                          Priority : 优先级
** Input parameters:
** Output parameters:
** Returned value:          ==OS_OK : 操作成功
**                          !=OS_OK : 操作失败(包含出错信息)
**--------------------------------------------------------------------------------------------------------------------
** Created by:              Fengliang
** Created Date:            2010-8-30  14:14:18
** Test recorde:
**--------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Test recorde:
*********************************************************************************************************************/
INT32S change_priority(INT32U id, INT32U Priority);

/*********************************************************************************************************************
** Function name:           sleep
** Descriptions:            睡眠
** input parameters:        Time: 延时时间(单位: 毫秒)
** output parameters:       
** Returned value:          == OS_OK: 正常唤醒
**                          != OS_OK: 异常唤醒
**--------------------------------------------------------------------------------------------------------------------
** Created by:              Fengliang
** Created Date:            2010-01-06
**--------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Test record:
**--------------------------------------------------------------------------------------------------------------------
*********************************************************************************************************************/
INT32S sleep(INT32U Time);

#ifdef __cplusplus
}
#endif                                                                      /* __cplusplus                          */

#endif                                                                      /* end of __OS_KERNEL_H_                */
/*********************************************************************************************************************
                                                    END OF FILE
*********************************************************************************************************************/

