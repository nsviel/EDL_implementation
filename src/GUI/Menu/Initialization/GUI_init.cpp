#include "GUI_init.h"

#include "../../Node_gui.h"

#include "../../../Engine/Node_engine.h"
#include "../../../Data/Node_data.h"
#include "../../../Data/Scene/Scene.h"
#include "../../../Load/Node_load.h"
#include "../../../Load/Processing/Loader.h"
#include "../../../Operation/Transformation/Transformation.h"
#include "../../../Specific/File/Directory.h"
#include "../../../Specific/File/Info.h"


//Constructor / Destructor
GUI_init::GUI_init(Node_gui* node_gui){
  //---------------------------

  Node_load* node_load = node_gui->get_node_load();

  this->loaderManager = node_load->get_loaderManager();
  this->transformManager = new Transformation();

  //---------------------------
  this->init_init();
  this->construst_tree();
}
GUI_init::~GUI_init(){}

//Main functions
void GUI_init::design_init(){
  //---------------------------

  this->operation_option();
  this->treeview();

  //---------------------------
}
void GUI_init::init_init(){
  //---------------------------

  this->init.remove_old = true;
  this->init.scale = 1;

  //Open accepted formats
  this->init.accepted_format.push_back("pts");
  this->init.accepted_format.push_back("obj");
  this->init.accepted_format.push_back("ply");
  this->init.accepted_format.push_back("xyz");
  this->init.accepted_format.push_back("cbor");
  this->init.accepted_format.push_back("pcap");
  this->init.accepted_format.push_back("ptx");
  this->init.accepted_format.push_back("csv");
  this->init.accepted_format.push_back("las");
  this->init.accepted_format.push_back("laz");

  //Custom folder tree
  this->init.vec_path_folder.push_back("../media");

  //Custom file leaf
  //this->init.vec_path_file.push_back("../media/dragon.ply");

  //---------------------------
}

//Operation on loaded cloud
void GUI_init::operation_option(){
  //---------------------------

  //Point cloud scaling
  ImGui::SetNextItemWidth(100);
  ImGui::DragFloat("Scale##4567", &init.scale, 0.1, 0.1, 100, "%.2f x");
  ImGui::SameLine();

  //Remove old clouds
  ImGui::Checkbox("Remove##222", &init.remove_old);

  //---------------------------
}
void GUI_init::operation_new_object(Object* object){
  if(object == nullptr) return;
  //---------------------------

  //transformManager->make_scaling(object, init.scale);

  //---------------------------
}

//Custom scene
void GUI_init::build_custom_scene(vector<vector<Tree_node*>>& nodes_path_vec){
  //---------------------------

  //Scene folder
  /*vector<Tree_node*> root_scene;
  Tree_node* node = new Tree_node();
  node->name = "scene";
  node->type = "Folder";
  node->end_folder = true;
  node->leaf_nb = 3;
  node->leaf_idx = 1;
  node->already_open = true;
  root_scene.push_back(node);

  //Scene 1 -> example of custom scene integration in tree
  /*node = new Tree_node();
  node->name = "Rocks";
  node->leaf_nb = 0;
  node->type = "scene_1";
  root_scene.push_back(node);*/

//  nodes_path_vec.push_back(root_scene);

  //---------------------------
}
void GUI_init::build_scene_1(){
  //---------------------------

  //Object* rock = loaderManager->load_collection("/home/aeter/Desktop/Point_cloud/obj/rock/rock.obj");
  //transformManager->make_translation(rock, vec3(2-4*i, 0, 0));
  //sceneManager->update_collection_location(rock);

  //---------------------------
}

