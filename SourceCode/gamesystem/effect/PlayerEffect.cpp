#include "PlayerEffect.h"

PlayerEffect::PlayerEffect() {
	
}

void PlayerEffect::CreateEffect(const std::string& newname, XMFLOAT3 pos, int dir) {
	if (newname == "Attack") {
		AttackEffect* newAttackEffect;
		newAttackEffect = new AttackEffect();
		newAttackEffect->Initialize();
		newAttackEffect->SetEffect(pos, dir);
		attackeffects.push_back(newAttackEffect);
	}
	else if (newname == "Damege") {
		PlayerDamageEffect* newDamageEffect;
		newDamageEffect = new PlayerDamageEffect();
		newDamageEffect->Initialize();
		newDamageEffect->DamageEffectSet(pos);
		damageeffects.push_back(newDamageEffect);
	}
	else if (newname == "Wall") {
		WallAttackEffect* newwallEffect;
		newwallEffect = new WallAttackEffect();
		newwallEffect->Initialize();
		newwallEffect->EffectSet(pos,dir);
		walleffects.push_back(newwallEffect);
	}
	else if (newname == "Dush") {
		PlayerDushEffect* newDushEffect;
		newDushEffect = new PlayerDushEffect();
		newDushEffect->Initialize();
		newDushEffect->DushEffectSet(pos);
		dusheffects.push_back(newDushEffect);
	}
	else if (newname == "Heal") {
		PlayerHealEffect* newHealEffect;
		newHealEffect = new PlayerHealEffect();
		newHealEffect->Initialize();
		newHealEffect->SetEffect(pos);
		healeffect.push_back(newHealEffect);
	}
}

void PlayerEffect::Initialize() {

}

void PlayerEffect::Update() {
	//エフェクト関係
	for (AttackEffect* attackeffect : attackeffects) {
		if (attackeffect != nullptr) {
			attackeffect->Update();
		}
	}

	for (WallAttackEffect* walleffect : walleffects) {
		if (walleffect != nullptr) {
			walleffect->Update();
		}
	}

	for (PlayerDushEffect* dusheffect : dusheffects) {
		if (dusheffect != nullptr) {
			dusheffect->Update();
		}
	}

	for (PlayerDamageEffect* damageeffect : damageeffects) {
		if (damageeffect != nullptr) {
			damageeffect->Update();
		}
	}

	for (PlayerHealEffect* healeffect : healeffect) {
		if (healeffect != nullptr) {
			healeffect->Update();
		}
	}
}

void PlayerEffect::Draw() {
	//エフェクトの描画
	for (AttackEffect* attackeffect : attackeffects) {
		if (attackeffect != nullptr) {
			attackeffect->Draw();
		}
	}

	for (WallAttackEffect* walleffect : walleffects) {
		if (walleffect != nullptr) {
			walleffect->Draw();
		}
	}

	for (PlayerDushEffect* dusheffect : dusheffects) {
		if (dusheffect != nullptr) {
			dusheffect->Draw();
		}
	}

	for (PlayerDamageEffect* damageeffect : damageeffects) {
		if (damageeffect != nullptr) {
			damageeffect->Draw();
		}
	}

	for (PlayerHealEffect* healeffect : healeffect) {
		if (healeffect != nullptr) {
			healeffect->Draw();
		}
	}
}