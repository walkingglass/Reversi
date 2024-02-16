#include "Board.h"
#include "Set.h"

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <direct.h>
#include <io.h>
#include <random>

Set set_board;

int ExtractDigits(const char* string, int num) {
    if (strcmp(string, "HIGH") == 0)
    {
        uint8_t HIGH = num / 100;
        return HIGH;
    }
    else if (strcmp(string, "LOW") == 0)
    {
        uint8_t LOW = num % 100;
        return LOW;
    }
}

void Board::CreateBoard()
{
    for (uint8_t y = 0; y < BOARD_SIZE; y++)
        for (uint8_t x = 0; x < BOARD_SIZE; x++)
            board[x][y].state = EMPTY;

    //初始化
    board[BOARD_SIZE / 2][BOARD_SIZE / 2].state = WHITE;
    board[BOARD_SIZE / 2 - 1][BOARD_SIZE / 2].state = BLACK;
    board[BOARD_SIZE / 2][BOARD_SIZE / 2 - 1].state = BLACK;
    board[BOARD_SIZE / 2 - 1][BOARD_SIZE / 2 - 1].state = WHITE;
}

void Board::ShowBoard(short wave)
{

    printf("\33[?25l\33[0;0H");//清除終端(去0,0)
    printf("╔═");
    for (uint8_t i = 0; i < BOARD_SIZE; i++)printf("══");

    printf("╗\n");

    for (uint8_t y = 0; y < BOARD_SIZE; y++)
    {
        printf("║ ");
        for (uint8_t x = 0; x < BOARD_SIZE; x++)
        {
            if (board[x][y].state == EMPTY)
                printf("\33[%dm\33[%dm□\33[0m", set_board.Background_color, set_board.empty_chess_color);
            else if (board[x][y].state == BLACK)
                printf("\33[%dm\33[%dm○\33[0m", set_board.Background_color, set_board.Player_A_color);
            else if (board[x][y].state == WHITE)
                printf("\33[%dm\33[%dm●\33[0m", set_board.Background_color, set_board.Player_B_color);
            else if (board[x][y].state == OK)
                printf("\33[%dm\33[%dm˙\33[0m", set_board.Background_color, set_board.hint_chess_color);//⊙
            else
                printf("%c", board[x][y].state);
        }
        printf("║\n");
    }
    printf("╚═");
    for (uint8_t i = 0; i < BOARD_SIZE; i++)printf("══");

    printf("╝\n");

    (wave % 2 == 0) ? printf("●") : printf("○");
    printf("Wave:%d\n", wave);

    short point = BOARD_SIZE * 2 + 6;

    printf("\33[1;%dH╔", point);
    printf("═════");
    printf("╗");
    printf("\33[2;%dH║ 儲存║", point);
    printf("\33[3;%dH", point);
    printf("╚");
    printf("═════");
    printf("╝");

    printf("\33[4;%dH╔", point);
    printf("═════");
    printf("╗");
    printf("\33[5;%dH║ 讀檔║", point);
    printf("\33[6;%dH", point);
    printf("╚");
    printf("═════");
    printf("╝");

    printf("\33[7;%dH╔", point);
    printf("═════");
    printf("╗");
    printf("\33[8;%dH║ 設置║", point);
    printf("\33[9;%dH", point);
    printf("╚");
    printf("═════");
    printf("╝");
}

void Board::Judge_0(uint8_t x, uint8_t y)
{
    uint8_t x_original = x, y_original = y;//保存原始位置
    char original_state = board[x_original][y_original].state;//原始色棋
    char opposite_state = (original_state == BLACK) ? WHITE : BLACK;//相反色棋

    while ((x + 1 < BOARD_SIZE) && (board[x + 1][y].state == original_state) && (original_state == WHITE || original_state == BLACK))
    {
        board[x_original][y_original].judge_direction[0]++;
        x++;
    }


    while ((x + 1 < BOARD_SIZE) && board[x + 1][y].state == opposite_state)
    {
        board[x_original][y_original].judge_direction[0] += 100;
        x++;
    }
}

