#include <unistd.h>
#include <termios.h>
#include <stdlib.h>  

struct termios default_att; 

void disableRaw(){
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &default_att);  // Sets default attributes into standard input 
}

void enableRaw(){
  
  tcgetattr(STDIN_FILENO, &default_att); // Get's current attributes in standard input and puts it into default_att
  atexit(disableRaw); // registers the function disableRaw to be later use when program exits
  
  struct termios raw = default_att; // Creates a COPY of default_att 


  raw.c_lflag &= ~(ECHO); // Edits an attribute by flipping the bits, in this case ECHO where we will be turning it off

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw); // Sets custom attributes in raw into the standard input 
}

int main() {

  enableRaw(); 
  
  char c;
  while(read(STDIN_FILENO, &c, 1) == 1 && c != 'q'){

  }
  
  return 0;


}