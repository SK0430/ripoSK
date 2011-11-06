//Nimotsu.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include <iostream>
#include <string>
#include "Nimotsu.h"
#include <stdio.h>

using namespace std;


Nimotsu::Nimotsu(void) : m_state(NULL)
	, m_width(0)
	, m_height(0)
{
	// とりあえずデータは固定でロード
	m_map = new char[256];
	/*m_map = "\
			########\n\
			# .. P #\n\
			# OO   #\n\
			#      #\n\
			########";*/

	/*m_width = 8;
	m_height = 5;*/
	//createState();
}

Nimotsu::~Nimotsu(void)
{
	delete[] m_map;
	delete[] m_state;
}

int Nimotsu::getKeyInput()
{
	string input;
	
	getline(cin, input);

	if (input == "h")
		moveLeft();
	else if (input == "l")
		moveRight();
	else if (input == "k")
		moveUp();
	else if (input == "j")
		moveDown();
	else if (input == "q")
		return 2;
	else
		cout << "Invalid Character" << endl;
	return 0;
}

int Nimotsu::moveLeft()
{
	//左方向の移動
	cout<<"左へ移動"<<endl;
	OneStep=-1;
	TwoStep=-2;
	MoveCommon(OneStep,TwoStep);
	return 0;
}

int Nimotsu::moveRight()
{
	//右方向の移動
	cout<<"右へ移動"<<endl;
	OneStep=1;
	TwoStep=2;
	MoveCommon(OneStep,TwoStep);
	return 0;
}

int Nimotsu::moveUp()
{
//上方向の移動
	cout<<"上へ移動"<<endl;
	OneStep=-8;
	TwoStep=-16;
	MoveCommon(OneStep,TwoStep);
	return 0;
}

int Nimotsu::moveDown()
{
	cout<<"下へ移動"<<endl;
	OneStep=8;
	TwoStep=16;
	MoveCommon(OneStep,TwoStep);
	return 0;
}
int Nimotsu::MoveCommon(int OneStep,int TwoStep){
	cout<<"m_pPos@MoveCommon"<<m_pPos<<",OneStep@MoveCommon="<<OneStep<<endl;//"TwoStep@MoveCommon="<<TwoStep<<endl;
	/*-------1016デバッグコード-------
			cout<<m_state[m_pPos-8]<<endl;
			cout<<m_state[m_pPos+4]<<endl;
			cout<<m_state[m_pPos+5]<<endl;
			cout<<m_state[m_pPos+6]<<endl;
		
			*/
	cout<<"before:移動直前のプレイヤーの位置"<<m_state[m_pPos]\
	<<"移動先"<<m_state[m_pPos+OneStep]\
	<<"移動直前のプレイヤーから二歩先"<<m_state[m_pPos+TwoStep]<<endl;
	judge_move=false;//移動可否結果を変数に代入
	
	if(m_state[m_pPos+OneStep]==OBJ_WALL){//移動可否判定　不可のケース1
				//一歩先が壁の場合
		judge_move=false;
	}else if((m_state[m_pPos+OneStep]==OBJ_BLOCK)&&(m_state[m_pPos+TwoStep]==OBJ_BLOCK||m_state[m_pPos+TwoStep]==OBJ_WALL)){//移動可否判定　不可のケース2
				//一歩先が荷物であり且二歩先が荷物または壁である場合
		judge_move=false;
	}else{//移動可否判定　可能
		judge_move=true;
		//-------現在地の更新----------
			/*-------1016デバッグコード-------
			cout<<m_state[m_pPos-8]<<endl;
			cout<<m_state[m_pPos+4]<<endl;
			cout<<m_state[m_pPos+5]<<endl;
			cout<<m_state[m_pPos+6]<<endl;
		
			*/
		if(m_state[m_pPos-8]==OBJ_WALL&&\
			(((m_state[m_pPos+4]==OBJ_WALL)&&(m_state[m_pPos+5]==OBJ_WALL))||\
			((m_state[m_pPos+5]==OBJ_WALL)&&(m_state[m_pPos+6]==OBJ_WALL)))){//全方向共通
										//現在地がゴールであることを確認
		//-------------------現在地がゴールである場合の処理-----------------------
			m_state[m_pPos]=OBJ_GOAL;
		}else{
			m_state[m_pPos]=OBJ_SPACE;
		}
		if(m_state[m_pPos+OneStep]==OBJ_BLOCK){//移動先が荷物の時の処理
			m_state[m_pPos+TwoStep]=OBJ_BLOCK;//現在地より二歩先の処理
		}
				//-------移動先の更新----------
		m_state[m_pPos+OneStep]=OBJ_PLAYER;
	}
	cout<<"after :プレイヤーがいた位置"<<m_state[m_pPos]\
	<<"現在プレイヤーがる場所"<<m_state[m_pPos+OneStep]<<endl;
	/*<<"移動直前のプレイヤーから二歩先"<<m_state[m_pPos+TwoStep]<<endl;
	cout<<"要素数は"<<m_pPos+TwoStep<<endl;*/
	if(judge_move==true){
		m_pPos=m_pPos+OneStep;//プレイヤーの位置を示す要素数更新
	}
	return 0;
}

