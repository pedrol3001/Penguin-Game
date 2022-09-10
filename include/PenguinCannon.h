#ifndef PENGUIN_CANNON_H
#define PENGUIN_CANNON_H

#include "Component.h"
#include <memory>

class PenguinCannon: public Component {
	public:
		PenguinCannon(GameObject& associated, weak_ptr<GameObject> penguinBody);

		void Update(float dt);
		void Render();
		bool Is(string type);

		void Shoot();

	private:
		weak_ptr <GameObject> pbody;
		float angle;
};

#endif
