
#include "Engine/Layer.h"
#include "imgui.h"
#include "Engine/Application.h"

class ExampleLayer : public lve::Layer {
public:
    void OnUIRender() override {
        ImGui::Begin("Hello");
        ImGui::Button("Button");
        ImGui::End();
    }
};

bool g_ApplicationRunning = true;

int main(int, char**)
{
    while (g_ApplicationRunning)
    {
        lve::ApplicationSpecification spec;
        spec.Name = "RayTracing Example";

        auto* app = new lve::Application(spec);
        app->PushLayer<ExampleLayer>();
        app->SetMenubarCallback([app]() {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Exit")) {
                    app->Close();
                }
                ImGui::EndMenu();
            }
        });

        app->Run();
        delete app;
    }

    return 0;
}
