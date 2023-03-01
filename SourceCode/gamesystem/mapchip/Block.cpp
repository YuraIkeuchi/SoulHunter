#include "Block.h"
#include "imgui.h"
#include "ModelManager.h"
#include "VariableCommon.h"
Block* Block::GetInstance()
{
	static Block instance;

	return &instance;
}

//モデル読み込み
void Block::ModelInit() {
	IKEModel* modelNormalBlock_;
	modelNormalBlock_ = ModelManager::GetInstance()->GetModel(ModelManager::NormalBlock);
	//マップチップ用のオブジェクトの初期化
	for (int y = 0; y < map_max_y; y++)
	{
		for (int x = 0; x < map_max_x; x++)
		{
			IKEObject3d* objNormalBlock_[map_max_y][map_max_x];
			objNormalBlock_[y][x] = new IKEObject3d();
			objNormalBlock_[y][x] = IKEObject3d::Create();
			objNormalBlock_[y][x]->SetModel(modelNormalBlock_);
			objNormalBlock_[y][x]->SetScale({ 0.7f,1.2f,3.0f });
			objNormalBlock_[y][x]->SetTiling({ 5.0f });
			objNormalBlock_[y][x]->SetPosition({ 1000.0f,1000.0f,1000.0f });
			objNormalBlock[y][x].reset(objNormalBlock_[y][x]);
		}
	}
	modelNormalBlock.reset(modelNormalBlock_);

	IKEModel* modelInBlock_;
	modelInBlock_ = ModelManager::GetInstance()->GetModel(ModelManager::InBlock);
	//マップチップ用のオブジェクトの初期化
	for (int y = 0; y < map_max_y; y++)
	{
		for (int x = 0; x < map_max_x; x++)
		{
			IKEObject3d* objInBlock_[map_max_y][map_max_x];
			objInBlock_[y][x] = new IKEObject3d();
			objInBlock_[y][x] = IKEObject3d::Create();
			objInBlock_[y][x]->SetModel(modelInBlock_);
			objInBlock_[y][x]->SetScale({ 0.8f,2.0f,3.0f });
			objInBlock_[y][x]->SetTiling({ 5.0f });
			objInBlock_[y][x]->SetPosition({ 1000.0f,1000.0f,1000.0f });
			objInBlock[y][x].reset(objInBlock_[y][x]);
		}
	}
	modelInBlock.reset(modelInBlock_);
	IKEModel* modelToge_;
	modelToge_ = ModelManager::GetInstance()->GetModel(ModelManager::Toge);

	for (int y = 0; y < map_max_y; y++)
	{
		for (int x = 0; x < map_max_x; x++)
		{
			IKEObject3d* objToge_[map_max_y][map_max_x];
			objToge_[y][x] = new IKEObject3d();
			objToge_[y][x] = IKEObject3d::Create();
			objToge_[y][x]->SetModel(modelToge_);
			objToge_[y][x]->SetScale({ 0.6f,1.0f,0.6f });
			objToge_[y][x]->SetPosition({ 1000.0f,1000.0f,1000.0f });
			objToge[y][x].reset(objToge_[y][x]);
		}
	}
	modelToge.reset(modelToge_);

	IKEModel* modelGoalBlock_;
	//modelWhiteBlock = ModelManager::GetInstance()->GetModel(ModelManager::WhiteBlock);
	modelGoalBlock_ = ModelManager::GetInstance()->GetModel(ModelManager::NormalBlock);

	modelGoalBlock.reset(modelGoalBlock_);
}
//初期化
void Block::Initialize(std::vector<std::vector<int>>& map, int mapNumber,int StageNumber) {

	stagemap = map;
	//ステージによってマップの読み込みが変わる
	if (StageNumber == Map1) {

		MapChip::LoadCsvMap(stagemap, "Resources/csv/firststage.csv");
	}
	else if (StageNumber == Map2) {

		MapChip::LoadCsvMap(stagemap, "Resources/csv/firststage_second.csv");
	}
	else if (StageNumber == Map3) {

		MapChip::LoadCsvMap(stagemap, "Resources/csv/firststage_third.csv");
	}
	else if (StageNumber == Map4) {

		MapChip::LoadCsvMap(stagemap, "Resources/csv/firststage_fourth.csv");
	}
	else if (StageNumber == Map5) {

		MapChip::LoadCsvMap(stagemap, "Resources/csv/firststage_fifth.csv");
	}
	else if (StageNumber == Map6) {

		MapChip::LoadCsvMap(stagemap, "Resources/csv/firststage_sixth.csv");
	}
	else if (StageNumber == BossMap) {

		MapChip::LoadCsvMap(stagemap, "Resources/csv/firstboss.csv");
	}
	else if (StageNumber == TutoRial) {

		MapChip::LoadCsvMap(stagemap, "Resources/csv/tutorial.csv");
	}
	MapCreate(0,StageNumber);
}
//更新
void Block::Update(XMFLOAT3& pos) {
	//ステージごとに違う
		//各ブロックのアップデート
	for (int y = 0; y < map_max_y; y++)
	{
		for (int x = 0; x < map_max_x; x++)
		{
			m_Distance[y][x].x = pos.x - objNormalBlock[y][x]->GetPosition().x;
			m_Distance[y][x].x = fabs(m_Distance[y][x].x);
			m_Distance[y][x].y = pos.y - objNormalBlock[y][x]->GetPosition().y;
			m_Distance[y][x].y = fabs(m_Distance[y][x].y);
			if ((m_Distance[y][x].x <= 80.0f && m_Distance[y][x].y <= 80.0f) && (objNormalBlock[y][x]->GetPosition().z != 1000.0f)) {
					objNormalBlock[y][x]->Update();
			}

			m_InDistance[y][x].x = pos.x - objInBlock[y][x]->GetPosition().x;
			m_InDistance[y][x].x = fabs(m_InDistance[y][x].x);
			m_InDistance[y][x].y = pos.y - objInBlock[y][x]->GetPosition().y;
			m_InDistance[y][x].y = fabs(m_InDistance[y][x].y);
			if ((m_InDistance[y][x].x <= 80.0f && m_InDistance[y][x].y <= 80.0f) && (objInBlock[y][x]->GetPosition().z != 1000.0f)) {
				objInBlock[y][x]->Update();
			}

			m_TogeDistance[y][x].x = pos.x - objToge[y][x]->GetPosition().x;
			m_TogeDistance[y][x].x = fabs(m_TogeDistance[y][x].x);
			m_TogeDistance[y][x].y = pos.y - objToge[y][x]->GetPosition().y;
			m_TogeDistance[y][x].y = fabs(m_TogeDistance[y][x].y);
			if ((m_TogeDistance[y][x].x <= 60.0f && m_TogeDistance[y][x].y <= 60.0f) && objToge[y][x]->GetPosition().z != 1000.0f) {
				objToge[y][x]->Update();
			}
		}
	}
}
//描画
void Block::Draw(XMFLOAT3& pos) {
	IKEObject3d::PreDraw();
	//マップチップの描画
	for (int y = 0; y < map_max_y; y++)
	{
		for (int x = 0; x < map_max_x; x++)
		{
			if ((m_Distance[y][x].x <= 80.0f && m_Distance[y][x].y <= 80.0f) && (objNormalBlock[y][x]->GetPosition().z != 1000.0f)) {
				if (m_AirType[y][x] == NoAir && m_GoalType[y][x] == NoGoal) {
					objNormalBlock[y][x]->Draw();
				}
			}

			if ((m_InDistance[y][x].x <= 80.0f && m_InDistance[y][x].y <= 80.0f) && (objInBlock[y][x]->GetPosition().z != 1000.0f)) {
				objInBlock[y][x]->Draw();
			}

			if ((m_TogeDistance[y][x].x <= 60.0f && m_TogeDistance[y][x].y <= 60.0f) && objToge[y][x]->GetPosition().z != 1000.0f) {
				objToge[y][x]->Draw();
			}
		}
	}
}
//ブロック配置
void Block::MapCreate(int mapNumber, int StageNumber)
{
	
	for (int y = 0; y < map_max_y; y++) {//(yが15)
		for (int x = 0; x < map_max_x; x++) {//(xが59)

			if (MapChip::GetChipNum(x, y, stagemap[mapNumber]) == Chip_Normal)
			{
				//位置と大きさの変更
				objNormalBlock[y][x]->SetPosition({ x * LAND_SCALE,  -y * LAND_SCALE, 7.5 });
			}

			else if (MapChip::GetChipNum(x, y, stagemap[mapNumber]) == Chip_Air)
			{
				m_AirType[y][x] = AirBlock;
				//位置と大きさの変更
				//objNormalBlock[l_MapPosY][l_MapPosX]->SetScale({ LAND_SCALE, LAND_SCALE, LAND_SCALE });
				objNormalBlock[y][x]->SetPosition({ x * LAND_SCALE,  -y * LAND_SCALE, 0 });
			}
			else if (MapChip::GetChipNum(x, y, stagemap[mapNumber]) == Chip_Down_Goal || MapChip::GetChipNum(x, y, stagemap[mapNumber]) == Chip_Up_Goal || MapChip::GetChipNum(x, y, stagemap[mapNumber]) == Chip_Right_Goal || MapChip::GetChipNum(x, y, stagemap[mapNumber]) == Chip_Left_Goal) {
				objNormalBlock[y][x]->SetPosition({ x * LAND_SCALE,  -y * LAND_SCALE, 5 });
				if (MapChip::GetChipNum(x, y, stagemap[mapNumber]) == Chip_Down_Goal) {
					m_GoalType[y][x] = DownGoal;
				}
				else if (MapChip::GetChipNum(x, y, stagemap[mapNumber]) == Chip_Up_Goal) {
					m_GoalType[y][x] = UpGoal;
				}
				else if (MapChip::GetChipNum(x, y, stagemap[mapNumber]) == Chip_Right_Goal) {
					m_GoalType[y][x] = RightGoal;
				}
				else if (MapChip::GetChipNum(x, y, stagemap[mapNumber]) == Chip_Left_Goal) {
					m_GoalType[y][x] = LeftGoal;
				}
			}

			else if (MapChip::GetChipNum(x, y, stagemap[mapNumber]) == Chip_Up_Thorn || MapChip::GetChipNum(x, y, stagemap[mapNumber]) == Chip_Down_Thorn || MapChip::GetChipNum(x, y, stagemap[mapNumber]) == Chip_Left_Thorn || MapChip::GetChipNum(x, y, stagemap[mapNumber]) == Chip_Right_Thorn)
			{
				//位置と大きさの変更
				objToge[y][x]->SetPosition({ x * LAND_SCALE,  -y * LAND_SCALE, 0 });
				if (MapChip::GetChipNum(x, y, stagemap[mapNumber]) == Chip_Up_Thorn) {
					objToge[y][x]->SetRotation({ 0.0f,0.0f,0.0f });
				}
				else if (MapChip::GetChipNum(x, y, stagemap[mapNumber]) == Chip_Down_Thorn) {
					objToge[y][x]->SetRotation({ 0.0f,0.0f,180.0f });
				}
				else if (MapChip::GetChipNum(x, y, stagemap[mapNumber]) == Chip_Left_Thorn) {
					objToge[y][x]->SetRotation({ 0.0f,0.0f,270.0f });
				}
				else if (MapChip::GetChipNum(x, y, stagemap[mapNumber]) == Chip_Right_Thorn) {
					objToge[y][x]->SetRotation({ 0.0f,0.0f,90.0f });
				}
			}
			else if (MapChip::GetChipNum(x, y, stagemap[mapNumber]) == Chip_In_Block) {
				objInBlock[y][x]->SetPosition({ x * LAND_SCALE,  -y * LAND_SCALE, 7.5 });
			}
		}
	}
}
//プレイヤーとブロック当たり判定
bool Block::PlayerMapCollideCommon(XMFLOAT3& pos, XMFLOAT2 radius,
	const XMFLOAT3& old_pos, bool& is_jump, float& addPower)
{
	if (addPower != 0.0f) {
		m_HitDown = false;
	}
	//マップチップ
	//X, Y
	float l_MapPosX = 0.0f;
	float l_MapPosY = 0.0f;
	//Radius
	float l_RadiusX = 2.5f;
	float l_RadiusUp = 2.5f;
	float l_RadiusDown = 2.8f;

	//フラグ
	bool l_IsHit = false;

	//判定
	int l_MapMaxX = static_cast<int>((pos.x + radius.x + LAND_SCALE / 2) / LAND_SCALE);
	int l_MapMinX = static_cast<int>((pos.x - radius.x + LAND_SCALE / 2) / LAND_SCALE);
	int l_MapMaxY = -static_cast<int>((pos.y - radius.y + LAND_SCALE / 2) / LAND_SCALE - 1);
	int l_MapMinY = -static_cast<int>((pos.y + radius.y + LAND_SCALE / 2) / LAND_SCALE - 1);

	for (int h = l_MapMinY; h <= l_MapMaxY; h++)
	{
		if (h < 0)
		{
			continue;
		}
		for (int w = l_MapMinX; w <= l_MapMaxX; w++)
		{
			if (w < 0)
			{
				continue;
			}

			if (MapChip::GetChipNum(w, h, stagemap[0]) == Chip_Normal)
			{
				l_MapPosX = objNormalBlock[h][w]->GetPosition().x;
				l_MapPosY = objNormalBlock[h][w]->GetPosition().y;

				if (pos.x <= l_MapPosX + l_RadiusX && l_MapPosX - l_RadiusX <= pos.x)
				{
					//下の当たり判定
					if (l_MapPosY + l_RadiusUp + radius.y > pos.y && l_MapPosY < old_pos.y)
					{
						m_HitDown = true;
						pos.y = l_MapPosY + l_RadiusUp + radius.y;
						l_IsHit = true;
					}
					//上の当たり判定
					else if (l_MapPosY - l_RadiusDown - radius.y < pos.y && l_MapPosY > old_pos.y)
					{
						m_HitDown = false;
						pos.y = l_MapPosY - l_RadiusDown - radius.y;
						if (is_jump == false)
						{
							l_IsHit = true;
						}
						else
						{
							addPower = 0;
						}
					}
				}
				if (pos.y <= l_MapPosY + l_RadiusUp && l_MapPosY - l_RadiusDown <= pos.y)
				{
					//左の当たり判定
					if (l_MapPosX + l_RadiusX + radius.x > pos.x && l_MapPosX < old_pos.x)
					{
						m_HitDown = false;
						pos.x = l_MapPosX + l_RadiusX + radius.x;
						if (is_jump == false)
						{
							m_LimitLeft = true;
							l_IsHit = true;
						}
					}
					else {
						m_LimitLeft = false;
					}
					//右の当たり判定
					if (l_MapPosX - l_RadiusX - radius.x < pos.x && l_MapPosX > old_pos.x)
					{
						m_HitDown = false;
						pos.x = l_MapPosX - l_RadiusX - radius.x;
						if (is_jump == false)
						{
							m_LimitRight = true;
							l_IsHit = true;
						}
					}
					else {
						m_LimitRight = false;
					}
				}
			}

			//ゴールとの当たり判定
			else if (MapChip::GetChipNum(w, h, stagemap[0]) == Chip_Down_Goal && !m_Down_Goal && m_GoalType[h][w] == DownGoal)
			{
				l_MapPosX = objNormalBlock[h][w]->GetPosition().x;
				l_MapPosY = objNormalBlock[h][w]->GetPosition().y;

				if (pos.x <= l_MapPosX + l_RadiusX && l_MapPosX - l_RadiusX <= pos.x)
				{
					if (l_MapPosY + l_RadiusUp + radius.y > pos.y && l_MapPosY < old_pos.y)
					{
						m_Down_Goal = true;
					}
					else if (l_MapPosY - l_RadiusDown - radius.y < pos.y && l_MapPosY > old_pos.y)
					{
						if (is_jump == false)
						{
							m_Down_Goal = true;
						}
					}
					else {
						m_Down_Goal = false;
					}
				}
				if (pos.y <= l_MapPosY + l_RadiusUp && l_MapPosY - l_RadiusDown <= pos.y)
				{
					if (l_MapPosX + l_RadiusX + radius.x > pos.x && l_MapPosX < old_pos.x)
					{
						m_Down_Goal = true;
						if (is_jump == false)
						{
							m_Down_Goal = true;
						}
					}
					else if (l_MapPosX - l_RadiusX - radius.x < pos.x && l_MapPosX > old_pos.x)
					{
						m_Down_Goal = true;
						if (is_jump == false)
						{
							m_Down_Goal = true;
						}
					}
					else {
						m_Down_Goal = false;
					}
				}
			}

			//ゴールとの当たり判定
			else if (MapChip::GetChipNum(w, h, stagemap[0]) == Chip_Up_Goal && !m_Up_Goal && m_GoalType[h][w] == UpGoal)
			{
				l_MapPosX = objNormalBlock[h][w]->GetPosition().x;
				l_MapPosY = objNormalBlock[h][w]->GetPosition().y;

				if (pos.x <= l_MapPosX + l_RadiusX && l_MapPosX - l_RadiusX <= pos.x)
				{
					if (l_MapPosY + l_RadiusUp + radius.y > pos.y && l_MapPosY < old_pos.y)
					{
						m_Up_Goal = true;
					}
					else if (l_MapPosY - l_RadiusDown - radius.y < pos.y && l_MapPosY > old_pos.y)
					{
						if (is_jump == false)
						{
							m_Up_Goal = true;
						}
					}
					else {
						m_Up_Goal = false;
					}
				}
				if (pos.y <= l_MapPosY + l_RadiusUp && l_MapPosY - l_RadiusDown <= pos.y)
				{
					if (l_MapPosX + l_RadiusX + radius.x > pos.x && l_MapPosX < old_pos.x)
					{
						m_Up_Goal = true;
						if (is_jump == false)
						{
							m_Up_Goal = true;
						}
					}
					else if (l_MapPosX - l_RadiusX - radius.x < pos.x && l_MapPosX > old_pos.x)
					{
						m_Up_Goal = true;
						if (is_jump == false)
						{
							m_Up_Goal = true;
						}
					}
					else {
						m_Up_Goal = false;
					}
				}
			}

			//ゴールとの当たり判定
			else if (MapChip::GetChipNum(w, h, stagemap[0]) == Chip_Right_Goal && !m_Right_Goal && m_GoalType[h][w] == RightGoal)
			{
				l_MapPosX = objNormalBlock[h][w]->GetPosition().x;
				l_MapPosY = objNormalBlock[h][w]->GetPosition().y;

				if (pos.x <= l_MapPosX + l_RadiusX && l_MapPosX - l_RadiusX <= pos.x)
				{
					if (l_MapPosY + l_RadiusUp + radius.y > pos.y && l_MapPosY < old_pos.y)
					{
						m_Right_Goal = true;
					}
					else if (l_MapPosY - l_RadiusDown - radius.y < pos.y && l_MapPosY > old_pos.y)
					{
						if (is_jump == false)
						{
							m_Right_Goal = true;
						}
					}
					else {
						m_Right_Goal = false;
					}
				}
				if (pos.y <= l_MapPosY + l_RadiusUp && l_MapPosY - l_RadiusDown <= pos.y)
				{
					if (l_MapPosX + l_RadiusX + radius.x > pos.x && l_MapPosX < old_pos.x)
					{
						m_Right_Goal = true;
						if (is_jump == false)
						{
							m_Right_Goal = true;
						}
					}
					else if (l_MapPosX - l_RadiusX - radius.x < pos.x && l_MapPosX > old_pos.x)
					{
						m_Right_Goal = true;
						if (is_jump == false)
						{
							m_Right_Goal = true;
						}
					}
					else {
						m_Right_Goal = false;
					}
				}
			}

			//ゴールとの当たり判定
			else if (MapChip::GetChipNum(w, h, stagemap[0]) == Chip_Left_Goal && !m_Left_Goal && m_GoalType[h][w] == LeftGoal)
			{
				l_MapPosX = objNormalBlock[h][w]->GetPosition().x;
				l_MapPosY = objNormalBlock[h][w]->GetPosition().y;

				if (pos.x <= l_MapPosX + l_RadiusX && l_MapPosX - l_RadiusX <= pos.x)
				{
					if (l_MapPosY + l_RadiusUp + radius.y > pos.y && l_MapPosY < old_pos.y)
					{
						m_Left_Goal = true;
					}
					else if (l_MapPosY - l_RadiusDown - radius.y < pos.y && l_MapPosY > old_pos.y)
					{
						if (is_jump == false)
						{
							m_Left_Goal = true;
						}
					}
					else {
						m_Left_Goal = false;
					}
				}
				if (pos.y <= l_MapPosY + l_RadiusUp && l_MapPosY - l_RadiusDown <= pos.y)
				{
					if (l_MapPosX + l_RadiusX + radius.x > pos.x && l_MapPosX < old_pos.x)
					{
						m_Left_Goal = true;
						if (is_jump == false)
						{
							m_Left_Goal = true;
						}
					}
					else if (l_MapPosX - l_RadiusX - radius.x < pos.x && l_MapPosX > old_pos.x)
					{
						m_Left_Goal = true;
						if (is_jump == false)
						{
							l_IsHit = true;
							m_Left_Goal = true;
						}
					}
					else {
						m_Left_Goal = false;
					}
				}
			}


			//棘との当たり判定
			else if ((MapChip::GetChipNum(w, h, stagemap[0]) == Chip_Up_Thorn || MapChip::GetChipNum(w, h, stagemap[0]) == Chip_Down_Thorn ||
				MapChip::GetChipNum(w, h, stagemap[0]) == Chip_Left_Thorn || MapChip::GetChipNum(w, h, stagemap[0]) == Chip_Right_Thorn)
				&& objToge[h][w]->GetPosition().z != 1000.0f)
			{
				l_MapPosX = objToge[h][w]->GetPosition().x;
				l_MapPosY = objToge[h][w]->GetPosition().y;

				if (pos.x <= l_MapPosX + l_RadiusX && l_MapPosX - l_RadiusX <= pos.x)
				{
					//下の当たり判定
					if (l_MapPosY + l_RadiusUp + radius.y > pos.y && l_MapPosY < old_pos.y)
					{
						m_ThornDir = DownThorn;
						m_ThornHit = true;
						pos.y = l_MapPosY + l_RadiusUp + radius.y;
						l_IsHit = true;
					}
					//上の当たり判定
					else if (l_MapPosY - l_RadiusDown - radius.y < pos.y && l_MapPosY > old_pos.y)
					{
						m_ThornDir = UpThorn;
						m_ThornHit = true;
						pos.y = l_MapPosY - l_RadiusDown - radius.y;
						if (is_jump == false)
						{
							l_IsHit = true;
						}
					}
				}
				if (pos.y <= l_MapPosY + l_RadiusUp && l_MapPosY - l_RadiusDown <= pos.y)
				{
					//左の当たり判定
					if (l_MapPosX + l_RadiusX + radius.x > pos.x && l_MapPosX < old_pos.x)
					{
						m_ThornDir = LeftThorn;
						m_ThornHit = true;
						pos.x = l_MapPosX + l_RadiusX + radius.x;
						if (is_jump == false)
						{
							m_ThornHit = true;
							l_IsHit = true;
						}
					}
					//右の当たり判定
					else if (l_MapPosX - l_RadiusX - radius.x < pos.x && l_MapPosX > old_pos.x)
					{
						m_ThornDir = RightThorn;
						m_ThornHit = true;
						pos.x = l_MapPosX - l_RadiusX - radius.x;
						if (is_jump == false)
						{
							m_ThornHit = true;
							l_IsHit = true;
						}
					}
				}
			}

		}
	}

	return l_IsHit;
}
//攻撃の当たり判定
bool Block::AttackMapCollideCommon(XMFLOAT3 pos, XMFLOAT2 radius, const XMFLOAT3 old_pos)
{
	//マップチップ
	//X, Y
	float l_MapPosX = 0;
	float l_MapPosY = 0;
	//Radius
	float l_RadiusX = 0;
	float l_RadiusY = 0;

	//フラグ
	bool l_IsHit = false;

	//判定
	int l_MapMaxX = static_cast<int>((pos.x + radius.x + LAND_SCALE / 2) / LAND_SCALE);
	int l_MapMinX = static_cast<int>((pos.x - radius.x + LAND_SCALE / 2) / LAND_SCALE);
	int l_MapMaxY = -static_cast<int>((pos.y - radius.y + LAND_SCALE / 2) / LAND_SCALE - 1);
	int l_MapMinY = -static_cast<int>((pos.y + radius.y + LAND_SCALE / 2) / LAND_SCALE - 1);

	for (int h = l_MapMinY; h <= l_MapMaxY; h++)
	{
		if (h < 0)
		{
			continue;
		}
		for (int w = l_MapMinX; w <= l_MapMaxX; w++)
		{
			if (w < 0)
			{
				continue;
			}
			if (MapChip::GetChipNum(w, h, stagemap[0]) == Chip_Normal)
			{
				l_MapPosX = objNormalBlock[h][w]->GetPosition().x;
				l_MapPosY = objNormalBlock[h][w]->GetPosition().y;
				l_RadiusX = 2.5f;
				l_RadiusY = 2.5f;

				if (pos.x <= l_MapPosX + l_RadiusX && l_MapPosX - l_RadiusX <= pos.x)
				{
					//下の当たり判定
					if (l_MapPosY + l_RadiusY + radius.y > pos.y && l_MapPosY < old_pos.y)
					{
						l_IsHit = true;
					}
					//上の当たり判定
					else if (l_MapPosY - l_RadiusY - radius.y < pos.y && l_MapPosY > old_pos.y)
					{
						l_IsHit = true;
					}
				}
				if (pos.y <= l_MapPosY + l_RadiusY && l_MapPosY - l_RadiusY <= pos.y)
				{
					//左の当たり判定
					if (l_MapPosX + l_RadiusX + radius.x > pos.x && l_MapPosX < old_pos.x)
					{
						l_IsHit = true;
					}
					//右の当たり判定
					else if (l_MapPosX - l_RadiusX - radius.x < pos.x && l_MapPosX > old_pos.x)
					{
						l_IsHit = true;
					}
				}
			}
		}
	}

	return l_IsHit;
}
//移動限界用当たり判定(攻撃)
bool Block::LimitMapCollideCommon(XMFLOAT3& pos, XMFLOAT2 radius, const XMFLOAT3 old_pos) {
	//マップチップ
		//X, Y
	float l_MapPosX = 0;
	float l_MapPosY = 0;
	//Radius
	float l_RadiusX = 0;
	float l_RadiusY = 0;

	//フラグ
	bool l_IsHit = false;

	//判定
	int l_MapMaxX = static_cast<int>((pos.x + radius.x + LAND_SCALE / 2) / LAND_SCALE);
	int l_MapMinX = static_cast<int>((pos.x - radius.x + LAND_SCALE / 2) / LAND_SCALE);
	int l_MapMaxY = -static_cast<int>((pos.y - radius.y + LAND_SCALE / 2) / LAND_SCALE - 1);
	int l_MapMinY = -static_cast<int>((pos.y + radius.y + LAND_SCALE / 2) / LAND_SCALE - 1);

	for (int h = l_MapMinY; h <= l_MapMaxY; h++)
	{
		if (h < 0)
		{
			continue;
		}
		for (int w = l_MapMinX; w <= l_MapMaxX; w++)
		{
			if (w < 0)
			{
				continue;
			}
			if (MapChip::GetChipNum(w, h, stagemap[0]) == Chip_Normal)
			{
				l_MapPosX = objNormalBlock[h][w]->GetPosition().x;
				l_MapPosY = objNormalBlock[h][w]->GetPosition().y;
				l_RadiusX = 2.5f;
				l_RadiusY = 2.5f;

				if (pos.x <= l_MapPosX + l_RadiusX && l_MapPosX - l_RadiusX <= pos.x)
				{
					//下の当たり判定
					if (l_MapPosY + l_RadiusY + radius.y > pos.y && l_MapPosY < old_pos.y)
					{
						l_IsHit = true;
					}
					//上の当たり判定
					else if (l_MapPosY - l_RadiusY - radius.y < pos.y && l_MapPosY > old_pos.y)
					{
						l_IsHit = true;
					}
				}
				if (pos.y <= l_MapPosY + l_RadiusY && l_MapPosY - l_RadiusY <= pos.y)
				{
					//左の当たり判定
					if (l_MapPosX + l_RadiusX + radius.x > pos.x && l_MapPosX < old_pos.x)
					{
						l_IsHit = true;
					}
					//右の当たり判定
					else if (l_MapPosX - l_RadiusX - radius.x < pos.x && l_MapPosX > old_pos.x)
					{
						l_IsHit = true;
					}
				}
			}
		}
	}

	return l_IsHit;
}
//敵とブロックの当たり判定
bool Block::EnemyMapCollideCommon(XMFLOAT3& pos, XMFLOAT2 radius,
	const XMFLOAT3& old_pos, bool& is_jump, float& EnemyaddPower, int& touchWall, int& HP)
{
	//マップチップ
	//X, Y
	float l_MapPosX = 0;
	float l_MapPosY = 0;
	//Radius
	float l_RadiusX = 0;
	float l_RadiusY = 0;

	//フラグ
	bool l_IsHit = false;

	//判定
	int l_MapMaxX = static_cast<int>((pos.x + radius.x + LAND_SCALE / 2) / LAND_SCALE);
	int l_MapMinX = static_cast<int>((pos.x - radius.x + LAND_SCALE / 2) / LAND_SCALE);
	int l_MapMaxY = -static_cast<int>((pos.y - radius.y + LAND_SCALE / 2) / LAND_SCALE - 1);
	int l_MapMinY = -static_cast<int>((pos.y + radius.y + LAND_SCALE / 2) / LAND_SCALE - 1);

	for (int h = l_MapMinY; h <= l_MapMaxY; h++)
	{
		if (h < 0)
		{
			continue;
		}
		for (int w = l_MapMinX; w <= l_MapMaxX; w++)
		{
			if (w < 0)
			{
				continue;
			}
			if (MapChip::GetChipNum(w, h, stagemap[0]) == Chip_Normal)
			{
				l_MapPosX = objNormalBlock[h][w]->GetPosition().x;
				l_MapPosY = objNormalBlock[h][w]->GetPosition().y;
				l_RadiusX = 2.5f;
				l_RadiusY = 2.5f;

				if (pos.x <= l_MapPosX + l_RadiusX && l_MapPosX - l_RadiusX <= pos.x)
				{
					//下の当たり判定
					if (l_MapPosY + l_RadiusY + radius.y > pos.y && l_MapPosY < old_pos.y)
					{
						is_jump = true;
						pos.y = l_MapPosY + l_RadiusY + radius.y;
						l_IsHit = true;
					}
					//上の当たり判定
					else if (l_MapPosY - l_RadiusY - radius.y < pos.y && l_MapPosY > old_pos.y)
					{

						pos.y = l_MapPosY - l_RadiusY - radius.y;
						if (is_jump == false)
						{
							l_IsHit = true;
						}
						else
						{
							EnemyaddPower = 0;
						}
					}
				}
				if (pos.y <= l_MapPosY + l_RadiusY && l_MapPosY - l_RadiusY <= pos.y)
				{
					//左の当たり判定
					if (l_MapPosX + l_RadiusX + radius.x > pos.x && l_MapPosX < old_pos.x)
					{
						touchWall = Left;
						pos.x = l_MapPosX + l_RadiusX + radius.x;
						if (is_jump == false)
						{
							touchWall = Left;
							l_IsHit = true;
						}
					}
					//右の当たり判定
					else if (l_MapPosX - l_RadiusX - radius.x < pos.x && l_MapPosX > old_pos.x)
					{
						touchWall = Right;
						pos.x = l_MapPosX - l_RadiusX - radius.x;
						if (is_jump == false)
						{
							touchWall = Right;
							l_IsHit = true;
						}
					}
				}
			}
			else if (MapChip::GetChipNum(w, h, stagemap[0]) == Chip_Air && m_AirType[h][w] == AirBlock && HP >= 1)
			{
				l_MapPosX = objNormalBlock[h][w]->GetPosition().x;
				l_MapPosY = objNormalBlock[h][w]->GetPosition().y;
				l_RadiusX = 2.5f;
				l_RadiusY = 2.5f;

				if (pos.x <= l_MapPosX + l_RadiusX && l_MapPosX - l_RadiusX <= pos.x)
				{
					//下の当たり判定
					if (l_MapPosY + l_RadiusY + radius.y > pos.y && l_MapPosY < old_pos.y)
					{
						touchWall = Down;
						pos.y = l_MapPosY + l_RadiusY + radius.y;
						l_IsHit = true;
					}
					//上の当たり判定
					else if (l_MapPosY - l_RadiusY - radius.y < pos.y && l_MapPosY > old_pos.y)
					{
						touchWall = Down;
						pos.y = l_MapPosY - l_RadiusY - radius.y;
						if (is_jump == false)
						{
							l_IsHit = true;
						}
						else
						{
							EnemyaddPower = 0;
						}
					}
				}
				if (pos.y <= l_MapPosY + l_RadiusY && l_MapPosY - l_RadiusY <= pos.y)
				{
					//左の当たり判定
					if (l_MapPosX + l_RadiusX + radius.x > pos.x && l_MapPosX < old_pos.x)
					{
						touchWall = Left;
						pos.x = l_MapPosX + l_RadiusX + radius.x;
						if (is_jump == false)
						{
							touchWall = Left;
							l_IsHit = true;
						}
					}
					//右の当たり判定
					else if (l_MapPosX - l_RadiusX - radius.x < pos.x && l_MapPosX > old_pos.x)
					{
						touchWall = Right;
						pos.x = l_MapPosX - l_RadiusX - radius.x;
						if (is_jump == false)
						{
							touchWall = Right;
							l_IsHit = true;
						}
					}
				}
			}
		}
	}

	return l_IsHit;
}
//飛んでる敵とブロックの当たり判定
bool Block::BirdEnemyMapCollideCommon(XMFLOAT3& pos, XMFLOAT2 radius, int& touchWall,
	const XMFLOAT3& old_pos, bool& is_Attack)
{
	//マップチップ
	//X, Y
	float l_MapPosX = 0;
	float l_MapPosY = 0;
	//Radius
	float l_RadiusX = 0;
	float l_RadiusY = 0;

	//フラグ
	bool l_IsHit = false;

	//判定
	int l_MapMaxX = static_cast<int>((pos.x + radius.x + LAND_SCALE / 2) / LAND_SCALE);
	int l_MapMinX = static_cast<int>((pos.x - radius.x + LAND_SCALE / 2) / LAND_SCALE);
	int l_MapMaxY = -static_cast<int>((pos.y - radius.y + LAND_SCALE / 2) / LAND_SCALE - 1);
	int l_MapMinY = -static_cast<int>((pos.y + radius.y + LAND_SCALE / 2) / LAND_SCALE - 1);

	for (int h = l_MapMinY; h <= l_MapMaxY; h++)
	{
		if (h < 0)
		{
			continue;
		}
		for (int w = l_MapMinX; w <= l_MapMaxX; w++)
		{
			if (w < 0)
			{
				continue;
			}
			if (MapChip::GetChipNum(w, h, stagemap[0]) == Chip_Normal)
			{
				l_MapPosX = objNormalBlock[h][w]->GetPosition().x;
				l_MapPosY = objNormalBlock[h][w]->GetPosition().y;
				l_RadiusX = 2.5f;
				l_RadiusY = 2.5f;

				if (pos.x <= l_MapPosX + l_RadiusX && l_MapPosX - l_RadiusX <= pos.x)
				{
					//下の当たり判定
					if (l_MapPosY + l_RadiusY + radius.y > pos.y && l_MapPosY < old_pos.y)
					{
						if (is_Attack) {
							is_Attack = false;
						}
						touchWall = 0;
						pos.y = l_MapPosY + l_RadiusY + radius.y;
						l_IsHit = true;
					}
					//上の当たり判定
					else if (l_MapPosY - l_RadiusY - radius.y < pos.y && l_MapPosY > old_pos.y)
					{

						if (is_Attack) {
							is_Attack = false;
						}
						touchWall = 1;
						pos.y = l_MapPosY - l_RadiusY - radius.y;
						l_IsHit = true;
					}
					else {
						touchWall = 2;
					}
				}
				if (pos.y <= l_MapPosY + l_RadiusY && l_MapPosY - l_RadiusY <= pos.y)
				{
					//左の当たり判定
					if (l_MapPosX + l_RadiusX + radius.x > pos.x && l_MapPosX < old_pos.x)
					{
						pos.x = l_MapPosX + l_RadiusX + radius.x;
						if (is_Attack) {
							is_Attack = false;
						}
						l_IsHit = true;
					}
					//右の当たり判定
					else if (l_MapPosX - l_RadiusX - radius.x < pos.x && l_MapPosX > old_pos.x)
					{
						//touchWall = Right;
						pos.x = l_MapPosX - l_RadiusX - radius.x;
						if (is_Attack) {
							is_Attack = false;
						}
						l_IsHit = true;
					}
				}
			}
		}
	}

	return l_IsHit;
}
//追尾的との当たり判定
bool Block::FollowEnemyMapCollideCommon(XMFLOAT3& pos, XMFLOAT2 radius, const XMFLOAT3& old_pos) {
	//マップチップ
	//X, Y
	float l_MapPosX = 0;
	float l_MapPosY = 0;
	//Radius
	float l_RadiusX = 0;
	float l_RadiusY = 0;

	//フラグ
	bool l_IsHit = false;

	//判定
	int l_MapMaxX = static_cast<int>((pos.x + radius.x + LAND_SCALE / 2) / LAND_SCALE);
	int l_MapMinX = static_cast<int>((pos.x - radius.x + LAND_SCALE / 2) / LAND_SCALE);
	int l_MapMaxY = -static_cast<int>((pos.y - radius.y + LAND_SCALE / 2) / LAND_SCALE - 1);
	int l_MapMinY = -static_cast<int>((pos.y + radius.y + LAND_SCALE / 2) / LAND_SCALE - 1);

	for (int h = l_MapMinY; h <= l_MapMaxY; h++)
	{
		if (h < 0)
		{
			continue;
		}
		for (int w = l_MapMinX; w <= l_MapMaxX; w++)
		{
			if (w < 0)
			{
				continue;
			}
			if (MapChip::GetChipNum(w, h, stagemap[0]) == Chip_Normal)
			{
				l_MapPosX = objNormalBlock[h][w]->GetPosition().x;
				l_MapPosY = objNormalBlock[h][w]->GetPosition().y;
				l_RadiusX = 2.5f;
				l_RadiusY = 2.5f;

				if (pos.x <= l_MapPosX + l_RadiusX && l_MapPosX - l_RadiusX <= pos.x)
				{
					//下の当たり判定
					if (l_MapPosY + l_RadiusY + radius.y > pos.y && l_MapPosY < old_pos.y)
					{
						pos.y = l_MapPosY + l_RadiusY + radius.y;
						l_IsHit = true;
					}
					//上の当たり判定
					else if (l_MapPosY - l_RadiusY - radius.y < pos.y && l_MapPosY > old_pos.y)
					{
						pos.y = l_MapPosY - l_RadiusY - radius.y;
						l_IsHit = true;
					}
				}
				if (pos.y <= l_MapPosY + l_RadiusY && l_MapPosY - l_RadiusY <= pos.y)
				{
					//左の当たり判定
					if (l_MapPosX + l_RadiusX + radius.x > pos.x && l_MapPosX < old_pos.x)
					{
						pos.x = l_MapPosX + l_RadiusX + radius.x;
						l_IsHit = true;
					}
					//右の当たり判定
					else if (l_MapPosX - l_RadiusX - radius.x < pos.x && l_MapPosX > old_pos.x)
					{
						pos.x = l_MapPosX - l_RadiusX - radius.x;
						l_IsHit = true;
					}
				}
			}
			else if (MapChip::GetChipNum(w, h, stagemap[0]) == Chip_In_Block)
			{
				l_MapPosX = objInBlock[h][w]->GetPosition().x;
				l_MapPosY = objInBlock[h][w]->GetPosition().y;
				l_RadiusX = 2.5f;
				l_RadiusY = 2.5f;

				if (pos.x <= l_MapPosX + l_RadiusX && l_MapPosX - l_RadiusX <= pos.x)
				{
					//下の当たり判定
					if (l_MapPosY + l_RadiusY + radius.y > pos.y && l_MapPosY < old_pos.y)
					{
						pos.y = l_MapPosY + l_RadiusY + radius.y;
						l_IsHit = true;
					}
					//上の当たり判定
					else if (l_MapPosY - l_RadiusY - radius.y < pos.y && l_MapPosY > old_pos.y)
					{
						pos.y = l_MapPosY - l_RadiusY - radius.y;
						l_IsHit = true;
					}
				}
				if (pos.y <= l_MapPosY + l_RadiusY && l_MapPosY - l_RadiusY <= pos.y)
				{
					//左の当たり判定
					if (l_MapPosX + l_RadiusX + radius.x > pos.x && l_MapPosX < old_pos.x)
					{
						pos.x = l_MapPosX + l_RadiusX + radius.x;
						l_IsHit = true;
					}
					//右の当たり判定
					else if (l_MapPosX - l_RadiusX - radius.x < pos.x && l_MapPosX > old_pos.x)
					{
						pos.x = l_MapPosX - l_RadiusX - radius.x;
						l_IsHit = true;
					}
				}
			}
		}
	}

	return l_IsHit;
}
//魂とブロック当たり判定
bool Block::PlayerSoulMapCollideCommon(XMFLOAT3& pos, XMFLOAT2 radius,
	const XMFLOAT3& old_pos, bool& is_jump, float& addPower)
{
	//マップチップ
	//X, Y
	float l_MapPosX = 0;
	float l_MapPosY = 0;
	//Radius
	float l_RadiusX = 0;
	float l_RadiusY = 0;

	//フラグ
	bool l_IsHit = false;

	//判定
	int l_MapMaxX = static_cast<int>((pos.x + radius.x + LAND_SCALE / 2) / LAND_SCALE);
	int l_MapMinX = static_cast<int>((pos.x - radius.x + LAND_SCALE / 2) / LAND_SCALE);
	int l_MapMaxY = -static_cast<int>((pos.y - radius.y + LAND_SCALE / 2) / LAND_SCALE - 1);
	int l_MapMinY = -static_cast<int>((pos.y + radius.y + LAND_SCALE / 2) / LAND_SCALE - 1);

	for (int h = l_MapMinY; h <= l_MapMaxY; h++)
	{
		if (h < 0)
		{
			continue;
		}
		for (int w = l_MapMinX; w <= l_MapMaxX; w++)
		{
			if (w < 0)
			{
				continue;
			}

			if (MapChip::GetChipNum(w, h, stagemap[0]) == Chip_Normal)
			{
				l_MapPosX = objNormalBlock[h][w]->GetPosition().x;
				l_MapPosY = objNormalBlock[h][w]->GetPosition().y;
				l_RadiusX = 2.5f;
				l_RadiusY = 2.5f;

				if (pos.x <= l_MapPosX + l_RadiusX && l_MapPosX - l_RadiusX <= pos.x)
				{
					//下の当たり判定
					if (l_MapPosY + l_RadiusY + radius.y > pos.y && l_MapPosY < old_pos.y)
					{
						pos.y = l_MapPosY + l_RadiusY + radius.y;
						l_IsHit = true;
					}
					//上の当たり判定
					else if (l_MapPosY - l_RadiusY - radius.y < pos.y && l_MapPosY > old_pos.y)
					{
						//hit = 2;
						pos.y = l_MapPosY - l_RadiusY - radius.y;
						if (is_jump == false)
						{
							l_IsHit = true;
						}
						else
						{
							addPower = 0;
						}
					}
				}
				if (pos.y <= l_MapPosY + l_RadiusY && l_MapPosY - l_RadiusY <= pos.y)
				{
					//左の当たり判定
					if (l_MapPosX + l_RadiusX + radius.x > pos.x && l_MapPosX < old_pos.x)
					{
						pos.x = l_MapPosX + l_RadiusX + radius.x;
						if (is_jump == false)
						{
							l_IsHit = true;
						}
					}
					//右の当たり判定
					else if (l_MapPosX - l_RadiusX - radius.x < pos.x && l_MapPosX > old_pos.x)
					{
						pos.x = l_MapPosX - l_RadiusX - radius.x;
						if (is_jump == false)
						{
							l_IsHit = true;
						}
					}
				}
			}

		}
	}

	return l_IsHit;
}
//マップチップの初期化
void Block::ResetBlock() {
	for (int y = 0; y < map_max_y; y++)
	{
		for (int x = 0; x < map_max_x; x++)
		{
			objNormalBlock[y][x]->SetPosition({ 1000.0f,1000.0f,1000.0f });
			objInBlock[y][x]->SetPosition({ 1000.0f,1000.0f,1000.0f });
			objToge[y][x]->SetPosition({ 1000.0f,1000.0f,1000.0f });
			m_GoalType[y][x] = NoGoal;
			m_AirType[y][x] = NoAir;
		}
	}
	m_Down_Goal = false;
	m_Up_Goal = false;
	m_Right_Goal = false;
	m_Left_Goal = false;
}