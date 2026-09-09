#ifndef Category_Enum_hpp
#define Category_Enum_hpp


// Entity/scene node category, used to dispatch commands
namespace Category
{
	enum Type
	{
		None,
		Scene,
		ViewArea,
		Superlayer, //Special category for drawing on above layers

		Platformer,
		PlatformerMover,
		Platform,

		Entity,
		Player,
		Enemy,
		Attack,

		Movable,
		MovingPlatform,
		
		Weapon,

		Interactable,
		Door,
		NPC,
		TypeCount
	};
}

#endif
