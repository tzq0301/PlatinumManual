//
// Created by TZQ on 2020/7/20.
//

#include "manage_diary.h"
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

#define ESC 27        //退出键
/* 1************定义日记结构体*************************/
typedef struct Link1 {
	char date[10];          //日期    格式2009-12-30
	char title[40];         //标题
	char content[1000];     //日记内容
	char keyword[20];       //关键字，可用空格隔开
	int tag;             //用来标记该日记是否满足查阅要求，是为0，否为-1，初始值为0；
	struct Link1 *nextd;
} Diary;
typedef struct Link2 {
	char id[20];
	Diary *diarys_list;       //该用户拥有的日记链表
	struct Link2 *nextu;
} User;

/* 开始对于下面函数的声明 */
User *Init_User(User *U1);    //定义一个空的用户结构体

Diary *Init_Diary(Diary *D1);  //定义一个空的日记结构体

int Open_Users_info(User *U1);       //导入账号信息

int Delete_Diary(Diary *D);    //删除日记

int Open_Diary(Diary *D1);       //打开日记

int Save_Diary(Diary *D1);      //保存日记

User *User_check(char *id, User *U1);      //检查这个id对应的账号是否出现过,返回id对应的User链结构点

int Input_Choose();       //此函数用来判断是否输入的是正整数，结果将返回该正整数

Diary *Open_DiaryFile(Diary *D1, char FileName[30]);       //打开一个文件目录并且将里面的人日记文件读取到一个diary结构体当中

int Printf_DiaryList(Diary *D1);        //给日记结构体链表的头位置，把所有日记展示出来

void Print_Menu2(int *choose2);     //进入日记菜单

void Print_Menu3(int *choose3);      //进入日记查阅菜单并选择操作

int Search_Diary(Diary *D1);         //查阅日记总的

Diary *Search_order(Diary *D1);     //按顺序查阅日记

Diary *Filter_word(Diary *D1, char cmpword[], int n);      //按标题，日期，关键字查询数据

int Write_Diary(Diary *D1);         //新写日记并决定是否以文件格式保存

int Save_Users_info(User *U1);       //保存用户信息

void Initial_Tag(Diary *D1, int tag);        //将标记值初始化

int Diary_Operation(User *U2, Diary *D1, User *U1);        //对日记的操作分离出

User *Create_User(char *id, User *U1);

User *Find_User(User *U1, char *id);

int Open_Users_info(User *U1) {
	FILE *fp;
	User *U2 = NULL;
	Diary *D1 = NULL, *D2 = NULL;
	char filepn[80], tempstr[80];/*用来存放文件保存路径以及文件名*/
	strcpy(filepn, "..\\information\\User_info.txt");
	if ((fp = fopen(filepn, "r")) == NULL) {
		printf("不能打开文件!\n");
		return 0;
	} else {
		fscanf(fp, "%s\n", tempstr);
		while (strcmp(tempstr, "User:") == 0 && (!feof(fp))) {
			U2 = (User *) malloc(sizeof(User));
			if (U2 == NULL) {
				printf("\t用户空间申请失败！\n");
				return 0;
			} else {
				fscanf(fp, "用户id:%s\n", U2->id);
				fscanf(fp, "%80s", tempstr);
				D1 = (Diary *) malloc(sizeof(Diary));
				D1 = Init_Diary(D1);
				U2->diarys_list = D1;
				while (strcmp(tempstr, "Diary:") == 0 && (!feof(fp))) {
					D2 = (Diary *) malloc(sizeof(Diary));
					D2 = Init_Diary(D2);
					if (D2 == NULL) {
						printf("\t日记空间申请失败！\n");
						return 0;
					} else {
						fscanf(fp, "\t日期: %s\n", D2->date);
						fscanf(fp, "\t关键字: %s\n", D2->keyword);
						fscanf(fp, "\t标题: %s\n", D2->title);
						fscanf(fp, "\t日记内容: \n%s\n\n", D2->content);
						fscanf(fp, "%s\n", tempstr);
						D2->tag = 0;
						D2->nextd = D1->nextd;
						D1->nextd = D2;
					}
				}
				U2->nextu = U1->nextu;
				U1->nextu = U2;
			}
			fscanf(fp, "\n\n");
		}

	}
	fclose(fp);
	return 0;
}

