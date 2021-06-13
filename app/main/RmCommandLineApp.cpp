/////////////////////////////////////////////////////////////////////////////
// Name:        RmCommandLineApp.cpp
// Purpose:     
// Author:      R. van Hugten
// Modified by: 
// Created:     13/12/2007 17:05:50
// RCS-ID:      
// Copyright:   ©2006 University of Tasmania
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#include "wx/colour.h"
#include "app/main/RmCommandLineApp.h"
#include "app/common/RmGetOpts.h"
#include "app/common/FileSystemUtilities.h"
#include "app/common/CliSimulationEngine.h"
#include "simulation/data_access/tinyxmlconfig/TXDataAccessManager.h"

#include "core/log/Logger.h"
#include "core/common/RmAssert.h"
#include "core/macos_compatibility/MacResourceManager.h"

#include "simulation/file/output/OutputFileAlarm.h"
#include "simulation/process/modules/OrganicMatter.h"
#include "simulation/process/modules/Phosphorus.h"
#include "simulation/process/modules/Nitrate.h"
#include "simulation/process/modules/Water.h"
#include "simulation/process/raytrace/ScoreboardRenderer.h"

wxIMPLEMENT_APP_CONSOLE(RmCommandLineApp);

RmCommandLineApp::RmCommandLineApp()
    : m_engine(__nullptr)
    , m_tx_dam(__nullptr)
{
    Init();
}

void RmCommandLineApp::Init()
{}

/*!
 * Initialisation for RmCommandLineApp
 */
bool RmCommandLineApp::OnInit()
{
    // Get default options
    auto opts = rootmap::RmGetOpts::getInstance();
    // Apply any options set via the command line
    opts.parseCmdLine(argc, argv);

    std::cout << "ROOTMAP CLI v" << opts.getVersion() << " (C) 2020 University of Tasmania / University of Western Australia" << std::endl;

    std::deque<wxString> subdirs;
    std::string configDir = (opts.isOptSet(RMGETOPTS_CONFIGDIR)) ? opts.getOpt(RMGETOPTS_CONFIGDIR) : "Configurations";
    // Ensure configuration directory path is absolute.
    configDir = rootmap::FilesystemUtilities::resolveAbsolutePath(configDir, subdirs, opts.getVersion()).c_str();

    std::string configFile = "rootmap.xml";
    if (opts.isOptSet(RMGETOPTS_CONFIGFILE))
    {
        configFile = opts.getOpt(RMGETOPTS_CONFIGFILE);
    }

    subdirs.clear();
    std::string outputDir = (opts.isOptSet(RMGETOPTS_OUTPUTDIR)) ? opts.getOpt(RMGETOPTS_OUTPUTDIR) : "Output";
    // Ensure output directory path is absolute.
    outputDir = rootmap::FilesystemUtilities::resolveAbsolutePath(outputDir, subdirs, opts.getVersion()).c_str();

    std::cout << "Loading configuration data from " << configDir << configFile << "..." << std::endl;
    if (opts.isOptSet(RMGETOPTS_SEED))
    {
        std::string seedStr = opts.getOpt(RMGETOPTS_SEED);
        m_tx_dam = new rootmap::TXDataAccessManager(configDir, outputDir, configFile, seedStr);
    }
    else
    {
        m_tx_dam = new rootmap::TXDataAccessManager(configDir, outputDir, configFile);
    }

    std::cout << "Configuring logging..." << std::endl;
    wxString specifiedLogConfigFile = opts.getOpt(RMGETOPTS_LOGFILENAME);
    wxString exeDirLogConfigFile = "";
    wxString workingDirLogConfigFile = opts.getOpt(RMGETOPTS_WORKINGDIR);
    workingDirLogConfigFile << "rootmap.log.cfg";
    WCHAR ownPth[MAX_PATH];
    HMODULE hModule = GetModuleHandle(__nullptr);
    if (hModule != __nullptr)
    {
        GetModuleFileName(hModule, ownPth, (sizeof(ownPth)));
        std::string::size_type pos = wxString(ownPth).find_last_of("\\/");
        exeDirLogConfigFile << wxString(ownPth).substr(0, pos) << "\\rootmap.log.cfg";
    }
    if (!specifiedLogConfigFile.empty() && !specifiedLogConfigFile.Contains(":"))
    {
        // Assume to be relative if path does not contain a colon.
        // If it's relative, convert it to absolute here.
        specifiedLogConfigFile = opts.getOpt(RMGETOPTS_WORKINGDIR) + specifiedLogConfigFile;
    }

    // Attempt to load config from
    // 1. Any explicitly specified file
    // 2. The current exe directory
    // 3. The base working directory
    bool success = !specifiedLogConfigFile.empty() && RootMapLoggerConfigure(specifiedLogConfigFile.c_str());
    if (!success && hModule != __nullptr)
    {
        success = RootMapLoggerConfigure(exeDirLogConfigFile.c_str());
    }
    if (!success)
    {
        success = RootMapLoggerConfigure(workingDirLogConfigFile.c_str());
    }

    if (!success)
    {
        wxString s = specifiedLogConfigFile.empty()
            ? ""
            : ("specified directory " + specifiedLogConfigFile + "\nor ");
        std::cout << "ERROR: Could not find a log configuration file rootmap.log.cfg\nin ";
        std::cout << s;
        std::cout << "executable directory " << wxString(ownPth) << "\nor working directory " << workingDirLogConfigFile << "." << std::endl;
        return false;
    }

    // Initialise common string pool
    rootmap::MacResourceManager::Initialise();

    // MSA TODO allow passing simulation path args
    // std::cout << "simulation data loaded from " << "...";

    std::cout << "Building simulation engine...\t";
    m_engine = new rootmap::CliSimulationEngine(*m_tx_dam, this);
    std::cout << "ROOTMAP CLI engine v" << opts.getVersion() << " constructed" << std::endl;

    std::cout << "Initialising simulation engine..." << std::endl;
    m_engine->Initialise();

    return true;
}

int RmCommandLineApp::OnRun()
{
    m_engine->Run();
    return 0;
}

/*!
 * Cleanup for RmCommandLineApp
 */

int RmCommandLineApp::OnExit()
{
    delete m_engine; m_engine = __nullptr;
    delete m_tx_dam; m_tx_dam = __nullptr;

    return wxAppConsole::OnExit();
}

//#define FORCE_DYNAMIC_CLASS_USE(cname) static rootmap::cname Force##cname##Use
#define FORCE_DYNAMIC_CLASS_USE(cname) rootmap::cname * ForcedUseOf##cname = new rootmap::cname; delete ForcedUseOf##cname

void RmCommandLineApp::ForceDynamicClassUsage()
{
    FORCE_DYNAMIC_CLASS_USE(Water);
    FORCE_DYNAMIC_CLASS_USE(Nitrate);
    FORCE_DYNAMIC_CLASS_USE(Phosphorus);
    FORCE_DYNAMIC_CLASS_USE(OrganicMatter);
    FORCE_DYNAMIC_CLASS_USE(OutputFileAlarm);
    FORCE_DYNAMIC_CLASS_USE(ScoreboardRenderer);
    //FORCE_DYNAMIC_CLASS_USE(DummyProcessNothing);
    //FORCE_DYNAMIC_CLASS_USE(DummyProcessWith2Characteristics);
}
