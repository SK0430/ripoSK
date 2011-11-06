#include<iostream>
#include<string>
#include "stdlib.h"

#include "main.h"
#include "Nimotsu.h"

using namespace std;


int main()
{
	Nimotsu* m_ni = new Nimotsu();
	m_ni->loadMap("..\\UnitTest\\mapdata_01.txt", 8, 5);

	while (1) {
		cout << "移動方向は？ [←↓↑→] = [h,j,k,l]" << endl;
		cout << endl;
		m_ni->updateGame();
		int result = m_ni->getKeyInput();

		system("cls"); //画面クリア
		if (result == 2) {
			cout << "アプリケーションを終了します。" << endl;
			exit(0);
		}
	}
}
