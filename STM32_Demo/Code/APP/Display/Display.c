#include "BSP\OLED\OLED.h"
#include "BSP\Time\Time.h"
#include <stdint.h>

/**********************************************
* 显示时间
**********************************************/
void Display_Time(void)
{
    OLED_ShowString(10, 10, "Minute: ");
    OLED_ShowString(10, 30, "Second: ");
    OLED_ShowString(10, 50, "MillSe: ");

    OLED_ShowNumber(60, 10, System_Time.Minutes, 3, 12);
    OLED_ShowNumber(60, 30, System_Time.Seconds, 3, 12);
    OLED_ShowNumber(60, 50, System_Time.Milliseconds, 3, 12);

    OLED_Refresh_Gram();
}

void Display_Test(uint32_t a)
{
    OLED_ShowNumber(60, 10, a, 3, 12);
    OLED_Refresh_Gram();
}