int Nimotsu::updateGame()
	{
		drawGraphic();
		return 0;
}

void Nimotsu::checkObject(int move)
{
	/**
	switch(move) {
	case 1:
		if ((m_pPos - 1) == m_tPos1 || (m_pPos - 1)== m_tPos2)  {
			m_map[m_pPos - 1] = 'P';
			m_map[m_pPos] = ' ';
		}
		else if ((m_pPos - 1) == m_nPos1) {
			m_map[m_pPos - 2] = 'O';
			m_map[m_pPos - 1] = 'P';
			m_map[m_pPos] = ' ';
			m_nPos1 = m_nPos1 - 1;
		}
		else if ((m_pPos - 1 ) == m_nPos2) {
			m_map[m_pPos - 2] = 'O';
			m_map[m_pPos - 1] = 'P';
			m_map[m_pPos] = ' ';
			m_nPos2 = m_nPos2 - 1;
		}

		break;
	case 2:
		if ((m_pPos + 5) == m_tPos1 || (m_pPos + 5)== m_tPos2)  {
			m_map[m_pPos + 5] = 'P';
			m_map[m_pPos] = ' ';
		}
		else if ((m_pPos + 5) == m_nPos1) {
			m_map[m_pPos + 10] = 'O';
			m_map[m_pPos + 5] = 'P';
			m_map[m_pPos] = ' ';
			m_nPos1 = m_nPos1 + 5;
		}
		else if ((m_pPos + 5 ) == m_nPos2) {
			m_map[m_pPos + 10] = 'O';
			m_map[m_pPos + 5] = 'P';
			m_map[m_pPos] = ' ';
			m_nPos2 = m_nPos2 + 5;
		}

		break;
	case 3:
		if ((m_pPos - 5) == m_tPos1 || (m_pPos - 5)== m_tPos2)  {
			m_map[m_pPos - 5] = 'P';
			m_map[m_pPos] = ' ';
		}
		else if ((m_pPos - 5) == m_nPos1) {
			m_map[m_pPos - 10] = 'O';
			m_map[m_pPos - 5] = 'P';
			m_map[m_pPos] = ' ';
			m_nPos1 = m_nPos1 - 5;
		}
		else if  ((m_pPos - 5 ) == m_nPos2) {
			m_map[m_pPos - 10] = 'O';
			m_map[m_pPos - 5] = 'P';
			m_map[m_pPos] = ' ';
			m_nPos2 = m_nPos2 - 5;
		}
		
		break;
	case 4:
		if ((m_pPos + 1) == m_tPos1 || (m_pPos + 1)== m_tPos2)  {
			m_map[m_pPos + 1] = 'P';
			m_map[m_pPos] = ' ';
		}
		else if ((m_pPos + 1) == m_nPos1) {
			m_map[m_pPos + 2] = 'O';
			m_map[m_pPos + 1] = 'P';
			m_map[m_pPos] = ' ';
			m_nPos1 = m_nPos1 + 1;
		}
		else if ((m_pPos + 1 ) == m_nPos2) {
			m_map[m_pPos + 2] = 'O';
			m_map[m_pPos + 1] = 'P';
			m_map[m_pPos] = ' ';
			m_nPos2 = m_nPos2 + 1;
		}

		break;
	default:
		break;
	}
	**/
}

