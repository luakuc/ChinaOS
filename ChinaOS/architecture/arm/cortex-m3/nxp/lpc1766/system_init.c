/******************************************************Copyright (c)**************************************************
**                                              ��������ֹһ�п��ܵĸ���Ե��
**
**                                             E-Mail: ChinaFengliang@163.com
**
**---------File Information-------------------------------------------------------------------------------------------
** File name:            init.c
** Last version:         V1.00
** Descriptions:         ϵͳ��ʼ���ļ�.
** Hardware platform:    lpc17xx
** SoftWare platform:   
**
**--------------------------------------------------------------------------------------------------------------------
** Created by:           Fengliang
** Created date:         2010��9��3��  14:45:10
** Version:              V1.00
** Descriptions:         ARM7TDMI-S���������������Ƶ��Ϊ72MHz
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
#include    <string.h>
#include    <include/macro.h>
#include    <library/ioport.h>
#include    "../lpc17xx.h"

/*********************************************************************************************************************
                                                    �궨����
*********************************************************************************************************************/
/* ʱ��Դ ----------------------------------------------------------------------------------------------------------*/
#define Fosc                12000000                                        /* ϵͳ������Ƶ��: 12MHz              */
#define Firc                 4000000                                        /* �ڲ�RC����Ƶ��: 4MHz               */
#define Frtc                       0                                        /* ʵʱ������Ƶ��: 0MHz               */
/* ģ��Ƶ�� --------------------------------------------------------------------------------------------------------*/
#define Fcpu               100000000                                        /* CPU����Ƶ��: 100MHz                  */
#define Fusb                48000000                                        /* USB����Ƶ��: 48MHz                   */
/* ��ƵƵ�� --------------------------------------------------------------------------------------------------------*/
#define Fcco               300000000                                        /* PLL��Ƶ�����Ƶ��: 300MHz (ԽСԽ��) */
/* ���ò��� --------------------------------------------------------------------------------------------------------*/
#define M                         25                                        /* ��Ƶ��(PLL)����M(ԽСԽ��)           */
#define N                          2                                        /* ��Ƶ��(PLL)����N(ԽСԽ��)           */

/* ��ʾ��Ϣ --------------------------------------------------------------------------------------------------------*/
#if (100000000 < Fcpu)
#error "Fcpu must less than 72000000!"
#endif

#if (48000000 != Fusb)
#error "Fusb must be 48000000!"
#endif

#if (Fcco < 275000000)
#error "Fcco must be [275000000, 550000000]!"
#endif

#if (550000000 < Fcco)
#error "Fcco must be [275000000, 550000000]!"
#endif



/*********************************************************************************************************************
                                                    ���Ͷ�����
*********************************************************************************************************************/
/* �������� --------------------------------------------------------------------------------------------------------*/



/*********************************************************************************************************************
                                                  ȫ�ֱ���������
*********************************************************************************************************************/



