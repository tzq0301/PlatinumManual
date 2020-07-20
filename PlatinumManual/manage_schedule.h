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

void schedule_add(const char*);//增 insert done
void insert_schedule(Schedule*,const char *);

void schedule_delete(const char*);//删 delete  done
void remove_schedule(char *, const char *);

void schedule_change(const char*);//改  done
void update_schedule(const char*,Schedule *);

void schedule_lookup(const char*);//查  done

void schedule_count(const char*);//统计  done

void schedule_traverse(const char*);//遍历 + check   done
int day_diff(int, int, int, int, int ,int );

void schedule_remind(const char*);//提醒 + 排序   done
int linked_length(pSchedule);

void show_schedule(char*);//界面展示

void show_menu();

#endif //PLATINUMMANUAL_MANAGE_SCHEDULE_H
