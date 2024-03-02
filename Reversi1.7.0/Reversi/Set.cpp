#include "Set.h"
#include <cstdio>
#include <fstream>
#include <direct.h>
#include <io.h>
#include <string>
#include <iostream>

char Set::Player_A = PLAYER;//PLAYER
char Set::Player_B = AI;
uint8_t Set::Background_color = 42;
uint8_t Set::Player_A_color = 37;
uint8_t Set::Player_B_color = 37;
uint8_t Set::hint_chess_color = 37;
uint8_t Set::empty_chess_color = 37;
short Set::normal_point[2] = {100,100};
short Set::bonus_point[2] = { 1000,1000 };
short Set::penalty_point[2] = {-1800, -1800};
short Set::distance_point[2] = { 10,10 };
short Set::distance_point_variation[2] = { 1,1 };
double Set::random[2] = { 0.9,0.9 };
short Set::delar_time = 1;
bool Set::Mouse_movement_display = true;//false
bool Set::Mouse_right_display = true;
bool Set::AI_skip = true;
bool Set::hint_chess_open = true;
short Set::Number_of_executions = 100;

void Set::set_up()
{
    printf("\33[1;0H╔");
    printf("═════");
    printf("╗");
    printf("\33[2;0H║ 返回║");
    printf("\33[3;0H");
    printf("╚");
    printf("═════");
    printf("╝\n");

    printf("\33[1;10H╔");
    printf("═════════");
    printf("╗");
    printf("\33[2;10H║ 離開遊戲║");
    printf("\33[3;10H");
    printf("╚");
    printf("═════════");
    printf("╝\n");

    printf("\33[1;23H╔");
    printf("═════");
    printf("╗");
    printf("\33[2;23H║ 還原║");
    printf("\33[3;23H");
    printf("╚");
    printf("═════");
    printf("╝\n");

    printf("黑棋玩家(Player A):  ");
    (Player_A == PLAYER) ? printf("\33[34mPLAYER\33[0m  AI\n") : printf("PLAYER  \33[34mAI\33[0m\n");

    printf("白棋玩家(Player B):  ");
    (Player_B == PLAYER) ? printf("\33[34mPLAYER\33[0m  AI\n") : printf("PLAYER  \33[34mAI\33[0m\n");

    printf("整體背景顏色:[\33[%dm  \33[0m]  \33[5m點擊設置\33[0m->[", Background_color);
    for (uint8_t i = 40; i < 48; i++)
        printf("\33[%dm  ",i);
    printf("\33[0m]\n");

    printf("黑棋顏色     [\33[%dm\33[%dm○\33[0m]  \33[5m點擊設置\33[0m->[", Background_color, Player_A_color);
    for (uint8_t i = 30; i < 38; i++)
        printf("\33[%dm○", i);
    printf("\33[0m]\n");

    printf("白棋顏色:    [\33[%dm\33[%dm●\33[0m]  \33[5m點擊設置\33[0m->[", Background_color, Player_B_color);
    for (uint8_t i = 30; i < 38; i++)
        printf("\33[%dm●", i);
    printf("\33[0m]\n");

    printf("提示棋顏色:  [\33[%dm\33[%dm˙\33[0m]  \33[5m點擊設置\33[0m->[", Background_color, hint_chess_color);
    for (uint8_t i = 30; i < 38; i++)
        printf("\33[%dm˙", i);
    printf("\33[0m]\n");

    printf("空棋顏色:    [\33[%dm\33[%dm□\33[0m]  \33[5m點擊設置\33[0m->[", Background_color, empty_chess_color);
    for (uint8_t i = 30; i < 38; i++)
        printf("\33[%dm□", i);
    printf("\33[0m]\n");

    printf("連著的不同棋加分:%7d\33[35mpoint\33[0m      %7d\33[36mpoint\33[0m\n", normal_point[0], normal_point[1]);
    printf("最邊線加分:      %7d\33[35mpoint\33[0m      %7d\33[36mpoint\33[0m\n", bonus_point[0], bonus_point[1]);
    printf("[最邊線-1]扣分:  %7d\33[35mpoint\33[0m      %7d\33[36mpoint\33[0m\n", penalty_point[0], penalty_point[1]);
    printf("中心擴散加分:    %7d\33[35mpoint\33[0m      %7d\33[36mpoint\33[0m\n", distance_point[0], distance_point[1]);
    printf("中心擴散加分倍率:%7d\33[35m倍\33[0m         %7d\33[36m倍\33[0m\n", distance_point_variation[0], distance_point_variation[1]);
    printf("AI人性隨機數:    %7.2f(%.2f\33[35m%%\33[0m)   %7.2f(%.2f\33[36m%%\33[0m)\n", random[0], random[0] * 100, random[1], random[1] * 100);

    printf("電腦下棋速度:    %7d\33[35mms\33[0m\n", delar_time);

    
    printf("即時滑鼠位置:            ");
    (Mouse_movement_display == true) ? printf("\33[34mTRUE\33[0m  FALSE\n") : printf("TRUE  \33[34mFALSE\33[0m\n");
    
    printf("右鍵棋子的內部詳細資料:  ");
    (Mouse_right_display == true) ? printf("\33[34mTRUE\33[0m  FALSE\n") : printf("TRUE  \33[34mFALSE\33[0m\n");

    printf("輪到AI時關閉點擊:        ");
    (AI_skip == true) ? printf("\33[34mTRUE\33[0m  FALSE\n") : printf("TRUE  \33[34mFALSE\33[0m\n");

    printf("提示棋:                  ");
    (hint_chess_open == true) ? printf("\33[34mTRUE\33[0m  FALSE\n") : printf("TRUE  \33[34mFALSE\33[0m\n");

    printf("AI調適次數:      %7d\33[35m次\33[0m\n", Number_of_executions);

}

