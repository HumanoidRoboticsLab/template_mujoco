/**
 *  @file template.hpp
 *  @author: JunYoung Kim / lgkimjy
 *  @from: Cognitive & Collaborative Robotics Research Group
 * 	      @ Korea Institute of Science and Technology (KIST)
 *  @date: 2023.07.24
 *  @brief: Template header of using MuJoCo Simulate.cc
 **/

#include <iostream>
#include <vector>
#include <algorithm>

#include <Eigen/Dense>

#include "simulate.h"
#include "lodepng.h"
#include <mujoco/mjdata.h>
#include <mujoco/mjvisualize.h>
#include <mujoco/mjxmacro.h>
#include <mujoco/mujoco.h>
#include "platform_ui_adapter.h"
#include "array_safety.h"

using namespace std;
using namespace Eigen;

class TEST
{
    public:
    TEST() { cout << "Construtor" << endl; };
    ~TEST() { cout << "Destrutor" << endl;};
    private:
};