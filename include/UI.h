/*
 * @Author: 林鹏飞
 * @ID: 202000810047
 * @Date: 2022-05-30
 * @LastEditors: LAPTOP-3VNCP688
 * @Description: 
 */

# ifndef __UI_H_
# define __UI_H_

#include "Core_Administrater1.h"


// 显示主界面
int ShowMainUI();

// 显示欢迎界面，返回登录用户类型{Admin, User}
enum UserType ShowWelcomeUI();

// 显示管理员界面
void ShowAdminUI();

// 显示服务员界面
void ShowWaiterUI();

// 

// 清空输入缓冲区
void clearScreenBuffer(void);

#define MAX 1000

# endif 