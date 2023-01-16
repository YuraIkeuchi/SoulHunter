#include "ImageManager.h"

ImageManager* ImageManager::GetIns() {
	static ImageManager instans;
	return &instans;
}
//スプライトの読み込み
void ImageManager::Load2D() {
	IKESprite::LoadTexture(Title, L"Resources/2d/sceneback/Title1.png");
	IKESprite::LoadTexture(TitleParts, L"Resources/2d/sceneback/TitleParts.png");
	IKESprite::LoadTexture(BlackFilter, L"Resources/2d/effect/Blackfilter.png");
	IKESprite::LoadTexture(PauseBack, L"Resources/2d/sceneback/PauseBack.png");
	IKESprite::LoadTexture(Pause1, L"Resources/2d/sceneback/PauseMenu.png");
	IKESprite::LoadTexture(PauseParts, L"Resources/2d/sceneback/MenuParts.png");
	IKESprite::LoadTexture(Option1, L"Resources/2d/sceneback/PauseOption1.png");
	IKESprite::LoadTexture(VolumBar, L"Resources/2d/ui/VolumBar.png");
	IKESprite::LoadTexture(PauseSkill, L"Resources/2d/sceneback/PauseSkill.png");
	IKESprite::LoadTexture(PauseSelect, L"Resources/2d/ui/Select.png");
	IKESprite::LoadTexture(NoItem, L"Resources/2d/effect/NoItem.png");
	IKESprite::LoadTexture(LibraExplain, L"Resources/2d/ui/Libraexplain.png");
	IKESprite::LoadTexture(DushExplain, L"Resources/2d/ui/Dushexplain.png");
	IKESprite::LoadTexture(CompassExplain, L"Resources/2d/ui/Compassexplain.png");
	IKESprite::LoadTexture(HealExplain, L"Resources/2d/ui/Healexplain.png");
	IKESprite::LoadTexture(Save1, L"Resources/2d/sceneback/SaveText.png");
	IKESprite::LoadTexture(LoadText1, L"Resources/2d/sceneback/LoadText1.png");
	IKESprite::LoadTexture(NowLoad1, L"Resources/2d/sceneback/NowLoading1.png");
	IKESprite::LoadTexture(ChestBack, L"Resources/2d/SkillExplain/ExplainBack.png");
	IKESprite::LoadTexture(Curtain, L"Resources/2d/sceneback/Curtain.png");
	IKESprite::LoadTexture(SkipText, L"Resources/2d/sceneback/SkipText.png");
	IKESprite::LoadTexture(IntroText, L"Resources/2d/sceneback/IntroText.png");
	IKESprite::LoadTexture(ClearText, L"Resources/2d/sceneback/ClearText.png");
}

//テクスチャの読み込み
void ImageManager::LoadTex2D() {
	IKETexture::LoadTexture(DushEffect, L"Resources/2d/effect/DushEffect.png");
	IKETexture::LoadTexture(AttackEffect, L"Resources/2d/effect/Attack.png");
	IKETexture::LoadTexture(ParticleEffect, L"Resources/2d/effect/effect1.png");
	IKETexture::LoadTexture(DamageEffect, L"Resources/2d/effect/effect2.png");
	IKETexture::LoadTexture(NormalEffect, L"Resources/2d/effect/NormalEffect.png");
	IKETexture::LoadTexture(SmokeTex, L"Resources/2d/effect/hootEffect.png");
	IKETexture::LoadTexture(HealEffect, L"Resources/2d/effect/HealEffect.png");
	IKETexture::LoadTexture(HitEffect, L"Resources/2d/effect/HitEffect3.png");
	IKETexture::LoadTexture(TutorialTex, L"Resources/2d/text/textpoint.png");
	IKETexture::LoadTexture(ChestTex, L"Resources/2d/text/textpoint.png");
	IKETexture::LoadTexture(WingEffect, L"Resources/2d/effect/Wing3.png");
	IKETexture::LoadTexture(LightTex, L"Resources/2d/sceneback/BackLight.png");
	IKETexture::LoadTexture(ReadTex, L"Resources/2d/text/textpointread.png");
	IKETexture::LoadTexture(OutArea, L"Resources/2d/effect/OutArea.png");
}