void Print_Menu2(int *choose2) {
	printf("\n\t\t\t          “日记操作”                \n");
	printf("\t|^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^|\n");
	printf("\t|  0.退出    1.写日记     2.导入日记    3.日记列表     4.查阅与删除     5.保存账号信息   |\n");
	printf("\t|^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^|\n");
	do {
		printf("\n\t请选择操作:\t");
		*choose2 = Input_Choose();
	} while (*choose2 < 0 || *choose2 > 5);
	rewind(stdin);         /*清空键盘缓冲区里的无用字符*/
}

void Print_Menu3(int *choose3) {
	printf("\n\t\t                     “日记查阅与删除”－－－－－－－－－(ESC返回上级)\n");
	printf("\t|^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^|\n");
	printf("\t|  0.退出   1.日记列表  2.按顺序查阅   3.按标题查阅  4.按日期查阅    5.按关键字查阅       |\n");
	printf("\t|^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^|\n");
	do {
		printf("\n\t请选择操作:\t");
		*choose3 = Input_Choose();
	} while (*choose3 < 0 || *choose3 > 5);
	rewind(stdin);         /*清空键盘缓冲区里的无用字符*/
}

User *User_check(char *id, User *U1) {
	User *tempu = NULL;
	tempu = Init_User(tempu);
	tempu = Find_User(U1, id);
	if (tempu == NULL)
		return Create_User(id, U1);
	else
		return tempu;
}

int Diary_Operation(User *U2, Diary *D1, User *U1) {
	char tempch = '1';
	int choose2;
	char FileName[40];
	Diary *p = NULL;
	U1->nextu = U2;
	D1 = U2->diarys_list;
	while (tempch != ESC) {
		system("cls");
		printf("\n\t\t\t欢迎用户---id为“%s”的到来!......\n\n", U2->id);
		Print_Menu2(&choose2);
		switch (choose2) {
			case 0:
				return 0;
			case 1: {
				Write_Diary(D1);
				tempch = getch();
			}
				break;
			case 2: {
				printf("\n\t参考文件:  听雨的思索.txt");
				printf("\n\t请输入文件路径及文件名:");
				scanf("%s", FileName);
				p = Open_DiaryFile(D1, FileName);
				if (p != NULL)
					Open_Diary(p);
				tempch = getch();
			};
				break;
			case 3: {
				printf("\n\n\t该用户有以下日记:\n\n");
				Printf_DiaryList(D1);
				tempch = getch();
			}
				break;
			case 4: {
				if (Search_Diary(D1) == 1)
					tempch = getch();
			}
				break;    //打开帮助文件
			case 5: {
				Save_Users_info(U1);
			}
				break;
		}
	}
	return 1;
}

int Write_Diary(Diary *D1) {
	int temp;
	Diary *p = NULL;
	p = Init_Diary(p);
	p = (Diary *) malloc(sizeof(Diary));
	printf("\n\n\t请输入日期(2008-12-31):\t");
	scanf("%s", &p->date);
	printf("\n\t请输入标题:\t");
	scanf("%s", &p->title);
	printf("\n\t请开始写日记:......\n\n\t");
	scanf("%s", &p->content);
	printf("\n\t请为该日记写关键字:\t");
	scanf("%s", &p->keyword);
	p->tag = 0;
	p->nextd = D1->nextd;
	D1->nextd = p;
	printf("\n\t--------------------------------------------------\n");
	printf("\t是否要以文件方式保存日记?\t1-是  0--否\t");
	printf("\n\t--------------------------------------------------\n\t");
	temp = Input_Choose();
	if (temp == 1)
		Save_Diary(p);
	return 1;
}

User *Init_User(User *U1) {
	U1 = (User *) malloc(sizeof(User));
	if (U1 != NULL) {
		U1->nextu = NULL;
		return U1;
	} else
		return NULL;
}

Diary *Init_Diary(Diary *D1) {
	D1 = (Diary *) malloc(sizeof(Diary));
	if (D1 != NULL) {
		D1->nextd = NULL;
		return D1;
	} else
		return NULL;
}

int Input_Choose()       //此函数用来判断是否输入的是正整数，结果将返回该正整数
{
	char str1[50];
	long n, i = 0;
	str1[0] = getch();
	printf("%c", str1[0]);
	if (str1[0] == ESC) {
		rewind(stdin);
		return 0;
	}
	getch();
	if (str1[0] > '0' || str1[0] < '9') {
		rewind(stdin);
		return (str1[0] - 48);
	}
	n = atoi(str1);          //利用atoi函数将字符串str转换成整型数
	return n;        //返回输入的正整数
}

