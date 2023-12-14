#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
#include<io.h>
 
typedef struct        //定义缴费信息结构体
{
	char paytime[30];//缴费时间
	double pay;//缴费金额
	int year; //缴费截止年份 
	int month;//缴费截止月份
}payinfo;

typedef struct {                   
	//定义住户信息结构体
	char name[10];        //户主姓名
	char gender[3];         //户主性别
	char phonenumber[20]; //联系电话
	int building;         //楼号
	int unit;            //单元号
	int room;         //房间号
	float area;       //面积
	int paymonth;    //物业月单价
	float publicpay;  //公摊水电费
	payinfo lastpay;//最近一次缴费的日期
}residentinfo;




//主页面函数
void menu();

//从文件中导入住户信息，需要指定文件的路径
void importresidents(char path[],residentinfo re[]);

//查找主页面
void querymenu(residentinfo re[]);

//通过房间号查找住户信息
void querybyroom(int rnum,residentinfo re[]);

//通过户主姓名查找住户信息
void querybyname(char nname[] ,residentinfo re[]);

//物业缴费
void payment(residentinfo re[]);

//统计未缴费住户信息
void overduecount(residentinfo re[]);

//统计文件中的行数
//住户信息中的每一行代表一个住户信息
//统计住户信息文件中的行数可以表示总住户数
int countLines(FILE*file);


//新增住户留言功能
void Announcement();

//判断是否是管理员
//1:是管理员
//0:不是管理员
int adm();



int residentcount=0;
int main()
{
	if (!adm())
	{
		return 0 ;

	}
	int choice;
	residentinfo residents[100]; //定义住户数组，存放住户信息
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
					printf("输入错误\n");
					printf("请重新输入\n");
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
	printf("                            ………………欢迎来到物业缴费程序………………\n");
	printf("                             ------------------------------------------\n");
	printf("                            |           1.住户信息管理                 |\n");
	printf("                            |           2.缴费情况查询                 |\n");
 	printf("                            |           3.物业缴费                     |\n");
	printf("                            |           4.统计未按期缴费住户           |\n");
	printf("                            |           5.程序更新公告                 |\n");
	printf("                            |           0.退出程序                     |\n");
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

		//每一个住户信息生成一个专门的缴费记录文件
		//文件以户主姓名和房间号构成
		sprintf(a, "./缴费记录/%s%d.txt",re[i].name, re[i].room);
		if (_access(a , 0)==-1)//判断文件是否存在（存在则放回0，不存在放回-1）
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
	printf("导入成功，共有%d条信息\n", residentcount);
	fclose(fp);
	printf("即将退回至页面\n");
	system("pause");
	return;
}


