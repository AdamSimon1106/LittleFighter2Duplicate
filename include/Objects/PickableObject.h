#pragma once
#include "Objects/Object.h"
#include "Objects/ObjectStates/ObjectBaseState.h"
#include "Objects/PlayableObject.h"
#include "EventCommands\ICommand.h"
#include <memory>

enum Status { ON_EARTH, PICKED, THROWN, COLLIDE, EXPLODE};

class PickableObject : public Object {
public:
	PickableObject(const sf::Vector2f pos, const std::string& name, std::unique_ptr<ICommand> cmd);
	virtual void handleCollision() {};
	const std::string& getName();
	virtual void move(sf::Vector2f goal);
	void drop(float dt);
	virtual void playAttack() = 0;
	virtual bool onEarth() { return m_status == ON_EARTH; }
	virtual bool picked() { return m_status == PICKED; }
	virtual bool thrown() { return m_status == THROWN; }
	virtual bool isCollided() { return m_status == COLLIDE; }
	virtual bool isExploded() { return m_status == EXPLODE; }
	virtual void putBack(); 
	virtual void pick() { m_status = PICKED; }
	virtual void throwIt() { m_status = THROWN; }
	virtual void collide() { m_status = COLLIDE; }
	virtual void explode() { m_status = EXPLODE; }
	float getRange() const { return m_range; } 
	std::unique_ptr<ICommand> getHitCommand();
	Status getStatus() const { return m_status; }




	void markAsUsed();
	bool isUsed() const; 
	void setHolder(PlayableObject* holder);
	PlayableObject*  getHolder() const;
	const std::string& getStateName() const { return m_stateName; }
	void setStateName(const std::string& state) { m_stateName = state; }
	void setAnimationName(const std::string& animationName) { m_animationName = animationName; }
	const std::string& getAnimationName() const { return m_animationName; }
	void setState(std::unique_ptr<ObjectBaseState> state);
	const std::unique_ptr<ObjectBaseState>& getState() const { return m_state; }
	void setCommand(std::unique_ptr<ICommand> cmd) { m_command = std::move(cmd); }
	const int getXDirThrow() const;
protected:
	sf::Vector2f m_offset;
	Status m_status = ON_EARTH;
	float m_range;
	bool m_justDropped = false;
	sf::Vector2f m_dropTarget;
	int m_xDirThrow = 0;
	std::unique_ptr<ICommand> m_command = nullptr;
private:
	std::unique_ptr<ObjectBaseState> m_state = nullptr;
	PlayableObject* m_holder = nullptr;

	sf::Vector2f m_goalPosition;
	std::string m_name;
	std::string m_stateName ; // Default state is idle
	std::string m_animationName; // Default animation name is idle
	bool m_used = false;
	
};
