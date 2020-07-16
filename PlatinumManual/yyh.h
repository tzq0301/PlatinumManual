#ifndef PLATINUMMANUAL_YYH_H
#define PLATINUMMANUAL_YYH_H

struct user {
	long long int id;
	char password[16];
	char user_name[20];
	char birthday[15];
	char introduce[100];
};

int sign_up();
int log_in();
void update_password();
void show_information();
void delete_information();



#endif //PLATINUMMANUAL_YYH_H
