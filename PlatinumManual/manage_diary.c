//
// Created by TZQ on 2020/7/20.
//

#include "manage_diary.h"
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

#define ESC 27        //�˳���
/* 1************�����ռǽṹ��*************************/
typedef struct Link1 {
	char date[10];          //����    ��ʽ2009-12-30
	char title[40];         //����
	char content[1000];     //�ռ�����
	char keyword[20];       //�ؼ��֣����ÿո����
	int tag;             //������Ǹ��ռ��Ƿ��������Ҫ����Ϊ0����Ϊ-1����ʼֵΪ0��
	struct Link1 *nextd;
} Diary;
typedef struct Link2 {
	char id[20];
	Diary *diarys_list;       //���û�ӵ�е��ռ�����
	struct Link2 *nextu;
} User;

/* ��ʼ�������溯�������� */
User *Init_User(User *U1);    //����һ���յ��û��ṹ��

Diary *Init_Diary(Diary *D1);  //����һ���յ��ռǽṹ��

int Open_Users_info(User *U1);       //�����˺���Ϣ

int Delete_Diary(Diary *D);    //ɾ���ռ�

int Open_Diary(Diary *D1);       //���ռ�

int Save_Diary(Diary *D1);      //�����ռ�

User *User_check(char *id, User *U1);      //������id��Ӧ���˺��Ƿ���ֹ�,����id��Ӧ��User���ṹ��

int Input_Choose();       //�˺��������ж��Ƿ������������������������ظ�������

Diary *Open_DiaryFile(Diary *D1, char FileName[30]);       //��һ���ļ�Ŀ¼���ҽ���������ռ��ļ���ȡ��һ��diary�ṹ�嵱��

int Printf_DiaryList(Diary *D1);        //���ռǽṹ�������ͷλ�ã��������ռ�չʾ����

void Print_Menu2(int *choose2);     //�����ռǲ˵�

void Print_Menu3(int *choose3);      //�����ռǲ��Ĳ˵���ѡ�����

int Search_Diary(Diary *D1);         //�����ռ��ܵ�

Diary *Search_order(Diary *D1);     //��˳������ռ�

Diary *Filter_word(Diary *D1, char cmpword[], int n);      //�����⣬���ڣ��ؼ��ֲ�ѯ����

int Write_Diary(Diary *D1);         //��д�ռǲ������Ƿ����ļ���ʽ����

int Save_Users_info(User *U1);       //�����û���Ϣ

void Initial_Tag(Diary *D1, int tag);        //�����ֵ��ʼ��

int Diary_Operation(User *U2, Diary *D1, User *U1);        //���ռǵĲ��������

User *Create_User(char *id, User *U1);

User *Find_User(User *U1, char *id);