//Tree view
void GUI_init::treeview(){
  //---------------------------

  static ImGuiTableFlags flags = ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterH | ImGuiTableFlags_Resizable | ImGuiTableFlags_RowBg | ImGuiTableFlags_NoBordersInBody;
  if (ImGui::BeginTable("init_tree", 3, flags)){
    // The first column will use the default _WidthStretch when ScrollX is Off and _WidthFixed when ScrollX is On
    ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_NoHide, 175);
    ImGui::TableSetupColumn("Size", ImGuiTableColumnFlags_WidthFixed, 75);
    ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_WidthFixed, 75);
    ImGui::TableHeadersRow();

    //Display pre-built trees
    this->display_node_root(nodes_root);
    for(int i=0; i<nodes_path_vec.size(); i++){
      this->display_node(nodes_path_vec[i][0], nodes_path_vec[i]);
    }

    ImGui::EndTable();
  }

  //---------------------------
}
void GUI_init::construst_tree(){
  this->nodes_path_vec.clear();
  //---------------------------

  //Construct init path nodes for specific cloud locations
  this->construct_node_root(init.vec_path_file, nodes_root);

  //Set a node for specific scene construction
  this->build_custom_scene(nodes_path_vec);

  //Construct predefined init path nodes
  for(int i=0; i<init.vec_path_folder.size(); i++){
    vector<Tree_node*> nodes_path;
    this->construct_node(init.vec_path_folder[i], nodes_path);
    this->nodes_path_vec.push_back(nodes_path);
  }

  //---------------------------
}
void GUI_init::construct_node(string path, vector<Tree_node*>& nodes){
  if(path != ""){
    //---------------------------

    //Save root
    Tree_node* node = new Tree_node();
    node->name = get_filename_from_path(path);
    node->type = get_type_from_path(path);
    node->path = path;
    node->size = get_file_size(path);
    nodes.push_back(node);

    //Recussively check all child leafs
    this->node_child_scan(path, nodes, node);

    //---------------------------
  }
}
void GUI_init::construct_node_root(vector<string>& vec_path, vector<Tree_node*>& nodes){
  //---------------------------

  for(int i=0; i<vec_path.size(); i++){
    if(vec_path[i] != ""){
      Tree_node* node = new Tree_node();

      node->name = get_filename_from_path(vec_path[i]);
      node->type = get_type_from_path(vec_path[i]);
      node->path = vec_path[i];
      node->size = get_file_size(vec_path[i]);
      node->leaf_nb = 1;
      node->leaf_idx = 1;
      node->already_open = true;
      node->end_folder = true;

      nodes.push_back(node);
    }
  }

  //---------------------------
}
void GUI_init::node_child_scan(string path, vector<Tree_node*>& nodes, Tree_node* parent){
  vector<string> list_path = list_all_path(path);
  //---------------------------

  bool is_sub_folder = false;
  int id = nodes.size();
  parent->leaf_nb = list_path.size();
  parent->leaf_idx = id;
  parent->already_open = true;

  for(int i=0; i<list_path.size(); i++){
    string path_file = list_path[i];

    Tree_node* node = new Tree_node();
    node->name = get_filename_from_path(path_file);
    node->type = get_type_from_path(path_file);
    node->path = path_file;

    if(node->type != "Folder"){
      if(check_file_format(path_file)){
        node->leaf_nb = 0;
        node->size = get_file_size(path_file);
        nodes.push_back(node);
      }else{
        parent->leaf_nb--;
        delete node;
      }
    }else{
      is_sub_folder = true;
      node->leaf_nb = 1;
      nodes.push_back(node);
    }
  }

  if(is_sub_folder){
    parent->end_folder = false;
  }else{
    parent->end_folder = true;
  }

  //---------------------------
}
void GUI_init::display_node(Tree_node* node, vector<Tree_node*>& all_nodes){
  if(all_nodes.size() != 0){
    //---------------------------

    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    const bool is_folder = (node->leaf_nb > 0);
    if(is_folder){
      ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanFullWidth;
      bool open = ImGui::TreeNodeEx(node->name.c_str(), node_flags);
      if(ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)){
        if(node->already_open == false){
          this->node_child_scan(node->path, all_nodes, node);
        }
        this->open_selection(node);
      }
      ImGui::TableNextColumn();
      ImGui::TextDisabled("--");
      ImGui::TableNextColumn();
      ImGui::TextUnformatted(node->type.c_str());
      if(open){
        if(node->already_open == false){
          this->node_child_scan(node->path, all_nodes, node);
        }
        for(int i=0; i<node->leaf_nb; i++){
          int id = node->leaf_idx + i;
          display_node(all_nodes[id], all_nodes);
        }
        ImGui::TreePop();
      }
    }
    else if(node->type != "Folder"){
      ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_SpanFullWidth;
      ImGui::TreeNodeEx(node->name.c_str(), node_flags);
      if(ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)){
        this->open_selection(node);
      }
      ImGui::TableNextColumn();
      ImGui::Text("%.1f MB", node->size);
      ImGui::TableNextColumn();
      ImGui::TextUnformatted(node->type.c_str());
    }

    //---------------------------
  }
}
void GUI_init::display_node_root(vector<Tree_node*>& all_nodes){
  //---------------------------

  for(int i=0; i<all_nodes.size(); i++){
    Tree_node* node = all_nodes[i];

    ImGui::TableNextRow();
    ImGui::TableNextColumn();

    ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_SpanFullWidth;
    ImGui::TreeNodeEx(node->name.c_str(), node_flags);
    if(ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)){
      this->open_selection(node);
    }
    ImGui::TableNextColumn();
    ImGui::Text("%.1f MB", node->size);
    ImGui::TableNextColumn();
    ImGui::TextUnformatted(node->type.c_str());
  }

  //---------------------------
}
bool GUI_init::check_file_format(string path){
  string format = get_format_from_path(path);
  //---------------------------

  for(int i=0; i<init.accepted_format.size(); i++){
    if(format == init.accepted_format[i]){
      return true;
    }
  }

  //---------------------------
  return false;
}
void GUI_init::open_selection(Tree_node* node){
  //---------------------------

  if(init.remove_old){
    //sceneManager->remove_collection_all();
  }

  if(node->type == "File"){
    Object* object = loaderManager->load_object(node->path);
    this->operation_new_object(object);
  }
  /*else if(node->type == "Folder" && node->end_folder){
    if(pathManager->check_folder_format(node->path, "ply")){
      Object* object;

      if(with_onthefly == false){
        object = pathManager->loading_directory_frame(node->path);
      }else{
        object = pathManager->loading_onthefly(node->path);
      }

      this->operation_new_collection(object);
    }
  }*/
  else if(node->type == "scene_1"){
    this->build_scene_1();
  }

  //---------------------------
}
