//
// Created by TZQ on 2020/7/19.
//

#include "manage_password.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//index���������return�ĳ����˵�
/*�ټ����޸ĵ�ַ
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

// ע�͸ú����������Խ��δ֪ԭ��ı���
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
	FILE *fp; //����ָ���ļ��ṹ���ָ�����fp
	struct password_password *head = NULL; //��������ͷ���ָ��head������ֵΪ��
	struct password_password *p = NULL; //��������ڵ�ָ��p,p1��p���ڴ洢���ļ���ȡ�ĵ�ǰ�ڵ㣬p1���ڱ�ʶ����������̵�β�ڵ㣩
	struct password_password *p1 = NULL;
	unsigned int ret; //�����޷������ͱ���ret�����ڴ洢fread����ʵ�ʶ�ȡ�����ַ���
	int count = 0;  //�������ͱ���count�����ڴ洢����ڵ����
	fp = fopen(filename, "a+"); //��׷�Ӷ�д�ķ�ʽ���ļ������ļ�������ʱ�����ļ������ѷ���ֵ��ֵ��ָ�����fp
	if (fp == NULL) {  //��ʧ�ܣ�������
		printf("û���ҵ�����ļ���o(�i�n�i)o\n");
		exit(1);
	}
	p = (struct password_password *) malloc(sizeof(struct password_password)); //����һ���ڵ�ṹ���Ŀռ䣬��������ڵ�ָ��pָ������ռ�
	memset(p, 0, sizeof(struct password_password)); //��ʼ������Ŀռ䣨��0��䣩
	ret = fread(p, sizeof(User_t), 1, fp);    //��ȡ�ļ��е��������ݽṹ���С�����ݣ�һ���û�data��Ϣ��������Ľڵ�ṹ����
	if (!ret) {  //�ж϶�ȡ�����ַ����Ƿ�Ϊ0���ж��ļ��Ƿ�Ϊ�գ�Ϊ��Ϊ�棩��
		return head; //��������ͷ���ָ��head��headδ����ռ䣬ΪNULL��
	}
	while (ret) {  //�ж϶�ȡ�����ַ����Ƿ�Ϊ1���ж��ļ��Ƿ�Ϊ�գ��ǿ�Ϊ�棩��
		count++;  //�ڵ������1
		if (count == 1) {    //�ж��Ƿ�Ϊ��һ���ڵ㣨ͷ��㣩
			head = p; //����ǰ��ȡ���Ľڵ�p��ֵ��ͷ���
			p1 = p; //����ǰ��ȡ���Ľڵ���Ϊβ���
		}
		p1->next = p; //����ǰ��ȡ���Ľڵ�p��ֵ���ϴβ�����β���
		p1 = p; //����ǰ��ȡ���Ľڵ���Ϊβ�ڵ㣨β�ڵ�����ƶ�һ�Σ�
		p = (struct password_password *) malloc(sizeof(struct password_password)); //����һ���ڵ�ṹ���Ŀռ䣬��������ڵ�ָ��pָ������ռ�
		memset(p, 0, sizeof(struct password_password)); //��ʼ������Ŀռ䣨��0��䣩
		ret = fread(p, sizeof(User_t), 1, fp); //��ȡ�ļ��е��������ݽṹ���С�����ݣ�һ���û�data��Ϣ��������Ľڵ�ṹ����
	}
	p1->next = NULL; //��β�ڵ��next��ֵΪ��
	fclose(fp); //�ر��ļ�
	return head; //��������ͷ���ָ��head��headΪһ���ǿ������ͷ��㣩
}


void insert_data(struct Userdata_password *pdata, char *address) {
	struct password_password *head = readFile_password(address); //��ȡ�ļ��е����ݲ�����Ϊ������ͷ���ָ�봫�ݸ�head
	struct password_password *p; //��������ڵ�ָ��p��p���ڴ洢������û����ݣ�
	struct password_password *p1 = head; //��������ڵ�ָ��p1��p1���ڴ洢��ǰ�ڵ㣩
	if (!p1) { //�ж�ͷ����Ƿ�Ϊ�գ�Ϊ��Ϊ�棨Ϊ�漴Ϊ�ļ�Ϊ�գ���ͷ���δ����ռ䣩
		head = (struct password_password *) malloc(sizeof(struct password_password)); //����һ���ڵ�ṹ���Ŀռ䣬��������ͷ�ڵ�ָ��headָ������ռ�
		memset(head, 0, sizeof(struct password_password)); //��ʼ������Ŀռ䣨��0��䣩
		head->data = *pdata; //��������û����ݸ�ֵ��ͷ����������
		head->next = NULL; //��ͷ���ָ����ֵΪNULL
	} else { //ͷ��㲻Ϊ�գ��ļ��д����û���Ϣ��
		while (p1->next) { //ѭ�����������ҵ�ָ����Ϊ�յĽڵ㣬������β�ڵ�
			p1 = p1->next;
		}
		p = (struct password_password *) malloc(sizeof(struct password_password)); //������һ���ڵ�ṹ���С�Ŀռ䣬��������ڵ�ָ��pָ������ռ�
		memset(p, 0, sizeof(struct password_password)); //��ʼ������Ŀռ䣨��0��䣩
		p->data = *pdata; //��������û����ݸ�ֵ������ڵ�p��������
		p->next = p1->next; //��β�ڵ��next��ֵ��p�ڵ��next�򣨽�NULL��ֵ��β����next��
		p1->next = p; //����β����next��ָ��ǰp�ڵ㣨β����Ϊp�ڵ㣬����p���뵽�����β����
	}
	save_file_password(address, head); //����������������ļ�
	free_file_password(head); //�ͷ�����
}

void save_file_password(const char *filename, struct password_password *p) {
	FILE *fp; //����ָ���ļ��ṹ���ָ�����fp
	fp = fopen(filename, "w+"); //��ÿ�δ�����ļ����ݵķ�ʽ�򿪿ɶ�д�ļ������ļ�������ʱ�����ļ������ѷ���ֵ��ֵ��ָ�����fp
	if (fp == NULL) { //��ʧ�ܣ�������
		printf("�ļ���ʧ����o(�i�n�i)o\n");
		exit(1);
	}
	while (p) { //ѭ������������û���Ϣ����
		fwrite(p, sizeof(User_t), 1, fp); //����ǰ���������û���Ϣ�ڵ��������д���ļ�
		p = p->next; //��ǰ�����ڵ�����ƶ�
	}
	fclose(fp); //�ر��ļ�
}

void free_file_password(struct password_password *p) {
	struct password_password *p1; //��������ڵ�ָ��p1��p1���ڴ洢Ҫ�ͷŵĵ�ǰ�ڵ㣩
	while (p) { //ѭ�����봫�������
		p1 = p; //����ǰ�����ڵ㸳ֵ��p1
		p = p->next; //��ǰ�����ڵ�����ƶ�
		free(p1); //�ͷ�p1�ڵ㣨���ͷ�����ƶ�ǰ�Ľڵ㣩
	}
}

void manage_password_index(char *id) {
	int choice_one = 0;
	printf("\n�ܸ���Ϊ��������ѡ���ҵĹ��ܰȣ�(*^��^*)\n");
	printf("1��ͨ�������ѯ�������޸ģ�\n");
	printf("2��ͨ���˺Ų�ѯ�������޸ģ�\n");
	printf("3��ͨ�������ѯ�������޸ģ�\n");
	printf("4:����¼�¼\n");
	printf("5:������뿪o(�i�n�i)o\n");
	scanf("%d", &choice_one);
	while ((choice_one != 1) && (choice_one != 2) && (choice_one != 3) && (choice_one != 4) && (choice_one != 5)) {
		printf("û�����ѡ��Ŷ�ף��ѷ��أ�(��'��'��)");
		//�Ѵ˴���return�ĳɷ������˵�����һЩ
		return;
	}
	switch (choice_one) {
		case 1:
			printf("������������ѯ��������ƣ�");
			char app[30];
			scanf("%s", app);
			seeking_by_software(id, app);
			break;
		case 2:
			printf("������������ѯ���˺ţ�");
			char accountnumber[30];
			scanf("%s", accountnumber);
			seeking_by_account(id, accountnumber);
			break;
		case 3:
			printf("������������ѯ�����룺");
			char codenumber[30];
			scanf("%s", codenumber);
			seeking_by_code(id, codenumber);
			break;
		case 4:
			writing_password(id);
			break;
		case 5:
			//�˴���returnӦ�øĳ����˵��ĺ�������Ȼ��Ҫ�˺ܶ�βŻ��˳�����
			return;
			break;
		default:
			printf("û�����ѡ����Ѿ��Զ���������(��'��'��)");
			return;
			break;
	}
}

void seeking_by_software(char *id, char *app) {
	int choice_two = 0;
	//ͨ��id�õ���ַ
	char fileaddress[60];
	strcpy(fileaddress, "F:\\");
	//strcat(fileaddress, id);
	strcat(fileaddress, "manage_password.txt");
	struct password_password *head = readFile_password(fileaddress); //��ȡ�ļ��е����ݲ�����Ϊ������ͷ���ָ�봫�ݸ�head
	struct password_password *point = head; //��������ڵ�ָ��p��p���ڴ洢��ǰ�ڵ㣩������head��ֵ��p
	if (!point) { //�жϵ�ǰ��㣨ͷ��㣩�Ƿ�Ϊ�գ�Ϊ��Ϊ�棬���ļ�Ϊ�գ�
		printf("�����û�м�¼������o^^o��\n");
		return; //����0
	}
	while (point != NULL && strcmp(point->data.software, app) != 0) { //ѭ�����������ҵ�Ҫ���ҵĽڵ�
		point = point->next;
	}
	if (point != NULL && strcmp(point->data.software, app) == 0) {
		printf("����ǣ�%s\n", point->data.software);
		printf("�˺��ǣ�%s\n", point->data.account);
		printf("�����ǣ�%s\n", point->data.code);
		int judge;
		printf("����0���أ�����1�޸ģ�����2ɾ����\n");
		scanf("%d", &judge);
		switch (judge) {
			case 0:
				manage_password_index(id);
				break;
			case 1:
				printf("1���޸����\n");
				printf("2���޸��˺�\n");
				printf("3���޸�����\n");
				scanf("%d", &choice_two);
				char new_software[30]; // ��������1Ǩ������*
				char new_account[30]; // ��������2Ǩ������*
				char new_code[30]; // ��������3Ǩ������*
				switch (choice_two) {
					case 1:
//						char new_software[30];  // ��������1Ǩ�����ⲿ*
						printf("�������µ�������ƣ�\n");
						scanf("%s", new_software);
						del_data_by_software(point->data.software, fileaddress);
						strcpy(point->data.software, new_software);
						change_password(id, fileaddress, point->data.software, point->data.account, point->data.code);
						printf("�޸ĳɹ���(*^��^*)\n");
						manage_password_index(id);
						break;
					case 2:
//						char new_account[30];  // ��������2Ǩ�����ⲿ*
						printf("�������µ��˺ţ�\n");
						scanf("%s", new_account);
						del_data_by_account(point->data.account, fileaddress);
						strcpy(point->data.account, new_account);
						change_password(id, fileaddress, point->data.software, point->data.account, point->data.code);
						printf("�޸ĳɹ���(*^��^*)\n");
						manage_password_index(id);
						break;
					case 3:
//						char new_code[30]; // ��������3Ǩ�����ⲿ*
						printf("�������µ����룺\n");
						scanf("%s", new_code);
						del_data_by_code(point->data.code, fileaddress);
						strcpy(point->data.code, new_code);
						change_password(id, fileaddress, point->data.software, point->data.account, point->data.code);
						printf("�޸ĳɹ���(*^��^*)\n");
						manage_password_index(id);
						break;
					default:
						printf("����������ѡ��ǲ����Ե�o(�i�n�i)o\n");
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
				printf("����������ѡ��ǲ����Ե�o(�i�n�i)o\n");
				manage_password_index(id);
				break;
		}
	} else //��������Ҫ���ҵĽڵ�
	{
		printf("��û���ҵ�����������=(?�ϣ�*)))\n");
		manage_password_index(id);
	}
	free_file_password(head); //�ͷ�����
}

void seeking_by_account(char *id, char *accountnumber) {
	int choice_two = 0;
	//ͨ��id�õ���ַ
	char fileaddress[60];
	strcpy(fileaddress, "F:\\");
	//strcat(fileaddress, id);
	strcat(fileaddress, "manage_password.txt");
	struct password_password *head = readFile_password(fileaddress); //��ȡ�ļ��е����ݲ�����Ϊ������ͷ���ָ�봫�ݸ�head
	struct password_password *point = head; //��������ڵ�ָ��p��p���ڴ洢��ǰ�ڵ㣩������head��ֵ��p
	if (!point) { //�жϵ�ǰ��㣨ͷ��㣩�Ƿ�Ϊ�գ�Ϊ��Ϊ�棬���ļ�Ϊ�գ�
		printf("�����û�м�¼������o^^o��\n");
		return; //����0
	}
	while (point && strcmp(point->data.account, accountnumber)) { //ѭ�����������ҵ�Ҫ���ҵĽڵ�
		point = point->next;
	}
	if (point) {
		printf("����ǣ�%s\n", point->data.software);
		printf("�˺��ǣ�%s\n", point->data.account);
		printf("�����ǣ�%s\n", point->data.code);
		int judge;
		printf("����0���أ�����1�޸ģ�����2ɾ����\n");
		scanf("%d", &judge);
		switch (judge) {
			case 0:
				manage_password_index(id);
				break;
			case 1:
				printf("1���޸����\n");
				printf("2���޸��˺�\n");
				printf("3���޸�����\n");
				scanf("%d", &choice_two);
				char new_software[30]; // ��������1Ǩ������*
				char new_account[30]; // ��������2Ǩ������*
				char new_code[30]; // ��������3Ǩ������*
				switch (choice_two) {
					case 1:
//						char new_software[30];  // ��������1Ǩ�����ⲿ*
						printf("�������µ�������ƣ�\n");
						scanf("%s", new_software);
						strcpy(point->data.software, new_software);
						printf("�޸ĳɹ�(*^��^*)\n");
						manage_password_index(id);
						break;
					case 2:
//						char new_account[30];  // ��������2Ǩ�����ⲿ*
						printf("�������µ��˺ţ�\n");
						scanf("%s", new_account);
						strcpy(point->data.account, new_account);
						printf("�޸ĳɹ�(*^��^*)\n");
						manage_password_index(id);
						break;
					case 3:
//						char new_code[30];  // ��������3Ǩ�����ⲿ*
						printf("�������µ����룺\n");
						scanf("%s", new_code);
						strcpy(point->data.code, new_code);
						printf("�޸ĳɹ�(*^��^*)\n");
						manage_password_index(id);
						break;
					default:
						printf("����������ѡ��ǲ����Ե�o(�i�n�i)o\n");
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
				printf("����������ѡ��ǲ����Ե�o(�i�n�i)o\n");
				manage_password_index(id);
				break;
		}
	} else //��������Ҫ���ҵĽڵ�
	{
		printf("��û���ҵ�����˺Ű���=(?�ϣ�*)))\n");
		manage_password_index(id);
	}
	free_file_password(head); //�ͷ�����
}

void seeking_by_code(char *id, char *codenumber) {
	int choice_two = 0;
	//ͨ��id�õ���ַ
	char fileaddress[60];
	strcpy(fileaddress, "F:\\");
	//strcat(fileaddress, id);
	strcat(fileaddress, "manage_password.txt");
	struct password_password *head = readFile_password(fileaddress); //��ȡ�ļ��е����ݲ�����Ϊ������ͷ���ָ�봫�ݸ�head
	struct password_password *point = head; //��������ڵ�ָ��p��p���ڴ洢��ǰ�ڵ㣩������head��ֵ��p
	if (!point) { //�жϵ�ǰ��㣨ͷ��㣩�Ƿ�Ϊ�գ�Ϊ��Ϊ�棬���ļ�Ϊ�գ�
		printf("�����û�м�¼������o^^o��\n");
		return; //����0
	}
	while (point && strcmp(point->data.code, codenumber)) { //ѭ�����������ҵ�Ҫ���ҵĽڵ�
		point = point->next;
	}
	if (point) {
		printf("����ǣ�%s\n", point->data.software);
		printf("�˺��ǣ�%s\n", point->data.account);
		printf("�����ǣ�%s\n", point->data.code);
		int judge;
		printf("����0���أ�����1�޸ģ�����2ɾ����\n");
		scanf("%d", &judge);
		switch (judge) {
			case 0:
				manage_password_index(id);
				break;
			case 1:
				printf("1���޸����\n");
				printf("2���޸��˺�\n");
				printf("3���޸�����\n");
				scanf("%d", &choice_two);
				char new_software[30]; // ��������1Ǩ������*
				char new_account[30]; // ��������2Ǩ������*
				char new_code[30]; // ��������3Ǩ������*
				switch (choice_two) {
					case 1:
//						char new_software[30];  // ��������1Ǩ�����ⲿ*
						printf("�������µ�������ƣ�\n");
						scanf("%s", new_software);
						strcpy(point->data.software, new_software);
						printf("�޸ĳɹ�(*^��^*)\n");
						manage_password_index(id);
						break;
					case 2:
//						char new_account[30];  // ��������2Ǩ�����ⲿ*
						printf("�������µ��˺ţ�\n");
						scanf("%s", new_account);
						strcpy(point->data.account, new_account);
						printf("�޸ĳɹ�(*^��^*)\n");
						manage_password_index(id);
						break;
					case 3:
//						char new_code[30];  // ��������3Ǩ�����ⲿ*
						printf("�������µ����룺\n");
						scanf("%s", new_code);
						strcpy(point->data.code, new_code);
						printf("�޸ĳɹ�(*^��^*)\n");
						manage_password_index(id);
						break;
					default:
						printf("����������ѡ��ǲ����Ե�o(�i�n�i)o\n");
						manage_password_index(id);
						break;
				}
				break;
			case 2:
				del_data_by_code(codenumber, fileaddress);
				manage_password_index(id);
				break;
			default:
				printf("����������ѡ��ǲ����Ե�o(�i�n�i)o\n");
				manage_password_index(id);
				break;
		}
	} else //��������Ҫ���ҵĽڵ�
	{
		printf("��û���ҵ�������밥��=(?�ϣ�*)))\n");
		manage_password_index(id);
	}
	free_file_password(head); //�ͷ�����
}

void del_data_by_software(char *name, char *address) {
	struct password_password *head = readFile_password(address); //��ȡ�ļ��е����ݲ�����Ϊ������ͷ���ָ�봫�ݸ�head
	struct password_password *p = head; //��������ڵ�ָ��p��p���ڴ洢��ǰ�ڵ㣩������head��ֵ��p
	struct password_password *pdel; //��������ڵ�ָ��pdel��pdel���ڴ洢Ҫɾ���Ľڵ㣩
	if (!head) { //�ж�ͷ����Ƿ�Ϊ�գ�Ϊ��Ϊ�棬���ļ�Ϊ�գ�
		printf("�����û�м�¼������o^^o��\n");
	} else if (!strcmp(p->data.software, name)) { //�ж�ͷ����Ƿ�ΪҪɾ���Ľڵ㣨��Ϊ�棩
		pdel = p; //����ǰ�ڵ�p��ͷ���head����ֵ��pdel
		head = head->next; //��ͷ������һ���ڵ㸳ֵ��ͷ���
		free(pdel); //�ͷ�Ҫɾ���Ľڵ�
	} else { //ͷ��㲻Ϊ�գ���Ҫɾ���Ľڵ㲻��ͷ���
		while (p->next && strcmp(p->next->data.software, name)) { //ѭ�����������ҵ�Ҫɾ���ڵ����һ���ڵ�
			p = p->next;
		}
		if (p->next) { //�ж�Ҫɾ���Ľڵ��Ƿ�Ϊ�գ���Ϊ�ռ�Ϊ�ҵ���Ϊ�棩��Ϊ�ռ�Ϊδ�ҵ�����������Ҫɾ���Ľڵ㣩��
			pdel = p->next; //��Ҫɾ���Ľڵ㣨��ǰ�ڵ����һ���ڵ㣩��ֵ��pdel
			p->next = pdel->next; //��Ҫɾ���ڵ����һ���ڵ㸳ֵ��Ҫɾ���ڵ����һ���ڵ㣨����ǰһ���ڵ�ͺ�һ���ڵ�������
			free(pdel); //�ͷ�Ҫɾ���Ľڵ�
		} else { //��������Ҫɾ���Ľڵ�
			printf("��û���ҵ�����������=(?�ϣ�*)))\n");
		}
	}
	save_file_password(address, head); //��ɾ�������������ļ�
	free_file_password(head); //�ͷ�����
}

void del_data_by_account(char *name, char *address) {
	struct password_password *head = readFile_password(address); //��ȡ�ļ��е����ݲ�����Ϊ������ͷ���ָ�봫�ݸ�head
	struct password_password *p = head; //��������ڵ�ָ��p��p���ڴ洢��ǰ�ڵ㣩������head��ֵ��p
	struct password_password *pdel; //��������ڵ�ָ��pdel��pdel���ڴ洢Ҫɾ���Ľڵ㣩
	if (!head) { //�ж�ͷ����Ƿ�Ϊ�գ�Ϊ��Ϊ�棬���ļ�Ϊ�գ�
		printf("�����û�м�¼������o^^o��\n");
	} else if (!strcmp(p->data.account, name)) { //�ж�ͷ����Ƿ�ΪҪɾ���Ľڵ㣨��Ϊ�棩
		pdel = p; //����ǰ�ڵ�p��ͷ���head����ֵ��pdel
		head = head->next; //��ͷ������һ���ڵ㸳ֵ��ͷ���
		free(pdel); //�ͷ�Ҫɾ���Ľڵ�
	} else { //ͷ��㲻Ϊ�գ���Ҫɾ���Ľڵ㲻��ͷ���
		while (p->next && strcmp(p->next->data.account, name)) { //ѭ�����������ҵ�Ҫɾ���ڵ����һ���ڵ�
			p = p->next;
		}
		if (p->next) { //�ж�Ҫɾ���Ľڵ��Ƿ�Ϊ�գ���Ϊ�ռ�Ϊ�ҵ���Ϊ�棩��Ϊ�ռ�Ϊδ�ҵ�����������Ҫɾ���Ľڵ㣩��
			pdel = p->next; //��Ҫɾ���Ľڵ㣨��ǰ�ڵ����һ���ڵ㣩��ֵ��pdel
			p->next = pdel->next; //��Ҫɾ���ڵ����һ���ڵ㸳ֵ��Ҫɾ���ڵ����һ���ڵ㣨����ǰһ���ڵ�ͺ�һ���ڵ�������
			free(pdel); //�ͷ�Ҫɾ���Ľڵ�
		} else { //��������Ҫɾ���Ľڵ�
			printf("��û���ҵ�����˺Ű���=(?�ϣ�*)))\n");
		}
	}
	save_file_password(address, head); //��ɾ�������������ļ�
	free_file_password(head); //�ͷ�����
}

void del_data_by_code(char *name, char *address) {
	struct password_password *head = readFile_password(address); //��ȡ�ļ��е����ݲ�����Ϊ������ͷ���ָ�봫�ݸ�head
	struct password_password *p = head; //��������ڵ�ָ��p��p���ڴ洢��ǰ�ڵ㣩������head��ֵ��p
	struct password_password *pdel; //��������ڵ�ָ��pdel��pdel���ڴ洢Ҫɾ���Ľڵ㣩
	if (!head) { //�ж�ͷ����Ƿ�Ϊ�գ�Ϊ��Ϊ�棬���ļ�Ϊ�գ�
		printf("�����û�м�¼������o^^o��\n");
	} else if (!strcmp(p->data.code, name)) { //�ж�ͷ����Ƿ�ΪҪɾ���Ľڵ㣨��Ϊ�棩
		pdel = p; //����ǰ�ڵ�p��ͷ���head����ֵ��pdel
		head = head->next; //��ͷ������һ���ڵ㸳ֵ��ͷ���
		free(pdel); //�ͷ�Ҫɾ���Ľڵ�
	} else { //ͷ��㲻Ϊ�գ���Ҫɾ���Ľڵ㲻��ͷ���
		while (p->next && strcmp(p->next->data.code, name)) { //ѭ�����������ҵ�Ҫɾ���ڵ����һ���ڵ�
			p = p->next;
		}
		if (p->next) { //�ж�Ҫɾ���Ľڵ��Ƿ�Ϊ�գ���Ϊ�ռ�Ϊ�ҵ���Ϊ�棩��Ϊ�ռ�Ϊδ�ҵ�����������Ҫɾ���Ľڵ㣩��
			pdel = p->next; //��Ҫɾ���Ľڵ㣨��ǰ�ڵ����һ���ڵ㣩��ֵ��pdel
			p->next = pdel->next; //��Ҫɾ���ڵ����һ���ڵ㸳ֵ��Ҫɾ���ڵ����һ���ڵ㣨����ǰһ���ڵ�ͺ�һ���ڵ�������
			free(pdel); //�ͷ�Ҫɾ���Ľڵ�
		} else { //��������Ҫɾ���Ľڵ�
			printf("��û���ҵ�������밥��=(?�ϣ�*)))\n");
		}
	}
	save_file_password(address, head); //��ɾ�������������ļ�
	free_file_password(head); //�ͷ�����
}

void writing_password(char *id) {
	User_t data;
	char fileaddress[60];
	strcpy(fileaddress, "F:\\");
	//strcat(fileaddress, id);
	//�ϲ�֮����Ҫ��ǰ���\\����
	strcat(fileaddress, "manage_password.txt");
	printf("�����������\n");
	scanf("%s", &data.software);
	printf("�������˺ţ�\n");
	scanf("%s", &data.account);
	printf("���������룺\n");
	scanf("%s", &data.code);
	insert_data(&data, fileaddress);
	printf("�ɹ���¼���ѷ���(*^��^*)\n");
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
