//
// Created by Maarten Peels on 28/10/2022.
//

#include "Random.h"

namespace RayTracer {
    std::mt19937 Random::s_RandomEngine;
    std::uniform_int_distribution<std::mt19937::result_type> Random::s_Distribution;
}