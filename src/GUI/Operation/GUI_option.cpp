#include "GUI_option.h"

#include "../../Engine/Node_engine.h"
#include "../../Engine/Param_engine.h"
#include "../../Node.h"


//Constructor / Destructor
GUI_option::GUI_option(Node* node){
  //---------------------------

  Node_engine* node_engine = node->get_node_engine();
  this->param_engine = node_engine->get_param_engine();
  this->width = 150;

  //---------------------------
}
GUI_option::~GUI_option(){}

//Main function
void GUI_option::design_option(){
  //---------------------------

  /*this->option_font();
  this->option_glyph();
  this->option_mode();
  this->option_parameter();*/
  this->option_color();

  //---------------------------
}
/*
//Subfunctions
void GUI_option::option_font(){
  ImGuiIO& io = ImGui::GetIO();
  //---------------------------

  static int font_selected = 0;
  ImGui::SetNextItemWidth(150);
  if(ImGui::Combo("Font size", &font_selected, "13\0 12\0")){
    ImFont* font = io.Fonts->Fonts[font_selected];
    io.FontDefault = font;
  }

  //---------------------------
  ImGui::Separator();
}
void GUI_option::option_glyph(){
  Collection* collection = sceneManager->get_selected_collection();
  ImGui::Columns(2);
  //---------------------------

  //Display grid
  Grid* gridObject = objectManager->get_object_grid();
  Glyph* grid = gridObject->get_grid();
  bool& grid_ON = grid->is_visible;
  ImGui::Checkbox("Grid", &grid_ON);
  ImGui::NextColumn();

  //Grid number of square
  static int nb_square = 4;
  ImGui::PushItemWidth(75);
  if(ImGui::DragInt("##457", &nb_square, 1, 1, 100, "%d")){
    Grid* gridObject = objectManager->get_object_grid();
    gridObject->update_grid(nb_square);
    gridObject->update_grid_sub(nb_square);
    gridObject->update_grid_plane(nb_square);
    glyphManager->update_glyph_buffer(gridObject->get_grid());
    glyphManager->update_glyph_buffer(gridObject->get_grid_sub());
    glyphManager->update_glyph_buffer(gridObject->get_grid_plane());
  }
  ImGui::NextColumn();

  //Subgrid
  Glyph* grid_sub = gridObject->get_grid_sub();
  bool& grid_sub_ON = grid_sub->is_visible;
  if(ImGui::Checkbox("Subgrid", &grid_sub_ON)){
    Glyph* grid_plane = gridObject->get_grid_plane();
    grid_plane->is_visible = grid_sub_ON;
  }
  ImGui::NextColumn();

  //Display Bounding Box
  AABB* aabbObject = objectManager->get_object_aabb();
  Glyph* aabb = aabbObject->get_glyph();
  bool& aabb_ON = aabb->is_visible;
  ImGui::Checkbox("AABB", &aabb_ON);
  ImGui::NextColumn();

  //Display normals
  Normal* normObject = objectManager->get_object_normal();
  bool* norm_visib = normObject->get_visibility();
  if(ImGui::Checkbox("Normal", norm_visib)){
    if(sceneManager->get_is_list_empty() == false){
      objectManager->set_object_visibility("normal", *norm_visib);
    }
  }
  ImGui::NextColumn();

  //Texture
  bool* with_texture = texManager->get_with_texture();
  ImGui::Checkbox("Texture##444", with_texture);
  ImGui::NextColumn();

  //Display Axis world
  Axis* axisObject = objectManager->get_object_axis();
  Glyph* axis_scene = axisObject->get_axis_scene();
  bool& axis_scene_ON = axis_scene->is_visible;
  ImGui::Checkbox("Axis world", &axis_scene_ON);
  ImGui::NextColumn();

  //Display Axis cloud
  static bool axis_cloud = true;
  if(ImGui::Checkbox("Axis cloud", &axis_cloud)){
    bool* axis_visibility = axisObject->get_axis_subset_visibility();
    *axis_visibility = axis_cloud;
    objectManager->update_glyph_collection(collection);
  }
  ImGui::NextColumn();

  //Display Axis circle
  static bool axisCircleON = false;
  if(ImGui::Checkbox("Axis circle", &axisCircleON)){
    //objectManager->obj_axisCircle(circleRadius);
    //objectManager->set_visibility("axisCircle", axisCircleON);
  }
  ImGui::NextColumn();

  //Axis circlev radius
  static float circleRadius = 1;
  ImGui::PushItemWidth(75);
  if(ImGui::DragFloat("##456", &circleRadius, 0.001, 0, 5, "%.3f")){
    //objectManager->obj_axisCircle(circleRadius);
  }
  ImGui::NextColumn();

  //Display tree
  Tree* treeObject = objectManager->get_object_tree();
  bool* tree_visible = treeObject->get_visibility();
  if(ImGui::Checkbox("Tree", tree_visible)){
    if(sceneManager->get_is_list_empty() == false){
      objectManager->set_object_visibility("tree", *tree_visible);
    }
  }
  ImGui::NextColumn();

  //Tree level
  int* tree_level = treeObject->get_tree_level();
  ImGui::PushItemWidth(75);
  if(ImGui::DragInt("##458", tree_level, 1, 1, 50, "%d")){
    Cloud* cloud = (Cloud*)collection->selected_obj;
    //treeObject->update_tree(cloud);
    //glyphManager->update_glyph_buffer(&cloud->glyphs["tree"]);
  }
  ImGui::NextColumn();

  //---------------------------
  ImGui::Columns(1);
  ImGui::Separator();
}
void GUI_option::option_mode(){
  if(ImGui::CollapsingHeader("Mode")){
    //---------------------------

    //Visualization mode
    static bool mode_visualization = false;
    if(ImGui::Checkbox("Display mode", &mode_visualization)){
      vec4* screen_color = renderManager->get_screen_color();
      Glyph* axis = objectManager->get_glyph_scene_byName("axis");
      Glyph* aabb = objectManager->get_glyph_scene_byName("aabb");
      Glyph* grid = objectManager->get_glyph_scene_byName("grid");

      if(mode_visualization == true){
        axis->is_visible = false;
        aabb->is_visible = false;
        grid->is_visible = false;
      }else{
        axis->is_visible = true;
        aabb->is_visible = true;
        grid->is_visible = true;
      }
    }

    //---------------------------
    ImGui::Separator();
  }
}
void GUI_option::option_parameter(){
  if(ImGui::CollapsingHeader("Parameters")){
    Collection* collection = sceneManager->get_selected_collection();
    Cloud* cloud = (Cloud*)collection->selected_obj;
    ImGuiStyle& style = ImGui::GetStyle();
    //---------------------------

    //cloud movement
    float* transCoef = gui_control->get_transCoef();
    ImGui::DragFloat("Translation", transCoef, 0.001, 0, 100, "%.4f m");
    float* rotatDegree = gui_control->get_rotatDegree();
    ImGui::DragFloat("Rotation", rotatDegree, 0.5, 0, 90, "%.4f °");

    //Point cloud scaling
    static float scale = 1.0f;
    ImGui::SetNextItemWidth(75);
    if(ImGui::DragFloat("Scale", &scale, 0.01, 0.1, 100, "%.2f x")){
      if(!sceneManager->get_is_list_empty()){
        Transformation transformManager;
        for(int i=0; i<collection->list_obj.size(); i++){
          Cloud* cloud = (Cloud*)collection->get_obj(i);
          transformManager.make_scaling(cloud, scale);
          sceneManager->update_buffer_location(cloud);
        }
      }
    }

    //Point shape
    static int point_shape = 0;
    if(ImGui::Combo("Point shape", &point_shape, "Quad\0Circle\0")){
      if(point_shape == 0){
        glDisable(GL_POINT_SMOOTH);
      }
      else if(point_shape == 1){
        glEnable(GL_POINT_SMOOTH);
      }
    }

    //Draw type
    static int draw_type = 0;
    if(collection != nullptr){
      if(cloud->draw_type_name == "point"){
        draw_type = 0;
      }
      if(cloud->draw_type_name == "line"){
        draw_type = 1;
      }
      if(cloud->draw_type_name == "triangle"){
        draw_type = 2;
      }
      if(cloud->draw_type_name == "quad"){
        draw_type = 3;
      }
    }
    if(ImGui::Combo("Draw type", &draw_type, "Point\0Line\0Triangle\0Quad\0")){
      if(draw_type == 0){
        cloud->draw_type_name = "point";
      }
      else if(draw_type == 1){
        cloud->draw_type_name = "line";
      }
      else if(draw_type == 2){
        cloud->draw_type_name = "triangle";
      }
      else if(draw_type == 3){
        cloud->draw_type_name = "quad";
      }
    }

    //Point size
    ImGui::Columns(2);
    ImGui::AlignTextToFramePadding();
    ImGui::Text("Points size ");
    ImGui::NextColumn();
    ImGui::PushButtonRepeat(true);
    static int point_size = 1;
    if(cloud != nullptr){
      point_size = cloud->draw_point_size;
    }
    if (ImGui::ArrowButton("##left", ImGuiDir_Left) && cloud != nullptr){
      cloud->draw_point_size--;

      if(cloud->draw_point_size <= 1){
        cloud->draw_point_size = 1;
      }
    }
    ImGui::SameLine(0.0f, style.ItemInnerSpacing.x);
    if (ImGui::ArrowButton("##right", ImGuiDir_Right) && cloud != nullptr){
      cloud->draw_point_size++;

      point_size = cloud->draw_point_size;
    }
    ImGui::PopButtonRepeat();
    ImGui::SameLine();
    ImGui::Text("%d", point_size);
    ImGui::NextColumn();

    //Normals size
    Normal* normObject = objectManager->get_object_normal();
    ImGui::AlignTextToFramePadding();
    ImGui::Text("Normal size ");
    ImGui::NextColumn();
    static int cpt_nor = 1;
    ImGui::PushButtonRepeat(true);
    if(ImGui::ArrowButton("##left_n", ImGuiDir_Left)){
      //Change normal size value
      cpt_nor--;
      if(cpt_nor <= 1){
        cpt_nor = 1;
      }

      //Apply new normal size value
      int* size = normObject->get_size();
      *size = cpt_nor;
      objectManager->update_glyph_collection(collection);
    }
    ImGui::SameLine(0.0f, style.ItemInnerSpacing.x);
    if(ImGui::ArrowButton("##right_n", ImGuiDir_Right)){
      //Change normal size value
      cpt_nor++;

      //Apply new normal size value
      int* size = normObject->get_size();
      *size = cpt_nor;
      objectManager->update_glyph_collection(collection);
    }
    ImGui::PopButtonRepeat();
    ImGui::SameLine();
    ImGui::Text("%d", cpt_nor);
    ImGui::Columns(1);

    //---------------------------
    ImGui::Separator();
  }
}*/
void GUI_option::option_color(){
  if(ImGui::CollapsingHeader("Colors")){
    //---------------------------

    //Background color
    vec4* screen_color = &param_engine->background_color;
    ImGui::SetNextItemWidth(width);
    ImGui::ColorEdit4("Background", (float*)screen_color);
/*
    //Grid color
    ImGui::SetNextItemWidth(width);
    Grid* gridObject = objectManager->get_object_grid();
    vec4* grid_color = gridObject->get_grid_color();
    if(ImGui::ColorEdit4("Grid", (float*)grid_color)){
      glyphManager->update_glyph_color(gridObject->get_grid(), *grid_color);
    }

    //Bounding box color
    ImGui::SetNextItemWidth(width);
    AABB* aabbObject = objectManager->get_object_aabb();
    vec4* aabb_color = aabbObject->get_color();
    if(ImGui::ColorEdit4("AABB", (float*)aabb_color)){
      glyphManager->update_glyph_color(aabbObject->get_glyph(), *aabb_color);
    }

    //Uniform collection color
    if(collection != nullptr){
      vec4 cloud_color = collection->unicolor;

      ImGui::SetNextItemWidth(width);
      if(ImGui::ColorEdit4("Point cloud", (float*)&cloud_color, ImGuiColorEditFlags_AlphaBar)){
        if(!sceneManager->get_is_list_empty()){
          colorManager->set_color_new(collection, cloud_color);
        }
      }
    }
*/
    //---------------------------
    ImGui::Separator();
  }
}