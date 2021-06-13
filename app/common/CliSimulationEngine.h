#ifndef CliSimulationEngine_H
#define CliSimulationEngine_H
/////////////////////////////////////////////////////////////////////////////
// Name:        CliSimulationEngine.h
// Purpose:     Declaration of the CliSimulationEngine class
// Created:     DD/MM/YYYY
// Author:      RvH
// $Date: 2008-06-16 02:07:36 +0800 (Mon, 16 Jun 2008) $
// $Revision: 1 $
// Copyright:   ©2006 University of Tasmania
//
// The CliSimulationEngine "is a" SimulationEngine that understands basic
// non-GUI requirements 
/////////////////////////////////////////////////////////////////////////////

#include "simulation/common/SimulationEngine.h"
#include "simulation/common/ISimulationActivityObserver.h"

class RmCommandLineApp;

namespace rootmap
{
    class SimulationActivityOutput;
    class TXDataAccessManager;


    class CliSimulationEngine
        : public SimulationEngine, public ISimulationActivityObserver
    {
    public:
        CliSimulationEngine(DataAccessManager & dam, RmCommandLineApp * parent);
        virtual ~CliSimulationEngine();

        virtual void Initialise();

        virtual void Run();

    protected:
        virtual void NotifyPreTimestamp();
        virtual void NotifyMidTimestamp();
        virtual void NotifyPostTimestamp();
    private:

        /** Parent application */
        RmCommandLineApp * m_parent;

        /** Object that prints output to std::cout */
        SimulationActivityOutput * m_output;

        /// Hidden copy constructor
        CliSimulationEngine(const CliSimulationEngine &);
        /// Hidden assignment operator
        CliSimulationEngine & operator=(const CliSimulationEngine &);

        size_t GetPercentageComplete(const PostOffice & postOffice);

        size_t m_timestampCount;
        size_t m_percentageComplete;

        // Inherited via ISimulationActivityObserver
        virtual void PreRunNotification(const PostOffice & postOffice) override;
        virtual void PreTimestampNotification(const PostOffice & postOffice) override;
        virtual void MidTimestampNotification(const PostOffice & postOffice) override;
        virtual void PostTimestampNotification(const PostOffice & postOffice) override;
        virtual void PostRunNotification(const PostOffice & postOffice) override;
        virtual void DisconnectNotification() override;
    }; // class CliSimulationEngine

} // namespace rootmap

#endif // #ifndef CliSimulationEngine_H
