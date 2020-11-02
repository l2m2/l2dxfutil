#include "l2_dxfadapter.h"
#include <math.h>
#include <QDebug>
#include <QtMath>
#include <QVector2D>

#define PRINT_FUNC qDebug() << __FUNCTION__

namespace {
static const double DEFAULT_THICKNESS = 0.01;
static const double EPSILON = 0.000001;
static const bool AUTOFILL = false;
}

L2_DxfAdapter::L2_DxfAdapter()
{

}

L2_DxfAdapter::~L2_DxfAdapter()
{

}

QMap<QString, QVariantList> L2_DxfAdapter::getLayers() const
{
    return this->layers;
}

void L2_DxfAdapter::addLayer(const DL_LayerData &)
{
    PRINT_FUNC;
}

void L2_DxfAdapter::addLinetype(const DL_LinetypeData &)
{
    PRINT_FUNC;
}

void L2_DxfAdapter::addLinetypeDash(double)
{
    PRINT_FUNC;
}

void L2_DxfAdapter::addBlock(const DL_BlockData &data)
{
    PRINT_FUNC;
    this->current_block = QString::fromStdString(data.name);
}

void L2_DxfAdapter::endBlock()
{
    PRINT_FUNC;
    this->blocks.insert(this->current_block, this->current_block_objects);
    this->current_block_objects.clear();
    this->current_block.clear();
}

void L2_DxfAdapter::addPoint(const DL_PointData &)
{
    PRINT_FUNC;
}

void L2_DxfAdapter::addLine(const DL_LineData &data)
{
    PRINT_FUNC;
    QString layer = QString::fromStdString(this->attributes.getLayer());
    QString device = QString("C,%1*").arg(DEFAULT_THICKNESS);
    QVariantList objects;
    objects.push_back(QVariantMap{
                          { "layer", layer },
                          { "device", device },
                          { "x", data.x1 },
                          { "y", data.y1 },
                          { "style", "D02" }
                      });
    objects.push_back(QVariantMap{
                          { "layer", layer },
                          { "device", device },
                          { "x", data.x2 },
                          { "y", data.y2 },
                          { "style", "D01" }
                      });
    if (!this->current_block.isEmpty()) {
        this->current_block_objects.append(objects);
    } else {
        process(objects, true);
    }
}

void L2_DxfAdapter::addXLine(const DL_XLineData &)
{
    PRINT_FUNC;
}

void L2_DxfAdapter::addRay(const DL_RayData &)
{
    PRINT_FUNC;
}

void L2_DxfAdapter::addArc(const DL_ArcData &data)
{
    PRINT_FUNC;
    QString layer = QString::fromStdString(this->attributes.getLayer());
    QString device = QString("C,%1*").arg(DEFAULT_THICKNESS);
    double start_angle = data.angle1 / 180 * M_PI;
    double end_angle = data.angle2 / 180 * M_PI;
    double rel_x = data.radius * qCos(start_angle);
    double rel_y = data.radius * qSin(start_angle);
    double start_x = data.cx + rel_x;
    double start_y = data.cy + rel_y;
    double end_x = data.cx + data.radius * qCos(end_angle);
    double end_y = data.cy + data.radius * qSin(end_angle);
    QVariantList objects;
    objects.push_back(QVariantMap{
                          { "layer", layer },
                          { "command", "G75*" },
                      });
    objects.push_back(QVariantMap{
                          { "layer", layer },
                          { "device", device },
                          { "mode", "G01" },
                          { "x", start_x },
                          { "y", start_y },
                          { "style", "D02" }
                      });
    objects.push_back(QVariantMap{
                          { "layer", layer },
                          { "device", device },
                          { "mode", "G03" },
                          { "x", end_x },
                          { "y", end_y },
                          { "style", "D01" },
                          { "i", -rel_x },
                          { "j", -rel_y }
                      });
    objects.push_back(QVariantMap{
                          { "layer", layer },
                          { "command", "G01*" }
                      });

    if (!this->current_block.isEmpty()) {
        this->current_block_objects.append(objects);
    } else {
        process(objects, true);
    }
}

