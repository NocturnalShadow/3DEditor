#include "entity.h"


IEntity::IEntity(const IEntity& entity)
{
    if(entity.id != 0) {
        entity.manager->AddItem(this);
    }
}

IEntity::IEntity(IEntity&& entity)
{
    if(entity.id != 0) {
        entity.manager->ReplaceItem(&entity, this);
    }
}

void EntityManager::AddItem(IEntity* item)
{
    if((item->id == 0) && (entities.count(item->id) == 0))
    {
        item->manager = this;
        item->id = unused_id;
        entities[unused_id] = item;
        ++unused_id;
    }
}

void EntityManager::ReplaceItem(IEntity* item, IEntity* with)
{
    if(item->id != 0 && with->id == 0)
    {
        with->manager = this;
        entities[item->id] = with;
        with->id = item->id;
        item->id = 0;
    }
}

IEntity* EntityManager::Item(uint item_id)
{
    if(entities.count(item_id)) {
        return entities[item_id];
    } else {
        return nullptr;
    }
}
