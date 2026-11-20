#include <stdio.h>
#include "include/Colors.h"
#include "include/Auth.h"
#include "include/Customer.h"
#include "include/FileHandler.h"
#include "include/Menu.h"
#include "include/Input.h"
int main(void) {
    loadFromFile();
    if(!login()) return 0;
    for(;;) {
        int choice; printMenu();
        if(!readInt("",&choice)){puts(COLOR_ERROR "Please enter a number from 1 to 7." RESET);continue;}
        switch(choice){case 1:addCustomer();break;case 2:showDetails();break;case 3:updateCustomer();break;case 4:checkAvailability();break;case 5:deleteCustomer();break;case 6:generateBill();break;case 7:puts(COLOR_SUCCESS "Goodbye!" RESET);return 0;default:puts(COLOR_ERROR "Invalid choice." RESET);}
    }
}
