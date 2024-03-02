#ifndef BOARD_H
#define BOARD_H

#define _CRT_SECURE_NO_WARNINGS
#define BOARD_SIZE 8  //´Ñ½LX*X	(´è¬V¥¿±`·¥­­½d³ò1~78)

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
		char state = EMPTY;//´Ñ¤lª¬ºA: '¶Â' '¥Õ' 'ªÅ' '¥i'
		short judge_direction[8] = { 0 };
		int point = 0;
	};


	struct File
	{
		uint8_t num;
		char string[64];
	};

public:

	short wave = 1;

	struct Data board[BOARD_SIZE][BOARD_SIZE];
	struct Data board_history[BOARD_SIZE][BOARD_SIZE][BOARD_SIZE * BOARD_SIZE];
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

	uint8_t ChangeBoard(char who, char state, uint8_t x, uint8_t y);
	void RightButtom(short wave, short x, short y);

	void ClearOK();
	void Reversal(short wave);//Â½Âà
	void SaveToFile(char filename[256]);
	void LoadFromFile(const char* filename, uint8_t filenum);
	void CopyBoard(short wave);
	uint8_t Ending(short wave);
	uint8_t HaveOK();
	uint8_t CountBoard(char state);
	void AICount(uint8_t who, short wave);//who (0 or 1)
	uint8_t AIPut(char state);
	void regret_chess(short &wave);
};

#endif
