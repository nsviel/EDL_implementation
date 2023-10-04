#ifndef HEATMAP_H
#define HEATMAP_H

//#include "../common.h"

class Scene;
class Attribut;
class Colormap;
class GPU_data;


class Heatmap
{
public:
  //Constructor / Destructor
  Heatmap();
  ~Heatmap();

public:
  //Main functions
  void make_col_heatmap(Set* set);
  void make_cloud_heatmap(Object* object);
  void make_heatmap_all(bool heatAll);

  //Specific mode functions
  void mode_height(Object* object);
  void mode_intensity(Object* object);
  void mode_distance(Object* object);
  void mode_cosIt(Object* object);
  void mode_It(Object* object);

  //Heatmap functions
  void heatmap_set(Object* object, vector<float>& v_in);
  void heatmap_unset(Object* object);

  //Setters / Getters
  inline int* get_heatmap_mode(){return &heatmap_mode;}
  inline bool* get_is_normalization(){ return &is_normalization;}
  inline vec2* get_range_normalization(){return &range_norm;}
  inline vec2* get_range_height(){return &range_height;}
  inline vec2* get_range_intensity(){return &range_intensity;}
  inline Colormap* get_colormapManager(){return colormapManager;}

private:
  Colormap* colormapManager;

  vec2 range_norm;
  vec2 range_height;
  vec2 range_intensity;
  bool is_normalization;
  int heatmap_mode;
};

#endif
