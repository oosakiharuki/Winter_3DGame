#include "Wall.h"

Wall::~Wall() {
	delete object3d;
}

void Wall::Initialize(Object3dCommon* object3dCommon, const Vector3& position) {
	ObjCommon = object3dCommon;
	object3d = new Object3d();
	object3d->SetModelFile("wall.obj");
	object3d->Initialize(ObjCommon);

	this->position = position;
	object3d->SetTranslate(position);

	coolTime = 0.0f;
}

void Wall::Update() {
	object3d->Update();

	coolTime -= 1.0f / 60.0f;

	if (isHit_ && coolTime < 0) {
		hp--;
		coolTime = 0.5f;
		shakeTime = true;
	}
	else {
		isHit_ = false;
		if (coolTime < 0) {
			coolTime = 0;
			shakeTime = false;
		}
	}

	if (!hp) {
		isDead_ = true;
	}
}

void Wall::Draw() {
	object3d->Draw();
}

void Wall::OnCollision() {
	isHit_ = true;
}
