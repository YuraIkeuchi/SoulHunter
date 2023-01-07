#include "TitleObj.h"
#include "ModelManager.h"
#include "ImageManager.h"
#include "JsonLoader.h"
using namespace DirectX;	
//������
void TitleObj::Initialize() {
	ParticleTex* particletex_ = new ParticleTex();
	particletex_->Initialize();
	particletex.reset(particletex_);

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
void TitleObj::Update() {
	//Json�p
	for (auto& object : objects) {
		object->Update();
	}

	//���̃p�[�e�B�N��
	if (!m_StopParticle) {
		m_ParticleCount++;
		if (m_ParticleCount > 6) {
			m_ParticleCount = 0;
		}
	}
	else {
		m_ParticleCount = 0;
	}

	particletex->SetStartColor({ 1.0f,0.5f,0.0f,0.5f });
	particletex->Update({ 0.0f,23.0f,0.0f }, m_ParticleCount, 6, 4);
	particletex->SetParticleBreak(true);
	particletex->SetParticleBillboard(true);
	particletex->SetStartScale(0.5f);
	particletex->SetAddScale(0.1f);
	
}
//�O�ʕ`��
const void TitleObj::FrontDraw() {
	particletex->Draw();
}
//�w�i�`��
const void TitleObj::BackDraw() {
	//Json�p
	for (auto& object : objects) {
		object->Draw();
	}
}
//���
void TitleObj::Finalize() {

}