void Board::Judge_45(uint8_t x, uint8_t y)
{
    uint8_t x_original = x, y_original = y;//保存原始位置
    char original_state = board[x_original][y_original].state;//原始色棋
    char opposite_state = (original_state == BLACK) ? WHITE : BLACK;//相反色棋

    while ((x + 1 < BOARD_SIZE) && (y > 0) && (board[x + 1][y - 1].state == original_state) && (original_state == WHITE || original_state == BLACK))
    {
        board[x_original][y_original].judge_direction[1]++;
        x++; y--;
    }


    while ((x + 1 < BOARD_SIZE) && (y > 0) && board[x + 1][y - 1].state == opposite_state)
    {
        board[x_original][y_original].judge_direction[1] += 100;
        x++; y--;
    }
}

void Board::Judge_90(uint8_t x, uint8_t y)
{
    uint8_t x_original = x, y_original = y;//保存原始位置
    char original_state = board[x_original][y_original].state;//原始色棋
    char opposite_state = (original_state == BLACK) ? WHITE : BLACK;//相反色棋

    while ((y > 0) && (board[x][y - 1].state == original_state) && (original_state == WHITE || original_state == BLACK))
    {
        board[x_original][y_original].judge_direction[2]++;
        y--;
    }


    while (y > 0 && board[x][y - 1].state == opposite_state)
    {
        board[x_original][y_original].judge_direction[2] += 100;
        y--;
    }
}

void Board::Judge_135(uint8_t x, uint8_t y)
{
    uint8_t x_original = x, y_original = y;//保存原始位置
    char original_state = board[x_original][y_original].state;//原始色棋
    char opposite_state = (original_state == BLACK) ? WHITE : BLACK;//相反色棋

    while ((x > 0) && (y > 0) && (board[x - 1][y - 1].state == original_state) && (original_state == WHITE || original_state == BLACK))
    {
        board[x_original][y_original].judge_direction[3]++;
        x--; y--;
    }


    while ((x > 0) && (y > 0) && board[x - 1][y - 1].state == opposite_state)
    {
        board[x_original][y_original].judge_direction[3] += 100;
        x--; y--;
    }
}

void Board::Judge_180(uint8_t x, uint8_t y)
{
    uint8_t x_original = x, y_original = y;//保存原始位置
    char original_state = board[x_original][y_original].state;//原始色棋
    char opposite_state = (original_state == BLACK) ? WHITE : BLACK;//相反色棋

    while ((x > 0) && (board[x - 1][y].state == original_state) && (original_state == WHITE || original_state == BLACK))
    {
        board[x_original][y_original].judge_direction[4]++;
        x--;
    }


    while (x > 0 && board[x - 1][y].state == opposite_state)
    {
        board[x_original][y_original].judge_direction[4] += 100;
        x--;
    }
}

void Board::Judge_225(uint8_t x, uint8_t y)
{
    uint8_t x_original = x, y_original = y;//保存原始位置
    char original_state = board[x_original][y_original].state;//原始色棋
    char opposite_state = (original_state == BLACK) ? WHITE : BLACK;//相反色棋

    while ((x > 0) && (y + 1 < BOARD_SIZE) && (board[x - 1][y + 1].state == original_state) && (original_state == WHITE || original_state == BLACK))
    {
        board[x_original][y_original].judge_direction[5]++;
        x--; y++;
    }


    while ((x > 0) && (y + 1 < BOARD_SIZE) && board[x - 1][y + 1].state == opposite_state)
    {
        board[x_original][y_original].judge_direction[5] += 100;
        x--; y++;
    }
}

