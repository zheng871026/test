#include "stm8l10x.h"
#include "dht22.h"
#include "delay.h"

int DHT22_ReadByte(void)
{
	u8 data=0, i;
        disableInterrupts();//使能中断
	for(i=0; i<8; i++)
	{       
		while(!DHT22_In);
		delay_us(30);
		data = data << 1;
		if(DHT22_In)
                data |= 1;
	        while(DHT22_In);	
	}
        enableInterrupts();//使能中断
	return data;
}
	

u8 ReadDHT22(u8 data[])
{  
   u8 check = 0xff, sum = 0;
   disableInterrupts();//使能中断
   DHT22_PortOUT;
   DHT22_Reset;
   delay_ms(22);  
   DHT22_Set;
   delay_us(25);
   DHT22_PortIN;
   if(!DHT22_In)
   {        
	while(!DHT22_In);
        while(DHT22_In); 
        enableInterrupts();//使能中断      
        data[0] = DHT22_ReadByte();
        data[1] = DHT22_ReadByte();
        data[2] = DHT22_ReadByte();
	data[3] = DHT22_ReadByte();
	check = DHT22_ReadByte();
	sum = (data[0]+data[1]+data[2]+data[3]);
   }
   else enableInterrupts();//使能中断
   DHT22_PortOUT;  
   IWDG_ReloadCounter(); 
   if(check == sum)
   return 1;
   else	
   return 0;
}