void L2_DxfAdapter::addCircle(const DL_CircleData &data)
{
    PRINT_FUNC;
    QString layer = QString::fromStdString(this->attributes.getLayer());
    QString device;
    if (AUTOFILL) {
        device = QString("C,%1*").arg(data.radius * 2);
    } else {
        device = QString("C,%1X%2").arg(data.radius * 2, data.radius * 2 - DEFAULT_THICKNESS);
    }
    QVariantList objects;
    objects.push_back(QVariantMap{
                          { "leyer", layer },
                          { "device", device },
                          { "x", data.cx },
                          { "y", data.cy },
                          { "style", "D03" }
                      });
    if (!this->current_block.isEmpty()) {
        this->current_block_objects.append(objects);
    } else {
        process(objects, true);
    }
}

void L2_DxfAdapter::addEllipse(const DL_EllipseData &data)
{
    PRINT_FUNC;
    QString layer = QString::fromStdString(this->attributes.getLayer());
    double tilt = 0.0;
    if (data.mx > 0) {
        tilt = qAtan(data.my / data.mx);
    } else {
        tilt = copysign(M_PI / 2, data.my);
    }
    int sampling = static_cast<int>((data.angle2 - data.angle1) * 8 / M_PI);
    QString device = QString("C,%1*").arg(DEFAULT_THICKNESS);
    double major_len = qSqrt(qPow(data.mx, 2) + qPow(data.my, 2));
    double minor_len = (qPow(data.mx, 2) + qPow(data.my, 2)) * ( qPow(data.ratio, 2) );
    QVariantList objects;
    if (AUTOFILL) {
        objects.push_back(QVariantMap{
                              { "layer", layer },
                              { "command", "G36*" }
                          });
    }
    for (int step = 0; step < sampling; step++) {
        double t = (data.angle2 - data.angle1) * step / sampling;
        double x = data.cx + major_len * qCos(t) * qCos(tilt) - minor_len * qSin(t) * qSin(tilt);
        double y = data.cy + major_len * qCos(t) * qSin(tilt) - minor_len * qSin(t) * qCos(tilt);
        objects.push_back(QVariantMap{
                              { "layer", layer },
                              { "device", device },
                              { "x", x },
                              { "y", y },
                              { "style", "D01" }
                          });
    }
    auto first = objects.first().toMap();
    first.insert("style", "D02");
    objects[0] = first;

    if (AUTOFILL) {
        objects.push_back(QVariantMap{
                              { "layer", layer },
                              { "command", "G37*" }
                          });
    }
    if (!this->current_block.isEmpty()) {
        this->current_block_objects.append(objects);
    } else {
        process(objects, true);
    }
}

void L2_DxfAdapter::addPolyline(const DL_PolylineData &data)
{
    PRINT_FUNC;
    this->current_polyline = data;
}

static QVector2D perpendicular(const QVector2D &a)
{
    return QVector2D{ a.y(), -a.x() };
}

