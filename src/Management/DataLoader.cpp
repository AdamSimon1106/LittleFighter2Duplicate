#include "Management/DataLoader.h"
#include "Gameplay/Player.h"
#include "Management/ResourceManager.h"
#include "json.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

DataLoader::DataLoader(std::string pathToIndex) : m_pathToIndex(pathToIndex)
{
	parseDataIndex();
}

void DataLoader::parseDataIndex()
{
	std::ifstream file(m_pathToIndex);
	if(!file.is_open()) throw std::runtime_error("Failed to open file: " + m_pathToIndex);

	std::string line, token, type, path;
	while (std::getline(file, line)) {
		std::stringstream ss(line);
		while (ss >> token) {
			if (token == "type:") ss >> type;
			else if (token == "file:") ss >> path;
		}
		if (type == "character" && !path.empty()) {
			m_datPaths.push_back({type, path});
		}
	}
}

void DataLoader::printPaths() const
{
	for (const auto& member : m_datPaths) {
		std::cout << "type: " << member.first << " path: " << member.second << std::endl;
	}
}

bool DataLoader::loadCharacterDat()
{
	if (m_currentIndex == m_datPaths.size()) return false;
	std::string type = m_datPaths[m_currentIndex].first;
	std::string path = m_datPaths[m_currentIndex].second;
	m_currentFile = path;
	std::ifstream file(path);
	if (!file.is_open()) throw std::runtime_error("couldn't open file: " + path);
	nlohmann::json jsonData = nlohmann::json::parse(file);

	if (!jsonData.contains("name") || !jsonData["name"].is_string()) {
		throw std::runtime_error("Missing or invalid 'name' in: " + path);
	}
	if (!jsonData.contains("description") || !jsonData["description"].is_string()) {
		throw std::runtime_error("Missing or invalid 'description' in: " + path);
	}

	auto p = std::make_shared<PlayerData>();
	p->m_name = jsonData["name"].get<std::string>();
	p->m_description = jsonData["description"].get<std::string>();
	p->m_hp = jsonData["hp"].get<int>();
	p->m_speed = jsonData["speed"].get<float>();
	p->m_profilePic = std::make_shared<sf::Texture>(ResourceManager::instance().getTexture(jsonData["profile"]));
	p->m_chracterIcon = std::make_shared<sf::Texture>(ResourceManager::instance().getTexture(jsonData["icon"]));
	p->m_animationSheet = std::make_shared<sf::Texture>(ResourceManager::instance().getTexture(jsonData["animation"]));

	ResourceManager::instance().loadCharacterData(p);

	++m_currentIndex;
	return true;
}

std::string DataLoader::getCurrentlyLoadingFile() const
{
	return m_currentFile;
}
