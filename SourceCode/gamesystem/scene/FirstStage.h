#pragma once
#include "BaseScene.h"
#include <array>       // �w�b�_�t�@�C���C���N���[�h
#include "BossStagObj.h"
#include "BossSceneChange.h"
#include "PlayerEffect.h"
#include "PlayerSoul.h"
using namespace std;         //  ���O��Ԏw��

//�Q�[���v���C�V�[��
class FirstStage : public BaseScene
{
private://�����o�ϐ�

public:
	//������
	void Initialize(DirectXCommon* dxCommon) override;
	//�X�V
	void Update(DirectXCommon* dxCommon) override;
	//�`��
	void Draw(DirectXCommon* dxCommon) override;
	void PlaySceneInitialize();//�v���C�V�[���݂̂̏�����
	//�J��
	void Finalize() override;
	void ModelDraw(DirectXCommon* dxCommon);
	void FrontDraw(DirectXCommon* dxCommon);
	void BackDraw(DirectXCommon* dxCommon);
	void NormalDraw(DirectXCommon* dxCommon);//���ʂ̕`��
	void BossAppDraw(DirectXCommon* dxCommon);//�{�X�o��V�[���̕`��
	void BossEndDraw(DirectXCommon* dxCommon);//�{�X�o��V�[���̕`��
	void NormalUpdate();//���ʂ̍X�V
	void BossAppUpdate();//�{�X�o��V�[���̍X�V
	void BossEndUpdate();//�{�X�I���V�[���̍X�V
	void ImGuiDraw(DirectXCommon* dxCommon);
	
	//�v�f�S�폜
	void AllDelete();
	//�}�b�v�̏�����
	void MapInitialize();

	//�X�V�����֐��킯
	//�e�N���X�̍X�V
	void AllUpdate();
	//���C�g�̐ݒu
	void LightSet();
	//�{�X�����̍X�V
	void BossRoomUpdate();
	//�V�[���`�F���W�Ȃ�
	void ChangeUpdate();
	//�S�[������
	void GoalHit();
private:
	//�{�X�o��V�[���̃N���X
	unique_ptr<BossStagObj> bossstagobj = nullptr;
	//�{�X�o��V�[���̉�ʈÓ]
	unique_ptr<BossSceneChange> bossscenechange = nullptr;
	//���N���X
	PlayerSoul* normalplayersoul[Soul_Max][Enemy_Max];
	PlayerSoul* boundplayersoul[Soul_Max][Enemy_Max];
	PlayerSoul* birdplayersoul[Soul_Max][Enemy_Max];
	PlayerEffect* playereffect = nullptr;
};