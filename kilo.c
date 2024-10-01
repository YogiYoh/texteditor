#include <unistd.h>
#include <termios.h>
#include <stdlib.h>  
#include <ctype.h>
#include <stdio.h>

struct termios default_att; // struct that will store default terminal attributes 

void disableRaw(){
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &default_att);  // Sets default attributes into standard input 
}

void enableRaw(){
  
  tcgetattr(STDIN_FILENO, &default_att); // Get's current attributes in standard input and puts it into default_att
  atexit(disableRaw); // registers the function disableRaw to be later use when program exits
  
  struct termios raw = default_att; // Creates a COPY of default_att 

  raw.c_iflag &= ~(IXON | ICRNL); // Edits INPUT attributes (determines how data coming from the keyboard is handled) by flipping bits (~) and adding them to raw struct (&=), to turn off certain signals  
  raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN); // Edits local attributes (how should the terminal behave while you're typing) by flipping the bits (~) and adding them to raw struct (&=), to turn off certain signals  

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw); // Sets custom attributes in raw into the standard input 
}

int main() {

  enableRaw(); // Enables raw mode in terminal
  
  char c;
  while(read(STDIN_FILENO, &c, 1) == 1 && c != 'q'){
      if(iscntrl(c)){
        printf("%d\n", c);  // Prints control character (backspace, spacebar, etc)
      }else{
        printf("%d ('%c')\n", c, c); // Print non control characters with its associated ASCII value
      }
  }
  return 0;
}