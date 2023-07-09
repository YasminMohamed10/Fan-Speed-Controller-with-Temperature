#include "std_types.h"
#include "PWM.h"
#include "adc.h"
#include "lcd.h"
#include "DC_Motor.h"
#include "lm35_sensor.h"

int main(void)
{
	uint8 temp;
	ADC_ConfigType ADC_Config = {Internal_Vref,F_CPU_8};
	ADC_init(&ADC_Config);
	LCD_init();
	DcMotor_Init();
	/* Display this string "Temp =   C" only once on LCD at the first row */
	LCD_displayStringRowColumn(1,1,"Temp =    C");
    while(1)
    {
    	temp = LM35_getTemperature();

    	if(temp<30)
    	{
    		DcMotor_Rotate(DcMotor_OFF,0);
    		LCD_displayStringRowColumn(0,1,"FAN is OFF");
    	}
    	else if(temp>=30 && temp<60)
		{
    		DcMotor_Rotate(DcMotor_u8FORWARD,25);
    		LCD_displayStringRowColumn(0,1,"FAN is ON ");
		}
    	else if(temp>=60 && temp<90)
    	{
    		DcMotor_Rotate(DcMotor_u8FORWARD,50);
    		LCD_displayStringRowColumn(0,1,"FAN is ON ");
    	}
    	else if(temp>=90 && temp<120)
    	{
    		DcMotor_Rotate(DcMotor_u8FORWARD,75);
    		LCD_displayStringRowColumn(0,1,"FAN is ON ");
    	}
    	else
    	{
    		DcMotor_Rotate(DcMotor_u8FORWARD,100);
    		LCD_displayStringRowColumn(0,1,"FAN is ON ");
    	}

		LCD_moveCursor(1,7);
		if(temp >= 100)
		{
			LCD_intgerToString(temp);
		}
		else
		{
			LCD_intgerToString(temp);

			LCD_displayCharacter(' ');
		}
    }
}
