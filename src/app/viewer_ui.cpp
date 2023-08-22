#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "app/viewer.h"
#include "app/viewer_ui.h"


ViewerUi::ViewerUi(core::Window& window, Viewer& viewer) :
    Ui{ window }, mViewer{ viewer}
{
}

void ViewerUi::update()
{
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar;
    window_flags |= ImGuiWindowFlags_NoBackground;



    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("View"))
        {
            if (ImGui::MenuItem("Side Menu")) {
                mViewer.mViewerOpen = !(mViewer.mViewerOpen);
            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    /*if (mViewer.mViewerOpen) {

        ImGui::Begin("Phong Model Menu");

     

        if (ImGui::CollapsingHeader("Light Properites", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::ColorEdit3("Color", mViewer.mLight.mColor.getRawData());
            ImGui::SliderFloat("Shininess", &mViewer.mLight.mShininess, 0.0001, 10.0);
        }

        if (ImGui::CollapsingHeader("Material Properties", ImGuiTreeNodeFlags_DefaultOpen))
        {

            ImGui::ColorEdit3("Emissive Color", mViewer.mMaterial.mEmissiveColor.getRawData());
            ImGui::ColorEdit3("Ambient Color", mViewer.mMaterial.mAmbientColor.getRawData());
            ImGui::ColorEdit3("Diffuse Color", mViewer.mMaterial.mDiffuseColor.getRawData());
            ImGui::ColorEdit3("Specular Color", mViewer.mMaterial.mSpecularColor.getRawData());
        }



        

        ImGui::End();
    }*/
}
