#pragma once
#include "IKESprite.h"
#include "Player.h"
#include "Save.h"
#include "MapChip.h"
#include <array>   
using namespace std;         //  名前空間指定
//ミニマップ
class MiniMap {
public:
	MiniMap();
	void SetPlayer(Player* player) { this->player = player; }
	void SetSave(Save* save) { this->save = save; }
	void Initialize();//初期化
	void Update();//更新
	void Finalize();//解放
	const void Draw();//描画
	void UseCompass();//スキル(コンパス)を使っているか
	void SetMiniPlayerPos(int StageNumber);//ステージごとの初期化
	void InitMap(std::vector<std::vector<int>>& map, int StageNumber);//マップの初期化
	void ResetBlock();//マップのリセット
	void MoveStateTex();//テキストの動き
	//マップチップ生成
	void MapCreate(int mapNumber, int StageNumber);
	//マップ選択肢
	void SelectMapType();
	void WholeUpdate();
	void SelectUpdate();
	void ColorChange();
private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	//getter
	bool GetReturnMap() { return m_ReturnMap; }
	int GetMapType() { return m_MapType; }
	XMFLOAT4 GetMapColor() { return m_MapColor; }
	//setter
	void SetReturnMap(bool m_ReturnMap) { this->m_ReturnMap = m_ReturnMap; }
	void SetDushDraw(bool m_DushDraw) { this->m_DushDraw = m_DushDraw; }
	void SetChangeColorType(int m_ColorChangeType) { this->m_ColorChangeType = m_ColorChangeType; }
	void SetMapType(int m_MapType) { this->m_MapType = m_MapType; }
private:
	const float m_LAND_SCALEX = 22.0f;
	const float m_LAND_SCALEY = 12.0f;
	Player* player = nullptr;
	Save* save = nullptr;
	XMFLOAT2 m_PlayerPos;
	XMFLOAT2 m_SavePos;
	XMFLOAT2 m_DushPos;
	//スプライト
	unique_ptr<IKESprite> MiniMapSprite;
	unique_ptr<IKESprite> MiniPlayerSprite;
	unique_ptr<IKESprite> MiniSaveSprite;
	unique_ptr<IKESprite> MiniDushSprite;
	unique_ptr<IKESprite> MiniBlockSprite[map_max_y][map_max_x]; //ステージブロック
	unique_ptr<IKESprite> MiniBlockTogeSprite[map_max_y][map_max_x]; //ステージブロック(棘)
	unique_ptr<IKESprite> WholeMapSprite;
	unique_ptr<IKESprite> MapStateSprite;
	//変数
	XMFLOAT3 m_Distance[map_max_y][map_max_x];
	bool LookMap[map_max_y][map_max_x];
	//各マップの読み込み
	std::vector<std::vector<int>> stagemap; //1マップ
	bool m_ReturnMap = false;
	bool LookPlayer = false;
	//ステージナンバー
	int m_StageNumber = 0;
	//ダッシュのスプライトの描画判定
	bool m_DushDraw = false;
	enum StageNumber {
		Map1,
		Map2,
		Map3,
		Map4,
		Map5,
		Map6,
		BossMap,
		TutoRial,
	};
	//色
	XMFLOAT4 m_PlayerColor = { 1.0f,1.0f,1.0f,0.0f };
	XMFLOAT4 m_SaveColor = { 1.0f,1.0f,1.0f,0.0f };
	XMFLOAT4 m_MapColor = { 1.0f,1.0f,1.0f,0.0f };
	XMFLOAT4 m_WholeColor = { 1.0f,1.0f,1.0f,1.0f };
	XMFLOAT4 m_DushColor = { 1.0f,1.0f,1.0f,0.0f };
	//透過の動き
	int m_ColorChangeType = 0;
	enum ChangeType {
		No,
		Add,
		Sub,
	};
	//下に流れるテキスト関係の関数
	XMFLOAT2 m_SelectPos;
	XMFLOAT2 m_SelectSize = { 96.0f,96.0f };
	float m_Angle = 0.0f;
	float m_Angle2 = 0.0f;

	bool m_MapTypeChange = false;
	int m_MapType = 0;
	enum MapType {
		Whole,
		SelectMap
	};
	int m_StateTextNumber = 0;
	int m_TextTimer = 0;
	XMFLOAT2 m_StatePos = { 0.0f,0.0f };
	XMFLOAT2 m_AfterStatePos = { 0.0f,0.0f };
	float m_Frame = 0.0f;
	enum StateTextNumber {
		NoText,
		StartText,
		BackText,
	};
};