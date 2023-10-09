//
// Created by erwan on 10/6/23.
//

#include "client.h"

client::client() {
    _engine.init();
}

client::~client() {}

void client::start() {
    if (!_isBuild) build();
    while (_engine.isOpen()) {
        _engine.update();
    }
    std::cout << "engine closed!" << std::endl;
}
void client::build() {
    std::cout << "[CLIENT] Building resources..." << std::endl;
    _window = _engine.createEntity();
    _window->addComponent(new Haze::Window(800, 600));

    _ip = std::make_unique<cmp::TextInput>(_engine, "address");
    _ip->getEntity().addComponent(new Haze::Position(100, 100));

    std::cout << "[CLIENT] Building completed!" << std::endl;
    _isBuild = true;
}
