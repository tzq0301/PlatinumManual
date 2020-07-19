//
// Created by TZQ on 2020/7/19.
//

#include "manage_url_of_web_page.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void manage_web_index(char *id);

void seeking_by_webname(char *id, char *webname);

void seeking_by_remarks(char *id, char *remarks);

void writing(char *id);

struct web *readFile(const char *filename);

// 注释该函数声明以解决未知原因的报错
//void insert_data(struct Userdata *pdata, char *address);

void save_file(const char *filename, struct web *p);

void free_file(struct web *p);

void del_data_by_webname(char *webname, char *address);

void del_data_by_remarks(char *remarks, char *address);

typedef struct Userdata {
	char id[20];
	char remark[100];
	char web[60];
} User_t;

struct web {
	User_t data;
	struct web *next;
};

struct web *readFile(const char *filename) {
	FILE *fp; //声明指向文件结构体的指针变量fp
	struct web *head = NULL; //声明链表头结点指针head，并赋值为空
	struct web *p = NULL; //声明链表节点指针p,p1（p用于存储从文件读取的当前节点，p1用于标识创建链表过程的尾节点）
	struct web *p1 = NULL;
	unsigned int ret; //声明无符号整型变量ret，用于存储fread函数实际读取到的字符数
	int count = 0;  //定义整型变量count，用于存储链表节点个数
	fp = fopen(filename, "a+"); //以追加读写的方式打开文件，在文件不存在时创建文件，并把返回值赋值给指针变量fp
	if (fp == NULL) {  //打开失败，错误处理
		perror("read open");
		exit(1);
	}
	p = (struct web *) malloc(sizeof(struct web)); //申请一个节点结构体大的空间，并用链表节点指针p指向这个空间
	memset(p, 0, sizeof(struct web)); //初始化申请的空间（用0填充）
	ret = fread(p, sizeof(User_t), 1, fp);    //读取文件中的链表数据结构体大小的数据（一个用户data信息）到申请的节点结构体中
	if (!ret) {  //判断读取到的字符数是否为0（判断文件是否为空（为空为真））
		return head; //返回链表头结点指针head（head未申请空间，为NULL）
	}
	while (ret) {  //判断读取到的字符数是否为1（判断文件是否为空（非空为真））
		count++;  //节点个数加1
		if (count == 1) {    //判断是否为第一个节点（头结点）
			head = p; //将当前读取到的节点p赋值给头结点
			p1 = p; //将当前读取到的节点作为尾结点
		}
		p1->next = p; //将当前读取到的节点p赋值给上次操作的尾结点
		p1 = p; //将当前读取到的节点作为尾节点（尾节点向后移动一次）
		p = (struct web *) malloc(sizeof(struct web)); //申请一个节点结构体大的空间，并用链表节点指针p指向这个空间
		memset(p, 0, sizeof(struct web)); //初始化申请的空间（用0填充）
		ret = fread(p, sizeof(User_t), 1, fp); //读取文件中的链表数据结构体大小的数据（一个用户data信息）到申请的节点结构体中
	}
	p1->next = NULL; //将尾节点的next域赋值为空
	fclose(fp); //关闭文件
	return head; //返回链表头结点指针head（head为一个非空链表的头结点）
}