void Nimotsu::drawGraphic()
{
#ifdef _DEBUG
	cout <<  "01234567" << endl;
#endif

	for (int i = 0; i < m_width * m_height; i++) {
		switch(m_state[i]) {
			case OBJ_PLAYER:
				cout << 'P';
				break;
			case OBJ_SPACE:
				cout << ' ';
				break;
			case OBJ_WALL:
				cout << '#';
				break;
			case OBJ_GOAL:
				cout << '.';
				break;
			case OBJ_BLOCK:
				cout << 'O';
				break;
			case OBJ_UNKNOWN:
				break;
			default:
				break;
		}
		if (((i + 1) % m_width) == 0)
			cout << endl;
	}
}

void Nimotsu::createState()
{
	m_state = new NObject[m_width * m_height]; // 5 * 8のマップを作成
	/*cout<<"This is createState"<<endl;
	cout<<"m_width="<<m_width<<endl;
	cout<<"m_height="<<m_height<<endl;*/

	//sk write8/28
		int i=0;
	int m=0;
			/*cout<<"\nm_map出力@createstate"<<endl;
			for(int i=0;i<50;i++){
				cout<<m_map[i];
			}*/
	while(m_map[i]!='\0'){
		switch(m_map[i]){
			case('P'):m_state[m]=OBJ_PLAYER;++m;break;
			case(' '):m_state[m]=OBJ_SPACE;++m;break;
			case('#'):m_state[m]=OBJ_WALL;++m;break;
			case('.'):m_state[m]=OBJ_GOAL;++m;break;
			case('O'):m_state[m]=OBJ_BLOCK;++m;break;
			default:break;
		}
		
			
		++i;
	}
	m_pPos=13;//プレイヤーの位置初期化
	/*cout<<"\nm_state出力@createstate"<<endl;
			for(int i=0;i<40;i++){
				cout<<m_state[i];
			}*/
	cout<<" "<<endl;

//sk write end
}

NObject* Nimotsu::getObjectState()
{

	return m_state;
}
//----------------0828SK編集箇所----------------------

int Nimotsu::loadMap(char file_name[],int m,int n){//fp==NULの処理で値を返すようになっているので型はint
		FILE *fp;
		int k;
			k=(m+1)*n-1;//要素数
		m_width = m;
		m_height = n;
		/*char* m_map;
		m_map=new char[k];*/
		cout<<file_name<<endl;
		fp = fopen(file_name,"r");
		//ファイルオープンに失敗したとき

			if(fp==NULL){
				//失敗を表示し終了
				printf("ファイルオープン失敗\n");
				return -1;
			}
/*		int i=0;
		while (m_map[i] != '\0') {
			m_map[i]=0;

			i++;
		}*/
			/*for(int i=0;i<100;i++){
				m_map[i]=0;
			}*/
			int i;
			cout<<"マップデータアフィル読み込み、m_map[i]出力@loadMap"<<endl;
			for(i=0;i<k;i++){
				fread( &m_map[i], sizeof(char), 1, fp );
				//cout<<m_map[i];
					
			}
			cout<<endl;
				m_map[44]=0;
				/*cout<<"i="<<i<<endl;
				cout<<"m_map[i]="<<m_map[i]<<endl;*/
		fclose(fp);
		createState();
		cout<<"m_pPos@loadmap"<<m_pPos<<endl;
	}
//----------------0731SK編集箇所----------------------	