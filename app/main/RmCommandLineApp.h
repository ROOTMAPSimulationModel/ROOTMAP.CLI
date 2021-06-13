/////////////////////////////////////////////////////////////////////////////
// Name:        RmCommandLineApp.h
// Purpose:     
// Author:      R. van Hugten
// Modified by: 
// Created:     13/12/2007 17:05:50
// RCS-ID:      
// Copyright:   ©2006 University of Tasmania
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _RMCOMMANDLINEAPP_H_
#define _RMCOMMANDLINEAPP_H_

#include "wx/wx.h"

 ////@begin forward declarations
namespace rootmap
{
    class CliSimulationEngine;
    class TXDataAccessManager;
} // namespace rootmap
 ////@end forward declarations

class RmCommandLineApp : public wxAppConsole
{

public:
    /// Constructor
    RmCommandLineApp();

    void Init();

    /// Initialises the application
    virtual bool OnInit();

    /// Called on exit
    virtual int OnExit();

    // This is the replacement for the normal main(): all program work should
    // be done here. When OnRun() returns, the programs starts shutting down.
    virtual int OnRun();

    void ForceDynamicClassUsage();

private:
    rootmap::CliSimulationEngine * m_engine;
    rootmap::TXDataAccessManager * m_tx_dam;
};

#endif // _RMCOMMANDLINEAPP_H_
