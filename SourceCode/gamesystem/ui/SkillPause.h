#pragma once
#include "IKESprite.h"
#include "GamePlayer.h"
#include "CompassPause.h"
#include "LibraPause.h"
#include "DushPause.h"
#include "HealPause.h"
#include "JumpPause.h"
#include <array>   
#include <memory> 
using namespace std;         //  名前空間指定
//スキルセット画面のクラス
class SkillPause {
public:
	SkillPause();
	void SetPlayer(GamePlayer* player) { this->player.reset(player); }
	void Initialize();//初期化
	void InitPos();//最初の位置
	void Update();//更新
	void Finalize();
	const void Draw();//描画
	void ResetSkillPause();//リセット
	void SelectSkill();//スキル選択
private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
private:
	static const int Skill_Max = 5;//スキルの数

public:
	//getter
	bool GetReturnSkill() { return m_ReturnSkill; }
	//setter
	void SetReturnSkill(bool m_ReturnSkill) { this->m_ReturnSkill = m_ReturnSkill; }
	void SetChangeColorType(int m_ColorChangeType) { this->m_ColorChangeType = m_ColorChangeType; }
private:
	//クラス
	unique_ptr<GamePlayer> player = nullptr;
	unique_ptr<CompassPause> compasspause = nullptr;
	unique_ptr<DushPause> dushpause = nullptr;
	unique_ptr<LibraPause> librapause = nullptr;
	unique_ptr<HealPause> healpause = nullptr;
	unique_ptr<JumpPause> jumppause = nullptr;
	//スプライト
	unique_ptr<IKESprite> PauseSprite = nullptr;
	unique_ptr<IKESprite> select = nullptr;
	array<unique_ptr<IKESprite>, Skill_Max> NoItemSprite;
	array<unique_ptr<IKESprite>, Skill_Max> ExplainSprite;
	//変数
	int m_SelectHeight = 0;
	int m_SelectWeight = 0;
	int m_SetNumber = 0;
	XMFLOAT2 m_SelectPos = { 0.0f,0.0f };
	enum SelectHeight {
		Up,
		Down,
	};

	enum SelectWight {
		LeftSide,
		CenterSide,
		RightSide,
	};

	enum SkillName {
		None,
		Libra,
		Dush,
		Compass,
		Heal
	};
	int SetCount = 0;
	bool m_ReturnSkill = false;
	XMFLOAT4 m_SkillColor = { 1.0f,1.0f,1.0f,0.0f };
	int m_ColorChangeType = 0;
	enum ChangeType {
		No,
		Add,
		Sub,
	};
};