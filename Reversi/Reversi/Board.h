#ifndef BOARD_H
#define BOARD_H

#define _CRT_SECURE_NO_WARNINGS
#define BOARD_SIZE 30  //棋盤X*X	(顯示工整極限範圍1~32)
//(1~10)
//(1-12)int -> short int
//(1-13)short int -> uint8_t
//(1-26)屬性 連結器 系統 堆疊預留大小 16777216(16MB)
//(1-31)屬性 連結器 系統 堆疊預留大小 33554432(32MB)

#define BLACK 'B'
#define WHITE 'W'
#define EMPTY 'E'
#define OK 'O'

#define PLAYER 'P'
#define SYSTEM 'S'


typedef unsigned char uint8_t;

class Board
{
private:

	struct Data
	{
		char state = EMPTY;//棋子狀態: '黑' '白' '空' '可'
		short int judge_0 = 0;
		short int judge_45 = 0;
		short int judge_90 = 0;
		short int judge_135 = 0;
		short int judge_180 = 0;
		short int judge_225 = 0;
		short int judge_270 = 0;
		short int judge_315 = 0;

		uint8_t clamp_0 = 0;
		uint8_t clamp_45 = 0;
		uint8_t clamp_90 = 0;
		uint8_t clamp_135 = 0;
		uint8_t clamp_180 = 0;
		uint8_t clamp_225 = 0;
		uint8_t clamp_270 = 0;
		uint8_t clamp_315 = 0;

		uint8_t point_0 = 0;
		uint8_t point_45 = 0;
		uint8_t point_90 = 0;
		uint8_t point_135 = 0;

		uint8_t total_point = 0;
	};

	struct File
	{
		uint8_t num;
		char string[64];
	};

public:
	struct Data board[BOARD_SIZE][BOARD_SIZE];
	struct Data board_history[BOARD_SIZE][BOARD_SIZE][BOARD_SIZE * BOARD_SIZE];

	struct File file[250];

	void CreateBoard();
	void ShowBoard(int wave);

	void Judge_0(int x, int y);
	void Judge_45(int x, int y);
	void Judge_90(int x, int y);
	void Judge_135(int x, int y);
	void Judge_180(int x, int y);
	void Judge_225(int x, int y);
	void Judge_270(int x, int y);
	void Judge_315(int x, int y);

	void JudgeBoard(int wave);

	int ChangeBoard(char who, char state, int x, int y);
	void RightButtom(int wave, int x, int y);

	void ClearOK();
	void Reversal(int wave);//翻轉
	void SaveToFile(char filename[256]);
	void LoadFromFile(const char* filename, uint8_t filenum);
	void CopyBoard(int wave);
	int Ending(int wave);
	int HaveOK();
	int CountBoard(char state);
};

#endif
