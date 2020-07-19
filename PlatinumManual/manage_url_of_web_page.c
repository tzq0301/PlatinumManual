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

// ע�͸ú��������Խ��δ֪ԭ��ı���
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
	FILE *fp; //����ָ���ļ��ṹ���ָ�����fp
	struct web *head = NULL; //��������ͷ���ָ��head������ֵΪ��
	struct web *p = NULL; //��������ڵ�ָ��p,p1��p���ڴ洢���ļ���ȡ�ĵ�ǰ�ڵ㣬p1���ڱ�ʶ����������̵�β�ڵ㣩
	struct web *p1 = NULL;
	unsigned int ret; //�����޷������ͱ���ret�����ڴ洢fread����ʵ�ʶ�ȡ�����ַ���
	int count = 0;  //�������ͱ���count�����ڴ洢����ڵ����
	fp = fopen(filename, "a+"); //��׷�Ӷ�д�ķ�ʽ���ļ������ļ�������ʱ�����ļ������ѷ���ֵ��ֵ��ָ�����fp
	if (fp == NULL) {  //��ʧ�ܣ�������
		perror("read open");
		exit(1);
	}
	p = (struct web *) malloc(sizeof(struct web)); //����һ���ڵ�ṹ���Ŀռ䣬��������ڵ�ָ��pָ������ռ�
	memset(p, 0, sizeof(struct web)); //��ʼ������Ŀռ䣨��0��䣩
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
		p = (struct web *) malloc(sizeof(struct web)); //����һ���ڵ�ṹ���Ŀռ䣬��������ڵ�ָ��pָ������ռ�
		memset(p, 0, sizeof(struct web)); //��ʼ������Ŀռ䣨��0��䣩
		ret = fread(p, sizeof(User_t), 1, fp); //��ȡ�ļ��е��������ݽṹ���С�����ݣ�һ���û�data��Ϣ��������Ľڵ�ṹ����
	}
	p1->next = NULL; //��β�ڵ��next��ֵΪ��
	fclose(fp); //�ر��ļ�
	return head; //��������ͷ���ָ��head��headΪһ���ǿ������ͷ��㣩
}

void insert_data(struct Userdata *pdata, char *address) {
	struct web *head = readFile(address); //��ȡ�ļ��е����ݲ�����Ϊ������ͷ���ָ�봫�ݸ�head
	struct web *p; //��������ڵ�ָ��p��p���ڴ洢������û����ݣ�
	struct web *p1 = head; //��������ڵ�ָ��p1��p1���ڴ洢��ǰ�ڵ㣩
	if (!p1) { //�ж�ͷ����Ƿ�Ϊ�գ�Ϊ��Ϊ�棨Ϊ�漴Ϊ�ļ�Ϊ�գ���ͷ���δ����ռ䣩
		head = (struct web *) malloc(sizeof(struct web)); //����һ���ڵ�ṹ���Ŀռ䣬��������ͷ�ڵ�ָ��headָ������ռ�
		memset(head, 0, sizeof(struct web)); //��ʼ������Ŀռ䣨��0��䣩
		head->data = *pdata; //��������û����ݸ�ֵ��ͷ����������
		head->next = NULL; //��ͷ���ָ����ֵΪNULL
	} else { //ͷ��㲻Ϊ�գ��ļ��д����û���Ϣ��
		while (p1->next) { //ѭ�����������ҵ�ָ����Ϊ�յĽڵ㣬������β�ڵ�
			p1 = p1->next;
		}
		p = (struct web *) malloc(sizeof(struct web)); //������һ���ڵ�ṹ���С�Ŀռ䣬��������ڵ�ָ��pָ������ռ�
		memset(p, 0, sizeof(struct web)); //��ʼ������Ŀռ䣨��0��䣩
		p->data = *pdata; //��������û����ݸ�ֵ������ڵ�p��������
		p->next = p1->next; //��β�ڵ��next��ֵ��p�ڵ��next�򣨽�NULL��ֵ��β����next��
		p1->next = p; //����β����next��ָ��ǰp�ڵ㣨β����Ϊp�ڵ㣬����p���뵽�����β����
	}
	save_file(address, head); //����������������ļ�
	free_file(head); //�ͷ�����
}

