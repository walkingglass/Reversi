#ifndef BOARD_H
#define BOARD_H

#define _CRT_SECURE_NO_WARNINGS
#define BOARD_SIZE 8  //棋盤X*X	(渲染正常極限範圍1~78)

#define BLACK 'B'
#define WHITE 'W'
#define EMPTY 'E'
#define OK 'O'

#define PLAYER 'P'
#define SYSTEM 'S'
#define AI 'A'


typedef unsigned char uint8_t;

class Board
{
private:

	short max_point = -32768;
	uint8_t max_x = 0;
	uint8_t max_y = 0;

	struct Data
	{
		char state = EMPTY;//棋子狀態: '黑' '白' '空' '可'
		short judge_0 = 0;
		short judge_45 = 0;
		short judge_90 = 0;
		short judge_135 = 0;
		short judge_180 = 0;
		short judge_225 = 0;
		short judge_270 = 0;
		short judge_315 = 0;

		uint8_t clamp_0 = 0;
		uint8_t clamp_45 = 0;
		uint8_t clamp_90 = 0;
		uint8_t clamp_135 = 0;
		uint8_t clamp_180 = 0;
		uint8_t clamp_225 = 0;
		uint8_t clamp_270 = 0;
		uint8_t clamp_315 = 0;

		int point = 0;
	};

	struct Data_history
	{
		char state = EMPTY;//棋子狀態: '黑' '白' '空' '可'

		uint8_t clamp_0 = 0;
		uint8_t clamp_45 = 0;
		uint8_t clamp_90 = 0;
		uint8_t clamp_135 = 0;
		uint8_t clamp_180 = 0;
		uint8_t clamp_225 = 0;
		uint8_t clamp_270 = 0;
		uint8_t clamp_315 = 0;
	};

	struct File
	{
		uint8_t num;
		char string[64];
	};

public:

	short wave = 1;

	struct Data board[BOARD_SIZE][BOARD_SIZE];
	struct Data_history board_history[BOARD_SIZE][BOARD_SIZE][BOARD_SIZE * BOARD_SIZE];
	struct File file[250];

	void CreateBoard();
	void ShowBoard(short wave);

	void Judge_0(uint8_t x, uint8_t y);
	void Judge_45(uint8_t x, uint8_t y);
	void Judge_90(uint8_t x, uint8_t y);
	void Judge_135(uint8_t x, uint8_t y);
	void Judge_180(uint8_t x, uint8_t y);
	void Judge_225(uint8_t x, uint8_t y);
	void Judge_270(uint8_t x, uint8_t y);
	void Judge_315(uint8_t x, uint8_t y);

	void JudgeBoard(int wave);

	int ChangeBoard(char who, char state, uint8_t x, uint8_t y);
	void RightButtom(short int wave, short x, short y);

	void ClearOK();
	void Reversal(short wave);//翻轉
	void SaveToFile(char filename[256]);
	void LoadFromFile(const char* filename, uint8_t filenum);
	void CopyBoard(short wave);
	uint8_t Ending(short wave);
	uint8_t HaveOK();
	uint8_t CountBoard(char state);
	void AICount(short wave);
	int AIPut(char state);
};

#endif
