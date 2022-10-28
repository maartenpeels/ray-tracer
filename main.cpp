
#include "Engine/Layer.h"
#include "imgui.h"
#include "Engine/Application.h"
#include "Engine/Image.h"
#include "Engine/Timer.h"
#include "App/Renderer.h"

using namespace RayTracer;

class ExampleLayer : public Layer {
public:
    void OnUIRender() override {
        ImGui::Begin("Settings");
        ImGui::Text("Last render: %.3f ms", m_LastRenderTime);
        if (ImGui::Button("Render")) {
            Render();
        }
        ImGui::End();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::Begin("Viewport");

        m_ViewportWidth = static_cast<uint32_t>(ImGui::GetContentRegionAvail().x);
        m_ViewportHeight = static_cast<uint32_t>(ImGui::GetContentRegionAvail().y);

        auto image = m_Renderer.GetFinalImage();
        if (image) {
            ImGui::Image(reinterpret_cast<ImU64>(image->GetDescriptorSet()),
                         {(float) image->GetWidth(), (float) image->GetHeight()});
        }

        ImGui::End();
        ImGui::PopStyleVar();

        Render();
    }

    void Render() {
        Timer timer;

        m_Renderer.OnResize(m_ViewportWidth, m_ViewportHeight);
        m_Renderer.Render();

        m_LastRenderTime = timer.ElapsedMillis();
    }

private:
    Renderer m_Renderer;
    uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
    float m_LastRenderTime = 0;
};

bool g_ApplicationRunning = true;

int main(int, char **) {
    while (g_ApplicationRunning) {
        RayTracer::ApplicationSpecification spec;
        spec.Name = "RayTracing Example";

        auto *app = new RayTracer::Application(spec);
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
