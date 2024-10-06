#include <unistd.h>
#include <termios.h>
#include <stdlib.h>  
#include <ctype.h>
#include <stdio.h>
#include <errno.h> 

struct termios default_att; // struct that will store default terminal attributes 

void disableRaw(){
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &default_att);  // Sets default attributes into standard input 
  if(read(STDIN_FILENO, TCSAFLUSH, 1) == -1){
    die("tcsetattr"); 
  }
}

void die(const char* c){ // A function that is used to create custom errors. Can be use to print out a custom error message 
  perror(c); // Prints an error message 
  exit(1);  // Exits out of terminal/program 
}

void enableRaw(){
  if (tcgetattr(STDIN_FILENO, &default_att) == -1){ //If getting current attributes in standard input fails "returns -1" it will call the die() function and exit the program with custom message "tcgetattr" to show what happen. 
    die("tcgetattr"); 
  }

  tcgetattr(STDIN_FILENO, &default_att); // Get's current attributes in standard input and puts it into default_att
  atexit(disableRaw); // registers the function disableRaw to be later use when program exits

  struct termios raw = default_att; // Creates a COPY of default_att 

  raw.c_cc[VMIN] = 0; // Sets the minimum amount of bytes needed before read() will return. For the following, making it 0 will make read() return immediately whether an input is inputted or not
  raw.c_cc[VTIME] = 1;  // Sets the maximum amount of time before read() can return. For the following, setting it to 1 will make read() wait 100 milliseconds before read() can return 


  raw.c_oflag &= ~(OPOST); // Edits OUTPUT attributes (determines how data going to the screen is processed before being displayed) by flipping bits (~) and adding them to raw struct (&=), to turn off certain signals 
  raw.c_iflag &= ~(IXON | ICRNL | BRKINT | INPCK | ISTRIP); // Edits INPUT attributes (determines how data coming from the keyboard is handled) by flipping bits (~) and adding them to raw struct (&=), to turn off certain signals  
  raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN); // Edits local attributes (how should the terminal behave while you're typing) by flipping the bits (~) and adding them to raw struct (&=), to turn off certain signals  
  raw.c_cflag |= (CS8); // Edits CONTROL attributes (dictate how data travels (format, error checks, flow)). The following ENABLES CS8 which make terminal specify each character received/outgoing data as 8 bits
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw); // Sets custom attributes in raw into the standard input 
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1){ // If setting custom attribute fails "-1" it will exit the program and will print the custom error message tcsetattr. 
    die("tcsetattr");
  } 
}

int main() {

  enableRaw(); // Enables raw mode in terminal
  
  while(1){
    char c = '\0'; // Initialize to null char to ensure that c starts with a known value before read() is called. If doesn't read input thanks to VMIN and VTIME, it will print 0. 
    if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN){  // If read() fails "returns -1" and the error is not EAGIN, it will call the function die which will print error message "read" and exit the program 
      die("read"); 
    }
    read(STDIN_FILENO, &c, 1);
    if(iscntrl(c)){
      printf("%d\r\n", c);  // Prints control character (backspace, spacebar, etc)
    }else{
      printf("%d ('%c')\r\n", c, c); // Print non control characters with its associated ASCII value
    }
    if(c == 'q'){
      break; 
    }
  }
  return 0;
}