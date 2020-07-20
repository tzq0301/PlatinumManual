#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include<direct.h>

struct Birthday {
	int year;
	int month;
	int day;
};

typedef struct The_users {
	char id[20];
	char password[20];
	char name[15];
	char sex;
	long phone;
	struct Birthday birth;
} Users;

//创建储存用户账号密码的文件
void Create_File() {
	FILE *fp;
	if ((fp = fopen("..\\information\\users.txt", "wb")) == NULL) {
		printf("无法建立文件！\n");
		exit(0);
	} else {
		Users a = {"", "", "", '0', 0, {0, 0, 0}};
		for (long long int i = 1; i <= 1000000000; ++i) {
			fwrite(&a, sizeof(struct The_users), 1, fp);
		}
		fclose(fp);
	}
}

//注册模块
char *sign_up(char *id) {
	Users a, b;
	FILE *fp;
	char temp[20];

	printf("★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n");
	printf("★欢迎来到注册界面！白金手册全体员工欢迎您使用我们的产品！★\n");
	printf("★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n");
	printf("              ★★★★★★★★★★★★★★★★              \n");
	printf("              ★接下来我们将引导您完成注册！★              \n");
	printf("              ★★★★★★★★★★★★★★★★              \n\n\n");

	fp = fopen("..\\information\\users.txt", "rb+");
	fread(&b, sizeof(struct The_users), 1, fp);

	printf("请输入账号(最多不超过9个字符):");
	scanf("%9s", a.id);

	while (strlen(a.id) > 9) {
		printf("账号长度输入错误！请重新输入！\n");
		printf("请输入账号(最多不超过9个字符):");
		scanf("%c", a.id);
	}

	while (1) {
		if (strcmp(a.id, b.id)) {
			if (!feof(fp)) {
				fread(&b, sizeof(struct The_users), 1, fp);
			} else {
				break;
			}
		} else {
			printf("此用户名已存在！请选择登陆(输入数字1)或重新注册(输入数字2)！\n");
			int num_of_choices = 2;
			printf("请输入：");
			scanf("%d", &num_of_choices);
			do {
				if (num_of_choices != 1 && num_of_choices != 2) {
					printf("选择输入错误！请重新输入！\n");
					printf("请输入：");
					scanf("%c", &a.sex);
				}
			} while (num_of_choices == 1 || num_of_choices == 2);

			switch (num_of_choices) {
				case 1:
					fclose(fp);
					return id;
				default:
					break;
			}

			printf("请输入账号(最多不超过19个字符):");
			scanf("%19s", &a.id);
			do {
				if (strlen(a.id) > 20) {
					printf("账号长度输入错误！请重新输入！\n");
					printf("请输入账号(最多不超过19个字符):");
					scanf("%c", &a.id);
				}
			} while (strlen(a.id) <= 20);
		}
	}

	char path[1024];
	char st[] = "..\\information\\";
	sprintf(path, "%s%s", st, a.id);
	_mkdir(path);

	printf("\n★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n\n");

	printf("请输入姓名(最多不超过14个字符)：");
	scanf("%s", &a.name);
	do {
		if (sizeof(a.id) > 15) {
			printf("姓名长度输入错误！请重新输入！\n");
			printf("请输入姓名(最多不超过14个字符)：");
			scanf("%c", &a.sex);
		}
	} while (sizeof(a.id) <= 15);

	printf("\n★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n\n");

	printf("请输入性别(f(女)/m(男))：");
	scanf(" %c", &a.sex);
	do {
		if (a.sex != 'f' && a.sex != 'm') {
			printf("性别输入错误！请重新输入！\n");
			printf("请输入性别(f(女)/m(男))：");
			scanf("%c", &a.sex);
		}
	} while (a.sex != 'f' && a.sex != 'm');

	printf("\n★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n\n");

	printf("请输入电话号码：\n");
	scanf("%ld", &a.phone);

	printf("\n★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n\n");

	printf("请输入生日：\n");
	printf("请输入年份：");
	scanf("%ld", &a.birth.year);
	printf("请输入月份：\n");
	scanf("%ld", &a.birth.month);
	printf("请输入日份：\n");
	scanf("%ld", &a.birth.day);

	printf("\n★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n\n");

	printf("请输入密码:");
	scanf(" %s", &a.password);
	printf("请确认密码:");
	scanf(" %s", &temp);
	do {
		if (!strcmp(a.password, temp)) {
			fseek(fp, (a.phone - 1) * sizeof(struct The_users), SEEK_SET);
			fwrite(&a, sizeof(struct The_users), 1, fp);
			printf("\n\n\n          ★★★★★★★★★★★★★★★★★★★★\n");
			printf("          ★账号注册成功！即将自动登陆，请稍等！★\n");
			printf("          ★★★★★★★★★★★★★★★★★★★★\n\n");
			fclose(fp);
			id = a.id;
			return id;
		} else {
			printf("两次密码不匹配！请重新输入！\n");
			printf("请输入密码:");
			scanf("%s", &a.password);
			printf("请确认密码:");
			scanf("%s", &temp);
		}
	} while (1);
}

