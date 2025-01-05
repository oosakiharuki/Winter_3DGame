#include "GameOverScene.h"

GameOverScene::~GameOverScene() {
	delete fead_;
	delete sprite_;
	delete camera;
	delete skydorm_;
}

void GameOverScene::Initialize(SpriteCommon* spriteCommon, Object3dCommon* objCommon, Input* input) {
	this->spriteCommon_ = spriteCommon;
	this->object3dCommon_ = objCommon;
	this->input_ = input;

	fead_ = new Fead();
	fead_->Initialize(spriteCommon_, "resource/Fead.png");

	sprite_ = new Sprite();
	sprite_->Initialize(spriteCommon_, "resource/LozeScene.png");

	camera = new Camera();
	Vector3 cameraRotate = { 0.0f,0.0f,0.0f };
	Vector3 cameraTranslate = { 0.0f,0.0f,-15.0f };

	camera->SetRotate(cameraRotate);
	camera->SetTranslate(cameraTranslate);
	object3dCommon_->SetDefaultCamera(camera);

	skydorm_ = new Skydorm();
	skydorm_->Initialize(object3dCommon_, camera, "skydorm.obj");
}

void GameOverScene::Update() {
	camera->Update();
	input_->Update();
	fead_->Update();
	sprite_->Update();
	skydorm_->Update();

	if (input_->TriggerKey(DIK_SPACE)) {
		fead_->StartFead();
	}

	if (fead_->SceneChange()) {
		sceneNo = SCENE::GAME;
	}
}

void GameOverScene::Draw() {
	//object
	object3dCommon_->Command();
	skydorm_->Draw();

	spriteCommon_->Command();
	sprite_->Draw();
	fead_->Draw();
}