void save_file(const char *filename, struct web *p) {
	FILE *fp; //����ָ���ļ��ṹ���ָ�����fp
	fp = fopen(filename, "w+"); //��ÿ�δ�����ļ����ݵķ�ʽ�򿪿ɶ�д�ļ������ļ�������ʱ�����ļ������ѷ���ֵ��ֵ��ָ�����fp
	if (fp == NULL) { //��ʧ�ܣ�������
		perror("save open");
		exit(1);
	}
	while (p) { //ѭ������������û���Ϣ����
		fwrite(p, sizeof(User_t), 1, fp); //����ǰ���������û���Ϣ�ڵ��������д���ļ�
		p = p->next; //��ǰ�����ڵ�����ƶ�
	}
	fclose(fp); //�ر��ļ�
}

void free_file(struct web *p) {
	struct web *p1; //��������ڵ�ָ��p1��p1���ڴ洢Ҫ�ͷŵĵ�ǰ�ڵ㣩
	while (p) { //ѭ�����봫�������
		p1 = p; //����ǰ�����ڵ㸳ֵ��p1
		p = p->next; //��ǰ�����ڵ�����ƶ�
		free(p1); //�ͷ�p1�ڵ㣨���ͷ�����ƶ�ǰ�Ľڵ㣩
	}
}

void manage_web_index(char *id) {
	int choice_one = 0;
	printf("\n��ѡ���ܣ�\n");
	printf("1��ͨ����վ��ѯ�������޸ģ�\n");
	printf("2��ͨ����ע��ѯ�������޸ģ�\n");
	printf("3:��¼\n");
	printf("4:����\n");
	scanf("%d", &choice_one);
	while ((choice_one != 1) && (choice_one != 2) && (choice_one != 3) && (choice_one != 4)) {
		printf("û�����ѡ��Ŷ�ף�����һ��ɣ�");
		scanf("%d", &choice_one);
	}
	switch (choice_one) {
		case 1:
			printf("������������ѯ����վ���ƣ�");
			char webname[60];
			scanf("%s", webname);
			seeking_by_webname(id, webname);
			break;
		case 2:
			printf("������������ѯ�ı�ע��");
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
			printf("�����Զ����ء�");
			return;
	}
}

