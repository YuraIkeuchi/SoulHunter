#pragma once
#include <map>
#include <string>
#include "IKESprite.h"
#include "IKETexture.h"
#include "ParticleManager.h"
//2D�̓ǂݍ��ݏ���
class ImageManager  final {
private:
	ImageManager() = default;
	~ImageManager() = default;
	ImageManager(const ImageManager& r) = default;
	ImageManager& operator= (const ImageManager& r) = default;

public:
	//�X�v���C�g�̖��O
	enum texName {
		Title = 31,
		TitleParts,
		ModeParts,
		ModeBack,
		ModeExplain,
		BlackFilter,
		PauseBack,
		Pause1,
		PauseParts,
		PauseSkill,
		Option1,
		VolumBar,
		PauseSelect,
		NoItem,
		DushExplain,
		CompassExplain,
		LibraExplain,
		HealExplain,
		JumpExplain,
		Save1,
		LoadText1,
		NowLoad1,
		ChestBack,
		Curtain,
		SkipText,
		IntroText,
		ClearText,
		MiniSkill,
	};
	//�e�N�X�`���̖��O
	enum tex2dName {
		DushEffect,
		AttackEffect,
		ParticleEffect,
		DamageEffect,
		NormalEffect,
		SmokeTex,
		HealEffect,
		HitEffect,
		TutorialTex,
		ChestTex,
		WingEffect,
		LightTex,
		ReadTex,
		OutArea,
	};

	enum particleName {
		Normal,
		Smoke

	};
public:
	static ImageManager* GetIns();		//�擾�p
	static bool load;
	void Load2D();
	void LoadTex2D();
	void LoadParticle();
};

