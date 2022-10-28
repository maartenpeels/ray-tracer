//
// Created by Maarten Peels on 28/10/2022.
//

#include "Renderer.h"
#include "Engine/Random.h"


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
    for (uint32_t i = 0; i < m_FinalImage->GetWidth() * m_FinalImage->GetHeight(); i++) {
        m_ImageData[i] = RayTracer::Random::UInt();
        m_ImageData[i] |= 0xFF000000;
    }

    m_FinalImage->SetData(m_ImageData);
}