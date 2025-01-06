#include "GameScene.h"
#include <cassert>
#include <fstream>

GameScene::~GameScene() {
	delete camera;
	delete player;
	for (Enemy* enemy : enemies) {
		delete enemy;
	}
	delete fead_;
	delete skydorm_;
	delete wall_;
	delete UI;
	delete BGM;
}

void GameScene::Initialize(SpriteCommon* spriteCommon, Object3dCommon* objCommon, Input* input) {
	
	this->input_ = input;
	this->object3dCommon_ = objCommon;
	this->spriteCommon_ = spriteCommon;

	camera = new Camera();
	Vector3 cameraRotate = { 0.25f,0.0f,0.0f };
	Vector3 cameraTranslate = { 0.0f,7.0f,-20.0f };

	camera->SetRotate(cameraRotate);
	camera->SetTranslate(cameraTranslate);
	object3dCommon_->SetDefaultCamera(camera);

	player = new Player();
	player->Initialize(object3dCommon_, input_);
	

	LoadEnemyPopData();

	fead_ = new Fead();
	fead_->Initialize(spriteCommon_,"resource/Fead.png");

	skydorm_ = new Skydorm();
	skydorm_->Initialize(object3dCommon_, camera,"skydorm.obj");

	wall_ = new Wall();
	Vector3 wallPos = { 0.0f,0.0f,-5.5f };
	wall_->Initialize(object3dCommon_, spriteCommon_, wallPos);

	isClear_ = false;
	isGameOver_ = false;

	UI = new Sprite();
	UI->Initialize(spriteCommon_, "resource/UI.png");

	BGM = new Audio();
	BGM->Initialize("resource/BGM.wav");

	audio_ = new Audio();
	audio_->Initialize("resource/damageE.wav");
}

void GameScene::Update() {

	camera->Update();

	Vector3 cameraTranslate = { 0.0f,7.0f,-20.0f };

	if (wall_->IsShake()) {
		if (wall_->IsTime() > 0.25f) {
			shakeX = rand() % 20 - 10;
			shakeZ = rand() % 20 - 10;
		}
		else {
			shakeX = rand() % 40 - 20;
			shakeZ = rand() % 40 - 20;
		}
	}
	else {
		shakeX = 0;
		shakeZ = 0;
	}

	float shake1 = 1.0f / shakeX;
	float shake2 = 1.0f / shakeZ;
		
	if (shakeX == 0.0f || shakeZ == 0.0f) {
		shake1 = 1.0f / 0.1f;
		shake2 = 1.0f / 0.1f;
	}

	if (shakeX == 0.0f && shakeZ == 0.0f) {
		camera->SetTranslate({ cameraTranslate.x,cameraTranslate.y,cameraTranslate.z });
	}
	else {		
		camera->SetTranslate({ cameraTranslate.x + (shake1 / 1),cameraTranslate.y,cameraTranslate.z + (shake2 / 1) });
	}


	player->Update();

	UpdateEnemyPop();

	for (Enemy* enemy : enemies) {
		enemy->Update();
	}	

	CheckAllCollisions();

	enemies.remove_if([](Enemy* enemy) {
		if (enemy->IsDead()) {
			delete enemy;
			return true;
		}
		return false;
	});
	
	wall_->Update();

	fead_->Update();
	skydorm_->Update();
	//SceneChange
	if (wall_->IsDead()) {
		isGameOver_ = true;
		fead_->StartFead();
	}
	else if (isBornFinish && enemies.empty()) {
		isClear_ = true;
		fead_->ChangeSpriteFile("resource/FeadWin.png");
		fead_->StartFead();	
	}

	if (fead_->SceneChange() && isGameOver_) {
		sceneNo = SCENE::GameOver;
	}
	else if (fead_->SceneChange() && isClear_) {
		sceneNo = SCENE::Clear;
	}

	UI->Update();

}

