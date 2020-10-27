#include "l2_creationadapter.h"
#include <QDebug>

#define PRINT_FUNC qDebug() << __FUNCTION__

L2_CreationAdapter::L2_CreationAdapter()
{

}

L2_CreationAdapter::~L2_CreationAdapter()
{

}

void L2_CreationAdapter::processCodeValuePair(unsigned int, const std::string &)
{
//    PRINT_FUNC;
}

void L2_CreationAdapter::endSection()
{
//    PRINT_FUNC;
}

void L2_CreationAdapter::addLayer(const DL_LayerData &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addLinetype(const DL_LinetypeData &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addLinetypeDash(double)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addBlock(const DL_BlockData &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::endBlock()
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addTextStyle(const DL_StyleData &)
{
//    PRINT_FUNC;
}

void L2_CreationAdapter::addPoint(const DL_PointData &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addLine(const DL_LineData &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addXLine(const DL_XLineData &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addRay(const DL_RayData &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addArc(const DL_ArcData &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addCircle(const DL_CircleData &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addEllipse(const DL_EllipseData &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addPolyline(const DL_PolylineData &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addVertex(const DL_VertexData &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addSpline(const DL_SplineData &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addControlPoint(const DL_ControlPointData &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addFitPoint(const DL_FitPointData &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addKnot(const DL_KnotData &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addInsert(const DL_InsertData &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addMText(const DL_MTextData &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addMTextChunk(const std::string &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addText(const DL_TextData &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addArcAlignedText(const DL_ArcAlignedTextData &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addAttribute(const DL_AttributeData &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addDimAlign(const DL_DimensionData &, const DL_DimAlignedData &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addDimLinear(const DL_DimensionData &, const DL_DimLinearData &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addDimRadial(const DL_DimensionData &, const DL_DimRadialData &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addDimDiametric(const DL_DimensionData &, const DL_DimDiametricData &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addDimAngular(const DL_DimensionData &, const DL_DimAngularData &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addDimAngular3P(const DL_DimensionData &, const DL_DimAngular3PData &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addDimOrdinate(const DL_DimensionData &, const DL_DimOrdinateData &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addLeader(const DL_LeaderData &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addLeaderVertex(const DL_LeaderVertexData &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addHatch(const DL_HatchData &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addTrace(const DL_TraceData &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::add3dFace(const DL_3dFaceData &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addSolid(const DL_SolidData &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addImage(const DL_ImageData &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::linkImage(const DL_ImageDefData &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addHatchLoop(const DL_HatchLoopData &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addHatchEdge(const DL_HatchEdgeData &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addXRecord(const std::string &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addXRecordString(int, const std::string &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addXRecordReal(int, double)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addXRecordInt(int, int)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addXRecordBool(int, bool)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addXDataApp(const std::string &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addXDataString(int, const std::string &)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addXDataReal(int, double)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addXDataInt(int, int)
{
    PRINT_FUNC;
}

void L2_CreationAdapter::addDictionary(const DL_DictionaryData &)
{
//    PRINT_FUNC;
}

void L2_CreationAdapter::addDictionaryEntry(const DL_DictionaryEntryData &)
{
//    PRINT_FUNC;
}

void L2_CreationAdapter::endEntity()
{
//    PRINT_FUNC;
}

void L2_CreationAdapter::addComment(const std::string &)
{
//    PRINT_FUNC;
}

void L2_CreationAdapter::setVariableVector(const std::string &, double, double, double, int)
{
//    PRINT_FUNC;
}

void L2_CreationAdapter::setVariableString(const std::string &, const std::string &, int)
{
//    PRINT_FUNC;
}

void L2_CreationAdapter::setVariableInt(const std::string &, int, int)
{
//    PRINT_FUNC;
}

void L2_CreationAdapter::setVariableDouble(const std::string &, double, int)
{
//    PRINT_FUNC;
}
