//
// Created by Maarten Peels on 27/10/2022.
//

#ifndef LGE_LAYER_H
#define LGE_LAYER_H

namespace RayTracer {
    class Layer
    {
    public:
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}

        virtual void OnUpdate(float ts) {}
        virtual void OnUIRender() {}
    };
}

#endif //LGE_LAYER_H
