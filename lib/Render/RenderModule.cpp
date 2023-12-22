/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Physics
*/

#include "RenderModule.hpp"

#include <vector>
#include <memory>

struct Sprite {
    sf::Sprite sprite;
    float x;
    float y;
    float width;
    float height;
    size_t draw_order;
};

void Render::run(ECS::Core &c)
{
    auto &registry = c.get_registry();
    auto &gui = c.get_gui();

    auto &positions = registry.get_components<component::Position>();
    auto &drawables = registry.get_components<component::Drawable>();
    auto &hitboxes = registry.get_components<component::HitBox>();

    std::vector<std::shared_ptr<Sprite>> sprites;

    gui.clear();

    for (size_t i = 0; i < positions.size() || i < drawables.size() || i < hitboxes.size(); ++i) {
        auto &pos = positions[i];
        auto &draw = drawables[i];
        auto &hit = hitboxes[i];

        if (pos && draw) {
            std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>();
            sprite->sprite = *draw->sprite;
            sprite->x = pos->x;
            sprite->y = pos->y;
            sprite->width = hit->width;
            sprite->height = hit->height;
            sprite->draw_order = draw->draw_order;
            sprites.push_back(sprite);
        }
    }

    std::sort(sprites.begin(), sprites.end(), [](const std::shared_ptr<Sprite> &a, const std::shared_ptr<Sprite> &b) {
        return a->draw_order < b->draw_order;
    });

    for (auto sprite : sprites) {
        gui.draw(sprite->sprite, sprite->x, sprite->y, sprite->width, sprite->height);
    }

    gui.display();
}
