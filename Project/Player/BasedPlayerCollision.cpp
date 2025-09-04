#include "BasePlayerCollision.h"

void BasePlayerCollision::OnCollision([[maybe_unused]] const Collider& collider){
	isTouch_ = true;

	if (shouldPushBack_) {
		Vector3 vec = CalculateAABBPushbackVector(collider.GetAABB());

	}
}

void BasePlayerCollision::OffCollision(){
	isTouch_ = false;
}