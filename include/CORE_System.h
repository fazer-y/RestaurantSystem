/*
 * @Author: 林鹏飞
 * @ID: 202000810047
 * @Date: 2022-05-30
 * @LastEditors: LAPTOP-3VNCP688
 * @Description: 
 */

# ifndef __CORE_SYSTEM_H_
# define __CORE_SYSTEM_H_

#include "UI.h"
#include "CORE_Administrater1.h"


enum UserType{undefine, Waiter, Admin};

// 餐厅当前信息
typedef struct RSCurrentInfo
{
    struct Admin currentAdmin;  // 当前管理员
    // 当前服务员
    enum UserType userType;
    
}RSCurrentInfo;

RSCurrentInfo rsCurrentInfo;


// 管理员信息链表
Adminnode *AdminList = NULL;

// 服务员信息链表
//

// 菜品信息链表
foodnode *foodList = NULL;


// 系统初始化
bool initializeSystem(int argc, char const *argv[]);

// 系统休眠指定时间
void systemSleep(unsigned long dwMilliseconds);


#endif /* __CORE_SYSTEM_H_ */