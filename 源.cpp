#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
#include<io.h>
 
typedef struct        //����ɷ���Ϣ�ṹ��
{
	char paytime[30];//�ɷ�ʱ��
	double pay;//�ɷѽ��
	int year; //�ɷѽ�ֹ��� 
	int month;//�ɷѽ�ֹ�·�
}payinfo;

typedef struct {                   
	//����ס����Ϣ�ṹ��
	char name[10];        //��������
	char gender[3];         //�����Ա�
	char phonenumber[20]; //��ϵ�绰
	int building;         //¥��
	int unit;            //��Ԫ��
	int room;         //�����
	float area;       //���
	int paymonth;    //��ҵ�µ���
	float publicpay;  //��̯ˮ���
	payinfo lastpay;//���һ�νɷѵ�����
}residentinfo;




//��ҳ�溯��
void menu();

//���ļ��е���ס����Ϣ����Ҫָ���ļ���·��
void importresidents(char path[],residentinfo re[]);

//������ҳ��
void querymenu(residentinfo re[]);

//ͨ������Ų���ס����Ϣ
void querybyroom(int rnum,residentinfo re[]);

//ͨ��������������ס����Ϣ
void querybyname(char nname[] ,residentinfo re[]);

//��ҵ�ɷ�
void payment(residentinfo re[]);

//ͳ��δ�ɷ�ס����Ϣ
void overduecount(residentinfo re[]);

//ͳ���ļ��е�����
//ס����Ϣ�е�ÿһ�д���һ��ס����Ϣ
//ͳ��ס����Ϣ�ļ��е��������Ա�ʾ��ס����
int countLines(FILE*file);


//����ס�����Թ���
void Announcement();

//�ж��Ƿ��ǹ���Ա
//1:�ǹ���Ա
//0:���ǹ���Ա
int adm();



int residentcount=0;
int main()
{
	if (!adm())
	{
		return 0 ;

	}
	int choice;
	residentinfo residents[100]; //����ס�����飬���ס����Ϣ
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
				importresidents(path,residents);
				break;
			case 2:
				querymenu(residents);
				break;
			case 3:
				payment(residents);
				break;
			case 4:
				overduecount(residents);
				break;
			case 5:

				Announcement();
				break;
			default:
				if (choice)
				{
					printf("�������\n");
					printf("����������\n");
					system("pause");

				}		
				break;
			}
	} while (choice);
	return 0;

}
void menu()
{
	system("cls");
	printf("                            ��������������ӭ������ҵ�ɷѳ��򡭡���������\n");
	printf("                             ------------------------------------------\n");
	printf("                            |           1.ס����Ϣ����                 |\n");
	printf("                            |           2.�ɷ������ѯ                 |\n");
 	printf("                            |           3.��ҵ�ɷ�                     |\n");
	printf("                            |           4.ͳ��δ���ڽɷ�ס��           |\n");
	printf("                            |           5.������¹���                 |\n");
	printf("                            |           0.�˳�����                     |\n");
	printf("                             ------------------------------------------\n");
}
void importresidents(char path[],residentinfo re[])
{
	FILE* fp;
	char a[30];
	fp=fopen( path, "r+");
	if ( NULL == fp)
		return ;
	residentcount = countLines(fp);
	for (int i = 0; i < residentcount; i++)
	{
		fscanf_s(fp, "%s %s %s %d %d %d %f %d %f %d %d\n",
			re[i].name, 20, re[i].gender,3,
			re[i].phonenumber,20, &re[i].building,
			&re[i].unit, &re[i].room, &re[i].area,
			&re[i].paymonth, &re[i].publicpay,
			&re[i].lastpay.year,&re[i].lastpay.month);

		//ÿһ��ס����Ϣ����һ��ר�ŵĽɷѼ�¼�ļ�
		//�ļ��Ի��������ͷ���Ź���
		sprintf(a, "./�ɷѼ�¼/%s%d.txt",re[i].name, re[i].room);
		if (_access(a , 0)==-1)//�ж��ļ��Ƿ���ڣ�������Ż�0�������ڷŻ�-1��
		{
			FILE* fp2 = fopen(a , "a+");
			fprintf(fp2, "%s %s %s %d %d %d %.2f %d %.2f\n", 
				re[i].name, re[i].gender,
				re[i].phonenumber, re[i].building,
				re[i].unit, re[i].room, re[i].area,
				re[i].paymonth, re[i].publicpay);
			fclose(fp2);
		}
	}
	printf("����ɹ�������%d����Ϣ\n", residentcount);
	fclose(fp);
	printf("�����˻���ҳ��\n");
	system("pause");
	return;
}


