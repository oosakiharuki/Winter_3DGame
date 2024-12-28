#include "GameScene.h"

GameScene::~GameScene() {


	delete player;
	for (Enemy* enemy : enemies) {
		delete enemy;
	}
}

void GameScene::Initialize(SpriteCommon* spriteCommon, Object3dCommon* objCommon, Input* input) {
	
	this->input_ = input;
	this->object3dCommon_ = objCommon;
	this->spriteCommon_ = spriteCommon;

	ModelManager::GetInstance()->LoadModel("plane.obj");
	ModelManager::GetInstance()->LoadModel("axis.obj");
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


	for (uint32_t i = 0; i < 2; ++i) {
		Enemy* enemy = new Enemy();
		Vector3 EnemyPos;

		if (i == 0) {
			EnemyPos = { 1.0f,0.0f,25.0f };
		}
		else {
			EnemyPos = { -1.0f,0.0f,20.0f };
		}

		enemy->Initialize(objCommon, EnemyPos);
		enemies.push_back(enemy);
	}
}

void GameScene::Update() {

	camera->Update();
	player->Update();

	for (Enemy* enemy : enemies) {
		enemy->Update();
	}	
	
	//SceneChange
	//if () {
	//	sceneNo = SCENE:: ;
	//}
}

void GameScene::Draw() {

	//backScreen
	spriteCommon_->Command();


	//object
	object3dCommon_->Command();

	player->Draw();
	for (Enemy* enemy : enemies) {
		enemy->Draw();
	}

	//UI
	spriteCommon_->Command();

	player->Draw2D();

}
