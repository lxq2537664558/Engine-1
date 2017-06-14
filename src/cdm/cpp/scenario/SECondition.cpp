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

#include "stdafx.h"
#include "scenario/SECondition.h"
#include "bind/ConditionData.hxx"

#include "substance/SESubstanceManager.h"
//Patient Conditions
#include "patient/conditions/SEChronicAnemia.h"
#include "bind/ChronicAnemiaData.hxx"
#include "patient/conditions/SEChronicObstructivePulmonaryDisease.h"
#include "bind/ChronicObstructivePulmonaryDiseaseData.hxx"
#include "patient/conditions/SEChronicHeartFailure.h"
#include "bind/ChronicHeartFailureData.hxx"
#include "patient/conditions/SEChronicRenalStenosis.h"
#include "bind/ChronicRenalStenosisData.hxx"
#include "patient/conditions/SEChronicVentricularSystolicDysfunction.h"
#include "bind/ChronicVentricularSystolicDysfunctionData.hxx"
#include "patient/conditions/SEConsumeMeal.h"
#include "bind/ConsumeMealData.hxx"
#include "patient/conditions/SELobarPneumonia.h"
#include "bind/LobarPneumoniaData.hxx"
#include "patient/conditions/SEChronicPericardialEffusion.h"
#include "bind/ChronicPericardialEffusionData.hxx"
#include "patient/conditions/SEImpairedAlveolarExchange.h"
#include "bind/ImpairedAlveolarExchangeData.hxx"
// Environment Conditions
#include "system/environment/conditions/SEInitialEnvironment.h"
#include "bind/InitialEnvironmentData.hxx"

SECondition::SECondition() : Loggable()
{
	m_Comment="";
}

SECondition::~SECondition()
{
	Clear();
}

void SECondition::Clear()
{
  m_Comment = "";
}

SECondition* SECondition::newFromBind(const CDM::ConditionData& data, SESubstanceManager& substances)
{
	// Could speed up case by testing Patient Conditions vs another type
	// But we only have 1 type at this time, and a few conditions to support
	const CDM::ChronicAnemiaData* ccAnemiaData = dynamic_cast<const CDM::ChronicAnemiaData*>(&data);
	if (ccAnemiaData != nullptr)
	{
		SEChronicAnemia* cc = new SEChronicAnemia();
		cc->Load(*ccAnemiaData);
		return cc;
	}
	const CDM::ChronicObstructivePulmonaryDiseaseData* ccopdData = dynamic_cast<const CDM::ChronicObstructivePulmonaryDiseaseData*>(&data);
	if (ccopdData != nullptr)
	{
		SEChronicObstructivePulmonaryDisease* cc = new SEChronicObstructivePulmonaryDisease();
		cc->Load(*ccopdData);
		return cc;
	}
	const CDM::ChronicVentricularSystolicDysfunctionData* ccVentSysDysfuncData = dynamic_cast<const CDM::ChronicVentricularSystolicDysfunctionData*>(&data);
	if (ccVentSysDysfuncData != nullptr)
	{
		SEChronicVentricularSystolicDysfunction* cc = new SEChronicVentricularSystolicDysfunction();
		cc->Load(*ccVentSysDysfuncData);
		return cc;
	}
	const CDM::ChronicPericardialEffusionData* ccPericardialEffusionData = dynamic_cast<const CDM::ChronicPericardialEffusionData*>(&data);
	if (ccPericardialEffusionData != nullptr)
	{
		SEChronicPericardialEffusion* cc = new SEChronicPericardialEffusion();
		cc->Load(*ccPericardialEffusionData);
		return cc;
	}
	const CDM::ChronicRenalStenosisData* ccRenalStenosisData = dynamic_cast<const CDM::ChronicRenalStenosisData*>(&data);
	if (ccRenalStenosisData != nullptr)
	{
		SEChronicRenalStenosis* cc = new SEChronicRenalStenosis();
		cc->Load(*ccRenalStenosisData);
		return cc;
	}
	const CDM::ConsumeMealData* ccConsumeMealData = dynamic_cast<const CDM::ConsumeMealData*>(&data);
	if (ccConsumeMealData != nullptr)
	{
		SEConsumeMeal* cc = new SEConsumeMeal();
		cc->Load(*ccConsumeMealData);
		return cc;
	}
  const CDM::ImpairedAlveolarExchangeData* ccImpairedAlveolarExchangeData = dynamic_cast<const CDM::ImpairedAlveolarExchangeData*>(&data);
  if (ccImpairedAlveolarExchangeData != nullptr)
  {
    SEImpairedAlveolarExchange* cc = new SEImpairedAlveolarExchange();
    cc->Load(*ccImpairedAlveolarExchangeData);
    return cc;
  }
	const CDM::LobarPneumoniaData* ccLobarPneumoniaData = dynamic_cast<const CDM::LobarPneumoniaData*>(&data);
	if (ccLobarPneumoniaData != nullptr)
	{
		SELobarPneumonia* cc = new SELobarPneumonia();
		cc->Load(*ccLobarPneumoniaData);
		return cc;
	}
	const CDM::InitialEnvironmentData* ccInitialEnvironmentData = dynamic_cast<const CDM::InitialEnvironmentData*>(&data);
	if (ccInitialEnvironmentData != nullptr)
	{
		SEInitialEnvironment* cc = new SEInitialEnvironment(substances);
		cc->Load(*ccInitialEnvironmentData);
		return cc;
	}

	if (substances.GetLogger() != nullptr)
		substances.GetLogger()->Error("Unsupported Condition Received", "SECondition::newFromBind");
	return nullptr;
}

bool SECondition::Load(const CDM::ConditionData& in)
{
	Clear();
	if(in.Comment().present())
		m_Comment=in.Comment().get();
	return true;
}

CDM::ConditionData* SECondition::Unload() const
{
	CDM::ConditionData* data = new CDM::ConditionData();
	Unload(*data);
	return data;
}

void SECondition::Unload(CDM::ConditionData& data) const
{
	if(HasComment())
		data.Comment(m_Comment);
}


std::string SECondition::GetComment() const
{
	return m_Comment;
}
void SECondition::SetComment(const std::string& comment)
{
	m_Comment = comment;
}
bool SECondition::HasComment() const
{
	return m_Comment.empty()?false:true;
}
void SECondition::InvalidateComment()
{
	m_Comment = "";
}