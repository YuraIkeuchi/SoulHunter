#include "EnemyEdit.h"
//通常の敵の生成
void EnemyEdit::NormalEnemyArgment(std::vector<InterEnemy*>& enemy, Player* player,
	Block* block, HitStop* hitstop){
	InterEnemy* newEnemy;
	newEnemy = new Enemy();
	newEnemy->Initialize();
	newEnemy->SetPlayer(player);
	newEnemy->SetBlock(block);
	newEnemy->SetHitStop(hitstop);
	newEnemy->SetPosition(player->GetPosition());
	newEnemy->SetStartPos(player->GetPosition());
	enemy.push_back(newEnemy);
}
//棘の敵の生成
void EnemyEdit::ThornEnemyArgment(std::vector<InterEnemy*>& enemy, Player* player,
	HitStop* hitstop) {
	InterEnemy* newThornEnemy;
	newThornEnemy = new ThornEnemy();
	newThornEnemy->Initialize();
	newThornEnemy->SetPlayer(player);
	newThornEnemy->SetHitStop(hitstop);
	newThornEnemy->SetThornPos(player->GetPosition().y - 5.0f);
	newThornEnemy->SetPosition({ player->GetPosition().x, 0.0f, player->GetPosition().z });
	enemy.push_back(newThornEnemy);
}
//跳ねる敵の生成
void EnemyEdit::BoundEnemyArgment(std::vector<InterEnemy*>& enemy, Player* player,
	Block* block, HitStop* hitstop) {
	InterEnemy* newBoundEnemy;
	newBoundEnemy = new BoundEnemy();
	newBoundEnemy->Initialize();
	newBoundEnemy->SetPlayer(player);
	newBoundEnemy->SetBlock(block);
	newBoundEnemy->SetHitStop(hitstop);
	newBoundEnemy->SetPosition(player->GetPosition());
	newBoundEnemy->SetStartPos(player->GetPosition());
	enemy.push_back(newBoundEnemy);
}
//飛ぶ敵の生成
void EnemyEdit::BirdEnemyArgment(std::vector<InterEnemy*>& enemy, Player* player,
	Block* block, HitStop* hitstop) {
	InterEnemy* newBirdEnemy;
	newBirdEnemy = new BirdEnemy();
	newBirdEnemy->Initialize();
	newBirdEnemy->SetPlayer(player);
	newBirdEnemy->SetBlock(block);
	newBirdEnemy->SetHitStop(hitstop);
	newBirdEnemy->SetPosition(player->GetPosition());
	newBirdEnemy->SetStartPos(player->GetPosition());
	enemy.push_back(newBirdEnemy);
}