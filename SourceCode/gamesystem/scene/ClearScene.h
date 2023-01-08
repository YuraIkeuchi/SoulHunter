#pragma once
#include "BaseScene.h"
#include "ClearObj.h"
#include "VariableCommon.h"
/// �^�C�g���V�[��
class ClearScene : public BaseScene {
public:
	/// ������
	void Initialize(DirectXCommon* dxCommon) override;
	/// �I��
	void Finalize() override;
	/// ���t���[���X�V
	void Update(DirectXCommon* dxCommon) override;
	/// �`��
	void Draw(DirectXCommon* dxCommon) override;
	void ModelDraw(DirectXCommon* dxCommon);
	void GameDraw(DirectXCommon* dxCommon);
	void ImGuiDraw(DirectXCommon* dxCommon);
	void PostImGuiDraw(DirectXCommon* dxCommon);
	void FrontDraw();
	void ChangePostEffect(int PostType);
	//���o
	void Movie();
private://�����o�ϐ�
	//Json�ǂݍ��݂̃N���X
	ClearObj* clearobj = nullptr;
	array<unique_ptr<IKESprite>, 2> CurtainSprite;
	unique_ptr<IKESprite> SkipSprite;
	unique_ptr<IKESprite> ClearSprite;
	//�^�C�}�[
	int m_Timer = 0;
	int m_ResetTimer = 0;
	//�|�X�g�G�t�F�N�g�̒l
	float m_Sepia = 0.0f;
	//�t���[��
	float m_Frame = 0.0f;
	//�F
	XMFLOAT4 m_TextColor = { 1.0f,1.0f,1.0f,0.0f };
	//���W
	XMFLOAT2 m_ClearPos = { 0.0f,900.0f };
	int m_ChangeTimer = 0;
	//���C�g�̕ϐ�
	XMFLOAT3 m_LightPos = { 0.0f,0.0f,0.0f };
};

