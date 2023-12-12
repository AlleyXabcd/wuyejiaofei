#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
#include<io.h>
typedef struct 
{                    //定义住户信息结构体
	char name[20];        //户主姓名
	char gender[2];         //户主性别
	char phonenumber[20]; //联系电话
	int building;         //楼号
	int unit;            //单元号
	int room;         //房间号
	float area;       //面积
	int paymonth;    //物业月单价
	float publicpay;  //公摊水电费
}residentinfo;
void menu();
void importresidents(char path[]);
void querymenu();
void querybyroom(int rnum);
void querybyname(char nname[]);
void payment();
void overduecount();

long countLines(FILE* file)  //统计文件的行数
{
	char ch;
	long count = 0;

	while ((ch = fgetc(file)) != EOF) {
		if (ch == '\n') {
			count++;
		}
	}
	rewind(file);//文件指针归位
	return count;
}

residentinfo residents[100];
int residentcount = 0;
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
				printf("请输入需要导入的文件路径:");
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
	printf("                            ………………欢迎来到物业缴费程序………………\n");
	printf("                             ------------------------------------------\n");
	printf("                            |           1.住户信息管理                 |\n");
	printf("                            |           2.缴费情况查询                 |\n");
 	printf("                            |           3.物业缴费                     |\n");
	printf("                            |           4.统计未按期缴费住户           |\n");
	printf("                            |           0.退出程序                     |\n");
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
		sprintf(a + i, "./缴费记录/%s%d",residents[i].name, residents[i].room);
		if (_access(a + i, 0)==-1)//判断文件是否存在（存在则放回0，不存在放回-1）
		{
			FILE* fp2 = fopen(a + i, "a+");
			fprintf(fp2, "%s %s %s %d %d %d %f %d %f\n", residents[i].name, residents[i].gender,
				residents[i].phonenumber, residents[i].building,
				residents[i].unit, residents[i].room, residents[i].area,
				residents[i].paymonth, residents[i].publicpay);
			fclose(fp2);
		}
	}
	printf("导入成功，共有%d条信息\n", residentcount);
	fclose(fp);
	printf("即将退回至页面\n");
	system("pause");
}
void querymenu()
{
	 int choice;
	 do
	 {
		 printf("                            ………………欢迎来到缴费情况查询………………\n");
		 if(!residentcount)
		 {
			 printf("ERROR,未导入住户信息\n");
			 system("pause");
			 return;
		 }
		 printf("                                        请选择：               \n");
		 printf("                             ------------------------------------------\n");
		 printf("                            |           1.按房号查询                   |\n");
		 printf("                            |           2.按户主姓名查询               |\n");
		 printf("                            |           3.返回主页面                   |\n");
		 printf("                             ------------------------------------------\n");
		 scanf_s("%d", &choice);
		 switch (choice)
		 {
		 case 1:
			 int roomnum;
			 printf("请输入房号:");
			 scanf("%d", &roomnum);
			 querybyroom(roomnum);
			 return;
		 case 2:
			 char nname[10];
			 printf("请输入人名:");
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
		printf("找不到该房间号");
	}
	sprintf(a + i, "./缴费记录/%s%d", residents[i].name, residents[i].room);
	FILE* fp = fopen(a+i, "r+");
	if(countLines(fp)==1)
	{ 
		printf("没有缴费记录");
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
	printf("即将退回至主页面\n");
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
		printf("找不到该人名");
	}
	sprintf(a + i, "./缴费记录/%s%d", residents[i].name, residents[i].room);
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
	printf("即将退回至主页面\n");
	system("pause");


}
void payment() 
{
		char name[20];//用户姓名
		int month = 0;//缴费月数
		printf("请输入你的姓名：");
		scanf("%s", name);
		int i = 0;
		for (i = 0; i < residentcount; i++) 
		{
			if (!strcmp(residents[i].name,name)) 
			{
				break;
			}
		}
		printf("请您选择您要缴纳的月数");
		scanf("%d", &month);//缴纳优惠政策需要确定缴纳月数。
		double pay;
		if (month < 12)		
		{
			pay = (residents[i].area * residents[i].paymonth + residents[i].publicpay) * month;
			printf("姓名%s,性别%s,电话%s,楼号%d,单元号%d,房间号%d,住房面积%f\n", residents[i].name, residents[i].gender, residents[i].phonenumber, residents[i].building, residents[i].unit, residents[i].room, residents[i].area);
			printf("您应该缴纳的物业费为:%f元\n", pay );
		}
		else if (month > 11 and month < 24)
		{
			pay = ((residents[i].area * residents[i].paymonth + residents[i].publicpay) * month) * 0.95;
			printf("姓名%s,性别%s,电话%s,楼号%d,单元号%d,房间号%d,住房面积%f\n", residents[i].name, residents[i].gender, residents[i].phonenumber, residents[i].building, residents[i].unit, residents[i].room, residents[i].area);			
			printf("您应该缴纳的物业费为:%f元\n", pay);
		}
		else
		{
			pay = ((residents[i].area * residents[i].paymonth + residents[i].publicpay) * month) * 0.9;
			printf("姓名%s,性别%s,电话%s,楼号%d,单元号%d,房间号%d,住房面积%f\n", residents[i].name, residents[i].gender, residents[i].phonenumber, residents[i].building, residents[i].unit, residents[i].room, residents[i].area);
			printf("\n您应该缴纳的物业费为:%f元\n", pay);
	     }
		
		sprintf(a + i, "./缴费记录/%s%d", residents[i].name, residents[i].room);
		FILE* fp = fopen(a+i, "a+");
		if (fp == NULL)
		{
			printf("error");
			return;
		}
		time_t current_time;
		struct tm* time_info;
		int current_month, current_year;
		char time1[28];
		// 获取当前时间  
		time(&current_time);
		time_info = localtime(&current_time);

		// 获取当前月份  年份
		current_month = time_info->tm_mon + 1; // 月份从0开始计数，所以需要加1
		current_year = time_info->tm_year;
		sprintf(time1, "%d年%d月%d日 %d:%d:%d", 1900 + time_info->tm_year, 1 + time_info->tm_mon, time_info->tm_mday, time_info->tm_hour, time_info->tm_min, time_info->tm_sec);
		fprintf(fp, "您在%s缴纳物业费%f元，到期年月:%d年%d月\n",time1,pay, current_year+1900+ (current_month + month)/12,(current_month + month)%12);

		fclose(fp);
		system("pause");
}
void overduecount()
{




	
}