#include "main.h"
#include "base.h"

char TXbuff[128];
char RXbuff[128];
char start_flag=0;
uint32_t  White_On_Times=0;
uint32_t  White_Off_Times=0;
uint32_t   Black_Times=0;
uint32_t   White_Times=0;
uint8_t    Cyclic_Times=0;
uint32_t   Idle_Times=0;
uint8_t   White_On_Flag=0;
uint8_t   White_Off_Flag=0;
uint8_t   i=0;

uint8_t   Pass_Flag=0;
uint8_t   Fail_Flag=0;
uint8_t   Test_Flag=0;
uint8_t   Busy_Flag=0;
uint8_t   Help_Flag=0;
float     White_val=0;
float     Black_val=0;
uint8_t   Debug_flag=0;

uint32_t  Test_Times=0;
uint32_t  timeout=0;
uint8_t   CMD_HELP[]="HELP\r\n";
uint8_t   LED_R_ON_[]="LED_R_ON\r\n";
uint8_t   LED_G_ON_[]="LED_G_ON\r\n";
uint8_t   LED_Y_ON_[]="LED_Y_ON\r\n";
uint8_t   LED_ON_[]="LED_ON\r\n";
uint8_t   LED_OFF_[]="LED_OFF\r\n";
uint8_t   VERSION[]="VERSION\r\n";
uint8_t   GET_ADC[]="GET_ADC\r\n";
uint8_t   GET_VAL[]="GET_VAL\r\n";
uint8_t   F_SET_VAL1[]="F_SET_VALW\r\n";
uint8_t   F_SET_VAL2[]="F_SET_VALB\r\n";
uint8_t   F_GET_VAL[]="F_GET_VAL\r\n";
uint8_t   DEBUG[]="DEBUG\r\n";
float voltage=0.0;
float voltage_new=0.0;
float voltage_new1=0.0;
float voltage_new2=0.0;

void USART_protocol_parsing(void)
{
	char i;

	uint8_t String_buf[128]={0};
	
	if(USART1_RX_Flag==1)
	{
		USART1_RX_Flag=0;
		for(i=0;i<USART1_RX_Count;i++)
		{
			String_buf[i]=toupper(USART1_RX_BUF[i]); //È«²¿×ª»»Îª´óÐ´
		}
		memset(USART1_RX_BUF,'\0',USART1_RX_Count);
		String_buf[i]='\0';
		switch(String_buf[0])
		{		
			case 'H':
				if(StringCompare2(CMD_HELP,String_buf)==0)
					{
					printf("HELP\r\n");
					printf("Version\r\n");
					printf("DEBUG\r\n");
					printf("LED_R_ON\r\n");
					printf("LED_G_ON\r\n");
					printf("LED_Y_ON\r\n");
					printf("LED_ON\r\n");
					printf("LED_OFF\r\n");					
					printf("GET_ADC\r\n");
					printf("GET_VAL\r\n");
					printf("F_SET_VALW:2.22\r\n");
					printf("F_SET_VALB:0.50\r\n");						
					printf("F_GET_VAL\r\n");
					Help_Flag=1;						 
					}	
				else
					{
						Help_Flag=0;
						Debug_flag=0;
						printf("COMMAND ERROR\r\n");
					}				
			break;
					
			case 'D':
				if(StringCompare2(DEBUG,String_buf)==0)
					{				
					    Debug_flag=1;	
   						Help_Flag=0;
					}	
				else
					{
						Help_Flag=0;
						Debug_flag=0;
						printf("COMMAND ERROR\r\n");
					}				
			break;		
									

			case 'L':
				if(StringCompare2(LED_R_ON_,String_buf)==0)
					{
					   LED_R_ON;					
					   printf("ok\r\n");					
					
					}
				else if(StringCompare2(LED_G_ON_,String_buf)==0)
					{
						LED_G_ON;
					   printf("ok\r\n");
					}
				else if(StringCompare2(LED_Y_ON_,String_buf)==0)
					{
					   LED_Y_ON;
					   printf("ok\r\n");
					}
			   else if(StringCompare2(LED_OFF_,String_buf)==0)
					{
					  LED_Y_OFF;
					  LED_G_OFF;
					  LED_R_OFF;
					  printf("ok\r\n");
					}
			   else if(StringCompare2(LED_ON_,String_buf)==0)
					{
					  LED_Y_ON;
					  LED_G_ON;
					  LED_R_ON;
					  printf("ok\r\n");
					}				
			   else
					{
					printf("COMMAND ERROR\r\n");
					}
				break;

			case 'V':
				if(StringCompare2(VERSION,String_buf)==0)
					{
					printf("Burnin Version 1.6\r\n");
					}
				else
					{
					printf("COMMAND ERROR\r\n");
					}
				break;
				
			case 'G':
				if(StringCompare2(GET_ADC,String_buf)==0)
					{				                
						printf("ADC_Value:%.3f\r\n",GetValue2(9));
					}
							
			  else if(string_compare_len(GET_VAL,String_buf,7)==0)
					{
				      int a=0;
                      for(a=0;a<200;a++)
						{
							HAL_Delay(100);
							printf("ADC_Value:%.3f\r\n",GetValue2(9));
						}					
					
					}
				else
					{
					printf("COMMAND ERROR\r\n");
					}
				break;
			case 'F':
				if(string_compare_len(F_SET_VAL1,String_buf,10)==0)
					{													
					     uint32_t a;
						 int b,c,d;
						 b=String_buf[11]-'0';						
						 c=String_buf[13]-'0';						
						 d=String_buf[14]-'0';											
						 a=b*100+c*10+d;					  										
					     FLASH_Write(0x08008000,a);
						 float e=(float)a/100;						
					     printf("set value1:%.2f\r\n",e);
						 SET_VAL();
					}
				else if(string_compare_len(F_SET_VAL2,String_buf,10)==0)
					{						
							
					     uint32_t a;
						 int b,c,d;
						 b=String_buf[11]-'0';						
						 c=String_buf[13]-'0';						
						 d=String_buf[14]-'0';												
						 a=b*100+c*10+d;					  										
					     FLASH_Write(0x08008400,a);
						 float e=(float)a/100;						
					     printf("set value2:%.2f\r\n",e);
						 SET_VAL();
					}					
				else if(StringCompare2(F_GET_VAL,String_buf)==0)
					{
					    
						SET_VAL();											
						
					}
				else
					{
					printf("COMMAND ERROR\r\n");
					}
					
				 break;								

			default:
				Help_Flag=0;
			    Debug_flag=0;
				printf("COMMAND ERROR\r\n");
			    break;
			
		}
		
		memset(String_buf,'\0',USART1_RX_Count);
		USART1_RX_Count=0;
	}
}




