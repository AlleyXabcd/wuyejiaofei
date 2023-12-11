#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
typedef struct {           //����ס����Ϣ�ṹ��
	char name[20];        //��������
	char gender[2];         //�����Ա�
	char phonenumber[20]; //��ϵ�绰
	int building;         //¥��
	int unit;            //��Ԫ��
	int room;         //�����
	float area;       //���
	int paymonth;    //��ҵ�µ���
	float publicpay;  //��̯ˮ���
}residentinfo;

residentinfo residents[100];
int residentcount = 0;


void menu();
void importresidents(char path[]);
void querymenu();
void querybyroom();
void querybyname();
void payment();
void overduecount();
int main()
{
	menu();


}
void menu()
{
	int choice;
	printf("                            ��������������ӭ������ҵ�ɷѳ��򡭡���������\n");
	printf("                                       ��ѡ��Ҫ�����ҵ��               \n");
	printf("                             ------------------------------------------\n");
	printf("                            |           1.ס����Ϣ����                 |\n");
	printf("                            |           2.�ɷ������ѯ                 |\n");
 	printf("                            |           3.��ҵ�ɷ�                     |\n");
	printf("                            |           4.ͳ��δ���ڽɷ�ס��           |\n");
	printf("                            |           0.�˳�����                     |\n");
	printf("                             ------------------------------------------\n");
	scanf_s("%d", &choice);
	while (choice)
	{
		switch (choice)
		{
		case 1:
			char path[100];
			printf("��������Ҫ������ļ�·��:");
			scanf("%s", path);

			importresidents(path);
		case 2:
			querymenu();
		case 3:
			payment();
		case 4:
			overduecount();
		default:
			break;
		}

	}
}
void importresidents(char path[])
{
	FILE* fp;
	fp=fopen( path, "r+");
	if ( NULL == fp)
		return ;
	fscanf_s(fp, "%d", &residentcount);
	for (int i = 0; i < residentcount; i++)
	{
		fscanf_s(fp, "%s %s %s %d %d %d %f %d %f\n",residents[i].name, 20, residents[i].gender, 20, 
			residents[i].phonenumber, 20, &residents[i].building,
			&residents[i].unit, &residents[i].room, &residents[i].area,
			&residents[i].paymonth, &residents[i].publicpay);
	}
	printf("����ɹ�������%d����Ϣ\n", residentcount);
	fclose(fp);
	system("pause");
	menu();
}


void querymenu()
{
	 int choice;
	printf("                            ��������������ӭ�����ɷ������ѯ������������\n");
	printf("                                        ��ѡ��           \n");
	printf("                             ------------------------------------------\n");
	printf("                            |           1.�����Ų�ѯ                   |\n");
	printf("                            |           2.������������ѯ               |\n");
	printf("                            |           3.������ҳ��                   |\n");
	printf("                             ------------------------------------------\n");
	scanf_s("%d", &choice);
	while (choice)
	{
		switch (choice)
		{
		case 1:
			querybyroom();
		case 2:
			querybyname();
		case 3:
			menu();

		default:
			break;
		}

	}
}
void querybyroom() {

}
void querybyname() {

}
void payment() {

}
void overduecount()
{
	
}