void Board::Judge_270(uint8_t x, uint8_t y)
{
    uint8_t x_original = x, y_original = y;//保存原始位置
    char original_state = board[x_original][y_original].state;//原始色棋
    char opposite_state = (original_state == BLACK) ? WHITE : BLACK;//相反色棋

    while ((y + 1 < BOARD_SIZE) && (board[x][y + 1].state == original_state) && (original_state == WHITE || original_state == BLACK))
    {
        board[x_original][y_original].judge_direction[6]++;
        y++;
    }


    while (y + 1 < BOARD_SIZE && board[x][y + 1].state == opposite_state)
    {
        board[x_original][y_original].judge_direction[6] += 100;
        y++;
    }
}

void Board::Judge_315(uint8_t x, uint8_t y)
{
    uint8_t x_original = x, y_original = y;//保存原始位置
    char original_state = board[x_original][y_original].state;//原始色棋
    char opposite_state = (original_state == BLACK) ? WHITE : BLACK;//相反色棋

    while ((x + 1 < BOARD_SIZE) && (y + 1 < BOARD_SIZE) && (board[x + 1][y + 1].state == original_state) && (original_state == WHITE || original_state == BLACK))
    {
        board[x_original][y_original].judge_direction[7]++;
        x++; y++;
    }


    while ((x + 1 < BOARD_SIZE) && (y + 1 < BOARD_SIZE) && board[x + 1][y + 1].state == opposite_state)
    {
        board[x_original][y_original].judge_direction[7] += 100;
        x++; y++;
    }
}

void Board::JudgeBoard(int wave)
{
    for (uint8_t y = 0; y < BOARD_SIZE; y++)
        for (uint8_t x = 0; x < BOARD_SIZE; x++)
        {
            for (uint8_t i = 0; i < 8; i++)
                board[x][y].judge_direction[i] = 0;

            board[x][y].point = 0;
        }

    for (uint8_t y = 0; y < BOARD_SIZE; y++)
        for (uint8_t x = 0; x < BOARD_SIZE; x++)
        {
            char virtual_state = board[x][y].state;//虛擬色棋(OK)
            if (virtual_state == OK)
                board[x][y].state = (wave % 2 == 0) ? WHITE : BLACK;

            Judge_0(x, y);
            Judge_45(x, y);
            Judge_90(x, y);
            Judge_135(x, y);
            Judge_180(x, y);
            Judge_225(x, y);
            Judge_270(x, y);
            Judge_315(x, y);

            board[x][y].state = virtual_state;
        }

    for (uint8_t y = 0; y < BOARD_SIZE; y++)
        for (uint8_t x = 0; x < BOARD_SIZE; x++)
        {
            int x_original = x, y_original = y;//保存原始位置
            char original_state = board[x_original][y_original].state;//原始色棋
            char opposite_state = ' ';//相反色棋
            char now_state;//現在誰要下棋

            if (original_state == BLACK)opposite_state = WHITE;
            else if (original_state == WHITE)opposite_state = BLACK;

            now_state = (wave % 2 == 0) ? WHITE : BLACK;

            if (now_state == opposite_state)
            {
                uint8_t clamp[8];
                for (uint8_t i = 0; i < 8; i++)
                    clamp[i] = (board[x][y].judge_direction[i] >= 100)?1:0;

                if (clamp[0] + clamp[4] == 1)
                {
                    if (clamp[0] == 1)
                    {
                        ChangeBoard(SYSTEM, OK, x - ExtractDigits("LOW", board[x][y].judge_direction[4]) - 1, y);
                    }
                    else if (clamp[4] == 1)
                    {
                        ChangeBoard(SYSTEM, OK, x + ExtractDigits("LOW", board[x][y].judge_direction[0]) + 1, y);
                    }
                }
                if (clamp[1] + clamp[5] == 1)
                {
                    if (clamp[1] == 1)
                    {
                        ChangeBoard(SYSTEM, OK, x - ExtractDigits("LOW", board[x][y].judge_direction[5]) - 1, y + ExtractDigits("LOW", board[x][y].judge_direction[5]) + 1);
                    }
                    else if (clamp[5] == 1)
                    {
                        ChangeBoard(SYSTEM, OK, x + ExtractDigits("LOW", board[x][y].judge_direction[1]) + 1, y - ExtractDigits("LOW", board[x][y].judge_direction[1]) - 1);
                    }
                }
                if (clamp[2] + clamp[6] == 1)
                {
                    if (clamp[2] == 1)
                    {
                        ChangeBoard(SYSTEM, OK, x, y + ExtractDigits("LOW", board[x][y].judge_direction[6]) + 1);
                    }
                    else if (clamp[6] == 1)
                    {
                        ChangeBoard(SYSTEM, OK, x, y - ExtractDigits("LOW", board[x][y].judge_direction[2]) - 1);
                    }
                }
                if (clamp[3] + clamp[7] == 1)
                {
                    if (clamp[3] == 1)
                    {
                        ChangeBoard(SYSTEM, OK, x + ExtractDigits("LOW", board[x][y].judge_direction[7]) + 1, y + ExtractDigits("LOW", board[x][y].judge_direction[7]) + 1);
                    }
                    else if (clamp[7] == 1)
                    {
                        ChangeBoard(SYSTEM, OK, x - ExtractDigits("LOW", board[x][y].judge_direction[3]) - 1, y - ExtractDigits("LOW", board[x][y].judge_direction[3]) - 1);
                    }
                }
            }
        }
}

