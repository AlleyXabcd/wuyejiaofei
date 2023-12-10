#include<stdio.h>
#include<stdlib.h>
typedef struct {           //定义住户信息结构体
	char name[20];        //户主姓名
	char gender;       //户主性别
	char phonenumber; //联系电话
	int building;         //楼号
	int unit;            //单元号
	int room;         //房间号
	float area;       //面积
	float paymonth;    //物业月单价
	float publicpay;  //公摊水电费
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
	printf("                            ………………欢迎来到物业缴费程序………………\n");
	printf("                                       请选择要办理的业务               \n");
	printf("                             ------------------------------------------\n");
	printf("                            |           1.住户信息管理                 |\n");
	printf("                            |           2.缴费情况查询                 |\n");
	printf("                            |           3.物业缴费                     |\n");
	printf("                            |           4.统计未按期缴费住户           |\n");
	printf("                            |           0.退出程序                     |\n");
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
	printf("                            ………………欢迎来到缴费情况查询………………\n");
	printf("                                        请选择：           \n");
	printf("                             ------------------------------------------\n");
	printf("                            |           1.按房号查询                   |\n");
	printf("                            |           2.按户主姓名查询               |\n");
	printf("                            |           3.返回主页面                   |\n");
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