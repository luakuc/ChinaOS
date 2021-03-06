/******************************************************Copyright (c)**************************************************
**
**                              Copyright (c) 2009,2011 Fengliang And His Friends Corporation.
**
**                                             E-Mail: ChinaFengliang@163.com
**
**
**---------File Information-------------------------------------------------------------------------------------------
** File name:            semaphore.c
** Last version:         V1.00
** Descriptions:         信息量同步机制文件.
** Hardware platform:    
** SoftWare platform:
**
**--------------------------------------------------------------------------------------------------------------------
** Created by:           FengLiang
** Created date:         2011年2月25日  14:6:28
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

/*********************************************************************************************************************
                                                    头文件区
*********************************************************************************************************************/
#include    <syscall.h>
#include    <include/macro.h>
#include    <include/types.h>
#include    <kernel/kernel.h>
#include    <kernel/semaphore/semaphore.h>
#include    <library/malloc/malloc.h>

/*********************************************************************************************************************
                                                    宏定义区
*********************************************************************************************************************/
/* 宏段名 ----------------------------------------------------------------------------------------------------------*/


/*********************************************************************************************************************
                                                    类型定义区
*********************************************************************************************************************/
/* 基本类型 --------------------------------------------------------------------------------------------------------*/


/*********************************************************************************************************************
                                                  全局变量定义区
*********************************************************************************************************************/


/*********************************************************************************************************************
** Function name:           semaphore_new
** Descriptions:            新建一个动态的计数信号量
** Input parameters:        Amount : 计数信号量初始值
** Output parameters:       
** Returned value:          ==NULL : 操作失败
**                          !=NULL : 操作成功(包含消息邮箱)
**--------------------------------------------------------------------------------------------------------------------
** Created by:              Fengliang
** Created Date:            2011-2-25  14:9:48
** Test recorde:            
**--------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Test recorde: 
*********************************************************************************************************************/
SEMAPHORE semaphore_new(INT32U Amount)
{
    SEMAPHORE   Semaphore = NULL;

    
    if (NULL != (Semaphore = (SEMAPHORE)malloc(sizeof(struct semaphore))))
    {
        Semaphore->Counter = Amount;
        INIT_LIST_HEAD(&Semaphore->WaitHead);
    }
    
    return Semaphore;
}

/*********************************************************************************************************************
** Function name:           semaphore_free
** Descriptions:            释放一个动态信号量
** Input parameters:        Semaphore : 信号量
** Output parameters:       
** Returned value:          ==OK : 操作成功
**                          !=OK : 操作失败(包含出错信息)
**--------------------------------------------------------------------------------------------------------------------
** Created by:              Fengliang
** Created Date:            2011-4-13  2:33:9
** Test recorde:            
**--------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Test recorde: 
*********************************************************************************************************************/
int semaphore_free(SEMAPHORE Semaphore)
{
    free(Semaphore);
    return OK;
}

/*********************************************************************************************************************
** Function name:           semaphore_setup
** Descriptions:            创建静态信号量
** Input parameters:        Semaphore : 信号量地址
**                          Amount    : 初始数量
** Output parameters:       
** Returned value:          ==OK : 操作成功
**                          !=OK : 操作失败(包含出错信息)
**--------------------------------------------------------------------------------------------------------------------
** Created by:              Fengliang
** Created Date:            2011-2-25  14:9:48
** Test recorde:            
**--------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Test recorde: 
*********************************************************************************************************************/
int semaphore_create(SEMAPHORE Semaphore, INT32U Amount)
{
    if (NULL == Semaphore)
    {
        return ERR_BAD_PARAM;
    }

    Semaphore->Counter = Amount;
    INIT_LIST_HEAD(&Semaphore->WaitHead);
    
    return OK;
}

/*********************************************************************************************************************
** Function name:           mail_fetch
** Descriptions:            获取信号量(非阻塞方式). 
** Input parameters:        Semaphore : 信号量地址
** Output parameters:       
** Returned value:          ==OK : 操作成功。信号量非零,获取信号量成功.
**                          !=OK : 操作失败. 信号量为零,获取信号量失败.
**--------------------------------------------------------------------------------------------------------------------
** Created by:              Fengliang
** Created Date:            2011-5-10  18:20:52
** Test recorde:            
**--------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Test recorde: 
*********************************************************************************************************************/
int semaphore_fetch(SEMAPHORE Semaphore)
{
    int              Key;

    
    if (NULL == Semaphore)
    {
        return ERR_BAD_PARAM;
    }

    Key = atom_operate_lock();
    if (Semaphore->Counter)
    {
        Semaphore->Counter--;
        atom_operate_unlock(Key);
        return OK;
    }
    atom_operate_unlock(Key);
    
    return ERR;
}

