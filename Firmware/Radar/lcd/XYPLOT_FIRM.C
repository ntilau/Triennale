void cursore(int x, int y, int1 colore)
{
   glcd_text57(x-2, y-4, curs, 1, colore);
}

void griglia(void)
{

   int i,j;

   for(i=0;i<239;i+=24)
   {
      glcd_pixel(i,2,on);
      glcd_pixel(i,3,on);
      glcd_pixel(i,237,on);
      glcd_pixel(i,236,on);
      glcd_pixel(2,i,on);
      glcd_pixel(3,i,on);
      glcd_pixel(236,i,on);
      glcd_pixel(237,i,on);
   }

   restart_wdt();

   for(i=0;i<239;i+=24)
   {
      for(j=0;j<239;j+=24)
      {

         glcd_pixel(i,j,on);
      }
   }

  glcd_line(118, 120, 122, 120, on);
  glcd_line(120, 118, 120, 122, on);

}

void Rett(void)
{
   int i,j;

   glcd_line(0, 0, 319, 0, on);
   glcd_line(0, 239, 319, 239, on);
   glcd_line(0, 0, 0, 239, on);
   glcd_line(239, 0, 239, 239, on);

   glcd_line(1, 1, 239, 1, on);
   glcd_line(1, 238, 239, 238, on);
   glcd_line(1, 0, 1, 239, on);
   glcd_line(238, 0, 238, 239, on);
   
   glcd_line(319, 0, 319, 239, on);

   glcd_line(240, 48, 319, 48, on);
   glcd_line(240, 96, 319, 96, on);
   glcd_line(240, 144, 319, 144, on);
   glcd_line(240, 192, 319, 192, on);

   



}

