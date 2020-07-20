#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "manage_schedule.h"

void manage_schedule(char *id) {

	show_schedule(id);

	return;

}

pSchedule read_schedule_file(const char* filename)
{
	FILE *fp;
	pSchedule head=NULL;
	pSchedule p,tail;
	unsigned int check=0;
	int schedule_count=0;

	fp=fopen(filename,"a+");
	if (fp==NULL)
	{
		printf("open failed!\n");
		exit(1);
	}

	p=(pSchedule)malloc(sizeof(struct Schedule_Point));
	memset(p,0,sizeof(struct Schedule_Point));
	check=fread(p,sizeof(Schedule),1,fp);
	if(!check)
	{
		return head;
	}

	while (check)
	{
		schedule_count++;
		if (schedule_count==1)
		{
			head=p;
			tail=p;
		}
		tail->next=p;
		tail=p;
		p=(pSchedule)malloc(sizeof(struct Schedule_Point));
		memset(p,0,sizeof(struct Schedule_Point));
		check=fread(p,sizeof(Schedule),1,fp);
	}
	tail->next=NULL;
	fclose(fp);

	return head;//返回的是文件的头指针
}

//保存：P为头结点的指针
void save_schedule_file(const char *filename,pSchedule p)
{
	FILE *fp;
	fp=fopen(filename,"w+");
	if(fp==NULL)
	{
		perror("Save failed!");
		exit(1);
	}
	while (p)
	{
		fwrite(p,sizeof(Schedule),1,fp);
		p=p->next;
	}
	fclose(fp);
}


void print_schedule_file(const char *filename)
{
	pSchedule head=read_schedule_file(filename);
	pSchedule p=head;
	while (p)
	{
		printf("%s\n",p->data.title);
		printf("time:%d/%d/%d ",p->data.time.tm_year,p->data.time.tm_mon,p->data.time.tm_mday);
		printf("%d:%d:%d\t",p->data.time.tm_hour,p->data.time.tm_min,p->data.time.tm_sec);
		printf("type:%d\tlevel:%d\n",p->data.type,p->data.level);
		printf("remark:%s\n\n",p->data.remark);
		p=p->next;
	}
	free_file(head);
}

void free_file(pSchedule head)
{
	pSchedule p;
	while(head)
	{
		p=head;
		head=head->next;
		free(p);
	}
}

void schedule_add(const char *filename)
{
	Schedule data;
	printf("Now you can create a schedule!\n");
	printf("Please input the title(less than 20 characters):\n");
	fflush(stdin);
	gets(data.title);
	printf("Please input the time(e.g year month day hour minute second):\n");
	fflush(stdin);
	scanf("%d%d%d%d%d%d",&data.time.tm_year,&data.time.tm_mon,&data.time.tm_mday,&data.time.tm_hour,&data.time.tm_min,&data.time.tm_sec);
	getchar();
	printf("Type: '1' work, '2' study, '3' travel, '4' recreation ,'5' others\n");
	fflush(stdin);
	printf("Please input the number of type:\n");
	fflush(stdin);
	scanf("%d",&data.type);
	getchar();
	printf("Please input the level( 1 to 5 ):\n");
	fflush(stdin);
	scanf("%d",&data.level);
	getchar();
	printf("Do you want to add some remarks about this schedule(0 or 1)?\n");
	fflush(stdin);
	int choice;
	scanf("%d",&choice);
	getchar();
	if (choice)
	{
		printf("Please input the remark(less than 50 words):\n");
		fflush(stdin);
		gets(data.remark);
	}
	else{
		strcpy(data.remark,"None");
	}
	data.symbol=1;
	insert_schedule(&data,filename);
}

void insert_schedule(Schedule *pdata,const char *filename)
{
	pSchedule head=read_schedule_file(filename);
	pSchedule p,p1=head;
	if(!p1)
	{
		head=(pSchedule)malloc(sizeof(struct Schedule_Point));
		memset(head,0,sizeof(struct Schedule_Point));
		head->data=*pdata;
		head->next=NULL;
	}
	else
	{
		while (p1->next) {
			p1 = p1->next;
		}
		p = (pSchedule) malloc(sizeof(struct Schedule_Point));
		memset(p, 0, sizeof(struct Schedule_Point));
		p->data = *pdata;
		p->next = p1->next;
		p1->next = p;
	}

	save_schedule_file(filename,head);
	free_file(head);
}

