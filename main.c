//#include<reg51.h>
#include<reg52.h>
#include<stdio.h>
#include<string.h>

/********************************************* LCD control signals declaration ***************************************************/
 
sbit RS = P0^0;     //
sbit RW = P0^1;  // Read/write line
sbit Enable = P0^2; // Enable line
#define LCD_PORT P2 // define port
//#define Temp_Port P1 // defining Port 1
 
/********************************************* LCD function prototypes ************************************************/
void send_cmd(unsigned char);
void send_char(unsigned char);
void send_int();
void LCD_init(void);
void delayms(unsigned int);
//int get_temp(unsigned int);
//int get_humidity();

/******************************************* delayms Function declaration***********************************************/
void delayms(unsigned int val)
{
 unsigned int i,j;
   
 for(i=0;i<=val;i++)
 {
  for(j=0;j<=2;j++)  ;
  //_nop_();   // no operation produce 1us time delay
 }
  
}
/*********************************************LCD Command Sending Function declaration********************************/
 
void send_cmd(unsigned char Command)
{
 LCD_PORT = Command;
 RS = 0;      // Select Command Register
 RW = 0;    // write operation
 Enable = 1;      // High to Low pulse provided on the enable pin with nearly 1ms(>450ns)
 delayms(1);   // 1 millisec delay
 Enable = 0;
}
 

 

/********************************************* LCD Initialization Function declaration ********************************/
 
void LCD_init()
{
 send_cmd(0x38);      // configuring LCD as 2 line 5x7 matrix
 send_cmd(0x0E);      // Display on, Cursor blinking
 send_cmd(0x01);      // Clear Display Screen
 send_cmd(0x06);      // Increment Cursor (Right side)
}
 
void send_char(unsigned char character)
{
 LCD_PORT = character;
 RS = 1;    // Select Data Register
 RW = 0;    // write operation
 Enable = 1;      // High to Low pulse provided on the enable pin with nearly 1ms(>450ns)
 delayms(1);   // 1 millisec delay
 Enable = 0;
 delayms(10);   // 100 millisec delay
}
 
 


/****************************************** Temperature Function Declaration ********************************************/
void get_temp(unsigned char avalue) large {
	char temp;
	int i = 0;
	int binaryvalue[71] = {01000001,00100001,01100001,00010001,10010001,11010001,10110001,11110001,00001001,01001001,00101001,01101001,11101001,10011001,01011001,00111001,01111001,11111001,10000101,01000101,00100101,10100101,01100101,00010101,10010101,11010101,00110101,01110101,01110101,00001101,10001101,01001101,11001101,00101101,01101101,01101101,11101101,00011101,01011101,01011101,11011101,00111101,10111101,01111101,11111101,11111101,00000011,10000011,10000011,01000011,11000011,00100011,00100011,10100011,10100011,01100011,11100011,11100011,11100011,00010011,00010011,10010011,10010011,01010011,01010011,11010011,11010011,11010011,00110011,00110011,10110011};
	const char *temperature[71] = {"-20","-19","-18","-17","-16","-15","-14","-13","-12","-10","-9","-8","-7","-6","-5","-4","-3","-2","-1","0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50"};
	if(avalue == binaryvalue[i])
	{
		for(i=0 ; i<sizeof(binaryvalue) ; i++)
		{
			temp = temperature[i];
		}
	}
	//unsigned char p1,p2,p3;
	send_char(temp);
}

/********************************************* Main Funciton declaration ***********************************************/
void main()
{

	LCD_PORT = 0x00; // Make the port as output port
  P1 = 0xFF; 
	LCD_init();            // LCD initialization
  send_cmd(0x80);     // Force cursor to beginning of 1st line, if the number is 0x83 then force the cursor to 53rd position
  delayms(100);    // Delay of 100millisec
  send_char('T');
	send_char('H');
	send_char('E');
	send_char('R');
	send_char('M');  // Send data
	send_char('I');
	send_char('S');
	send_char('T');
	send_char('O');
	send_char('R');  // Send data	
  send_cmd(0xC0);     // Force cursor to beginning of 2nd line
  delayms(100);    // Delay of 100millisec
  send_char('V');  // Send data 
  send_char('A');  // Send data 
  send_char('L');  // Send data 
	send_char('U');  // Send data 
  send_char('E');  // Send data 
  send_char(':');  // Send data
	char value;
	value = P1;
	get_temp(value);
	}
 //}

 
 