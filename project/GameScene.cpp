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
}

void GameScene::Initialize(SpriteCommon* spriteCommon, Object3dCommon* objCommon, Input* input) {
	
	this->input_ = input;
	this->object3dCommon_ = objCommon;
	this->spriteCommon_ = spriteCommon;

	ModelManager::GetInstance()->LoadModel("plane.obj");
	ModelManager::GetInstance()->LoadModel("enemy.obj");
	ModelManager::GetInstance()->LoadModel("player.obj");
	ModelManager::GetInstance()->LoadModel("bullet.obj");

	
	camera = new Camera();
	Vector3 cameraRotate = { 0.0f,0.0f,0.0f };
	Vector3 cameraTranslate = { 0.0f,0.0f,-15.0f };

	camera->SetRotate(cameraRotate);
	camera->SetTranslate(cameraTranslate);
	object3dCommon_->SetDefaultCamera(camera);

	player = new Player();
	player->Initialize(object3dCommon_, spriteCommon_, input_);
	

	LoadEnemyPopData();

	fead_ = new Fead();
	fead_->Initialize(spriteCommon_,"resource/Fead.png");

	skydorm_ = new Skydorm();
	skydorm_->Initialize(object3dCommon_, camera,"skydorm.obj");
}

void GameScene::Update() {

	camera->Update();
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
	
	fead_->Update();
	skydorm_->Update();
	//SceneChange
	if (player->FinishWin()) {
		fead_->ChangeSpriteFile("resource/FeadWin.png");
		fead_->StartFead();
	}
	else if (player->FinishLoze()) {
		fead_->StartFead();
	}


	if (fead_->SceneChange() && player->FinishWin()) {
		sceneNo = SCENE::Clear;
	}

	if (fead_->SceneChange() && player->FinishLoze()) {
		sceneNo = SCENE::GameOver;
	}
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

	//UI
	spriteCommon_->Command();

	player->Draw2D();
	fead_->Draw();

}

void GameScene::CheckAllCollisions() {
	Vector3 posA, posB;

	const std::list<PlayerBullet*>& playerBullets = player->GetBullets();

	//const std::list<EnemyBullet*>& enemyBullets = enemyBullets_;

	// case radius
	const float plaeyrRadius = 0.2f;

	const float EnemyRadius = 0.2f;

	for (Enemy* enemy_ : enemies) {
		for (PlayerBullet* bullet : playerBullets) {

			posA = enemy_->GetPosition();
			posB = bullet->GetPosition();

			Vector3 distance{};

			distance.x = (posB.x - posA.x) * (posB.x - posA.x);
			distance.y = (posB.y - posA.y) * (posB.y - posA.y);
			distance.z = (posB.z - posA.z) * (posB.z - posA.z);

			float L;

			L = (plaeyrRadius + EnemyRadius) * (plaeyrRadius + EnemyRadius);

			if (distance.x + distance.y + distance.z <= L) {

				enemy_->OnCollision();
				bullet->OnCollision();
			}
		}
	}
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