void schedule_delete(const char* filename)
{
	char title[21];
	printf("Now you can delete the schedule!\n");
	fflush(stdin);
	printf("Please input the title:\n");
	fflush(stdin);
	gets(title);

	remove_schedule(title,filename);

	printf("Delete done!\n");

}

void remove_schedule(char *title, const char *filename)
{
	pSchedule head=read_schedule_file(filename);
	pSchedule p,p1=head;
	if(!head)
	{
		printf("No data in the file!");
	}
	else if (!strcmp(p1->data.title,title))
	{
		p=p1;
		head=head->next;
		free(p);
	}else
	{
		while ((p1->next) && strcmp(p1->next->data.title, title) != 0) {
			p1 = p1->next;
		}
		if (p1->next) {
			p = p1->next;
			p1->next = p->next;
			free(p);
		} else {
			printf("No this schedule in the file!");
		}
	}
	save_schedule_file(filename,head);
	free_file(head);
}

void schedule_change(const char* filename)
{
	Schedule data;

	printf("Now you can change the schedule!\n");
	printf("Please input the title(less than 20 characters):\n");
	fflush(stdin);
	gets(data.title);
	printf("Please input the time(e.g year month day hour minute second):\n");
	fflush(stdin);
	scanf("%d%d%d%d%d%d",&data.time.tm_year,&data.time.tm_mon,&data.time.tm_mday,&data.time.tm_hour,&data.time.tm_min,&data.time.tm_sec);
	printf("Please input the type:\n");
	fflush(stdin);
	scanf("%d",&data.type);
	printf("Please input the level:");
	fflush(stdin);
	scanf("%d",&data.level);
	printf("Do you want to add some remarks about this schedule(0 or 1)?\n");
	fflush(stdin);
	int choice;
	scanf("%d",&choice);
	if (choice)
	{
		printf("Please input the remark(less than 50 words):\n");
		fflush(stdin);
		gets(data.remark);
	}
	data.symbol=1;
	update_schedule(filename,&data);
}

void update_schedule(const char *filename,Schedule *pdata)
{
	pSchedule head=read_schedule_file(filename);
	pSchedule p=head;
	if(!p)
	{
		printf("No data in the file!\n");
		return;
	}

	while (p && strcmp(p->data.title, pdata->title) != 0)
	{
		p=p->next;
	}
	if(p)
	{
		p->data=*pdata;
	} else{
		printf("No this schedule in the file!\n");
	}
	save_schedule_file(filename,head);
	free_file(head);
}

void schedule_lookup(const char *filename)
{
	pSchedule head=read_schedule_file(filename);
	pSchedule p=head;
	if (!p)
	{
		printf("No this schedule in the file!");
		return;
	}

	char title[21];
	printf("Now you can look up the schedule!\n");
	printf("Please input the title:\n");
	fflush(stdin);
	gets(title);

	while (p && strcmp(p->data.title,title) != 0)
	{
		p=p->next;
	}
	if (p)
	{
		printf("title: %s\n",p->data.title);
		printf("target time: %d/%d/%d ",p->data.time.tm_year,p->data.time.tm_mon,p->data.time.tm_mday);
		printf("%d:%d:%d\t",p->data.time.tm_hour,p->data.time.tm_min,p->data.time.tm_sec);
		printf("type: %d\tlevel: %d\n",p->data.type,p->data.level);
		printf("remark: %s\n",p->data.remark);
		return;
	} else{
		printf("No this schedule in the file!");
	}
	free_file(head);
}

void schedule_count(const char* filename)
{
	int unexpired_count=0,expired_count=0;
	int type_1=0,type_2=0,type_3=0,type_4=0,type_5=0;

	pSchedule head=read_schedule_file(filename);
	pSchedule p=head;
	while (p)
	{
		if (p->data.symbol==1)unexpired_count++;
		else expired_count++;

		switch (p->data.type) {
			case 1:
				type_1++;
				break;
			case 2:
				type_2++;
				break;
			case 3:
				type_3++;
				break;
			case 4:
				type_4++;
				break;
			case 5:
				type_5++;
				break;
			default:
				break;
		}

		p=p->next;
	}
	free_file(head);

	if (unexpired_count!=0||expired_count!=0)
	{
		printf("The number of unexpired schedule: %d\n", unexpired_count);
		printf("The number of expired schedule: %d\n\n", expired_count);
		printf("The number of working schedule: %d\n", type_1);
		printf("The number of studying schedule: %d\n", type_2);
		printf("The number of travelling schedule: %d\n", type_3);
		printf("The number of recreational schedule: %d\n", type_4);
		printf("The number of other schedule: %d\n", type_5);
	}
	else{
		printf("No schedule now.\n");
	}
}

