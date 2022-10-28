//
// Created by Maarten Peels on 28/10/2022.
//

#ifndef RAY_TRACER_RENDERER_H
#define RAY_TRACER_RENDERER_H

#include "Engine/Image.h"
#include <memory>

class Renderer {
public:
    Renderer() = default;

    void OnResize(uint32_t width, uint32_t height);
    void Render();

    std::shared_ptr<RayTracer::Image> GetFinalImage() const { return m_FinalImage; }
private:
    std::shared_ptr<RayTracer::Image> m_FinalImage;
    uint32_t *m_ImageData = nullptr;
};


#endif //RAY_TRACER_RENDERER_H