Diary *Open_DiaryFile(Diary *D1, char FileName[]) {
	FILE *fp;
	Diary *p = NULL;
	if ((fp = fopen(FileName, "r")) == NULL) {
		printf("\t文件打开失败！");
		return NULL;
	} else {
		p = (Diary *) malloc(sizeof(Diary));
		if (p == NULL) {
			printf("\t日记创建失败！");
			return NULL;
		}
		fscanf(fp, "\t日期: %s\n", p->date);
		fscanf(fp, "\t标题: %s\n", p->title);
		fscanf(fp, "\t关键字: %s\n", p->keyword);
		fscanf(fp, "\t正文如下:\n\t%s\n", p->content);
		p->tag = 0;
		p->nextd = D1->nextd;
		D1->nextd = p;
		fclose(fp);
		return p;
	}
}

int Open_Diary(Diary *D1) {
	printf("\n\t--------------------------------------------------\n");
	printf("\n\t日记日期==>%s", D1->date);
	printf("\n\t日记标题==>%s", D1->title);
	printf("\n\n\t关键字==>%s", D1->keyword);
	printf("\n\t--------------------------------------------------\n");
	printf("\n\n\t日记正文如下:\n");
	printf("\n\t%s", D1->content);
	return 1;
}

int Printf_DiaryList(Diary *D1) {
	int count = 0;
	Diary *D;
	D = D1;
	printf("\n");
	if (D->nextd == NULL)
		printf("\t没有日记信息！.....\n");
	else {
		while (D->nextd != NULL) {
			D = D->nextd;
			if (D->tag == 0) {
				count++;
				printf("\t第%2d篇==>时间:%-10s   日记标题:%-20s  \t关键字:%-s\n", count, D->date, D->title, D->keyword);
			}
		}
	}
	return count;
}

int Search_Diary(Diary *D1) {
	char tempch = '1';
	char cmpword[20];
	int choose3;
	Diary *p;
	while (tempch != ESC) {
		system("cls");
		Print_Menu3(&choose3);
		p = D1;
		if (p->nextd == NULL)
			printf("\n\t没有日记......\n");
		else {
			switch (choose3) {
				case 0:
					return 0;
				case 1: {
					printf("\n\t该用户有以下日记:\n\n");
					Printf_DiaryList(D1);
				}
					break;
				case 2:
					Search_order(D1);
					break;
				case 3: {
					printf("\n\t参考标题:  我不再爱你了");
					printf("\n\t请输入要查阅的日记标题:\t");
					scanf("%s", cmpword);
					Filter_word(D1, cmpword, 1);
				}
					break;     //按标题查阅
				case 4: {
					printf("\n\t请输入要查阅的日记日期(2009-4-11):\t");
					scanf("%s", cmpword);
					Filter_word(D1, cmpword, 2);
				}
					break;     //按日期查阅
				case 5: {
					printf("\n\t请输入要查阅的关键字(如:想你):\t");
					scanf("%s", cmpword);
					Filter_word(D1, cmpword, 3);
				}
					break;     //按关键字查阅
			}

		}
		Initial_Tag(D1, 0);
		tempch = getch();
		rewind(stdin);                    /*清空键盘缓冲区里的无用字符*/
	}
	return 1;
}

int Save_Diary(Diary *D1) {
	FILE *fp;
	char FileName[40], postfix[6] = ".txt\0";
	printf("\t请输入文件路径及文件名:");
	scanf("%s", FileName);
	if ((fp = fopen(FileName, "w+")) == NULL) {
		printf("\t打开文件失败！");
		return 0;
	}
	fprintf(fp, "\t日期: %s\n", D1->date);
	fprintf(fp, "\t标题: %s\n", D1->title);
	fprintf(fp, "\t关键字: %s\n", D1->keyword);
	fprintf(fp, "\t正文如下:\n\t%s\n", D1->content);
	fclose(fp);
	printf("\t日记文件保存成功！");
	return 1;
}

