#pragma once
#include "BaseActor.h"
#include "IKESprite.h"
#include "IntroductionObj.h"
#include "IntroPlayer.h"
/// �^�C�g���V�[��
class IntroductionSceneActor : public BaseActor {
public:
	/// ������
	void Initialize(DirectXCommon* dxCommon, DebugCamera* camera, LightGroup* lightgroup) override;
	/// �I��
	void Finalize() override;
	/// ���t���[���X�V
	void Update(DirectXCommon* dxCommon, DebugCamera* camera, LightGroup* lightgroup) override;
	/// �`��
	void Draw(DirectXCommon* dxCommon) override;
	void ModelDraw(DirectXCommon* dxCommon);
	void GameDraw(DirectXCommon* dxCommon);
	void ImGuiDraw(DirectXCommon* dxCommon);
	void FrontDraw();
	//���o
	void Movie();
private://�����o�ϐ�
	unique_ptr<IntroPlayer> introplayer = nullptr;
	//Json�ǂݍ��݂̃N���X
	static IntroductionObj* Introductionobj;
	array<unique_ptr<IKESprite>, 2> CurtainSprite;
	unique_ptr<IKESprite> SkipSprite;
	unique_ptr<IKESprite> IntroSprite;
	//�^�C�}�[
	int m_Timer = 0;
	//�|�X�g�G�t�F�N�g�̒l
	float m_Sepia = 0.0f;
	//�t���[��
	float m_Frame = 0.0f;
	//�F
	XMFLOAT4 m_TextColor = { 1.0f,1.0f,1.0f,0.0f };
	int m_ChangeTimer = 0;

	static bool m_IntroNew;
};