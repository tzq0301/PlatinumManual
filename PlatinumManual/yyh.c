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

//���������û��˺�������ļ�
void Create_File() {
	FILE *fp;
	if ((fp = fopen("..\\information\\users.txt", "wb")) == NULL) {
		printf("�޷������ļ���\n");
		exit(0);
	} else {
		Users a = {"", "", "", '0', 0, {0, 0, 0}};
		for (long long int i = 1; i <= 1000000000; ++i) {
			fwrite(&a, sizeof(struct The_users), 1, fp);
		}
		fclose(fp);
	}
}

//ע��ģ��
char *sign_up(char *id) {
	Users a, b;
	FILE *fp;
	char temp[20];

	printf("�������������������������������\n");
	printf("�ﻶӭ����ע����棡�׽��ֲ�ȫ��Ա����ӭ��ʹ�����ǵĲ�Ʒ����\n");
	printf("�������������������������������\n");
	printf("              �����������������              \n");
	printf("              ����������ǽ����������ע�ᣡ��              \n");
	printf("              �����������������              \n\n\n");

	fp = fopen("..\\information\\users.txt", "rb+");
	fread(&b, sizeof(struct The_users), 1, fp);

	printf("�������˺�(��಻����9���ַ�):");
	scanf("%9s", a.id);

	while (strlen(a.id) > 9) {
		printf("�˺ų�������������������룡\n");
		printf("�������˺�(��಻����9���ַ�):");
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
			printf("���û����Ѵ��ڣ���ѡ���½(��������1)������ע��(��������2)��\n");
			int num_of_choices = 2;
			printf("�����룺");
			scanf("%d", &num_of_choices);
			do {
				if (num_of_choices != 1 && num_of_choices != 2) {
					printf("ѡ������������������룡\n");
					printf("�����룺");
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

			printf("�������˺�(��಻����19���ַ�):");
			scanf("%19s", &a.id);
			do {
				if (strlen(a.id) > 20) {
					printf("�˺ų�������������������룡\n");
					printf("�������˺�(��಻����19���ַ�):");
					scanf("%c", &a.id);
				}
			} while (strlen(a.id) <= 20);
		}
	}

	char path[1024];
	char st[] = "..\\information\\";
	sprintf(path, "%s%s", st, a.id);
	_mkdir(path);

	printf("\n�������������������������������\n\n");

	printf("����������(��಻����14���ַ�)��");
	scanf("%s", &a.name);
	do {
		if (sizeof(a.id) > 15) {
			printf("������������������������룡\n");
			printf("����������(��಻����14���ַ�)��");
			scanf("%c", &a.sex);
		}
	} while (sizeof(a.id) <= 15);

	printf("\n�������������������������������\n\n");

	printf("�������Ա�(f(Ů)/m(��))��");
	scanf(" %c", &a.sex);
	do {
		if (a.sex != 'f' && a.sex != 'm') {
			printf("�Ա�����������������룡\n");
			printf("�������Ա�(f(Ů)/m(��))��");
			scanf("%c", &a.sex);
		}
	} while (a.sex != 'f' && a.sex != 'm');

	printf("\n�������������������������������\n\n");

	printf("������绰���룺\n");
	scanf("%ld", &a.phone);

	printf("\n�������������������������������\n\n");

	printf("���������գ�\n");
	printf("��������ݣ�");
	scanf("%ld", &a.birth.year);
	printf("�������·ݣ�\n");
	scanf("%ld", &a.birth.month);
	printf("�������շݣ�\n");
	scanf("%ld", &a.birth.day);

	printf("\n�������������������������������\n\n");

	printf("����������:");
	scanf(" %s", &a.password);
	printf("��ȷ������:");
	scanf(" %s", &temp);
	do {
		if (!strcmp(a.password, temp)) {
			fseek(fp, (a.phone - 1) * sizeof(struct The_users), SEEK_SET);
			fwrite(&a, sizeof(struct The_users), 1, fp);
			printf("\n\n\n          ���������������������\n");
			printf("          ���˺�ע��ɹ��������Զ���½�����Եȣ���\n");
			printf("          ���������������������\n\n");
			fclose(fp);
			id = a.id;
			return id;
		} else {
			printf("�������벻ƥ�䣡���������룡\n");
			printf("����������:");
			scanf("%s", &a.password);
			printf("��ȷ������:");
			scanf("%s", &temp);
		}
	} while (1);
}

//��¼ģ��
char *log_in(char *id) {
	Users a, b;
	FILE *fp;

	printf("�������������������������������\n");
	printf("�ﻶӭ����ע����棡�׽��ֲ�ȫ��Ա����ӭ��ʹ�����ǵĲ�Ʒ����\n");
	printf("�������������������������������\n\n\n");

	fp = fopen("..\\information\\users.txt", "rb");
	fread(&b, sizeof(struct The_users), 1, fp);

	printf("�������˺�(��಻����9���ַ�):");
	scanf("%9s", &a.id);
	do {
		if (sizeof(a.id) > 10) {
			printf("�˺ų�������������������룡\n");
			printf("�������˺�(��಻����9���ַ�):");
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
				printf("���û��������ڣ���ѡ��ע��(��������1)�����µ�½(��������2)��\n");
				int num_of_choices = 2;
				printf("�����룺");
				scanf("%d", &num_of_choices);
				do {
					if (num_of_choices != 1 && num_of_choices != 2) {
						printf("ѡ������������������룡\n");
						printf("�����룺");
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

				printf("�������˺�(��಻����19���ַ�):");
				scanf("%19s", &a.id);
				do {
					if (sizeof(a.id) > 20) {
						printf("�˺ų�������������������룡\n");
						printf("�������˺�(��಻����19���ַ�):");
						scanf("%c", &a.id);
					}
				} while (sizeof(a.id) <= 20);
			}
		}
	}

	printf("\n�������������������������������\n\n");

	printf("����������:");
	scanf("%s", &a.password);
	do {
		if (strcmp(a.password, b.password) == 0) {
			fclose(fp);
			printf("\n\n\n          ���������������������\n");
			printf("          ���˺ŵ�½�ɹ���������ɵ�½�����Եȣ���\n");
			printf("          ���������������������\n\n");
			id = a.id;
			return id;
		} else {
			printf("���벻��ȷ!�������������룺");
			scanf("%s", &a.password);
		}
	} while (strcmp(a.password, b.password) == 0);
}

//���������޸�
void update_password(char *id) {
	Users b;
	FILE *fp;
	char temp[20];

	printf("��������������\n");
	printf("�ﻶӭ���������޸Ľ��棡��\n");
	printf("��������������\n\n\n");

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
				printf("ϵͳ���󣡼������������棡");
				return;
			}
		}
	}

	printf("������ԭ���룺");
	scanf("%19s", &temp);
	do {
		if (strcmp(b.password, temp) == 0) {
			break;
		} else {
			printf("ԭ���벻��ȷ!����������ԭ���룺");
			scanf("%s", &temp);
		}
	} while (strcmp(b.password, temp) == 0);

	printf("�����������룺");
	scanf("%19s", &b.password);
	printf("��ȷ�������룺");
	scanf("%19s", &temp);
	do {
		if (!strcmp(b.password, temp)) {
			fp = fopen("users.txt", "a");
			fseek(fp, (b.phone - 1) * sizeof(struct The_users), SEEK_SET);
			fwrite(&b, sizeof(struct The_users), 1, fp);
			printf("\n\n\n          ���������������������\n");
			printf("          �������޸ĳɹ����������ͬ�������Եȣ���\n");
			printf("          ���������������������\n\n");
			fclose(fp);
			return;
		} else {
			printf("�������벻ƥ�䣡���������룡\n");
			printf("����������:");
			scanf("%s", &b.password);
			printf("��ȷ������:");
			scanf("%s", &temp);
		}
	} while (1);

}

//������Ϣ�鿴
void show_information(char *id) {
	Users b;
	FILE *fp;

	printf("��������������\n");
	printf("�ﻶӭ����������Ϣ���棡��\n");
	printf("��������������\n\n\n");

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
				printf("ϵͳ���󣡼������������棡");
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

//ɾ���û���Ϣ
void delete_information(char *id) {
	Users b;
	FILE *fp;

	printf("��������������\n");
	printf("�ﻶӭ����ע���˺Ž��棡��\n");
	printf("��������������\n\n\n");

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
				printf("ϵͳ���󣡼������������棡");
				return;
			}
		}
	}

	printf("���ٴ�ȷ���Ƿ�ע���˺�(y��ʾ�ǣ�n��ʾ��)");
	char choice;
	scanf("%c", &choice);
	do {
		if (choice != 'y' && choice != 'n') {
			printf("ѡ������������������룡\n");
			printf("���ٴ�ȷ���Ƿ�ע���˺�(y��ʾ�ǣ�n��ʾ��)");
			scanf("%c", &choice);
		}
	} while (choice == 'y' || choice == 'n');
	switch (choice) {
		case 'y':
			break;
		case 'n':
			return;
		default:
			printf("ϵͳ�쳣���������������棡\n");
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