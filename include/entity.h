#pragma once

#include <map>

#include <QtGlobal>

class EntityManager;
class IEntity
{
    friend class EntityManager;
private:
    EntityManager* manager = nullptr;
    uint id = 0;

public:
    IEntity() = default;

protected:
    IEntity(const IEntity& entity);
    IEntity(IEntity&& entity);

public:
    virtual ~IEntity()  { }

public:
    uint Id() const {
        return id;
    }
};

class EntityManager
{
private:
    std::map<uint, IEntity*> entities;
    uint unused_id  = 1;

public:
    EntityManager() = default;

public:
    uint AddItem(IEntity* item);
    uint ReplaceItem(IEntity* item, IEntity* with);
    IEntity* Item(uint item_id);
};
