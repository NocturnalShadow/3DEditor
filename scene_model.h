#pragma once

#include "ui_item.h"
#include "scene_item.h"

#include <map>
#include <memory>
#include <utility>


class SceneModel
{
private:
        std::map<uint, std::unique_ptr<UserInterfaceItem>> ui_items;
        std::map<uint, std::unique_ptr<SceneItem>> scene_items;

public:
    SceneModel() = default;

public:
    void AddItem(uint item_id, SceneItem* item) {
        scene_items[item_id] = std::unique_ptr<SceneItem>(item);
    }
    void AddItem(uint item_id, SceneItem&& item) {
       scene_items[item_id] = std::make_unique<SceneItem>(std::move(item));
    }
    void AddUIItem(uint item_id, UserInterfaceItem* item) {
        ui_items[item_id] = std::unique_ptr<UserInterfaceItem>(item);
    }
    void AddUIItem(uint item_id, UserInterfaceItem&& item) {
       ui_items[item_id] = std::make_unique<UserInterfaceItem>(std::move(item));
    }

    SceneItem& Item(uint item_id) {
        return *scene_items.at(item_id);
    }
};

