#include "LoadScene.h"

//������
void LoadScene::Initialize(DirectXCommon* dxCommon) {
	//���ʂ̏�����
	BaseInitialize(dxCommon);
	actor = new LoadSceneActor();
	actor->Initialize(dxCommon,camera,lightGroup);
}
//�X�V
void LoadScene::Update(DirectXCommon* dxCommon) {
	lightGroup->Update();
	actor->Update(dxCommon, camera, lightGroup);
}
//�`��
void LoadScene::Draw(DirectXCommon* dxCommon) {
	//�|�X�g�G�t�F�N�g�������邩
	actor->Draw(dxCommon);
}

//���
void LoadScene::Finalize() {
	actor->Finalize();
}
