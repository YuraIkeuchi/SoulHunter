#include "BossAppObj.h"
#include "ModelManager.h"
#include "imgui.h"
#include "JsonLoader.h"
using namespace DirectX;
//������
void BossAppObj::Initialize() {
	//�X�e�[�W�w�i
	modelskydome = ModelManager::GetInstance()->GetModel(ModelManager::Back);
	IKEObject3d* objskydome_ = new IKEObject3d();
	objskydome_ = IKEObject3d::Create();
	objskydome_->SetModel(modelskydome);
	objskydome_->SetPosition({ 0, 0, -30 });
	objskydome_->SetScale({ 4.0f,4.0f,4.0f });
	objskydome.reset(objskydome_);

	jsonData = JsonLoader::LoadFile("Title");

	//���X�|�[���ʒu
	for (auto& objectData : jsonData->objects) {
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

			newObject->SetTiling(30.0f);
			// �z��ɓo�^
			objects.push_back(newObject);
		}
	}
}
//�X�V
void BossAppObj::Update() {
	//pos = player->GetPosition();
	//�{�X�o��t���O����������^�C�}�[������
	if (m_AppStart && !m_EndApp) {
		//�o��̊Ԃ�true
		m_App = true;
		m_AppTimer++;
		//���t���[���Ńt���O�I��
		if (m_AppTimer == 400) {
			m_App = false;
			m_AppStart = false;
			m_EndApp = true;
		}
	}
	
	//Json�p
	for (auto& object : objects) {
		object->Update();
	}

}
//�O�ʕ`��
const void BossAppObj::FrontDraw() {
}
//�w�i�`��
const void BossAppObj::BackDraw() {
	ImGui::Begin("BossApp");
	ImGui::Text("m_App:%d", m_App);
	ImGui::Text("m_AppTimer:%d", m_AppTimer);
	ImGui::Text("m_End:%d", m_EndApp);
	ImGui::Text("m_AppStart:%d", m_AppStart);
	ImGui::End();
	//Json�p
	for (auto& object : objects) {
		object->Draw();
	}
	//objskydome->Draw();
}
//���
void BossAppObj::Finalize() {

}