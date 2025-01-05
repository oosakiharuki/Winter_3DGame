#include "Player.h"
#include <algorithm>

Player::~Player() {
	delete object3d;
	for (PlayerBullet* bullet : bullets_) {
		delete bullet;
	}
}

void Player::Initialize(Object3dCommon* object3dCommon, Input* input){
	input_ = input;

	ObjCommon = object3dCommon;
	object3d = new Object3d();
	object3d->SetModelFile("player.obj");
	object3d->Initialize(ObjCommon);

}

void Player::Update() {
	object3d->Update();
	input_->Update();


	if (Move) {
		if (input_->PushKey(DIK_W)) {
			position.z += speed;
		}

		if (input_->PushKey(DIK_S)) {
			position.z -= speed;
		}

		if (input_->PushKey(DIK_A)) {
			position.x -= speed;
		}

		if (input_->PushKey(DIK_D)) {
			position.x += speed;
		}

		position.x = std::clamp(position.x, -kMoveX - position.z / 4, kMoveX + position.z / 4);
		position.z = std::clamp(position.z, kMoveZNear, kMoveZFar);


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
			else if (rotation.z > 0.1f) {
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


		Attack();
	}
	else {
		rotation.x += 0.1f;
		if (rotation.x > 5.0f) {
			rotation.x = 0.0f;
			Move = true;
		}
		object3d->SetRotate(rotation);
	}


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
	

}

void Player::Attack() {
	if (input_->PushKey(DIK_SPACE) && distanceTime == 0) {

		const float kBulletSpeed = 0.3f;
		Vector3 velocity(0, 0, kBulletSpeed);
		Matrix4x4 worldMatrix = object3d->GetWorld();

		velocity = MyMath::TransformNormal(velocity, worldMatrix);
		velocity.y = 0.0f;

		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(ObjCommon, position, velocity, object3d->GetRotate());

		bullets_.push_back(newBullet);

		distanceTime = 0.1f;
	}
	else {
		distanceTime -= 1.0f / 60.0f;
		if (distanceTime < 0) {
			distanceTime = 0;
		}
	}
}


void Player::Draw() {
	object3d->Draw();
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw();
	}
}


AABB Player::GetAABB() {

	AABB aabb;

	aabb.min = { position.x - 0.8f / 2.0f,position.y - 0.2f / 2.0f,position.z - 0.2f / 2.0f };
	aabb.max = { position.x + 0.8f / 2.0f,position.y + 0.2f / 2.0f,position.z + 0.2f / 2.0f };

	return aabb;
}


void Player::OnCollision() {
	Move = false;
}