int Open_Users_info(User *U1) {
	FILE *fp;
	User *U2 = NULL;
	Diary *D1 = NULL, *D2 = NULL;
	char filepn[80], tempstr[80];/*��������ļ�����·���Լ��ļ���*/
	strcpy(filepn, "..\\information\\User_info.txt");
	if ((fp = fopen(filepn, "r")) == NULL) {
		printf("���ܴ��ļ�!\n");
		return 0;
	} else {
		fscanf(fp, "%s\n", tempstr);
		while (strcmp(tempstr, "User:") == 0 && (!feof(fp))) {
			U2 = (User *) malloc(sizeof(User));
			if (U2 == NULL) {
				printf("\t�û��ռ�����ʧ�ܣ�\n");
				return 0;
			} else {
				fscanf(fp, "�û�id:%s\n", U2->id);
				fscanf(fp, "%80s", tempstr);
				D1 = (Diary *) malloc(sizeof(Diary));
				D1 = Init_Diary(D1);
				U2->diarys_list = D1;
				while (strcmp(tempstr, "Diary:") == 0 && (!feof(fp))) {
					D2 = (Diary *) malloc(sizeof(Diary));
					D2 = Init_Diary(D2);
					if (D2 == NULL) {
						printf("\t�ռǿռ�����ʧ�ܣ�\n");
						return 0;
					} else {
						fscanf(fp, "\t����: %s\n", D2->date);
						fscanf(fp, "\t�ؼ���: %s\n", D2->keyword);
						fscanf(fp, "\t����: %s\n", D2->title);
						fscanf(fp, "\t�ռ�����: \n%s\n\n", D2->content);
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
	printf("\n\t\t\t          ���ռǲ�����                \n");
	printf("\t|^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^|\n");
	printf("\t|  0.�˳�    1.д�ռ�     2.�����ռ�    3.�ռ��б�     4.������ɾ��     5.�����˺���Ϣ   |\n");
	printf("\t|^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^|\n");
	do {
		printf("\n\t��ѡ�����:\t");
		*choose2 = Input_Choose();
	} while (*choose2 < 0 || *choose2 > 5);
	rewind(stdin);         /*��ռ��̻�������������ַ�*/
}

void Print_Menu3(int *choose3) {
	printf("\n\t\t                     ���ռǲ�����ɾ����������������������(ESC�����ϼ�)\n");
	printf("\t|^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^|\n");
	printf("\t|  0.�˳�   1.�ռ��б�  2.��˳�����   3.���������  4.�����ڲ���    5.���ؼ��ֲ���       |\n");
	printf("\t|^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^|\n");
	do {
		printf("\n\t��ѡ�����:\t");
		*choose3 = Input_Choose();
	} while (*choose3 < 0 || *choose3 > 5);
	rewind(stdin);         /*��ռ��̻�������������ַ�*/
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
		printf("\n\t\t\t��ӭ�û�---idΪ��%s���ĵ���!......\n\n", U2->id);
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
				printf("\n\t�ο��ļ�:  �����˼��.txt");
				printf("\n\t�������ļ�·�����ļ���:");
				scanf("%s", FileName);
				p = Open_DiaryFile(D1, FileName);
				if (p != NULL)
					Open_Diary(p);
				tempch = getch();
			};
				break;
			case 3: {
				printf("\n\n\t���û��������ռ�:\n\n");
				Printf_DiaryList(D1);
				tempch = getch();
			}
				break;
			case 4: {
				if (Search_Diary(D1) == 1)
					tempch = getch();
			}
				break;    //�򿪰����ļ�
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
	printf("\n\n\t����������(2008-12-31):\t");
	scanf("%s", &p->date);
	printf("\n\t���������:\t");
	scanf("%s", &p->title);
	printf("\n\t�뿪ʼд�ռ�:......\n\n\t");
	scanf("%s", &p->content);
	printf("\n\t��Ϊ���ռ�д�ؼ���:\t");
	scanf("%s", &p->keyword);
	p->tag = 0;
	p->nextd = D1->nextd;
	D1->nextd = p;
	printf("\n\t--------------------------------------------------\n");
	printf("\t�Ƿ�Ҫ���ļ���ʽ�����ռ�?\t1-��  0--��\t");
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

int Input_Choose()       //�˺��������ж��Ƿ������������������������ظ�������
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
	n = atoi(str1);          //����atoi�������ַ���strת����������
	return n;        //���������������
}

Diary *Open_DiaryFile(Diary *D1, char FileName[]) {
	FILE *fp;
	Diary *p = NULL;
	if ((fp = fopen(FileName, "r")) == NULL) {
		printf("\t�ļ���ʧ�ܣ�");
		return NULL;
	} else {
		p = (Diary *) malloc(sizeof(Diary));
		if (p == NULL) {
			printf("\t�ռǴ���ʧ�ܣ�");
			return NULL;
		}
		fscanf(fp, "\t����: %s\n", p->date);
		fscanf(fp, "\t����: %s\n", p->title);
		fscanf(fp, "\t�ؼ���: %s\n", p->keyword);
		fscanf(fp, "\t��������:\n\t%s\n", p->content);
		p->tag = 0;
		p->nextd = D1->nextd;
		D1->nextd = p;
		fclose(fp);
		return p;
	}
}

int Open_Diary(Diary *D1) {
	printf("\n\t--------------------------------------------------\n");
	printf("\n\t�ռ�����==>%s", D1->date);
	printf("\n\t�ռǱ���==>%s", D1->title);
	printf("\n\n\t�ؼ���==>%s", D1->keyword);
	printf("\n\t--------------------------------------------------\n");
	printf("\n\n\t�ռ���������:\n");
	printf("\n\t%s", D1->content);
	return 1;
}

int Printf_DiaryList(Diary *D1) {
	int count = 0;
	Diary *D;
	D = D1;
	printf("\n");
	if (D->nextd == NULL)
		printf("\tû���ռ���Ϣ��.....\n");
	else {
		while (D->nextd != NULL) {
			D = D->nextd;
			if (D->tag == 0) {
				count++;
				printf("\t��%2dƪ==>ʱ��:%-10s   �ռǱ���:%-20s  \t�ؼ���:%-s\n", count, D->date, D->title, D->keyword);
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
			printf("\n\tû���ռ�......\n");
		else {
			switch (choose3) {
				case 0:
					return 0;
				case 1: {
					printf("\n\t���û��������ռ�:\n\n");
					Printf_DiaryList(D1);
				}
					break;
				case 2:
					Search_order(D1);
					break;
				case 3: {
					printf("\n\t�ο�����:  �Ҳ��ٰ�����");
					printf("\n\t������Ҫ���ĵ��ռǱ���:\t");
					scanf("%s", cmpword);
					Filter_word(D1, cmpword, 1);
				}
					break;     //���������
				case 4: {
					printf("\n\t������Ҫ���ĵ��ռ�����(2009-4-11):\t");
					scanf("%s", cmpword);
					Filter_word(D1, cmpword, 2);
				}
					break;     //�����ڲ���
				case 5: {
					printf("\n\t������Ҫ���ĵĹؼ���(��:����):\t");
					scanf("%s", cmpword);
					Filter_word(D1, cmpword, 3);
				}
					break;     //���ؼ��ֲ���
			}

		}
		Initial_Tag(D1, 0);
		tempch = getch();
		rewind(stdin);                    /*��ռ��̻�������������ַ�*/
	}
	return 1;
}

int Save_Diary(Diary *D1) {
	FILE *fp;
	char FileName[40], postfix[6] = ".txt\0";
	printf("\t�������ļ�·�����ļ���:");
	scanf("%s", FileName);
	if ((fp = fopen(FileName, "w+")) == NULL) {
		printf("\t���ļ�ʧ�ܣ�");
		return 0;
	}
	fprintf(fp, "\t����: %s\n", D1->date);
	fprintf(fp, "\t����: %s\n", D1->title);
	fprintf(fp, "\t�ؼ���: %s\n", D1->keyword);
	fprintf(fp, "\t��������:\n\t%s\n", D1->content);
	fclose(fp);
	printf("\t�ռ��ļ�����ɹ���");
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
			printf("\n\t��Ҫ���ĵ��ǵڼ�ƪ(<=%d):\t", count);
			choose = Input_Choose();
		} while (choose < 1 || choose > count);

		while (D->nextd != NULL) {
			if (D->nextd->tag == 0) {
				if (count1 == choose - 1) {
					Open_Diary(D->nextd);
					printf("\n\n\t--------------------------------------------------\n");
					printf("\t�Ƿ�Ҫɾ����ƪ�ռ�?\t1-��  0--��\t");
					printf("\n\t--------------------------------------------------\n\t");
					printf("\t��ѡ�����:\t");
					temp = Input_Choose();
					if (temp == 1)
						Delete_Diary(D);        //ɾ��P����һ�����
					return D;
				}
				count1++;
			}
			D = D->nextd;
		}
	} else if (count == 0)
		printf("\n\tû�з��ϲ���Ҫ����ռ�.....");
	return D;
}

int Delete_Diary(Diary *D) {
	Diary *p;
	p = D->nextd;
	D->nextd = p->nextd;
	free(p);
	printf("\n\t�ռ�ɾ���ɹ�......");
	return 1;
}

Diary *Filter_word(Diary *D1, char cmpword[], int n)    //���õ���ɸѡ�㷨
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
	printf("\n\n\t�����µ��ռǷ��ϲ���Ҫ��:\n");
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
	char filepn[80];/*��������ļ�����·���Լ��ļ���*/
	printf("\n\n\t--------------------------------------------------\n");
	printf("\t�Ƿ񱣴汾��ʹ�����������в���?...\t1-��  0--��\t");
	printf("\n\t--------------------------------------------------\n\t");
	printf("��ѡ�����:\t");
	temp = Input_Choose();
	if (temp == 1) {
		strcpy(filepn, "..\\information\\User_info.txt");
		if ((fp = fopen(filepn, "w+")) == NULL) {
			printf("���ܴ��ļ�!\n");
			return 0;
		}
		while (U1->nextu != NULL) {
			fprintf(fp, "User:\n");
			U1 = U1->nextu;/*����һ�����*/
			fprintf(fp, "�û�id:%s\n", U1->id);
			D1 = U1->diarys_list;
			while (D1->nextd != NULL) {
				D1 = D1->nextd;
				fprintf(fp, "Diary:\n");
				fprintf(fp, "\t����:%s\n\t�ؼ���: %s\n", D1->date, D1->keyword);
				fprintf(fp, "\t����:%s\n", D1->title);
				fprintf(fp, "\t�ռ�����:\n%s\n", D1->content);
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
		printf("\t�û�����ʧ�ܣ�");
		return NULL;
	}

	s->diarys_list = D2;
	s->nextu = U1->nextu;
	U1->nextu = s;
	for (int i = 0; i < 20; i++) {
		s->id[i] = id[i];
	}
	flag = 0;
	printf("\n\t�û������ɹ�!......\n");
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

