#ifndef SET_H
#define SET_H

typedef unsigned char uint8_t;

#define PLAYER 'P'
#define AI 'A'

class Set
{
public:

	static char Player_A;        //�´�										 (�w�] ���a)
	static char Player_B;        //�մ�										 (�w�] �q��AI)
	static uint8_t Background_color;  //����I���C��					     (�w�]42)(��)(40~47)
	static uint8_t Player_A_color;    //�´��C��						     (�w�]37)(��)(30~37)
	static uint8_t Player_B_color;    //�մ��C��							 (�w�]37)(��)(30~37)
	static uint8_t hint_chess_color;  //���ܴ��C��					         (�w�]37)(��)(30~37)
	static uint8_t empty_chess_color; //�Ŵ��C��		 			         (�w�]37)(��)(30~37)
	static short normal_point;    //�s�۪����P�ѥ[��						 (�w�]100)
	static short bonus_point;     //����u�[��								 (�w�]1000)
	static short penalty_point;   //[����u-1]����							 (�w�]-1800)
	static short distance_point;//�����X���[��								 (�w�]10)
	static short distance_point_variation;//�����X���[�����v				 (�w�]1)
	static double random;         //AI�H���H����							 (�w�]0.9)(0~1)
	static short delar_time;      //�q���U�ѳt��(����)(�V�����C�q���t��)	 (�i�]�m0)
	static bool Mouse_movement_display;//�Y�ɷƹ���m						 (�w�]��)
	static bool Mouse_right_display;   //�Ѥl�������ԲӸ��					 (�w�]�})
	static bool AI_skip;//����AI�� ���ݭn�I���@�U�ѽL(�����ɯ�F��AI����)  	 (�w�]�})
	static bool hint_chess_open;  //���ܴ�    					             (�w�]�})


	void set_up();
};

#endif // MOUSE_H