void querymenu(residentinfo re[])
{
	 int choice;
	 do
	 {
		 printf("                            ………………欢迎来到缴费情况查询………………\n");
		 if(residentcount==0)
		 {
			 printf("ERROR,未导入住户信息\n");
			 printf("即将返回至主程序\n");
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
			 querybyroom(roomnum,re);
			 return;
		 case 2:
			 char nname[10];
			 printf("请输入人名:");
			 scanf("%s", nname);
			 querybyname(nname,re);
			 return;
		 case 3:
			 return;
		 default:
			 printf("输入错误\n");
			 printf("请重新输入\n");
			 system("pause");
		 }
     }while (1);
}
void querybyroom(int rnum,residentinfo re[])
{
	int i;
	char a[30];
	//遍历住户数组中元素
    //当数组中存储的房号和输入房号相同时break
    //记录此时住户的信息，即i的值
	for ( i = 0; i < residentcount ; i++)
	{
		if (re[i].room == rnum)
		{
			break;
		}
	}
	if (i == residentcount)
	{
		printf("找不到该房间号\n");
		printf("即将退回至主页面\n");
		system("pause");
		return;
	}
	sprintf(a, "./缴费记录/%s%d.txt", re[i].name, re[i].room);
	FILE* fp = fopen(a, "r+");
	if (fp == NULL)
	{
		printf("error");
		return;
	} 
	int line = countLines(fp);

	//缴费记录中只有一行，只储存了住户基本信息
	//而不包括缴费的信息
	if (line == 1)               	                       
	{
		printf("没有缴费记录\n");
		printf("即将退回至主页面\n");
		system("pause");
		fclose(fp);
		return;
	}
	else 
	{
		//读取文件中的每一行并输出
		//即构成缴费记录
		char inf[100][100];
		for (int j = 0; j < line; j++)
		{
			fgets(inf[j], 100, fp);
			printf("%s", inf[j]);
		}
		fclose(fp);
	}

	printf("即将退回至主页面\n");
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
	//越界即失败
	if (i == residentcount)
	{
		printf("找不到该人名\n");
		printf("即将退回至主页面\n");
		system("pause");
		return;
	}
	sprintf(a, "./缴费记录/%s%d.txt", re[i].name, re[i].room);
	FILE* fp = fopen(a, "r+");
	if (fp == NULL)
	{
		printf("error");
		return;
	}
	int line = countLines(fp);

	//缴费记录中只有一行，只储存了住户基本信息
	//而不包括缴费的信息
	if (line == 1)               	
	{
		printf("没有缴费记录\n");
		printf("即将退回至主页面\n");
		system("pause");
		fclose(fp);
		return;
	}
	else
	{
		//读取文件中的每一行并输出
		//即构成缴费记录
		char inf[100][100];
		for (int j = 0; j < line; j++)
		{
			fgets(inf[j], 100, fp);
			printf("%s", inf[j]);
		}
		fclose(fp);
	}

	printf("即将退回至主页面\n");
	system("pause");
	return;


}
void payment(residentinfo re[])
{
	char name[10];//用户姓名
	int month = 0;//缴费月数
	double pay; //需要支付的物业费
	printf("请输入你的姓名：");
	scanf("%s", name);
	int i = 0;

	//遍历住户数组中元素
	//当数组中存储的姓名和输入姓名相同时break
	//记录此时住户的信息，即i的值
	for (i = 0; i < residentcount; i++)
	{
		if (!strcmp(re[i].name, name))  
		{
			break;
		}
	}
	//判断越界
	//越界则表示存储的住户信息中没有该住户
	if (i == residentcount)
	{
		printf("没有该住户信息,请核对信息\n");
		system("pause");
		return;
	}
	printf("输入您要缴纳的月数:");
	scanf("%d", &month);
	
	//缴纳优惠政策需要判定缴纳月数。
	//一次缴纳一年以上物业费的住户享9.5折优惠。
	// 一次缴纳两年以上物业费的住户享9折优惠。
	if (month < 12)
	{
		pay = (re[i].area * re[i].paymonth + re[i].publicpay) * month;
	 	
		printf("*********************************\n");
		printf("你的基本信息:\n");
		printf("姓名:%s\n",re[i].name);
		printf("性别:%s\n",re[i].gender);
		printf("联系方式:%s\n",re[i].phonenumber);
		printf("楼号:%d\n",re[i].building);
		printf("单元号:%d\n",re[i].unit);
		printf("房间号:%d\n",re[i].room);
		printf("住房面积:%.2f\n",re[i].area);
		printf("*********************************\n");
		printf("您应该缴纳的物业费为:%.2f元\n", pay);
	}
	else if (month > 11 and month < 24)
	{
		pay = ((re[i].area * re[i].paymonth + re[i].publicpay) * month) * 0.95;
		printf("*********************************\n");
		printf("你的基本信息:\n");
		printf("姓名:%s\n", re[i].name);
		printf("性别:%s\n", re[i].gender);
		printf("联系方式:%s\n", re[i].phonenumber);
		printf("楼号:%d\n", re[i].building);
		printf("单元号:%d\n", re[i].unit);
		printf("房间号:%d\n", re[i].room);
		printf("住房面积:%.2f\n", re[i].area);
		printf("*********************************\n");
		printf("您应该缴纳的物业费为:%.2f元\n", pay);
	}
	else
	{
		pay = ((re[i].area * re[i].paymonth + re[i].publicpay) * month) * 0.9;
		printf("*********************************\n");
		printf("你的基本信息:\n");
		printf("姓名:%s\n", re[i].name);
		printf("性别:%s\n", re[i].gender);
		printf("联系方式:%s\n", re[i].phonenumber);
		printf("楼号:%d\n", re[i].building);
		printf("单元号:%d\n", re[i].unit);
		printf("房间号:%d\n", re[i].room);
		printf("住房面积:%.2f\n", re[i].area);
		printf("*********************************\n");
		printf("您应该缴纳的物业费为:%.2f元\n", pay);
	}
	char a[30];
	sprintf(a, "./缴费记录/%s%d.txt", re[i].name, re[i].room);
	FILE* fp = fopen(a, "a+");
	if (fp == NULL)
	{
		printf("error");
		return;
	}

	
	//获取当前的时间作为缴费时间

	time_t current_time;
	struct tm* time_info;
	int current_month, current_year;
	// 获取当前时间  
	time(&current_time);
	time_info = localtime(&current_time);
	// 获取当前月份  年份
	// 月份从0开始计数，所以需要加1
	//年份相对于1900年计算，所以需要加1900
	current_month = time_info->tm_mon + 1; 
	
	current_year = time_info->tm_year+1900;

	char nowtime[28];
	sprintf(nowtime, "%d年%d月%d日%d:%d:%d", 1900 + time_info->tm_year, 1 + time_info->tm_mon, time_info->tm_mday, time_info->tm_hour, time_info->tm_min, time_info->tm_sec);

	//记录文件中的行数
	//行数==1表示无缴费记录
	//此时到期年月在此此缴费时间基础上+缴费的月数
	//行数>1表示有缴费记录
	//此时应优先在到期年月的基础上+缴费的月数
	int lines = countLines(fp);
	if (lines == 1)
	{

		//对住户信息中物业到期年月做更新
		re[i].lastpay.year = current_year + (current_month + month) / 12;
		if ((current_month + month) % 12 == 0)
		{
			re[i].lastpay.month == 12;
		}
		else
		{
			re[i].lastpay.month = (re[i].lastpay.month + month) % 12;
		}
		//注意到期年月的计算
		fprintf(fp, "您在 %s 缴纳物业费 %.2f 元,到期年月: %d年%d月\n", nowtime, pay, re[i].lastpay.year, re[i].lastpay.month);


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
		//对住户信息中物业到期年月做更新
		re[i].lastpay.year = re[i].lastpay.year + (re[i].lastpay.month + month) / 12;
		if ((re[i].lastpay.month + month) % 12 == 0)
		{
			re[i].lastpay.month == 12;
		}
		else
		{
			re[i].lastpay.month = (re[i].lastpay.month + month) % 12;
		}
		fprintf(fp, "您在 %s 缴纳物业费 %.2f 元,到期年月: %d年%d月\n", nowtime, pay,re[i].lastpay.year , re[i].lastpay.month );
	
		


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
		printf("即将退回至主页面\n");
		system("pause");

}

void overduecount(residentinfo re[]) {

	//获取当前时间
	time_t current_time;
	struct tm* time_info;
	time(&current_time);
	time_info = localtime(&current_time);
	int current_month, current_year;

	current_month = time_info->tm_mon + 1;
	current_year = time_info->tm_year + 1900;



	int qianmonth;//欠费月数
	double money;//数额
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
	printf("请选择按欠费金额或楼号排序\n");
	printf("欠费金额(Q)      楼号(L)");
	char choice[2];
	scanf("%s", choice);
	if (!strcmp(choice ,"Q"))
	{
		//冒泡排序法 :小的在前
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
			sprintf(a, "./未按期缴费住户统计/%d_%d.txt", current_year, current_month);
			FILE* fp1 = fopen(a, "a+");
			fprintf(fp1, "户主:%s 楼号%d 房间号%d 已欠费%d个月,总欠费金额%.2f元\n", oduere[i].name, oduere[i].building, oduere[i].room, qianmonth, money);
			fprintf(fp1, "--------------------------------------------------------------");
			printf("户主:%s 楼号%d 房间号%d 已欠费%d个月,总欠费金额%.2f元\n", oduere[i].name, oduere[i].building, oduere[i].room, qianmonth, money);
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
			sprintf(a, "./未按期缴费住户统计/%d_%d.txt", current_year, current_month);
			FILE* fp1 = fopen(a, "a+");
			fprintf(fp1, "户主:%s 楼号%d 房间号%d 已欠费%d个月,总欠费金额%.2f元\n", oduere[i].name,oduere[i].building, oduere[i].room, qianmonth, money);
			fprintf(fp1, "--------------------------------------------------------------");
			printf("户主:%s 楼号%d 房间号%d 已欠费%d个月,总欠费金额%.2f元\n", oduere[i].name, oduere[i].building, oduere[i].room, qianmonth, money);
			fclose(fp1);
		}
	}
	if (j == 0)
	{
		printf("没有欠费住户\n");
		printf("即将退回至主页面\n");
	}
	else
	{
		printf("已统计成功\n");
		printf("即将退回至主页面\n");
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
	rewind(file);//文件指针归位
	return count;
}


void Announcement()
{
	FILE* fp = fopen("./更新公告.txt", "r");
	char ann[30];
	printf("*****************************\n");
	while (fgets(ann,30,fp)!=0) 
	{
		printf("%s\n", ann);

	}
	printf("*****************************\n");

	fclose(fp);

	printf("即将返回主界面\n");
	system("pause");
	return;
}

//判断是否是管理员
int adm() 
{
	int zhanghao;
	int mima;
	printf("************************************************\n");
	printf("请输入管理员账号:");
	scanf("%d", &zhanghao);
	printf("请输入管理员密码:");
	scanf("%d", &mima);
	printf("************************************************\n");
	if (zhanghao == 123456 and mima == 123456)
	{
		printf("账号密码正确！请继续操作\n");
		return 1;
	}
	else
	{
		printf("账号或密码错误，请重试！\n");
		return 0;
	}
}
