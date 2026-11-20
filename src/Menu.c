#include "../include/Menu.h"
#include "../include/Colors.h"
#include <stdio.h>
void printMenu(void) {
    puts(COLOR_HEADER "\n============================================================\n|                 HOTEL MANAGEMENT SYSTEM                 |\n============================================================" RESET);
    puts(COLOR_MENU "1 -> Add Customer\n2 -> Show Details\n3 -> Update Information\n4 -> Room Availability\n5 -> Delete Customer\n6 -> Generate Bill\n7 -> Exit" RESET);
    printf(COLOR_INPUT "Enter your choice: " RESET);
}
