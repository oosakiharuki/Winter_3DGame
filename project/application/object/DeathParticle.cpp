#include "DeathParticle.h"
#include "ModelManager.h"

DeathParticle::~DeathParticle() {
	delete object3d;
}

void DeathParticle::Initialize(Object3dCommon* object3dCommon, Vector3 position) {
	ObjCommon = object3dCommon;
	
	object3d = new Object3d();	
	object3d->SetModelFile("bom.obj");
	
	object3d->Initialize(ObjCommon);
	this->position = position;
	object3d->SetTranslate(position);
}

void DeathParticle::Update() {
	object3d->Update();

	rotation.y += 0.5f;
	object3d->SetRotate(rotation);

	size.x += 0.05f;
	size.y += 0.05f;
	size.z += 0.05f;

	object3d->SetScale(size);

	timer -= 1.0f / 60.0f;
}

void DeathParticle::Draw() {
	object3d->Draw();
}

AABB DeathParticle::GetAABB() {

	AABB aabb;

	aabb.min = { position.x - size.x / 2.0f,position.y - size.y / 2.0f,position.z - size.z / 2.0f };
	aabb.max = { position.x + size.x / 2.0f,position.y + size.y / 2.0f,position.z + size.z / 2.0f };

	return aabb;
}
