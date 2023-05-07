#ifndef VK_DATA_H
#define VK_DATA_H

#include "../../../common.h"

class Engine;


class VK_data
{
public:
  //Constructor / Destructor
  VK_data(Engine* engineManager);
  ~VK_data();

public:
  //Main functions
  Object* load_model();
  std::vector<VkVertexInputAttributeDescription> description_vertex();
  std::vector<VkVertexInputBindingDescription> description_binding();

  inline void set_list_data(std::list<Object*> value){this->list_data = value;}
  inline std::list<Object*> get_list_data(){return list_data;}

private:
  Engine* engineManager;

  std::list<Object*> list_data;
};

#endif
