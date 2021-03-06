/**************************************************************************************
Copyright 2015 Applied Research Associates, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use
this file except in compliance with the License. You may obtain a copy of the License
at:
http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.
**************************************************************************************/

#pragma once
#include "circuit/SECircuit.h"
#include "circuit/fluid/SEFluidCircuitNode.h"
#include "circuit/fluid/SEFluidCircuitPath.h"
#include "bind/FluidCircuitData.hxx"
class SECircuitManager;

class DLL_DECL SEFluidCircuit : public SECircuit<CDM::FluidCircuitData, SEFluidCircuitNode, CDM::FluidCircuitNodeData, SEFluidCircuitPath, CDM::FluidCircuitPathData>
{
  friend class SECircuitManager;
protected:
  SEFluidCircuit(const std::string& name, SECircuitManager& mgr);
public:
  virtual ~SEFluidCircuit();

  SEFluidCircuitNode& CreateNode(const std::string& name);
  SEFluidCircuitPath& CreatePath(SEFluidCircuitNode& src, SEFluidCircuitNode& tgt, const std::string& name);

  void AddCircuit(SEFluidCircuit& circuit);

protected:
  SECircuitManager& m_Mgr;
};