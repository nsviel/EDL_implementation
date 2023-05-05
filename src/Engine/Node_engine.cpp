#include "Node_engine.h"

#include "Vulkan/Engine_vulkan.h"
#include "Core/Scene.h"
#include "Core/Control.h"
#include "Dimension/Dimension.h"
#include "Camera/Camera.h"

#include "../Load/Node_load.h"
#include "../GUI/Node_gui.h"


//Constructor / Destructor
Node_engine::Node_engine(){
  //---------------------------

  this->dimManager = new Dimension();
  this->engine_vulkan = new Engine_vulkan(this);
  this->sceneManager = new Scene(this);
  this->controlManager = new Control(this);
  this->cameraManager = new Camera(this);

  this->node_load = new Node_load(this);
  this->node_gui = new Node_gui(this);

  //---------------------------
}
Node_engine::~Node_engine(){
  //---------------------------

  delete engine_vulkan;
  delete dimManager;
  delete sceneManager;

  delete node_load;
  delete node_gui;

  //---------------------------
}

//Main function
void Node_engine::init(){
  //---------------------------

  dimManager->update();

  //---------------------------
}
void Node_engine::loop(){
  //---------------------------

  node_gui->loop();

  //---------------------------
}
