//
// Created by Niels Ouvrard on 16/10/2023.
//

#include "Explosion.h"

/**
 * @brief Construct an Explosion object.
 *
 * @param engine The game engine.
 * @param channel The network data channel.
 * @param x The x-coordinate of the explosion.
 * @param y The y-coordinate of the explosion.
 */
Explosion::Explosion(Haze::Engine &engine, network::data_channel<protocol::data> &channel, float x, float y)
    : _engine(engine), _channel(channel), _x(x), _y(y)
{
}

/**
 * @brief Build the explosion entity with initial components.
 */
void Explosion::build()
{
    // Activate the time-to-destroy cooldown
    _time_to_destroyCd.Activate();

    // Create a new entity
    _entity = _engine.createEntity();

    // Add Position, Velocity, and Scale components to the entity
    _entity->addComponent(new Haze::Position(_x, _y));
    _entity->addComponent(new Haze::Velocity(0, 0, 0.1));
    _entity->addComponent(new Haze::Scale(3, 3));
}

/**
 * @brief Send messages to create and initialize the explosion entity.
 */
void Explosion::send()
{
    // Send messages to create the explosion entity
    _channel.sendGroup(RType::message::createEntity(_entity->getId()));

    // Send messages to add Position, Scale, Sprite, and Animation components
    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Position", new Haze::PositionData{_x, _y}, sizeof(Haze::PositionData)));
    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Scale", new Haze::ScaleData{3, 3}, sizeof(Haze::ScaleData)));
    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Sprite", new Haze::SpriteData{"assets/sprites/spaceship.gif"}, sizeof(Haze::SpriteData)));
    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Animation", new Haze::AnimationData{"assets/AnimationJSON/explosion.json"}, sizeof(Haze::AnimationData)));
}

/**
 * @brief Send a message to destroy the explosion entity.
 */
void Explosion::destroy()
{
    // Send a message to initiate the destruction of the explosion entity
    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Destroy", nullptr, 0));

    // Add a Destroy component to the entity
    _entity->addComponent(new Haze::Destroy());

    // Set the entity to nullptr
    _entity = nullptr;
}
