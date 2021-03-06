#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "SFML\Graphics.hpp"
#include "pugixml.hpp"
#include <sstream>
#include <memory>
#include "VectorMath.h"

//you should do a check against this if you're drawing any debug sprites so it can be toggled easily
#define LEVEL_DEBUG true

class Level
{
public:
	Level();
	//Pass in the path to the desired levels XML file, should be in Assets/Levels
	Level(std::string levelDataPath);
	~Level(void);

	//Loads the level in from the xml file found at levelPath
	bool LoadLevel(std::string levelPath);

	//Renders the loaded level
	void Draw(sf::RenderWindow &window);

	//Returns a pointer to the collision rects so they can be iterated over to check for collision
	std::vector<sf::Rect<int>> *GetCollisionBounds();

private:

	//The xml file that we load in to define the level
	pugi::xml_document levelDoc;

	enum LevelLayers
	{
		BACKGROUNDCOLOUR,
		BACKGROUND,
		OBJECTS,
		FOREGROUND,
		COLLISION
	};

	//The background colour of the level
	sf::Color backgroundColor;

	//Loads a layer into the level, done like this so we can load layers in different orders if we want.
	void LoadLayer(LevelLayers layer);

	//The textures the level uses are stored here. Some fancy stuff is done so one texture is never duplicated to save on the memory footprint and increase performence.
	std::map<std::string, std::unique_ptr<sf::Texture>> textureMap;

	std::vector<sf::Sprite> backgroundSprites;
	std::vector<sf::Sprite> objectSprites;
	std::vector<sf::Sprite> foregroundSprites;

	std::vector<sf::Rect<int>> collisionBounds;

};

