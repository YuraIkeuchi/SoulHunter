#pragma once
//���ʂ̕ϐ��͂܂Ƃ߂�(��Ƀ}�W�b�N�i���o�[)
const float m_ColorMax = 1.0f;//���ߓx�̍ő�
const float m_ColorMin = 0.0f;//���ߓx�̍ŏ�

//�t���[���̍ő�ƍŏ�(�C�[�W���O�̂��߂̂��)
const float m_FrameMax = 1.0f;
const float m_FrameMin = 0.0f;

//�X�e�[�W�i���o�[
enum StageNumber {
	Map1,
	Map2,
	Map3,
	Map4,
	Map5,
	Map6,
	BossMap,
	TutoRial,
};
//�U����H���������
enum HitDir {
	HitRight,
	HitLeft,
};