void SET_VAL(void)
{
    float Read; 						
	Read=FLASH_Read(0x08008000);
	White_val=Read/100;	
   if(White_val>5||White_val<2.5)
		{
		   FLASH_Write(0x08008000,250);
		   Read=FLASH_Read(0x08008000);
	       White_val=Read/100;	
		   printf("read value1:%.2f\r\n", White_val);	 
		}
   else  printf("read value1:%.2f\r\n", White_val);		 
	Read=FLASH_Read(0x08008400);
	Black_val=Read/100;	
 if(Black_val>5)
          {
           FLASH_Write(0x08008400,50);
		   Read=FLASH_Read(0x08008400);
	       Black_val=Read/100;	
           printf("read value2:%.2f\r\n", Black_val);		
           }	 
else  printf("read value2:%.2f\r\n", Black_val);		

}

void LED_GREEN(void)
{
	 LED_G_ON;			
	 LED_R_OFF;
	 LED_Y_OFF;	

}
void LED_RED(void)
{
	 LED_G_OFF;			
	 LED_R_ON;
	 LED_Y_OFF;	

}
void LED_Yellow(void)
{
     LED_G_OFF;		
	 LED_R_OFF;
	 LED_Y_ON;
}


void LED_DISPALY(void)
{   	 
 
	voltage=GetValue2(7);
	printf("voltage=%.3f\r\n",voltage);
if(fabs(voltage-voltage_new)<0.4)
	{
	    Test_Times++;
		if(i==99)
		{
			i=0;
		  printf("###################################################################Busy_Times=%d\r\n",Test_Times);	
		}
		else i++;

	}
else 
	{
		i=0;
		Test_Times=0;
		printf("#########################################################################Busy_Times=%d\r\n",Test_Times);
	}
//	voltage_new2=voltage_new1;
//	voltage_new1=voltage_new;
	voltage_new=voltage;
	
//	printf("voltage_new=%.3f\r\n",voltage_new);	
if(voltage>White_val&&voltage<3.4)                   //ÆÁÄ»°×É«µçÑ¹  0.1S¶ÁÒ»´Î
	{	
		 
		 Idle_Times=0;
		 Black_Times=White_Off_Times;
//		 printf("$Black_Times=%d\r\n",Black_Times);		    
		 White_Off_Flag=0;
		if(White_On_Flag==0)
		{
			
			White_On_Times=1;
			White_On_Flag=1;
		}
        else 
		{  
			White_Times=0;
		    White_Off_Times=0;
			White_On_Times++;
            			
		}	
		printf("*****************W_TIMES=%d\r\n",White_On_Times);		
	}
else if(voltage<Black_val&&voltage>0.2)             //ÆÁÄ»ºÚÉ«µçÑ¹
		{	
			White_Times=White_On_Times;
//			printf("*****************White_Times=%d\r\n",White_Times);	
			Black_Times=0;
			Idle_Times=0;		
			White_On_Flag=0;
        if(White_Off_Flag==0)
			{
			 White_Off_Times=1;
			 White_Off_Flag=1;
			}
		else 
		{
		   White_Off_Times++;
//			if(White_Off_Times==6000)
//			{
//			    White_Off_Times=0;
//				White_On_Times=0;
//			}
		}	    
		printf("$B_TIMES=%d\r\n",White_Off_Times);		
		}
else  
{
     Idle_Times++;
	if(Idle_Times==15)
	{
		White_Off_Times=0;
	    White_On_Times=0;
		Black_Times=0;
		White_Times=0;
	}

}
	
//ÆÁÄ»°×É«2S£¬ºÚÉ«118S,£¬ÂÌµÆ 20 1180
if(Debug_flag==0)
	{
//		if(6<White_Times&&White_Times<34&&2966<Black_Times&&Black_Times<2994)	 //6/27ÐÞ¸Ä
		if(10<White_Times&&White_Times<34&&1170<Black_Times&&Black_Times<1194)	   
		{
		  White_Times=0;
		  Black_Times=0;
		  Busy_Flag=0;  		
		  LED_GREEN();	 
	      printf("Test PASS*****\r\n*_*\r\n");        				
		}
//ÆÁÄ»°×É«6S£¬ºÚÉ«112S£¬ºìµÆ	60 1140
//		else if (66<White_Times&&White_Times<94&&2906<Black_Times&&Black_Times<2934)   //6/27ÐÞ¸Ä
		else if (50<White_Times&&White_Times<74&&1130<Black_Times&&Black_Times<1154) 
		{
		  White_Times=0;
		  Black_Times=0;
		  Busy_Flag=0;						
		  LED_RED();
		  printf("Test FAIL\r\n*_*\r\n");		
		}
 //ÆÁÄ»°×É«2S£¬ºÚÉ«58S ,»ÆÉ«µÆ 20 580
//		else if (36<White_Times&&White_Times<64&&536<Black_Times&&Black_Times<564)   //6/27ÐÞ¸Ä
		else if (10<White_Times&&White_Times<34&&570<Black_Times&&Black_Times<594)  			
		{		 
			White_Times=0;
			Black_Times=0;
			Busy_Flag=0;	
			LED_Yellow();		
			printf("Testing\r\n*_*\r\n");		
		}
 //ÆÁÄ»°×É«2S£¬ºÚÉ«30S ,»ÆÉ«µÆ 20 280	
//	else if (16<White_Times&&White_Times<44&&256<Black_Times&&Black_Times<284)       //6/27ÐÞ¸Ä
	else if (10<White_Times&&White_Times<34&&270<Black_Times&&Black_Times<294)  	 
		{	 
			reset();		
			Busy_Flag=2;
			printf("Detected Puck\r\n*_*\r\n");		
		}
//×´Ì¬²»¶Ô		
		else if(Test_Times==18000) 
		{     				
			reset();		
			Busy_Flag=1;
		}		
	} 	
 else
	{
    	//ÆÁÄ»°×É«2S£¬ºÚÉ«8S£¬ÂÌµÆ	
	  if(10<White_Times&&White_Times<30&&Black_Times>60&&Black_Times<90)   	 
		{
			  White_Times=0;
			  Black_Times=0;
			  Busy_Flag=0;	  		
			  LED_GREEN();	 
			  printf("Test PASS*****\r\n*_*\r\n");        				
		}
	//ÆÁÄ»°×É«8S£¬ºÚÉ«2S£¬ºìµÆ	

	 else if (70<White_Times&&White_Times<90&&Black_Times>10&&Black_Times<30)  	 
		{
			  White_Times=0;
			  Black_Times=0;
			  Busy_Flag=0;						
			  LED_RED();
			  printf("Test FAIL\r\n*_*\r\n");		
		}
	 //ÆÁÄ»°×É«5S£¬ºÚÉ«5S ,»ÆÉ«µÆ 
	else if (36<White_Times&&White_Times<64&&36<Black_Times&&Black_Times<64)  	 
		{	 
			White_Times=0;
			Black_Times=0;
			Busy_Flag=0;
	//		Test_Times=0;	
			LED_Yellow();		
			printf("Testing\r\n*_*\r\n");		
		}
 //ÆÁÄ»°×É«3S£¬ºÚÉ«15S ,»ÆÉ«µÆÉÁË¸ 		
	else if (16<White_Times&&White_Times<44&&136<Black_Times&&Black_Times<164)  	 
	{	 
		 reset();		
		 Busy_Flag=2;
		 printf("Detected puck\r\n*_*\r\n");		
    }			
//×´Ì¬²»¶Ô 5mins		
	else if(Test_Times==3000) 
		{     				
			reset();		
			Busy_Flag=1;
		}		
	 } 
 
}

void reset(void)
{
    White_On_Times=0;
    White_Off_Times=0;	
	Black_Times=0;
	White_Times=0;
    Test_Times=0;
	LED_G_OFF;
	LED_R_OFF;	
	LED_Y_OFF;
	Pass_Flag=0;
	Fail_Flag=0;
	Test_Flag=0;
}

