#include "../include/UI.h"
#include "../include/CORE_System.h"
#include <stdio.h>

int ShowMainUI()
{
    printf("111");
}

void clearScreenBuffer(void)
{
    char c;
    while ((c = getchar()) != EOF && c != '\n');
}

enum UserType ShowWelcomeUI()
{
    enum UserType userType = undefine;
    int typeInput = 0;
    system("cls");
    while( !(userType==Admin || userType==Waiter) )
    {
        printf("########## 山东大学（威海） 泰园餐厅 ##########\n\n");
        printf("\t请选择您的身份\n\n\n");
        printf("\t1) 服务员登录.\n\n");
        printf("\t2) 系统管理员登录.\n\n");
        printf("请输入你的身份对应的序号: [ ]\b\b");
        scanf("%d", &typeInput);
        clearScreenBuffer();
        system("cls");
        if( typeInput==1 )
        {
            printf("########## 山东大学（威海） 泰园餐厅 ##########\n\n");
            printf("\t请输入服务员账号: \n\n");
            printf("\t> ___________________________\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
            char password_input[ADMINPAS_LENGTH_MAX+1];
            char adminID_input[ADMINID_LENGTH_MAX+1];
            //scanf("%s", password_input);
            fscanf(stdin, "%s", password_input);//更安全的输入函数！
            clearScreenBuffer();
            printf("\t请输入服务员密码: \n\n");
            printf("\t> ___________________________\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
            fscanf(stdin, "%s", adminID_input);
            clearScreenBuffer();
            userType = Waiter;
            rsCurrentInfo.userType = userType;
        }
        else if( typeInput==2 )
        {
            printf("########## 山东大学（威海） 泰园餐厅 ##########\n\n");
            printf("\t请输入管理员账号: \n\n");
            printf("\t> ___________________________\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
            char password_input[ADMINPAS_LENGTH_MAX+1];
            char adminID_input[ADMINID_LENGTH_MAX+1];
            //scanf("%s", password_input);
            fscanf(stdin, "%s", password_input);//更安全的输入函数！
            clearScreenBuffer();
            printf("\t请输入管理员密码: \n\n");
            printf("\t> ___________________________\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
            fscanf(stdin, "%s", adminID_input);
            clearScreenBuffer();


            if(!findAdminByID(AdminList, adminID_input)) // 未找到管理员id
            {
                // 账号不存在
                printf("系统管理员账号不存在，请检查后再次输入!\n");
                rainbow_sleep(1000);
                userType = undefine;
            }
            else
            {
                // 查找管理员账户对应密码
                Adminnode *p = AdminList;
                bool pwdTrue = false;
                while(p!=NULL)
                {
                    if(strcmp(p->data.ID, adminID_input)==0)
                    {
                        if(strcmp(p->data.password, password_input) == 0)
                        {
                            pwdTrue = true;
                            break;
                        }
                    }
                    p = p->next;
                }

                // 登录成功
                if(pwdTrue) 
                {
                    userType = Admin;
                }
            }


            rsCurrentInfo.userType = userType;
            system("cls");
        }
    }
    return userType;
}