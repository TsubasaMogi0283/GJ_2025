#include "BasePlayerCollision.h"

void BasePlayerCollision::OnCollision([[maybe_unused]] const Collider& collider){
	isTouch_ = true;

	if (shouldPushBack_) {
		
	}
}

void BasePlayerCollision::OffCollision(){
	isTouch_ = false;
}
