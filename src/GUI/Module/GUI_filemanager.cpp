#include "GUI_filemanager.h"

#include "../Node_gui.h"


//Constructor / Destructor
GUI_filemanager::GUI_filemanager(Node_gui* node_gui){
  //---------------------------



  //---------------------------
}
GUI_filemanager::~GUI_filemanager(){}

//Main function
void GUI_filemanager::tree_view(){
  //---------------------------

  static ImGuiTableFlags flags;
  //flags |= ImGuiTableFlags_BordersV;
  flags |= ImGuiTableFlags_BordersOuterH;
  //flags |= ImGuiTableFlags_SizingFixedFit;
  flags |= ImGuiTableFlags_RowBg;
  flags |= ImGuiTableFlags_NoBordersInBody;

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::BeginTable("data_view", 3, flags);

    // Simple storage to output a dummy file-system.
    struct MyTreeNode{
      const char*     Name;
      const char*     Type;
      int             Size;
      int             ChildIdx;
      int             ChildCount;
      static void DisplayNode(const MyTreeNode* node, const MyTreeNode* all_nodes){
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        const bool is_folder = (node->ChildCount > 0);
        if (is_folder){
          bool open = ImGui::TreeNodeEx(node->Name, ImGuiTreeNodeFlags_SpanFullWidth);
          ImGui::TableNextColumn();
          ImGui::TextDisabled("--");
          ImGui::TableNextColumn();
          ImGui::TextUnformatted(node->Type);
          if (open){
            for (int child_n = 0; child_n < node->ChildCount; child_n++)
              DisplayNode(&all_nodes[node->ChildIdx + child_n], all_nodes);
            ImGui::TreePop();
          }
        }
        else{
          ImGui::TreeNodeEx(node->Name, ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_SpanFullWidth);
          ImGui::TableNextColumn();
          ImGui::Text("%d", node->Size);
          ImGui::TableNextColumn();
          ImGui::TextUnformatted(node->Type);
        }
      }
    };
    static const MyTreeNode nodes[] ={
      { "Root",                         "Folder",       -1,       1, 3    }, // 0
      { "Music",                        "Folder",       -1,       4, 2    }, // 1
      { "Textures",                     "Folder",       -1,       6, 3    }, // 2
      { "desktop.ini",                  "System file",  1024,    -1,-1    }, // 3
      { "File1_a.wav",                  "Audio file",   123000,  -1,-1    }, // 4
      { "File1_b.wav",                  "Audio file",   456000,  -1,-1    }, // 5
      { "Image001.png",                 "Image file",   203128,  -1,-1    }, // 6
      { "Copy of Image001.png",         "Image file",   203256,  -1,-1    }, // 7
      { "Copy of Image001 (Final2).png","Image file",   203512,  -1,-1    }, // 8
    };
    MyTreeNode::DisplayNode(&nodes[0], nodes);

  ImGui::EndTable();
  ImGui::PopStyleVar();



  //---------------------------
}
