/******************************************************Copyright (c)**************************************************
**                                              ��������ֹһ�п��ܵĸ���Ե��
**
**                                             E-Mail: ChinaFengliang@163.com
**
**---------File Information-------------------------------------------------------------------------------------------
** File name:            ethernet.h
** Last version:         V1.00
** Descriptions:         ��̫�����������ļ�.
** Hardware platform:    
** SoftWare platform:    ChinaOS
**
**--------------------------------------------------------------------------------------------------------------------
** Created by:           Feng Liang
** Created date:         2012��3��6��  15:17:8
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
#ifndef __ETHERNET_H_
#define __ETHERNET_H_

#ifdef __cplusplus
extern "C" {
#endif                                                                      /* __cplusplus                          */

/*********************************************************************************************************************
                                                    ͷ�ļ���
*********************************************************************************************************************/
#include    "lwip/err.h"
#include    "lwip/netif.h"

/*********************************************************************************************************************
                                                    �궨����
*********************************************************************************************************************/
/* ����� ----------------------------------------------------------------------------------------------------------*/


/*********************************************************************************************************************
                                                    ���Ͷ�����
*********************************************************************************************************************/
/* �������� --------------------------------------------------------------------------------------------------------*/


/*********************************************************************************************************************
** Function name:           ethernet_setup
** Descriptions:            ��װ��̫���ӿ�
** Input parameters:        pEthernet : �ӿڶ���ָ��
** Output parameters:       
** Returned value:          ==ERR_OK : �����ɹ�
**                          !=ERR_OK : ����ʧ��(����������Ϣ)
**--------------------------------------------------------------------------------------------------------------------
** Created by:              Feng Liang
** Created Date:            2012-3-2  14:19:33
** Test recorde:            
**--------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Test recorde: 
*********************************************************************************************************************/
err_t ethernet_setup(struct netif *pEthernet);

/*********************************************************************************************************************
** Function name:           ethernet_scan
** Descriptions:            ɨ����̫���ӿ�,������������֡
** Input parameters:        pEthernet : �ӿڶ���ָ��
** Output parameters:       
** Returned value:          
**--------------------------------------------------------------------------------------------------------------------
** Created by:              Feng Liang
** Created Date:            2012-3-6  15:20:13
** Test recorde:            
**--------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Test recorde: 
*********************************************************************************************************************/
void ethernet_scan(struct netif *pEthernet);


#ifdef __cplusplus
}
#endif                                                                      /* __cplusplus                          */

#endif                                                                      /* end of __ETHERNET_H_                 */
/*********************************************************************************************************************
                                                    END OF FILE
*********************************************************************************************************************/
