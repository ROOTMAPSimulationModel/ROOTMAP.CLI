/////////////////////////////////////////////////////////////////////////////
// Name:        ProcessDrawing.cpp
// Purpose:     Implementation of the ProcessDrawing class
// Created:     DD/MM/YYYY
// Author:      RvH
// $Date: 2009-07-07 02:40:29 +0800 (Tue, 07 Jul 2009) $
// $Revision: 67 $
// Copyright:   ©2006 University of Tasmania
//
// IMPORTANT NOTE: This class breaks the file-placement paradigm by not being
// with its header file. The reasoning behind this is to keep process drawing
// efficient, so it does not have an abstract interface in
// simulation/process/common//src that is implemented in app, where the drawing
// logic actually is. 
//
// With this batch/command-line interface that does no drawing, we merely
// implement the methods without using the ProcessDrawingBuffer class.
//
/////////////////////////////////////////////////////////////////////////////
#include "simulation/process/common/ProcessDrawing.h"
#include "simulation/process/common/Process.h"
#include "core/common/RmAssert.h"

namespace rootmap
{
    class IProcessDrawingBuffer;

    ProcessDrawing::ProcessDrawing(Process * p)
        : m_process(p)
        , m_singleBuffer(__nullptr)
    {
    }

    ProcessDrawing::~ProcessDrawing()
    {
    }

    void ProcessDrawing::BeginDrawing(IProcessDrawingBuffer * /* buffer */)
    {
    }

    void ProcessDrawing::EndDrawing(IProcessDrawingBuffer * /* buffer */)
    {
    }

    void ProcessDrawing::AddDrawingBuffer(IProcessDrawingBuffer * /* buffer */)
    {
        //m_drawingBuffers.push_back(buffer);
    }

    void ProcessDrawing::RemoveDrawingBuffer(IProcessDrawingBuffer * /* buffer */)
    {    }

    void ProcessDrawing::DrawScoreboard(const DoubleRect & /* area */, Scoreboard * /* scoreboard */, IProcessDrawingBuffer * /* buffer */)
    {    }

    void ProcessDrawing::MovePenTo(const DoubleCoordinate & /* fi */) { }

    void ProcessDrawing::DrawLineTo(const DoubleCoordinate & /* fi */) { }

    void ProcessDrawing::DrawLine(const DoubleCoordinate & /* from_coord */, const DoubleCoordinate & /* to_coord */) { }

    void ProcessDrawing::DrawRectangle(const ScoreboardStratum & /* stratum */, BoxCoordinate * /* bc */, ViewDirection /* direction */, double /* place */) { }

    void ProcessDrawing::DrawRectangle(const DoubleBox & /* soil_box */, ViewDirection /* direction */, double /* place */) { }

    void ProcessDrawing::DrawRectangle(const DoubleBox & /* soil_box */, ViewDirection /* direction */) { }

    void ProcessDrawing::DrawRectangle(const DoubleBox & /* soil_box */) { }

    void ProcessDrawing::DrawOval(const ScoreboardStratum & /* stratum */, BoxCoordinate * /* bc */, ViewDirection /* direction */, double /* place */) { }

    void ProcessDrawing::DrawOval(const DoubleBox & /* soil_box */, ViewDirection /* direction */, double /* place */) { }

    void ProcessDrawing::DrawOval(const DoubleBox & /* soil_box */, ViewDirection /* direction */) { }

    void ProcessDrawing::DrawOval(const DoubleBox & /* soil_box */) { }

    void ProcessDrawing::DrawDot(DoubleCoordinate & /* fi */) { }

    void ProcessDrawing::DrawLineTo(const DoubleCoordinate & /* fi */, wxColour & /* colour */) { }

    void ProcessDrawing::DrawLine(const DoubleCoordinate & /* coord1 */, const DoubleCoordinate & /* coord2 */, wxColour & /* colour */) { }

    void ProcessDrawing::DrawRectangle(const ScoreboardStratum & /* stratum */, BoxCoordinate * /* bc */, ViewDirection /* direction */, double /* place */, wxColour & /* colour */) { }

    void ProcessDrawing::DrawRectangle(const DoubleBox & /* soil_box */, ViewDirection /* direction */, double /* place */, wxColour & /* colour */) { }

    void ProcessDrawing::DrawRectangle(const DoubleBox & /* soil_box */, ViewDirection /* direction */, wxColour & /* colour */) { }

    void ProcessDrawing::DrawRectangle(const DoubleBox & /* soil_box */, wxColour & /* colour */) { }

    void ProcessDrawing::DrawOval(const ScoreboardStratum & /* stratum */, BoxCoordinate * /* bc */, ViewDirection /* direction */, double /* place */, wxColour & /* colour */) { }

    void ProcessDrawing::DrawOval(const DoubleBox & /* soil_box */, ViewDirection /* direction */, double /* place */, wxColour & /* colour */) { }

    void ProcessDrawing::DrawOval(const DoubleBox & /* soil_box */, ViewDirection /* direction */, wxColour & /* colour */) { }

    void ProcessDrawing::DrawOval(const DoubleBox & /* soil_box */, wxColour & /* colour */) { }

    void ProcessDrawing::DrawDot(DoubleCoordinate & /* fi */, wxColour & /* colour */) { }

    // MSA 10.01.19 Empty implementations of the ProcessDrawing methods added recently

    void ProcessDrawing::RemoveDot(const DoubleCoordinate & /* fi */) { }

    void ProcessDrawing::RemoveAllDots() { }

    void ProcessDrawing::RemoveRectangle(const ScoreboardStratum& /*stratum*/, BoxCoordinate* /*bc*/, ViewDirection /*direction*/, double /*place*/) { }

    void ProcessDrawing::DrawRootSegment(const DoubleCoordinate & /* start */, const DoubleCoordinate & /* end */, const long & /* order */, const double & /*radius*/, const unsigned long & /* plantElementId */) { }

    void ProcessDrawing::DrawCone(const DoubleCoordinate& /*coord1*/, const DoubleCoordinate& /*coord2*/, const double& /*radius1*/, const double& /*radius2*/, wxColour& /*colour*/, const ViewDirection& /*direction*/, const size_t& /*stacksNSlices*/, const bool& /*wireframe*/) { }

} // namespace rootmap
