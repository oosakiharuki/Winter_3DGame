#include "PlayerBullet.h"
#include "MyMath.h"

PlayerBullet::~PlayerBullet() {
	delete object;
}

void PlayerBullet::Initialize(Object3dCommon* object3dCommon, const Vector3& position, const Vector3& velocity, const Vector3& rotate){

	object = new Object3d();
	object->SetModelFile("bullet.obj");
	object->Initialize(object3dCommon);
	object->SetTranslate(position);

	this->velocity = velocity;
	this->rotation = rotate;	
	object->SetRotate(rotation);
}

void PlayerBullet::Update(){
	object->Update();
	
	position = object->GetTranslate();

	position.x += velocity.x;
	position.y += velocity.y;
	position.z += velocity.z;

	object->SetTranslate(position);

	rotation = object->GetRotate();
	rotation.x = 0.0f;
	object->SetRotate(rotation);

	lifeTimer -= deltaTimer;
	if (lifeTimer < 0.0f) {
		isDead_ = true;
	}
}

void PlayerBullet::Draw(){
	object->Draw();
}

AABB PlayerBullet::GetAABB() {

	AABB aabb;

	aabb.min = { position.x - 0.5f / 2.0f,position.y - 0.5f / 2.0f,position.z - 0.5f / 2.0f };
	aabb.max = { position.x + 0.5f / 2.0f,position.y + 0.5f / 2.0f,position.z + 0.5f / 2.0f };

	return aabb;
}

void PlayerBullet::OnCollision() {
	isDead_ = true;
}