//登录模块
char *log_in(char *id) {
	Users a, b;
	FILE *fp;

	printf("★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n");
	printf("★欢迎来到注册界面！白金手册全体员工欢迎您使用我们的产品！★\n");
	printf("★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n\n\n");

	fp = fopen("..\\information\\users.txt", "rb");
	fread(&b, sizeof(struct The_users), 1, fp);

	printf("请输入账号(最多不超过9个字符):");
	scanf("%9s", &a.id);
	do {
		if (sizeof(a.id) > 10) {
			printf("账号长度输入错误！请重新输入！\n");
			printf("请输入账号(最多不超过9个字符):");
			scanf("%c", &a.id);
		}
	} while (sizeof(a.id) <= 10);
	while (1) {
		if (strcmp(a.id, b.id) == 0) {
			break;
		} else {
			if (!feof(fp)) {
				fread(&b, sizeof(struct The_users), 1, fp);
			} else {
				printf("此用户名不存在！请选择注册(输入数字1)或重新登陆(输入数字2)！\n");
				int num_of_choices = 2;
				printf("请输入：");
				scanf("%d", &num_of_choices);
				do {
					if (num_of_choices != 1 && num_of_choices != 2) {
						printf("选择输入错误！请重新输入！\n");
						printf("请输入：");
						scanf("%c", &a.sex);
					}
				} while (num_of_choices == 1 || num_of_choices == 2);

				switch (num_of_choices) {
					case 1:
						fclose(fp);
						return id;
						break;
					default:
						break;
				}

				printf("请输入账号(最多不超过19个字符):");
				scanf("%19s", &a.id);
				do {
					if (sizeof(a.id) > 20) {
						printf("账号长度输入错误！请重新输入！\n");
						printf("请输入账号(最多不超过19个字符):");
						scanf("%c", &a.id);
					}
				} while (sizeof(a.id) <= 20);
			}
		}
	}

	printf("\n★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n\n");

	printf("请输入密码:");
	scanf("%s", &a.password);
	do {
		if (strcmp(a.password, b.password) == 0) {
			fclose(fp);
			printf("\n\n\n          ★★★★★★★★★★★★★★★★★★★★\n");
			printf("          ★账号登陆成功！即将完成登陆，请稍等！★\n");
			printf("          ★★★★★★★★★★★★★★★★★★★★\n\n");
			id = a.id;
			return id;
		} else {
			printf("密码不正确!请重新输入密码：");
			scanf("%s", &a.password);
		}
	} while (strcmp(a.password, b.password) == 0);
}

//个人密码修改
void update_password(char *id) {
	Users b;
	FILE *fp;
	char temp[20];

	printf("★★★★★★★★★★★★★\n");
	printf("★欢迎来到密码修改界面！★\n");
	printf("★★★★★★★★★★★★★\n\n\n");

	fp = fopen("users.txt", "rb+");
	fread(&b, sizeof(struct The_users), 1, fp);
	//strcpy(a.id, id);
	while (1) {
		if (strcmp(id, b.id) == 0) {
			break;
		} else {
			if (!feof(fp)) {
				fread(&b, sizeof(struct The_users), 1, fp);
			} else {
				printf("系统错误！即将返回主界面！");
				return;
			}
		}
	}

	printf("请输入原密码：");
	scanf("%19s", &temp);
	do {
		if (strcmp(b.password, temp) == 0) {
			break;
		} else {
			printf("原密码不正确!请重新输入原密码：");
			scanf("%s", &temp);
		}
	} while (strcmp(b.password, temp) == 0);

	printf("请输入新密码：");
	scanf("%19s", &b.password);
	printf("请确认新密码：");
	scanf("%19s", &temp);
	do {
		if (!strcmp(b.password, temp)) {
			fp = fopen("users.txt", "a");
			fseek(fp, (b.phone - 1) * sizeof(struct The_users), SEEK_SET);
			fwrite(&b, sizeof(struct The_users), 1, fp);
			printf("\n\n\n          ★★★★★★★★★★★★★★★★★★★★\n");
			printf("          ★密码修改成功！即将完成同步，请稍等！★\n");
			printf("          ★★★★★★★★★★★★★★★★★★★★\n\n");
			fclose(fp);
			return;
		} else {
			printf("两次密码不匹配！请重新输入！\n");
			printf("请输入密码:");
			scanf("%s", &b.password);
			printf("请确认密码:");
			scanf("%s", &temp);
		}
	} while (1);

}

