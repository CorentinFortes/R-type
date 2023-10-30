/*
** EPITECH PROJECT, 2023
** cpp r-type
** File description:
** ball.cpp
*/

#include "Ball.h"

Ball::Ball(Haze::Engine &engine, network::data_channel<protocol::data> &channel) : _engine(engine), _channel(channel)
{
}

Ball::~Ball()
{
}

void Ball::update()
{
    auto pos = dynamic_cast<Haze::Position *>(_entity->getComponent("Position"));
    auto velocity = dynamic_cast<Haze::Velocity *>(_entity->getComponent("Velocity"));
    if (pos->y <= 0 || pos->y >= 580) {
        if (pos->y <= 0)
            pos->y = 1;
        else
            pos->y = 579;
        _entity->addComponent(new Haze::Position(pos->x, pos->y));
        _entity->addComponent(new Haze::Velocity(velocity->x, velocity->y * -1, velocity->tick));
        send();
    }
    if (pos->x <= 0 || pos->y >= 780) {
        _entity->addComponent(new Haze::Velocity(5, 3, 0.05));
        _entity->addComponent(new Haze::Position(390, 190));
        send();
    }
}

void Ball::sendUpdate()
{
}

void Ball::send()
{
    auto pos = dynamic_cast<Haze::Position *>(_entity->getComponent("Position"));
    auto scale = dynamic_cast<Haze::Scale *>(_entity->getComponent("Scale"));
    auto hitbox = dynamic_cast<Haze::Hitbox *>(_entity->getComponent("Hitbox"))->hitbox.front();
    auto velocity = dynamic_cast<Haze::Velocity *>(_entity->getComponent("Velocity"));

    _channel.sendGroup(cocs_game::message::createEntity(_entity->getId()));
    _channel.sendGroup(cocs_game::message::addComponent(_entity->getId(), "Velocity", new Haze::VelocityData{velocity->x, velocity->y, velocity->tick}, sizeof(Haze::VelocityData)));
    _channel.sendGroup(cocs_game::message::addComponent(_entity->getId(), "Position", new Haze::PositionData{pos->x, pos->y}, sizeof(Haze::PositionData)));
    _channel.sendGroup(cocs_game::message::addComponent(_entity->getId(), "Scale", new Haze::ScaleData{scale->x, scale->y}, sizeof(Haze::ScaleData)));
    _channel.sendGroup(cocs_game::message::addComponent(_entity->getId(), "Hitbox", new Haze::HitboxData{hitbox}, sizeof(Haze::HitboxData)));
    _channel.sendGroup(cocs_game::message::addComponent(_entity->getId(), "Sprite", new Haze::SpriteData{"assets/sprites/ball.png"}, sizeof(Haze::SpriteData)));
    _channel.sendGroup(cocs_game::message::addComponent(_entity->getId(), "HitboxDisplay", nullptr, 0));
}

void Ball::build()
{
    _entity = _engine.createEntity();
    std::cout << "["
              << _entity->getId()
              << "] ball Created"
              << std::endl;
    _entity->addComponent(new Haze::Velocity(5, 1, 0.05));
    _entity->addComponent(new Haze::Position(390, 190));
    _entity->addComponent(new Haze::Scale(1, 1));
    _entity->addComponent(new Haze::Hitbox({{0, 0, 20, 20}}));
    send();
    std::map<std::string, Haze::Collision::CollisionInfo> mapCollision;
    mapCollision["player"] = {
            Haze::Collision::LAMBDA,
            0.1,
            [this](int a, int b) {
                std::cout << "COLLISION" << std::endl;
                if (!_entity) {
                    return;
                }
                auto velocity = dynamic_cast<Haze::Velocity *>(_entity->getComponent("Velocity"));
                auto pos = dynamic_cast<Haze::Position *>(_entity->getComponent("Position"));
                auto pos_p = dynamic_cast<Haze::Position *>(_engine.getEntity(b)->getComponent("Position"));
                _entity->addComponent(new Haze::Velocity(velocity->x * -1, velocity->y, velocity->tick * 0.9));
                send();
            }};
    _entity->addComponent(new Haze::Collision("ball", mapCollision));
}