void querymenu(residentinfo re[])
{
	 int choice;
	 do
	 {
		 printf("                            ��������������ӭ�����ɷ������ѯ������������\n");
		 if(residentcount==0)
		 {
			 printf("ERROR,δ����ס����Ϣ\n");
			 printf("����������������\n");
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
			 querybyroom(roomnum,re);
			 return;
		 case 2:
			 char nname[10];
			 printf("����������:");
			 scanf("%s", nname);
			 querybyname(nname,re);
			 return;
		 case 3:
			 return;
		 default:
			 printf("�������\n");
			 printf("����������\n");
			 system("pause");
		 }
     }while (1);
}
void querybyroom(int rnum,residentinfo re[])
{
	int i;
	char a[30];
	//����ס��������Ԫ��
    //�������д洢�ķ��ź����뷿����ͬʱbreak
    //��¼��ʱס������Ϣ����i��ֵ
	for ( i = 0; i < residentcount ; i++)
	{
		if (re[i].room == rnum)
		{
			break;
		}
	}
	if (i == residentcount)
	{
		printf("�Ҳ����÷����\n");
		printf("�����˻�����ҳ��\n");
		system("pause");
		return;
	}
	sprintf(a, "./�ɷѼ�¼/%s%d.txt", re[i].name, re[i].room);
	FILE* fp = fopen(a, "r+");
	if (fp == NULL)
	{
		printf("error");
		return;
	} 
	int line = countLines(fp);

	//�ɷѼ�¼��ֻ��һ�У�ֻ������ס��������Ϣ
	//���������ɷѵ���Ϣ
	if (line == 1)               	                       
	{
		printf("û�нɷѼ�¼\n");
		printf("�����˻�����ҳ��\n");
		system("pause");
		fclose(fp);
		return;
	}
	else 
	{
		//��ȡ�ļ��е�ÿһ�в����
		//�����ɽɷѼ�¼
		char inf[100][100];
		for (int j = 0; j < line; j++)
		{
			fgets(inf[j], 100, fp);
			printf("%s", inf[j]);
		}
		fclose(fp);
	}

	printf("�����˻�����ҳ��\n");
	system("pause");
	return;
}
void querybyname(char nname[],residentinfo re[])
{
	int i;
	char a[30];
	for (i = 0; i < residentcount; i++)
	{
		if (!strcmp(nname,re[i].name))
		{
			break;
		}
	}
	//Խ�缴ʧ��
	if (i == residentcount)
	{
		printf("�Ҳ���������\n");
		printf("�����˻�����ҳ��\n");
		system("pause");
		return;
	}
	sprintf(a, "./�ɷѼ�¼/%s%d.txt", re[i].name, re[i].room);
	FILE* fp = fopen(a, "r+");
	if (fp == NULL)
	{
		printf("error");
		return;
	}
	int line = countLines(fp);

	//�ɷѼ�¼��ֻ��һ�У�ֻ������ס��������Ϣ
	//���������ɷѵ���Ϣ
	if (line == 1)               	
	{
		printf("û�нɷѼ�¼\n");
		printf("�����˻�����ҳ��\n");
		system("pause");
		fclose(fp);
		return;
	}
	else
	{
		//��ȡ�ļ��е�ÿһ�в����
		//�����ɽɷѼ�¼
		char inf[100][100];
		for (int j = 0; j < line; j++)
		{
			fgets(inf[j], 100, fp);
			printf("%s", inf[j]);
		}
		fclose(fp);
	}

	printf("�����˻�����ҳ��\n");
	system("pause");
	return;


}
void payment(residentinfo re[])
{
	char name[10];//�û�����
	int month = 0;//�ɷ�����
	double pay; //��Ҫ֧������ҵ��
	printf("���������������");
	scanf("%s", name);
	int i = 0;

	//����ס��������Ԫ��
	//�������д洢������������������ͬʱbreak
	//��¼��ʱס������Ϣ����i��ֵ
	for (i = 0; i < residentcount; i++)
	{
		if (!strcmp(re[i].name, name))  
		{
			break;
		}
	}
	//�ж�Խ��
	//Խ�����ʾ�洢��ס����Ϣ��û�и�ס��
	if (i == residentcount)
	{
		printf("û�и�ס����Ϣ,��˶���Ϣ\n");
		system("pause");
		return;
	}
	printf("������Ҫ���ɵ�����:");
	scanf("%d", &month);
	
	//�����Ż�������Ҫ�ж�����������
	//һ�ν���һ��������ҵ�ѵ�ס����9.5���Żݡ�
	// һ�ν�������������ҵ�ѵ�ס����9���Żݡ�
	if (month < 12)
	{
		pay = (re[i].area * re[i].paymonth + re[i].publicpay) * month;
	 	
		printf("*********************************\n");
		printf("��Ļ�����Ϣ:\n");
		printf("����:%s\n",re[i].name);
		printf("�Ա�:%s\n",re[i].gender);
		printf("��ϵ��ʽ:%s\n",re[i].phonenumber);
		printf("¥��:%d\n",re[i].building);
		printf("��Ԫ��:%d\n",re[i].unit);
		printf("�����:%d\n",re[i].room);
		printf("ס�����:%.2f\n",re[i].area);
		printf("*********************************\n");
		printf("��Ӧ�ý��ɵ���ҵ��Ϊ:%.2fԪ\n", pay);
	}
	else if (month > 11 and month < 24)
	{
		pay = ((re[i].area * re[i].paymonth + re[i].publicpay) * month) * 0.95;
		printf("*********************************\n");
		printf("��Ļ�����Ϣ:\n");
		printf("����:%s\n", re[i].name);
		printf("�Ա�:%s\n", re[i].gender);
		printf("��ϵ��ʽ:%s\n", re[i].phonenumber);
		printf("¥��:%d\n", re[i].building);
		printf("��Ԫ��:%d\n", re[i].unit);
		printf("�����:%d\n", re[i].room);
		printf("ס�����:%.2f\n", re[i].area);
		printf("*********************************\n");
		printf("��Ӧ�ý��ɵ���ҵ��Ϊ:%.2fԪ\n", pay);
	}
	else
	{
		pay = ((re[i].area * re[i].paymonth + re[i].publicpay) * month) * 0.9;
		printf("*********************************\n");
		printf("��Ļ�����Ϣ:\n");
		printf("����:%s\n", re[i].name);
		printf("�Ա�:%s\n", re[i].gender);
		printf("��ϵ��ʽ:%s\n", re[i].phonenumber);
		printf("¥��:%d\n", re[i].building);
		printf("��Ԫ��:%d\n", re[i].unit);
		printf("�����:%d\n", re[i].room);
		printf("ס�����:%.2f\n", re[i].area);
		printf("*********************************\n");
		printf("��Ӧ�ý��ɵ���ҵ��Ϊ:%.2fԪ\n", pay);
	}
	char a[30];
	sprintf(a, "./�ɷѼ�¼/%s%d.txt", re[i].name, re[i].room);
	FILE* fp = fopen(a, "a+");
	if (fp == NULL)
	{
		printf("error");
		return;
	}

	
	//��ȡ��ǰ��ʱ����Ϊ�ɷ�ʱ��

	time_t current_time;
	struct tm* time_info;
	int current_month, current_year;
	// ��ȡ��ǰʱ��  
	time(&current_time);
	time_info = localtime(&current_time);
	// ��ȡ��ǰ�·�  ���
	// �·ݴ�0��ʼ������������Ҫ��1
	//��������1900����㣬������Ҫ��1900
	current_month = time_info->tm_mon + 1; 
	
	current_year = time_info->tm_year+1900;

	char nowtime[28];
	sprintf(nowtime, "%d��%d��%d��%d:%d:%d", 1900 + time_info->tm_year, 1 + time_info->tm_mon, time_info->tm_mday, time_info->tm_hour, time_info->tm_min, time_info->tm_sec);

	//��¼�ļ��е�����
	//����==1��ʾ�޽ɷѼ�¼
	//��ʱ���������ڴ˴˽ɷ�ʱ�������+�ɷѵ�����
	//����>1��ʾ�нɷѼ�¼
	//��ʱӦ�����ڵ������µĻ�����+�ɷѵ�����
	int lines = countLines(fp);
	if (lines == 1)
	{

		//��ס����Ϣ����ҵ��������������
		re[i].lastpay.year = current_year + (current_month + month) / 12;
		if ((current_month + month) % 12 == 0)
		{
			re[i].lastpay.month == 12;
		}
		else
		{
			re[i].lastpay.month = (re[i].lastpay.month + month) % 12;
		}
		//ע�⵽�����µļ���
		fprintf(fp, "���� %s ������ҵ�� %.2f Ԫ,��������: %d��%d��\n", nowtime, pay, re[i].lastpay.year, re[i].lastpay.month);


		FILE* fp1 = fopen("residents.txt", "w+");
		for (i = 0; i < residentcount; i++)
		{
			fprintf(fp1, "%s %s %s %d %d %d %.2f %d %.2f %d %02d\n",
				re[i].name, re[i].gender,
				re[i].phonenumber, re[i].building,
				re[i].unit, re[i].room, re[i].area,
				re[i].paymonth, re[i].publicpay,
				re[i].lastpay.year, re[i].lastpay.month
			);
		}
		fclose(fp1);
		
	}
	else
	{

		fseek(fp, 0, SEEK_END);
		//��ס����Ϣ����ҵ��������������
		re[i].lastpay.year = re[i].lastpay.year + (re[i].lastpay.month + month) / 12;
		if ((re[i].lastpay.month + month) % 12 == 0)
		{
			re[i].lastpay.month == 12;
		}
		else
		{
			re[i].lastpay.month = (re[i].lastpay.month + month) % 12;
		}
		fprintf(fp, "���� %s ������ҵ�� %.2f Ԫ,��������: %d��%d��\n", nowtime, pay,re[i].lastpay.year , re[i].lastpay.month );
	
		


		FILE* fp1 = fopen("residents.txt", "w+");
		for (i = 0; i < residentcount; i++)
		{
			fprintf(fp1, "%s %s %s %d %d %d %.2f %d %.2f %d %02d\n",
				re[i].name, re[i].gender,
				re[i].phonenumber, re[i].building,
				re[i].unit, re[i].room, re[i].area,
				re[i].paymonth, re[i].publicpay,
				re[i].lastpay.year,re[i].lastpay.month
			);
		}
		fclose(fp1);
		
	}
		fclose(fp);
		printf("�����˻�����ҳ��\n");
		system("pause");

}

