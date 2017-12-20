#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <curses.h>
#include <termios.h>
#include <time.h>

//function to identify if any key is pressed down
int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;
 
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
  ch = getchar();
 
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
 
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }
 
  return 0;
}
//function to split a string using a separator
void split(char buffer[100][100], char *string, char separator){
	int count=0, posi=0;
//clean all the strings
	int z=0;
	while(buffer[z][0] != '\0'==1){
		memset(buffer[z], 0x0, 8);
		z++;
	}

	int i=0;
	while(i<strlen(string)+1){
//if the char is the separator
		if(string[i]==separator){
//replace it with the "end of string" char or the null char
			buffer[count][posi]='\0';

//increment the counter to go to the next string
			count++;
//put the address of first char of the string
			posi=0;
//break the cicle
			i++;
			continue;
		}
//if no put the char of the original string to the new array
		else{
			buffer[count][posi]=string[i];
//increment the char address
			posi++;
		}
		i++;
	}
}

//i just copy this function and have no ideia how it works, i just wanna get a md5 hash of a string
//https://gist.github.com/creationix/4710780

#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

// These vars will contain the hash
uint32_t h0, h1, h2, h3;
 
void md5(uint8_t *initial_msg, size_t initial_len) {
 
    // Message (to prepare)
    uint8_t *msg = NULL;
 
    // Note: All variables are unsigned 32 bit and wrap modulo 2^32 when calculating
 
    // r specifies the per-round shift amounts
 
    uint32_t r[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                    5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
                    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

    // Use binary integer part of the sines of integers (in radians) as constants// Initialize variables:
    uint32_t k[] = {
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
        0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
        0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
        0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
        0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
        0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
        0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
        0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
        0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};
 
    h0 = 0x67452301;
    h1 = 0xefcdab89;
    h2 = 0x98badcfe;
    h3 = 0x10325476;
 
    // Pre-processing: adding a single 1 bit
    //append "1" bit to message    
    /* Notice: the input bytes are considered as bits strings,
       where the first bit is the most significant bit of the byte.[37] */
 
    // Pre-processing: padding with zeros
    //append "0" bit until message length in bit ≡ 448 (mod 512)
    //append length mod (2 pow 64) to message
 
    int new_len;
    for(new_len = initial_len*8 + 1; new_len%512!=448; new_len++);
    new_len /= 8;
 
    msg = calloc(new_len + 64, 1); // also appends "0" bits 
                                   // (we alloc also 64 extra bytes...)
    memcpy(msg, initial_msg, initial_len);
    msg[initial_len] = 128; // write the "1" bit
 
    uint32_t bits_len = 8*initial_len; // note, we append the len
    memcpy(msg + new_len, &bits_len, 4);           // in bits at the end of the buffer
 
    // Process the message in successive 512-bit chunks:
    //for each 512-bit chunk of message:
    int offset;
    for(offset=0; offset<new_len; offset += (512/8)) {
 
        // break chunk into sixteen 32-bit words w[j], 0 ≤ j ≤ 15
        uint32_t *w = (uint32_t *) (msg + offset);
 
#ifdef DEBUG
        printf("offset: %d %x\n", offset, offset);
 
        int j;
        for(j =0; j < 64; j++) printf("%x ", ((uint8_t *) w)[j]);
        puts("");
#endif
 
        // Initialize hash value for this chunk:
        uint32_t a = h0;
        uint32_t b = h1;
        uint32_t c = h2;
        uint32_t d = h3;
 
        // Main loop:
        uint32_t i;
        for(i = 0; i<64; i++) {

#ifdef ROUNDS
            uint8_t *p;
            printf("%i: ", i);
            p=(uint8_t *)&a;
            printf("%2.2x%2.2x%2.2x%2.2x ", p[0], p[1], p[2], p[3], a);
         
            p=(uint8_t *)&b;
            printf("%2.2x%2.2x%2.2x%2.2x ", p[0], p[1], p[2], p[3], b);
         
            p=(uint8_t *)&c;
            printf("%2.2x%2.2x%2.2x%2.2x ", p[0], p[1], p[2], p[3], c);
         
            p=(uint8_t *)&d;
            printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], d);
            puts("");
#endif        

 
            uint32_t f, g;
 
             if (i < 16) {
                f = (b & c) | ((~b) & d);
                g = i;
            } else if (i < 32) {
                f = (d & b) | ((~d) & c);
                g = (5*i + 1) % 16;
            } else if (i < 48) {
                f = b ^ c ^ d;
                g = (3*i + 5) % 16;          
            } else {
                f = c ^ (b | (~d));
                g = (7*i) % 16;
            }

#ifdef ROUNDS
            printf("f=%x g=%d w[g]=%x\n", f, g, w[g]);
#endif 
            uint32_t temp = d;
            d = c;
            c = b;
//            printf("rotateLeft(%x + %x + %x + %x, %d)\n", a, f, k[i], w[g], r[i]);
            b = b + LEFTROTATE((a + f + k[i] + w[g]), r[i]);
            a = temp;


 
        }
 
        // Add this chunk's hash to result so far:
 
        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
 
    }
 
    // cleanup
    free(msg);
 
}

