//nimotsutest.cpp
#include "Nimotsu.h"
#include "NimotsuTest.h"
#include <stdio.h>//sk write
using namespace std;//sk write

CPPUNIT_TEST_SUITE_REGISTRATION( NimotsuTest );

void NimotsuTest::setUp()
{
}
void NimotsuTest::tearDown()
{
}


void NimotsuTest::test_init()
{
	CPPUNIT_ASSERT(1);
}

/**
 * m_mapにデータを正しく読み込めるか確認するテスト
 **/
void NimotsuTest::createMapTest()
{
	cout<<"<sk Test>createMapTest is here!"<<endl;
	Nimotsu* m_ni = new Nimotsu();
	m_ni->loadMap("mapdata_01.txt", 8, 5);
	
	// テスト対象のデータ
	const char base_map[] = \
"########\n\
# .. P #\n\
# OO   #\n\
#      #\n\
########";
	//sk test
	cout<<"sk test m_ni->m_map[i]出力@createMapTest()"<<endl;
	int i = 0;
	while (m_ni->m_map[i] != '\0') {
		cout<<m_ni->m_map[i];
		i++;
	}
	 i = 0;
	//sk test end
	
	while (m_ni->m_map[i] != '\0') {
		CPPUNIT_ASSERT(m_ni->m_map[i] == base_map[i]);
		i++;
	}
}

/**
 * マップデータを読み込めるようにするテスト
 **/
void NimotsuTest::loadMapTest()
{
	Nimotsu* m_ni = new Nimotsu();
	m_ni->loadMap("mapdata_02.txt", 10, 5);

	// テスト対象データ
	const char base_map[] = \
"##########\n\
# . #  P #\n\
# OO#    #\n\
#   .    #\n\
##########";

	int i = 0;
	while (m_ni->m_map[i] != '\0') {
		CPPUNIT_ASSERT(m_ni->m_map[i] == base_map[i]);
		i++;
	}

}

/**
 * m_mapに読み込んだデータを状態データに変換できるか
 * 確認するテスト
 **/
void NimotsuTest::stateTest()
{
	Nimotsu* m_ni = new Nimotsu();
	m_ni->loadMap("mapdata_01.txt", 8, 5);

	// テスト対象のデータ
	const NObject base_state[] = {
		OBJ_WALL, OBJ_WALL, OBJ_WALL, OBJ_WALL, OBJ_WALL, OBJ_WALL, OBJ_WALL, OBJ_WALL,
		OBJ_WALL, OBJ_SPACE, OBJ_GOAL, OBJ_GOAL, OBJ_SPACE, OBJ_PLAYER, OBJ_SPACE, OBJ_WALL,
		OBJ_WALL, OBJ_SPACE, OBJ_BLOCK, OBJ_BLOCK, OBJ_SPACE, OBJ_SPACE, OBJ_SPACE, OBJ_WALL,
		OBJ_WALL, OBJ_SPACE, OBJ_SPACE, OBJ_SPACE, OBJ_SPACE, OBJ_SPACE, OBJ_SPACE, OBJ_WALL,
		OBJ_WALL, OBJ_WALL, OBJ_WALL, OBJ_WALL, OBJ_WALL, OBJ_WALL, OBJ_WALL, OBJ_WALL
	};
			cout<<"\nbase_state出力"<<endl;
			/*for(int i=0;i<40;i++){
				cout<<base_state[i];
			}*/
			cout<<"\ntest出力"<<endl;

	NObject* test = m_ni->getObjectState();	
	NObject* test2=test;
			/*for(int i=0;i<40;i++){
				cout<<*test2;
				test2++;

			}*/	

			cout<<"stateTest判定開始"<<endl;
	for (int i = 0; i <  m_ni->m_width * m_ni->m_height; i++) {
				//cout<<*test<<"\t"<<base_state[i]<<endl;
		CPPUNIT_ASSERT(*test == base_state[i]);
		test++;
	}
}

/**
 * プレイヤーを動かした時に期待通りの配置になることを
 * 確認するテスト
 **/
