#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "yyh.h"
#include "hyk.h"
#include "manage_password.h"
#include "manage_url_of_web_page.h"
#include "manage_address_list.h"
#include "manage_diary.h"


// 全局变量：用户id
char id[20] = "fail"; // 当前使用程序的用户的id

// 用户交互界面的函数声明
void welcome(); // 欢迎界面
int get_choice(int amount); // 获取choice选择
void main_menu(); // 主界面


int main() {
	// 若在命令行运行，则选择0B或0F；若在CLion内运行，则选择0E
	system("color 0B");

//	printf("软件加载中~~~");
//	Create_File();
//
//	/*
//	 * 若注册失败或登陆失败，两个函数均会将"fail"赋值给main.c的全局变量id；
//	 * 若注册成功或登陆成功，两个函数均会将当前用户的id赋值给main.c的全局变量id。
//	 */
//	do {
//		welcome();
//		system("pause");
//		system("CLS");
//	} while (!strcmp(id, "fail"));

	/*
	 * 在此设置死循环，
	 * 当用户从相应的功能模块退出后，将会继续弹出主界面，
	 * 让用户继续选择想要执行的操作。
	 * 当用户选择“退出”操作时，程序将调用exit(1)函数，退出程序（也退出循环）。
	 */
	while (1) {
		main_menu();
		system("pause");
		system("CLS");
	}

}

void welcome() {
	printf("\n");
	printf("★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n");
	printf("                         欢迎使用白金手册！！！\n");
	printf("                          请选择注册或者登陆\n");
	printf("                          1. 注册   2. 登陆\n");
	printf("                               3. 退出\n");
	printf("★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n");
	printf("\n");

	int num_of_choices = 3;
	int choice = get_choice(num_of_choices); // 获得用户所要进行的操作对应的选项

	// 根据choice进行选择
	switch (choice) {
		case 1:
			strcpy(id, sign_up(id));
			break;
		case 2:
			strcpy(id, log_in(id));
			break;
		case 3:
			printf("\n");
			printf("★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n");
			printf("                               期待您的下次使用！！！\n");
			printf("★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n");
			printf("\n");
			system("pause");
			exit(1);
		default:
			break;
	}
}

int get_choice(int amount) {
	int choice;
	printf("请输入：");
	scanf("%d", &choice);

	// 确保用户输入的数在1~amount之间
	while (!(0 < choice && choice <= amount)) {
		printf("输出错误！\n请重新输出一个从1至%d的数。\n", amount);
		scanf("%d", &choice);
	}
	return choice;
}

void main_menu() {
	printf("\n");
	printf("★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n");
	printf("                     欢迎进入白金手册主界面！！！\n");
	printf("                      请选择您要进行的操作：\n");
	printf("                         1. 网页夹管理\n");
	printf("                         2. 通讯录管理\n");
	printf("                         3. 日记管理\n");
	printf("                         4. 密码管理\n");
	printf("                         5. 日程管理\n");
	printf("                         6. 个人密码修改\n");
	printf("                         7. 个人信息查看\n");
	printf("                         8. 删除用户数据\n");
	printf("                         9. 退出程序\n");
	printf("★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n");
	printf("\n");

	int num_of_choices = 9;
	int choice = get_choice(num_of_choices); // 获得用户所要进行的操作对应的选项

	// 根据choice进行选择
	switch (choice) {
		case 1:
			manage_url_of_web_page(id);
			break;
		case 2:
			manage_address_list(id);
			break;
		case 3:
			manage_diary(id);
			break;
		case 4:
			manage_password(id);
			break;
		case 5:
			manage_schedule(id);
			break;
		case 6:
			update_password(id);
			break;
		case 7:
			show_information(id);
			break;
		case 8:
			delete_information(id);
			break;
		case 9:
			printf("\n");
			printf("★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n");
			printf("                               期待您的下次使用！！！\n");
			printf("★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n");
			printf("\n");
			system("pause");
			exit(1);
		default:
			break;
	}
}