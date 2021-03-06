/******************************************************Copyright (c)**************************************************
**                                              胆怯是阻止一切可能的根本缘由
**
**                                             E-Mail: ChinaFengliang@163.com
**
**---------File Information-------------------------------------------------------------------------------------------
** File name:            common.h
** Last version:         V1.00
** Descriptions:         系统之数据类型头文件.
** Hardware platform:
** SoftWare platform:
**
**--------------------------------------------------------------------------------------------------------------------
** Created by:           Fengliang
** Created date:         2010年11月16日  11:21:28
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
#ifndef __COMMON_H_
#define __COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif                                                                      /* __cplusplus                          */

/*********************************************************************************************************************
                                                    头文件区
*********************************************************************************************************************/
#include    <include/macro.h>
#include    <include/types.h>

/*********************************************************************************************************************
                                                    宏定义区
*********************************************************************************************************************/
/* 宏段名 ----------------------------------------------------------------------------------------------------------*/


/*********************************************************************************************************************
                                                    类型定义区
*********************************************************************************************************************/
/* 基本类型 --------------------------------------------------------------------------------------------------------*/



/*********************************************************************************************************************
** Function name:           get_endian_format
** Descriptions:            获取系统存储端格式信息
** Input parameters:        none
** Output parameters:       none
** Returned value:          ==0 : 小端存储格式
**                          ==1 : 大端存储格式
**--------------------------------------------------------------------------------------------------------------------
** Created by:              Fengliang
** Created Date:            2010-11-11  15:12:32
** Test recorde:            通过测试
**--------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Test recorde:
*********************************************************************************************************************/
INLINE INT32U get_endian_format( void )
{
    union
    {
        INT32U a;
        INT8U  b;
    }data;

    data.a = 0x01000000;
    return (INT32U)data.b;
}

/*********************************************************************************************************************
** Function name:           align_upside
** Descriptions:            上侧对齐
** Input parameters:        x       : 原始数值
**                          align   : 对齐格式
** Output parameters:       none
** Returned value:          对齐格式化后的数值
**--------------------------------------------------------------------------------------------------------------------
** Created by:              Fengliang
** Created Date:            2010-11-11  14:28:29
** Test recorde:            通过测试
**--------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Test recorde:
*********************************************************************************************************************/
INLINE INT32U align_upside(INT32U x, INT32U align)
{
    return (x + align - 1) & ~(align - 1);
}

/*********************************************************************************************************************
** Function name:           align_downside
** Descriptions:            下侧对齐
** Input parameters:        x       : 原始数值
**                          align   : 对齐格式
** Output parameters:       none
** Returned value:          对齐格式化后的数值
**--------------------------------------------------------------------------------------------------------------------
** Created by:              Fengliang
** Created Date:            2010-11-11  14:29:47
** Test recorde:            通过测试
**--------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Test recorde:
*********************************************************************************************************************/
INLINE INT32U align_downside(INT32U x, INT32U align)
{
    return x & ~(align-1);
}



#ifdef __cplusplus
}
#endif                                                                      /* __cplusplus                          */

#endif                                                                      /* end of __COMMON_H_                 */
/*********************************************************************************************************************
                                                    END OF FILE
*********************************************************************************************************************/