void NimotsuTest::moveTest01()
{
	Nimotsu* m_ni = new Nimotsu();
	m_ni->loadMap("mapdata_01.txt", 8, 5);
	//cout<<"m_pPos@moveTest01"<<m_pPos<<endl;
	NObject* nobj = m_ni->getObjectState();
	cout<<"m_state変換完了@moveTest01"<<endl;
	CPPUNIT_ASSERT( nobj[13] == OBJ_PLAYER );   // プレイヤー位置を確認

	// 上下左右へ移動
	m_ni->moveDown();
	cout<<"nobj[13]:"<<nobj[13]<<"nobj[21]:"<<nobj[21]<<endl;
	CPPUNIT_ASSERT( nobj[13] == OBJ_SPACE && nobj[21] == OBJ_PLAYER );
	m_ni->moveUp();
	CPPUNIT_ASSERT( nobj[13] == OBJ_PLAYER && nobj[21] == OBJ_SPACE );
	m_ni->moveLeft();
	cout<<"nobj[12]:"<<nobj[12]<<"nobj[13]:"<<nobj[13]<<endl;
	m_ni->drawGraphic();
	CPPUNIT_ASSERT( nobj[12] == OBJ_PLAYER && nobj[13] == OBJ_SPACE );
	m_ni->moveRight();
	CPPUNIT_ASSERT( nobj[12] == OBJ_SPACE && nobj[13] == OBJ_PLAYER );
}


/**
 * ゴール位置の状態が正しく維持できるかを確認するテスト
 **/
void NimotsuTest::moveTest02()
{
	Nimotsu* m_ni = new Nimotsu();
	m_ni->loadMap("mapdata_01.txt", 8, 5);
	NObject* nobj = m_ni->getObjectState();

	m_ni->moveLeft();
	CPPUNIT_ASSERT( nobj[12] == OBJ_PLAYER);
	CPPUNIT_ASSERT( nobj[13] == OBJ_SPACE);

	// ゴール位置へのプレイヤーの移動
	m_ni->moveLeft();
	CPPUNIT_ASSERT( nobj[11] == OBJ_PLAYER);
	CPPUNIT_ASSERT( nobj[12] == OBJ_SPACE);
	
	m_ni->moveLeft();
	CPPUNIT_ASSERT( nobj[10] == OBJ_PLAYER);
	CPPUNIT_ASSERT( nobj[11] == OBJ_GOAL);

	m_ni->moveLeft();
	CPPUNIT_ASSERT( nobj[9] == OBJ_PLAYER);
	CPPUNIT_ASSERT( nobj[10] == OBJ_GOAL);
	cout<<"ゴール到着"<<endl;
	// 壁で止まる
	m_ni->moveLeft();
	CPPUNIT_ASSERT( nobj[8] == OBJ_WALL);
	CPPUNIT_ASSERT( nobj[9] == OBJ_PLAYER);
}

/**
 * プレイヤーの壁ぶつかりテスト
 **/
void NimotsuTest::moveTest03()
{
	Nimotsu* m_ni = new Nimotsu();
	m_ni->loadMap("mapdata_01.txt", 8, 5);
	NObject* nobj  = m_ni->getObjectState();

	m_ni->moveRight();
	cout<<"nobj[14]="<<nobj[14]<<"nobj[15]="<<nobj[15]<<endl;
	CPPUNIT_ASSERT( nobj[14] == OBJ_PLAYER );
	CPPUNIT_ASSERT( nobj[15] == OBJ_WALL );

	m_ni->moveRight();  // 壁にぶつかったら進まないことを確認
	cout<<"nobj[14]="<<nobj[14]<<"nobj[15]="<<nobj[15]<<endl;
	CPPUNIT_ASSERT( nobj[14] == OBJ_PLAYER );
	CPPUNIT_ASSERT( nobj[15] == OBJ_WALL );

	m_ni->moveUp();     // 壁ぶつかりテスト
	cout<<"nobj[6]="<<nobj[6]<<"nobj[14]="<<nobj[14]<<endl;
	CPPUNIT_ASSERT( nobj[6] == OBJ_WALL );
	CPPUNIT_ASSERT( nobj[14] == OBJ_PLAYER );

	m_ni->moveDown();
	//m_ni->drawGraphic();
	m_ni->moveDown();
	//m_ni->drawGraphic();
	m_ni->moveDown();   // 壁ぶつかりテスト
	//m_ni->drawGraphic();
	/*for(int i=0;i<40;i++){
		cout<<nobj[i];
	}
	cout<<endl;*/
	cout<<"nobj[22]="<<nobj[22]<<"nobj[30]="<<nobj[30]<<"nobj[38]="<<nobj[38]<<endl;
	CPPUNIT_ASSERT( nobj[30] == OBJ_PLAYER );
	CPPUNIT_ASSERT( nobj[38] == OBJ_WALL );
}

/**
 * 荷物の押し方の制約条件を確認するテスト
 **/
