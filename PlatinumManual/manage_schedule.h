#ifndef PLATINUMMANUAL_MANAGE_SCHEDULE_H
#define PLATINUMMANUAL_MANAGE_SCHEDULE_H

#include <time.h>

void manage_schedule(char *id);


typedef struct user_schedule{
	struct tm time;
	int type;
	char title[21];
	int level;
	char remark[55];
	int symbol;
	int rest;
}Schedule;

typedef struct Schedule_Point{
	Schedule data;
	struct Schedule_Point *next;
}*pSchedule;

pSchedule read_schedule_file(const char*);
void save_schedule_file(const char*,pSchedule);
void print_schedule_file(const char*);
void free_file(pSchedule);

void schedule_add(const char*);//�� insert done
void insert_schedule(Schedule*,const char *);

void schedule_delete(const char*);//ɾ delete  done
void remove_schedule(char *, const char *);

void schedule_change(const char*);//��  done
void update_schedule(const char*,Schedule *);

void schedule_lookup(const char*);//��  done

void schedule_count(const char*);//ͳ��  done

void schedule_traverse(const char*);//���� + check   done
int day_diff(int, int, int, int, int ,int );

void schedule_remind(const char*);//���� + ����   done
int linked_length(pSchedule);

void show_schedule(char*);//����չʾ

void show_menu();

#endif //PLATINUMMANUAL_MANAGE_SCHEDULE_H