void insert_data(struct Userdata *pdata, char *address) {
	struct web *head = readFile(address); //读取文件中的数据并整合为链表，将头结点指针传递给head
	struct web *p; //声明链表节点指针p（p用于存储传入的用户数据）
	struct web *p1 = head; //声明链表节点指针p1（p1用于存储当前节点）
	if (!p1) { //判断头结点是否为空（为空为真（为真即为文件为空），头结点未申请空间）
		head = (struct web *) malloc(sizeof(struct web)); //申请一个节点结构体大的空间，并用链表头节点指针head指向这个空间
		memset(head, 0, sizeof(struct web)); //初始化申请的空间（用0填充）
		head->data = *pdata; //将传入的用户数据赋值给头结点的数据域
		head->next = NULL; //将头结点指针域赋值为NULL
	} else { //头结点不为空（文件中存在用户信息）
		while (p1->next) { //循环遍历链表找到指针域为空的节点，即链表尾节点
			p1 = p1->next;
		}
		p = (struct web *) malloc(sizeof(struct web)); //并申请一个节点结构体大小的空间，并用链表节点指针p指向这个空间
		memset(p, 0, sizeof(struct web)); //初始化申请的空间（用0填充）
		p->data = *pdata; //将传入的用户数据赋值给链表节点p的数据域
		p->next = p1->next; //将尾节点的next域赋值给p节点的next域（将NULL赋值给尾结点的next域）
		p1->next = p; //曾经尾结点的next域指向当前p节点（尾结点变为p节点，即将p插入到链表的尾部）
	}
	save_file(address, head); //将插入后的链表存入文件
	free_file(head); //释放链表
}

void save_file(const char *filename, struct web *p) {
	FILE *fp; //声明指向文件结构体的指针变量fp
	fp = fopen(filename, "w+"); //以每次打开清空文件内容的方式打开可读写文件，在文件不存在时创建文件，并把返回值赋值给指针变量fp
	if (fp == NULL) { //打开失败，错误处理
		perror("save open");
		exit(1);
	}
	while (p) { //循环遍历传入的用户信息链表
		fwrite(p, sizeof(User_t), 1, fp); //将当前遍历到的用户信息节点的数据域写入文件
		p = p->next; //当前遍历节点向后移动
	}
	fclose(fp); //关闭文件
}

void free_file(struct web *p) {
	struct web *p1; //声明链表节点指针p1（p1用于存储要释放的当前节点）
	while (p) { //循环编译传入的链表
		p1 = p; //将当前遍历节点赋值于p1
		p = p->next; //当前遍历节点向后移动
		free(p1); //释放p1节点（即释放向后移动前的节点）
	}
}

void manage_web_index(char *id) {
	int choice_one = 0;
	printf("\n请选择功能：\n");
	printf("1：通过网站查询（包括修改）\n");
	printf("2：通过备注查询（包括修改）\n");
	printf("3:记录\n");
	printf("4:返回\n");
	scanf("%d", &choice_one);
	while ((choice_one != 1) && (choice_one != 2) && (choice_one != 3) && (choice_one != 4)) {
		printf("没有这个选项哦亲，再来一遍吧！");
		scanf("%d", &choice_one);
	}
	switch (choice_one) {
		case 1:
			printf("请输入你所查询的网站名称：");
			char webname[60];
			scanf("%s", webname);
			seeking_by_webname(id, webname);
			break;
		case 2:
			printf("请输入你所查询的备注：");
			char remarks[100];
			scanf("%s", remarks);
			seeking_by_remarks(id, remarks);
			break;
		case 3:
			writing(id);
			break;
		case 4:
			return;
		default:
			printf("错误！自动返回。");
			return;
	}
}

