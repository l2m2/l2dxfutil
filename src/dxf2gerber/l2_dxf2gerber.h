#ifndef L2_DXF2GERBER_H
#define L2_DXF2GERBER_H

#include <QString>
#include "l2_dxf2gerber_global.h"

class L2_DXF2GERBERSHARED_EXPORT L2_Dxf2Gerber
{
public:
    static bool run(const QString &dxfPath, const QString &gerberDir, QString *err);
};

#endif // L2_DXF2GERBER_H
