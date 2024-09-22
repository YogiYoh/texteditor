#include <unistd.h>
#include <termios.h>
#include <stdlib.h>  


void enableRaw(){
  struct termios raw; 

  tcgetattr(STDIN_FILENO, &raw); // Get's current attributes in standard input and puts it into raw

  raw.c_lflag &= ~(ECHO); // Edits an attribute by flipping the bits, in this case ECHO where we will be turning it off

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw); // Sets attributes in raw into the standard input 
}

int main() {

  enableRaw(); 
  
  char c;
  while(read(STDIN_FILENO, &c, 1) == 1 && c != 'q'){

  }
  return 0;


}