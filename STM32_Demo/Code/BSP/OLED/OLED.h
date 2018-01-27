#ifndef __OLED_H
#define __OLED_H
			  	 
#include "sys.h"

//-----------------OLED端口定义---------------- 
#define OLED_RST_Clr()      PCout(8) = 0    //RST
#define OLED_RST_Set()      PCout(8) = 1    //RST

#define OLED_RS_Clr()       PCout(7) = 0    //DC
#define OLED_RS_Set()       PCout(7) = 1    //DC

#define OLED_SCLK_Clr()     PAout(8) = 0    //SCL D0
#define OLED_SCLK_Set()     PAout(8) = 1    //SCL

#define OLED_SDIN_Clr()     PCout(9) = 0    //SDA D1
#define OLED_SDIN_Set()     PCout(9) = 1    //SDA

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据


//OLED控制用函数
void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode);
void OLED_ShowNumber(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y,const u8 *p);	 
#endif  
	 
