#pragma once

class PickableObject;   

class ObjectBaseState {
public:
    virtual ~ObjectBaseState() = default;

    virtual void enter(PickableObject& obj) = 0;
    virtual void update(PickableObject& obj, float dt) = 0;
    //virtual void exit(Object& obj) {}
};