void L2_DxfAdapter::addVertex(const DL_VertexData &data)
{
    PRINT_FUNC;
    this->current_polyline_vertexs.push_back(data);
    if (this->current_polyline_vertexs.size() == this->current_polyline.number) {
        // analyze
        QString layer = QString::fromStdString(this->attributes.getLayer());
        bool closed = (this->current_polyline.flags == 1);
        QVariantList objects;
        for (int index = 0; index < this->current_polyline_vertexs.size() - !closed; index++) {
            DL_VertexData start_vertex = this->current_polyline_vertexs.at(index);
            DL_VertexData end_vertex = this->current_polyline_vertexs.at((index + 1) % this->current_polyline_vertexs.size());
            double start_bulge = start_vertex.bulge;
            double start_width = 0.0;
            double end_width = 0.0;
            QVector2D start { static_cast<float>(start_vertex.x), static_cast<float>(start_vertex.y) };
            QVector2D end { static_cast<float>(end_vertex.x), static_cast<float>(end_vertex.y) };
            QString device = QString("C,%1*").arg(DEFAULT_THICKNESS);
            bool contours = (start_width != 0 || end_width != 0);
            QVector2D ortholine = perpendicular(end - start);
            float ortholine_l = ortholine.length();

            QVector2D start1, start2, end1, end2;
            if (start_bulge) {
                double opening_angle = qAtan(start_bulge) * 4;
                QVector2D rel_start = (end - start) / 2 - ortholine / ( 2 * qTan(opening_angle / 2) );
                QVector2D rel_end = start - end + rel_start;
                float radius = rel_start.length();
                start1 = start - rel_start * 0.5 * start_width / radius;
                start2 = start + rel_start * 0.5 * start_width / radius;
                end1 = end - rel_end * 0.5 * end_width / radius;
                end2 = end + rel_end * 0.5 * end_width / radius;
            } else if (ortholine_l) {
                start1 = start - ortholine * 0.5 * start_width / ortholine_l;
                start2 = start + ortholine * 0.5 * start_width / ortholine_l;
                end1 = end - ortholine * 0.5 * end_width / ortholine_l;
                end2 = end + ortholine * 0.5 * end_width / ortholine_l;
            } else {
                start1 = start;
                start2 = start;
                end1 = end;
                end2 = end;
            }
            if (start_bulge) {
                double opening_angle = qAtan(start_bulge) * 4;
                QString mode = start_bulge > 0 ? "G03" : "G02";
                QString inv_mode = start_bulge > 0 ? "G02" : "G03";
                objects.append(QVariantMap{
                                   { "layer", layer },
                                   { "command", "G75*" }
                               });
                if (contours) {
                    auto ortho1 = perpendicular(end1 - start1);
                    auto ortho2 = perpendicular(end2 - start2);
                    auto cycle1 = -(end1 - start1) / 2 - ortho1 / ( 2 * qTan(opening_angle / 2) );
                    auto cycle2 = (end2 - start2) / 2 - ortho2 / ( 2 * qTan(opening_angle / 2) );
                    objects.append(QVariantMap{
                                       { "layer", layer },
                                       { "command", "G36*" }
                                   });
                    objects.append(QVariantMap{
                                       { "layer", layer },
                                       { "device", "C,0.001*" },
                                       { "mode", "G01" },
                                       { "x", start1.x() },
                                       { "y", start1.y() },
                                       { "style", "D02" }
                                   });
                    objects.append(QVariantMap{
                                       { "layer", layer },
                                       { "device", "C,0.001*" },
                                       { "mode", "G01" },
                                       { "x", start2.x() },
                                       { "y", start2.y() },
                                       { "style", "D01" }
                                   });
                    objects.append(QVariantMap{
                                       { "layer", layer },
                                       { "device", "C,0.001*" },
                                       { "mode", mode },
                                       { "x", end2.x() },
                                       { "y", end2.y() },
                                       { "i", cycle2.x() },
                                       { "j", cycle2.y() },
                                       { "style", "D01" }
                                   });
                    objects.append(QVariantMap{
                                       { "layer", layer },
                                       { "device", "C,0.001*" },
                                       { "mode", "G01" },
                                       { "x", end1.x() },
                                       { "y", end1.y() },
                                       { "style", "D01" }
                                   });
                    objects.append(QVariantMap{
                                       { "layer", layer },
                                       { "device", "C,0.001*" },
                                       { "mode", inv_mode },
                                       { "x", start1.x() },
                                       { "y", start1.y() },
                                       { "i", cycle1.x() },
                                       { "j", cycle1.y() },
                                       { "style", "D01" }
                                   });
                } else {
                    auto rel = - (start - end) / 2 - ortholine / ( 2 * qTan(opening_angle / 2) );
                    objects.append(QVariantMap{
                                       { "layer", layer },
                                       { "device", device },
                                       { "mode", "G01" },
                                       { "x", start.x() },
                                       { "y", start.y() },
                                       { "style", "D02" }
                                   });
                    objects.append(QVariantMap{
                                       { "layer", layer },
                                       { "device", device },
                                       { "mode", mode },
                                       { "x", end.x() },
                                       { "y", end.y() },
                                       { "i", rel.x() },
                                       { "j", rel.y() },
                                       { "style", "D01" }
                                   });
                }
                objects.append(QVariantMap{
                                   { "layer", layer },
                                   { "command", "G01*" }
                               });
            } else if (ortholine_l > 0) {
                if (contours) {
                    objects.append(QVariantMap{
                                       { "layer", layer },
                                       { "command", "G36*" }
                                   });
                    objects.append(QVariantMap{
                                       { "layer", layer },
                                       { "device", "C,0.001*" },
                                       { "x", start1.x() },
                                       { "y", start1.y() },
                                       { "style", "D02" }
                                   });
                    objects.append(QVariantMap{
                                       { "layer", layer },
                                       { "device", "C,0.001*" },
                                       { "x", start2.x() },
                                       { "y", start2.y() },
                                       { "style", "D01" }
                                   });
                    objects.append(QVariantMap{
                                       { "layer", layer },
                                       { "device", "C,0.001*" },
                                       { "x", end2.x() },
                                       { "y", end2.y() },
                                       { "style", "D01" }
                                   });
                    objects.append(QVariantMap{
                                       { "layer", layer },
                                       { "device", "C,0.001*" },
                                       { "x", end1.x() },
                                       { "y", end1.y() },
                                       { "style", "D01" }
                                   });
                    objects.append(QVariantMap{
                                       { "layer", layer },
                                       { "device", "C,0.001*" },
                                       { "x", start1.x() },
                                       { "y", start1.y() },
                                       { "style", "D01" }
                                   });
                    objects.append(QVariantMap{
                                       { "layer", layer },
                                       { "command", "G37*" }
                                   });
                } else {
                    objects.append(QVariantMap{
                                       { "layer", layer },
                                       { "device", device },
                                       { "x", start.x() },
                                       { "y", start.y() },
                                       { "style", "D02" },
                                   });
                    objects.append(QVariantMap{
                                       { "layer", layer },
                                       { "device", device },
                                       { "x", end.x() },
                                       { "y", end.y() },
                                       { "style", "D01" },
                                   });
                }
            }
        }

        // try really closed poly and remove doubled lines
        if (AUTOFILL && closed) {
            for (QVariantList::iterator it = objects.begin(); it != objects.end(); ) {
                QString command = it->toMap().value("command").toString();
                if (command == "G36*" || command == "G37*") {
                    it = objects.erase(it);
                } else {
                    it++;
                }
            }
            bool first = true;
            for (auto & o : objects) {
                QVariantMap oMap = o.toMap();
                if (oMap.contains("style")) {
                    oMap.insert("style", first ? "D02" : "D01");
                    first = false;
                }
                o = oMap;
            }
            objects.prepend(QVariantMap{
                                { "layer", layer },
                                { "command", "G36*" }
                            });
            objects.append(QVariantMap{
                               { "layer", layer },
                               { "command", "G37*" }
                           });
        }

        if (!this->current_block.isEmpty()) {
            this->current_block_objects.append(objects);
        } else {
            process(objects, true);
        }

        // clear
        this->current_polyline_vertexs.clear();
    }
}

