#include <Specific/common.h>
#include <imgui/node/imgui_node_editor.h>

namespace ed = ax::NodeEditor;




struct Platform;
struct Renderer;

struct Application
{
    Application(const char* name);
    Application(const char* name, int argc, char** argv);
    ~Application();

    bool Create(int width = -1, int height = -1);

    int Run();

    void SetTitle(const char* title);

    bool Close();
    void Quit();

    const std::string& GetName() const;

    ImFont* DefaultFont() const;
    ImFont* HeaderFont() const;

    ImTextureID LoadTexture(const char* path);
    ImTextureID CreateTexture(const void* data, int width, int height);
    void        DestroyTexture(ImTextureID texture);
    int         GetTextureWidth(ImTextureID texture);
    int         GetTextureHeight(ImTextureID texture);

    virtual void OnStart() {}
    virtual void OnStop() {}
    virtual void OnFrame(float deltaTime) {}

    virtual ImGuiWindowFlags GetWindowFlags() const;

    virtual bool CanClose() { return true; }

private:
    void RecreateFontAtlas();

    void Frame();

    std::string                 m_Name;
    std::string                 m_IniFilename;
    std::unique_ptr<Platform>   m_Platform;
    std::unique_ptr<Renderer>   m_Renderer;
    ImGuiContext*               m_Context = nullptr;
    ImFont*                     m_DefaultFont = nullptr;
    ImFont*                     m_HeaderFont = nullptr;
};




struct Example
{

    void OnStart()
    {
        ed::Config config;
        config.SettingsFile = "Simple.json";
        m_Context = ed::CreateEditor(&config);
    }

    void OnStop()
    {
        ed::DestroyEditor(m_Context);
    }

    void OnFrame(float deltaTime)
    {
        auto& io = ImGui::GetIO();

        ImGui::Text("FPS: %.2f (%.2gms)", io.Framerate, io.Framerate ? 1000.0f / io.Framerate : 0.0f);

        ImGui::Separator();

        ed::SetCurrentEditor(m_Context);
        ed::Begin("My Editor", ImVec2(0.0, 0.0f));
        int uniqueId = 1;
        // Start drawing nodes.
        ed::BeginNode(uniqueId++);
            ImGui::Text("Node A");
            ed::BeginPin(uniqueId++, ed::PinKind::Input);
                ImGui::Text("-> In");
            ed::EndPin();
            ImGui::SameLine();
            ed::BeginPin(uniqueId++, ed::PinKind::Output);
                ImGui::Text("Out ->");
            ed::EndPin();
        ed::EndNode();
        ed::End();
        ed::SetCurrentEditor(nullptr);

        //ImGui::ShowMetricsWindow();
    }

    ed::EditorContext* m_Context = nullptr;
};
