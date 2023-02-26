#include "ClearScene.h"

//������
void ClearScene::Initialize(DirectXCommon* dxCommon) {
	//���ʂ̏�����
	BaseInitialize(dxCommon);
	actor = new ClearSceneActor();
	actor->Initialize(dxCommon, camera, lightGroup);
}
//�X�V
void ClearScene::Update(DirectXCommon* dxCommon) {
	lightGroup->Update();
	actor->Update(dxCommon, camera, lightGroup);
}
//�`��
void ClearScene::Draw(DirectXCommon* dxCommon) {
	//�|�X�g�G�t�F�N�g�������邩
	actor->Draw(dxCommon);
}

//���
void ClearScene::Finalize() {
	actor->Finalize();
}
