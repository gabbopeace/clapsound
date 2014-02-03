#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <allegro.h>

const int scrx = 640;
const int scry = 480;
 PALETTE pal;

 const int b=2;

int main(int argc, char* argv[]) {

unsigned char myc[2][b]; int myi[2][b]; char number[5];
int MYI[2]={0,0};  

if (allegro_init() != 0) {
    allegro_message("Cannot initalize Allegro.\n");
    return 1;
  }
 
  //Set the window title when in a GUI environment
  set_window_title("Hello World");
 
  if (install_keyboard()) {
    allegro_message("Cannot initalize keyboard input.\n");
    return 1;
  }
 
  //set graphics mode, trying all acceptable depths
  set_color_depth(32);
  if (set_gfx_mode(GFX_AUTODETECT, scrx, scry,0,0)) {
    set_color_depth(24);
    if (set_gfx_mode(GFX_AUTODETECT, scrx, scry, 0, 0)) {
      set_color_depth(16);
      if (set_gfx_mode(GFX_AUTODETECT, scrx, scry, 0, 0)) {
        set_color_depth(15);
        if (set_gfx_mode(GFX_AUTODETECT, scrx, scry, 0, 0)) {
          allegro_message("Video Error: %s.\n", allegro_error);
          return 1;
        }
      }
    }
  }
	std::ifstream ampl("reg.raw");
	ampl.seekg(16);
	unsigned char n; std::string out; char txth[10]; char txtd[10];char txt[20];
	ampl>>n;
	unsigned int i = n;
	std::cout << n << "--->" << i << '\n';
	sprintf(txth,"%x",i);
	sprintf(txtd,"%d",i);
	sprintf(txt,"%x---%d",i,i);
	 
  //set text background color to bright blue
  text_mode(makecol(0, 0, 255));
 
  //prints yellow "Hello World!!!" in middle of screen
  textout_centre_ex(screen, font, &txt[0], scrx/2,scry/2, makecol(255, 255, 0),-1);
 
	//should make a graph of the raw file converting its bytes to int
ampl.seekg(0);
for(int x=0;(x<=scrx)&&(!keypressed());x+=5){

sprintf(number,"%d",x);
MYI[1]=0;
for(int t=0;t<b;t++){
  ampl>>myc[1][t];
  myi[1][t] = myc[1][t];
  MYI[1]+=myi[1][t];
}
get_palette(pal);
save_bitmap("bit.bmp",screen,pal);

line(screen, x,MYI[0],x+5,MYI[1],makecol(255, 0, 5));
putpixel(screen,x,MYI[0],makecol(255, 0, 5));
std::cout << '\t' << MYI[0] ;

if( x%30==0 ){
line(screen, x,0,x,scry,makecol(0,255, 5));
textout_centre_ex(screen, font, &number[0], x,scry-10, makecol(255, 255, 0),-1);
			}

MYI[0]=MYI[1];
}
putpixel(screen,1,1,makecol(0, 255, 5));
  //Wait for a key to be pressed
  while (!keypressed()) {}
 
//ampl.close();
  return 0;
  //Allegro will automatically deinitalize itself on exit
}
END_OF_MAIN()
