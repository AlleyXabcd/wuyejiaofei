#include<stdio.h>
#include<stdlib.h>
typedef struct {           //����ס����Ϣ�ṹ��
	char name[20];        //��������
	char gender;       //�����Ա�
	char phonenumber; //��ϵ�绰
	int building;         //¥��
	int unit;            //��Ԫ��
	int room;         //�����
	float area;       //���
	float paymonth;    //��ҵ�µ���
	float publicpay;  //��̯ˮ���
}residentinfo;

residentinfo residents[100];
int residentcount = 0;


void menu();
void importresidents();
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
			importresidents();
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
void importresidents()
{


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