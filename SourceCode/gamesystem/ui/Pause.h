#pragma once
#include "IKESprite.h"
#include "SkillPause.h"
#include "MiniMap.h"
#include "Option.h"
#include "Audio.h"
#include "VolumManager.h"
#include "Player.h"
#include "InterEnemy.h"
#include <array>   
#include <memory> 
#include <list> // ヘッダファイルインクルード
using namespace std;         //  名前空間指定
//ポーズメニューのクラス
class Pause {
public:
	Pause();
	void SetPlayer(Player* player) { this->player.reset(player); }
	void SetSkillPause(SkillPause* skillpause) { this->skillpause.reset(skillpause); }
	void SetMiniMap(MiniMap* minimap) { this->minimap.reset(minimap); }
	void SetOption(Option* option) { this->option.reset(option); }
	void Initialize();//初期化
	void Update();//更新
	void Finalize();//解放
	const void Draw();//描画
	void ResetPause();//リセット
	void PartsMove();//スプライトの動き
private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	//getter
	bool GetIsPause() { return m_IsPause; }
	int GetPauseNumber() { return m_PauseNumber; }
	//setter
	void SetIsPause(bool IsPause) { this->m_IsPause = IsPause; }
	void SetPauseNumber(int m_PauseNumber) { this->m_PauseNumber = m_PauseNumber; }
private:
	//定数
	static const int Pause_Max = 3;//ポーズの数
private:
	//継承元のクラス
	unique_ptr<SkillPause> skillpause = nullptr;
	unique_ptr<Option> option = nullptr;
	unique_ptr<MiniMap> minimap = nullptr;
	unique_ptr<Player> player = nullptr;
	//スプライト
	unique_ptr<IKESprite> PauseBack;
	unique_ptr<IKESprite> PauseSprite;
	array<unique_ptr<IKESprite>, Pause_Max> PausePartsSprite;
	//変数
	array<XMFLOAT2, Pause_Max> m_PartsPos;//座標
	array<XMFLOAT2, Pause_Max> m_PartsSize;//大きさ
	//sin波に使うもの
	array<float, Pause_Max> m_Angle;
	array<float, Pause_Max> m_Angle2;
	//色
	XMFLOAT4 m_PauseColor = { 1.0f,1.0f,1.0f,0.0f };
	//透過の動き
	int m_ColorChangeType = 0;
	bool m_IsPause = false;
	bool ColorSubs = false;
	int m_MenuNumber = 0;
	int m_PauseNumber = 0;
	int m_SelectNumber = 0;
	enum PauseNumber {
		NormalPause,
		MiniMap,
		SkillSet,
		Option,
	};
	enum SelectNumber {
		SkillPause,
		OptionPause,
		SelectPause
	};
	enum ChangeNumber {
		No,
		Add,
		Sub
	};

	int m_ReturnTimer = 0;
};