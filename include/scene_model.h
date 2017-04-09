#pragma once

#include "ui_item.h"
#include "scene_item.h"

#include <vector>
#include <memory>
#include <utility>


class SceneModel
{
private:
        std::vector<std::unique_ptr<UserInterfaceItem>> ui_items;
        std::vector<std::unique_ptr<SceneItem>> scene_items;

public:
    SceneModel() = default;

public:
    void AddItem(SceneItem* item) {
        scene_items.push_back(std::unique_ptr<SceneItem>(item));
    }
    void AddItem(SceneItem&& item) {
        scene_items.push_back(std::make_unique<SceneItem>(std::move(item)));
    }
    void AddUIItem(UserInterfaceItem* item) {
         ui_items.push_back(std::unique_ptr<UserInterfaceItem>(item));
    }
    void AddUIItem(UserInterfaceItem&& item) {
       ui_items.push_back(std::make_unique<UserInterfaceItem>(std::move(item)));
    }
};

