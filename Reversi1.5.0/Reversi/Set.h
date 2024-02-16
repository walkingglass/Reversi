#ifndef SET_H
#define SET_H

typedef unsigned char uint8_t;

#define PLAYER 'P'
#define AI 'A'

class Set
{
public:

	static char Player_A;        //黑棋										 (預設 玩家)
	static char Player_B;        //白棋										 (預設 電腦AI)
	static uint8_t Background_color;  //整體背景顏色					     (預設42)(綠)(40~47)
	static uint8_t Player_A_color;    //黑棋顏色						     (預設37)(白)(30~37)
	static uint8_t Player_B_color;    //白棋顏色							 (預設37)(白)(30~37)
	static uint8_t hint_chess_color;  //提示棋顏色					         (預設37)(白)(30~37)
	static uint8_t empty_chess_color; //空棋顏色		 			         (預設37)(白)(30~37)
	static short normal_point;    //連著的不同棋加分						 (預設100)
	static short bonus_point;     //最邊線加分								 (預設1000)
	static short penalty_point;   //[最邊線-1]扣分							 (預設-1800)
	static short distance_point;//中心擴散加分								 (預設10)
	static short distance_point_variation;//中心擴散加分倍率				 (預設1)
	static double random;         //AI人性隨機數							 (預設0.9)(0~1)
	static short delar_time;      //電腦下棋速度(延遲)(越高降低電腦負擔)	 (可設置0)
	static bool Mouse_movement_display;//即時滑鼠位置						 (預設關)
	static bool Mouse_right_display;   //棋子的內部詳細資料					 (預設開)
	static bool AI_skip;//輪到AI時 不需要點擊一下棋盤(關閉時能了解AI評分)  	 (預設開)
	static bool hint_chess_open;  //提示棋    					             (預設開)


	void set_up();
};

#endif // MOUSE_H