// �漰�ļ����޸�
void seeking_by_webname(char *id, char *webname) {
	int choice_two = 0;
	//ͨ��id�õ���ַ
	char fileaddress[60];
	strcpy(fileaddress, "..\\information\\");
	strcat(fileaddress, id);
	strcat(fileaddress, "\\manage_web.txt");
	struct web *head = readFile(fileaddress); //��ȡ�ļ��е����ݲ�����Ϊ������ͷ���ָ�봫�ݸ�head
	struct web *point = head; //��������ڵ�ָ��p��p���ڴ洢��ǰ�ڵ㣩������head��ֵ��p
	if (!point) { //�жϵ�ǰ��㣨ͷ��㣩�Ƿ�Ϊ�գ�Ϊ��Ϊ�棬���ļ�Ϊ�գ�
		printf("�㻹û�м�¼��Ŷ��o^^o��\n");
		return; //����0
	}
	while (point != NULL && strcmp(point->data.web, webname) != 0) { //ѭ�����������ҵ�Ҫ���ҵĽڵ�
		point = point->next;
	}
	if (point != NULL && strcmp(point->data.web, webname) == 0) {
		printf("������ѯ����վ�ǣ�%s\n", point->data.web);
		printf("������ѯ�ı�ע�ǣ�%s\n", point->data.remark);
		int judge;
		printf("����0���أ�����1�޸ģ�����2ɾ����\n");
		scanf("%d", &judge);
		switch (judge) {
			case 0:
				manage_web_index(id);
				break;
			case 1:
				printf("1���޸���վ\n");
				printf("2���޸ı�ע\n");
				scanf("%d", &choice_two);
				char new_webname[30]; // ��������1Ǩ������*
				char new_remarks[100]; // ��������2Ǩ������*
				switch (choice_two) {
					case 1:
//						char new_webname[30]; // ��������1Ǩ�����ⲿ*
						printf("�������µ���վ��\n");
						scanf("%s", new_webname);
						strcpy(point->data.web, new_webname);
						printf("�޸ĳɹ���");
						manage_web_index(id);
						break;
					case 2:
//						char new_remarks[100]; // ��������2Ǩ�����ⲿ*
						printf("�������µı�ע��\n");
						scanf("%s", new_remarks);
						strcpy(point->data.remark, new_remarks);
						printf("�޸ĳɹ���\n");
						manage_web_index(id);
						break;
					default:
						printf("��������Զ����ء�\n");
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
				printf("����������Զ����ء�\n");
				manage_web_index(id);
				break;
		}
	} else //��������Ҫ���ҵĽڵ�
	{
		printf("�Ҳ������ѷ��ء�");
		manage_web_index(id);
	}
	free_file(head); //�ͷ�����
}

// �漰�ļ����޸�
void seeking_by_remarks(char *id, char *remarks) {
	int choice_two = 0;
	//ͨ��id�õ���ַ
	char fileaddress[60];
	strcpy(fileaddress, "..\\information\\");
	strcat(fileaddress, id);
	strcat(fileaddress, "\\manage_web.txt");
	struct web *head = readFile(fileaddress); //��ȡ�ļ��е����ݲ�����Ϊ������ͷ���ָ�봫�ݸ�head
	struct web *point = head; //��������ڵ�ָ��p��p���ڴ洢��ǰ�ڵ㣩������head��ֵ��p
	if (!point) { //�жϵ�ǰ��㣨ͷ��㣩�Ƿ�Ϊ�գ�Ϊ��Ϊ�棬���ļ�Ϊ�գ�
		printf("�㻹û�м�¼��Ŷ��o^^o��\n");
		return; //����0
	}
	while (point != NULL && strcmp(point->data.remark, remarks) != 0) { //ѭ�����������ҵ�Ҫ���ҵĽڵ�
		point = point->next;
	}
	if (point != NULL && strcmp(point->data.remark, remarks) == 0) {
		printf("������ѯ����վ�ǣ�%s\n", point->data.web);
		printf("������ѯ�ı�ע�ǣ�%s\n", point->data.remark);
		int judge;
		printf("����0���أ�����1�޸ģ�����2ɾ����\n");
		scanf("%d", &judge);
		switch (judge) {
			case 0:
				manage_web_index(id);
				break;
			case 1:
				printf("1���޸���վ\n");
				printf("2���޸ı�ע\n");
				scanf("%d", &choice_two);
				char new_webname[30]; // ��������1Ǩ������*
				char new_remarks[100]; // ��������2Ǩ������*
				switch (choice_two) {
					case 1:
//						char new_webname[30]; // ��������1Ǩ�����ⲿ*
						printf("�������µ���վ��\n");
						scanf("%s", new_webname);
						strcpy(point->data.web, new_webname);
						printf("�޸ĳɹ���");
						manage_web_index(id);
						break;
					case 2:
//						char new_remarks[100]; // ��������2Ǩ�����ⲿ*
						printf("�������µı�ע��\n");
						scanf("%s", new_remarks);
						strcpy(point->data.remark, new_remarks);
						printf("�޸ĳɹ���\n");
						manage_web_index(id);
						break;
					default:
						printf("��������Զ����ء�\n");
						manage_web_index(id);
						break;
				}
				manage_web_index(id);
			case 2:
				del_data_by_remarks(remarks, fileaddress);
				manage_web_index(id);
				break;
			default:
				printf("����������Զ����ء�\n");
				manage_web_index(id);
				break;
		}
	} else { //��������Ҫ���ҵĽڵ�
		printf("�Ҳ������ѷ��ء�");
		manage_web_index(id);
	}
	free_file(head); //�ͷ�����
}

void del_data_by_webname(char *webname, char *address) {
	struct web *head = readFile(address); //��ȡ�ļ��е����ݲ�����Ϊ������ͷ���ָ�봫�ݸ�head
	struct web *p = head; //��������ڵ�ָ��p��p���ڴ洢��ǰ�ڵ㣩������head��ֵ��p
	struct web *pdel; //��������ڵ�ָ��pdel��pdel���ڴ洢Ҫɾ���Ľڵ㣩
	if (!head) { //�ж�ͷ����Ƿ�Ϊ�գ�Ϊ��Ϊ�棬���ļ�Ϊ�գ�
		printf("no have data delete!\n");
	} else if (!strcmp(p->data.web, webname)) { //�ж�ͷ����Ƿ�ΪҪɾ���Ľڵ㣨��Ϊ�棩
		pdel = p; //����ǰ�ڵ�p��ͷ���head����ֵ��pdel
		head = head->next; //��ͷ������һ���ڵ㸳ֵ��ͷ���
		free(pdel); //�ͷ�Ҫɾ���Ľڵ�
	} else { //ͷ��㲻Ϊ�գ���Ҫɾ���Ľڵ㲻��ͷ���
		while (p->next && strcmp(p->next->data.web, webname)) { //ѭ�����������ҵ�Ҫɾ���ڵ����һ���ڵ�
			p = p->next;
		}
		if (p->next) { //�ж�Ҫɾ���Ľڵ��Ƿ�Ϊ�գ���Ϊ�ռ�Ϊ�ҵ���Ϊ�棩��Ϊ�ռ�Ϊδ�ҵ�����������Ҫɾ���Ľڵ㣩��
			pdel = p->next; //��Ҫɾ���Ľڵ㣨��ǰ�ڵ����һ���ڵ㣩��ֵ��pdel
			p->next = pdel->next; //��Ҫɾ���ڵ����һ���ڵ㸳ֵ��Ҫɾ���ڵ����һ���ڵ㣨����ǰһ���ڵ�ͺ�һ���ڵ�������
			free(pdel); //�ͷ�Ҫɾ���Ľڵ�
		} else { //��������Ҫɾ���Ľڵ�
			printf("no have data delete!\n");
		}
	}
	save_file(address, head); //��ɾ�������������ļ�
	free_file(head); //�ͷ�����
}

void del_data_by_remarks(char *remarks, char *address) {
	struct web *head = readFile(address); //��ȡ�ļ��е����ݲ�����Ϊ������ͷ���ָ�봫�ݸ�head
	struct web *p = head; //��������ڵ�ָ��p��p���ڴ洢��ǰ�ڵ㣩������head��ֵ��p
	struct web *pdel; //��������ڵ�ָ��pdel��pdel���ڴ洢Ҫɾ���Ľڵ㣩
	if (!head) { //�ж�ͷ����Ƿ�Ϊ�գ�Ϊ��Ϊ�棬���ļ�Ϊ�գ�
		printf("no have data delete!\n");
	} else if (!strcmp(p->data.remark, remarks)) { //�ж�ͷ����Ƿ�ΪҪɾ���Ľڵ㣨��Ϊ�棩
		pdel = p; //����ǰ�ڵ�p��ͷ���head����ֵ��pdel
		head = head->next; //��ͷ������һ���ڵ㸳ֵ��ͷ���
		free(pdel); //�ͷ�Ҫɾ���Ľڵ�
	} else { //ͷ��㲻Ϊ�գ���Ҫɾ���Ľڵ㲻��ͷ���
		while (p->next && strcmp(p->next->data.remark, remarks)) { //ѭ�����������ҵ�Ҫɾ���ڵ����һ���ڵ�
			p = p->next;
		}
		if (p->next) { //�ж�Ҫɾ���Ľڵ��Ƿ�Ϊ�գ���Ϊ�ռ�Ϊ�ҵ���Ϊ�棩��Ϊ�ռ�Ϊδ�ҵ�����������Ҫɾ���Ľڵ㣩��
			pdel = p->next; //��Ҫɾ���Ľڵ㣨��ǰ�ڵ����һ���ڵ㣩��ֵ��pdel
			p->next = pdel->next; //��Ҫɾ���ڵ����һ���ڵ㸳ֵ��Ҫɾ���ڵ����һ���ڵ㣨����ǰһ���ڵ�ͺ�һ���ڵ�������
			free(pdel); //�ͷ�Ҫɾ���Ľڵ�
		} else { //��������Ҫɾ���Ľڵ�
			printf("no have data delete!\n");
		}
	}
	save_file(address, head); //��ɾ�������������ļ�
	free_file(head); //�ͷ�����
}

// �漰�ļ����޸�
void writing(char *id) {
	User_t data;
	char fileaddress[60];
	strcpy(fileaddress, "..\\information\\");
	strcat(fileaddress, id);
	//�ϲ�֮����Ҫ��ǰ���\\����
	strcat(fileaddress, "\\manage_web.txt");
	printf("��������վ��\n");
	scanf("%s", &data.web);
	printf("�����뱸ע��\n");
	scanf("%s", &data.remark);
	insert_data(&data, fileaddress);
	printf("�ɹ���¼���ѷ��ء�\n");
	manage_web_index(id);
}

void manage_url_of_web_page(char *id) {

	manage_web_index(id);

	return;
}