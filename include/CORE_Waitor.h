#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <Windows.h>
#include <time.h>
#include "../include/Core_Administrater.h"

#define WaitorName_MaxLength 30
#define WaitorPasswd_MaxLength 10
#define CustomerName_MaxLength 30
#define SumFoodsOfOrder_Max 50
#define MaxWidthOfSeatsMap 10
#define MaxHeightOfSeatsMap 10


typedef struct DateOfOrder {
    int year;
    int month;
    int day;
}DateOfOrder;

typedef struct seat {
    int col;
    int row;
    int IsSelected;
}seat;

typedef struct waitor{
    char name[WaitorName_MaxLength];
    char passwd[WaitorPasswd_MaxLength];
    int sumofserve;
    waitor* next;
}waitor;

typedef struct Order {
    char name[CustomerName_MaxLength];
    int DineInside;
    int numbers;//用餐人数
    char foods[50][50];
    int sumoffood;
    double MoneyPaid;
    int isCheckedout;//是否结账
    DateOfOrder date;
    seat seat;
}Order;

typedef struct OrderNode{
    Order order;
    struct OrderNode* next;
}ordernode;


ordernode* OrderListHead = (ordernode*)malloc(sizeof(ordernode));//系统当前未结账订单头结点
Order CurrentOrder;
waitor* WaitorListHead = (waitor*)malloc(sizeof(waitor));
waitor* currentWaitor;
seat  SeatsMap[MaxHeightOfSeatsMap][MaxWidthOfSeatsMap];
foodnode* foodsListHead = (foodnode*)malloc(sizeof(foodnode));


void ShowOrderUI();
void ShowWaitorMainUI();
void DeletetheOrder();
void ShowWaitorMainUI();
void ShowWaitorLoginUI();
void ShowCheckOutUI();
void ShowUnCheckedOrderUI();
void ShowTakeOrderUI();
void ExitWaitorMainUI();



waitor* getWaitorByName(char* name);
void UpdateWaitorsNode();
void Revereshow(foodnode* p);
void ShowMenu();
void LoadMenu();
void LoadWaitors();
void ReWriteUnDoneOrders();
void color(const unsigned short textColor);
void SetColor(int fore, int back);
void AddOrdertoOrderList(Order* order);
void SearchOrder();
void LoadSeatsMap();
void ShowSeatMap();
int wherex();
int wherey();
void gotoxy(int x, int y);
int CheckPasswd(char* name, char* passwd);
void AddWaitorToList(char* name, char* passwd, int sumofserve);
void UpdateWaitorsInfo();
void UpdateWaitorsNode();
double getPriceoffood(char* id);
char* getNameofFood(char* id);
ordernode* getOrderbyName(char* name);
void deleteOrder(char* name);
void CheckOut();
void DeletetheOrder();
void UpdateNameofOrder(ordernode* theorder);
void AddFoodtoOrder(ordernode* theorder);
void DelFoodofOrder(ordernode* theorder);
void ChangeOrder();
void LoadUnDoneOrders();
void Revereshow(foodnode* p);
void PrintfWaitorsInfo();
void DeleteWaitorOfList(char* name);
void UpdateCountofFood(char* id);
