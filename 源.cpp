#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
#include<io.h>
typedef struct {                   
	//����ס����Ϣ�ṹ��
	char name[10];        //��������
	char gender[2];         //�����Ա�
	char phonenumber[20]; //��ϵ�绰
	int building;         //¥��
	int unit;            //��Ԫ��
	int room;         //�����
	float area;       //���
	int paymonth;    //��ҵ�µ���
	float publicpay;  //��̯ˮ���
}residentinfo;

typedef struct        //����ɷ���Ϣ�ṹ��
{
	char paytime[30];//�ɷ�ʱ��
	float pay;//�ɷѽ��
	int year; //�ɷѽ�ֹ���
	int month;//�ɷѽ�ֹ�·�
}payinfo;


//��ҳ�溯��
void menu();

//���ļ��е���ס����Ϣ����Ҫָ���ļ���·��
void importresidents(char path[]);

//������ҳ��
void querymenu();

//ͨ������Ų���ס����Ϣ
void querybyroom(int rnum);

//ͨ��������������ס����Ϣ
void querybyname(char nname[]);

//��ҵ�ɷ�
void payment();

//ͳ��δ�ɷ�ס����Ϣ
void overduecount();

//ͳ���ļ��е�����
//ס����Ϣ�е�ÿһ�д���һ��ס����Ϣ
//ͳ��ס����Ϣ�ļ��е��������Ա�ʾ��ס����
int countLines(FILE*file);



