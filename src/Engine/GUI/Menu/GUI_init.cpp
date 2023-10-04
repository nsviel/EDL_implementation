#include "GUI_init.h"
#include "Initialization/GUI_tree.h"

#include "../Node_gui.h"

#include "../../Core/Node_core.h"
#include "../../Data/Node_data.h"
#include "../../Data/Scene/Scene.h"
#include "../../Load/Node_load.h"
#include "../../Load/Processing/Loader.h"
#include <Operation/Transformation/Transformation.h>
#include <Specific/File/Directory.h>
#include <Specific/File/Info.h>


//Constructor / Destructor
GUI_init::GUI_init(Node_gui* node_gui){
  //---------------------------

  Node_data* node_data = node_gui->get_node_data();
  Node_load* node_load = node_gui->get_node_load();

  this->sceneManager = node_data->get_sceneManager();
  this->loaderManager = node_load->get_loaderManager();
  this->transformManager = new Transformation();
  this->gui_tree = new GUI_tree(this);

  //---------------------------
  this->init_init();
}
GUI_init::~GUI_init(){}

//Main functions
void GUI_init::design_init(){
  //---------------------------

  this->design_option();
  gui_tree->design_tree();

  //---------------------------
}
void GUI_init::design_option(){
  //---------------------------

  //Point cloud scaling
  ImGui::SetNextItemWidth(100);
  ImGui::DragFloat("Scale##4567", &init.scale, 0.1, 0.1, 100, "%.2f x");
  ImGui::SameLine();

  //Remove old clouds
  ImGui::Checkbox("Remove##222", &init.remove_old);

  //---------------------------
}

//Subfunction
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
  this->init.vec_path_folder.push_back("../media/point_cloud");

  //Custom file leaf
  //this->init.vec_path_file.push_back("../media/dragon.ply");

  //---------------------------
  gui_tree->construct_tree(&init);
}
void GUI_init::load_config_file(){
  //---------------------------



  //---------------------------
}
void GUI_init::operation_new_object(string path){
  //---------------------------

  Object* object = loaderManager->load_object(path);
  if(object == nullptr) return;

  if(init.remove_old){
    sceneManager->empty_scene_set();
  }

  transformManager->make_scaling(object, init.scale);

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
