#ifndef NODE_SCENE_H
#define NODE_SCENE_H

class Core_node;
class Node;
class Scene;
class Data_param;
class Database;
class Glyphs;
class Control;
class Loader;


class Data_node
{
public:
  //Constructor / Destructor
  Data_node(Node* node);
  ~Data_node();

public:
  void init();
  void reset();

  inline Node* get_node(){return node;}
  inline Core_node* get_core_node(){return core_node;}

  inline Data_param* get_param_data(){return param_data;}
  inline Scene* get_sceneManager(){return sceneManager;}
  inline Database* get_dataManager(){return dataManager;}
  inline Loader* get_loaderManager(){return loaderManager;}
  inline Control* get_controlManager(){return controlManager;}

private:
  Node* node;
  Core_node* core_node;

  Data_param* param_data;
  Scene* sceneManager;
  Database* dataManager;
  Glyphs* glyphManager;
  Control* controlManager;
  Loader* loaderManager;
};

#endif
