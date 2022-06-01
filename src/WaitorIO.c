#include "../include/CORE_Waitor.h"


void DeleteWaitorOfList(char* name) {
    waitor* temp = WaitorListHead;
    while (temp->next && strcmp(temp->next->name, name) == 0) {
        waitor* deletewaitor = temp->next;
        temp->next = deletewaitor->next;
        free(temp);
    }
}


//设置字体颜色
void color(const unsigned short textColor)
{
    if (textColor >= 0 && textColor <= 15)
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), textColor);
    else
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

//设置字体前景色和背景色
void SetColor(int fore = 7, int back = 0)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (back << 4) + fore);
}

void AddOrdertoOrderList(Order* order) {
    ordernode* temp = OrderListHead;
    while (temp&&temp->next) {
        temp = temp->next;
    }
    ordernode* add = (ordernode*)malloc(sizeof(ordernode));
    add->order = *order;
    add->next = NULL;
    temp->next = add;
}


void ShowOrderUI() {
    system("cls");
    printf("======================订单界面============================\n");
    printf("%-10s \t%-10s \t%-10s \t%-10s\n", "序号", "顾客姓名", "时间", "支付金额");
    //显示DoneOrders
    FILE* fp = fopen("DoneOrders.txt", "r");
    char name[30];
    int year, month, date;
    double moneypaid;
    int count = 0;
    while (5 == fscanf(fp, "%s %d %d %d %lf", name, &year, &month, &date,&moneypaid)){
        printf("%-10d \t%-10s  \t%d年%d月%d日 \t%-10.2lf\n",++count, name, year, month, date,moneypaid);
    }
    printf("\n============================================================");
    printf("\n按任意键返回主界面");
    system("pause");
    ShowWaitorMainUI();
}




void LoadSeatsMap() 
{
    for (int i = 0; i < MaxHeightOfSeatsMap; i++) 
    {
        for (int j = 0; j < MaxWidthOfSeatsMap; j++)
        {
            SeatsMap[i][j].col = i;
            SeatsMap[i][j].row = j;
            SeatsMap[i][j].IsSelected = 0;
        }
    }
}

void ShowSeatMap() 
{
    printf("===============餐厅实时座位图==================\n ");
    for (int i = 0; i < MaxWidthOfSeatsMap; i++) 
    {
        printf("  %d  ", i);
    }
    for (int i = 0; i < MaxHeightOfSeatsMap; i++) 
    {
        printf("\n%d", i);
        for (int j = 0; j < MaxWidthOfSeatsMap; j++) 
        {
            if (SeatsMap[i][j].IsSelected == 0)
            {
                printf(" [ ] ");
            }
            else
            {
                printf(" [1] ");
            }
        }
        
    }
    printf("\n===================================================\n");
}

//光标控制
int wherex()
{
    CONSOLE_SCREEN_BUFFER_INFO pBuffer;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &pBuffer);
    return (pBuffer.dwCursorPosition.X + 1);
}
//获取光标的位置y
int wherey()
{
    CONSOLE_SCREEN_BUFFER_INFO pBuffer;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &pBuffer);
    return (pBuffer.dwCursorPosition.Y + 1);
}
//设置光标的位置
void gotoxy(int x, int y)
{
    COORD c;
    c.X = x - 1;
    c.Y = y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}


int CheckPasswd(char* name, char* passwd) {
    FILE* fp = fopen("WaitorsInfo.txt", "r");
    if (fp == NULL)
    {
        perror("文件读取失败");
        return 0;
    }
    //把日期先读走
    int year, month, day;
    fscanf(fp, "%d %d %d", &year, &month, &day);


    char nametest[WaitorName_MaxLength], passwdtest[WaitorPasswd_MaxLength];
    int sumofserve;
    while (3 == fscanf(fp, "%s %s %d", nametest, passwdtest,&sumofserve)) 
    {
        if (strcmp(nametest, name) == 0 && strcmp(passwdtest, passwd) == 0)
        {
            return 1;
        }
    }
    fclose(fp);
    return 0;
}


void AddWaitorToList(char *name,char *passwd,int sumofserve) {
    waitor* add = (waitor*)malloc(sizeof(waitor));
    strcpy(add->name, name);
    strcpy(add->passwd, passwd);
    add->sumofserve = sumofserve;
    waitor* temp = WaitorListHead;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = add;
    add->next = NULL;
}



