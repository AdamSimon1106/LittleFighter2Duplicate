#pragma once
#include <memory>
#include "Objects/Object.h"
#include <string>
#include <map>
#include <functional>

 

#pragma once
#include <memory>
#include <string>
#include <map>
#include <functional>
#include <SFML/System/Vector2.hpp>
#include "Objects/Object.h"

template<typename T>
class Factory {
public:
    using creatorFunc = std::function<std::unique_ptr<T>(const sf::Vector2f&, const std::string&)>;

    static std::unique_ptr<T> create(const std::string& name, const sf::Vector2f& pos);
    static bool registerIt(const std::string& name, creatorFunc f);

private:
    using myMap = std::map<std::string, creatorFunc>;

    static myMap& getMap() {
        static myMap m_map;
        return m_map;
    }
};

template<typename T>
inline std::unique_ptr<T> Factory<T>::create(const std::string& name, const sf::Vector2f& pos) {
    auto it = getMap().find(name);
    if (it == getMap().end())
        return nullptr;
    return it->second(pos, name);
}

template<typename T>
inline bool Factory<T>::registerIt(const std::string& name, creatorFunc f) {
    getMap().emplace(name, f);
    return true;
}