void overduecount(residentinfo re[]) {

	//��ȡ��ǰʱ��
	time_t current_time;
	struct tm* time_info;
	time(&current_time);
	time_info = localtime(&current_time);
	int current_month, current_year;

	current_month = time_info->tm_mon + 1;
	current_year = time_info->tm_year + 1900;



	int qianmonth;//Ƿ������
	double money;//����
	residentinfo oduere[100];
	int j = 0;
	for (int i = 0; i < residentcount; i++)
	{
		qianmonth = (current_year - re[i].lastpay.year) * 12 + current_month - re[i].lastpay.month;
		if (qianmonth > 0)
		{
			oduere[j] = re[i];
			j++;
		}
	}
	printf("��ѡ��Ƿ�ѽ���¥������\n");
	printf("Ƿ�ѽ��(Q)      ¥��(L)");
	char choice[2];
	scanf("%s", choice);
	if (!strcmp(choice ,"Q"))
	{
		//ð������ :С����ǰ
		for (int i = 0; i < j; i++)
		{
			for (int n = 0; n < j - i-1; n++)
			{
				int qianmonth1;
				int qianmonth2;

				qianmonth1 = (current_year - oduere[n].lastpay.year) * 12 + current_month - oduere[n].lastpay.month;
				qianmonth2 = (current_year - oduere[n + 1].lastpay.year) * 12 + current_month - oduere[n + 1].lastpay.month;
				if (qianmonth1 * (oduere[n].area * oduere[n].paymonth + oduere[n].publicpay)
			       > qianmonth2 * (oduere[n + 1].area * oduere[n + 1].paymonth + oduere[n + 1].publicpay))
				{
					residentinfo temp=oduere[n];
					oduere[n] = oduere[n + 1];
					oduere[n + 1] = temp;


				}
			}
		}

		for (int i = 0; i < j; i++)
		{
			qianmonth = (current_year - oduere[i].lastpay.year) * 12 + current_month - oduere[i].lastpay.month;
			money = qianmonth * (oduere[i].area * oduere[i].paymonth + oduere[i].publicpay);
			char a[50];
			sprintf(a, "./δ���ڽɷ�ס��ͳ��/%d_%d.txt", current_year, current_month);
			FILE* fp1 = fopen(a, "a+");
			fprintf(fp1, "����:%s ¥��%d �����%d ��Ƿ��%d����,��Ƿ�ѽ��%.2fԪ\n", oduere[i].name, oduere[i].building, oduere[i].room, qianmonth, money);
			fprintf(fp1, "--------------------------------------------------------------");
			printf("����:%s ¥��%d �����%d ��Ƿ��%d����,��Ƿ�ѽ��%.2fԪ\n", oduere[i].name, oduere[i].building, oduere[i].room, qianmonth, money);
			fclose(fp1);
		}
	}




	
	if (!strcmp(choice, "L"))
	{
		for (int i = 0; i < j; i++)
		{
			for (int n = 0; n < j - i-1; n++)
			{
				if (oduere[n].building>oduere[n+1].building)
				{
					residentinfo temp = oduere[n];
					oduere[n] = oduere[n + 1];
					oduere[n + 1] = temp;
				}
			}
		}

		for (int i = 0; i < j; i++)
		{
			qianmonth = (current_year - oduere[i].lastpay.year) * 12 + current_month - oduere[i].lastpay.month;
			money = qianmonth * (oduere[i].area * oduere[i].paymonth + oduere[i].publicpay);
			char a[50];
			sprintf(a, "./δ���ڽɷ�ס��ͳ��/%d_%d.txt", current_year, current_month);
			FILE* fp1 = fopen(a, "a+");
			fprintf(fp1, "����:%s ¥��%d �����%d ��Ƿ��%d����,��Ƿ�ѽ��%.2fԪ\n", oduere[i].name,oduere[i].building, oduere[i].room, qianmonth, money);
			fprintf(fp1, "--------------------------------------------------------------");
			printf("����:%s ¥��%d �����%d ��Ƿ��%d����,��Ƿ�ѽ��%.2fԪ\n", oduere[i].name, oduere[i].building, oduere[i].room, qianmonth, money);
			fclose(fp1);
		}
	}
	if (j == 0)
	{
		printf("û��Ƿ��ס��\n");
		printf("�����˻�����ҳ��\n");
	}
	else
	{
		printf("��ͳ�Ƴɹ�\n");
		printf("�����˻�����ҳ��\n");
	}
	system("pause");
	return;
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


void Announcement()
{
	FILE* fp = fopen("./���¹���.txt", "r");
	char ann[30];
	printf("*****************************\n");
	while (fgets(ann,30,fp)!=0) 
	{
		printf("%s\n", ann);

	}
	printf("*****************************\n");

	fclose(fp);

	printf("��������������\n");
	system("pause");
	return;
}

//�ж��Ƿ��ǹ���Ա
int adm() 
{
	int zhanghao;
	int mima;
	printf("************************************************\n");
	printf("���������Ա�˺�:");
	scanf("%d", &zhanghao);
	printf("���������Ա����:");
	scanf("%d", &mima);
	printf("************************************************\n");
	if (zhanghao == 123456 and mima == 123456)
	{
		printf("�˺�������ȷ�����������\n");
		return 1;
	}
	else
	{
		printf("�˺Ż�������������ԣ�\n");
		return 0;
	}
}
