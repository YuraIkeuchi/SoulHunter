#pragma once
#include "IKESprite.h"
#include "PlayerSkill.h"
#include "Player.h"
#include "Audio.h"
#include "VolumManager.h"
#include "AllArray.h"
#include "CompassPause.h"
#include "LibraPause.h"
#include "DushPause.h"
#include "HealPause.h"
#include <array>   
#include <memory> 
#include <list> // ヘッダファイルインクルード
using namespace std;         //  名前空間指定
//スキルセット画面のクラス
class SkillPause {
public:
	SkillPause();
	void SetPlayerSkill(PlayerSkill* playerskill) { this->playerskill.reset(playerskill); }
	void SetPlayer(Player* player) { this->player.reset(player); }
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

public:
	//getter
	bool GetReturnSkill() { return m_ReturnSkill; }
	//setter
	void SetReturnSkill(bool m_ReturnSkill) { this->m_ReturnSkill = m_ReturnSkill; }
	void SetChangeColorType(int m_ColorChangeType) { this->m_ColorChangeType = m_ColorChangeType; }
private:
	//クラス
	unique_ptr<PlayerSkill> playerskill = nullptr;
	unique_ptr<Player> player = nullptr;
	unique_ptr<CompassPause> compasspause = nullptr;
	unique_ptr<DushPause> dushpause = nullptr;
	unique_ptr<LibraPause> librapause = nullptr;
	unique_ptr<HealPause> healpause = nullptr;
	//スプライト
	unique_ptr<IKESprite> PauseSprite = nullptr;
	unique_ptr<IKESprite> select = nullptr;
	//array<IKESprite*, SkillMax> SkillSprite;
	//static array<XMFLOAT2, SkillMax> SkillPos;
	static XMFLOAT2 m_SkillPos[SkillMax];
	array<unique_ptr<IKESprite>, SkillMax> NoItemSprite;
	array<unique_ptr<IKESprite>, SkillMax> ExplainSprite;
	array<unique_ptr<IKESprite>, SetMax> SetSkillSprite;
	//IKESprite* SetSkillSprite[SetMax];
	//static array<XMFLOAT2, SetMax> SetSkillPos;
	static XMFLOAT2 m_SetSkillPos[SetMax];
	static bool m_SetSkill[SetMax];
	static int m_SkillName[SetMax];

	//static array<bool, SetMax> SetSkill;
	//static array<int, SetMax> SkillName;
	array<XMFLOAT2, SetMax> m_AfterSkillPos;
	int m_SelectNumber = 0;
	int m_SelectDir;
	XMFLOAT2 m_SelectPos = { 0.0f,0.0f };
	enum SelectDir {
		Down,
		Up,
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