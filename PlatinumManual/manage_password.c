//
// Created by TZQ on 2020/7/19.
//

#include "manage_password.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//index里面的两个return改成主菜单
/*再加上修改地址
void seeking_by_software(char* id, char* app);
void seeking_by_account(char* id, char* accountnumber);
void seeking_by_code(char* id, char* codenumber);
void writing_password(char* id);
*/
void manage_password_index(char *id);

void seeking_by_software(char *id, char *app);

void seeking_by_account(char *id, char *accountnumber);

void seeking_by_code(char *id, char *codenumber);

void writing_password(char *id);

struct password_password *readFile_password(const char *filename);

// 注释该函数的声明以解决未知原因的报错
//void insert_data(struct Userdata_password *pdata, char *address);

void save_file_password(const char *filename, struct password_password *p);

void free_file_password(struct password_password *p);

void del_data_by_software(char *name, char *address);

void del_data_by_account(char *name, char *address);

void del_data_by_code(char *name, char *address);

void change_password(char *id, char *fileaddress, char *new_software, char *new_account, char *new_code);


typedef struct Userdata_password {
	char id[20];
	char software[30];
	char account[30];
	char code[30];
} User_t;

struct password_password {
	User_t data;
	struct password_password *next;
};

struct password_password *readFile_password(const char *filename) {
	FILE *fp; //声明指向文件结构体的指针变量fp
	struct password_password *head = NULL; //声明链表头结点指针head，并赋值为空
	struct password_password *p = NULL; //声明链表节点指针p,p1（p用于存储从文件读取的当前节点，p1用于标识创建链表过程的尾节点）
	struct password_password *p1 = NULL;
	unsigned int ret; //声明无符号整型变量ret，用于存储fread函数实际读取到的字符数
	int count = 0;  //定义整型变量count，用于存储链表节点个数
	fp = fopen(filename, "a+"); //以追加读写的方式打开文件，在文件不存在时创建文件，并把返回值赋值给指针变量fp
	if (fp == NULL) {  //打开失败，错误处理
		printf("没有找到你的文件哎o(╥﹏╥)o\n");
		exit(1);
	}
	p = (struct password_password *) malloc(sizeof(struct password_password)); //申请一个节点结构体大的空间，并用链表节点指针p指向这个空间
	memset(p, 0, sizeof(struct password_password)); //初始化申请的空间（用0填充）
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
		p = (struct password_password *) malloc(sizeof(struct password_password)); //申请一个节点结构体大的空间，并用链表节点指针p指向这个空间
		memset(p, 0, sizeof(struct password_password)); //初始化申请的空间（用0填充）
		ret = fread(p, sizeof(User_t), 1, fp); //读取文件中的链表数据结构体大小的数据（一个用户data信息）到申请的节点结构体中
	}
	p1->next = NULL; //将尾节点的next域赋值为空
	fclose(fp); //关闭文件
	return head; //返回链表头结点指针head（head为一个非空链表的头结点）
}


void insert_data(struct Userdata_password *pdata, char *address) {
	struct password_password *head = readFile_password(address); //读取文件中的数据并整合为链表，将头结点指针传递给head
	struct password_password *p; //声明链表节点指针p（p用于存储传入的用户数据）
	struct password_password *p1 = head; //声明链表节点指针p1（p1用于存储当前节点）
	if (!p1) { //判断头结点是否为空（为空为真（为真即为文件为空），头结点未申请空间）
		head = (struct password_password *) malloc(sizeof(struct password_password)); //申请一个节点结构体大的空间，并用链表头节点指针head指向这个空间
		memset(head, 0, sizeof(struct password_password)); //初始化申请的空间（用0填充）
		head->data = *pdata; //将传入的用户数据赋值给头结点的数据域
		head->next = NULL; //将头结点指针域赋值为NULL
	} else { //头结点不为空（文件中存在用户信息）
		while (p1->next) { //循环遍历链表找到指针域为空的节点，即链表尾节点
			p1 = p1->next;
		}
		p = (struct password_password *) malloc(sizeof(struct password_password)); //并申请一个节点结构体大小的空间，并用链表节点指针p指向这个空间
		memset(p, 0, sizeof(struct password_password)); //初始化申请的空间（用0填充）
		p->data = *pdata; //将传入的用户数据赋值给链表节点p的数据域
		p->next = p1->next; //将尾节点的next域赋值给p节点的next域（将NULL赋值给尾结点的next域）
		p1->next = p; //曾经尾结点的next域指向当前p节点（尾结点变为p节点，即将p插入到链表的尾部）
	}
	save_file_password(address, head); //将插入后的链表存入文件
	free_file_password(head); //释放链表
}