residentinfo residents[100];
int residentcount ; 
char* a = (char*)malloc(10 * sizeof(char));
int main()
{
	int choice;
	do
	{
		menu();
		printf("input your choice: ");
		scanf("%d", &choice);
			switch (choice)
			{
			case 1:
				char path[100];
				printf("��������Ҫ������ļ�·��:");
				scanf("%s", path);
				importresidents(path);
				break;
			case 2:
				querymenu();
				break;
			case 3:
				payment();
				break;
			case 4:
				overduecount();
				break;
			}
	} while (choice);
	return 0;

}
void menu()
{
	printf("                            ��������������ӭ������ҵ�ɷѳ��򡭡���������\n");
	printf("                             ------------------------------------------\n");
	printf("                            |           1.ס����Ϣ����                 |\n");
	printf("                            |           2.�ɷ������ѯ                 |\n");
 	printf("                            |           3.��ҵ�ɷ�                     |\n");
	printf("                            |           4.ͳ��δ���ڽɷ�ס��           |\n");
	printf("                            |           0.�˳�����                     |\n");
	printf("                             ------------------------------------------\n");
}
void importresidents(char path[])
{
	FILE* fp;
	fp=fopen( path, "r+");
	if ( NULL == fp)
		return ;
	residentcount = countLines(fp);
	for (int i = 0; i < residentcount; i++)
	{
		fscanf_s(fp, "%s %s %s %d %d %d %f %d %f\n",residents[i].name, 20, residents[i].gender, 20, 
			residents[i].phonenumber, 20, &residents[i].building,
			&residents[i].unit, &residents[i].room, &residents[i].area,
			&residents[i].paymonth, &residents[i].publicpay);
		sprintf(a + i, "./�ɷѼ�¼/%s%d",residents[i].name, residents[i].room);
		if (_access(a + i, 0)==-1)//�ж��ļ��Ƿ���ڣ�������Ż�0�������ڷŻ�-1��
		{
			FILE* fp2 = fopen(a + i, "a+");
			fprintf(fp2, "%s %s %s %d %d %d %f %d %f\n", residents[i].name, residents[i].gender,
				residents[i].phonenumber, residents[i].building,
				residents[i].unit, residents[i].room, residents[i].area,
				residents[i].paymonth, residents[i].publicpay);
			fclose(fp2);
		}
	}
	printf("����ɹ�������%d����Ϣ\n", residentcount);
	fclose(fp);
	printf("�����˻���ҳ��\n");
	system("pause");
}
void querymenu()
{
	 int choice;
	 do
	 {
		 printf("                            ��������������ӭ�����ɷ������ѯ������������\n");
		 if(!residentcount)
		 {
			 printf("ERROR,δ����ס����Ϣ\n");
			 system("pause");
			 return;
		 }
		 printf("                                        ��ѡ��               \n");
		 printf("                             ------------------------------------------\n");
		 printf("                            |           1.�����Ų�ѯ                   |\n");
		 printf("                            |           2.������������ѯ               |\n");
		 printf("                            |           3.������ҳ��                   |\n");
		 printf("                             ------------------------------------------\n");
		 scanf_s("%d", &choice);
		 switch (choice)
		 {
		 case 1:
			 int roomnum;
			 printf("�����뷿��:");
			 scanf("%d", &roomnum);
			 querybyroom(roomnum);
			 return;
		 case 2:
			 char nname[10];
			 printf("����������:");
			 scanf("%s", nname);
			 querybyname(nname);
			 return;
		 case 3:
			 return;
		 }
     }while (1);
}
void querybyroom(int rnum) 
{
	int i;
	for ( i = 0; i < residentcount; i++)
	{
		if (residents[i].room == rnum)
		{
			break;
		}
	}
	if (i == residentcount)
	{
		printf("�Ҳ����÷����");
	}
	sprintf(a + i, "./�ɷѼ�¼/%s%d", residents[i].name, residents[i].room);
	FILE* fp = fopen(a+i, "r+");
	if(countLines(fp)==1)
	{ 
		printf("û�нɷѼ�¼");
	}
	if (fp == NULL)
	{
		printf("error");
		return;
	} 
	char arr[100][100];
	int lines = countLines(fp);
	for (int j = 0; j < lines; j++)
	{
		fgets(arr[j], 100, fp);
		printf("%s", arr[j]);
	}
	fclose(fp);
	printf("�����˻�����ҳ��\n");
	system("pause");
}
void querybyname(char nname[])
{
	int i;
	for (i = 0; i < residentcount; i++)
	{
		if (!strcmp(nname,residents[i].name))
		{
			break;
		}
	}
	if (i == residentcount)
	{
		printf("�Ҳ���������");
	}
	sprintf(a + i, "./�ɷѼ�¼/%s%d", residents[i].name, residents[i].room);
	FILE* fp = fopen(a + i, "r+");
	if (fp == NULL)
	{
		printf("error");
		return;
	}
	char arr[100];
	fgets(arr, 100, fp);
	printf("%s", arr);
	fclose(fp);
	printf("�����˻�����ҳ��\n");
	system("pause");


}
void payment()
{
	char name[20];//�û�����
	int month = 0;//�ɷ�����
	printf("���������������");
	scanf("%s", name);
	int i = 0;
	for (i = 0; i < residentcount; i++)
	{
		if (!strcmp(residents[i].name, name))
		{
			break;
		}
	}
	printf("����ѡ����Ҫ���ɵ�����");
	scanf("%d", &month);//�����Ż�������Ҫȷ������������
	double pay;
	if (month < 12)
	{
		pay = (residents[i].area * residents[i].paymonth + residents[i].publicpay) * month;
		printf("����%s,�Ա�%s,�绰%s,¥��%d,��Ԫ��%d,�����%d,ס�����%f\n", residents[i].name, residents[i].gender, residents[i].phonenumber, residents[i].building, residents[i].unit, residents[i].room, residents[i].area);
		printf("��Ӧ�ý��ɵ���ҵ��Ϊ:%fԪ\n", pay);
	}
	else if (month > 11 and month < 24)
	{
		pay = ((residents[i].area * residents[i].paymonth + residents[i].publicpay) * month) * 0.95;
		printf("����%s,�Ա�%s,�绰%s,¥��%d,��Ԫ��%d,�����%d,ס�����%f\n", residents[i].name, residents[i].gender, residents[i].phonenumber, residents[i].building, residents[i].unit, residents[i].room, residents[i].area);
		printf("��Ӧ�ý��ɵ���ҵ��Ϊ:%fԪ\n", pay);
	}
	else
	{
		pay = ((residents[i].area * residents[i].paymonth + residents[i].publicpay) * month) * 0.9;
		printf("����%s,�Ա�%s,�绰%s,¥��%d,��Ԫ��%d,�����%d,ס�����%f\n", residents[i].name, residents[i].gender, residents[i].phonenumber, residents[i].building, residents[i].unit, residents[i].room, residents[i].area);
		printf("\n��Ӧ�ý��ɵ���ҵ��Ϊ:%fԪ\n", pay);
	}

	sprintf(a + i, "./�ɷѼ�¼/%s%d", residents[i].name, residents[i].room);
	FILE* fp = fopen(a + i, "a+");
	if (fp == NULL)
	{
		printf("error");
		return;
	}
	time_t current_time;
	struct tm* time_info;
	int current_month, current_year;
	char time1[28];
	// ��ȡ��ǰʱ��  
	time(&current_time);
	time_info = localtime(&current_time);

	// ��ȡ��ǰ�·�  ���
	current_month = time_info->tm_mon + 1; // �·ݴ�0��ʼ������������Ҫ��1
	current_year = time_info->tm_year;


	sprintf(time1, "%d��%d��%d��%d:%d:%d", 1900 + time_info->tm_year, 1 + time_info->tm_mon, time_info->tm_mday, time_info->tm_hour, time_info->tm_min, time_info->tm_sec);
	if (countLines(fp) == 1)
	{
		fprintf(fp, "���� %s ������ҵ�� %f Ԫ,��������: %d��%d��\n", time1, pay, current_year + 1900 + (current_month + month) / 12, (current_month + month) % 12);
	}
	else
	{
		int line = countLines(fp);
		char arr[100];
		int i;
		for (i = 0; i < line - 1; i++)
		{
			fgets(arr, 100, fp);
		} 
		payinfo payinfo;
		fscanf_s(fp,"���� %s ������ҵ�� %f Ԫ,��������: %d��%d��\n",payinfo.paytime,30, &payinfo.pay, &payinfo.year,&payinfo.month);
		fseek(fp, 0, SEEK_END);
		fprintf(fp, "���� %s ������ҵ�� %f Ԫ,��������: %d��%d��\n", time1, pay, payinfo.year+ (payinfo.month + month) / 12, (payinfo.month + month) % 12);
	}
		fclose(fp);
		system("pause");
}

void overduecount()
{

}

int countLines(FILE*file)
{
	char ch;
	long count = 0;

	while ((ch = fgetc(file)) != EOF) {
		if (ch == '\n') {
			count++;
		}
	}
	rewind(file);//�ļ�ָ���λ
	return count;
}

