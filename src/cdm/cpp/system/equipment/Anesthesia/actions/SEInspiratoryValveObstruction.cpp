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
#include "system/equipment/Anesthesia/actions/SEInspiratoryValveObstruction.h"
#include "properties/SEScalar0To1.h"
#include "bind/Scalar0To1Data.hxx"

SEInspiratoryValveObstruction::SEInspiratoryValveObstruction() : SEAnesthesiaMachineAction()
{
	m_Severity = nullptr;
}

SEInspiratoryValveObstruction::~SEInspiratoryValveObstruction()
{
	Clear();
}

void SEInspiratoryValveObstruction::Clear()
{
	SEAnesthesiaMachineAction::Clear();
	SAFE_DELETE(m_Severity);
}

bool SEInspiratoryValveObstruction::IsValid() const
{
	return SEAnesthesiaMachineAction::IsValid() && HasSeverity();
}

bool SEInspiratoryValveObstruction::IsActive() const
{
	return HasSeverity() ? !m_Severity->IsZero() : false;
}

bool SEInspiratoryValveObstruction::Load(const CDM::InspiratoryValveObstructionData& in)
{
	SEAnesthesiaMachineAction::Load(in);
	GetSeverity().Load(in.Severity());
	return true;
}

CDM::InspiratoryValveObstructionData* SEInspiratoryValveObstruction::Unload() const
{
	CDM::InspiratoryValveObstructionData* data = new CDM::InspiratoryValveObstructionData();
	Unload(*data);
	return data;
}

void SEInspiratoryValveObstruction::Unload(CDM::InspiratoryValveObstructionData& data) const
{
	SEAnesthesiaMachineAction::Unload(data);
	if (m_Severity != nullptr)
		data.Severity(std::unique_ptr<CDM::Scalar0To1Data>(m_Severity->Unload()));
}

bool SEInspiratoryValveObstruction::HasSeverity() const
{
	return m_Severity != nullptr;
}
SEScalar0To1& SEInspiratoryValveObstruction::GetSeverity()
{
	if (m_Severity == nullptr)
		m_Severity = new SEScalar0To1();
	return *m_Severity;
}

void SEInspiratoryValveObstruction::ToString(std::ostream &str) const
{
	str << "Anesthesia Machine Action : Inspiratory Valve Obstruction";
	if (HasComment())
		str << "\n\tComment: " << m_Comment;
	str << "\n\tSeverity :"; HasSeverity() ? str << *m_Severity : str << "NaN";
	str << std::flush;
}