void UpdateWaitorsInfo() {
    //先写日期
    time_t timep;
    struct tm* p;
    time(&timep);
    p = gmtime(&timep);
    int year = p->tm_year + 1900;
    int day = p->tm_mday;
    int month = p->tm_mon + 1;

    FILE* fp = fopen("WaitorsInfo.txt", "w");
    if (fp == NULL) {
        perror("文件读取失败");
    }
    fprintf(fp,"%d %d %d\n", year, month, day);

    waitor* temp = WaitorListHead->next;
    while (temp) {
        fprintf(fp, "%s %s %d\n", temp->name, temp->passwd, temp->sumofserve);
        temp = temp->next;
    }
    fclose(fp);
}

 
void ShowManageWaitorsUI() 
{
    system("cls");
    printf("===================服务员管理界面=====================\n");
    while (true) 
    {
        color(12);
        printf("\n(1)添加服务员\n(2)更新服务员\n(3)退出\n");
        color(7);
        printf("请输入操作序号 【  】");
        gotoxy(wherex() - 3, wherey());
        int index;
        scanf("%d", &index);
        switch (index) 
        {
        case 1: 
        {
            printf("\n请输入您要添加的服务员姓名 >>>_________");
            gotoxy(wherex() - 6, wherey());
            char name[WaitorName_MaxLength];
            scanf("%s", name);
            printf("\n请输入服务员登录密码 >>>_________");
            char passwd[WaitorPasswd_MaxLength];
            gotoxy(wherex() - 6, wherey());
            scanf("%s", passwd);
            AddWaitorToList(name, passwd, 0);
            UpdateWaitorsInfo();
        }
        break;
        case 2: 
        {
            UpdateWaitorsNode();
        }
        break;
        default:
            return;
        }
    }  
}


void UpdateWaitorsNode() {
    printf("\n请输入您要更新的服务员姓名（输入0取消）>>>___________");
    int x = wherex(), y = wherey();
    gotoxy(x - 6, y);
    char name[WaitorName_MaxLength];
    scanf("%s", name);
    if (strcmp(name, "0") == 0)
        return;
    waitor* temp = getWaitorByName(name);
    while(temp == NULL) {
        printf("\n服务员不存在，请重新输入（输入0取消）>>>___________");
        x = wherex(), y = wherey();
        gotoxy(x - 6, y);
        scanf("%s", name);
        if (strcmp(name, "0") == 0)
            return;
        waitor* temp = getWaitorByName(name);
    }

    printf("\n      (1)更新姓名\n      (2)更新密码\n      (3)更新服务人员数量\n      (4)删除\n      (5)返回");
    while (true) {
        printf("\n请输入您要选择的操作序号【  】");
        gotoxy(wherex() - 3, wherey());
        int index;
        scanf("%d", &index);

        switch (index) {
        case 1: 
        {
            printf("\n请输入更新后的姓名（输入0取消）>>>________");
            gotoxy(wherex() - 5, wherey());
            scanf("%s", name);
            if (strcmp(name, "0") == 0)
                continue;
            //更新姓名
            strcpy(temp->name, name);
            printf("\n更新成功！");
            UpdateWaitorsInfo();
        }
            break;
        case 2:
        {
            printf("\n请输入更新后的密码（输入0取消）>>>________");
            gotoxy(wherex() - 5, wherey());
            scanf("%s", name);
            if (strcmp(name, "0") == 0)
                continue;
            //更新姓名
            strcpy(temp->passwd, name);
            printf("\n更新成功！");
            UpdateWaitorsInfo();
        }
            break;
        case 3:
        {
            printf("\n请输入更新后的服务数量（输入-1取消）>>>________");
            gotoxy(wherex() - 5, wherey());
            int sum;
            scanf("%d", &sum);
            if (sum < 0)
                continue;
            //更新姓名
            temp->sumofserve = sum;
            printf("\n更新成功！");
            UpdateWaitorsInfo();
        }
            break;
        case 4: 
        {
            DeleteWaitorOfList(temp->name);
        }
              break;
        default:
            UpdateWaitorsNode();
            return;
        }
    }    
}

