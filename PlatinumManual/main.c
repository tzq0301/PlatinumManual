#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "yyh.h"
#include "lyy.h"
#include "zyz.h"
#include "hyk.h"


char id[20] = "fail"; // ��ǰʹ�ó�����û���id

void welcome(); // ��ӭ����
int get_choice(int amount); // ��ȡchoiceѡ��
void main_menu(); // ������


int main() {

	/*
	 * ��ע��ʧ�ܻ��½ʧ�ܣ������������Ὣ-1��ֵ��main.c��ȫ�ֱ���id��
	 * ��ע��ɹ����½�ɹ��������������Ὣ��ǰ�û���id��ֵ��main.c��ȫ�ֱ���id��
	 */
	while (!strcmp(id, "fail")) {
		welcome();
	}

	/*
	 * �ڴ�������ѭ����
	 * ���û�����Ӧ�Ĺ���ģ���˳��󣬽���������������棬
	 * ���û�����ѡ����Ҫִ�еĲ�����
	 * ���û�ѡ���˳�������ʱ�����򽫵���exit(1)�������˳�����Ҳ�˳�ѭ������
	 */
	while (1) {
		main_menu();
	}

}

void welcome() {
	printf("\n");
	printf("�������������������������������������\n");
	printf("                         ��ӭʹ�ð׽��ֲᣡ����\n");
	printf("                           ��ѡ��ע����ߵ�½\n");
	printf("                             1. ע��      2. ��½\n");
	printf("�������������������������������������\n");
	printf("\n");

	int num_of_choices = 2;
	int choice = get_choice(num_of_choices); // ����û���Ҫ���еĲ�����Ӧ��ѡ��

	// ����choice����ѡ��
	switch (choice) {
		case 1:
			strcpy(id, sign_up());
			break;
		case 2:
			strcpy(id, log_in());
			break;
		default:
			break;
	}
}

int get_choice(int amount) {
	int choice;
	printf("�����룺");
	scanf("%d", &choice);

	// ȷ���û����������1~amount֮��
	while (!(0 < choice && choice <= amount)) {
		printf("�������\n���������һ����1��%d������\n", amount);
		scanf("%d", &choice);
	}
	return choice;
}

void main_menu() {
	printf("\n");
	printf("����������������������������������\n");
	printf("                       ��ӭ����׽��ֲ������棡����\n");
	printf("                            ��ѡ����Ҫ���еĲ�����\n");
	printf("                                 1. ��ҳ�й���\n");
	printf("                                 2. ͨѶ¼����\n");
	printf("                                 3. �ռǹ���\n");
	printf("                                 4. �������\n");
	printf("                                 5. �ճ̹���\n");
	printf("                                 6. ���������޸�\n");
	printf("                                 7. ������Ϣ�鿴\n");
	printf("                                 8. ɾ���û�����\n");
	printf("                                 9. �˳�����\n");
	printf("�����������������������������������\n");
	printf("\n");

	int num_of_choices = 9;
	int choice = get_choice(num_of_choices); // ����û���Ҫ���еĲ�����Ӧ��ѡ��

	// ����choice����ѡ��
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
			printf("����������������������������������������������\n");
			printf("                               �ڴ������´�ʹ�ã�����\n");
			printf("����������������������������������������������\n");
			printf("\n");
			exit(1);
		default:
			break;
	}
}