void save_file_password(const char *filename, struct password_password *p) {
	FILE *fp; //声明指向文件结构体的指针变量fp
	fp = fopen(filename, "w+"); //以每次打开清空文件内容的方式打开可读写文件，在文件不存在时创建文件，并把返回值赋值给指针变量fp
	if (fp == NULL) { //打开失败，错误处理
		printf("文件打开失败了o(╥﹏╥)o\n");
		exit(1);
	}
	while (p) { //循环遍历传入的用户信息链表
		fwrite(p, sizeof(User_t), 1, fp); //将当前遍历到的用户信息节点的数据域写入文件
		p = p->next; //当前遍历节点向后移动
	}
	fclose(fp); //关闭文件
}

void free_file_password(struct password_password *p) {
	struct password_password *p1; //声明链表节点指针p1（p1用于存储要释放的当前节点）
	while (p) { //循环编译传入的链表
		p1 = p; //将当前遍历节点赋值于p1
		p = p->next; //当前遍历节点向后移动
		free(p1); //释放p1节点（即释放向后移动前的节点）
	}
}

void manage_password_index(char *id) {
	int choice_one = 0;
	printf("\n很高兴为您服务！请选择我的功能叭：(*^▽^*)\n");
	printf("1：通过软件查询（包括修改）\n");
	printf("2：通过账号查询（包括修改）\n");
	printf("3：通过密码查询（包括修改）\n");
	printf("4:添加新记录\n");
	printf("5:无情地离开o(╥﹏╥)o\n");
	scanf("%d", &choice_one);
	while ((choice_one != 1) && (choice_one != 2) && (choice_one != 3) && (choice_one != 4) && (choice_one != 5)) {
		printf("没有这个选项哦亲，已返回！(〃'▽'〃)");
		//把此处的return改成返回主菜单更好一些
		return;
	}
	switch (choice_one) {
		case 1:
			printf("请输入您所查询的软件名称：");
			char app[30];
			scanf("%s", app);
			seeking_by_software(id, app);
			break;
		case 2:
			printf("请输入您所查询的账号：");
			char accountnumber[30];
			scanf("%s", accountnumber);
			seeking_by_account(id, accountnumber);
			break;
		case 3:
			printf("请输入您所查询的密码：");
			char codenumber[30];
			scanf("%s", codenumber);
			seeking_by_code(id, codenumber);
			break;
		case 4:
			writing_password(id);
			break;
		case 5:
			//此处的return应该改成主菜单的函数，不然需要退很多次才会退出程序
			return;
			break;
		default:
			printf("没有这个选项哎！已经自动返回啦。(〃'▽'〃)");
			return;
			break;
	}
}

void seeking_by_software(char *id, char *app) {
	int choice_two = 0;
	//通过id得到地址
	char fileaddress[60];
	strcpy(fileaddress, "F:\\");
	//strcat(fileaddress, id);
	strcat(fileaddress, "manage_password.txt");
	struct password_password *head = readFile_password(fileaddress); //读取文件中的数据并整合为链表，将头结点指针传递给head
	struct password_password *point = head; //声明链表节点指针p（p用于存储当前节点），并将head赋值给p
	if (!point) { //判断当前结点（头结点）是否为空（为空为真，即文件为空）
		printf("你好像还没有记录过哎（o^^o）\n");
		return; //返回0
	}
	while (point != NULL && strcmp(point->data.software, app) != 0) { //循环遍历链表，找到要查找的节点
		point = point->next;
	}
	if (point != NULL && strcmp(point->data.software, app) == 0) {
		printf("软件是：%s\n", point->data.software);
		printf("账号是：%s\n", point->data.account);
		printf("密码是：%s\n", point->data.code);
		int judge;
		printf("输入0返回，输入1修改，输入2删除。\n");
		scanf("%d", &judge);
		switch (judge) {
			case 0:
				manage_password_index(id);
				break;
			case 1:
				printf("1：修改软件\n");
				printf("2：修改账号\n");
				printf("3：修改密码\n");
				scanf("%d", &choice_two);
				char new_software[30]; // 变量定义1迁移至此*
				char new_account[30]; // 变量定义2迁移至此*
				char new_code[30]; // 变量定义3迁移至此*
				switch (choice_two) {
					case 1:
//						char new_software[30];  // 变量定义1迁移至外部*
						printf("请输入新的软件名称：\n");
						scanf("%s", new_software);
						del_data_by_software(point->data.software, fileaddress);
						strcpy(point->data.software, new_software);
						change_password(id, fileaddress, point->data.software, point->data.account, point->data.code);
						printf("修改成功。(*^▽^*)\n");
						manage_password_index(id);
						break;
					case 2:
//						char new_account[30];  // 变量定义2迁移至外部*
						printf("请输入新的账号：\n");
						scanf("%s", new_account);
						del_data_by_account(point->data.account, fileaddress);
						strcpy(point->data.account, new_account);
						change_password(id, fileaddress, point->data.software, point->data.account, point->data.code);
						printf("修改成功。(*^▽^*)\n");
						manage_password_index(id);
						break;
					case 3:
//						char new_code[30]; // 变量定义3迁移至外部*
						printf("请输入新的密码：\n");
						scanf("%s", new_code);
						del_data_by_code(point->data.code, fileaddress);
						strcpy(point->data.code, new_code);
						change_password(id, fileaddress, point->data.software, point->data.account, point->data.code);
						printf("修改成功。(*^▽^*)\n");
						manage_password_index(id);
						break;
					default:
						printf("这个。。这个选项，是不可以的o(╥﹏╥)o\n");
						manage_password_index(id);
						break;
				}
				manage_password_index(id);
				break;
			case 2:
				del_data_by_software(app, fileaddress);
				manage_password_index(id);
				break;
			default:
				printf("这个。。这个选项，是不可以的o(╥﹏╥)o\n");
				manage_password_index(id);
				break;
		}
	} else //链表中无要查找的节点
	{
		printf("我没有找到这个软件哎ε=(?ο｀*)))\n");
		manage_password_index(id);
	}
	free_file_password(head); //释放链表
}

