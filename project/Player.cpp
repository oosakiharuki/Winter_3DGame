#include "Player.h"
#include "ModelManager.h"

Player::~Player() {
	delete object3d;
	delete sprite;
}

void Player::Initialize(Object3dCommon* object3dCommon, SpriteCommon* spriteCommon , WinApp* winApp){
	winApp_ = winApp;
	input_ = new Input();
	input_->Initialize(winApp_);

	sprite = new Sprite();
	sprite->Initialize(spriteCommon, "resource/Hp.png");

	object3d = new Object3d();
	//ModelManager::GetInstance()->LoadModel("plane.obj");
	object3d->SetModelFile("player.obj");
	object3d->Initialize(object3dCommon);
}

void Player::Update() {
	object3d->Update();
	sprite->Update();
	input_->Update();

	if (input_->PushKey(DIK_W)) {
		position.y += 0.1f;
	}

	if (input_->PushKey(DIK_S)) {
		position.y -= 0.1f;
	}

	if (input_->PushKey(DIK_A)) {
		position.x -= 0.1f;
	}
	
	if (input_->PushKey(DIK_D)) {
		position.x += 0.1f;
	}




	object3d->SetTranslate(position);

	rotation = object3d->GetRotate();

	if (input_->PushKey(DIK_A)) {
		if (rotation.z > -0.5f) {
			rotation.z -= 0.1f;
		}
	}	
	else if (input_->PushKey(DIK_D)) {
		if (rotation.z < 0.5f) {
			rotation.z += 0.1f;
		}
	}
	else {
		
		if (rotation.z < -0.1f) {
			rotation.z += 0.1f;
		}
		else if(rotation.z > 0.1f) {
			rotation.z -= 0.1f;
		}
		else {
			rotation.z = 0.0f;
		}
	}


	if (input_->PushKey(DIK_W)) {
		if (rotation.x > -0.5f) {
			rotation.x -= 0.1f;
		}
	}
	else if (input_->PushKey(DIK_S)) {
		if (rotation.x < 0.5f) {
			rotation.x += 0.1f;
		}
	}
	else {

		if (rotation.x < -0.1f) {
			rotation.x += 0.1f;
		}
		else if (rotation.x > 0.1f) {
			rotation.x -= 0.1f;
		}
		else {
			rotation.x = 0.0f;
		}
	}

	object3d->SetRotate(rotation);

	size = object3d->GetScale();

	object3d->SetScale(size);
}

void Player::Draw() {
	object3d->Draw();
}

void Player::Draw2D() {
	sprite->Draw();
}