uint8_t Board::ChangeBoard(char who, char state, uint8_t x, uint8_t y)
{
    if (x >= 0 && y >= 0 && x < BOARD_SIZE && y < BOARD_SIZE)
    {
        if (who == SYSTEM)
            if (board[x][y].state == EMPTY)
                board[x][y].state = state;

        if (who == PLAYER)
            if (board[x][y].state == OK)
            {
                board[x][y].state = state;
                return 1;
            }
        if (who == AI)
            if (board[x][y].state == OK)
            {
                board[x][y].state = state;
                return 1;
            }
    }
    return 0;
}

void Board::RightButtom(short wave, short x, short y)
{
    system("cls");
    printf("\33[?25l\33[0;0H");//清除終端(去0,0)

    if (set_board.Mouse_right_display)
    {
        if (x >= 0 && y >= 0 && x < BOARD_SIZE && y < BOARD_SIZE)
        {
            printf(" \33[30Cboard[%d][%d].state:%3c\n\n", x, y, board[x][y].state);

            printf(" \33[30Cboard[%d][%d].judge_direction[0]:%3d\n", x, y, board[x][y].judge_direction[0]);
            printf(" \33[30Cboard[%d][%d].judge_direction[1]:%3d\n", x, y, board[x][y].judge_direction[1]);
            printf(" \33[30Cboard[%d][%d].judge_direction[2]:%3d\n", x, y, board[x][y].judge_direction[2]);
            printf(" \33[30Cboard[%d][%d].judge_direction[3]:%3d\n", x, y, board[x][y].judge_direction[3]);
            printf(" \33[30Cboard[%d][%d].judge_direction[4]:%3d\n", x, y, board[x][y].judge_direction[4]);
            printf(" \33[30Cboard[%d][%d].judge_direction[5]:%3d\n", x, y, board[x][y].judge_direction[5]);
            printf(" \33[30Cboard[%d][%d].judge_direction[6]:%3d\n", x, y, board[x][y].judge_direction[6]);
            printf(" \33[30Cboard[%d][%d].judge_direction[7]:%3d\n\n", x, y, board[x][y].judge_direction[7]);

            printf(" \33[30Cboard[%d][%d].point:%7d\n", x, y, board[x][y].point);
        }
        else
        {
            printf("\33[30C\33[31m溢出(無資料)\33[0m\n");

        }
    }
    else
        printf("\33[30C右鍵功能已關閉 請去\33[34m設置\33[0m設定\n");
}

void Board::ClearOK()
{
    for (uint8_t y = 0; y < BOARD_SIZE; y++)
        for (uint8_t x = 0; x < BOARD_SIZE; x++)
            if (board[x][y].state == OK)
                board[x][y].state = EMPTY;
}

