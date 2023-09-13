#include <Novice.h>
#include<math.h>
const char kWindowTitle[] = "GC2C_12_マンダイユウタ";
const int kWindowWidth = 800;
const int kWindowHeight = 800;
bool Collision(int ax, int ay, int* bx, int* by, int size)
{
	//player,左上の角
	int lTopX1 = ax;
	int lTopY1 = ay;
	//player,右下の角
	int rDownX1 = ax + size;
	int rDownY1 = ay + size;

	//Enemy,左上の角
	int lTopX2 = *bx;
	int lTopY2 = *by;
	//Enemy,左下の角
	int rDownX2 = *bx + size;
	int rDownY2 = *by + size;

	if (lTopX2 < rDownX1 && lTopX1 < rDownX2)
	{
		if (lTopY2 < rDownY1 && lTopY1 < rDownY2)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};
	
	//プレイヤー
	int PosX = 48;
	int PosY = 48;
	int radius = 16;
	
	//敵
	int Enemy_X[4] = {750,378,750,378};
	int Enemy_Y[4] = {750,378,750,378};
	int Enemy_Spd[4] = { 4,4,4,4 };
    int Enemy_Rad = 16;
	bool isAlive_[4] = {};

	int PosX2 = -782;
	int PosY2 = -806;
	
	//左上
	int playerLeftTopX;
	int playerLeftTopY;
	//右上
	int playerRightTopX;
	int playerRightTopY;
	//左下
	int  playerLeftBottomX;
	int  playerLeftBottomY;
	//右下
	int  playerRightBottomX;
	int  playerRightBottomY;

	//
	int speedX;
	int speedY;
	int speedTmp = 2;

	int gameScene = 1;
	///画像読み込み
	/*int Player = Novice::LoadTexture("Player.png");
	int GAMEOVER = Novice::LoadTexture("GAMEOVER.png");
	int GAMECLEAR = Novice::LoadTexture("GAMECLEAR.png");
	int Enemy = Novice::LoadTexture("Enemy.png");
	int STG = Novice::LoadTexture("STG.png");
	int RULE = Novice::LoadTexture("rule.png");
	int TITLE = Novice::LoadTexture("TITLE.png");*/

	////ブロック画像の読み込み
	int block = Novice::LoadTexture("./block.png");
	int Handle = Novice::LoadTexture("./tyuuou.png");

	const int blockSize = 32;


	int map[25][25] =
	{
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1},
{1,0,0,0,0,1,0,1,0,1,0,1,0,0,1,1,1,1,1,1,1,1,1,0,1},
{1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,1},
{1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,1},
{1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,1},
{1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1},
{1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,1},
{1,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
{1,0,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,0,0,1},
{1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
{1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,1},
{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,1},
{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,1},
{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,1},
{1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,1},
{1,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	};
	enum MapInfo {
		NOME,//0
		BLOCK//1

	};


	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);
	
		/// ↓更新処理ここから
	   ///
	  /// 
		switch (gameScene)
		{
		case 0:
			playerLeftTopX = (PosX - radius) / 32;
			playerLeftTopY = (PosY - radius) / 32;

			playerRightTopX = (PosX + radius - 1) / 32;
			playerRightTopY = (PosY - radius) / 32;

			playerLeftBottomX = (PosX - radius) / 32;
			playerLeftBottomY = (PosY + radius - 1) / 32;

			playerRightBottomX = (PosX + radius - 1) / 32;
			playerRightBottomY = (PosY + radius - 1) / 32;

			speedX = 0;
			speedY = 0;
			

			if (keys[DIK_D])
			{
				playerRightTopX = (PosX + radius - 1 + speedTmp) / 32;
				playerRightBottomX = (PosX + radius - 1 + speedTmp) / 32;
				if (map[playerRightTopY][playerRightTopX] == 0 && map[playerRightBottomY][playerRightBottomX] == 0)
				{
					speedX = 4;
				}

			}
			if (keys[DIK_A])
			{
				playerLeftTopX = (PosX - radius - speedTmp) / 32;
				playerLeftBottomX = (PosX - radius - speedTmp) / 32;
				if (map[playerLeftTopY][playerLeftTopX] == 0 && map[playerLeftBottomY][playerLeftBottomX] == 0)
				{
					speedX = -4;
				}

			}
			if (keys[DIK_S])
			{
				playerLeftBottomY = (PosY + radius - 1 + speedTmp) / 32;
				playerRightBottomY = (PosY + radius - 1 + speedTmp) / 32;
				if (map[playerRightBottomY][playerRightBottomX] == 0 && map[playerLeftBottomY][playerLeftBottomX] == 0)
				{
					speedY = 4;
				}
			}
			if (keys[DIK_W])
			{
				playerLeftTopY = (PosY - radius - speedTmp) / 32;
				playerRightTopY = (PosY - radius - speedTmp) / 32;
				if (map[playerRightTopY][playerRightTopX] == 0 && map[playerLeftTopY][playerLeftTopX] == 0)
				{
					speedY = -4;
				}
			}

			PosX += speedX;
			PosY += speedY;

			for (int i = 0; i < 4; i++)
			{
				if (isAlive_[i] == false)
				{
					Enemy_X[0] += Enemy_Spd[0];
					Enemy_X[1] += Enemy_Spd[1];
					Enemy_Y[2] += Enemy_Spd[2];
					Enemy_Y[3] += Enemy_Spd[3];

				}

				if (Enemy_X[0] + Enemy_Rad >= 768)
				{
					Enemy_Spd[0] *= -1;
				}
				if (Enemy_X[0] + Enemy_Rad <= 32)
				{
					Enemy_Spd[0] *= -1;

				}

				if (Enemy_X[1] + Enemy_Rad >= 768)
				{
					Enemy_Spd[1] *= -1;
				}
				if (Enemy_X[1] + Enemy_Rad <= 32)
				{
					Enemy_Spd[1] *= -1;

				}


				if (Enemy_Y[2] + Enemy_Rad >= 768)
				{
					Enemy_Spd[2] *= -1;
				}
				if (Enemy_Y[2] + Enemy_Rad <= 32)
				{
					Enemy_Spd[2] *= -1;

				}


				if (Enemy_Y[3] + Enemy_Rad >= 768)
				{
					Enemy_Spd[3] *= -1;
				}
				if (Enemy_Y[3] + Enemy_Rad <= 32)
				{
					Enemy_Spd[3] *= -1;

				}

			}
			for (int i = 0;i < 4;i++) 
			{
				if (Collision(PosX, PosY, &Enemy_X[i], &Enemy_Y[i], Enemy_Rad)) 
				{
					gameScene=3;
				}
			}
			break;
			case 1:
				if (keys[DIK_X] && preKeys[DIK_X] == false) 
				{
					gameScene = 4;
				}
				break;
			case 2:
				break;
			case 3:
				PosX = 48;
				PosY = 48;
				radius = 16;
				for (int i = 0; i < 4; i++) 
				{
					if (i % 2 == 1) 
					{
						Enemy_X[i] = 378;
						Enemy_Y[i] = 378;
					}
					Enemy_X[i] = 750;
					Enemy_Y[i] = 750;
					Enemy_Spd[i] = 4;
					Enemy_Rad = 16;
					isAlive_[i] = {};
					if (keys[DIK_RETURN] && preKeys[DIK_RETURN] == false)
					{
						gameScene = 1;
					}
				}
				break;
			case 4:
				if (keys[DIK_Z] && preKeys[DIK_Z] == false) 
				{
					gameScene = 0;
				}
				break;
		}

		
			

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		switch (gameScene)
		{
		case 0:
			for (int y = 0; y < 25; y++) {
				for (int x = 0; x < 25; x++) {
					if (map[y][x] == BLOCK) {
						Novice::DrawSprite(x * blockSize, y * blockSize, block, 1.0f, 1.0f, 0.0f, WHITE);
					}
				}
			}

			for (int i = 0; i < 4; i++)
			{
				if (isAlive_[i] == false)
				{
					Novice::DrawEllipse(Enemy_X[i], Enemy_Y[i], Enemy_Rad, Enemy_Rad, 0.0f, RED, kFillModeSolid);
				}
			}
			Novice::DrawSprite(PosX2 + PosX, PosY2 + PosY, Handle, 1.0f, 1.0f, 0.0f, WHITE);
			Novice::DrawEllipse(PosX, PosY, radius, radius, 0.0f, RED, kFillModeSolid);
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		}
		
		
		
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