/*********************************************************************************************************************
** Function name:           system_clock_init
** Descriptions:            ϵͳʱ���źų�ʼ��
** Input parameters:        
** Output parameters:       
** Returned value:          
**--------------------------------------------------------------------------------------------------------------------
** Created by:              
** Created Date:            2011-8-24  10:30:15
** Test recorde:            
**--------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Test recorde: 
*********************************************************************************************************************/
void system_clock_init(void)
{
    /* 1.1) ȷ��ϵͳ������ 
     * ��ȡ������״̬,ȷ�������������ȶ�����״̬��
     */
    dword_modify(SCS, (1ul<<4),                                             /* ѡ��������Ƶ�ʷ�Χ: 1MHz~20MHz     */
                      (1ul<<5));                                            /* ʹ��������                         */
    while (0 == ((1ul<<6) & read_dword(SCS)));                              /* �ȴ��������ź��ȶ�                 */

    /* 
     * 1.2) ����PLL��Ƶ������
     */
    /* 1.2.1) �Ͽ�PLL��Ƶ�� */     
    write_dword(PLL0CON, (0ul<<1) |                                         /* ��·PLL��Ƶ��                        */
                         (0ul<<0));                                         /* ����PLL��Ƶ��                        */
    write_dword(PLL0FEED, 0xAA);                                            /* ִ����֤����A                        */
    write_dword(PLL0FEED, 0x55);                                            /* ִ����֤����B                        */

    /* 1.2.2) ѡ��PLLʱ��Դ */ 
    write_dword(CLKSRCSEL, 0x01);                                           /* ѡ����������ΪPLL����ʱ��Դ        */
    
    /* 1.2.3) ���ñ�Ƶ���� */
    write_dword(PLL0CFG, ((N-1) << 16)|                                     /* ����PLL��Ƶ����                      */
                         ((M-1) << 0));
    write_dword(PLL0FEED, 0xAA);                                            /* ִ����֤����A                        */
    write_dword(PLL0FEED, 0x55);                                            /* ִ����֤����B                        */
        
    /* 1.2.4 ���Ƶ��Ƶ��������Ϊ */
    dword_set_bits(PLL0CON, 1ul<<0);
    write_dword(PLL0FEED, 0xAA);                                            /* ִ����֤����A                        */
    write_dword(PLL0FEED, 0x55);                                            /* ִ����֤����B                        */

    /* 1.2.5) ����CPUʱ��Ƶ�� */
    write_dword(CCLKCFG, Fcco/Fcpu - 1);                                    /* ����CPUʱ�ӷ�Ƶϵ��                  */    
    
    /* 1.2.6) �л�����Ƶ�ź� */
    while (0 == ((1ul<<26) & read_dword(PLL0STAT)));                        /* �ȴ�PLL��Ƶ������Ŀ���ź�Ƶ��        */
    dword_set_bits(PLL0CON, 1ul<<1);                                       /* ����PLL��Ƶ��                        */
    write_dword(PLL0FEED, 0xAA);                                            /* ִ����֤����A                        */
    write_dword(PLL0FEED, 0x55);                                            /* ִ����֤����B                        */

    /*
     * 3) ��������ʱ��Ԥ��Ƶϵ��
     *    00 : PCLK_peripheral = Fcpu/4;
     *    01 : PCLK_peripheral = Fcpu;
     *    10 : PCLK_peripheral = Fcpu/2;
     *    11 : PCLK_peripheral = Fcpu/8,
     *    except for CAN1, CAN2, and CAN filtering when ��11�� selects = Fcpu/6
     */
    write_dword(PCLKSEL0, (0ul << 0)  |                                     /* WDT                                  */
                          (3ul << 2)  |                                     /* TIMER0                               */
                          (3ul << 4)  |                                     /* TIMER1                               */
                          (3ul << 6)  |                                     /* UART0                                */
                          (0ul << 8)  |                                     /* UART1                                */
                          (0ul << 10) |                                     /* (����)                               */
                          (0ul << 12) |                                     /* PWM1                                 */
                          (0ul << 14) |                                     /* I2C0                                 */
                          (0ul << 16) |                                     /* SPI                                  */
                          (0ul << 18) |                                     /* (����)                               */
                          (0ul << 20) |                                     /* SSP1                                 */
                          (0ul << 22) |                                     /* DAC                                  */
                          (0ul << 24) |                                     /* ADC                                  */
                          (0ul << 26) |                                     /* CAN1                                 */
                          (0ul << 28) |                                     /* CAN2                                 */
                          (0ul << 30));                                     /* ACF                                  */
    write_dword(PCLKSEL1, (0ul << 0)  |                                     /* Quadrature Encoder Interface         */   
                          (0ul << 2)  |                                     /* GPIO interrupts                      */
                          (0ul << 4)  |                                     /* Pin Connect block.                   */
                          (0ul << 6)  |                                     /* I2C1                                 */
                          (0ul << 8)  |                                     /* (����)                               */
                          (0ul << 10) |                                     /* SSP0                                 */  
                          (0ul << 12) |                                     /* TIMER2                               */
                          (0ul << 14) |                                     /* TIMER3                               */
                          (0ul << 16) |                                     /* UART2                                */
                          (0ul << 18) |                                     /* UART3                                */
                          (0ul << 20) |                                     /* I2C2                                 */
                          (0ul << 22) |                                     /* I2S                                  */
                          (0ul << 24) |                                     /* (����)                               */
                          (0ul << 26) |                                     /* Repetitive Interrupt Timer           */
                          (0ul << 28) |                                     /* System Control block                 */
                          (0ul << 30));                                     /* Motor Control PWM                    */
    write_dword(USBCLKCFG, Fcco/Fusb - 1);                                  /* ����USBʱ�ӷ�Ƶϵ��                  */

	//write_dword(PCONP, 0xFFFFFFFF);                                         /* ʹ���������蹩��                     */
}

/*********************************************************************************************************************
                                                    END OF FILE
*********************************************************************************************************************/
