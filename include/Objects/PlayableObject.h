#pragma once
#include "Objects/Object.h"
#include "PlayableObjectStates/PlayableObjectState.h"
#include "EventCommands/ICommand.h"
#include <iostream>

enum class Direction
{
	RIGHT = 1, LEFT = -1
};

class PlayableObject : public Object{
public:
	PlayableObject(sf::Vector2f pos, const std::string& name) : Object(pos, name), m_prevPosition(pos) {}
	PlayableObject(std::shared_ptr<sf::Texture> textSheet, std::shared_ptr<sf::Texture> icon) : Object(textSheet),m_icon(icon), m_prevPosition(sf::Vector2f(1000, 800)) {}
	void setState(std::unique_ptr<PlayableObjectState> newState); 
	virtual void handleCommand(std::unique_ptr<ICommand> command);
	virtual void pickUpObject(std::shared_ptr<PickableObject> obj);
	virtual void setDiraction(Input input);
	virtual void attack();
	virtual int getDirection() const { return static_cast<int>(m_dir); }
	virtual void setStrategyName(const std::string& name);
	virtual void resetDirection(); 
	const PlayableObjectState* getState() const { return m_state.get(); }

	virtual void takeDamage(int damageAmount);
	virtual void update(float dt) = 0;
	virtual float getSpeed() const;
	virtual void move(const sf::Vector2f& delta);
	virtual void move(float dt);
	virtual void setAniName(const std::string& name);
	virtual std::string getName() const;
	virtual void updateScale();
	bool isHoldingWeapon(std::shared_ptr<PickableObject> obj) const;
	virtual std::shared_ptr<Object> getTarget() { return nullptr; };
	virtual std::shared_ptr<PickableObject> getObject() {
		return nullptr; 
	};
	std::string getStrategyName();
	virtual void tookItem();
	virtual void wantItem();
	virtual bool needItem();
	virtual void startAttackTimer();

	virtual bool canAttack();

	// in-game Events:
	virtual void onStoneHit() = 0;
	virtual void onBoxHit() = 0 ;
	virtual void onHandsAttack() = 0;
	virtual void onExplosion() = 0;

	void adjustRange(float range);
	float getAttackRange() const;
	std::shared_ptr<PickableObject> getHeldObj() const;
	void dropHeldObj();
	void setSafeZone(const sf::Vector2f& zone) { m_safeZone = zone; }
	sf::Vector2f getSafeZone() const { return m_safeZone; }
	void reduceHp(int amountToReduce);
	int getHp()const  { return m_hp; }
	int getPotentialHp() const { return m_potentialHp; }
	void updateHp();
	std::shared_ptr<sf::Texture> getIcon() const;
	virtual void resetHP() = 0;
	void setXHit(int xdirHit) { m_xdirHit = xdirHit; }
	float getHitCooldown() const;
	void setHitCooldown(float cooldown);
protected:
	int m_hp;
	int m_potentialHp;
	int m_hpClock = 0;
	int m_energy;
	float m_speed;
	std::string m_aniName;
	std::string m_strategyName = "";
	std::string m_currentAnimationName;
	std::string m_name;
	sf::Vector2f m_prevPosition;
	bool m_needItem = true;
	std::shared_ptr<sf::Texture> m_icon;
	std::unique_ptr<PlayableObjectState> m_state;
	std::unique_ptr<AttackBehavior> m_attack;
	std::shared_ptr<PickableObject> m_heldObject = nullptr;
	Direction m_dir;
	sf::Vector2f m_direction{ 0.f,0.f };
	sf::Vector2f m_safeZone = { 0.f, 0.f };
	float m_attackRange = 50.f;
	int m_xdirHit = 0;
	float m_hitCooldown = 0.f;
	bool m_attackTimer = false;
	bool m_canAttack = true;
};


	