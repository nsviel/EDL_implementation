#include "Engine.h"

#include "Core/Node_engine.h"
#include "Load/Node_load.h"
#include "GUI/Node_gui.h"
#include "Data/Node_data.h"
#include "Operation/Node_operation.h"


//Constructor / Destructor
Engine::Engine(){
  //---------------------------

  this->node_ope = new Node_operation(this);
  this->node_engine = new Node_engine(this);
  this->node_data = new Node_data(this);
  this->node_load = new Node_load(this);
  this->node_gui = new Node_gui(this);

  //---------------------------
}
Engine::~Engine(){
  //---------------------------

  delete node_engine;
  delete node_load;
  delete node_gui;
  delete node_data;

  //---------------------------
}

void Engine::program(Window_manager* window){
  //---------------------------

  this->init(window);
  this->loop();
  this->exit();

  //---------------------------
}
void Engine::init(Window_manager* window){
  //---------------------------

  node_engine->init(window);
  node_data->init();
  node_gui->init();
  node_engine->loop_start();

  //---------------------------
}
void Engine::loop(){
  //---------------------------

  node_gui->loop();

  //---------------------------
}
void Engine::exit(){
  //---------------------------

  node_engine->exit();

  //---------------------------
}
void Engine::reset(){
  //---------------------------

  node_engine->reset();
  node_data->reset();

  //---------------------------
}