void LoadWaitors() {
    WaitorListHead->next = NULL;
    FILE* fp = fopen("WaitorsInfo.txt", "r");
    if (fp == NULL)
    {
        perror("文件读取失败");
    }
    //读日期，如果不是今天的日期，将则服务人员数量全部清零，否则直接转化为链表
    time_t timep;
    struct tm* p;
    time(&timep);
    p = gmtime(&timep);
    int year = p->tm_year + 1900;
    int day = p->tm_mday;
    int month = p->tm_mon + 1;
    int yearoffile, monthoffile, dayoffile;
    fscanf(fp, "%d %d %d", &yearoffile, &monthoffile, &dayoffile);
    if (year != yearoffile || month != monthoffile || day != dayoffile) {


        char name[WaitorName_MaxLength], passwd[WaitorPasswd_MaxLength];
        int sumofserve;
        while (3 == fscanf(fp, "%s %s %d", name, passwd, &sumofserve))
        {
            AddWaitorToList(name, passwd,0);
        }
        //修改文件
        UpdateWaitorsInfo();
    }
    else
    {
        char name[WaitorName_MaxLength], passwd[WaitorPasswd_MaxLength];
        int sumofserve;
        while (3 == fscanf(fp, "%s %s %d", name, passwd, &sumofserve))
        {
            AddWaitorToList(name, passwd, sumofserve);
        }      
    }
    fclose(fp); 
}


void PrintfWaitorsInfo() {
    waitor* temp = WaitorListHead->next;
    printf("\n==============================服务员信息===============================");
    printf("\n%-10s \t%-10s \t%-10s", "姓名", "密码", "今日服务数量");
    while (temp) {
        printf("\n%-10s \t%-10s \t%-10d", temp->name, temp->passwd, temp->sumofserve);
        temp = temp->next;
    }

}



