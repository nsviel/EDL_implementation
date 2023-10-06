#ifndef NODE_SCENE_H
#define NODE_SCENE_H

class Render_node;
class Engine;
class Scene;
class Database;
class Glyphs;

class Loader;


class Data_node
{
public:
  //Constructor / Destructor
  Data_node(Render_node* render_node);
  ~Data_node();

public:
  void init();
  void reset();

  inline Render_node* get_node_render(){return render_node;}
  inline Scene* get_sceneManager(){return sceneManager;}
  inline Database* get_dataManager(){return dataManager;}
  inline Loader* get_loaderManager(){return loaderManager;}

private:
  Render_node* render_node;
  Scene* sceneManager;
  Database* dataManager;
  Glyphs* glyphManager;
  Loader* loaderManager;
};

#endif
