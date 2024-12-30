#include "Player.h"
#include "ModelManager.h"

Player::~Player() {
	delete object3d;
	delete sprite;
	for (PlayerBullet* bullet : bullets_) {
		delete bullet;
	}
}

void Player::Initialize(Object3dCommon* object3dCommon, SpriteCommon* spriteCommon , Input* input){
	input_ = input;

	sprite = new Sprite();
	sprite->Initialize(spriteCommon, "resource/Hp.png");

	ObjCommon = object3dCommon;
	object3d = new Object3d();
	object3d->SetModelFile("player.obj");
	object3d->Initialize(ObjCommon);

	isClear_ = false;
	isGameOver_ = false;
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

	//rotation.y += 0.1f;

	object3d->SetRotate(rotation);

	size = object3d->GetScale();

	object3d->SetScale(size);

	Attack();
	for(PlayerBullet* bullet : bullets_) {
		bullet->Update();
	}

	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	if(input_->TriggerKey(DIK_8)) {
		isClear_ = true;
	}

	if (input_->TriggerKey(DIK_9)) {
		isGameOver_ = true;
	}

}

void Player::Attack() {
	if (input_->TriggerKey(DIK_SPACE)) {

		const float kBulletSpeed = 0.2f;
		Vector3 velocity(0, 0, kBulletSpeed);
		Matrix4x4 worldMatrix = object3d->GetWorld();

		velocity = MyMath::TransformNormal(velocity, worldMatrix);
		//velocity.y = 0.0f;

		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(ObjCommon, position, velocity, object3d->GetRotate());
		


		bullets_.push_back(newBullet);
	}
}


void Player::Draw() {
	object3d->Draw();
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw();
	}
}

void Player::Draw2D() {
	sprite->Draw();
}

void Player::OnCollision() {

}