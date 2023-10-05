#ifndef NODE_SCENE_H
#define NODE_SCENE_H

class Render_node;
class Node;
class Scene;
class Data_param;
class Database;
class Glyphs;

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
  inline Render_node* get_render_node(){return render_node;}

  inline Data_param* get_param_data(){return param_data;}
  inline Scene* get_sceneManager(){return sceneManager;}
  inline Database* get_dataManager(){return dataManager;}
  inline Loader* get_loaderManager(){return loaderManager;}


private:
  Node* node;
  Render_node* render_node;

  Data_param* param_data;
  Scene* sceneManager;
  Database* dataManager;
  Glyphs* glyphManager;
  
  Loader* loaderManager;
};

#endif
