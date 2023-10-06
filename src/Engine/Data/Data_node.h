#ifndef NODE_SCENE_H
#define NODE_SCENE_H

class Render_node;
class Engine;
class Scene;
class Data_param;
class Database;
class Glyphs;

class Loader;


class Data_node
{
public:
  //Constructor / Destructor
  Data_node(Engine* engine);
  ~Data_node();

public:
  void init();
  void reset();

  inline Engine* get_engine(){return engine;}
  inline Render_node* get_node_render(){return render_node;}

  inline Data_param* get_param_data(){return param_data;}
  inline Scene* get_sceneManager(){return sceneManager;}
  inline Database* get_dataManager(){return dataManager;}
  inline Loader* get_loaderManager(){return loaderManager;}


private:
  Engine* engine;
  Render_node* render_node;

  Data_param* param_data;
  Scene* sceneManager;
  Database* dataManager;
  Glyphs* glyphManager;

  Loader* loaderManager;
};

#endif
