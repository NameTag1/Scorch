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


// Forward declaration
namespace sf
{
	class RenderWindow;
}

struct Scene_Change_Request {
	Scenes scene;
	sf::Vector2f playerPos;
	bool fadeIn;
};

class World : private sf::NonCopyable
{
	public:
		explicit							World(sf::RenderWindow& window);
		void								update(sf::Time dt);
		void								draw();
		
		CommandQueue&						getCommandQueue();
		sf::FloatRect						getWorldViewBounds();
		sf::FloatRect						getWorldBounds();
		SceneNode*							getSceneGraph();

		static Player_Entity*				getPlayer();
		static double						getGravity();

		Scene_Change_Request				requestSceneChange();
		void								prepareSceneForPlay(Scene_Builder* builder);

		static World*						getInstance();

		std::array<SceneNode*, LayerCount>	getSceneLayers();

	private:
		void								changeScene(Scenes scene, sf::Vector2f playerPos);

		void								enforceGravity();
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

		float								mGravity;
		float								mMaxFallVelocity;
		float								mMaxXVelocity;
		float								mMaxYVelocity;
		float								mConstantDeaccel;

		Timekeeper							mTimekeeper;
		ViewHandler							mViewHandler;

		Scene_Change_Request				mSceneChangeRequest;
		Scenes								mScene;

		static World*						instance;
};

#endif
