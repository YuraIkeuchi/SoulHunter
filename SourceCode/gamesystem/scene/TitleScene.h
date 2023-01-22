#pragma once
#include "BaseScene.h"
#include "TitleObj.h"

/// �^�C�g���V�[��
class TitleScene : public BaseScene {
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
	void PartsMove();//�^�C�g���̕����̓���
	void PartsBirth();//�^�C�g���̕����������т���
private://�����o�ϐ�
	//�X�v���C�g
	unique_ptr<IKESprite> TitleSprite;
	array<unique_ptr<IKESprite>,3> TitlePartsSprite;
	unique_ptr<IKETexture> backtex;
	//Json�ǂݍ��݂̃N���X
	static TitleObj* titleobj;
	//�V�[���J�ڂ̂��߂̂���
	int m_TitleSelect = 0;
	//�^�C�g���̃p�[�c�ɕK�v�Ȃ���
	array<float, 2> m_Angle;
	array<float, 2> m_Angle2;
	array<XMFLOAT2, 3> m_PartsPos;
	array<XMFLOAT2, 3> m_PartsSize;
	enum TitleSelect {
		NewGame,
		LoadGame,
		SelectGame
	};

	//�i�X�ƐF�������яオ�鉉�o
	int m_TitleTimer = 0;
	XMFLOAT4 m_TitleColor = { 1.0f,1.0f,1.0f,0.0 };
	float m_Frame = 0.0f;

	//���C�g�̕ϐ�
	XMFLOAT3 m_LightPos = { 0.0f,0.0f,0.0f };

	static bool m_TitleNew;
};

