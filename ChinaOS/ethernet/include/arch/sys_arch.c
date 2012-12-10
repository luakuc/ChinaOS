/******************************************************Copyright (c)**************************************************
**                                              ��������ֹһ�п��ܵĸ���Ե��
**
**                                             E-Mail: ChinaFengliang@163.com
**
**---------File Information-------------------------------------------------------------------------------------------
** File name:            sys_arch.c
** Last version:         V1.00
** Descriptions:         lwipϵͳ�ӿڲ��ļ�.
** Hardware platform:    
** SoftWare platform:    ChinaOS & lwip
**
**--------------------------------------------------------------------------------------------------------------------
** Created by:           Feng Liang
** Created date:         2012��2��8��  14:55:13
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
                                                    ͷ�ļ���
*********************************************************************************************************************/
#include <lwip/debug.h>
#include "lwip/sys.h"
#include "lwip/opt.h"
#include "lwip/stats.h"
#include "arch/sys_arch.h"

/*********************************************************************************************************************
                                                    �궨����
*********************************************************************************************************************/
/* ����� ----------------------------------------------------------------------------------------------------------*/


/*********************************************************************************************************************
                                                    ���Ͷ�����
*********************************************************************************************************************/
/* �������� --------------------------------------------------------------------------------------------------------*/


/*********************************************************************************************************************
                                                  ȫ�ֱ���������
*********************************************************************************************************************/



/*********************************************************************************************************************
** Function name:           sys_init
** Descriptions:            must be called before anthing else.
** Input parameters:        
** Output parameters:       
** Returned value:          
**--------------------------------------------------------------------------------------------------------------------
** Created by:              Feng Liang
** Created Date:            2012-2-8  16:18:51
** Test recorde:            
**--------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Test recorde: 
*********************************************************************************************************************/
void sys_init(void)
{

}


/*********************************************************************************************************************
** Function name:           sys_sem_new
** Descriptions:            Creates and returns a new semaphore. The "count" argument specifies  the initial state
**                          of the semaphore.
** Input parameters:        count
** Output parameters:       
** Returned value:          ==NULL : ����ʧ��
**                          !=NULL : �����ɹ�(������Ϣ����)
**--------------------------------------------------------------------------------------------------------------------
** Created by:              Feng Liang
** Created Date:            2012-2-8  14:58:7
** Test recorde:            
**--------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Test recorde: 
*********************************************************************************************************************/
sys_sem_t sys_sem_new(u8_t count)
{
    return semaphore_new(count);
}

/*********************************************************************************************************************
** Function name:           sys_sem_free
** Descriptions:            Deallocates a semaphore.
** Input parameters:        Semaphore : �ź���
** Output parameters:       
** Returned value:          
**--------------------------------------------------------------------------------------------------------------------
** Created by:              Feng Liang
** Created Date:            2012-2-8  14:59:7
** Test recorde:            
**--------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Test recorde: 
*********************************************************************************************************************/
void sys_sem_free(sys_sem_t Semaphore)
{
    semaphore_free(Semaphore);
}

/*********************************************************************************************************************
** Function name:           sys_sem_signal
** Descriptions:            Signals a semaphore.
** Input parameters:        Semaphore : �ź���
** Output parameters:       
** Returned value:          
**--------------------------------------------------------------------------------------------------------------------
** Created by:              Feng Liang
** Created Date:            2012-2-8  14:59:31
** Test recorde:            
**--------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Test recorde: 
*********************************************************************************************************************/
void sys_sem_signal(sys_sem_t Semaphore)
{
    semaphore_post(Semaphore);
}

