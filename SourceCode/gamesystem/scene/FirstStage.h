#pragma once
#include "BaseScene.h"
#include "PlaySceneActor.h"
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
	//�J��
	void Finalize() override;
	
};