void Set::LoadSetFile(const char* folderPath, const char* fileName)
{
    struct _finddata_t fileData;
    intptr_t findHandle;

    std::string searchPath = std::string(folderPath) + "/" + fileName;
    findHandle = _findfirst(searchPath.c_str(), &fileData);

    if (findHandle == -1) {
        std::cerr << "\33[3;30H文件未找到: " << fileName << searchPath << std::endl;
        return;
    }

    std::string filePath = std::string(folderPath) + "/" + fileName;

    std::ifstream inFile(filePath.c_str(), std::ios::binary);
    if (inFile.is_open()) {
        inFile >> Player_A 
            >> Player_B 
            >> Background_color 
            >> Player_A_color 
            >> Player_B_color 
            >> hint_chess_color
            >> empty_chess_color 
            >> normal_point[0]
            >> bonus_point[0]
            >> penalty_point[0]
            >> distance_point[0]
            >> distance_point_variation[0]
            >> random[0]
            >> normal_point[1]
            >> bonus_point[1]
            >> penalty_point[1]
            >> distance_point[1]
            >> distance_point_variation[1]
            >> random[1]
            >> delar_time 
            >> Mouse_movement_display 
            >> Mouse_right_display 
            >> AI_skip 
            >> hint_chess_open
            >> Number_of_executions;

        //inFile.read(reinterpret_cast<char*>(this), sizeof(Set)); // 讀取 Set 數據結構
        inFile.close();
    }
    else {
        std::cerr << "\33[3;45HUnable to open file for reading: " << filePath << std::endl;
    }

    _findclose(findHandle);
}

void Set::SaveSetFile(char filename[256])
{
    std::string board_folderPath = "./boards";// 資料夾路徑
    if (_access(board_folderPath.c_str(), 0) != 0) // 檢查資料夾是否存在，如果不存在就創建
        _mkdir(board_folderPath.c_str());

    std::string newFilename = board_folderPath + "/" + filename + ".board_set";// 修改 filename，加上 ".board_set"
    std::ofstream outFile(newFilename, std::ios::binary);// 打開二進位檔案

    if (outFile.is_open()) // 檢查是否成功打開檔案
    {
        outFile << Player_A << ' ' 
            << Player_B << ' ' 
            << Background_color << ' ' 
            << Player_A_color << ' ' 
            << Player_B_color << ' ' 
            << hint_chess_color << ' ' 
            << empty_chess_color << ' ' 
            << normal_point[0] << ' '
            << bonus_point[0] << ' '
            << penalty_point[0] << ' '
            << distance_point[0] << ' '
            << distance_point_variation[0] << ' '
            << random[0] << ' '
            << normal_point[1] << ' '
            << bonus_point[1] << ' '
            << penalty_point[1] << ' '
            << distance_point[1] << ' '
            << distance_point_variation[1] << ' '
            << random[1] << ' '
            << delar_time << ' ' 
            << Mouse_movement_display << ' ' 
            << Mouse_right_display << ' ' 
            << AI_skip << ' ' 
            << hint_chess_open << ' '
            << Number_of_executions
            << std::endl;

        //outFile.write(reinterpret_cast<char*>(this), sizeof(Set));// 寫入 Set 數據結構
        outFile.close();
        std::cout << "\33[1B\33[15D檔案已保存成功。\n" << newFilename << std::endl;
    }
    else
    {
        std::cerr << "無法打開檔案。\n" << newFilename << std::endl;
    }
    //system("cls");// 清除終端
}


void Set::reset()
{
    Player_A = PLAYER;
    Player_B = AI;
    Background_color = 42;
    Player_A_color = 37;
    Player_B_color = 37;
    hint_chess_color = 37;
    empty_chess_color = 37;
    for(uint8_t i=0;i<=1;i++)
    { 
        normal_point[i] = 100;
        bonus_point[i] = 1000;
        penalty_point[i] = -1800;
        distance_point[i] = 10;
        distance_point_variation[i] = 1;
        random[i] = 0.9;
    }
    delar_time = 1;
    Mouse_movement_display = true;
    Mouse_right_display = true;
    AI_skip = true;
    hint_chess_open = true;
    AI_skip = true;
    hint_chess_open = true;
    Number_of_executions = 100;
}
