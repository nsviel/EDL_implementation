#include "struct_cloud.h"


Cloud::Cloud(){
  //---------------------------

  this->pose_T = Eigen::Vector3d::Zero();
  this->pose_R = Eigen::Matrix3d::Zero();

  //---------------------------
}

void Cloud::reset(){
  //---------------------------

  this->pose_T = Eigen::Vector3d::Zero();
  this->pose_R = Eigen::Matrix3d::Zero();

  //---------------------------
}
