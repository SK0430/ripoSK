#pragma once
#include <deque>

enum NObject{
		OBJ_PLAYER,
		OBJ_SPACE,
		OBJ_WALL,
		OBJ_GOAL,
		OBJ_BLOCK,
		OBJ_BLOCK_ON_GOAL,

		OBJ_UNKNOWN
};

class Nimotsu
{
	friend class NimotsuTest;

public:
	Nimotsu(void);
	~Nimotsu(void);

public:
	int loadMap(char file_name[],int m,int n);
	int getKeyInput();
	int moveRight();
	int moveLeft();
	int moveUp();
	int moveDown();
	int MoveCommon(int OneStep,int TwoStep);
	int updateGame();
	NObject* getObjectState();
	void checkObject(int move);
	void drawGraphic();
	void playerMove();

private:
	void createState();

	int m_width;
	int m_height;
	int m_pPos;
	std::deque<int> m_targetPos;
	int m_nPos1;
	int m_nPos2;
	char* m_map;
	NObject* m_state;
	int OneStep;//プレイヤーの移動量
	int TwoStep;//移動直前のプレイヤーの二歩先
	bool judge_move;//移動可否結果が代入される
};