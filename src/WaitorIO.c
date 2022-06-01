#include "../include/CORE_Waitor.h"


void DeleteWaitorOfList(char* name) {
    waitor* temp = WaitorListHead;
    while (temp->next && strcmp(temp->next->name, name) == 0) {
        waitor* deletewaitor = temp->next;
        temp->next = deletewaitor->next;
        free(temp);
    }
}


//����������ɫ
void color(const unsigned short textColor)
{
    if (textColor >= 0 && textColor <= 15)
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), textColor);
    else
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

//��������ǰ��ɫ�ͱ���ɫ
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
    printf("======================��������============================\n");
    printf("%-10s \t%-10s \t%-10s \t%-10s\n", "���", "�˿�����", "ʱ��", "֧�����");
    //��ʾDoneOrders
    FILE* fp = fopen("DoneOrders.txt", "r");
    char name[30];
    int year, month, date;
    double moneypaid;
    int count = 0;
    while (5 == fscanf(fp, "%s %d %d %d %lf", name, &year, &month, &date,&moneypaid)){
        printf("%-10d \t%-10s  \t%d��%d��%d�� \t%-10.2lf\n",++count, name, year, month, date,moneypaid);
    }
    printf("\n============================================================");
    printf("\n�����������������");
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
    printf("===============����ʵʱ��λͼ==================\n ");
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

