#pragma once
#include "SFML\Graphics.hpp"

class Player
{
public:
	Player(std::string playerTexturePath, sf::Vector2f startPos);
	~Player(void);

	void Update(sf::Event events, bool eventFired, double deltaTime, std::vector<sf::Rect<float>> &levelCollisionRects);
	void Render(sf::RenderWindow &window);
	void Move(float x, float y);
	sf::Vector2f GetPosition();
	void SetPosition(float xPos, float yPos);
	sf::FloatRect GetCollider();
	void SetPosition(sf::Vector2f position);
private:
	sf::Texture texture;
	sf::Sprite sprite;

	bool Initialise(std::string playerTexturePath, sf::Vector2f startPos);

	//This function polls the input devices and updates the player state accordingly.
	void ReceiveControlInput(sf::Event events, bool eventFired);
	//All these vectors are set in Initialise, may seem a bit unnescesary, but doing it this way means we can easily change what keys control what, have as many keys as we like do one thing without loads of ifs, + allows easy support for in-game control remapping if neccesary
	std::vector<sf::Keyboard::Key> moveLeftKeys;
	std::vector<sf::Keyboard::Key> moveRightKeys;
	std::vector<sf::Keyboard::Key> jumpKeys;

	//Reads the current state of input from the playerstate and deals with moving
	void HandleMovement(float deltaTime, std::vector<sf::Rect<float>> &levelCollisionRects);

	void HandleHorizontalCollision(std::vector<sf::Rect<float>> &levelCollisionRects);
	void HandleVerticalCollision(std::vector<sf::Rect<float>> &levelCollisionRects);

	float maxGroundMovementSpeed;
	float groundAcceleration;
	float personalGravity;
	float terminalVelocity;
	float jumpStrength;

	//This struct should store the complete state of the player, both in what it is currently doing and what it has been commanded to do last frame
	struct PlayerState
	{
		//These variables store the current absolute state of the player
		bool movingLeft;
		bool movingRight;
		bool jumping;
		bool grounded;

		sf::Vector2f velocity;

		//These variables are updated from ReceiveControlInput() and are the last inputs received, should probably be set back to false every frame unless you're doing something weird.
		bool INPUT_MoveLeft;
		bool INPUT_MoveRight;
		bool INPUT_Jump;

		PlayerState::PlayerState()
		{
			movingLeft = false;
			movingRight = false;
			jumping = false;
			grounded = false;
			INPUT_MoveLeft = false;
			INPUT_MoveRight = false;
			INPUT_Jump = false;
			velocity = sf::Vector2f(0,0);
		}

		void PlayerState::ResetInputs()
		{
			INPUT_MoveLeft = false;
			INPUT_MoveRight = false;
			INPUT_Jump = false;
		}
	};
	PlayerState playerState;
};

