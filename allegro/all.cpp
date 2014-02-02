#include <fstream>
#include <iostream>
#include <stdio.h>
#include <allegro.h>

const int scrx = 640;
const int scry = 480;
 
int main(int argc, char* argv[]) {
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
  if (set_gfx_mode(GFX_AUTODETECT, scrx, scry, 0, 0)) {
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
	std::ifstream ampl("prova.raw");
	ampl.seekg(16);
	unsigned char n; std::string out; char txth[10]; char txtd[10];char txt[20];
	ampl>>n;
	unsigned int i = n;
	std::cout << n << "--->" << i << '\n';
	ampl.close();
	sprintf(txth,"%x",i);
	sprintf(txtd,"%d",i);
	sprintf(txt,"%x---%d",i,i);
	 
  //set text background color to bright blue
  text_mode(makecol(0, 0, 255));
 
  //prints yellow "Hello World!!!" in middle of screen
  textout_centre_ex(screen, font, &txt[0], scrx/2,scry/2, makecol(255, 255, 0),-1);
 
	//should make a graph of the raw file converting its bytes to int

for(int x=0;x<=15;x++){
unsigned char myc; int myi;
ampl.seekg(x);
  ampl>>myc;
  myi = myc;
putpixel(screen,x,myi,makecol(255, 0, 5));
std::cout << '\n' << std::hex << myi ;
}

//line(screen, 0,0,480,480,makecol(255, 0, 5));

  //Wait for a key to be pressed
  while (!keypressed()) {}
 
  return 0;
  //Allegro will automatically deinitalize itself on exit
}
END_OF_MAIN()
