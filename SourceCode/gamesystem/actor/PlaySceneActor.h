#pragma once
#include "BaseActor.h"
#include "IKESprite.h"
#include "BossSceneChange.h"
#include "BossStagObj.h"

/// �^�C�g���V�[��
class PlaySceneActor : public BaseActor {
public:
	/// ������
	void Initialize(DirectXCommon* dxCommon, DebugCamera* camera, LightGroup* lightgroup) override;
	/// �I��
	void Finalize() override;
	/// ���t���[���X�V
	void Update(DirectXCommon* dxCommon, DebugCamera* camera, LightGroup* lightgroup) override;
	/// �`��
	void Draw(DirectXCommon* dxCommon) override;
	void PlaySceneInitialize();//�v���C�V�[���݂̂̏�����
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
	void MapInitialize(LightGroup* lightgroup);

	//�X�V�����֐��킯
	//�e�N���X�̍X�V
	void AllUpdate(DebugCamera* camera);
	//���C�g�̐ݒu
	void LightSet(LightGroup* lightgroup);
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

};