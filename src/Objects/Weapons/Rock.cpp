#include "Objects/Weapons/Rock.h"

Rock::Rock(const sf::Vector2f pos, const std::string& name)
	:Weapon(pos, name)
{
    Animation rockAnim(
        getTexture(),    // מניח שירשת פונקציית getTexture()
        0, 0,          // x, y – התחלת האנימציה
        58, 58,          // רוחב וגובה פריים
        1,               // מספר פריימים
        0.15f            // זמן בין פריימים
    );

    setAnimation(rockAnim);
}

bool Rock::m_registered = Factory<PickableObject>::registerIt("r", [](const sf::Vector2f& pos, const std::string& name) {
    return std::make_unique<Rock>(pos, name);
    });