/////////////////////////////////////////////////////////////////////////////
// Name:        ViewCaptureOutputStrategy.cpp
// Purpose:     Definition of the ViewCaptureOutputStrategy class
// Created:     21/09/2009
// Author:      MSA
// $Date: 2009-09-21 02:07:36 +0800 (Mon, 21 Sep 2009) $
// $Revision: 1 $
// Copyright:   ©2009 University of Tasmania/University of Western Australia
//
// NOTE: Breaks file-placement paradigm in the same manner and for
// the same reasons as ProcessDrawing.
//
/////////////////////////////////////////////////////////////////////////////
#include "simulation/file/output/ViewCaptureOutputStrategy.h"

namespace rootmap
{
    ViewCaptureOutputStrategy::ViewCaptureOutputStrategy(SimulationEngine * septr, const ViewType vt, const size_t & viewWindowIndex, const wxString & fileExt)
        : m_simulationEngine(septr)
        , m_viewType(vt)
        , m_viewWindowIndex(viewWindowIndex)
        , m_fileExt(fileExt)
    {
    }

    ViewCaptureOutputStrategy::~ViewCaptureOutputStrategy()
    {
    }

    void ViewCaptureOutputStrategy::ArrangeOutput(ProcessActionDescriptor * /* action */, OutputRule * /* output_rule */)
    {
        // Do nothing. No view to capture.
    }

    void ViewCaptureOutputStrategy::OutputToFile(DataOutputFile & /* file */)
    {
    }

} // namespace rootmap
