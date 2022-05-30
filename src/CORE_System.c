#include "../include/Core_System.h"


bool initializeSystem(int argc, char const *argv[])
{
    // 读入所有系统管理员信息
    AdminList =  readAdminFromFile(ADMIN_FILE_PATH);
    // 读入所有服务员信息
    //
    // 读入所有菜品信息
    foodList = readFoodFromFile(FOOD_FILE_PATH);

    //设置控制台大小
    system("mode con cols=50 lines=40");
}

// 系统休眠指定时间
void systemSleep(unsigned long dwMilliseconds)
{
    Sleep((DWORD)dwMilliseconds);
}