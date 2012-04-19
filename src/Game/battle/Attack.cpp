#include <actions/Attack.h>

namespace Game
{
	namespace Battle
	{
		namespace Actions
		{
			float Attack::GetMagicWeight() const
			{
				return MagicWeight;
			}
			float Attack::GetPhysicalWeight() const
			{
				return PhysicalWeight;
			}
		}
	}
}