void Board::Reversal(short wave)//翻轉
{
    char state = ' ';
    state = (wave % 2 == 1) ? WHITE : BLACK;

    for (uint8_t y = 0; y < BOARD_SIZE; y++)
        for (uint8_t x = 0; x < BOARD_SIZE; x++)
            if (board[x][y].state == BLACK || board[x][y].state == WHITE)//防虛擬棋被翻
            {
                uint8_t clamp[8],history_clamp[8];

                for (uint8_t i = 0; i < 8; i++)
                    clamp[i] = (board[x][y].judge_direction[i] >= 100) ? 1 : 0;

                for (uint8_t i = 0; i < 8; i++)
                    history_clamp[i] = (board_history[x][y][wave].judge_direction[i] >= 100) ? 1 : 0;

                for (uint8_t i = 0; i < 4; i++)
                    if (history_clamp[i+0] + history_clamp[i+4] == 1 && clamp[i + 0] + clamp[i + 4] == 2)//上回合1夾 現在這回合2夾
                        board[x][y].state = state;
            }
}

void Board::SaveToFile(char filename[256])
{
    std::string board_folderPath = "./boards";// 資料夾路徑
    if (_access(board_folderPath.c_str(), 0) != 0) // 檢查資料夾是否存在，如果不存在就創建
        _mkdir(board_folderPath.c_str());


    std::string folderPath = "./boards/board_" + std::to_string(BOARD_SIZE);// 資料夾路徑
    if (_access(folderPath.c_str(), 0) != 0) // 檢查資料夾是否存在，如果不存在就創建
        _mkdir(folderPath.c_str());

    std::string newFilename = folderPath + "/" + filename + ".board_" + std::to_string(BOARD_SIZE);// 修改 filename，加上 ".board_BOARD_SIZE"
    std::ofstream outFile(newFilename, std::ios::binary);// 打開二進位檔案

    if (outFile.is_open()) // 檢查是否成功打開檔案
    {
        outFile.write(reinterpret_cast<char*>(this), sizeof(Board));// 寫入 board 數據結構
        outFile.close();
        std::cout << "檔案已保存成功。\n" << newFilename << std::endl;
    }
    else
    {
        std::cerr << "無法打開檔案。\n" << newFilename << std::endl;
        Sleep(2500);
    }
    system("cls");// 清除終端
}



void Board::LoadFromFile(const char* folderPath, uint8_t filenum)
{
    struct _finddata_t fileData;
    intptr_t findHandle;

    std::string searchPath = std::string(folderPath) + "/board_" + std::to_string(BOARD_SIZE) + "/*";
    findHandle = _findfirst(searchPath.c_str(), &fileData);

    if (findHandle == -1) {
        std::cerr << "No files found in directory: " << searchPath << std::endl;
        return;
    }

    int currentFileNum = 0;

    do {
        if (!(fileData.attrib & _A_SUBDIR)) // 如果不是子目錄，處理文件
        {
            std::string filePath = std::string(folderPath) + "/board_" + std::to_string(BOARD_SIZE) + "/" + fileData.name;
            std::cout << fileData.name << std::endl;

            if (currentFileNum < 250)
            {
                file[currentFileNum].num = currentFileNum;                // 將檔案名稱保存到 struct File file[250]
                strncpy(file[currentFileNum].string, fileData.name, sizeof(file[currentFileNum].string) - 1);
                file[currentFileNum].string[sizeof(file[currentFileNum].string) - 1] = '\0';

                if (filenum >= 0 && currentFileNum == filenum)
                {
                    std::ifstream inFile(filePath.c_str(), std::ios::binary);
                    if (inFile.is_open()) {
                        inFile.read(reinterpret_cast<char*>(this), sizeof(Board));// 讀取 board 數據結構
                        inFile.close();
                    }
                    else {
                        std::cerr << "Unable to open file for reading: " << filePath << std::endl;
                    }
                    break;
                }
                currentFileNum++;
            }
            else
            {
                std::cerr << "Too many files found. Maximum limit reached." << std::endl;
                break;
            }
        }
    } while (_findnext(findHandle, &fileData) == 0);

    _findclose(findHandle);
}