void GameScene::Draw() {

	//backScreen
	spriteCommon_->Command();


	//object
	object3dCommon_->Command();

	skydorm_->Draw();
	player->Draw();
	for (Enemy* enemy : enemies) {
		enemy->Draw();
	}
	wall_->Draw();
	//UI
	spriteCommon_->Command();

	wall_->Draw2D();
	UI->Draw();
	fead_->Draw();

	PlayAudio();
}

bool GameScene::IsCollision(const AABB& aabb1, const AABB& aabb2) {
	if ((aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) &&
		(aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y) &&
		(aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z)) {
		return true;
	}
	return false;
}

void GameScene::CheckAllCollisions() {
	AABB posA, posB;

	const std::list<PlayerBullet*>& playerBullets = player->GetBullets();

	//const std::list<EnemyBullet*>& enemyBullets = enemyBullets_;

	posA = player->GetAABB();

	for (Enemy* enemy_ : enemies) {		
		posB = enemy_->GetAABB();

		if (IsCollision(posA,posB) && !enemy_->IsBow()) {
			player->OnCollision();			
		}
	}


	posA = wall_->GetAABB();

	for (Enemy* enemy_ : enemies) {
		posB = enemy_->GetAABB();

		if (IsCollision(posA, posB)) {
			wall_->OnCollision();
			enemy_->OnCollisionWall();			
		}

	}

	for (Enemy* enemy_ : enemies) {
		for (PlayerBullet* bullet : playerBullets) {
			posA = enemy_->GetAABB();
			posB = bullet->GetAABB();

			if (IsCollision(posA, posB) && !enemy_->IsBow()) {
				enemy_->OnCollision();
				bullet->OnCollision();
				audioHandle = -1;
			}
		}
	}


	//連鎖
	//for (Enemy* enemy_ : enemies) {
	//	posA = enemy_->GetAABB();
	//	if (enemy_->GetParticle()) {
	//		posB = enemy_->GetParticle()->GetAABB();
	//		if (IsCollision(posA, posB)) {
	//			enemy_->OnCollision();
	//			//bullet->OnCollision();
	//		}
	//	}
	//}

}

void GameScene::EnemyBorn(Vector3 position) {
	Enemy* enemy = new Enemy();
	Vector3 EnemyPos = position;

	enemy->Initialize(object3dCommon_, EnemyPos);
	enemies.push_back(enemy);
}

void GameScene::LoadEnemyPopData() {

	std::ifstream file;
	file.open("resource/EnemyPop.csv");
	assert(file.is_open());

	enemyPopCommands << file.rdbuf();

	file.close();

}

void GameScene::UpdateEnemyPop() {
	if (!isBornFinish) {

		// if A
		if (WaitFlag) {
			waitTimer--;
			if (waitTimer <= 0) {
				WaitFlag = false;
			}
			return;
		}

		std::string line;

		while (getline(enemyPopCommands, line)) {

			std::istringstream line_stream(line);

			std::string word;

			getline(line_stream, word, ',');

			if (word.find("//") == 0) {
				continue;
			}

			if (word.find("POP") == 0) {
				getline(line_stream, word, ',');
				float x = (float)std::atof(word.c_str());

				getline(line_stream, word, ',');
				float y = (float)std::atof(word.c_str());

				getline(line_stream, word, ',');
				float z = (float)std::atof(word.c_str());

				getline(line_stream, word, ',');
				float direction = (float)std::atof(word.c_str());//向き

				EnemyBorn(Vector3(x, y, z));

			}
			else if (word.find("WAIT") == 0) {
				getline(line_stream, word, ',');

				int32_t waitTime = atoi(word.c_str());

				WaitFlag = true;
				waitTimer = waitTime;

				break; // 待機時間にif Aを使うため一度while文から抜ける
			}
			else if (word.find("FINISH") == 0) {
				isBornFinish = true;
				break;
			}
		}
	}

}


void GameScene::PlayAudio() {
	if (BGMHandle < 0) {
		BGM->SoundPlayWave(0.02f);
		BGMHandle++;
	}

	if (audioHandle < 0) {
		audio_->SoundPlayWave(0.05f);
		audioHandle++;
	}
}
