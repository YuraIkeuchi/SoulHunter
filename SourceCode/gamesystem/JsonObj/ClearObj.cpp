#include "ClearObj.h"
#include "ModelManager.h"
#include "JsonLoader.h"
#include "imgui.h"
using namespace DirectX;
ClearObj::ClearObj() {
	modeltorch = ModelManager::GetInstance()->GetModel(ModelManager::BackTorch);
}
//������
void ClearObj::Initialize() {
	
	//Json
	jsonData = JsonLoader::LoadFile("Clear");

	//Json�ǂݍ��݂�OBJ
	for (auto& objectData : jsonData->objects) {
		//���ʂ�OBJ
		if (objectData.GimmickName == "NoGimmick") {
			// �t�@�C��������o�^�ς݃��f��������
			IKEModel* model = IKEModel::LoadFromOBJ(objectData.fileName, true);
			decltype(models)::iterator it = models.find(objectData.fileName);
			if (it != models.end()) {
				model = it->second;
			}

			// ���f�����w�肵��3D�I�u�W�F�N�g�𐶐�
			IKEObject3d* newObject = IKEObject3d::Create();
			newObject->SetModel(model);
			XMFLOAT3 Startpos;

			// ���W
			DirectX::XMStoreFloat3(&Startpos, objectData.translation);

			newObject->SetPosition(Startpos);

			// ��]�p
			DirectX::XMFLOAT3 rot;
			DirectX::XMStoreFloat3(&rot, objectData.rotation);
			newObject->SetRotation(rot);

			// ���W
			DirectX::XMFLOAT3 scale;
			DirectX::XMStoreFloat3(&scale, objectData.scaling);
			newObject->SetScale(scale);

			newObject->SetTiling(50.0f);
			newObject->SetFog(true);
			// �z��ɓo�^
			objects.push_back(newObject);
		}
	}

	IKEObject3d* objtorch_ = new IKEObject3d();
	objtorch_ = IKEObject3d::Create();
	objtorch_->SetModel(modeltorch);
	objtorch_->SetScale({ 3.5f,3.5f,3.5f });
	objtorch.reset(objtorch_);
}
//�X�V
void ClearObj::Update(int Timer) {

	//Json�p
	for (auto& object : objects) {
		object->Update();
	}

	objtorch->SetPosition(m_TorchPos);
	objtorch->Update();
}
//�O�ʕ`��
const void ClearObj::FrontDraw() {
	ImGui::Begin("torch");
	ImGui::Text("torchX:%f", m_TorchPos.x);
	ImGui::Text("torchY:%f", m_TorchPos.y);
	ImGui::Text("torchZ:%f", m_TorchPos.z);
	ImGui::End();
}
//�w�i�`��
const void ClearObj::BackDraw() {	//Json�p
	for (auto& object : objects) {
		object->Draw();
	}

	objtorch->Draw();
}
//���
void ClearObj::Finalize() {

}