// 涉及文件名修改
void seeking_by_webname(char *id, char *webname) {
	int choice_two = 0;
	//通过id得到地址
	char fileaddress[60];
	strcpy(fileaddress, "..\\information\\");
	strcat(fileaddress, id);
	strcat(fileaddress, "\\manage_web.txt");
	struct web *head = readFile(fileaddress); //读取文件中的数据并整合为链表，将头结点指针传递给head
	struct web *point = head; //声明链表节点指针p（p用于存储当前节点），并将head赋值给p
	if (!point) { //判断当前结点（头结点）是否为空（为空为真，即文件为空）
		printf("你还没有记录过哦（o^^o）\n");
		return; //返回0
	}
	while (point != NULL && strcmp(point->data.web, webname) != 0) { //循环遍历链表，找到要查找的节点
		point = point->next;
	}
	if (point != NULL && strcmp(point->data.web, webname) == 0) {
		printf("你所查询的网站是：%s\n", point->data.web);
		printf("你所查询的备注是：%s\n", point->data.remark);
		int judge;
		printf("输入0返回，输入1修改，输入2删除。\n");
		scanf("%d", &judge);
		switch (judge) {
			case 0:
				manage_web_index(id);
				break;
			case 1:
				printf("1：修改网站\n");
				printf("2：修改备注\n");
				scanf("%d", &choice_two);
				char new_webname[30]; // 变量定义1迁移至此*
				char new_remarks[100]; // 变量定义2迁移至此*
				switch (choice_two) {
					case 1:
//						char new_webname[30]; // 变量定义1迁移至外部*
						printf("请输入新的网站：\n");
						scanf("%s", new_webname);
						strcpy(point->data.web, new_webname);
						printf("修改成功。");
						manage_web_index(id);
						break;
					case 2:
//						char new_remarks[100]; // 变量定义2迁移至外部*
						printf("请输入新的备注：\n");
						scanf("%s", new_remarks);
						strcpy(point->data.remark, new_remarks);
						printf("修改成功。\n");
						manage_web_index(id);
						break;
					default:
						printf("输入错误，自动返回。\n");
						manage_web_index(id);
						break;
				}
				manage_web_index(id);
				break;
			case 2:
				del_data_by_webname(webname, fileaddress);
				manage_web_index(id);
				break;
			default:
				printf("输入错误，已自动返回。\n");
				manage_web_index(id);
				break;
		}
	} else //链表中无要查找的节点
	{
		printf("找不到，已返回。");
		manage_web_index(id);
	}
	free_file(head); //释放链表
}

// 涉及文件名修改
void seeking_by_remarks(char *id, char *remarks) {
	int choice_two = 0;
	//通过id得到地址
	char fileaddress[60];
	strcpy(fileaddress, "..\\information\\");
	strcat(fileaddress, id);
	strcat(fileaddress, "\\manage_web.txt");
	struct web *head = readFile(fileaddress); //读取文件中的数据并整合为链表，将头结点指针传递给head
	struct web *point = head; //声明链表节点指针p（p用于存储当前节点），并将head赋值给p
	if (!point) { //判断当前结点（头结点）是否为空（为空为真，即文件为空）
		printf("你还没有记录过哦（o^^o）\n");
		return; //返回0
	}
	while (point != NULL && strcmp(point->data.remark, remarks) != 0) { //循环遍历链表，找到要查找的节点
		point = point->next;
	}
	if (point != NULL && strcmp(point->data.remark, remarks) == 0) {
		printf("你所查询的网站是：%s\n", point->data.web);
		printf("你所查询的备注是：%s\n", point->data.remark);
		int judge;
		printf("输入0返回，输入1修改，输入2删除。\n");
		scanf("%d", &judge);
		switch (judge) {
			case 0:
				manage_web_index(id);
				break;
			case 1:
				printf("1：修改网站\n");
				printf("2：修改备注\n");
				scanf("%d", &choice_two);
				char new_webname[30]; // 变量定义1迁移至此*
				char new_remarks[100]; // 变量定义2迁移至此*
				switch (choice_two) {
					case 1:
//						char new_webname[30]; // 变量定义1迁移至外部*
						printf("请输入新的网站：\n");
						scanf("%s", new_webname);
						strcpy(point->data.web, new_webname);
						printf("修改成功。");
						manage_web_index(id);
						break;
					case 2:
//						char new_remarks[100]; // 变量定义2迁移至外部*
						printf("请输入新的备注：\n");
						scanf("%s", new_remarks);
						strcpy(point->data.remark, new_remarks);
						printf("修改成功。\n");
						manage_web_index(id);
						break;
					default:
						printf("输入错误，自动返回。\n");
						manage_web_index(id);
						break;
				}
				manage_web_index(id);
			case 2:
				del_data_by_remarks(remarks, fileaddress);
				manage_web_index(id);
				break;
			default:
				printf("输入错误，已自动返回。\n");
				manage_web_index(id);
				break;
		}
	} else { //链表中无要查找的节点
		printf("找不到，已返回。");
		manage_web_index(id);
	}
	free_file(head); //释放链表
}