//个人信息查看
void show_information(char *id) {
	Users b;
	FILE *fp;

	printf("★★★★★★★★★★★★★\n");
	printf("★欢迎来到个人信息界面！★\n");
	printf("★★★★★★★★★★★★★\n\n\n");

	fp = fopen("..\\information\\users.txt", "rb");
	fread(&b, sizeof(struct The_users), 1, fp);
	//strcpy(a.id, id);
	while (1) {
		if (strcmp(id, b.id) == 0) {
			break;
		} else {
			if (!feof(fp)) {
				fread(&b, sizeof(struct The_users), 1, fp);
			} else {
				printf("系统错误！即将返回主界面！");
				return;
			}
		}
	}

	printf("%-20s%-20s%-15s%-5s%-15s%-15s%-15s%-15s\n", "ID", "Password", "Name", "Sex", "Phone", "Birth_Year",
	       "birth_Month", "Birth_Day");
	printf("%-20s%-20s%-15s%-5c%-15d%-15d%-15d%-15d\n", b.id, b.password, b.name, b.sex, b.phone, b.birth.year,
	       b.birth.month, b.birth.day);

	return;
}

//删除用户信息
void delete_information(char *id) {
	Users b;
	FILE *fp;

	printf("★★★★★★★★★★★★★\n");
	printf("★欢迎来到注销账号界面！★\n");
	printf("★★★★★★★★★★★★★\n\n\n");

	fp = fopen("..\\information\\users.txt", "rb+");
	fread(&b, sizeof(struct The_users), 1, fp);
	//strcpy(a.id, id);
	while (1) {
		if (strcmp(id, b.id) == 0) {
			break;
		} else {
			if (!feof(fp)) {
				fread(&b, sizeof(struct The_users), 1, fp);
			} else {
				printf("系统错误！即将返回主界面！");
				return;
			}
		}
	}

	printf("请再次确认是否注销账号(y表示是；n表示否)");
	char choice;
	scanf("%c", &choice);
	do {
		if (choice != 'y' && choice != 'n') {
			printf("选择输入错误！请重新输入！\n");
			printf("请再次确认是否注销账号(y表示是；n表示否)");
			scanf("%c", &choice);
		}
	} while (choice == 'y' || choice == 'n');
	switch (choice) {
		case 'y':
			break;
		case 'n':
			return;
		default:
			printf("系统异常，即将返回主界面！\n");
			return;
	}

	fseek(fp, (b.phone - 1) * sizeof(struct The_users), SEEK_SET);
	Users blank = {"", "", "", '0', 0, {0, 0, 0}};
	fwrite(&blank, sizeof(struct The_users), 1, fp);

	rmdir("D:\\test");


	char path[1024];
	char st0[] = "..\\information\\";

	char st1[] = "\\manage_url_of_web_page.txt";
	sprintf(path, "%s%s%s", st0, id, st1);
	int result1 = remove(path);

	char st2[] = "\\manage_address_list.txt";
	sprintf(path, "%s%s%s", st0, id, st2);
	int result2 = remove(path);

	char st3[] = "\\manage_diary.txt";
	sprintf(path, "%s%s%s", st0, id, st3);
	int result3 = remove(path);

	char st4[] = "\\/manage_password.txt";
	sprintf(path, "%s%s%s", st0, id, st4);
	int result4 = remove(path);

	char st5[] = "\\manage_schedule.txt";
	sprintf(path, "%s%s%s", st0, id, st5);
	int result5 = remove(path);

	sprintf(path, "%s%s", st0, id);
	rmdir(path);

	return;
}