char *MD5(char *msg){
   size_t len = strlen(msg);
 
    // benchmark
    // int i;
    // for (i = 0; i < 1000000; i++) {
        md5(msg, len);
    // }
 
    //var char digest[16] := h0 append h1 append h2 append h3 //(Output is in little-endian)
    uint8_t *p;
 
    // display result
    char *value;
    value=(char *) malloc(33*sizeof(char));
    p=(uint8_t *)&h0;
    sprintf(value, "%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h0);
 
    p=(uint8_t *)&h1;
    sprintf(value, "%s%2.2x%2.2x%2.2x%2.2x", value, p[0], p[1], p[2], p[3], h1);
 
    p=(uint8_t *)&h2;
    sprintf(value, "%s%2.2x%2.2x%2.2x%2.2x", value, p[0], p[1], p[2], p[3], h1);
 
    p=(uint8_t *)&h3;
    sprintf(value, "%s%2.2x%2.2x%2.2x%2.2x", value, p[0], p[1], p[2], p[3], h1);
    return value;
}



void main(){
	FILE *file_r;
	FILE *file_w;
	FILE *passwrd;

	char message[100];
	char user[16];
	char pass[101];
	char line[116];
	char data[5][100];

	printf("USER: ");
	fgets(user, 15, stdin);
//replace the \n (new line char) with the finalization string char \0
	user[strlen(user)-1]='\0';
	printf("PASS: ");
	fgets(pass, 100, stdin);
	pass[strlen(pass)-1]='\0';
//open the password file
	passwrd=fopen("pass.txt", "r");
	if(passwrd==NULL){
		printf("Error opening the file pass.txt. Probably, it is a problem with the permissions.\n");
		exit(1);
	}
	int kill=0;
	while(fgets(line, 150, passwrd)){
		split(data, line, '@');
		if(strcmp(data[0], user)==0){
//if the hash of the password passed by user dont coincide with the recorded hash in the password file, kill the program
			if(strcmp(data[1], MD5(MD5(pass)))==0){
				kill=1;
			}
		}
	}
//no, the program is killed now lol
	if(kill==0){
		printf("Incorrect username or password!\n");
		exit(1);
	}
	fclose(passwrd);

//i prefered to create a pointer for each interaction mode with the file
//in this way, i dont had any problems with the line pointers when the file when the file was read
	file_r=fopen("chat.txt", "r");
	file_w=fopen("chat.txt", "a");
	if(file_w==NULL){
			printf("Could not open the file chat.txt in write mode\n");
			exit(1);
		}
	if(file_r==NULL){
			printf("Could not open the file chat.txt in read mode\n");
			exit(1);
		}
	char buffer[200];
//print all the log of the conversation recorded in the file chat.txt
	while(fgets(buffer, 150, file_r)){
		printf("%s", buffer);
//empty the buffer
		memset(buffer, 0x0, 8);
	}

	char input[100];
	while(1){
//if any new line was added, print the new part in the stdout
		if(fgets(buffer, 150, file_r)){
			printf("%s", buffer);
			memset(buffer, 0x0, 8);
		}
//if any key was pressed, deafen the client and capture all the input data to write in the file chat.txt
		if(kbhit()){
			memset(input, 0x0, 8);
			fgets(input, 200, stdin);
//if the user pressed the enter key without any other char, open other input box
//the common input have a problem, because some first chars cant be erased
//with this input box, we dont have this problem anymore
			if(input[0]=='\n'){
				memset(input, 0x0, 8);
				printf("MESSAGE: ");
				fgets(input, 200, stdin);

			}
//if the last char of the message (in fact, the last character is the \n, but i dont refer to it) is the '#', cancel the sending of the message
			if(input[strlen(input)-2]=='#' && input[strlen(input)-1]=='\n'){
				continue;
			}
//if the input is "/quit\n" (\n is enter key), exits the program
			else if(strcmp(input, "/quit\n")==0){
				fprintf(file_w,"[%s] %s exits\n",__TIME__, user);
				fflush(file_w);
				fclose(file_w);
				fclose(file_r);
				printf("Bye\n");
				exit(1);
			}
//in other case, write the message in the chat.txt file
			else{
				fprintf(file_w,"[%s] %s: %s",__TIME__, user, input);
//empty and force writing of data buffer in the file
				fflush(file_w);
			}
    	}
//refresh period, to save cpu
		sleep(0.5);
	}
}
