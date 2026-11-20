#include "../include/FileHandler.h"
#include "../include/Customer.h"
#include "../include/Colors.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef _WIN32
#include <direct.h>
#define MAKE_DIR(p) _mkdir(p)
#else
#include <sys/stat.h>
#define MAKE_DIR(p) mkdir(p,0777)
#endif
#define DB_PATH "database/customers.csv"
void saveToFile(void) {
    MAKE_DIR("database");
    FILE *f=fopen(DB_PATH,"w");
    if(!f){perror("Could not save database");return;}
    for(int i=0;i<count;i++) {
        Customer *c=&customers[i];
        if(fprintf(f,"%s,%s,%s,%s,%s,%s,%s,%d,%d,%s,%s\n",c->name,c->phone_number,c->idproof,c->CNICno,c->check_in_date,c->check_out_date,c->room_type,c->roomno,c->days,c->booking_type,c->purpose_of_visit)<0){puts(COLOR_ERROR "Error writing database." RESET);fclose(f);return;}
    }
    if(fclose(f)==0) puts(COLOR_SUCCESS "Data saved successfully." RESET);
}
void loadFromFile(void) {
    FILE *f=fopen(DB_PATH,"r"); if(!f)return;
    count=0; char line[512];
    while(count<MAX_LIMIT && fgets(line,sizeof line,f)) {
        Customer c={0}; int used=0;
        int fields=sscanf(line,"%49[^,],%15[^,],%19[^,],%13[^,],%10[^,],%10[^,],%9[^,],%d,%d,%14[^,],%29[^\r\n]%n",c.name,c.phone_number,c.idproof,c.CNICno,c.check_in_date,c.check_out_date,c.room_type,&c.roomno,&c.days,c.booking_type,c.purpose_of_visit,&used);
        if(fields==11 && c.roomno>=1 && c.roomno<=MAX_LIMIT && c.days>0) {
            int duplicate=0; for(int j=0;j<count;j++) if(customers[j].roomno==c.roomno) duplicate=1;
            if(!duplicate) customers[count++]=c;
        }
    }
    fclose(f);
}
