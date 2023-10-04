/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** System
*/

#include <chrono>
#include "SystemCore.hpp"

namespace Haze
{
    void MoveSystem(ComponentList *componentList)
    {
        for (int i = 0; i < componentList->getSize(); i++)
        {
            if (componentList->getComponent("Position", i) != nullptr && componentList->getComponent("Velocity", i) != nullptr)
            {
                auto position = static_cast<Position *>(componentList->getComponent("Position", i));
                auto velocity = static_cast<Velocity *>(componentList->getComponent("Velocity", i));
                position->oldX = position->x;
                position->oldY = position->y;
                position->x += velocity->x;
                position->y += velocity->y;
            }
        }
    }

    void CollisionHandling(ComponentList *componentList, int i, int j)
    {
        if (componentList->getComponent("Collision", i) &&
            componentList->getComponent("Collision", j))
        {
            auto collision1 = static_cast<Collision *>(componentList->getComponent("Collision", i));
            auto collision2 = static_cast<Collision *>(componentList->getComponent("Collision", j));
            if (collision1->behavior.find(collision2->scene) == collision1->behavior.end() ||
                collision2->behavior.find(collision1->scene) == collision2->behavior.end())
                return;
            Collision::CollisionInfo *info1 = &(collision1->behavior[collision2->scene]);
            Collision::CollisionInfo *info2 = &(collision2->behavior[collision1->scene]);
            if ((info1->type & Collision::CollisionType::LAMBDA) != 0)
            {
                if (std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - info1->lastCollision).count() > info1->tics)
                {
                    info1->lastCollision = std::chrono::high_resolution_clock::now();
                    info1->onCollision(i, j);
                }
            }
            if ((info2->type & Collision::CollisionType::LAMBDA) != 0)
            {
                if (std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - info2->lastCollision).count() > info2->tics)
                {
                    info2->lastCollision = std::chrono::high_resolution_clock::now();
                    info2->onCollision(j, i);
                }
            }
        }
    }

    bool isColiding(std::vector<Hitbox::floatRect> hitbox1, std::vector<Hitbox::floatRect> hitbox2, Scale *s1, Scale *s2, Position *pos1, Position *pos2)
    {
        for (auto rect1 : hitbox1)
        {
            Hitbox::floatRect tmp1 = {
                static_cast<int>(rect1.x * s1->x + pos1->x),
                static_cast<int>(rect1.y * s1->y + pos1->y),
                static_cast<int>(rect1.width * s1->x),
                static_cast<int>(rect1.height * s1->y)};

            for (auto rect2 : hitbox2)
            {
                Hitbox::floatRect tmp2 = {
                    static_cast<int>(rect2.x * s2->x + pos2->x),
                    static_cast<int>(rect2.y * s2->y + pos2->y),
                    static_cast<int>(rect2.width * s2->x),
                    static_cast<int>(rect2.height * s2->y)};
                if (tmp1.x < tmp2.x + tmp2.width &&
                    tmp1.x + tmp1.width > tmp2.x &&
                    tmp1.y < tmp2.y + tmp2.height &&
                    tmp1.y + tmp1.height > tmp2.y)
                {
                    return true;
                }
            }
        }
        return false;
    }

    void CollisionSystem(ComponentList *componentList)
    {
        for (int i = 0; i < componentList->getSize(); i++)
        {
            if (componentList->getComponent("Position", i) &&
                componentList->getComponent("Hitbox", i) &&
                componentList->getComponent("Scale", i))
            {
                auto position1 = static_cast<Position *>(componentList->getComponent("Position", i));
                auto size1 = static_cast<Hitbox *>(componentList->getComponent("Hitbox", i));
                auto scale1 = static_cast<Scale *>(componentList->getComponent("Scale", i));
                for (int j = 0; j < componentList->getSize(); j++)
                {
                    if (i == j)
                        continue;
                    if (componentList->getComponent("Position", j) &&
                        componentList->getComponent("Hitbox", j) &&
                        componentList->getComponent("Scale", i))
                    {
                        auto position2 = static_cast<Position *>(componentList->getComponent("Position", j));
                        auto size2 = static_cast<Hitbox *>(componentList->getComponent("Hitbox", j));
                        auto scale2 = static_cast<Scale *>(componentList->getComponent("Scale", j));
                        if (isColiding(size1->hitbox, size2->hitbox, scale1, scale2, position1, position2))
                        {
                printf("test\n");
                            CollisionHandling(componentList, i, j);
                        }
                    }
                }
            }
        }
    }

    void DestroyEntity(ComponentList *componentList)
    {
        for (int i = 0; i < componentList->getSize(); i++)
        {
            if (componentList->getComponent("LifeTime", i) != nullptr)
            {
                auto lifeTime = static_cast<LifeTime *>(componentList->getComponent("LifeTime", i));
                lifeTime->tics++;
                if (lifeTime->tics >= lifeTime->lifeTime)
                {
                    componentList->removeEntity(i);
                }
            }
        }
    }
}