void seeking_by_account(char *id, char *accountnumber) {
	int choice_two = 0;
	//通过id得到地址
	char fileaddress[60];
	strcpy(fileaddress, "F:\\");
	//strcat(fileaddress, id);
	strcat(fileaddress, "manage_password.txt");
	struct password_password *head = readFile_password(fileaddress); //读取文件中的数据并整合为链表，将头结点指针传递给head
	struct password_password *point = head; //声明链表节点指针p（p用于存储当前节点），并将head赋值给p
	if (!point) { //判断当前结点（头结点）是否为空（为空为真，即文件为空）
		printf("你好像还没有记录过哎（o^^o）\n");
		return; //返回0
	}
	while (point && strcmp(point->data.account, accountnumber)) { //循环遍历链表，找到要查找的节点
		point = point->next;
	}
	if (point) {
		printf("软件是：%s\n", point->data.software);
		printf("账号是：%s\n", point->data.account);
		printf("密码是：%s\n", point->data.code);
		int judge;
		printf("输入0返回，输入1修改，输入2删除。\n");
		scanf("%d", &judge);
		switch (judge) {
			case 0:
				manage_password_index(id);
				break;
			case 1:
				printf("1：修改软件\n");
				printf("2：修改账号\n");
				printf("3：修改密码\n");
				scanf("%d", &choice_two);
				char new_software[30]; // 变量定义1迁移至此*
				char new_account[30]; // 变量定义2迁移至此*
				char new_code[30]; // 变量定义3迁移至此*
				switch (choice_two) {
					case 1:
//						char new_software[30];  // 变量定义1迁移至外部*
						printf("请输入新的软件名称：\n");
						scanf("%s", new_software);
						strcpy(point->data.software, new_software);
						printf("修改成功(*^▽^*)\n");
						manage_password_index(id);
						break;
					case 2:
//						char new_account[30];  // 变量定义2迁移至外部*
						printf("请输入新的账号：\n");
						scanf("%s", new_account);
						strcpy(point->data.account, new_account);
						printf("修改成功(*^▽^*)\n");
						manage_password_index(id);
						break;
					case 3:
//						char new_code[30];  // 变量定义3迁移至外部*
						printf("请输入新的密码：\n");
						scanf("%s", new_code);
						strcpy(point->data.code, new_code);
						printf("修改成功(*^▽^*)\n");
						manage_password_index(id);
						break;
					default:
						printf("这个。。这个选项，是不可以的o(╥﹏╥)o\n");
						manage_password_index(id);
						break;
				}
				manage_password_index(id);
				break;
			case 2:
				del_data_by_account(accountnumber, fileaddress);
				manage_password_index(id);
				break;
			default:
				printf("这个。。这个选项，是不可以的o(╥﹏╥)o\n");
				manage_password_index(id);
				break;
		}
	} else //链表中无要查找的节点
	{
		printf("我没有找到这个账号哎ε=(?ο｀*)))\n");
		manage_password_index(id);
	}
	free_file_password(head); //释放链表
}

