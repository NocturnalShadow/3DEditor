#pragma once

#include "scene_item.h"

#include <map>
#include <memory>
#include <utility>


class SceneModel
{
private:
        std::map<std::string, std::unique_ptr<SceneItem>> items;

public:
    SceneModel() = default;

public:
    void AddItem(std::string item_name, SceneItem* item) {
        items[item_name] = std::unique_ptr<SceneItem>(item);
    }
    void AddItem(const std::string& item_name, SceneItem&& item) {
       items[item_name] = std::make_unique<SceneItem>(std::move(item));
    }

    SceneItem& Item(const std::string item_name) {
        return *items.at(item_name);
    }
};

