#pragma once
#include "Objects/Object.h"

class PlayableObject : public Object{
public:
	PlayableObject(sf::Vector2f pos, const std::string& name) : Object(pos, name), m_prevPosition(pos) {}
	virtual void takeDamage(int damageAmount);
	virtual void update(float dt) = 0;
	virtual float getSpeed() const;
	virtual void move(const sf::Vector2f& delta);
	virtual void setAniName(const std::string& name);
	virtual std::string getName() const;
	virtual void updateScale();
	virtual bool isAttacked() const;
	virtual void attack();



protected:
	int m_hp;
	int m_energy;
	float m_speed;
	std::string m_aniName;
	std::string m_strategyName = "";
	std::string m_currentAnimationName;
	std::string m_name;
	sf::Vector2f m_prevPosition;
	bool m_underAttack = false;
};
