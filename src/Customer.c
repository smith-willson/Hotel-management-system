#include "../include/Customer.h"
#include "../include/Colors.h"
#include "../include/FileHandler.h"
#include "../include/Input.h"
#include "../include/Date.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
Customer customers[MAX_LIMIT]; int count=0;
static int roomAssigned(int room,int except) { for(int i=0;i<count;i++) if(i!=except && customers[i].roomno==room)return 1; return 0; }
static int getText(const char *label,char *out,size_t cap) {
    if(!readLine(label,out,cap))return 0;
    if(out[0]=='\0' || strchr(out,',')){puts(COLOR_ERROR "Input cannot be empty or contain commas." RESET);return 0;} return 1;
}
static int getValidDateRange(char *in,char *out,int *days) {
    for(int tries=0;tries<3;tries++) {
        if(!getText("Check-in date (dd-mm-yyyy): ",in,DATE_LEN)||!getText("Check-out date (dd-mm-yyyy): ",out,DATE_LEN))return 0;
        if(calculateStayDays(in,out,days))return 1;
        puts(COLOR_ERROR "Invalid dates. Use valid dd-mm-yyyy dates; check-out must be after check-in." RESET);
    } return 0;
}
static int firstFreeRoom(void){for(int r=1;r<=MAX_LIMIT;r++)if(!roomAssigned(r,-1))return r;return 0;}
void addCustomer(void) {
    if(count>=MAX_LIMIT){puts(COLOR_ERROR "Maximum capacity reached." RESET);return;}
    Customer c={0}; int choice;
    if(!getText("Customer name: ",c.name,sizeof c.name)||!getText("Phone number: ",c.phone_number,sizeof c.phone_number)||!getText("ID proof: ",c.idproof,sizeof c.idproof)||!getText("CNIC (without hyphens): ",c.CNICno,sizeof c.CNICno))return;
    if(!getValidDateRange(c.check_in_date,c.check_out_date,&c.days))return;
    puts("Room type: 1. Single  2. Double"); if(!readInt("Select room type: ",&choice)||(choice!=1&&choice!=2)){puts(COLOR_ERROR "Invalid room type." RESET);return;}
    strcpy(c.room_type,choice==1?"Single":"Double");
    if(!getText("Booking type (Walk-in/Online): ",c.booking_type,sizeof c.booking_type))return;
    if(strcmp(c.booking_type,"Walk-in")&&strcmp(c.booking_type,"Online")){puts(COLOR_ERROR "Choose Walk-in or Online." RESET);return;}
    if(!getText("Purpose of visit: ",c.purpose_of_visit,sizeof c.purpose_of_visit))return;
    c.roomno=firstFreeRoom(); if(!c.roomno){puts(COLOR_ERROR "No rooms available." RESET);return;}
    customers[count++]=c; printf(COLOR_SUCCESS "Room %d assigned. Stay: %d night(s).\n" RESET,c.roomno,c.days); saveToFile();
}
static int findByRoom(int room){for(int i=0;i<count;i++)if(customers[i].roomno==room)return i;return -1;}
void showDetails(void) {
    int room;if(!count){puts(COLOR_WARNING "No customer records." RESET);return;}
    if(!readInt("Enter room number: ",&room)){puts(COLOR_ERROR "Invalid room number." RESET);return;}
    int i=findByRoom(room);if(i<0){puts(COLOR_ERROR "No booking found for that room." RESET);return;}
    Customer *c=&customers[i];
    puts(COLOR_HEADER "\n--- CUSTOMER DETAILS ---" RESET);
    printf("Name: %s\nPhone: %s\nID proof: %s\nCNIC: %s\nRoom: %d (%s)\nCheck-in: %s\nCheck-out: %s\nNights: %d\nBooking: %s\nPurpose: %s\n",c->name,c->phone_number,c->idproof,c->CNICno,c->roomno,c->room_type,c->check_in_date,c->check_out_date,c->days,c->booking_type,c->purpose_of_visit);
}
void updateCustomer(void) {
    int room,opt;if(!count){puts(COLOR_WARNING "No customer records." RESET);return;}
    if(!readInt("Enter room number to update: ",&room)){puts(COLOR_ERROR "Invalid room number." RESET);return;}
    int i=findByRoom(room);if(i<0){puts(COLOR_ERROR "Room not found." RESET);return;}
    puts("1. Name\n2. Phone\n3. Check-out date\n4. Room number");if(!readInt("Select field: ",&opt)){puts(COLOR_ERROR "Invalid choice." RESET);return;}
    Customer *c=&customers[i]; char temp[DATE_LEN]; int days;
    switch(opt){
      case 1: if(!getText("New name: ",c->name,sizeof c->name))return;break;
      case 2: if(!getText("New phone: ",c->phone_number,sizeof c->phone_number))return;break;
      case 3: if(!getText("New check-out date (dd-mm-yyyy): ",temp,sizeof temp))return; if(!calculateStayDays(c->check_in_date,temp,&days)){puts(COLOR_ERROR "Invalid check-out date." RESET);return;} strcpy(c->check_out_date,temp);c->days=days;break;
      case 4: {int nr;if(!readInt("New room number (1-15): ",&nr)||nr<1||nr>MAX_LIMIT||roomAssigned(nr,i)){puts(COLOR_ERROR "Room number invalid or already assigned." RESET);return;}c->roomno=nr;break;}
      default: puts(COLOR_ERROR "Invalid choice." RESET);return;
    }
    puts(COLOR_SUCCESS "Customer updated." RESET);saveToFile();
}
void checkAvailability(void){puts(COLOR_HEADER "\n===== ROOM AVAILABILITY =====" RESET);for(int r=1;r<=MAX_LIMIT;r++)printf("Room %2d -> %s\n",r,roomAssigned(r,-1)?COLOR_ERROR "BOOKED" RESET:COLOR_SUCCESS "AVAILABLE" RESET);}
void deleteCustomer(void){int room;if(!count){puts(COLOR_WARNING "No customer records." RESET);return;}if(!readInt("Enter room number to delete: ",&room)){puts(COLOR_ERROR "Invalid room number." RESET);return;}int i=findByRoom(room);if(i<0){puts(COLOR_ERROR "Room not found." RESET);return;}for(int j=i;j<count-1;j++)customers[j]=customers[j+1];count--;puts(COLOR_SUCCESS "Customer deleted." RESET);saveToFile();}
void generateBill(void){int room;if(!count){puts(COLOR_WARNING "No customer records." RESET);return;}if(!readInt("Enter room number: ",&room)){puts(COLOR_ERROR "Invalid room number." RESET);return;}int i=findByRoom(room);if(i<0){puts(COLOR_ERROR "No booking found." RESET);return;}Customer *c=&customers[i];double rent=strcmp(c->room_type,"Single")==0?10000.0:20000.0;double service=strcmp(c->room_type,"Single")==0?1200.0:2000.0;double total=rent*c->days+service;puts(COLOR_HEADER "\n========== BILL ==========" RESET);printf("Customer: %s\nRoom: %d (%s)\nStay: %d night(s)\nRoom rent: %.2f x %d = %.2f PKR\nService charges: %.2f PKR\n" COLOR_SUCCESS "TOTAL: %.2f PKR\n" RESET,c->name,c->roomno,c->room_type,c->days,rent,c->days,rent*c->days,service,total);}
