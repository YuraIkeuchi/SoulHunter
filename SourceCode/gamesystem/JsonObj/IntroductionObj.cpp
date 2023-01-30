#include "IntroductionObj.h"
#include "ModelManager.h"
#include "JsonLoader.h"
using namespace DirectX;
//������
void IntroductionObj::Initialize() {
	//�X�e�[�W�w�i
	modelskydome = ModelManager::GetInstance()->GetModel(ModelManager::Skydome);
	IKEObject3d* objskydome_ = new IKEObject3d();
	objskydome_ = IKEObject3d::Create();
	objskydome_->SetModel(modelskydome);
	objskydome_->SetPosition({ 0.0f, 0.0f, 0.0f });
	objskydome_->SetRotation({ 0.0f, 90.0f, 0.0f });
	objskydome_->SetScale({ 8.0f,8.0f,8.0f });
	objskydome.reset(objskydome_);

	//Json
	jsonData = JsonLoader::LoadFile("Introduction");

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

			newObject->SetTiling(20.0f);
			// �z��ɓo�^
			objects.push_back(newObject);
		}
		//�t�H�O
		if (objectData.GimmickName == "FogGimmick") {
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

			newObject->SetTiling(20.0f);
			newObject->SetFog(true);
			// �z��ɓo�^
			fogobjects.push_back(newObject);
		}
		//�n��
		if (objectData.GimmickName == "Ground") {
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

			newObject->SetTiling(20.0f);
			// �z��ɓo�^
			groundobjects.push_back(newObject);
		}
	}
}
//�X�V
void IntroductionObj::Update(int Timer) {

	if (Timer >= 120) {
		m_OffSet = 0.0f;
	}
	else {
		m_OffSet = -0.01f;
	}
	objskydome->Update();
	objskydome->SetAddOffset(0.0005f);
	//Json�p
	for (auto& object : objects) {
		object->Update();
	}

	for (auto& object : fogobjects) {
		object->Update();
	}

	for (auto& object : groundobjects) {
		object->Update();
		object->SetAddOffset(m_OffSet);
	}
}
//�O�ʕ`��
const void IntroductionObj::FrontDraw() {
	
}
//�w�i�`��
const void IntroductionObj::BackDraw() {
	objskydome->Draw();
	//objskydome->Draw();
	//Json�p
	for (auto& object : objects) {
		object->Draw();
	}
	for (auto& object : fogobjects) {
		object->Draw();
	}
	for (auto& object : groundobjects) {
		object->Draw();
	}
}
//���
void IntroductionObj::Finalize() {

}