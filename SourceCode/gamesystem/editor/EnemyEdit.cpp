#include "EnemyEdit.h"
//’Êí‚Ì“G‚Ì¶¬
void EnemyEdit::NormalEnemyArgment(std::vector<InterEnemy*>& enemy, Player* player, PlayerBullet* playerbullet,
	PlayerEffect* playereffect, Block* block, HitStop* hitstop){
	InterEnemy* newEnemy;
	newEnemy = new Enemy();
	newEnemy->Initialize();
	newEnemy->SetPlayer(player);
	newEnemy->SetBlock(block);
	newEnemy->SetHitStop(hitstop);
	newEnemy->SetPlayerBullet(playerbullet);
	newEnemy->SetPlayerEffect(playereffect);
	newEnemy->SetPosition(player->GetPosition());
	newEnemy->SetStartPos(player->GetPosition());
	enemy.push_back(newEnemy);
}
//™‚Ì“G‚Ì¶¬
void EnemyEdit::ThornEnemyArgment(std::vector<InterEnemy*>& enemy, Player* player, PlayerBullet* playerbullet,
	PlayerEffect* playereffect, HitStop* hitstop) {
	InterEnemy* newThornEnemy;
	newThornEnemy = new ThornEnemy();
	newThornEnemy->Initialize();
	newThornEnemy->SetPlayer(player);
	newThornEnemy->SetHitStop(hitstop);
	newThornEnemy->SetPlayerEffect(playereffect);
	newThornEnemy->SetPlayerBullet(playerbullet);
	newThornEnemy->SetThornPos(player->GetPosition().y - 5.0f);
	newThornEnemy->SetPosition({ player->GetPosition().x, 0.0f, player->GetPosition().z });
	enemy.push_back(newThornEnemy);
}
//’µ‚Ë‚é“G‚Ì¶¬
void EnemyEdit::WingEnemyArgment(std::vector<InterEnemy*>& enemy, Player* player, PlayerBullet* playerbullet,
	PlayerEffect* playereffect, Block* block, HitStop* hitstop) {
	InterEnemy* newWingEnemy;
	newWingEnemy = new WingEnemy();
	newWingEnemy->Initialize();
	newWingEnemy->SetPlayer(player);
	newWingEnemy->SetBlock(block);
	newWingEnemy->SetHitStop(hitstop);
	newWingEnemy->SetPlayerBullet(playerbullet);
	newWingEnemy->SetPlayerEffect(playereffect);
	newWingEnemy->SetPosition(player->GetPosition());
	newWingEnemy->SetStartPos(player->GetPosition());
	enemy.push_back(newWingEnemy);
}
//”ò‚Ô“G‚Ì¶¬
void EnemyEdit::BirdEnemyArgment(std::vector<InterEnemy*>& enemy, Player* player, PlayerBullet* playerbullet,
	PlayerEffect* playereffect, Block* block, HitStop* hitstop) {
	InterEnemy* newBirdEnemy;
	newBirdEnemy = new BirdEnemy();
	newBirdEnemy->Initialize();
	newBirdEnemy->SetPlayer(player);
	newBirdEnemy->SetBlock(block);
	newBirdEnemy->SetHitStop(hitstop);
	newBirdEnemy->SetPlayerBullet(playerbullet);
	newBirdEnemy->SetPlayerEffect(playereffect);
	newBirdEnemy->SetPosition(player->GetPosition());
	newBirdEnemy->SetStartPos(player->GetPosition());
	enemy.push_back(newBirdEnemy);
}