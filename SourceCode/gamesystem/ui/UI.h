#pragma once
#include"IKESprite.h"
#include"Player.h"
#include "InterBoss.h"
#include "AllArray.h"
#include "PlayerSkill.h"
//UI�̃N���X
class UI {
public:
	void SetPlayerSkill(PlayerSkill* playerskill) { this->playerskill.reset(playerskill); }
	UI(Player* player = nullptr, InterBoss* boss = nullptr);
	void Update(InterBoss* boss = nullptr);
	void Finalize();
	const void Draw();

private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
private:
	unique_ptr<Player> player = nullptr;
	unique_ptr<PlayerSkill> playerskill = nullptr;
	unique_ptr<InterBoss> interboss = nullptr;
	array<unique_ptr<IKESprite>,HP_Max> PlayerHpSprite;//�v���C���[��HP
	unique_ptr<IKESprite> BossHpSprite;//�{�X��HP
	array<unique_ptr<IKESprite>, 72> SoulSprite;//�v���C���[��MP
	unique_ptr<IKESprite> SoulGageSprite;//�v���C���[�̃X�^�~�i�̘g
	array<unique_ptr<IKESprite>, WingUI_Max> WingUiTex;
	//�ϐ�
	int m_HP = 0;
	float m_Soul = 0.0f;
	float m_BossHP = 0.0f;
	int m_JumpCount = 0;
	float m_AddPower = 0.0f;
	float m_DrawSoul = 0.0f;
	XMFLOAT3 m_JumpUiPos = {0.0f,0.0f,0.0f};
	//UI�̃T�C�Y
	XMFLOAT2 m_HPSize = { 0.0f,0.0f };
	XMFLOAT2 m_SoulSize = { 0.0f,0.0f };
	XMFLOAT2 m_AfterSoulSize = { 0.0f,0.0f };
	XMFLOAT2 m_BossHPSize = { 0.0f,0.0f };
	XMFLOAT2 m_AfterBossHPSize = { 0.0f,0.0f };
	//�F
	XMFLOAT4 m_HPColor[HP_Max];
	float m_CutWidth = 72.0f;
private:
};