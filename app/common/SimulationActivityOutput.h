#ifndef SimulationActivityOutput_H
#define SimulationActivityOutput_H
/////////////////////////////////////////////////////////////////////////////
// Name:        SimulationActivityOutput.h
// Purpose:     Declaration of the SimulationActivityOutput class
// Created:     DD/MM/YYYY
// Author:      RvH
// $Date: 2008-06-16 02:07:36 +0800 (Mon, 16 Jun 2008) $
// $Revision: 1 $
// Copyright:   ©2006 University of Tasmania
/////////////////////////////////////////////////////////////////////////////
#include "simulation/common/ISimulationActivityObserver.h"

namespace rootmap
{
    class SimulationActivityOutput : public ISimulationActivityObserver
    {
    public:
        SimulationActivityOutput();

        virtual ~SimulationActivityOutput();

        /**
         * Sent to each observer by the SimulationEngine just before the processes
         * are sent the Start message. The simulation is marked as being in
         * "starting" phase at this point
         *
         * @param postOffice reference to the postOffice.
         */
        virtual void PreRunNotification(const PostOffice & postOffice);

        /**
         * Sent to each observer by the SimulationEngine before each timestamp
         * is run.
         *
         * @param postOffice reference to the postOffice.
         */
        virtual void PreTimestampNotification(const PostOffice & postOffice);

        virtual void MidTimestampNotification(const PostOffice & postOffice);

        /**
         * Sent to each observer by the SimulationEngine after each timestamp
         * is complete.  This is the ideal place for window updates to be
         * triggered.
         *
         * Note that "Post" in this sense is not the verb but the prefix,
         * meaning "after" or "later"
         *
         * NOTE that we don't override this method, so that derived classes
         * must override this at least.
         *
         * @param postOffice reference to the postOffice.
         */
        virtual void PostTimestampNotification(const PostOffice & postOffice);

        /**
         * Sent to each observer by the SimulationEngine just after the processes
         * are sent the Ending message (but before control is returned to the
         * user). The simulation is in "stopping" phase at this point.
         *
         * @param postOffice reference to the postOffice.
         */
        virtual void PostRunNotification(const PostOffice & postOffice);

        virtual void DisconnectNotification();

    private:

        ///
        /// member declaration


    }; // class SimulationActivityOutput

} // namespace rootmap

#endif // #ifndef SimulationActivityOutput_H