Diary *Search_order(Diary *D1) {
	int choose, count, count1 = 0;
	int temp;
	Diary *D;
	D = D1;
	count = Printf_DiaryList(D);
	if (count > 0) {
		do {
			printf("\n\t您要查阅的是第几篇(<=%d):\t", count);
			choose = Input_Choose();
		} while (choose < 1 || choose > count);

		while (D->nextd != NULL) {
			if (D->nextd->tag == 0) {
				if (count1 == choose - 1) {
					Open_Diary(D->nextd);
					printf("\n\n\t--------------------------------------------------\n");
					printf("\t是否要删除此篇日记?\t1-是  0--否\t");
					printf("\n\t--------------------------------------------------\n\t");
					printf("\t请选择操作:\t");
					temp = Input_Choose();
					if (temp == 1)
						Delete_Diary(D);        //删除P的下一个结点
					return D;
				}
				count1++;
			}
			D = D->nextd;
		}
	} else if (count == 0)
		printf("\n\t没有符合查阅要求的日记.....");
	return D;
}

int Delete_Diary(Diary *D) {
	Diary *p;
	p = D->nextd;
	D->nextd = p->nextd;
	free(p);
	printf("\n\t日记删除成功......");
	return 1;
}

Diary *Filter_word(Diary *D1, char cmpword[], int n)    //采用的是筛选算法
{
	char *temp = NULL;
	Diary *D, *D2;
	Initial_Tag(D1, 0);
	D = D1;
	while (D->nextd != NULL) {
		if (n == 1)
			temp = strstr(D->nextd->title, cmpword);
		else if (n == 2)
			temp = strstr(D->nextd->date, cmpword);
		else if (n == 3)
			temp = strstr(D->nextd->keyword, cmpword);
		if (temp == NULL)
			D->nextd->tag = -1;
		D = D->nextd;
	}
	printf("\n\n\t有以下的日记符合查阅要求:\n");
	D2 = Search_order(D1);
	Initial_Tag(D1, 0);
	return D1;
}

void Initial_Tag(Diary *D1, int tag) {
	Diary *q;
	q = D1->nextd;
	while (q != NULL) {
		q->tag = tag;
		q = q->nextd;
	}
}

int Save_Users_info(User *U1) {
	FILE *fp;
	Diary *D1;
	int temp;
	char filepn[80];/*用来存放文件保存路径以及文件名*/
	printf("\n\n\t--------------------------------------------------\n");
	printf("\t是否保存本次使用所做的所有操作?...\t1-是  0--否\t");
	printf("\n\t--------------------------------------------------\n\t");
	printf("请选择操作:\t");
	temp = Input_Choose();
	if (temp == 1) {
		strcpy(filepn, "..\\information\\User_info.txt");
		if ((fp = fopen(filepn, "w+")) == NULL) {
			printf("不能打开文件!\n");
			return 0;
		}
		while (U1->nextu != NULL) {
			fprintf(fp, "User:\n");
			U1 = U1->nextu;/*下移一个结点*/
			fprintf(fp, "用户id:%s\n", U1->id);
			D1 = U1->diarys_list;
			while (D1->nextd != NULL) {
				D1 = D1->nextd;
				fprintf(fp, "Diary:\n");
				fprintf(fp, "\t日期:%s\n\t关键字: %s\n", D1->date, D1->keyword);
				fprintf(fp, "\t标题:%s\n", D1->title);
				fprintf(fp, "\t日记内容:\n%s\n", D1->content);
			}
		}
		fclose(fp);
	}
	return 0;
}

User *Create_User(char *id, User *U1) {
	int flag = 0;
	User *s, *temp;
	Diary *D2 = NULL;
	D2 = Init_Diary(D2);
	s = (User *) malloc(sizeof(User));
	if (s == NULL) {
		printf("\t用户创建失败！");
		return NULL;
	}

	s->diarys_list = D2;
	s->nextu = U1->nextu;
	U1->nextu = s;
	for (int i = 0; i < 20; i++) {
		s->id[i] = id[i];
	}
	flag = 0;
	printf("\n\t用户创建成功!......\n");
	return s;
}

User *Find_User(User *U1, char *id) {
	User *q;
	q = U1->nextu;
	while (q != NULL && strcmp(q->id, id) != 0)
		q = q->nextu;
	if (q != NULL)
		return q;
	else
		return NULL;
}

void manage_diary(char *id) {

	User *U1 = NULL;
	Diary *D1 = NULL;
	U1 = Init_User(U1);
	D1 = Init_Diary(D1);
	Open_Users_info(U1);
	User *U2 = User_check(id, U1);
	Diary_Operation(U2, D1, U1);

	return;
}