void seeking_by_code(char *id, char *codenumber) {
	int choice_two = 0;
	//通过id得到地址
	char fileaddress[60];
	strcpy(fileaddress, "F:\\");
	//strcat(fileaddress, id);
	strcat(fileaddress, "manage_password.txt");
	struct password_password *head = readFile_password(fileaddress); //读取文件中的数据并整合为链表，将头结点指针传递给head
	struct password_password *point = head; //声明链表节点指针p（p用于存储当前节点），并将head赋值给p
	if (!point) { //判断当前结点（头结点）是否为空（为空为真，即文件为空）
		printf("你好像还没有记录过哎（o^^o）\n");
		return; //返回0
	}
	while (point && strcmp(point->data.code, codenumber)) { //循环遍历链表，找到要查找的节点
		point = point->next;
	}
	if (point) {
		printf("软件是：%s\n", point->data.software);
		printf("账号是：%s\n", point->data.account);
		printf("密码是：%s\n", point->data.code);
		int judge;
		printf("输入0返回，输入1修改，输入2删除。\n");
		scanf("%d", &judge);
		switch (judge) {
			case 0:
				manage_password_index(id);
				break;
			case 1:
				printf("1：修改软件\n");
				printf("2：修改账号\n");
				printf("3：修改密码\n");
				scanf("%d", &choice_two);
				char new_software[30]; // 变量定义1迁移至此*
				char new_account[30]; // 变量定义2迁移至此*
				char new_code[30]; // 变量定义3迁移至此*
				switch (choice_two) {
					case 1:
//						char new_software[30];  // 变量定义1迁移至外部*
						printf("请输入新的软件名称：\n");
						scanf("%s", new_software);
						strcpy(point->data.software, new_software);
						printf("修改成功(*^▽^*)\n");
						manage_password_index(id);
						break;
					case 2:
//						char new_account[30];  // 变量定义2迁移至外部*
						printf("请输入新的账号：\n");
						scanf("%s", new_account);
						strcpy(point->data.account, new_account);
						printf("修改成功(*^▽^*)\n");
						manage_password_index(id);
						break;
					case 3:
//						char new_code[30];  // 变量定义3迁移至外部*
						printf("请输入新的密码：\n");
						scanf("%s", new_code);
						strcpy(point->data.code, new_code);
						printf("修改成功(*^▽^*)\n");
						manage_password_index(id);
						break;
					default:
						printf("这个。。这个选项，是不可以的o(╥﹏╥)o\n");
						manage_password_index(id);
						break;
				}
				break;
			case 2:
				del_data_by_code(codenumber, fileaddress);
				manage_password_index(id);
				break;
			default:
				printf("这个。。这个选项，是不可以的o(╥﹏╥)o\n");
				manage_password_index(id);
				break;
		}
	} else //链表中无要查找的节点
	{
		printf("我没有找到这个密码哎ε=(?ο｀*)))\n");
		manage_password_index(id);
	}
	free_file_password(head); //释放链表
}

void del_data_by_software(char *name, char *address) {
	struct password_password *head = readFile_password(address); //读取文件中的数据并整合为链表，将头结点指针传递给head
	struct password_password *p = head; //声明链表节点指针p（p用于存储当前节点），并将head赋值给p
	struct password_password *pdel; //声明链表节点指针pdel（pdel用于存储要删除的节点）
	if (!head) { //判断头结点是否为空（为空为真，即文件为空）
		printf("你好像还没有记录过哎（o^^o）\n");
	} else if (!strcmp(p->data.software, name)) { //判断头结点是否为要删除的节点（是为真）
		pdel = p; //将当前节点p（头结点head）赋值给pdel
		head = head->next; //将头结点的下一个节点赋值给头结点
		free(pdel); //释放要删除的节点
	} else { //头结点不为空，且要删除的节点不是头结点
		while (p->next && strcmp(p->next->data.software, name)) { //循环遍历链表，找到要删除节点的上一个节点
			p = p->next;
		}
		if (p->next) { //判断要删除的节点是否为空（不为空即为找到（为真），为空即为未找到（链表中无要删除的节点））
			pdel = p->next; //将要删除的节点（当前节点的下一个节点）赋值给pdel
			p->next = pdel->next; //将要删除节点的下一个节点赋值给要删除节点的上一个节点（将其前一个节点和后一个节点相连）
			free(pdel); //释放要删除的节点
		} else { //链表中无要删除的节点
			printf("我没有找到这个软件哎ε=(?ο｀*)))\n");
		}
	}
	save_file_password(address, head); //将删除后的链表存入文件
	free_file_password(head); //释放链表
}

