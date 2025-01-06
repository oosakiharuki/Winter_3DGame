#include "Wall.h"

Wall::~Wall() {
	delete object3d;	
	delete spriteHp;
	delete spriteBar;
	delete audio_;
}

void Wall::Initialize(Object3dCommon* object3dCommon, SpriteCommon* spriteCommon, const Vector3& position) {
	ObjCommon = object3dCommon;
	object3d = new Object3d();
	object3d->SetModelFile("wall.obj");
	object3d->Initialize(ObjCommon);

	this->position = position;
	object3d->SetTranslate(position);

	spriteHp = new Sprite();
	spriteBar = new Sprite();

	spriteHp->Initialize(spriteCommon, "resource/Hp.png");
	spriteBar->Initialize(spriteCommon, "resource/Hpbar.png");

	Vector2 translate = { 0,0 };
	translate.x += 10.0f;
	translate.y += 10.0f;
	spriteHp->SetPosition(translate);
	spriteBar->SetPosition(translate);

	coolTime = 0.0f;

	audio_ = new Audio();
	audio_->Initialize("resource/damageP.wav");
}

void Wall::Update() {
	object3d->Update();
	spriteHp->Update();
	spriteBar->Update();

	coolTime -= 1.0f / 60.0f;

	if (isHit_ && coolTime < 0) {
		hp--;
		Vector2 damage = spriteHp->GetSize();
		damage.x -= 32.0f;
		spriteHp->SetSize(damage);
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
	if (audioHandle < 0) {
		audio_->SoundPlayWave(0.05f);
		audioHandle++;
	}

}

void Wall::Draw() {
	object3d->Draw();
}

void Wall::Draw2D() {
	spriteHp->Draw();
	spriteBar->Draw();
}


AABB Wall::GetAABB() {

	AABB aabb;

	aabb.min = { position.x - 10.0f / 2.0f,position.y - 0.5f / 2.0f,position.z - 0.5f / 2.0f };
	aabb.max = { position.x + 10.0f / 2.0f,position.y + 0.5f / 2.0f,position.z + 0.5f / 2.0f };

	return aabb;
}

void Wall::OnCollision() {
	isHit_ = true;
	audioHandle = -1;
}