void del_data_by_webname(char *webname, char *address) {
	struct web *head = readFile(address); //读取文件中的数据并整合为链表，将头结点指针传递给head
	struct web *p = head; //声明链表节点指针p（p用于存储当前节点），并将head赋值给p
	struct web *pdel; //声明链表节点指针pdel（pdel用于存储要删除的节点）
	if (!head) { //判断头结点是否为空（为空为真，即文件为空）
		printf("no have data delete!\n");
	} else if (!strcmp(p->data.web, webname)) { //判断头结点是否为要删除的节点（是为真）
		pdel = p; //将当前节点p（头结点head）赋值给pdel
		head = head->next; //将头结点的下一个节点赋值给头结点
		free(pdel); //释放要删除的节点
	} else { //头结点不为空，且要删除的节点不是头结点
		while (p->next && strcmp(p->next->data.web, webname)) { //循环遍历链表，找到要删除节点的上一个节点
			p = p->next;
		}
		if (p->next) { //判断要删除的节点是否为空（不为空即为找到（为真），为空即为未找到（链表中无要删除的节点））
			pdel = p->next; //将要删除的节点（当前节点的下一个节点）赋值给pdel
			p->next = pdel->next; //将要删除节点的下一个节点赋值给要删除节点的上一个节点（将其前一个节点和后一个节点相连）
			free(pdel); //释放要删除的节点
		} else { //链表中无要删除的节点
			printf("no have data delete!\n");
		}
	}
	save_file(address, head); //将删除后的链表存入文件
	free_file(head); //释放链表
}

void del_data_by_remarks(char *remarks, char *address) {
	struct web *head = readFile(address); //读取文件中的数据并整合为链表，将头结点指针传递给head
	struct web *p = head; //声明链表节点指针p（p用于存储当前节点），并将head赋值给p
	struct web *pdel; //声明链表节点指针pdel（pdel用于存储要删除的节点）
	if (!head) { //判断头结点是否为空（为空为真，即文件为空）
		printf("no have data delete!\n");
	} else if (!strcmp(p->data.remark, remarks)) { //判断头结点是否为要删除的节点（是为真）
		pdel = p; //将当前节点p（头结点head）赋值给pdel
		head = head->next; //将头结点的下一个节点赋值给头结点
		free(pdel); //释放要删除的节点
	} else { //头结点不为空，且要删除的节点不是头结点
		while (p->next && strcmp(p->next->data.remark, remarks)) { //循环遍历链表，找到要删除节点的上一个节点
			p = p->next;
		}
		if (p->next) { //判断要删除的节点是否为空（不为空即为找到（为真），为空即为未找到（链表中无要删除的节点））
			pdel = p->next; //将要删除的节点（当前节点的下一个节点）赋值给pdel
			p->next = pdel->next; //将要删除节点的下一个节点赋值给要删除节点的上一个节点（将其前一个节点和后一个节点相连）
			free(pdel); //释放要删除的节点
		} else { //链表中无要删除的节点
			printf("no have data delete!\n");
		}
	}
	save_file(address, head); //将删除后的链表存入文件
	free_file(head); //释放链表
}

// 涉及文件名修改
void writing(char *id) {
	User_t data;
	char fileaddress[60];
	strcpy(fileaddress, "..\\information\\");
	strcat(fileaddress, id);
	//合并之后还需要在前面加\\才行
	strcat(fileaddress, "\\manage_web.txt");
	printf("请输入网站：\n");
	scanf("%s", &data.web);
	printf("请输入备注：\n");
	scanf("%s", &data.remark);
	insert_data(&data, fileaddress);
	printf("成功记录，已返回。\n");
	manage_web_index(id);
}

void manage_url_of_web_page(char *id) {

	manage_web_index(id);

	return;
}