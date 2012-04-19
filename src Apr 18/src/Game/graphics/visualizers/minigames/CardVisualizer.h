#include <graphics/Sprites/AnimatedSpriteInterface.h>
#include <minigames/triad/Card.h>

class Engine;

namespace Game
{
	namespace Graphics
	{
		namespace Visuazlizer
		{
			class CardVisualizer : public AnimatedSpriteInterface
			{
			public:
				CardVisualizer(MiniGames::Triad::card_ptr cardPtr) : AttachedCard(cardPtr)
				{

				}
				void virtual Draw(sf::RenderWindow &window, sf::Shader &shader) override;
			private:
				Engine* engine;
				MiniGames::Triad::card_ptr AttachedCard;
			};
		}
	}
}