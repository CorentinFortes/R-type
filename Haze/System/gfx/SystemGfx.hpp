/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** System
*/

#pragma once
#include "Entity.hpp"
#include "ComponentList.hpp"
#include "ComponentGfx.hpp"
#include <vector>
#include "protocol.hpp"

namespace Haze
{
    void ScaleSystem(ComponentList *componentList, info_inputs *inputs);
    void AnimateSystem(ComponentList *componentList, info_inputs *inputs);
    void RenderSystem(ComponentList *componentList, info_inputs *inputs);
    void PullEvent(ComponentList *componentList, info_inputs *inputs);
    void DisplaySystem(ComponentList *componentList, info_inputs *inputs);
    void ClearSystem(ComponentList *componentList, info_inputs *inputs);
}