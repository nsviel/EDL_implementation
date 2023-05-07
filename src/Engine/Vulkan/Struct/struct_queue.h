#ifndef STRUCT_QUEUE_H
#define STRUCT_QUEUE_H

#include "../../../common.h"


struct struct_queueFamily_indices {
  std::optional<uint32_t> family_graphics;
  std::optional<uint32_t> family_presentation;
  bool is_complete() {
    return family_graphics.has_value() && family_presentation.has_value();
  }
};


#endif
