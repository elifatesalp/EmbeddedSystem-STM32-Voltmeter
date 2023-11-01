//VOLTMETRE KODU
//LCD bağlantıları  tanımlanıyor

sbit LCD_RS at GPIOE_ODR.B8;
sbit LCD_EN at GPIOE_ODR.B10;
sbit LCD_D4 at GPIOE_ODR.B4;
sbit LCD_D5 at GPIOE_ODR.B5;
sbit LCD_D6 at GPIOE_ODR.B6;
sbit LCD_D7 at GPIOE_ODR.B7;
//lcd bağlantıları tanımlandı

int sayi=0, mV=0;
char txt[7], volt[9];

int ADC_Olcum(char kanal) //analog ölçümün yapıldığı fonksiyon
{
  unsigned long temp= 0;
  char k=0;
  for(k=0; k<128; k++)
  {
  temp+=ADC1_Get_Sample(kanal);
  }
  return temp>>7;
}
void LCD_Yaz(int okunan_deger) //okunan ADC değerinin voite dönüştürülmesi veya yazdırılması
{
mV=okunan_deger*0.7185;  //resualtion=(Vref+-Vref-)/2n-1 _ 2943/4095=0.7185

if(mV>=10000) volt[0]=(mV/10000)+48;

  else volt[0]=' ';
  volt[1]=(mV%10000)/1000+48;
  volt[2]=' ';
  volt[3]= (mV%1000)/100+48;
  volt[4]= (mV%1000)%100/10+48;
  volt[5]= (mV%1000)%100%10+48;
  volt[6]=' ';
  volt[7]='V';
  
  Lcd_Out(2,1,volt);
  }
  

void main() 
{
   GPIO_Digital_Output(&GPIOE_BASE, _GPIO_PINMASK_9); //  R/W pini şaseye çekiliyor
   GPIOE_ODR.B9=0;
   Lcd_Init();
   ADC1_Init();  //ADC1 kurulluyor
   ADC_Set_Input_Channel(_ADC_CHANNEL_1);      //ADCnin 1. kanalı ADC girişi tanımlıyor
   Lcd_Cmd(_LCD_CURSOR_OFF); //LCD imleci kpataılıyor
   Lcd_Out(1,1,"Voltmetre");
   do
   {
   sayi=ADC_Olcum(1);
   LCD_Yaz(sayi);
   }
   while(1);
}
