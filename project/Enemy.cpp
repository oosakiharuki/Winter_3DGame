#include "Enemy.h"
#include <fstream>

Enemy::~Enemy() {
	delete object3d;
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
		position.z -= 0.1f;
		object3d->SetTranslate(position);

		if (position.z < -5.0f) {
			action = Action::stop;
		}


		break;
	case stop:
		




		break;
	}

	if (isHit) {
		hp--;
		isHit = false;
	}

	if (!hp) {
		isDead_ = true;
	}
}

void Enemy::Draw() {
	object3d->Draw();
}

void Enemy::OnCollision() {
	isHit = true;
}