#ifndef CUSTOMER_H
#define CUSTOMER_H
#define MAX_LIMIT 15
#define NAME_LEN 50
#define PHONE_LEN 16
#define ID_LEN 20
#define CNIC_LEN 14
#define DATE_LEN 11
#define TYPE_LEN 10
#define BOOKING_LEN 15
#define PURPOSE_LEN 30

typedef struct {
    char name[NAME_LEN];
    char phone_number[PHONE_LEN];
    char idproof[ID_LEN];
    char CNICno[CNIC_LEN];
    char check_in_date[DATE_LEN];
    char check_out_date[DATE_LEN];
    char room_type[TYPE_LEN];
    int roomno;
    int days;
    char booking_type[BOOKING_LEN];
    char purpose_of_visit[PURPOSE_LEN];
} Customer;
extern Customer customers[MAX_LIMIT];
extern int count;
void addCustomer(void);
void showDetails(void);
void updateCustomer(void);
void checkAvailability(void);
void deleteCustomer(void);
void generateBill(void);
#endif
