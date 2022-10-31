//
// Created by Maarten Peels on 28/10/2022.
//

#include <cstdio>
#include "Renderer.h"
#include "Engine/Random.h"

namespace Utils {
    static uint32_t ConvertToRGBA(const glm::vec4& color) {
        auto  r = (uint8_t)(color.r * 255.0f);
        auto  g = (uint8_t)(color.g * 255.0f);
        auto  b = (uint8_t)(color.b * 255.0f);
        auto  a = (uint8_t)(color.a * 255.0f);

        return (a << 24) | (b << 16) | (g << 8) | r;
    }
}

void Renderer::OnResize(uint32_t width, uint32_t height) {
    if (m_FinalImage) {
        if (m_FinalImage->GetWidth() == width && m_FinalImage->GetHeight() == height) {
            return;
        }
        m_FinalImage->Resize(width, height);
    } else {
        m_FinalImage = std::make_shared<RayTracer::Image>(width, height, RayTracer::ImageFormat::RGBA);
    }

    delete[] m_ImageData;
    m_ImageData = new uint32_t[width * height];
}

void Renderer::Render() {
    for (uint32_t y = 0; y < m_FinalImage->GetHeight(); y++) {
        for (uint32_t x = 0; x < m_FinalImage->GetWidth(); x++) {
            glm::vec2 coord = { (float)x / (float)m_FinalImage->GetWidth(), (float)y / (float)m_FinalImage->GetHeight() };
            coord = coord * 2.0f - 1.0f; // 0 -> 1 to -1 -> 1

            glm::vec4 color = PerPixel(coord);
            color = glm::clamp(color, glm::vec4(0.0f), glm::vec4(1.0f));
            m_ImageData[x + y * m_FinalImage->GetWidth()] = Utils::ConvertToRGBA(color);
        }
    }

    m_FinalImage->SetData(m_ImageData);
}

glm::vec4 Renderer::PerPixel(glm::vec2 coord) {
    glm::vec3 rayOrigin(0.0f, 0.0f, 2.0f);
    glm::vec3 rayDirection(coord.x, coord.y, -1.0f);
//    rayDirection =` glm::normalize(rayDirection);

    float radius = 0.5f;

    // (bx^2 + by^2)t^2 + (2(axbx + ayby))t + (ax^2 + ay^2 - r^2) = 0
    // where
    // a = ray origin
    // b = ray direction (coord)
    // r = radius
    // t = hit distance

    float a = glm::dot(rayDirection, rayDirection);
    float b = 2.0f * glm::dot(rayOrigin, rayDirection);
    float c = glm::dot(rayOrigin, rayOrigin) - radius * radius;

    // Quadratic formula discriminant:
    // d = b^2 - 4ac
    float discriminant = b * b - 4.0f * a * c;

    if (discriminant < 0.0f) {
        return {0, 0, 0, 1};
    }

    // (-b +- sqrt(d)) / 2a
    float t0 = (-b + glm::sqrt(discriminant)) / (2.0f * a);
    float closestT = (-b - glm::sqrt(discriminant)) / (2.0f * a);

    glm::vec3 hitPoint = rayOrigin + rayDirection * closestT;
    glm::vec3 normal = glm::normalize(hitPoint);

    glm::vec3 lightDir = glm::normalize(glm::vec3(-1 -1 -1));

    float d = glm::max(glm::dot(normal, -lightDir), 0.0f); // same as cos(angle)

    glm::vec3 sphereColor(1, 0, 1);
    sphereColor *= d;
    return {sphereColor, 1.0f};
}
