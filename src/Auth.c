#include "../include/Auth.h"
#include "../include/Colors.h"
#include "../include/Input.h"
#include <stdio.h>
#include <string.h>
#ifdef _WIN32
#include <conio.h>
#endif
void getPasswordMasked(char *pass,int maxLen) {
#ifdef _WIN32
    int i=0;
    int ch;
    while ((ch=_getch())!='\r') {
        if (ch=='\b') { if(i>0){i--; printf("\b \b");} }
        else if(ch>=32 && ch<=126 && i<maxLen-1){pass[i++]=(char)ch; putchar('*');}
    }
    pass[i]='\0'; putchar('\n');
#else
    if (!fgets(pass,maxLen,stdin)) { pass[0]='\0'; return; }
    pass[strcspn(pass,"\r\n")]='\0';
#endif
}
int login(void) {
    char user[32], pass[32]; int attempts=3;
    printf(COLOR_HEADER "\n========== HOTEL MANAGEMENT SYSTEM ==========\n" RESET);
    while(attempts--) {
        if(!readLine(COLOR_INPUT "Enter Username: " RESET,user,sizeof user)) return 0;
        printf(COLOR_INPUT "Enter Password: " RESET); fflush(stdout);
        getPasswordMasked(pass,sizeof pass);
        if(strcmp(user,"admin")==0 && strcmp(pass,"12345")==0){printf(COLOR_SUCCESS "Login successful. Welcome, %s!\n" RESET,user);return 1;}
        printf(COLOR_ERROR "Invalid username or password. %d attempt(s) left.\n" RESET,attempts);
    }
    puts(COLOR_ERROR "Access denied. Account locked." RESET); return 0;
}
