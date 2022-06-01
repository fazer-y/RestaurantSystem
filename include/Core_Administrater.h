/*
 * @Author: 彭京
 * @ID: 202000810081
 * @Date: 2022-05-31
 * @LastEditors: LAPTOP-44TSMLLA
 * @Description:该源代码文件记录了系统管理员的五个功能需求中所要用到的所有链表和文件操作函数声明，大部分UI界面设计函数声明，主创作者为彭京。
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>

 //系统管理员账号 最大长度
#define ADMINID_LENGTH_MAX 15
//系统管理员密码 最大长度
#define ADMINPAS_LENGTH_MAX 20
//系统管理员姓名 最大长度
#define ADMINNAME_LENGTH_MAX 10

 //服务员姓名 最大长度
#define WaitorName_MaxLength 30
//服务员密码 最大长度
#define WaitorPasswd_MaxLength 10

//食物名称 最大长度
#define FOODNAME_LENGTH_MAX 30

//存放系统管理员信息的文本文档
#define ADMIN_FILE_PATH "admin.txt"

//存放食品信息的文本文档
#define FOOD_FILE_PATH "menu.txt"

//系统管理员
typedef struct Admin
{
	char ID[ADMINPAS_LENGTH_MAX];
	char password[ADMINPAS_LENGTH_MAX];
	char name[ADMINNAME_LENGTH_MAX];
	char sex[10];
	int age;
}Admin;

//服务员
typedef struct waitor {
	char name[30];
	char passwd[30];
	int sumofserve;
	struct waitor* next;
}waitor;

//初始化服务员链表
waitor* WaitorListHead = (waitor *)malloc(sizeof(waitor));
waitor* currentWaitor;

//链表节点(系统管理员)
typedef struct Adminnode
{
	Admin data;
	struct Adminnode* next;
	int number;//总数量
}Adminnode;

//食物类型
enum foodType
{
	specaility,//招牌菜
	staple,//主食
	hot,//热菜
	cold,//凉菜
	soup,//汤
	beverage,//饮料
};

//菜品
typedef struct food
{
	char id[10];//食物ID(唯一性)
	char name[FOODNAME_LENGTH_MAX];//食物名称
	enum foodType foodtype;
	double price;//食物价格
	int orderCount;//这个菜从添加到系统里以来一共被点的次数
}food;

//链表节点(食物)
typedef struct foodnode
{
	struct food data;
	struct foodnode* next;
	int number;//总数量
}foodnode;

//初始化一个无头结点的系统管理员链表
Adminnode* InitAdminTable();
//添加一个系统管理员数据到一个有序链表 根据系统管理员年龄递增排序
Adminnode* addAdminByOrder(Adminnode* pHead, Admin data);
//按年龄顺序打印系统管理员信息链表（浏览系统管理员信息）
void printAdminTable(Adminnode* pHead);
//查找链表中是否有对应ID的管理员
Adminnode* findAdminByID(Adminnode* pHead, char* ID);
//根据ID更新系统管理员信息
Adminnode* updateAdminByID(Adminnode* pHead, char* ID, Admin data);

//从文件中读取管理员信息(相当于创建单链表操作)
Adminnode* readAdminFromFile(Adminnode* pHead);
//将链表中管理员信息写入文件
bool writeAdminIntoFile(Adminnode* pHead);

//将枚举类型的菜品信息转化为字符串以便输出
char* switchenumtos(enum foodType type);
//将字符串类型转化为枚举类型以便食品录入
enum foodType switchstoenum(char* type);
//初始化一个无头结点的食物链表
foodnode* InitfoodTable();
//添加一个食品信息到一个链表（尾部）
foodnode* addfood(foodnode* pHead, food data);
//查找链表中对应ID的食物，返回指向该食物结点的指针
foodnode* findfoodByid(foodnode* pHead, char* ID);
//根据id更新食品的信息
foodnode* updatefoodByid(foodnode* pHead, char* ID, food data);
//根据食物的被点次数得到一个降序排序的有序链表
foodnode* orderfoodbycount(foodnode* pHead);
//根据id从菜单中删除食品
foodnode* deletefoodByID(foodnode* pHead, char* ID);
//显示菜单
void printfoodTable(foodnode* pHead);

//从文件中读取食物信息(相当于创建单链表操作)
foodnode* readfoodFromFile(foodnode* pHead);
//将链表中食物信息写入文件
bool writefoodIntoFile(foodnode* pHead);

//根据服务员的服务量得到一个降序排序的有序链表
waitor* orderWaitorbycount();   //-->应该是这个函数出了点问题，但我现在找不出来

//设置光标位置
void gotoxy(int x, int y);
//获取光标位置x
int wherex();
//获取光标的位置y
int wherey();
//如果传入的指针是NULL那么就报错并结束程序
void if_Is_Null_Then_End_Program(void* ptr);

//部分系统管理员UI界面
//系统管理员登录
void ShowAdminLoginUI(Adminnode* pHead);
//系统管理员主界面
void ShowAdminMainUI(Adminnode* pHead);
void ShowUserManageUI(Adminnode* pHead);
//用户管理
void showAdminManageUI(Adminnode* pHead);
void showWaitorManageUI(Adminnode* pHead);
//管理员信息管理
void addAdminUI(Adminnode* pHead);
void findAdminUI(Adminnode* pHead);
void updateAdminUI(Adminnode* pHead);
//服务员信息管理
void AddWaitorToList(char* name, char* passwd, int sumofserve);
void DeleteWaitorOfList(char* name);
void UpdateWaitorsInfo();
//将服务员文件中的信息读入链表
void LoadWaitors();
waitor* getWaitorByName(char* name);
//更改服务员信息UI
void UpdateWaitorsNode();
void PrintfWaitorsInfo();

//菜单管理
void showAdminfoodUI(foodnode* fHead);
void addfoodUI(foodnode* pHead);
foodnode* findfoodUI(foodnode* pHead);
void updatefoodUI(foodnode* pHead);


//统计分析
void showcensusUI(foodnode* pHead);   //这里的第二个功能出现了点问题