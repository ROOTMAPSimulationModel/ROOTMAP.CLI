/////////////////////////////////////////////////////////////////////////////
// Name:        SimulationActivityOutput.cpp
// Purpose:     Implementation of the SimulationActivityOutput class
// Created:     DD/MM/YYYY
// Author:      RvH
// $Date: 2008-06-16 02:07:36 +0800 (Mon, 16 Jun 2008) $
// $Revision: 1 $
// Copyright:   ©2006 University of Tasmania
/////////////////////////////////////////////////////////////////////////////
#include "app/common/SimulationActivityOutput.h"
#include "simulation/process/interprocess_communication/PostOffice.h"
#include "simulation/common/Types.h"

#include <iostream>

#include "wx/datetime.h"

namespace rootmap
{
    SimulationActivityOutput::SimulationActivityOutput()
    {
    }

    SimulationActivityOutput::~SimulationActivityOutput()
    {
    }

    void SimulationActivityOutput::PreRunNotification(const PostOffice & postOffice)
    {
        rootmap::ProcessTime_t the_time_t = postOffice.GetNow();
        wxDateTime the_time_wx(the_time_t);
        wxString the_time_s = the_time_wx.Format("%Y/%m/%d %H:%M:%S");

        std::cout << "Starting Simulation at " << the_time_s.c_str() << std::endl;
    }

    void SimulationActivityOutput::PreTimestampNotification(const PostOffice & postOffice)
    {
        rootmap::ProcessTime_t the_time_t = postOffice.GetNextTimeStamp();
        wxDateTime the_time_wx(the_time_t);
        wxString the_time_s = the_time_wx.Format("%Y/%m/%d %H:%M:%S");

        std::cout << "Next Timestamp at " << the_time_s.c_str() << std::endl;
    }

    void SimulationActivityOutput::MidTimestampNotification(const PostOffice& /*postOffice*/)
    {
    }

    void SimulationActivityOutput::PostTimestampNotification(const PostOffice & /* postOffice */)
    {
        // do nothing for post-timestamp
    }

    void SimulationActivityOutput::PostRunNotification(const PostOffice & postOffice)
    {
        rootmap::ProcessTime_t the_time_t = postOffice.GetNow();
        wxDateTime the_time_wx(the_time_t);
        wxString the_time_s = the_time_wx.Format("%Y/%m/%d %H:%M:%S");

        std::cout << "Finished Simulation at " << the_time_s.c_str() << std::endl;
    }

    void SimulationActivityOutput::DisconnectNotification()
    {
        // Do nothing; this method is just for GUI-wrangling.
    }

} // namespace rootmap
