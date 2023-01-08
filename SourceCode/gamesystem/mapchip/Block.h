#pragma once
#include <DirectXMath.h>
#include "MapChip.h"
#include "IKEObject3d.h"
#include "VariableCommon.h"
#include <memory>
#include <list> // ヘッダファイルインクルード
using namespace std;         //  名前空間指定
//マップチップのクラス
class Block {
private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	Block();

	void Initialize(std::vector<std::vector<int>>& map, int mapNumber,int StageNumber);
	void Finalize();
	void Update(XMFLOAT3& pos);
	void Draw(XMFLOAT3& pos);

	void ResetBlock();

	//マップチップ生成
	void MapCreate(int mapNumber,int StageNumber);

	//引数が多いので構造体にする予定
	//マップチップ当たり判定(プレイヤー)
	bool PlayerMapCollideCommon(XMFLOAT3& pos, XMFLOAT2 radius,
		const XMFLOAT3& old_pos, bool& is_jump,float& addPower);
	//マップチップ当たり判定(攻撃)
	bool AttackMapCollideCommon(XMFLOAT3& pos, XMFLOAT2 radius,const XMFLOAT3& old_pos);
	//マップチップ当たり判定(敵)
	bool EnemyMapCollideCommon(XMFLOAT3& pos, XMFLOAT2 radius,
		const XMFLOAT3& old_pos, bool& is_jump,float& EnemyaddPower,int& touchWall,int& HP);
	//マップチップ当たり判定(飛んでる敵)
	bool BirdEnemyMapCollideCommon(XMFLOAT3& pos, XMFLOAT2 radius, int &touchWall,
		const XMFLOAT3& old_pos, bool& Attack);
	//マップチップ当たり判定(魂)
	bool PlayerSoulMapCollideCommon(XMFLOAT3& pos, XMFLOAT2 radius, 
		const XMFLOAT3& old_pos, bool& is_jump, float& addPower);

	//getter
	const bool& GetThornHit() { return  m_ThornHit; }
	const int& GetThornDir() { return  m_ThornDir; }
	const bool& GetLeftGoal() { return  m_Left_Goal; }
	const bool& GetRightGoal() { return  m_Right_Goal; }
	const bool& GetDownGoal() { return  m_Down_Goal; }
	const bool& GetUpGoal() { return  m_Up_Goal; }
	const bool& GetHitDown() { return m_HitDown; }
	//setter
	void SetThornDir(const int& thorndir) { this->m_ThornDir = thorndir; }
	void SetThornHit(const bool& thornhit) { this->m_ThornHit = thornhit; }
	void SetLeftGoal(const bool& Left_goal) { this->m_Left_Goal = Left_goal; }
	void SetRightGoal(const bool& Right_goal) { this->m_Right_Goal = Right_goal; }
	void SetDownGoal(const bool& Down_goal) { this->m_Down_Goal = Down_goal; }
	void SetUpGoal(const bool& Up_goal) { this->m_Up_Goal = Up_goal; }
private:
	//地面にあたっているか
	bool m_HitDown = false;
	//棘に当たったか
	bool m_ThornHit = false;
	//どのゴールに当たったか
	bool m_Left_Goal = false;
	bool m_Right_Goal = false;
	bool m_Down_Goal = false;
	bool m_Up_Goal = false;
	//マップチップ1つの大きさ
	const float LAND_SCALE = 5.0f;
	//マップチップ関係
	unique_ptr<IKEModel> modelNormalBlock = nullptr;
	unique_ptr<IKEModel> modelInBlock = nullptr;
	unique_ptr<IKEModel> modelAirBlock = nullptr;
	unique_ptr<IKEModel> modelToge = nullptr;
	unique_ptr<IKEModel> modelGoalBlock = nullptr;
	//各マップの読み込み
	std::vector<std::vector<int>> stagemap; //1マップ
	std::vector<std::vector<int>> bossmap; //ボスマップ
	unique_ptr <IKEObject3d> objNormalBlock[map_max_y][map_max_x]; //ステージブロック
	unique_ptr <IKEObject3d> objInBlock[map_max_y][map_max_x]; //ステージブロック
	unique_ptr <IKEObject3d> objToge[map_max_y][map_max_x]; //ステージブロック(棘)
	
	//各変数
	int m_GoalType[map_max_y][map_max_x];//ゴールのタイプ
	int m_AirType[map_max_y][map_max_x];//透明かどうか
	XMFLOAT3 m_Distance[map_max_y][map_max_x];//プレイヤーとの距離
	XMFLOAT3 m_InDistance[map_max_y][map_max_x];//プレイヤーとの距離
	XMFLOAT3 m_TogeDistance[map_max_y][map_max_x];//上に同じ
	int m_ThornDir = 0;//棘の向き
	
	//敵のタイプ
	enum EnemyType {
		Normal,
		Wing,
	};

	enum TouchWall {
		Right,
		Left,
		Down,
	};

	enum GoalType {
		NoGoal,
		DownGoal,
		UpGoal,
		RightGoal,
		LeftGoal
	};

	enum AirType {
		NoAir,
		AirBlock,
	};

	enum ThornDir {
		NoThorn,
		UpThorn,
		DownThorn,
		LeftThorn,
		RightThorn
	};
};