void L2_DxfAdapter::addSpline(const DL_SplineData &)
{
    PRINT_FUNC;
}

void L2_DxfAdapter::addControlPoint(const DL_ControlPointData &)
{
    PRINT_FUNC;
}

void L2_DxfAdapter::addFitPoint(const DL_FitPointData &)
{
    PRINT_FUNC;
}

void L2_DxfAdapter::addKnot(const DL_KnotData &)
{
    PRINT_FUNC;
}

void L2_DxfAdapter::addInsert(const DL_InsertData &data)
{
    PRINT_FUNC;
    QString block = QString::fromStdString(data.name);
    QString layer = QString::fromStdString(this->attributes.getLayer());
    double rotation = data.angle / 180 * M_PI;
    bool switch_ccw = (data.sx * data.sy < 0);

    QVariantList objects;
    for (auto obj : this->blocks.value(block)) {
        QVariantMap objMap = obj.toMap();
        if (objMap.contains("x")) {
            double x = data.sx * objMap.value("x").toDouble();
            double y = data.sy * objMap.value("y").toDouble();
            objMap["x"] = x * qCos(rotation) - y * qSin(rotation) + data.ipx;
            objMap["y"] = x * qSin(rotation) + y * qCos(rotation) + data.ipy;
        }
        if (objMap.contains("i")) {
            double i = data.sx * objMap.value("i").toDouble();
            double j = data.sy * objMap.value("j").toDouble();
            objMap["i"] = i * qCos(rotation) - j * qSin(rotation);
            objMap["j"] = i * qSin(rotation) + j * qCos(rotation);
        }
        if (!block.startsWith('*')) {
            objMap.insert("layer", layer);
        }
        if (switch_ccw && objMap.contains("mode")) {
            if (objMap.value("mode").toString() == "G03") {
                objMap["mode"] = "G02";
            } else if (objMap.value("mode").toString() == "G02") {
                objMap["mode"] = "G03";
            }
        }
        objects.push_back(objMap);
    }
    process(objects, true);
}

