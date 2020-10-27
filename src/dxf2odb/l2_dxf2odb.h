#ifndef L2_DXF2ODB_H
#define L2_DXF2ODB_H

#include <QString>
#include "l2_dxf2odb_global.h"

class L2_DXF2ODBSHARED_EXPORT L2_Dxf2Odb
{
public:
    static bool run(const QString &dxfPath, const QString &odbPath, QString *err);
};

#endif // L2_DXF2ODB_H
