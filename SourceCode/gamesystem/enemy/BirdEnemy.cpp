#include "BirdEnemy.h"
#include "ModelManager.h"
#include "Collision.h"
using namespace DirectX;

BirdEnemy::BirdEnemy() {
	IKESprite::LoadTexture(27, L"Resources/2d/sceneback/MiniMapEnemy.png");
	IKESprite* MiniEnemySprite_;
	MiniEnemySprite_ = IKESprite::Create(27, { 0.0f,0.0f });
	MiniEnemySprite_->SetAnchorPoint({ 0.5f,0.5f });
	MiniEnemySprite.reset(MiniEnemySprite_);

	m_fbxModel = ModelManager::GetInstance()->GetFBXModel(ModelManager::BirdEnemy);
}
//������
bool BirdEnemy::Initialize() {
	m_Color = { 1.0f,1.0f,1.0f,1.0f };
	m_ChangeColor = true;
	//FBX
	IKEFBXObject3d* m_fbxObject_ = new IKEFBXObject3d();
	m_fbxObject_->Initialize();
	m_fbxObject_->SetModel(m_fbxModel);
	m_Position = { 110.0f,-90.0,0.0f };
	m_Rotation = { 0.0f,180.0f,0.0f };
	m_Scale = { 0.01f,0.01f,0.01f };
	m_fbxObject_->SetScale(m_Scale);
	m_fbxObject_->SetPosition(m_Position);
	m_fbxObject_->SetRotation(m_Rotation);
	m_fbxObject_->LoadAnimation();
	m_fbxObject_->PlayAnimation(0);
	m_fbxObject.reset(m_fbxObject_);
	m_Jump = true;
	//�G�̎��
	m_EnemyType = Bird;
	//X����
	m_Radius.x = 1.4f * 2.7f;
	//������
	m_Radius.y = 0.6f * 2.7f;
	m_HP = 5;
	m_fbxObject->Update(true, 1, m_AnimationStop);
	return true;
}
//�X�V
void BirdEnemy::Action() {
	m_OldPos = m_Position;
	
	if (m_Alive && UpdateCollide()) {
	
		//�����蔻��i
		PlayerCollide();
		m_fbxObject->Update(true, 1, m_AnimationStop);
		Fbx_SetParam();
		//�G�t�F�N�g�֌W
		for (EnemyEffect* enemyeffect : enemyeffects) {
			if (enemyeffect != nullptr) {
				enemyeffect->Update(m_Position, m_Effect);
			}
		}
		//�G�t�F�N�g�֌W
		for (BirdEnemyEffect* birdenemyeffect : birdenemyeffects) {
			if (birdenemyeffect != nullptr) {
				birdenemyeffect->Update(m_Position);
			}
		}
	}
	//�}�b�v�ɂ��������Ƃ���]���߂�
	if (block->BirdEnemyMapCollideCommon(m_Position, m_Radius, m_BirdTouchWall, m_OldPos, m_Attack)) {
		m_Rotation = { 0.0f,180.0f,0.0f };
	}

	//����
	Move();
	//�_���[�W���̓���
	DamageAct();
	//���񂾂Ƃ��̋���
	DeathMove();
	//�p�[�e�B�N������
	BirthParticle();
	DeathBirthParticle();
	//���b�N�I��
	BirdLockOn();
	//�G�t�F�N�g�֌W
	ArgEffect();
	//���֌W
	ArgSoul();

	//������
	VanishEnemy();
	//�G�t�F�N�g����
	BirdArgment();
	//�~�j�}�b�v�ɕ\��������
	MapEnemy();
}
//�`��
void BirdEnemy::Draw(DirectXCommon* dxCommon) {
	if (m_Alive && DrawCollide()) {
		Fbx_Draw(dxCommon);
		//�G�t�F�N�g�֌W
		for (EnemyEffect* enemyeffect : enemyeffects) {
			if (enemyeffect != nullptr) {
				enemyeffect->Draw();
			}
		}

		//�G�t�F�N�g�֌W
		for (BirdEnemyEffect* birdenemyeffect : birdenemyeffects) {
			if (birdenemyeffect != nullptr) {
				birdenemyeffect->Draw();
			}
		}
	}
}
//�|�[�Y�J�����Ƃ��̓L�����������Ȃ�
void BirdEnemy::Pause() {
	//�~�j�}�b�v�ɕ\��������
	MapEnemy();
	Fbx_SetParam();
	//m_fbxObject->StopAnimation();
	m_fbxObject->Update(true, 1, m_AnimationStop);
}
//�v���C���[�����b�N�I������
bool BirdEnemy::BirdLockOn() {
	XMFLOAT3 m_PlayerPos = player->GetPosition();
	//�����u���b�N��ɂ��ċ������߂������烍�b�N�I��
	m_DistanceY = m_Position.y - m_PlayerPos.y;
	if (Collision::CircleCollision(m_Position.x, m_Position.y, 15.0f, m_PlayerPos.x, m_PlayerPos.y, 15.0f) && (m_HP > 0)) {

		m_Lock = true;
		return true;
	}
	else {
		m_Lock = false;
		return false;
	}
	return true;
}
//�ړ�
void BirdEnemy::Move() {
	//�͈͓��ɓ����Ĉ�莞�ԗ��Ɠːi����
	if (!m_Attack) {
		if (m_Lock) {
			m_LockTimer++;
		}
		else {
			m_LockTimer = 0;
		}

		if (m_LockTimer >= 20.0f) {
			if (m_BirdTouchWall == Down) {
				m_Position.y += 0.02f;
			}
			else if (m_BirdTouchWall == Up) {
				m_Position.y -= 0.02f;
			}
			else {
				m_Position.y += 0.02f;
			}
		}
		if (m_LockTimer == 150) {
			double l_sb, l_sbx, l_sby;
			if (!m_Attack) {
				l_sbx = player->GetPosition().x - m_Position.x;
				l_sby = player->GetPosition().y - m_Position.y;

				l_sb = sqrt(l_sbx * l_sbx + l_sby * l_sby);
				m_speedX = l_sbx / l_sb * 0.5;
				m_speedY = l_sby / l_sb * 0.5;
				if (player->GetPosition().x > m_Position.x) {
					m_Rotation.y = 90.0f;
				}
				else {
					m_Rotation.y = 270.0f;
				}
				m_Attack = true;
				m_LockTimer = 0;
			}
		}
	}
	else {

		//�v���C���[�ɃX�s�[�h���Z
		m_Position.x += (float)m_speedX;
		m_Position.y += (float)m_speedY;
	}
}
//���񂾂Ƃ����˂�
void BirdEnemy::DeathMove() {
	if (m_DeathMotion && m_Jump) {
		m_AddPower = 0.5f;
		m_Jump = false;
		m_DeathMotion = false;
		m_BirdTouchWall = No;
	}

	if (m_BirdTouchWall != Down) {
		if (m_HP == 0 && m_AddPower >= -3.0f) {
			m_Rotation.y += 20.0f;
			m_AddPower -= m_Gravity;
			m_Position.y += m_AddPower;
		}
	}
	else {
		m_AddPower = 0.0f;
	}
}
//���
void BirdEnemy::Finalize() {
	//enemyeffects.pop_back();
}

void BirdEnemy::MapDraw(XMFLOAT4 Color) {
	MiniEnemySprite->SetColor(Color);
	IKESprite::PreDraw();
	if (m_EnemyPosition.x != 0.0f && m_EnemyPosition.y != 0.0f && m_Alive) {
		MiniEnemySprite->Draw();
	}
}

//�H�G�t�F�N�g����
void BirdEnemy::BirdArgment() {
	if (m_BirdEffectArgment) {
		BirdEnemyEffect* newBirdEnemyEffect;
		newBirdEnemyEffect = new BirdEnemyEffect();
		newBirdEnemyEffect->Initialize();
		birdenemyeffects.push_back(newBirdEnemyEffect);
		m_BirdEffectArgment = false;
	}
}
void BirdEnemy::ImGuiDraw() {
	ImGui::Begin("Bird");
	ImGui::Text("X:%f", m_Position.x);
	ImGui::End();
}