//////////////////////////////////////////////

void FrameH(void)
{

   output_high(pin_E0);

}

void FrameL(void)
{

   output_LOW(pin_E0);

}

//////////////////////////////////////////////

void LoadH(void)
{

   output_high(pin_E1);

}

void LoadL(void)
{

   output_low(pin_E1);

}

//////////////////////////////////////////////

void Cp(void)
{

   output_high(pin_E2);
   output_low(pin_E2);

}

//////////////////////////////////////////////

void DispOFF(void)
{

   output_low(pin_B4);

}
void DispON(void)
{

   output_high(pin_B4);

}

//////////////////////////////////////////////

void MON(void)
{

   output_high(pin_B5);

}
void MOFF(void)
{

   output_low(pin_B5);

}

void ToggleM(void)
{
   if((input(pin_b5))==1)
      output_low(pin_B5);
   else
      output_high(pin_B5);

}

//////////////////////////////////////////////

Void Pilota(long x, long y)
{
   int i,j;
   
   for(i=1;i<=240;++i)
   {
      
      if(i==240)
      {
         frameH();
      }     
      
      for(j=1;j<80;++j)
      {
         Cp();
      }
      
      LoadH();
      
      if(i==240)
      {
         frameL();
      }
      
      LoadL();        
      
   }
   
}


//////////////////////////////////////////////
