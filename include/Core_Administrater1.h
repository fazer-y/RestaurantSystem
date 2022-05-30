/*
 * @Author: 彭京
 * @ID: 202000810081
 * @Date: 2022-05-29
 * @LastEditors: LAPTOP-44TSMLLA
 * @Description: 
 */

#ifndef __CORE_ADMINISTRATER_H_
#define __CORE_ADMINISTRATER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>

//系统管理员账号 最大长度
#define ADMINID_LENGTH_MAX 15
//系统管理员密码 最大长度
#define ADMINPAS_LENGTH_MAX 20
//系统管理员姓名 最大长度
#define ADMINNAME_LENGTH_MAX 10

//食物名称 最大长度
#define FOODNAME_LENGTH_MAX 30

//存放系统管理员信息的文本文档
#define ADMIN_FILE_PATH "Files/admin.txt"

//存放食品信息的文本文档
#define FOOD_FILE_PATH "Files/,menu.txt"

//系统管理员
typedef struct Admin
{
    char ID[ADMINPAS_LENGTH_MAX+1];
    char password[ADMINPAS_LENGTH_MAX+1];
    char name[ADMINNAME_LENGTH_MAX+1];
    char sex[10];
    int age;
}Admin;

//链表节点(系统管理员)
typedef struct Adminnode
{
    struct Admin data;
    struct Adminnode *next;
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
    int price;//食物价格
    int orderCount;//这个菜从添加到系统里以来一共被点的次数
}food;

//链表节点(食物)
typedef struct foodnode
{
    struct food data;
    struct foodnode *next;
    int number;//总数量
}foodnode;

//初始化一个无头结点的系统管理员链表
Adminnode *InitAdminTable();

//添加一个系统管理员数据到一个有序链表 根据系统管理员年龄递增排序
Adminnode *addAdminByOrder(Adminnode *pHead, struct Admin data);

//按年龄顺序打印系统管理员信息链表（浏览系统管理员信息）
void printAdminTable(Adminnode *pHead);

//查找链表中是否有对应ID的管理员
bool findAdminByID(Adminnode *pHead, char* ID);

//根据ID更新系统管理员信息
Adminnode *updateAdminByID(Adminnode *pHead, char* ID, struct Admin data);

//从文件中读取管理员信息(相当于创建单链表操作)
Adminnode *readAdminFromFile(Adminnode *pHead);

//将链表中管理员信息写入文件
bool writeAdminIntoFile(Adminnode *pHead);


//初始化一个无头结点的食物链表
foodnode *InitfoodTable();

//添加一个食品信息到一个链表（尾部）
foodnode *addfood(foodnode *pHead, food data);

//查找链表中是否有对应ID的食物
bool findfoodByid(foodnode *pHead, char* ID);

//根据id更新食品的信息
foodnode *updatefoodByid(foodnode *pHead, char* ID, food data);

//根据id从菜单中删除食品
foodnode *deletefoodByID(foodnode *pHead, char* ID);

//显示菜单
void printfoodTable(foodnode *pHead);


//如果传入的指针是NULL那么就报错并结束程序
void if_Is_Null_Then_End_Program(void *ptr);

#endif // 管理员头文件