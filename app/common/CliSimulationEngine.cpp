/////////////////////////////////////////////////////////////////////////////
// Name:        CliSimulationEngine.cpp
// Purpose:     Implementation of the CliSimulationEngine class
// Created:     DD/MM/YYYY
// Author:      RvH
// $Date: 2008-06-16 02:07:36 +0800 (Mon, 16 Jun 2008) $
// $Revision: 1 $
// Copyright:   ©2006 University of Tasmania
/////////////////////////////////////////////////////////////////////////////

#include "app/common/CliSimulationEngine.h"
#include "app/common/SimulationActivityOutput.h"
#include "app/main/RmCommandLineApp.h"

#include "simulation/common/Types.h"
#include "simulation/data_access/common/DataAccessManager.h"
#include "simulation/data_access/interface/ViewDAI.h"
#include "simulation/process/common/ProcessCoordinator.h"
#include "simulation/process/common/Process.h"
#include "simulation/process/raytrace/ScoreboardColourInfo.h"
#include "simulation/scoreboard/ScoreboardCoordinator.h"
#include "simulation/scoreboard/Scoreboard.h"

#include "core/common/ExtraStuff.h"
#include "core/common/RmAssert.h"

#include <iomanip>

namespace rootmap
{
    CliSimulationEngine::CliSimulationEngine(DataAccessManager & dam, RmCommandLineApp * parent)
        : SimulationEngine(dam)
        , m_parent(parent)
        , m_output(new SimulationActivityOutput)
        , m_timestampCount(0)
        , m_percentageComplete(99999)
    {
        // TODO input flags!
        bool showProgress = false;
        if (showProgress)
        {
            RegisterSimulationActivityObserver(m_output);
        }
    }

    CliSimulationEngine::~CliSimulationEngine()
    {
        delete m_output;
    }

    void CliSimulationEngine::Initialise()
    {
        // performs the construction and initialisation phases
        SimulationEngine::Initialise();

        RegisterSimulationActivityObserver(this);
    }

    void CliSimulationEngine::Run()
    {
        wxDateTime now(wxDateTime::Now());
        std::cout << "Simulation run started at " << now.Format("%Y/%m/%d %H:%M:%S").c_str() << std::endl;
        SimulationEngine::Run();
        now = wxDateTime::Now();
        std::cout << "Simulation run completed at " << now.Format("%Y/%m/%d %H:%M:%S").c_str() << std::endl;
    }

    void CliSimulationEngine::NotifyPreTimestamp()
    {
        m_parent->Yield(true);
        SimulationEngine::NotifyPreTimestamp();
    }

    void CliSimulationEngine::NotifyMidTimestamp()
    {
        m_parent->Yield(true);
        SimulationEngine::NotifyMidTimestamp();
    }

    void CliSimulationEngine::NotifyPostTimestamp()
    {
        m_parent->Yield(true);
        SimulationEngine::NotifyPostTimestamp();
    }

    size_t CliSimulationEngine::GetPercentageComplete(const PostOffice & postOffice)
    {
        rootmap::ProcessTime_t end = postOffice.GetNearestEnd();
        rootmap::ProcessTime_t now = postOffice.GetNow();
        rootmap::ProcessTime_t start = postOffice.GetStart();

        rootmap::ProcessTime_t totalDuration = end - start;
        if (0 == totalDuration)
        {
            return 0;
        }
        else
        {
            size_t progressPercentage = (100 * (now - start) / totalDuration);
            return progressPercentage;
        }
    }

    void CliSimulationEngine::PreRunNotification(const PostOffice & /*postOffice*/)
    { }

    void CliSimulationEngine::PreTimestampNotification(const PostOffice & /*postOffice*/)
    { }

    void CliSimulationEngine::MidTimestampNotification(const PostOffice & /*postOffice*/)
    { }

    void CliSimulationEngine::PostTimestampNotification(const PostOffice & postOffice)
    {
        m_timestampCount++;
        size_t pc = GetPercentageComplete(postOffice);
        if (pc != m_percentageComplete || m_percentageComplete > 100)
        {
            m_percentageComplete = pc;
            // Use a carriage return without a newline, to return to the beginning of the current stdout line and overwrite it.
            std::cout << "\r" << std::setw(2) << m_percentageComplete << "% complete...";
        }
    }

    void CliSimulationEngine::PostRunNotification(const PostOffice & /*postOffice*/)
    { }

    void CliSimulationEngine::DisconnectNotification()
    { }
} // namespace rootmap
