#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
struct  PlayerData; // forward declaration
class Player; // forward declaration
class Ally; // forward declaration
class Enemy;// forward declaration
class PlayableObject;

class HUD {
public:
	HUD(const sf::Vector2u screenSize, const std::vector<std::shared_ptr<PlayableObject>>& members);
	void update(const std::vector<std::shared_ptr<PlayableObject>>& allies,const std::vector< std::shared_ptr<Enemy>>& enemies, const std::string levelInfo);
	void draw(sf::RenderWindow& window);
private:
	sf::RectangleShape m_frame;
	sf::Font m_font;
	sf::RectangleShape m_infoFrame;
	sf::Text m_alliesInfo;
	sf::Text m_enemyInfo;
	sf::Text m_levelInfo;
	class CharacterFrame {
	public:
		CharacterFrame(const sf::Vector2f size, const sf::Vector2f position, const std::shared_ptr<PlayableObject>& member);
		void update();
		void draw(sf::RenderWindow& window);
		float getMaxHp() const;
		void setMaxlHp(const float amount);
		float getPotentialHp() const;
		void setPotentialHp(const float amount);
		float getCurrHp() const;
		void setCurrHp(const float amount);
		
	private:
		std::shared_ptr<PlayableObject> m_member;
		sf::RectangleShape m_frame;
		sf::Sprite m_icon;
		sf::Text m_name;
		sf::RectangleShape m_hpBar;
		sf::RectangleShape m_potentialHpBar;
		sf::RectangleShape m_hpBarPlaceholder;
		float m_maxHp = -1;
		float m_potentialHp = -1;
		float m_currHp = -1;
	};
	std::vector<HUD::CharacterFrame> m_characterFrames;
	std::vector<std::shared_ptr<PlayableObject>> m_members;
	
};