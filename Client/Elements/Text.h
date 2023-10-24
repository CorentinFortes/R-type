//
// Created by erwan on 10/24/23.
//

#pragma once

#include "Element.h"

class Text : public Element {
public:
    void build() override;
    void update() override;

public:
    Text(Haze::Engine &engine, std::string value, std::string fontfile, Haze::Text::colorHaze color, AxisPair position = {0, 0}, AxisPair scale = {1, 1});

private:
    std::string _value;
    std::string _fontfile;
    Haze::Text::colorHaze _color;
};
