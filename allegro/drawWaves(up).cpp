#include <fstream>
#include <iostream>
#include <stdio.h>
#include <allegro.h>

const int scrx = 1280;
const int scry = 960;
 
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
  if (set_gfx_mode(GFX_AUTODETECT, 0, 0, scrx, scry)) {
    set_color_depth(24);
    if (set_gfx_mode(GFX_AUTODETECT, 0, 0, scrx, scry)) {
      set_color_depth(16);
      if (set_gfx_mode(GFX_AUTODETECT, 0, 0, scrx, scry)) {
        set_color_depth(15);
        if (set_gfx_mode(GFX_AUTODETECT, 0, 0, scrx, scry)) {
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

for(int x=0;x<=scrx;x+=1){
unsigned char myc[4]; unsigned int myi[4];
ampl.seekg(x);
for(int t=0;t<=4;t++){
  ampl>>myc[t];
  myi[t] = myc[t];
}



line(screen, x,myi[0]+myi[1]+scry/2,x+1,myi[1]+myi[2]+scry/2,makecol(255, 0, 5));
putpixel(screen,x,myi[0]+myi[2]+scry/2,makecol(255, 0, 5));
std::cout << '\t' << myi[0] ;
}

  //Wait for a key to be pressed
  while (!keypressed()) {}
 
ampl.close();
  return 0;
  //Allegro will automatically deinitalize itself on exit
}
END_OF_MAIN()
