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
#include <list> // �w�b�_�t�@�C���C���N���[�h
using namespace std;         //  ���O��Ԏw��
//�|�[�Y���j���[�̃N���X
class Pause {
public:
	Pause();
	void SetPlayer(Player* player) { this->player.reset(player); }
	void SetSkillPause(SkillPause* skillpause) { this->skillpause.reset(skillpause); }
	void SetMiniMap(MiniMap* minimap) { this->minimap.reset(minimap); }
	void SetOption(Option* option) { this->option.reset(option); }
	void Initialize();//������
	void Update();//�X�V
	void Finalize();//���
	const void Draw();//�`��
	void ResetPause();//���Z�b�g
	void PartsMove();//�X�v���C�g�̓���
private:
	// DirectX::���ȗ�
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
	//�萔
	static const int Pause_Max = 3;//�|�[�Y�̐�
private:
	//�p�����̃N���X
	unique_ptr<SkillPause> skillpause = nullptr;
	unique_ptr<Option> option = nullptr;
	unique_ptr<MiniMap> minimap = nullptr;
	unique_ptr<Player> player = nullptr;
	//�X�v���C�g
	unique_ptr<IKESprite> PauseBack;
	unique_ptr<IKESprite> PauseSprite;
	array<unique_ptr<IKESprite>, Pause_Max> PausePartsSprite;
	//�ϐ�
	array<XMFLOAT2, Pause_Max> m_PartsPos;//���W
	array<XMFLOAT2, Pause_Max> m_PartsSize;//�傫��
	//sin�g�Ɏg������
	array<float, Pause_Max> m_Angle;
	array<float, Pause_Max> m_Angle2;
	//�F
	XMFLOAT4 m_PauseColor = { 1.0f,1.0f,1.0f,0.0f };
	//���߂̓���
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