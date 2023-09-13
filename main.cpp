#include <Novice.h>
#include<math.h>
const char kWindowTitle[] = "GC2C_12_マンダイユウタ";
const int kWindowWidth = 800;
const int kWindowHeight = 800;
struct Vector2
{
	int x;
	int y;
};

struct ObjectFlag
{
	bool hitUp;
	bool hitDown;
	bool hitRight;
	bool hitLeft;
};

struct Object
{
	Vector2 pos;
	Vector2 speed;
	int rad;
	int color;
	ObjectFlag flag;
};

struct BOX
{
	Vector2 pos;
	Vector2 speed;
	int rad;
	bool Flag;
};
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
	
	//ブロック
	BOX box{
		{100,128},
		{32,32},
		{16},
		{true},
	};
	
	int BoxRightTopX = 0;
	int BoxRightTopY = 0;
	int BoxRightBottomX = 0;
	int BoxRightBottomY = 0;

	int BoxLeftTopX = 0;
	int BoxLeftTopY = 0;
	int BoxLeftBottomX = 0;
	int BoxLeftBottomY = 0;
	int Flag = 0;
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
	int Player = Novice::LoadTexture("./Player.png");
	int GAMEOVER = Novice::LoadTexture("./GAMEOVER.png");
	int GAMECLEAR = Novice::LoadTexture("./GAMECLEAR.png");
	int Enemy = Novice::LoadTexture("./Enemyt.png");
	int STG = Novice::LoadTexture("./STG.png");
	int RULE = Novice::LoadTexture("./rule-export.png");
	int TITLE = Novice::LoadTexture("./TITLE.png");
	int SWITH = Novice::LoadTexture("./SWITH.png");
	int Block = Novice::LoadTexture("./Blok.png");
	////ブロック画像の読み込み
	int block = Novice::LoadTexture("./block.png");
	int Handle = Novice::LoadTexture("./tyuuou.png");

	const int blockSize = 32;
	bool GoalFlag = false;


	int map[25][25] =
	{
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1},
{1,0,0,0,0,1,0,1,0,1,0,1,0,0,1,1,1,1,1,1,1,1,0,0,1},
{1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,1},
{1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,1},
{1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,1},
{1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1},
{1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,1},
{1,0,0,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,0,0,1},
{1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
{1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,1},
{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,1},
{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,1},
{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,1},
{1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,1},
{1,0,0,1,0,0,0,0,0,0,0,3,0,1,0,0,0,1,0,0,0,1,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	};

	enum MapInfo {
		NOME,//0
		BLOCK,//1
		SWITCH,//2
		AIR_GOAL,//3
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
			playerLeftTopX = (PosX - radius) / blockSize;
			playerLeftTopY = (PosY - radius) / blockSize;

			playerRightTopX = (PosX + radius - 1) / blockSize;
			playerRightTopY = (PosY - radius) / blockSize;

			playerLeftBottomX = (PosX - radius) / blockSize;
			playerLeftBottomY = (PosY + radius - 1) / blockSize;

			playerRightBottomX = (PosX + radius - 1) / blockSize;
			playerRightBottomY = (PosY + radius - 1) / blockSize;

			speedX = 0;
			speedY = 0;
			

			if (keys[DIK_D])
			{
				playerRightTopX = (PosX + radius - 1 + speedTmp) / blockSize;
				playerRightBottomX = (PosX + radius - 1 + speedTmp) / blockSize;
				if (map[playerRightTopY][playerRightTopX] == 0 && map[playerRightBottomY][playerRightBottomX] == 0)
				{
					speedX = 4;
				}
				BoxRightTopX = (box.pos.x + box.rad - 1) / blockSize;
				BoxLeftBottomX = (box.pos.x - box.rad) / blockSize;
			}
			if (keys[DIK_A])
			{
				BoxLeftTopX = (box.pos.x - box.rad) / blockSize;
				BoxLeftBottomX = (box.pos.x - box.rad) / blockSize;
				playerLeftTopX = (PosX - radius - speedTmp) / blockSize;
				playerLeftBottomX = (PosX - radius - speedTmp) / blockSize;
				if (map[playerLeftTopY][playerLeftTopX] == 0 && map[playerLeftBottomY][playerLeftBottomX] == 0)
				{
					speedX = -4;
				}

			}
			if (keys[DIK_S])
			{
				BoxLeftBottomY = (box.pos.y + box.rad) / blockSize;
				BoxLeftBottomY = (box.pos.y + box.rad) / blockSize;
				playerLeftBottomY = (PosY + radius - 1 + speedTmp) / blockSize;
				playerRightBottomY = (PosY + radius - 1 + speedTmp) / blockSize;
				if (map[playerRightBottomY][playerRightBottomX] == 0 && map[playerLeftBottomY][playerLeftBottomX] == 0)
				{
					speedY = 4;
				}
			}
			if (keys[DIK_W])
			{
				BoxLeftTopY = (box.pos.y - box.rad) / blockSize;
				BoxRightTopY = (box.pos.y - box.rad) /blockSize;
				playerLeftTopY = (PosY - radius - speedTmp) / blockSize;
				playerRightTopY = (PosY - radius - speedTmp) / blockSize;
				if (map[playerRightTopY][playerRightTopX] == 0 && map[playerLeftTopY][playerLeftTopX] == 0)
				{
					speedY = -4;
				}
			}

			PosX += speedX;
			PosY += speedY;
			
			//
			playerLeftTopX = PosX - 14;
			playerLeftTopY = PosY - 14;
			playerRightBottomX = PosX + 14;
			playerRightBottomY = PosY + 14;

			//
			BoxLeftTopX = box.pos.x - box.rad;
			BoxLeftTopY = box.pos.y - box.rad;
			BoxRightBottomX = box.pos.x + box.rad;
			BoxRightBottomY = box.pos.y + box.rad;

			//
			if (BoxLeftTopX <= playerRightBottomX && playerLeftTopX <= BoxRightBottomX) 
			{
				if (BoxLeftTopY <= playerRightBottomY && playerLeftTopY <= BoxRightBottomY) 
				{
					Flag = 1;

					box.pos.x += speedX;
					box.pos.y += speedY;
				}
			}

			BoxRightTopX = (box.pos.x + box.rad - 1) / blockSize;
			BoxRightTopY = (box.pos.y + box.rad - 1) / blockSize;
			BoxRightBottomX = (box.pos.x + box.rad - 1) / blockSize;
			BoxRightBottomY = (box.pos.y + box.rad - 1) / blockSize;
			BoxLeftTopX = (box.pos.x - box.rad) / blockSize;
			BoxLeftTopY = (box.pos.y - box.rad) / blockSize;
			BoxLeftBottomX = (box.pos.x - box.rad) / blockSize;
			BoxLeftBottomY = (box.pos.y + box.rad - 1) / blockSize;
			
			if (Flag == 1)
			{
				if (map[BoxRightTopY][BoxRightTopX] == BLOCK && map[BoxRightBottomY][BoxRightBottomX] == BLOCK)
				{
					box.pos.x -= speedX;
					PosX -= speedX;
				}

				if (map[BoxLeftBottomY][BoxLeftBottomX] == BLOCK && map[BoxLeftTopY][BoxLeftTopX] == BLOCK)
				{
					box.pos.x -= speedX;
					PosX -= speedX;
				}

				if (map[BoxRightTopY][BoxRightTopX] == BLOCK && map[BoxLeftTopY][BoxLeftTopX] == BLOCK)
				{
					box.pos.y -= speedY;
					PosY -= speedY;
				}

				if (map[BoxRightBottomY][BoxRightBottomX] == BLOCK && map[BoxLeftBottomY][BoxLeftBottomX] == BLOCK)
				{
					box.pos.y -= speedY;
					PosY -= speedY;
				}
			}
			if (map[BoxRightTopY][BoxRightTopX] == SWITCH && map[BoxRightBottomY][BoxRightBottomX] == SWITCH)
			{
				GoalFlag = true;
			}

			if (map[BoxLeftBottomY][BoxLeftBottomX] == SWITCH && map[BoxLeftTopY][BoxLeftTopX] == SWITCH)
			{
				GoalFlag = true;
			}

			if (map[BoxRightTopY][BoxRightTopX] == SWITCH && map[BoxLeftTopY][BoxLeftTopX] == SWITCH)
			{
				GoalFlag = true;
			}

			if (map[BoxRightBottomY][BoxRightBottomX] == SWITCH && map[BoxLeftBottomY][BoxLeftBottomX] == SWITCH)
			{
				GoalFlag = true;
			}

			//GOALにブロックがあればシーン切り替え
			playerRightTopX = (PosX + radius - 1) / blockSize;
			playerRightTopY = (PosY- radius) / blockSize;
			playerRightBottomX = (PosX + radius - 1) / blockSize;
			playerRightBottomY = (PosY + radius - 1) / blockSize;

			playerLeftTopX = (PosX - radius) / blockSize;
			playerLeftTopY = (PosY - radius) / blockSize;
			playerLeftBottomX = (PosX - radius) / blockSize;
			playerLeftBottomY = (PosY + radius - 1) / blockSize;

			if (GoalFlag)
			{
				if (map[playerRightTopY][playerRightTopX] == AIR_GOAL && map[playerRightBottomY][playerRightBottomX] == AIR_GOAL)
				{
					gameScene = 2;
					//シーン切り替え
				}

				if (map[playerLeftBottomY][playerLeftBottomX] == AIR_GOAL && map[playerLeftTopY][playerLeftTopX] == AIR_GOAL)
				{
					gameScene = 2;
					//シーン切り替え
				}

				if (map[playerRightTopY][playerRightTopX] == AIR_GOAL && map[playerLeftTopY][playerLeftTopX] == AIR_GOAL)
				{
					gameScene = 2;
					//シーン切り替え
				}

				if (map[playerRightBottomY][playerRightBottomX] == AIR_GOAL && map[playerLeftBottomY][playerLeftBottomX] == AIR_GOAL)
				{
					gameScene = 2;
					//シーン切り替え
				}
			}

			
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
				if (!isAlive_[i]) 
				{

					if (Collision(PosX, PosY, &Enemy_X[i], &Enemy_Y[i], Enemy_Rad))
					{
						gameScene = 3;
					}
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
					Enemy_X[0] = 750;
					Enemy_Y[0] = 750;
					Enemy_X[1] = 378;
					Enemy_Y[1] = 378;
					Enemy_X[2] = 750;
					Enemy_Y[2] = 750;
					Enemy_X[3] = 378;
					Enemy_Y[3] = 378;
					Enemy_Spd[i] = 4;
					Enemy_Rad = 16;
					isAlive_[i] = {};
					box.pos.x = 100;
					box.pos.y = 128;
					box.Flag = true;
					if (keys[DIK_RETURN] && preKeys[DIK_RETURN] == false)
					{
						gameScene = 1;
					}

					GoalFlag = false;
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
			Novice::DrawSprite(0, 0, STG, 1.0f, 1.0f, 0.0f, WHITE);
			for (int y = 0; y < 25; y++) {
				for (int x = 0; x < 25; x++) {
					if (map[y][x] == BLOCK) {
						Novice::DrawSprite(x * blockSize, y * blockSize, block, 1.0f, 1.0f, 0.0f, WHITE);
					}
				}
			}
			for (int y = 0; y < 25; y++) {
				for (int x = 0; x < 25; x++) {
					if (map[y][x] == SWITCH) {
						Novice::DrawSprite(x * 32, y * 32, SWITH, 1.0f, 1.0f, 0.0f, WHITE);
					}
				}
			}
			if (GoalFlag == true) {
				for (int y = 0; y < 25; y++) {
					for (int x = 0; x < 25; x++) {
						if (map[y][x] == AIR_GOAL) {
							Novice::DrawSprite(x * 32, y * 32, block, 1.0f, 1.0f, 0.0f, WHITE);
						}
					}
				}

			}
			Novice::DrawSprite(box.pos.x - box.rad, box.pos.y - box.rad, Block, 1.0f, 1.0f, 0.0f, WHITE);
			for (int i = 0; i < 4; i++)
			{
				if (isAlive_[i] == false)
				{
					Novice::DrawSprite(Enemy_X[i], Enemy_Y[i], Enemy,2.0f,2.0f, 0.0f,WHITE);
				}
			}
			Novice::DrawSprite(PosX2 + PosX, PosY2 + PosY, Handle, 1.0f, 1.0f, 0.0f, WHITE);
			Novice::DrawSprite(PosX, PosY, Player, 1.0f, 1.0f, 0.0f, WHITE);
			
			break;
		case 1:
			Novice::DrawSprite(0, 0, TITLE, 1.0f, 1.0f, 0.0f, WHITE);
			break;
		case 2:
			Novice::DrawSprite(0, 0, GAMECLEAR, 1.0f, 1.0f, 0.0f, WHITE);
			break;
		case 3:
			Novice::DrawSprite(0, 0, GAMEOVER, 1.0f, 1.0f, 0.0f, WHITE);
			break;
		case 4:
			Novice::DrawSprite(0, 0, RULE, 1.0f, 1.0f, 0.0f, WHITE);
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