void del_data_by_account(char *name, char *address) {
	struct password_password *head = readFile_password(address); //读取文件中的数据并整合为链表，将头结点指针传递给head
	struct password_password *p = head; //声明链表节点指针p（p用于存储当前节点），并将head赋值给p
	struct password_password *pdel; //声明链表节点指针pdel（pdel用于存储要删除的节点）
	if (!head) { //判断头结点是否为空（为空为真，即文件为空）
		printf("你好像还没有记录过哎（o^^o）\n");
	} else if (!strcmp(p->data.account, name)) { //判断头结点是否为要删除的节点（是为真）
		pdel = p; //将当前节点p（头结点head）赋值给pdel
		head = head->next; //将头结点的下一个节点赋值给头结点
		free(pdel); //释放要删除的节点
	} else { //头结点不为空，且要删除的节点不是头结点
		while (p->next && strcmp(p->next->data.account, name)) { //循环遍历链表，找到要删除节点的上一个节点
			p = p->next;
		}
		if (p->next) { //判断要删除的节点是否为空（不为空即为找到（为真），为空即为未找到（链表中无要删除的节点））
			pdel = p->next; //将要删除的节点（当前节点的下一个节点）赋值给pdel
			p->next = pdel->next; //将要删除节点的下一个节点赋值给要删除节点的上一个节点（将其前一个节点和后一个节点相连）
			free(pdel); //释放要删除的节点
		} else { //链表中无要删除的节点
			printf("我没有找到这个账号哎ε=(?ο｀*)))\n");
		}
	}
	save_file_password(address, head); //将删除后的链表存入文件
	free_file_password(head); //释放链表
}

void del_data_by_code(char *name, char *address) {
	struct password_password *head = readFile_password(address); //读取文件中的数据并整合为链表，将头结点指针传递给head
	struct password_password *p = head; //声明链表节点指针p（p用于存储当前节点），并将head赋值给p
	struct password_password *pdel; //声明链表节点指针pdel（pdel用于存储要删除的节点）
	if (!head) { //判断头结点是否为空（为空为真，即文件为空）
		printf("你好像还没有记录过哎（o^^o）\n");
	} else if (!strcmp(p->data.code, name)) { //判断头结点是否为要删除的节点（是为真）
		pdel = p; //将当前节点p（头结点head）赋值给pdel
		head = head->next; //将头结点的下一个节点赋值给头结点
		free(pdel); //释放要删除的节点
	} else { //头结点不为空，且要删除的节点不是头结点
		while (p->next && strcmp(p->next->data.code, name)) { //循环遍历链表，找到要删除节点的上一个节点
			p = p->next;
		}
		if (p->next) { //判断要删除的节点是否为空（不为空即为找到（为真），为空即为未找到（链表中无要删除的节点））
			pdel = p->next; //将要删除的节点（当前节点的下一个节点）赋值给pdel
			p->next = pdel->next; //将要删除节点的下一个节点赋值给要删除节点的上一个节点（将其前一个节点和后一个节点相连）
			free(pdel); //释放要删除的节点
		} else { //链表中无要删除的节点
			printf("我没有找到这个密码哎ε=(?ο｀*)))\n");
		}
	}
	save_file_password(address, head); //将删除后的链表存入文件
	free_file_password(head); //释放链表
}

void writing_password(char *id) {
	User_t data;
	char fileaddress[60];
	strcpy(fileaddress, "F:\\");
	//strcat(fileaddress, id);
	//合并之后还需要在前面加\\才行
	strcat(fileaddress, "manage_password.txt");
	printf("请输入软件：\n");
	scanf("%s", &data.software);
	printf("请输入账号：\n");
	scanf("%s", &data.account);
	printf("请输入密码：\n");
	scanf("%s", &data.code);
	insert_data(&data, fileaddress);
	printf("成功记录，已返回(*^▽^*)\n");
	manage_password_index(id);
}

void change_password(char *id, char *fileaddress, char *new_software, char *new_account, char *new_code) {
	User_t data;
	strcpy(data.software, new_software);
	strcpy(data.account, new_account);
	strcpy(data.code, new_code);
	insert_data(&data, fileaddress);
}

void manage_password(char *id) {

	manage_password_index(id);

	return;
}
