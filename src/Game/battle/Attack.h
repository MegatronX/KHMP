#pragma once

#include <actions/Action.h>

namespace Game
{
	namespace Battle
	{
		namespace Actions
		{
			class Attack : public Action
			{
			public:
				float GetMagicWeight() const;
				float GetPhysicalWeight() const;
			private:
				float MagicWeight;
				float PhysicalWeight;
			};

		}
	}
}