/*********************************************************************************************************************
** Function name:           sys_arch_sem_wait
** Descriptions:            Blocks the thread while waiting for the semaphore to be  signaled. If the "timeout" 
**                          argument is non-zero, the thread should  only be blocked for the specified time (measured
**                          in  milliseconds). If the "timeout" argument is zero, the thread should be  blocked until
**                          the semaphore is signalled.
** Input parameters:        Semaphore : �ź���
**                          Timeout   : �ȴ�ʱ��(��λ: ����)
**                                      == 0: �����ڵȴ�
**                                      != 0: �ȴ�ʱ��
** Output parameters:       
** Returned value:          If the timeout argument is non-zero, the return value is the number of  milliseconds spent
**                          waiting for the semaphore to be signaled. If the  semaphore wasn't signaled within the
**                          specified time, the return value is  SYS_ARCH_TIMEOUT. If the thread didn't have to wait
**                          for the semaphore  (i.e., it was already signaled), the function may return zero.
**--------------------------------------------------------------------------------------------------------------------
** Created by:              Feng Liang
** Created Date:            2012-2-8  15:0:6
** Test recorde:            
**--------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Test recorde: 
*********************************************************************************************************************/
u32_t sys_arch_sem_wait(sys_sem_t Semaphore, u32_t Timeout)
{
    INT32U       TimeStart, TimeEnd;

    
    TimeStart = mtimer.gettick();
    if (OS_ERR_TIMEOUT == semaphore_wait(Semaphore, Timeout))
    {
        return SYS_ARCH_TIMEOUT;
    }
    TimeEnd= mtimer.gettick();
    
    return TimeEnd - TimeStart;
}

/*********************************************************************************************************************
** Function name:           sys_mbox_new
** Descriptions:            
** Input parameters:        
** Output parameters:       
** Returned value:          
**--------------------------------------------------------------------------------------------------------------------
** Created by:              Feng Liang
** Created Date:            2012-2-8  15:3:12
** Test recorde:            
**--------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Test recorde: 
*********************************************************************************************************************/
sys_mbox_t sys_mbox_new(int size)
{
    return mailbox_new(size);
}

/*********************************************************************************************************************
** Function name:           sys_mbox_free
** Descriptions:            
** Input parameters:        
** Output parameters:       
** Returned value:          
**--------------------------------------------------------------------------------------------------------------------
** Created by:              Feng Liang
** Created Date:            2012-2-8  15:4:31
** Test recorde:            
**--------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Test recorde: 
*********************************************************************************************************************/
void sys_mbox_free(sys_mbox_t mbox)
{
    mailbox_free(mbox);
}

/*********************************************************************************************************************
** Function name:           sys_mbox_post
** Descriptions:            Posts the "msg" to the mailbox. This function have to block until  the "msg" is really
**                          posted.
** Input parameters:        
** Output parameters:       
** Returned value:          
**--------------------------------------------------------------------------------------------------------------------
** Created by:              Feng Liang
** Created Date:            2012-2-8  15:4:45
** Test recorde:            
**--------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Test recorde: 
*********************************************************************************************************************/
void sys_mbox_post(sys_mbox_t mbox, void *msg)
{
    int             Status;

    
    do
    {
        Status = mail_post(mbox, msg);
    } while (OS_OK != Status);
}

/*********************************************************************************************************************
** Function name:           sys_mbox_trypost
** Descriptions:            Try to post the "msg" to the mailbox. Returns ERR_MEM if this one  is full, else, ERR_OK if the "msg" is posted.
** Input parameters:        
** Output parameters:       
** Returned value:          ==OS_OK : �����ɹ�
**                          !=OS_OK : ����ʧ��(����������Ϣ)
**--------------------------------------------------------------------------------------------------------------------
** Created by:              Feng Liang
** Created Date:            2012-2-8  15:4:56
** Test recorde:            
**--------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Test recorde: 
*********************************************************************************************************************/
err_t sys_mbox_trypost(sys_mbox_t mbox, void *msg)    
{
    if (OS_OK == mail_post(mbox, msg))
    {
        return ERR_OK;
    }
    else
    {
        return ERR_MEM;
    }
}

