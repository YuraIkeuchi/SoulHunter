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
	void SelectGameMode();//�Q�[���⃂�[�h��I��
	void TitleMove();//�^�C�g���̕����̓���
	void ModeMove();//���[�h�̕����̓���
	void ColorChange();//���[�h�ς���ۂ̐F�̕ύX
private:
	static const int TITLE_MAX = 3;//�^�C�g���p�[�c�̍ő吔
	static const int MODE_MAX = 3;//���[�h�p�[�c�̍ő吔
	static const int EXPLAIN_MAX = 3;//�������̍ő吔
private://�����o�ϐ�
	//�X�v���C�g
	unique_ptr<IKESprite> TitleSprite;
	unique_ptr<IKESprite> ModeSprite;
	array<unique_ptr<IKESprite>, TITLE_MAX> TitlePartsSprite;
	array<unique_ptr<IKESprite>, MODE_MAX> ModePartsSprite;
	array<unique_ptr<IKESprite>, EXPLAIN_MAX> ModeEplainSprite;
	unique_ptr<IKETexture> backtex;
	//Json�ǂݍ��݂̃N���X
	static TitleObj* titleobj;
	//�V�[���J�ڂ̂��߂̂���
	int m_TitleSelect = 0;
	int m_ModeSelect = 0;
	//�^�C�g���̃p�[�c�ɕK�v�Ȃ���
	array<float, 3> m_Angle;
	array<float, 3> m_Angle2;
	array<XMFLOAT2, TITLE_MAX> m_PartsPos;
	array<XMFLOAT2, TITLE_MAX> m_PartsSize;
	enum TitleSelect {
		NewGame,
		LoadGame,
		SelectGame
	};

	//���[�h�Z���N�g�ɕK�v�Ȃ���
	array<XMFLOAT2, TITLE_MAX> m_ModePartsPos;
	array<XMFLOAT2, TITLE_MAX> m_ModePartsSize;

	array<XMFLOAT2, EXPLAIN_MAX> m_ExplainSize;
	enum ModeSelect {
		EasyMode,
		NormalMode,
		SelectMode
	};

	//�i�X�ƐF�������яオ�鉉�o
	XMFLOAT4 m_TitleColor = { 1.0f,1.0f,1.0f,1.0 };
	XMFLOAT4 m_ModeColor = { 1.0f,1.0f,1.0f,0.0 };

	//�C�[�W���O�̂���
	float m_AfterTitleAlpha = 0.0f;
	float m_AfterModeAlpha = 0.0f;
	bool m_ModeChange = false;
	float m_Frame = 0.0f;

	//���C�g�̕ϐ�
	XMFLOAT3 m_LightPos = { 0.0f,0.0f,0.0f };

	static bool m_TitleNew;

	int m_SelectType = 0;
	//�I�����Ă������
	enum SelectType {
		Game,
		Mode,
	};
};

