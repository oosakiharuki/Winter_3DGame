#include "Enemy.h"
#include <fstream>

Enemy::~Enemy() {
	delete object3d;
	delete deathBom;
}

void Enemy::Initialize(Object3dCommon* object3dCommon, const Vector3& position) {
	
	ObjCommon = object3dCommon;
	object3d = new Object3d();
	object3d->SetModelFile("enemy.obj");
	object3d->Initialize(ObjCommon);

	this->position = position;
	object3d->SetTranslate(position);

}

void  Enemy::Update() {
	object3d->Update();

	switch (action)
	{
	case move:
		position = object3d->GetTranslate();
		position.z -= 0.05f;
		object3d->SetTranslate(position);

		if (position.z < 1.0f) {
			action = Action::stop;
		}

		break;
	case stop:
		position = object3d->GetTranslate();
		position.z -= 0.05f;
		object3d->SetTranslate(position);

		rotation.y += 0.3f;
		object3d->SetRotate(rotation);
		
		break;
	case bom:	
		if (deathBom == nullptr) {
			deathBom = new DeathParticle();
			deathBom->Initialize(ObjCommon, position);
		}
		deathBom->Update();

		position = object3d->GetTranslate();
		deathBom->SetPosition(position);

		float particleTime = deathBom->GetTimer();
		if (particleTime < 0.0f) {
			isDead_ = true;
		}

		break;
	}

	if (isHit) {
		hp--;
		isHit = false;
	}

	if (!hp) {
		action = Action::bom;
		isBow = true;
	}
}

void Enemy::Draw() {
	switch (action)
	{
	case move:
		object3d->Draw();

		break;
	case stop:
		object3d->Draw();

		break;

	case bom:
		if (deathBom) {
			deathBom->Draw();
		}
		break;
	}
}

AABB Enemy::GetAABB() {

	AABB aabb;

	aabb.min = { position.x - 0.5f / 2.0f,position.y - 0.5f / 2.0f,position.z - 0.5f / 2.0f };
	aabb.max = { position.x + 0.5f / 2.0f,position.y + 0.5f / 2.0f,position.z + 0.5f / 2.0f };

	return aabb;
}

void Enemy::OnCollision() {
	isHit = true;
}

void Enemy::OnCollisionWall() {
	isDead_ = true;
}
