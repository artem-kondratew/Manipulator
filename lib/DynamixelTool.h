/*******************************************************************************
* Copyright 2018 ROBOTIS CO., LTD.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/* Authors: Taehun Lim (Darby) */

#ifndef DYNAMIXEL_TOOL_H
#define DYNAMIXEL_TOOL_H

#include <cstring>
#include <cstdio>

#include "DynamixelItem.h"

class DynamixelTool
{
 private:
  enum {DYNAMIXEL_BUFFER = 30};
  uint8_t dxl_id_[DYNAMIXEL_BUFFER];
  uint8_t dxl_cnt_;

  const char *model_name_;
  uint16_t model_number_;

  const ControlItem *control_table_;
  const ModelInfo *model_info_;

  uint16_t the_number_of_control_item_;

 public:
  DynamixelTool();
  ~DynamixelTool();

  void initTool();

  bool addTool(const char *model_name, uint8_t id, const char **log = nullptr);
  bool addTool(uint16_t model_number, uint8_t id, const char **log = nullptr);

  void addDXL(uint8_t id);

  const char *getModelName();
  uint16_t getModelNumber();

  const uint8_t* getID();
  uint8_t getDynamixelBuffer();
  uint8_t getDynamixelCount();

  float getRPM();

  int64_t getValueOfMinRadianPosition();
  int64_t getValueOfMaxRadianPosition();
  int64_t getValueOfZeroRadianPosition();

  float getMinRadian();
  float getMaxRadian();

  uint8_t getTheNumberOfControlItem();
  
  const ControlItem *getControlItem(const char *item_name, const char **log = nullptr);
  const ControlItem *getControlTable();
  const ModelInfo *getModelInfo();

 private:
  bool setControlTable(const char *model_name, const char **log = nullptr);
  bool setControlTable(uint16_t model_number, const char **log = nullptr);

  bool setModelName(uint16_t model_number, const char **log = nullptr);
  bool setModelNumber(const char *model_name, const char **log = nullptr);
};
#endif //DYNAMIXEL_TOOL_H
