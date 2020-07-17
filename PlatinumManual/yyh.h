#ifndef PLATINUMMANUAL_YYH_H
#define PLATINUMMANUAL_YYH_H

struct user {
	char id[20];
	char password[16];
	char user_name[20];
	char birthday[15];
	char introduce[100];
};

char *sign_up();
char *log_in();
void update_password();
void show_information();
void delete_information();



#endif //PLATINUMMANUAL_YYH_H
