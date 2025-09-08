#include "TerrainCollider.h"
#include "CollisionConfig.h"
#include "../ITerrain.h"

TerrainCollider::TerrainCollider(ITerrain* p_owner)
{
	owner_ = p_owner;
}

void TerrainCollider::Init()
{
	// 名前の設定
	name_ = "TerrainCollider";
	// 種類
	collisionType_ = ColliderType::AABBType;
	// 属性設定
	Collider::SetCollisionAttribute(COLLISION_ATTRIBUTE_STAGE_OBJECT);
	Collider::SetCollisionMask(COLLISION_ATTRIBUTE_FLASH_LIGHT);
}

void TerrainCollider::Update()
{
	const float SIZE = 0.5f;
	
	// AABBに値を入れる
	aabb_.max = {
		.x = owner_->GetWorldPos().x + SIZE,
		.y = owner_->GetWorldPos().y + SIZE,
		.z = owner_->GetWorldPos().z + SIZE,
	};
	aabb_.min = {
		.x = owner_->GetWorldPos().x - SIZE,
		.y = owner_->GetWorldPos().y - SIZE,
		.z = owner_->GetWorldPos().z - SIZE,
	};
}

void TerrainCollider::OnCollision()
{
	// 出現処理
	owner_->OnReveal();
}

void TerrainCollider::OffCollision()
{
}

Vector3 TerrainCollider::GetWorldPosition()
{
	return owner_->GetWorldPos();
}
