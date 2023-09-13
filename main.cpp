#include <Novice.h>
#include<math.h>
const char kWindowTitle[] = "GC2C_12_マンダイユウタ";
const int kWindowWidth = 800;
const int kWindowHeight = 800;;

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
		
			for (int  i = 0; i < 4; i++)
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
			

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
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
