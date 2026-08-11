#ifndef World_hpp
#define World_hpp

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Player_Entity.h"
#include "Scene_Builder.h"

#include <array>
#include <queue>
#include "ViewHandler.h"
#include "Timekeeper.h"
#include "WorldAction.h"


// Forward declaration
namespace sf
{
	class RenderWindow;
}

struct Scene_Change_Request {
	Scenes scene = Scenes::Null;
	sf::Vector2f playerPos;
	bool fadeIn = false;
};

class World : private sf::NonCopyable
{
	public:
		enum World_Mode {
			Normal, //Full freedom of movement
			Story, //All controls locked
			Combat, //Same as normal, some things locked
			Boss, //Same as combat, but with health/progress bar up top
			Death, //Supress updates? decide later
			Paused //Just in case, IDK
		};

	public:
		explicit							World(sf::RenderWindow& window);
		void								update(sf::Time dt);
		void								draw();
		
		CommandQueue&						getCommandQueue();
		sf::FloatRect						getWorldViewBounds();
		sf::FloatRect						getWorldBounds();
		SceneNode*							getSceneGraph();

		static Player_Entity*				getPlayer();
		double						getGravity();

		void								pushAction(WorldAction* worldAction);
		void								pushAction(std::vector<WorldAction*> worldActions);
		void								deployActionToChildren(Category::Type target, Action* actionToDeploy);

		Scene_Change_Request				requestSceneChange();
		void								prepareSceneForPlay(Scene_Builder* builder);

		static World*						getInstance();

		std::array<SceneNode*, LayerCount>	getSceneLayers();

		World_Mode							getWorldMode();
		void								setWorldMode(World_Mode newMode);

	private:
		void								changeScene(Scenes scene, sf::Vector2f playerPos);

		void								handleWorldActions(sf::Time dt);

		void								enforceGravity(sf::Time dt);
		void								adaptPlayerPosition();
		void								enforceVelocityCap();

		void								adaptView();
		
		void								handleCollisions();
		void								onCommand(const WorldCommand& command);

	private:
		sf::RenderWindow&					mWindow;
		sf::View							mWorldView;
		TextureHolder						mTextures;
		FontHolder							mFonts;

		SceneNode							mSceneGraph;
		std::array<SceneNode*, LayerCount>	mSceneLayers;
		
		Scene_Builder*						mBuilder;

		CommandQueue						mCommandQueue;

		sf::FloatRect						mWorldBounds;
		sf::Vector2f						mSpawnPosition;

		Player_Entity*						mPlayer;

		float								mGravity; //In m/s^2, converted to px later
		float								mMaxXVelocity;
		float								mMaxYVelocity;
		float								mConstantDeaccel;

		Timekeeper							mTimekeeper;
		ViewHandler							mViewHandler;

		Scene_Change_Request				mSceneChangeRequest;
		Scenes								mScene;

		World_Mode							mMode;
		std::queue<WorldAction*>			mActions;

		static World*						instance;
};

#endif