waitor* getWaitorByName(char* name) {
    waitor* temp = WaitorListHead->next;
    while (temp) {
        if (strcmp(name, temp->name) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}



double getPriceoffood(char* id) 
{
    foodnode* temp = foodsListHead->next;
    while (temp) 
    {
        if (strcmp(id, temp->data.id) == 0)
            return temp->data.price;
        temp = temp->next;
    }
    return 0;
}

char* getNameofFood(char* id) {
    foodnode* temp = foodsListHead;
    while (temp)
    {
        if (strcmp(id, temp->data.id) == 0)
            return temp->data.name;
        temp = temp->next;
    }
    return NULL;
}

ordernode* getOrderbyName(char* name) {
    ordernode* temp = OrderListHead->next;
    while (temp) {
        if (strcmp(name, temp->order.name) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void deleteOrder(char* name) {
    ordernode* temp= OrderListHead;
    while (temp->next && strcmp(temp->next->order.name, name) != 0) {
        temp = temp->next;
    }
    ordernode* delnode = temp->next;

    if (delnode->order.DineInside == 1) {
        SeatsMap[delnode->order.seat.col][delnode->order.seat.row].IsSelected = 0;//更新座位
    }
    temp->next = delnode->next;
}


void UpdateCountofFood(char* id) {
    foodnode* temp = foodsListHead->next;
    while (temp) {
        if (strcmp(temp->data.id, id) == 0) {
            temp->data.orderCount += 1;
            break;
        }
        temp = temp->next;
    }
}

void ReWriteBackFood() {
    foodnode* temp = foodsListHead->next;
    FILE* fp = fopen("menu.txt", "w");
    if (fp == NULL) {
        perror("文件读取失败");
        return;
    }
    while (temp) {
        char typeoffood[FOODNAME_LENGTH_MAX];
        foodType type = temp->data.foodtype;
        switch (type) {
        case specaility:
            strcpy(typeoffood, "招牌菜");
            break;
        case staple:
            strcpy(typeoffood, "主食");
            break;
        case  hot:
            strcpy(typeoffood, "热菜");
            break;
        case cold:
            strcpy(typeoffood, "凉菜");
            break;
        case soup:
            strcpy(typeoffood, "汤");
            break;
        case beverage:
            strcpy(typeoffood, "饮料");
            break;
        }
        fprintf(fp, "%s %s %s %d %.2lf\n", temp->data.id, temp->data.name,typeoffood, temp->data.orderCount, temp->data.price);
        temp = temp->next;
    } 
    fclose(fp);
}

void CheckOut() {
    printf("请选择要结账订单的顾客名>>>__________");
    int x = wherex(), y = wherey();
    gotoxy(x-10,y);
    char name[CustomerName_MaxLength];
    scanf("%s", name);
    ordernode* ordertocheck = getOrderbyName(name);
    while(ordertocheck == NULL) {
        printf("\n顾客不存在，请重新输入,输入0取消结账 >>>");
        scanf("%s", name);
        if (strcmp(name, "0") == 0) {
            return;
        }
            
        ordertocheck = getOrderbyName(name);
    }
    //具体结账操作
    //1.从链表中删除
    //2.写入DoneOrders.txt
    //3.座位改为0
    //4.增加菜品点单次数
    LoadMenu();
    for (int i = 0; i < ordertocheck->order.sumoffood; i++) {
        //修改次数，然后重写进文件
        UpdateCountofFood(ordertocheck->order.foods[i]);
    }
    ReWriteBackFood();

    deleteOrder(name);
   
    FILE* fp = fopen("DoneOrders.txt", "a+");
    if (fp == NULL) {
        perror("文件读取失败");
        return;
    }
    fprintf(fp, "%s %d %d %d %.2lf", ordertocheck->order.name, ordertocheck->order.date.year, ordertocheck->order.date.month, ordertocheck->order.date.day, ordertocheck->order.MoneyPaid);
    fclose(fp);
    free(ordertocheck);
}

void ShowCheckOutUI();


void DeletetheOrder() {
    printf("\n请输入您要删除的订单的顾客名>>>__________");
    int x = wherex(), y = wherey();
    gotoxy(x - 10, y);
    char name[CustomerName_MaxLength];
    scanf("%s", name);
    ordernode* ordertocheck = getOrderbyName(name);
    while (ordertocheck == NULL) {
        printf("\n顾客不存在，请重新输入,输入0取消删除>>>");
        scanf("%s", name);
        if (strcmp(name, "0") == 0) {
            return;
        }
        ordertocheck = getOrderbyName(name);
    }
    deleteOrder(name);
    printf("\n删除成功!");
    system("pause");

}

void SearchOrder() {
    printf("\n请输入您要查找的订单的顾客名>>>__________");
    int x = wherex(), y = wherey();
    gotoxy(x - 10, y);
    char name[CustomerName_MaxLength];
    scanf("%s", name);
    ordernode* temp = getOrderbyName(name);
    if (temp == NULL) {
        printf("\n未找到相关订单！");
    }
    else {
        printf("为您查询到以下订单信息:\n===============================================\n");
        printf("顾客名:  %s\n", temp->order.name);
        color(12);
        printf("%-10s \t%-10s \t%-10s\n", "菜品", "数量", "单价");
        color(7);
        int sum[1000] = { 0 };
        for (int i = 0; i < temp->order.sumoffood; i++) {
            char id[50];
            for (int j = 0; temp->order.foods[i][j + 1]; j++) {
                id[j] = temp->order.foods[i][j + 1];
            }
            int index = atoi(id);
            sum[index]++;

        }
        //统计完成
        for (int i = 0; i < 1000; i++) {
            if (sum[i] != 0) {
                //将数字转化为#xxx，再找到菜名和价格
                char id[50];
                sprintf(id, "#%03d", i);
                char name[FOODNAME_LENGTH_MAX];
                double price;
                LoadMenu();
                foodnode* temp = foodsListHead->next;
                while (temp) {
                    if (strcmp(temp->data.id, id) == 0)
                    {
                        strcpy(name, temp->data.name);
                        price = temp->data.price;
                        break;
                    }
                    temp = temp->next;
                }
                //打印
                printf("%-10s \t%-10d \t%-10.2lf\n", name, sum[i], price);
            }
        }
        printf("\n累计:  %.2lf元\n===============================================\n", temp->order.MoneyPaid);
    }
       
}

void ShowUnCheckedOrderUI() {
    system("cls");
    printf("==========================未结账订单界面=============================\n");
    ordernode* temp = OrderListHead->next;

    while (temp) {
        printf("顾客名:  %s\n", temp->order.name);
        color(12);
        printf("%-10s \t%-10s \t%-10s\n","菜品","数量","单价");
        color(7);
        int sum[1000]={0};
        for (int i = 0; i < temp->order.sumoffood; i++) {
            char id[50];
            for (int j = 0;temp->order.foods[i][j+1]; j++) {
                id[j] = temp->order.foods[i][j + 1];
            }
            int index = atoi(id);
            sum[index]++;

        }
        //统计完成
        for (int i = 0;i<1000; i++) {
            if (sum[i] != 0) {
                //将数字转化为#xxx，再找到菜名和价格
                char id[50];
                sprintf(id, "#%03d",i);
                char name[FOODNAME_LENGTH_MAX];
                double price;
                LoadMenu();
                foodnode* temp = foodsListHead->next;
                while (temp) {
                    if (strcmp(temp->data.id, id) == 0)
                    {
                        strcpy(name, temp->data.name);
                        price = temp->data.price;
                        break;
                    }
                    temp = temp->next;
                }
                //打印
                printf("%-10s \t%-10d \t%-10.2lf\n",name,sum[i],price);
            }
        }
        printf("\n累计:  %.2lf 元\n", temp->order.MoneyPaid);
        printf("----------------------------------------------------------------\n");
        temp = temp->next;
    }
    system("pause");
    ShowWaitorMainUI();
}

//修改订单所有函数
void UpdateNameofOrder(ordernode* theorder) {
    printf("\n请输入更新后的顾客姓名(输入0取消更新) >>>_________");
    gotoxy(wherex()-5,wherey());
    char name[CustomerName_MaxLength];
    scanf("%s", name);
    if (strcmp(name, "0") == 0) {
        return;
    }
    //查重姓名
    ordernode* temp = getOrderbyName(name);
    if (temp != NULL && temp != theorder) {
        printf("\n该顾客名已存在，请重新输入！");
        UpdateNameofOrder(theorder);
        return;
    }
    strcpy(theorder->order.name, name);
    printf("\n更新成功！\n");
    system("pause");
    return;
}

void AddFoodtoOrder(ordernode* theorder) {
    printf("\n请输入要添加的菜品ID，以下是所有菜品\n");
    ShowMenu();
    printf("\n请输入您要添加的菜品ID，输入0结束>>>  ");
    char id[10];
    while (scanf("%s", id)) {
        if (strcmp(id, "0") == 0)
            break;
        strcpy(theorder->order.foods[theorder->order.sumoffood++], id);
        theorder->order.MoneyPaid += getPriceoffood(id);
    }
    printf("\n添加成功！\n");
    system("pause");
    return;
}

void DelFoodofOrder(ordernode* theorder) {
    printf("\n请输入要删除的菜品ID，以下是所有菜品\n");
    ShowMenu();
    printf("\n请输入您要删除的菜品ID，输入0结束>>>  ");
    char id[10];
    while (scanf("%s", id)) {
        if (strcmp(id, "0") == 0)
            break;
        for (int i = 0; i < theorder->order.sumoffood; i++) {
            if (strcmp(theorder->order.foods[i], id) == 0) {
                for (int j = i; j < theorder->order.sumoffood - 1; j++) {
                    strcpy(theorder->order.foods[j], theorder->order.foods[j + 1]);
                }
                break;
            }
        }
        theorder->order.MoneyPaid -= getPriceoffood(id);
        theorder->order.sumoffood--;
    }
    printf("\n菜品删除成功!\n");
}

void ChangeOrder() {
    printf("\n请输入您要修改订单的顾客名>>>__________");
    int x = wherex(), y = wherey();
    gotoxy(x - 10, y);
    char name[CustomerName_MaxLength];
    scanf("%s", name);
    ordernode* temp = getOrderbyName(name);
    if (temp == NULL) {
        printf("\n未找到相关订单!\n");
        system("pause");
        return;
    }
    printf("该订单信息如下:\n===============================================\n");
    printf("顾客名:  %s\n", temp->order.name);
    color(12);
    printf("%-10s \t%-10s \t%-10s\n", "菜品", "数量", "单价");
    color(7);
    int sum[1000] = { 0 };
    for (int i = 0; i < temp->order.sumoffood; i++) {
        char id[50];
        for (int j = 0; temp->order.foods[i][j + 1]; j++) {
            id[j] = temp->order.foods[i][j + 1];
        }
        int index = atoi(id);
        sum[index]++;

    }
    for (int i = 0; i < 1000; i++) {
        if (sum[i] != 0) {
            char id[50];
            sprintf(id, "#%03d", i);
            char name[FOODNAME_LENGTH_MAX];
            double price;
            LoadMenu();
            foodnode* temp = foodsListHead->next;
            while (temp) {
                if (strcmp(temp->data.id, id) == 0)
                {
                    strcpy(name, temp->data.name);
                    price = temp->data.price;
                    break;
                }
                temp = temp->next;
            }
            //打印
            printf("%-10s \t%-10d \t%-10.2lf\n", name, sum[i], price);
        }
    }
    printf("\n累计:  %.2lf元\n===============================================\n", temp->order.MoneyPaid);
    //修改选项
    while (true) {
        color(12);
        printf("\n(1)修改订单所属顾客名\n(2)添加菜品\n(3)删除菜品\n(4)退出\n\n");
        color(7);
        printf("\n请输入操作序号>>>_________");
        gotoxy(wherex() - 4, wherey());
        int index;
        scanf("%d", &index);
        switch (index) {
        case 1:
            UpdateNameofOrder(temp);
            break;
        case 2:
            AddFoodtoOrder(temp);
            break;
        case 3:
            DelFoodofOrder(temp);
            break;
        default:
            ShowCheckOutUI();
            return;
        }
    }
}


void ShowCheckOutUI() {
    system("cls");
    printf("==========================结账界面=============================\n");
    ordernode* temp = OrderListHead->next;
    
    while (temp) {
        printf("顾客名:  %s\n",temp->order.name);
        color(12);
        printf("%-10s \t%-10s \t%-10s\n", "菜品", "数量", "单价");
        color(7);
        int sum[1000] = { 0 };
        for (int i = 0; i < temp->order.sumoffood; i++) {
            char id[50];
            for (int j = 0; temp->order.foods[i][j + 1]; j++) {
                id[j] = temp->order.foods[i][j + 1];
            }
            int index = atoi(id);
            sum[index]++;

        }
        //统计完成
        for (int i = 0; i < 1000; i++) {
            if (sum[i] != 0) {
                //将数字转化为#xxx，再找到菜名和价格
                char id[50];
                sprintf(id, "#%03d", i);
                char name[FOODNAME_LENGTH_MAX];
                double price;
                LoadMenu();
                foodnode* temp = foodsListHead->next;
                while (temp) {
                    if (strcmp(temp->data.id, id) == 0)
                    {
                        strcpy(name, temp->data.name);
                        price = temp->data.price;
                        break;
                    }
                    temp = temp->next;
                }
                //打印
                printf("%-10s \t%-10d \t%-10.2lf\n", name, sum[i], price);
            }
        }
        printf("\n累计:  %.2lf 元\n", temp->order.MoneyPaid);
        printf("----------------------------------------------------------------\n");
        temp = temp->next;
    }
    printf("=================================================================\n");
    while (true) {
        printf("\n请选择以下操作：\n");
        printf("(1) 结账订单\n");
        printf("(2) 查询订单\n");
        printf("(3) 删除订单\n");
        printf("(4) 修改订单\n");
        printf("(5) 返回主界面\n");
        printf("请输入操作序号： 【  】");
        int x = wherex(), y = wherey();
        gotoxy(x - 3, y);
        int index;
        scanf("%d", &index);
        switch (index) {
        case 1:
            CheckOut();
            break;
        case 2:
            SearchOrder();
            break;
        case 3:
            DeletetheOrder();
            break;
        case 4:
            ChangeOrder();//////////////////////////////////////test
            break;
        case 5:
            ShowWaitorMainUI();
            break;
        default:
            ShowWaitorMainUI();
            break;
        }
    }
    
}



void ShowTakeOrderUI() {
    system("cls");
    Order* order = (Order*)malloc(sizeof(Order));
    CurrentOrder = *order;//设置当前处理订单
    //设置订单时间
    time_t timep;
    struct tm* p;
    time(&timep);
    p = gmtime(&timep);
    order->date.year = p->tm_year + 1900;
    order->date.day = p->tm_mday;
    order->date.month = p->tm_mon + 1;

    printf("***********************点餐界面************************\n\n\n");
    printf("请输入顾客姓名  >>>____________");
    int x = wherex(), y = wherey();
    gotoxy(x - 8, y);
    char name[CustomerName_MaxLength];
    scanf("%s",name);
    printf("请输入用餐人数  >>>____________");
    x = wherex(), y = wherey();
    gotoxy(x - 8, y);
    int num;
    scanf("%d", &num);

    //设置订单属性
    order->numbers = num;
    strcpy(order->name, name);
    order->sumoffood = 0;
    order->isCheckedout = 0;
    order->MoneyPaid = 0;

    //增加服务员服务人员的数量
    currentWaitor->sumofserve += num;

    printf("店内用餐请按 a\n打包带走请按 b\n>>>");
    char select[2];
    scanf("%s", select);

    if (strcmp(select,"a")==0) 
    {
        ShowSeatMap();
        printf("请选择桌号  【  】【  】");
        int x = wherex(), y = wherey();
        gotoxy(x - 10, y);
        int col, row;
        scanf("%d", &col);
        gotoxy(x -3, y);
        scanf("%d", &row);
        //设置订单属性


        while (SeatsMap[col][row].IsSelected == 1) {
            printf("\n该位置已被占用，请重新选择座位！");
            printf("\n请选择桌号  【  】【  】");
            int x = wherex(), y = wherey();
            gotoxy(x - 10, y);
            scanf("%d", &col);
            gotoxy(x - 3, y);
            scanf("%d", &row);
        }



        order->DineInside = 1;
        order->seat.col = col;
        order->seat.row = row;
        //设置该桌已经被占用
        SeatsMap[col][row].IsSelected = 1;
        
    }
    else
    {
        order->DineInside = 0;
    }
   
    ShowMenu();
    printf("请输入菜品ID,以空格分割,按0结束输入 >>>  ");
    char id[10];
    while (scanf("%s", id)) {
        if (strcmp(id, "0") == 0)
            break;
        strcpy(order->foods[order->sumoffood++], id);
        order->MoneyPaid += getPriceoffood(id);
    }
    //订单设置完成
    AddOrdertoOrderList(order);//加入系统正在处理的订单链表中

    printf("\n按任意键返回主界面:");
    system("pause");
    ShowWaitorMainUI();
}


void ExitWaitorMainUI() {
    UpdateWaitorsInfo();
    ReWriteUnDoneOrders();
}

void ShowWaitorMainUI() {
    system("cls");
    printf("***********************服务员主界面************************\n\n\n");
    printf("             ---------------------------------             \n\n");
    printf("            |        (1) 查看菜单             |            \n");
    printf("            |        (2) 点餐                 |            \n");
    printf("            |        (3) 查看订单             |            \n");
    printf("            |        (4) 结账                 |            \n");
    printf("            |        (5) 查看座位             |            \n");
    printf("            |        (6) 查看未结账订单       |            \n");
    printf("            |        (7) 退出                 |            \n");
    printf("             ---------------------------------             \n\n\n");
    printf("***********************************************************\n\n");
    while (true) {
        printf("请选择操作序号 【  】");
        int x = wherex(), y = wherey();
        gotoxy(x - 3, y);
        int index;
        scanf("%d", &index);
        switch (index) {
        case 1:
            //查看菜单，调用pj的
            system("cls");
            ShowMenu();
            system("pause");
            ShowWaitorMainUI();
            break;
        case 2:
            system("cls");
            ShowTakeOrderUI();
            break;
        case 3:
            system("cls");
            ShowOrderUI();
            break;
        case 4:
            ShowCheckOutUI();
            break;
        case 5:
            ShowSeatMap();
            break;
        case 6:
            ShowUnCheckedOrderUI();
            
            break;
        case 7:
            ExitWaitorMainUI();
            ShowWaitorLoginUI();
            break;
        default:
            continue;
        }
   }
    

}

void LoadUnDoneOrders() 
{
    OrderListHead->next = NULL;
    FILE* fp = fopen("UnDoneOrders.txt", "r");
    if (fp == NULL) {
        perror("读取文件失败");
        return;
    }
    char name[CustomerName_MaxLength];
    while (fscanf(fp, "%s", name) != EOF) {
        Order* temp = (Order*)malloc(sizeof(Order));
        strcpy(temp->name, name);
        int DineInside, col, row,nums;
        fscanf(fp,"%d %d %d %d", &DineInside, &col, &row,&nums);
        temp->DineInside = DineInside;
        temp->seat.col = col;
        temp->seat.row = row;
        if (DineInside == 1) {
            SeatsMap[col][row].IsSelected = 1;
        }
        temp->isCheckedout = 0;
        temp->numbers = nums;
        int sumoffood;
        fscanf(fp, "%d", &sumoffood);
        temp->sumoffood = 0;
        temp->MoneyPaid = 0;
        for (int i = 0; i < sumoffood; i++) {
            char id[10];
            fscanf(fp, "%s", id);
            strcpy(temp->foods[temp->sumoffood++],id);
            temp->MoneyPaid += getPriceoffood(id);
        }
        time_t timep;
        struct tm* p;
        time(&timep);
        p = gmtime(&timep);
        int year = p->tm_year + 1900;
        int day = p->tm_mday;
        int month = p->tm_mon + 1;
        temp->date = { year,month,day };

        AddOrdertoOrderList(temp);
    }
    fclose(fp);
}

void ReWriteUnDoneOrders() {
    ordernode* temp = OrderListHead->next;
    FILE* fp = fopen("UnDoneOrders.txt", "w");
    if (fp == NULL) {
        perror("文件读取失败");
        return;
    }
    while (temp) {
        fprintf(fp, "%s", temp->order.name);
        fprintf(fp, "\n%d %d %d %d", temp->order.DineInside, temp->order.seat.col, temp->order.seat.row, temp->order.numbers);
        fprintf(fp, "\n%d\n", temp->order.sumoffood);
        for (int i = 0; i < temp->order.sumoffood; i++) {
            fprintf(fp,"%s ", temp->order.foods[i]);
        }   
        fprintf(fp,"\n");
        temp = temp->next;
    }
    fclose(fp);
}



void ShowWaitorLoginUI() {
    

    system("cls");
	printf("************************服务员登录界面**********************\n\n\n               请输入您的账户名  >>>___________");
    int x = wherex(), y = wherey();
    gotoxy(x - 11, y);
    char name[WaitorName_MaxLength];
    scanf("%s", name);
    printf("\n               请输入您的密码    >>>___________");
    x = wherex(), y = wherey();
    gotoxy(x - 11, y);
    char password[WaitorPasswd_MaxLength];
    scanf("%s", password);
    if (CheckPasswd(name, password) == 1)
    {
        printf("\n\n\n登录成功！");
        system("pause");
        system("cls");

        //设置系统当前服务员
        currentWaitor = getWaitorByName(name);  

        ShowWaitorMainUI();
    }
    else
    {
        printf("\n\n\nError>>>账户名不存在或密码输入错误，请重新输入！");
        system("pause");
        system("cls");
        ShowWaitorLoginUI();
    }
}


void LoadMenu() {
    foodsListHead->next = NULL;
    FILE* fp = fopen("menu.txt", "r");
    if (fp == NULL) {
        perror("文件读取失败");
        return;
    }
    char id[10];
    char name[FOODNAME_LENGTH_MAX];
    char foodtype[20];
    double price;
    int orderCount;
    while (5 == fscanf(fp, "%s %s %s %d %lf", id, name, foodtype, &orderCount, &price))
    {
        foodnode* f = (foodnode*)malloc(sizeof(foodnode));
        strcpy(f->data.name,name);
        strcpy(f->data.id, id);
        f->data.price = price;
        f->data.orderCount = orderCount;
        

        if (strcmp(foodtype, "招牌菜") == 0)
        {
            f->data.foodtype = specaility;
        }
        else if (strcmp(foodtype, "热菜") == 0)
        {
            f->data.foodtype = hot;
        }
        else if (strcmp(foodtype, "凉菜") == 0)
        {
            f->data.foodtype = cold;
        }
        else if (strcmp(foodtype, "饮料") == 0)
        {
            f->data.foodtype = beverage;
        }
        else if (strcmp(foodtype, "汤品") == 0)
        {
            f->data.foodtype = soup;
        }
        else {
            f->data.foodtype = staple;
        }
        //加入链表
        f->next = foodsListHead->next;
        foodsListHead->next = f;
    }
    //关闭文件
    fclose(fp);
 }

void Revereshow(foodnode* p) {
    if (p) {
        Revereshow(p->next);
        char foodtype[20];
        //将枚举类型的菜品信息转化为字符串以便输出
        switch (p->data.foodtype)
        {
        case specaility:
            strcpy(foodtype, "招牌菜");
            break;
        case hot:
            strcpy(foodtype, "热菜");
            break;
        case cold:
            strcpy(foodtype, "凉菜");
            break;
        case soup:
            strcpy(foodtype, "汤品");
            break;
        case staple:
            strcpy(foodtype, "主食");
            break;
        case beverage:
            strcpy(foodtype, "饮料");
            break;
        default:
            break;
        }
        printf("%-10s\t%-10s \t%-10s \t%-10d\t%-7.2lf\n", p->data.id, p->data.name, foodtype, p->data.orderCount, p->data.price);
    }
}


void ShowMenu() {
    system("cls");
    printf("=============================菜单=================================\n");
    printf("%-10s\t%-10s\t%-5s\t%-5s\t%-7s\n", "食品id", "食品名称", "食品类型", "被点次数", "价格");
    LoadMenu();
    foodnode* p = foodsListHead->next;
    Revereshow(p);
    printf("\n===================================================================\n");
}



int main() {
   
    LoadWaitors();
    LoadMenu();
    LoadUnDoneOrders();
    ShowWaitorLoginUI();
    ShowManageWaitorsUI();

}
