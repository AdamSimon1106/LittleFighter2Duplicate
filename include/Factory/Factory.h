#pragma once
#include <memory>
#include <string>
#include <map>
#include <functional>
#include <SFML/System/Vector2.hpp>
#include "Objects/Object.h"
#include "Attacks/AttackBehavior.h"
class PickableObject;


template<typename T>
class Factory {
public:
    using creatorFunc = std::function<std::unique_ptr<T>(const sf::Vector2f&, const std::string&)>;
    using attackCreatorFunc = std::function<std::unique_ptr<AttackBehavior>(const std::string&, PickableObject*)>;

    static std::unique_ptr<T> create(const std::string& name, const sf::Vector2f& pos);
    static bool registerIt(const std::string& name, creatorFunc f);

    static std::unique_ptr<AttackBehavior> createAttackBehavior(const std::string& name, PickableObject* obj);
    static bool registerAttackBehavior(const std::string& name, attackCreatorFunc f);

private:
    using myMap = std::map<std::string, creatorFunc>;

    using attackMap = std::map<std::string, attackCreatorFunc>;

    static myMap& getMap() {
        static myMap m_map;
        return m_map;
    }

    static attackMap& getAttackMap() {
        static attackMap m_attackMap;
        return m_attackMap;
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

template<typename T>
inline std::unique_ptr<AttackBehavior> Factory<T>::createAttackBehavior(const std::string& name, PickableObject* obj)
{
    auto it = getAttackMap().find(name);
    if (it == getAttackMap().end())
        return nullptr;
    return it->second(name, obj);
}

template<typename T>
inline bool Factory<T>::registerAttackBehavior(const std::string& name, attackCreatorFunc f)
{
    getAttackMap().emplace(name, f);
    return true;
}