void Board::CopyBoard(short wave)
{
    for (uint8_t y = 0; y < BOARD_SIZE; y++)
        for (uint8_t x = 0; x < BOARD_SIZE; x++)
            board_history[x][y][wave - 1] = board[x][y];

}




uint8_t Board::Ending(short wave)
{
    int total = 0;
    for (uint8_t y = 0; y < BOARD_SIZE; y++)
        for (uint8_t x = 0; x < BOARD_SIZE; x++)
            if (board[x][y].state == WHITE || board[x][y].state == BLACK)
                total++;

    int ok = 0;
    for (uint8_t y = 0; y < BOARD_SIZE; y++)
        for (uint8_t x = 0; x < BOARD_SIZE; x++)
        {
            if (board_history[x][y][wave - 1].state == OK)
                ok++;
            if (board_history[x][y][wave - 2].state == OK)
                ok++;

        }
    if (total >= BOARD_SIZE * BOARD_SIZE || ok == 0)
        return 1;

    else
        return 0;
}

uint8_t Board::HaveOK()
{
    int total = 0;
    for (uint8_t y = 0; y < BOARD_SIZE; y++)
        for (uint8_t x = 0; x < BOARD_SIZE; x++)
            if (board[x][y].state == OK)
                total++;
    if (total == 0)
        return 1;
    else
        return 0;
}

uint8_t Board::CountBoard(char state)
{
    short black = 0, white = 0;
    for (uint8_t y = 0; y < BOARD_SIZE; y++)
        for (uint8_t x = 0; x < BOARD_SIZE; x++)
            if (board[x][y].state == BLACK)
                black++;
            else if (board[x][y].state == WHITE)
                white++;
    if (state == BLACK)
        return black;
    else if (state == WHITE)
        return white;
}


double RandomNumber(double min) //範圍(min~1)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, 1.0);
    return dis(gen);
}

void Board::AICount(short wave)
{
    max_point = -32768;
    max_x = 0;
    max_y = 0;

    for (uint8_t y = 0; y < BOARD_SIZE; y++)
        for (uint8_t x = 0; x < BOARD_SIZE; x++)
            if (board[x][y].state == OK)
            {
                for (uint8_t i = 0; i < 8; i++)
                    board[x][y].point += set_board.normal_point * RandomNumber(set_board.random) * ExtractDigits("HIGH", board[x][y].judge_direction[i]);

                if (x == 0 || x == BOARD_SIZE - 1)
                    board[x][y].point += set_board.bonus_point * RandomNumber(set_board.random);
                if (y == 0 || y == BOARD_SIZE - 1)
                    board[x][y].point += set_board.bonus_point * RandomNumber(set_board.random);

                if (x == 1 || x == BOARD_SIZE - 2)
                    board[x][y].point += set_board.penalty_point * RandomNumber(set_board.random);
                if (y == 1 || y == BOARD_SIZE - 2)
                    board[x][y].point += set_board.penalty_point * RandomNumber(set_board.random);

                if (board[x][y].point > max_point)
                {
                    max_point = board[x][y].point;
                    max_x = x;
                    max_y = y;
                }

                uint8_t center = BOARD_SIZE / 2;
                if (x >= center)
                    board[x][y].point += (x - center) * set_board.distance_point * set_board.distance_point_variation;
                else if (x <= center)
                    board[x][y].point += (center - x) * set_board.distance_point * set_board.distance_point_variation;

                if (y >= center)
                    board[x][y].point += (y - center) * set_board.distance_point * set_board.distance_point_variation;
                else if (y <= center)
                    board[x][y].point += (center - y) * set_board.distance_point * set_board.distance_point_variation;

            }
}

uint8_t Board::AIPut(char state)
{
    if (ChangeBoard(AI, state, max_x, max_y) == 1)
        return 1;
}
