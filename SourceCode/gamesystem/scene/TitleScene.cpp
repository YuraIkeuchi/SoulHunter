#include "TitleScene.h"

//������
void TitleScene::Initialize(DirectXCommon* dxCommon) {
	//���ʂ̏�����
	BaseInitialize(dxCommon);
	actor = new TitleSceneActor();
	actor->Initialize(dxCommon, camera, lightGroup);
}
//�X�V
void TitleScene::Update(DirectXCommon* dxCommon) {
	lightGroup->Update();
	actor->Update(dxCommon, camera, lightGroup);
}
//�`��
void TitleScene::Draw(DirectXCommon* dxCommon) {
	//�|�X�g�G�t�F�N�g�������邩
	actor->Draw(dxCommon);
}

//���
void TitleScene::Finalize() {
	actor->Finalize();
}
