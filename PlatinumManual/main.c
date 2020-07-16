#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "yyh.h"
#include "lyy.h"
#include "zyz.h"
#include "hyk.h"



void welcome();
int get_choice(int amount);

long long int id;


int main() {
	welcome();



	return 0;
}

void welcome() {
	int sign_up();
	int log_in();

	printf("\n");
	printf("--------------------------------------------------------------------------------------------\n");
	printf("|★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★|\n");
	printf("|★★★                                欢迎使用学生学籍管理系统                                ★★★|\n");
	printf("|★★★                                     请选择注册或者登陆                                      ★★★|\n");
	printf("|★★★                                       1. 注册      2. 登陆                                        ★★★|\n");
	printf("|★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★|\n");
	printf("--------------------------------------------------------------------------------------------\n");
	printf("\n");

	int num_of_choices = 2;
	int choice = get_choice(num_of_choices);

	if (choice == 1) {
		id = sign_up();
	} else if (choice == 2) {
		id = log_in();
	}
}

int get_choice(int amount) {
	int choice;
	scanf("%d", &choice);
	while (!(0 < choice && choice <= amount)) {
		printf("输出错误！\n请重新输出一个从1至%d的数。\n", amount);
		scanf("%d", &choice);
	}
	return choice;
}