/*********************************************************************************************************************
** Function name:           semaphore_wait
** Descriptions:            等待信号量(阻塞方式)
** Input parameters:        Semaphore : 信号量
**                          Timeout   : 超时时间(单位: 毫秒)
**                                       ==0: 永久等待.
**                                       !=0: 等待时间.
** Output parameters:       
** Returned value:          ==OK : 操作成功
**                          !=OK : 操作失败(包含出错信息)
**--------------------------------------------------------------------------------------------------------------------
** Created by:              Fengliang
** Created Date:            2011-2-25  14:20:38
** Test recorde:            
**--------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Test recorde:            
*********************************************************************************************************************/
int semaphore_wait(SEMAPHORE Semaphore, INT32U Timeout)
{
    /*
     * 问: 如何解决多个线程等待一个信号量?
     * 解: 采用线程控制块中双链表结构将所有等待线程链接起来.
     */
    THREAD          *pThread;
    INT32U           Priority;                                              /* 优先级                               */
    int              Key;
    
    
    /* 0)
     * 参数过滤
     */
    if (NULL == Semaphore)
    {
        return ERR_BAD_PARAM;
    }

    Key = atom_operate_lock();
    if (Semaphore->Counter)
    {
        Semaphore->Counter--;
        atom_operate_unlock(Key);
        return OK;
    }

    /*  
     * 1) 将当前线程挂起
     */
    pThread = OS_This;
    Priority = pThread->Priority;
    list_del(&pThread->Node);
    if (list_empty(&OS_ActiveProc[Priority]))
    {   
        OS_ActivePrio &= ~(1ul << Priority);
    }

    /* 2)
     * 添加唤醒条件.
     * 2.1) 信号量触发事件;
     * 2.2) 等待超时事件.
     */
     
    /* 2.1)
     * 加入信号量等待队列
     */
    list_add(&pThread->Node, &Semaphore->WaitHead);

    /* 2.2) 
     * 添加唤醒定时器.
     */
    if (Timeout)
    {
        OS_timer_add(&pThread->Timer, Timeout);                             /* 添加唤醒定时器                       */
    }
    atom_operate_unlock(Key);


    /* 3)
     * 切换线程.
     */
    OS_thread_switch();


    /* 
     * 4) 删除唤醒条件
     */
     
    /*
     * 4.1) 删除超时唤醒条件
     */    
    Key = atom_operate_lock(); 
    if (Timeout)
    {
        OS_timer_del(&pThread->Timer);                                      /* 删除唤醒定时器                       */           
    }
    /*
     * 4.2) 退出信号量等待队列.
     */    
    list_del(&pThread->Node);
    
    /*
     * 5) 收取信号量
     */   
    if (0 == Semaphore->Counter)
    {
        atom_operate_unlock(Key);
        return ERR_TIMEOUT; 
    }
    Semaphore->Counter--;    
    atom_operate_unlock(Key);

    return OK;    
}

/*********************************************************************************************************************
** Function name:           semaphore_post
** Descriptions:            投递信号量
** Input parameters:        Semaphore : 信号量地址
** Output parameters:       
** Returned value:          ==OK : 操作成功
**                          !=OK : 操作失败(包含出错信息)
**--------------------------------------------------------------------------------------------------------------------
** Created by:              Fengliang
** Created Date:            2011-2-25  14:22:16
** Test recorde:            
**--------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Test recorde: 
*********************************************************************************************************************/
int semaphore_post(SEMAPHORE Semaphore)
{
    THREAD          *pThread;
    INT32S           Priority;
    int              Key;
    
    
    /* 0)
     * 参数过滤
     */
    if (NULL == Semaphore)
    {
        return ERR_BAD_PARAM;
    }

    /*
     * 1) 增加信号量
     */
    Key = atom_operate_lock();
    Semaphore->Counter++;
    if (list_empty(&Semaphore->WaitHead))
    {
        atom_operate_unlock(Key);
        return OK;
    }

    /* 
     * 2) 线程就绪
     *    将线程控制表插入到指定线程队列
     */
    pThread = container_of(&Semaphore->WaitHead.next->next, THREAD, Node);
    Priority = pThread->Priority;
    list_add(&pThread->Node, &OS_ActiveProc[Priority]);
    OS_ActivePrio |= 1ul << Priority;
    atom_operate_unlock(Key);

    /* 
     * 3) 切换线程
     */
    scheduler();                                                            /* 线程调度决策                         */    
    
    
    return OK;
}

/*********************************************************************************************************************
                                                    END OF FILE
*********************************************************************************************************************/