void NimotsuTest::moveTest04()
{
	Nimotsu* m_ni = new Nimotsu();
	m_ni->loadMap("mapdata_01.txt", 8, 5);
	NObject* nobj = m_ni->getObjectState();

	m_ni->moveDown();
	m_ni->moveLeft();
	m_ni->moveLeft(); // 荷物を2つ同時に動かそうとする

	// 荷物は2つ一緒には動かせない
	CPPUNIT_ASSERT( nobj[18] == OBJ_BLOCK );
	CPPUNIT_ASSERT( nobj[19] == OBJ_BLOCK );
	CPPUNIT_ASSERT( nobj[20] == OBJ_PLAYER );
}

/**
 * 荷物を押しながら壁にぶつかった時の挙動を確認するテスト
 **/
void NimotsuTest::moveTest05()
{
	Nimotsu* m_ni = new Nimotsu();
	m_ni->loadMap("mapdata_01.txt", 8, 5);
	NObject* nobj = m_ni->getObjectState();

	m_ni->moveLeft();
	m_ni->moveLeft();
	m_ni->moveDown();
	m_ni->moveDown(); // 壁にぶつかっている状態で下に移動しようとする

	// 壁にぶつかったらすすまないはず
	CPPUNIT_ASSERT( nobj[19] == OBJ_PLAYER );
	CPPUNIT_ASSERT( nobj[27] == OBJ_BLOCK );
	CPPUNIT_ASSERT( nobj[35] == OBJ_WALL );
}

/**
 * 最小ルートでのゴールへの移動がうまくいくかを
 * 確認するテスト
 **/
void NimotsuTest::goalTest()
{
	Nimotsu* m_ni = new Nimotsu();
	m_ni->loadMap("mapdata_01.txt", 8, 5);
	NObject* nobj = m_ni->getObjectState();
	
	m_ni->drawGraphic();

	m_ni->moveDown();
	//m_ni->drawGraphic();
	m_ni->moveDown();
	//m_ni->drawGraphic();
	m_ni->moveLeft();
	//m_ni->drawGraphic();
	m_ni->moveLeft();
	//m_ni->drawGraphic();
	m_ni->moveUp();     // 右側の荷物をゴールに移動
	//m_ni->drawGraphic();
	m_ni->moveDown();
	//m_ni->drawGraphic();
	m_ni->moveLeft();
	//m_ni->drawGraphic();
	m_ni->moveUp();     // 左側の荷物をゴールに移動
	//m_ni->drawGraphic();

	// プレイヤー、荷物の場所を確認
	cout<<"nobj[10]="<<nobj[10]<<endl;
	cout<<"nobj[11]="<<nobj[11]<<endl;
	cout<<"nobj[18]="<<nobj[18]<<endl;
	cout<<"m_ni="<<m_ni->m_pPos<<endl;
	CPPUNIT_ASSERT( nobj[10] == OBJ_BLOCK );
	CPPUNIT_ASSERT( nobj[11] == OBJ_BLOCK );
	CPPUNIT_ASSERT( nobj[18] == OBJ_PLAYER );
	CPPUNIT_ASSERT( m_ni->m_pPos == 18 );

	m_ni->drawGraphic();

	// Objectの状態をすべてチェック
	const NObject goal_state[] = {
		OBJ_WALL, OBJ_WALL, OBJ_WALL, OBJ_WALL, OBJ_WALL, OBJ_WALL, OBJ_WALL, OBJ_WALL,
		OBJ_WALL, OBJ_SPACE, OBJ_BLOCK, OBJ_BLOCK, OBJ_SPACE, OBJ_SPACE, OBJ_SPACE, OBJ_WALL,
		OBJ_WALL, OBJ_SPACE, OBJ_PLAYER, OBJ_SPACE, OBJ_SPACE, OBJ_SPACE, OBJ_SPACE, OBJ_WALL,
		OBJ_WALL, OBJ_SPACE, OBJ_SPACE, OBJ_SPACE, OBJ_SPACE, OBJ_SPACE, OBJ_SPACE, OBJ_WALL,
		OBJ_WALL, OBJ_WALL, OBJ_WALL, OBJ_WALL, OBJ_WALL, OBJ_WALL, OBJ_WALL, OBJ_WALL
	};
	for (int i = 0; i <  m_ni->m_width * m_ni->m_height; i++) {
		CPPUNIT_ASSERT(*nobj == goal_state[i]);
		nobj++;
	}
}

void NimotsuTest::test_clear()
{
	CPPUNIT_ASSERT(1);
}