void L2_DxfAdapter::addMText(const DL_MTextData &)
{
    PRINT_FUNC;
}

void L2_DxfAdapter::addMTextChunk(const std::string &)
{
    PRINT_FUNC;
}

void L2_DxfAdapter::addText(const DL_TextData &)
{
    PRINT_FUNC;
}

void L2_DxfAdapter::addArcAlignedText(const DL_ArcAlignedTextData &)
{
    PRINT_FUNC;
}

void L2_DxfAdapter::addAttribute(const DL_AttributeData &)
{
    PRINT_FUNC;
}

void L2_DxfAdapter::addDimAlign(const DL_DimensionData &, const DL_DimAlignedData &)
{
    PRINT_FUNC;
}

void L2_DxfAdapter::addDimLinear(const DL_DimensionData &, const DL_DimLinearData &)
{
    PRINT_FUNC;
}

void L2_DxfAdapter::addDimRadial(const DL_DimensionData &, const DL_DimRadialData &)
{
    PRINT_FUNC;
}

void L2_DxfAdapter::addDimDiametric(const DL_DimensionData &, const DL_DimDiametricData &)
{
    PRINT_FUNC;
}

void L2_DxfAdapter::addDimAngular(const DL_DimensionData &, const DL_DimAngularData &)
{
    PRINT_FUNC;
}

void L2_DxfAdapter::addDimAngular3P(const DL_DimensionData &, const DL_DimAngular3PData &)
{
    PRINT_FUNC;
}

void L2_DxfAdapter::addDimOrdinate(const DL_DimensionData &, const DL_DimOrdinateData &)
{
    PRINT_FUNC;
}

void L2_DxfAdapter::addLeader(const DL_LeaderData &)
{
    PRINT_FUNC;
}

void L2_DxfAdapter::addLeaderVertex(const DL_LeaderVertexData &)
{
    PRINT_FUNC;
}

void L2_DxfAdapter::addHatch(const DL_HatchData &)
{
    PRINT_FUNC;
}

void L2_DxfAdapter::addTrace(const DL_TraceData &)
{
    PRINT_FUNC;
}

void L2_DxfAdapter::add3dFace(const DL_3dFaceData &)
{
    PRINT_FUNC;
}

void L2_DxfAdapter::addSolid(const DL_SolidData &)
{
    PRINT_FUNC;
}

void L2_DxfAdapter::addImage(const DL_ImageData &)
{
    PRINT_FUNC;
}

void L2_DxfAdapter::linkImage(const DL_ImageDefData &)
{
    PRINT_FUNC;
}

void L2_DxfAdapter::addHatchLoop(const DL_HatchLoopData &)
{
    PRINT_FUNC;
}

void L2_DxfAdapter::addHatchEdge(const DL_HatchEdgeData &)
{
    PRINT_FUNC;
}

void L2_DxfAdapter::addXRecord(const std::string &)
{
    PRINT_FUNC;
}

void L2_DxfAdapter::addXRecordString(int, const std::string &)
{
    PRINT_FUNC;
}

void L2_DxfAdapter::addXRecordReal(int, double)
{
    PRINT_FUNC;
}

void L2_DxfAdapter::addXRecordInt(int, int)
{
    PRINT_FUNC;
}

void L2_DxfAdapter::addXRecordBool(int, bool)
{
    PRINT_FUNC;
}

void L2_DxfAdapter::addXDataApp(const std::string &)
{
    PRINT_FUNC;
}

void L2_DxfAdapter::addXDataString(int, const std::string &)
{
    PRINT_FUNC;
}

void L2_DxfAdapter::addXDataReal(int, double)
{
    PRINT_FUNC;
}

void L2_DxfAdapter::addXDataInt(int, int)
{
    PRINT_FUNC;
}

void L2_DxfAdapter::process(const QVariantList &objects, bool append)
{
    for (int i = 0; i < objects.size(); i++) {
        QVariantMap oMap = objects.at(i).toMap();
        QString layer = oMap.value("layer").toString();
        if (!this->layers.contains(layer)) {
            this->layers.insert(layer, QVariantList{ oMap });
        } else if (append) {
            auto objs = this->layers.value(layer);
            objs.push_back(oMap);
            this->layers[layer] = objs;
        } else {
            auto objs = this->layers.value(layer);
            objs.insert(i, oMap);
            this->layers[layer] = objs;
        }
    }
}