void schedule_traverse(const char* filename)
{
	pSchedule head=read_schedule_file(filename);
	pSchedule p=head;

	time_t t;
	struct tm * lt;
	struct tm *target ;
	target=(struct tm*)malloc(sizeof(struct tm));
	time (&t);//获取Unix时间戳。
	lt = localtime (&t);//转为时间结构。
	lt->tm_year+=1900;
	lt->tm_mon+=1;


	while (p)
	{
		*target=p->data.time;
		p->data.rest=day_diff(lt->tm_year,lt->tm_mon,lt->tm_mday,target->tm_year,target->tm_hour,target->tm_mday
		);

		if (p->data.rest<0)p->data.symbol=0;
		p=p->next;
	}
	save_schedule_file(filename,head);
	free_file(head);
}

int day_diff(int year_start, int month_start, int day_start
		, int year_end, int month_end, int day_end)
{
	int y2, m2, d2;
	int y1, m1, d1;

	m1 = (month_start + 9) % 12;
	y1 = year_start - m1/10;
	d1 = 365*y1 + y1/4 - y1/100 + y1/400 + (m1*306 + 5)/10 + (day_start - 1);

	m2 = (month_end + 9) % 12;
	y2 = year_end - m2/10;
	d2 = 365*y2 + y2/4 - y2/100 + y2/400 + (m2*306 + 5)/10 + (day_end - 1);

	return (d2 - d1);
}

void schedule_remind(const char *filename)
{
	pSchedule head=read_schedule_file(filename);
	pSchedule p=head,p1,tmp;

	if (p==NULL)
	{
		printf("No schedule now.\n");
		return;
	}

	int count=0;

	//int len=linked_length(head);


	/*while (p->next!=NULL)
	{
		p1=p->next;
		while (p1!=NULL)
		{
			if(p->data.rest > p1->data.rest)
			{
				tmp=p;
				p=p1;
				p1=tmp;
				tmp->next=p->next;
				p->next=p1->next;
				p1->next=tmp->next;

			}

			p1=p1->next;
		}
		p=p->next;
	}*/

	//提醒
	pSchedule pt=head;

	printf("The schedule need to finish:\n");
	while (pt)
	{
		if (pt->data.rest>0)
		{
			count++;
			printf("%s: %d days\n",p->data.title,pt->data.rest);
		}

		if (count==3)break;
		pt=pt->next;
	}
	if (count==0)
	{
		printf("No unexpired schedule now.\n");
	}

	save_schedule_file(filename,head);
	free_file(head);
}

int linked_length(pSchedule head)
{
	pSchedule p = head;
	int len=0;
	while(p!=NULL){
		len++;
		p=p->next;
	}
	return len;
}

void show_schedule(char *ID)
{
	printf("用户%s已登录\n",ID);
	char path[] = "..\\information\\";
	strcat(path,ID);
	strcat(path,"\\schedule.txt");

//	printf("%s",path);

	schedule_traverse(path);

	int choice=0;
	while (1)
	{
		show_menu();
		scanf("%d", &choice);

		switch (choice) {
			case 1:
				schedule_add(path);
				break;
			case 2:
				schedule_delete(path);
				break;
			case 3:
				schedule_change(path);
				break;
			case 4:
				schedule_lookup(path);
				break;
			case 5:
				schedule_count(path);
				break;
			case 6:
				schedule_remind(path);
				break;
			case 7:
				print_schedule_file(path);
				break;
			case 0:
				return;
			default:
				break;
		}
	}

}

void show_menu()
{
	printf("\n");
	printf("★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n");
	printf("                     欢迎来到日程管理界面!\n");
	printf("                      请输入编号来选择对应的功能:\n");
	printf("                         1. 添加日程\n");
	printf("                         2. 删除日程\n");
	printf("                         3. 修改日程\n");
	printf("                         4. 查看日程\n");
	printf("                         5. 日程统计\n");
	printf("                         6. 最近日程\n");
	printf("                         7. 查看所有日程\n");
	printf("                         0. 返回主界面\n");
	printf("★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n");
	printf("\n");
}
