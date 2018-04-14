#include <stdio.h>  //Including the header files.
#include<stdlib.h>
#include<string.h>
#include
#define KEY_LENGTH 9 // Can be anything from 1 to 13

int main(){  
  unsigned char ch;  
  FILE *fpIn, *fpOut;  
  int i;  unsigned char key[KEY_LENGTH] = {0x02 ,0x1A, 0xFB, 0xAC, 0xA9, 0x05, 0xFF, 0xAA, 0xBD};
  /*  Of course, I did not use the all-0s key to encrypt. */

  fpIn = fopen("ptext.txt","r");  
  fpOut = fopen("ctext.txt","w");
  i=0;  
  while (fscanf(fpIn, "%c", &ch)!= EOF) {
    /* avoid encrypting newline characters */      
   /* In a "real-world" implementation of the Vigenere cipher,        
      every ASCII character in the plaintext would be encrypted.       
      However, I want to avoid encrypting newlines here because        
      it makes recovering the plaintext slightly more difficult... */    
   /* ...and my goal is not to create "production-quality" code =) */    
   if (ch!='\n') {      
     fprintf(fpOut, "%02X", ch ^ key[i % KEY_LENGTH]); // ^ is logical XOR          
     i++;      }    
  }   
 
  fclose(fpIn);  //closing the files.
  fclose(fpOut);  
  return 0;
} 