//������
int wherex()
{
    CONSOLE_SCREEN_BUFFER_INFO pBuffer;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &pBuffer);
    return (pBuffer.dwCursorPosition.X + 1);
}
//��ȡ����λ��y
int wherey()
{
    CONSOLE_SCREEN_BUFFER_INFO pBuffer;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &pBuffer);
    return (pBuffer.dwCursorPosition.Y + 1);
}
//���ù���λ��
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
        perror("�ļ���ȡʧ��");
        return 0;
    }
    //�������ȶ���
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
    //��д����
    time_t timep;
    struct tm* p;
    time(&timep);
    p = gmtime(&timep);
    int year = p->tm_year + 1900;
    int day = p->tm_mday;
    int month = p->tm_mon + 1;

    FILE* fp = fopen("WaitorsInfo.txt", "w");
    if (fp == NULL) {
        perror("�ļ���ȡʧ��");
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
    printf("===================����Ա�������=====================\n");
    while (true) 
    {
        color(12);
        printf("\n(1)��ӷ���Ա\n(2)���·���Ա\n(3)�˳�\n");
        color(7);
        printf("������������ ��  ��");
        gotoxy(wherex() - 3, wherey());
        int index;
        scanf("%d", &index);
        switch (index) 
        {
        case 1: 
        {
            printf("\n��������Ҫ��ӵķ���Ա���� >>>_________");
            gotoxy(wherex() - 6, wherey());
            char name[WaitorName_MaxLength];
            scanf("%s", name);
            printf("\n���������Ա��¼���� >>>_________");
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
    printf("\n��������Ҫ���µķ���Ա����������0ȡ����>>>___________");
    int x = wherex(), y = wherey();
    gotoxy(x - 6, y);
    char name[WaitorName_MaxLength];
    scanf("%s", name);
    if (strcmp(name, "0") == 0)
        return;
    waitor* temp = getWaitorByName(name);
    while(temp == NULL) {
        printf("\n����Ա�����ڣ����������루����0ȡ����>>>___________");
        x = wherex(), y = wherey();
        gotoxy(x - 6, y);
        scanf("%s", name);
        if (strcmp(name, "0") == 0)
            return;
        waitor* temp = getWaitorByName(name);
    }

    printf("\n      (1)��������\n      (2)��������\n      (3)���·�����Ա����\n      (4)ɾ��\n      (5)����");
    while (true) {
        printf("\n��������Ҫѡ��Ĳ�����š�  ��");
        gotoxy(wherex() - 3, wherey());
        int index;
        scanf("%d", &index);

        switch (index) {
        case 1: 
        {
            printf("\n��������º������������0ȡ����>>>________");
            gotoxy(wherex() - 5, wherey());
            scanf("%s", name);
            if (strcmp(name, "0") == 0)
                continue;
            //��������
            strcpy(temp->name, name);
            printf("\n���³ɹ���");
            UpdateWaitorsInfo();
        }
            break;
        case 2:
        {
            printf("\n��������º�����루����0ȡ����>>>________");
            gotoxy(wherex() - 5, wherey());
            scanf("%s", name);
            if (strcmp(name, "0") == 0)
                continue;
            //��������
            strcpy(temp->passwd, name);
            printf("\n���³ɹ���");
            UpdateWaitorsInfo();
        }
            break;
        case 3:
        {
            printf("\n��������º�ķ�������������-1ȡ����>>>________");
            gotoxy(wherex() - 5, wherey());
            int sum;
            scanf("%d", &sum);
            if (sum < 0)
                continue;
            //��������
            temp->sumofserve = sum;
            printf("\n���³ɹ���");
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
        perror("�ļ���ȡʧ��");
    }
    //�����ڣ�������ǽ�������ڣ����������Ա����ȫ�����㣬����ֱ��ת��Ϊ����
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
        //�޸��ļ�
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
    printf("\n==============================����Ա��Ϣ===============================");
    printf("\n%-10s \t%-10s \t%-10s", "����", "����", "���շ�������");
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
        SeatsMap[delnode->order.seat.col][delnode->order.seat.row].IsSelected = 0;//������λ
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
        perror("�ļ���ȡʧ��");
        return;
    }
    while (temp) {
        char typeoffood[FOODNAME_LENGTH_MAX];
        foodType type = temp->data.foodtype;
        switch (type) {
        case specaility:
            strcpy(typeoffood, "���Ʋ�");
            break;
        case staple:
            strcpy(typeoffood, "��ʳ");
            break;
        case  hot:
            strcpy(typeoffood, "�Ȳ�");
            break;
        case cold:
            strcpy(typeoffood, "����");
            break;
        case soup:
            strcpy(typeoffood, "��");
            break;
        case beverage:
            strcpy(typeoffood, "����");
            break;
        }
        fprintf(fp, "%s %s %s %d %.2lf\n", temp->data.id, temp->data.name,typeoffood, temp->data.orderCount, temp->data.price);
        temp = temp->next;
    } 
    fclose(fp);
}

void CheckOut() {
    printf("��ѡ��Ҫ���˶����Ĺ˿���>>>__________");
    int x = wherex(), y = wherey();
    gotoxy(x-10,y);
    char name[CustomerName_MaxLength];
    scanf("%s", name);
    ordernode* ordertocheck = getOrderbyName(name);
    while(ordertocheck == NULL) {
        printf("\n�˿Ͳ����ڣ�����������,����0ȡ������ >>>");
        scanf("%s", name);
        if (strcmp(name, "0") == 0) {
            return;
        }
            
        ordertocheck = getOrderbyName(name);
    }
    //������˲���
    //1.��������ɾ��
    //2.д��DoneOrders.txt
    //3.��λ��Ϊ0
    //4.���Ӳ�Ʒ�㵥����
    LoadMenu();
    for (int i = 0; i < ordertocheck->order.sumoffood; i++) {
        //�޸Ĵ�����Ȼ����д���ļ�
        UpdateCountofFood(ordertocheck->order.foods[i]);
    }
    ReWriteBackFood();

    deleteOrder(name);
   
    FILE* fp = fopen("DoneOrders.txt", "a+");
    if (fp == NULL) {
        perror("�ļ���ȡʧ��");
        return;
    }
    fprintf(fp, "%s %d %d %d %.2lf", ordertocheck->order.name, ordertocheck->order.date.year, ordertocheck->order.date.month, ordertocheck->order.date.day, ordertocheck->order.MoneyPaid);
    fclose(fp);
    free(ordertocheck);
}

void ShowCheckOutUI();


void DeletetheOrder() {
    printf("\n��������Ҫɾ���Ķ����Ĺ˿���>>>__________");
    int x = wherex(), y = wherey();
    gotoxy(x - 10, y);
    char name[CustomerName_MaxLength];
    scanf("%s", name);
    ordernode* ordertocheck = getOrderbyName(name);
    while (ordertocheck == NULL) {
        printf("\n�˿Ͳ����ڣ�����������,����0ȡ��ɾ��>>>");
        scanf("%s", name);
        if (strcmp(name, "0") == 0) {
            return;
        }
        ordertocheck = getOrderbyName(name);
    }
    deleteOrder(name);
    printf("\nɾ���ɹ�!");
    system("pause");

}

void SearchOrder() {
    printf("\n��������Ҫ���ҵĶ����Ĺ˿���>>>__________");
    int x = wherex(), y = wherey();
    gotoxy(x - 10, y);
    char name[CustomerName_MaxLength];
    scanf("%s", name);
    ordernode* temp = getOrderbyName(name);
    if (temp == NULL) {
        printf("\nδ�ҵ���ض�����");
    }
    else {
        printf("Ϊ����ѯ�����¶�����Ϣ:\n===============================================\n");
        printf("�˿���:  %s\n", temp->order.name);
        color(12);
        printf("%-10s \t%-10s \t%-10s\n", "��Ʒ", "����", "����");
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
        //ͳ�����
        for (int i = 0; i < 1000; i++) {
            if (sum[i] != 0) {
                //������ת��Ϊ#xxx�����ҵ������ͼ۸�
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
                //��ӡ
                printf("%-10s \t%-10d \t%-10.2lf\n", name, sum[i], price);
            }
        }
        printf("\n�ۼ�:  %.2lfԪ\n===============================================\n", temp->order.MoneyPaid);
    }
       
}

void ShowUnCheckedOrderUI() {
    system("cls");
    printf("==========================δ���˶�������=============================\n");
    ordernode* temp = OrderListHead->next;

    while (temp) {
        printf("�˿���:  %s\n", temp->order.name);
        color(12);
        printf("%-10s \t%-10s \t%-10s\n","��Ʒ","����","����");
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
        //ͳ�����
        for (int i = 0;i<1000; i++) {
            if (sum[i] != 0) {
                //������ת��Ϊ#xxx�����ҵ������ͼ۸�
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
                //��ӡ
                printf("%-10s \t%-10d \t%-10.2lf\n",name,sum[i],price);
            }
        }
        printf("\n�ۼ�:  %.2lf Ԫ\n", temp->order.MoneyPaid);
        printf("----------------------------------------------------------------\n");
        temp = temp->next;
    }
    system("pause");
    ShowWaitorMainUI();
}

//�޸Ķ������к���
void UpdateNameofOrder(ordernode* theorder) {
    printf("\n��������º�Ĺ˿�����(����0ȡ������) >>>_________");
    gotoxy(wherex()-5,wherey());
    char name[CustomerName_MaxLength];
    scanf("%s", name);
    if (strcmp(name, "0") == 0) {
        return;
    }
    //��������
    ordernode* temp = getOrderbyName(name);
    if (temp != NULL && temp != theorder) {
        printf("\n�ù˿����Ѵ��ڣ����������룡");
        UpdateNameofOrder(theorder);
        return;
    }
    strcpy(theorder->order.name, name);
    printf("\n���³ɹ���\n");
    system("pause");
    return;
}

void AddFoodtoOrder(ordernode* theorder) {
    printf("\n������Ҫ��ӵĲ�ƷID�����������в�Ʒ\n");
    ShowMenu();
    printf("\n��������Ҫ��ӵĲ�ƷID������0����>>>  ");
    char id[10];
    while (scanf("%s", id)) {
        if (strcmp(id, "0") == 0)
            break;
        strcpy(theorder->order.foods[theorder->order.sumoffood++], id);
        theorder->order.MoneyPaid += getPriceoffood(id);
    }
    printf("\n��ӳɹ���\n");
    system("pause");
    return;
}

void DelFoodofOrder(ordernode* theorder) {
    printf("\n������Ҫɾ���Ĳ�ƷID�����������в�Ʒ\n");
    ShowMenu();
    printf("\n��������Ҫɾ���Ĳ�ƷID������0����>>>  ");
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
    printf("\n��Ʒɾ���ɹ�!\n");
}

void ChangeOrder() {
    printf("\n��������Ҫ�޸Ķ����Ĺ˿���>>>__________");
    int x = wherex(), y = wherey();
    gotoxy(x - 10, y);
    char name[CustomerName_MaxLength];
    scanf("%s", name);
    ordernode* temp = getOrderbyName(name);
    if (temp == NULL) {
        printf("\nδ�ҵ���ض���!\n");
        system("pause");
        return;
    }
    printf("�ö�����Ϣ����:\n===============================================\n");
    printf("�˿���:  %s\n", temp->order.name);
    color(12);
    printf("%-10s \t%-10s \t%-10s\n", "��Ʒ", "����", "����");
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
            //��ӡ
            printf("%-10s \t%-10d \t%-10.2lf\n", name, sum[i], price);
        }
    }
    printf("\n�ۼ�:  %.2lfԪ\n===============================================\n", temp->order.MoneyPaid);
    //�޸�ѡ��
    while (true) {
        color(12);
        printf("\n(1)�޸Ķ��������˿���\n(2)��Ӳ�Ʒ\n(3)ɾ����Ʒ\n(4)�˳�\n\n");
        color(7);
        printf("\n������������>>>_________");
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
    printf("==========================���˽���=============================\n");
    ordernode* temp = OrderListHead->next;
    
    while (temp) {
        printf("�˿���:  %s\n",temp->order.name);
        color(12);
        printf("%-10s \t%-10s \t%-10s\n", "��Ʒ", "����", "����");
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
        //ͳ�����
        for (int i = 0; i < 1000; i++) {
            if (sum[i] != 0) {
                //������ת��Ϊ#xxx�����ҵ������ͼ۸�
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
                //��ӡ
                printf("%-10s \t%-10d \t%-10.2lf\n", name, sum[i], price);
            }
        }
        printf("\n�ۼ�:  %.2lf Ԫ\n", temp->order.MoneyPaid);
        printf("----------------------------------------------------------------\n");
        temp = temp->next;
    }
    printf("=================================================================\n");
    while (true) {
        printf("\n��ѡ�����²�����\n");
        printf("(1) ���˶���\n");
        printf("(2) ��ѯ����\n");
        printf("(3) ɾ������\n");
        printf("(4) �޸Ķ���\n");
        printf("(5) ����������\n");
        printf("�����������ţ� ��  ��");
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
    CurrentOrder = *order;//���õ�ǰ������
    //���ö���ʱ��
    time_t timep;
    struct tm* p;
    time(&timep);
    p = gmtime(&timep);
    order->date.year = p->tm_year + 1900;
    order->date.day = p->tm_mday;
    order->date.month = p->tm_mon + 1;

    printf("***********************��ͽ���************************\n\n\n");
    printf("������˿�����  >>>____________");
    int x = wherex(), y = wherey();
    gotoxy(x - 8, y);
    char name[CustomerName_MaxLength];
    scanf("%s",name);
    printf("�������ò�����  >>>____________");
    x = wherex(), y = wherey();
    gotoxy(x - 8, y);
    int num;
    scanf("%d", &num);

    //���ö�������
    order->numbers = num;
    strcpy(order->name, name);
    order->sumoffood = 0;
    order->isCheckedout = 0;
    order->MoneyPaid = 0;

    //���ӷ���Ա������Ա������
    currentWaitor->sumofserve += num;

    printf("�����ò��밴 a\n��������밴 b\n>>>");
    char select[2];
    scanf("%s", select);

    if (strcmp(select,"a")==0) 
    {
        ShowSeatMap();
        printf("��ѡ������  ��  ����  ��");
        int x = wherex(), y = wherey();
        gotoxy(x - 10, y);
        int col, row;
        scanf("%d", &col);
        gotoxy(x -3, y);
        scanf("%d", &row);
        //���ö�������


        while (SeatsMap[col][row].IsSelected == 1) {
            printf("\n��λ���ѱ�ռ�ã�������ѡ����λ��");
            printf("\n��ѡ������  ��  ����  ��");
            int x = wherex(), y = wherey();
            gotoxy(x - 10, y);
            scanf("%d", &col);
            gotoxy(x - 3, y);
            scanf("%d", &row);
        }



        order->DineInside = 1;
        order->seat.col = col;
        order->seat.row = row;
        //���ø����Ѿ���ռ��
        SeatsMap[col][row].IsSelected = 1;
        
    }
    else
    {
        order->DineInside = 0;
    }
   
    ShowMenu();
    printf("�������ƷID,�Կո�ָ�,��0�������� >>>  ");
    char id[10];
    while (scanf("%s", id)) {
        if (strcmp(id, "0") == 0)
            break;
        strcpy(order->foods[order->sumoffood++], id);
        order->MoneyPaid += getPriceoffood(id);
    }
    //�����������
    AddOrdertoOrderList(order);//����ϵͳ���ڴ���Ķ���������

    printf("\n�����������������:");
    system("pause");
    ShowWaitorMainUI();
}


void ExitWaitorMainUI() {
    UpdateWaitorsInfo();
    ReWriteUnDoneOrders();
}

void ShowWaitorMainUI() {
    system("cls");
    printf("***********************����Ա������************************\n\n\n");
    printf("             ---------------------------------             \n\n");
    printf("            |        (1) �鿴�˵�             |            \n");
    printf("            |        (2) ���                 |            \n");
    printf("            |        (3) �鿴����             |            \n");
    printf("            |        (4) ����                 |            \n");
    printf("            |        (5) �鿴��λ             |            \n");
    printf("            |        (6) �鿴δ���˶���       |            \n");
    printf("            |        (7) �˳�                 |            \n");
    printf("             ---------------------------------             \n\n\n");
    printf("***********************************************************\n\n");
    while (true) {
        printf("��ѡ�������� ��  ��");
        int x = wherex(), y = wherey();
        gotoxy(x - 3, y);
        int index;
        scanf("%d", &index);
        switch (index) {
        case 1:
            //�鿴�˵�������pj��
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
        perror("��ȡ�ļ�ʧ��");
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
        perror("�ļ���ȡʧ��");
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
	printf("************************����Ա��¼����**********************\n\n\n               �����������˻���  >>>___________");
    int x = wherex(), y = wherey();
    gotoxy(x - 11, y);
    char name[WaitorName_MaxLength];
    scanf("%s", name);
    printf("\n               ��������������    >>>___________");
    x = wherex(), y = wherey();
    gotoxy(x - 11, y);
    char password[WaitorPasswd_MaxLength];
    scanf("%s", password);
    if (CheckPasswd(name, password) == 1)
    {
        printf("\n\n\n��¼�ɹ���");
        system("pause");
        system("cls");

        //����ϵͳ��ǰ����Ա
        currentWaitor = getWaitorByName(name);  

        ShowWaitorMainUI();
    }
    else
    {
        printf("\n\n\nError>>>�˻��������ڻ���������������������룡");
        system("pause");
        system("cls");
        ShowWaitorLoginUI();
    }
}


void LoadMenu() {
    foodsListHead->next = NULL;
    FILE* fp = fopen("menu.txt", "r");
    if (fp == NULL) {
        perror("�ļ���ȡʧ��");
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
        

        if (strcmp(foodtype, "���Ʋ�") == 0)
        {
            f->data.foodtype = specaility;
        }
        else if (strcmp(foodtype, "�Ȳ�") == 0)
        {
            f->data.foodtype = hot;
        }
        else if (strcmp(foodtype, "����") == 0)
        {
            f->data.foodtype = cold;
        }
        else if (strcmp(foodtype, "����") == 0)
        {
            f->data.foodtype = beverage;
        }
        else if (strcmp(foodtype, "��Ʒ") == 0)
        {
            f->data.foodtype = soup;
        }
        else {
            f->data.foodtype = staple;
        }
        //��������
        f->next = foodsListHead->next;
        foodsListHead->next = f;
    }
    //�ر��ļ�
    fclose(fp);
 }

void Revereshow(foodnode* p) {
    if (p) {
        Revereshow(p->next);
        char foodtype[20];
        //��ö�����͵Ĳ�Ʒ��Ϣת��Ϊ�ַ����Ա����
        switch (p->data.foodtype)
        {
        case specaility:
            strcpy(foodtype, "���Ʋ�");
            break;
        case hot:
            strcpy(foodtype, "�Ȳ�");
            break;
        case cold:
            strcpy(foodtype, "����");
            break;
        case soup:
            strcpy(foodtype, "��Ʒ");
            break;
        case staple:
            strcpy(foodtype, "��ʳ");
            break;
        case beverage:
            strcpy(foodtype, "����");
            break;
        default:
            break;
        }
        printf("%-10s\t%-10s \t%-10s \t%-10d\t%-7.2lf\n", p->data.id, p->data.name, foodtype, p->data.orderCount, p->data.price);
    }
}


void ShowMenu() {
    system("cls");
    printf("=============================�˵�=================================\n");
    printf("%-10s\t%-10s\t%-5s\t%-5s\t%-7s\n", "ʳƷid", "ʳƷ����", "ʳƷ����", "�������", "�۸�");
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