/*********************************************************************************************************************
** Function name:           sys_arch_mbox_fetch
** Descriptions:            
** Input parameters:        
** Output parameters:       
** Returned value:          Number of milliseconds spent waiting or SYS_ARCH_TIMEOUT if there was a  timeout.
**--------------------------------------------------------------------------------------------------------------------
** Created by:              Feng Liang
** Created Date:            2012-2-8  15:5:0
** Test recorde:            
**--------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Test recorde: 
*********************************************************************************************************************/
u32_t sys_arch_mbox_fetch(sys_mbox_t mbox, void **msg, u32_t timeout)
{
    MAIL            Mail;
    INT32U          TimeStart, TimeEnd;


    if (NULL == msg)
    {
        msg = &Mail;
    }
    
    TimeStart = mtimer.gettick();
    if (OS_ERR_TIMEOUT == mail_wait(mbox, msg, timeout))
    {
        return SYS_ARCH_TIMEOUT;
    }
    TimeEnd= mtimer.gettick();

    return TimeEnd - TimeStart;
}

/*********************************************************************************************************************
** Function name:           sys_arch_mbox_tryfetch
** Descriptions:            
** Input parameters:        
** Output parameters:       
** Returned value:          ==OS_OK : �����ɹ�
**                          !=OS_OK : ����ʧ��(����������Ϣ)
**--------------------------------------------------------------------------------------------------------------------
** Created by:              Feng Liang
** Created Date:            2012-2-8  15:5:5
** Test recorde:            
**--------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Test recorde: 
*********************************************************************************************************************/
u32_t sys_arch_mbox_tryfetch(sys_mbox_t mbox, void **msg)    
{
    if (OS_OK == mail_fetch(mbox, msg))
    {
        return 0;
    }
    else
    {
        return SYS_MBOX_EMPTY;
    }
}

/*********************************************************************************************************************
** Function name:           sys_arch_timeouts
** Descriptions:            
** Input parameters:        
** Output parameters:       
** Returned value:          
**--------------------------------------------------------------------------------------------------------------------
** Created by:              Feng Liang
** Created Date:            2012-2-9  0:41:56
** Test recorde:            
**--------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Test recorde: 
*********************************************************************************************************************/
struct sys_timeouts *sys_arch_timeouts(void)
{
    THREAD              *pThread;

    pThread = (THREAD *)getid();
    
    return (struct sys_timeouts *)&(pThread->pTimeout);
}

/*********************************************************************************************************************
** Function name:           sys_thread_new
** Descriptions:            
** Input parameters:        
** Output parameters:       
** Returned value:          ==OS_OK : �����ɹ�
**                          !=OS_OK : ����ʧ��(����������Ϣ)
**--------------------------------------------------------------------------------------------------------------------
** Created by:              Feng Liang
** Created Date:            2012-2-8  15:5:10
** Test recorde:            
**--------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Test recorde: 
*********************************************************************************************************************/
sys_thread_t sys_thread_new(char *name, void (* thread)(void *arg), void *arg, int stacksize, int prio)
{
    return labour(name, thread, arg, stacksize, prio);
}

/*********************************************************************************************************************
** Function name:           sys_arch_protect
** Descriptions:            
** Input parameters:        
** Output parameters:       
** Returned value:          ==OS_OK : �����ɹ�
**                          !=OS_OK : ����ʧ��(����������Ϣ)
**--------------------------------------------------------------------------------------------------------------------
** Created by:              Feng Liang
** Created Date:            2012-2-8  15:5:19
** Test recorde:            
**--------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Test recorde: 
*********************************************************************************************************************/
sys_prot_t sys_arch_protect(void)
{
    return atom_operate_lock();
}

/*********************************************************************************************************************
** Function name:           sys_arch_unprotect
** Descriptions:            
** Input parameters:        
** Output parameters:       
** Returned value:          ==OS_OK : �����ɹ�
**                          !=OS_OK : ����ʧ��(����������Ϣ)
**--------------------------------------------------------------------------------------------------------------------
** Created by:              Feng Liang
** Created Date:            2012-2-8  15:5:25
** Test recorde:            
**--------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Test recorde: 
*********************************************************************************************************************/
void sys_arch_unprotect(sys_prot_t pval)
{
    atom_operate_unlock(pval);
}

/*********************************************************************************************************************
                                                    END OF FILE
*********************************************************************************************************************/
