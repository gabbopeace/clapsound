#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <allegro.h>

const int scrx = 640*2;
const int scry = 480*2;
 PALETTE pal;


int main(int argc, char* argv[]) { 

int zoom=1; //distanza tra un campione e l'altro sullo schermo
if(argv[1]!=NULL)zoom=atoi(argv[1]);
std::string raw = "reg.raw"; //input raw file
if(argv[2]!=NULL)raw=argv[2];
int b=1; //numero di byte per frame
if(argv[3]!=NULL)b=atoi(argv[3]);
int vc=1; //Vertical zoom
if(argv[4]!=NULL)vc=atoi(argv[4]);
unsigned char myc[2][b-1]; char msbc; uint8_t myi[2][b-1]; int8_t msb; int msbi; char number[5];
int MYI[2]={0,0}; 

std::cout << "1 : "<< argv[0] << "--2 : "<< argv[1] << "\n";

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
  if (set_gfx_mode(GFX_AUTODETECT, scrx, scry,0, 0)) {
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
	std::ifstream ampl(&raw[0]);
	FILE *stream=fopen(&raw[0],"r");
	ampl.seekg(16);
	unsigned char n; std::string out; char txth[10]; char txtd[10];char txt[20];
	ampl>>n;
	unsigned int i = n;
	std::cout << n << "--->" << i<< "   zoom: "<< zoom << '\n';
	sprintf(txth,"%x",i);
	sprintf(txtd,"%d",i);
	sprintf(txt,"%x---%d",i,i);
	 
  //set text background color to bright blue
  text_mode(makecol(0, 0, 255));
 
  //prints yellow "Hello World!!!" in middle of screen
  textout_centre_ex(screen, font, &txt[0], scrx/2,scry/2, makecol(255, 255, 0),-1);
 
	//should make a graph of the raw file converting its bytes to int
ampl.seekg(0);
for(int x=0;(x<=scrx)&&(!keypressed());x+=zoom){
sprintf(number,"%d",x/zoom);
MYI[0]=MYI[1];
MYI[1]=0;
//MYI[1]=0;
//memorize the next frame value
for(int t=0;t<b-1;t++){
 // myi[1][t]=fgetc(stream);
  ampl>>myi[1][t];

  myi[1][t]*=1;
  MYI[1]+=myi[1][t];
}
 // msbi=fgetc(stream);
   ampl>>msb;
  msbi=msb*256;
if( msb<0 )
  MYI[1]*=-1;
  //MYI[0];
  MYI[1]+=msbi;

line(screen, x,MYI[0]/vc+scry/2,x+zoom,MYI[1]/vc+scry/2,makecol(255, 0, 5));
putpixel(screen,x,MYI[1]/vc+scry/2,makecol(100,255, 105));
std::cout <<"msb:" << (int) msb << "\t" <<"msbi:" << (int) msbi << "\t" <<"myi:" << (int) myi[1][0] << "\t" << "MYI[1]:" << MYI[1] << "\t" << "MYI[0]:" << MYI[0] << "\n";

//make a line every 30 frames
if( x%30==0 ){
line(screen, x,0,x,scry,makecol(0,255, 5));
textout_centre_ex(screen, font, &number[0], x,scry-10, makecol(255, 255, 0),-1);
			}
}
putpixel(screen,1,1,makecol(0, 255, 5));


//memorize screen on bitmap "bit.bmp"
get_palette(pal);
save_bitmap("bit.bmp",screen,pal);

  //Wait for a key to be pressed
  while (!keypressed()) {}
 
std::cout << "\n";

//ampl.close();
  return 0;
  //Allegro will automatically deinitalize itself on exit
}
END_OF_MAIN()
