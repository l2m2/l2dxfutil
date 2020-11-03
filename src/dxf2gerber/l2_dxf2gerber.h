#ifndef L2_DXF2GERBER_H
#define L2_DXF2GERBER_H

#include <QString>
#include "l2_dxf2gerber_global.h"

class L2_DXF2GERBERSHARED_EXPORT L2_Dxf2Gerber
{
public:
    /*!
     * \brief 将DXF转换到目录下，Gerber的文件名是对应Layer的名称
     */
    static bool toDir(const QString &dxfPath, const QString &gerberDir, QString *err);
    /*!
     * \brief 将DXF转换成QString
     */
    static bool toString(const QString &dxfPath, QString *gerberStr, QString *err);
};

#endif // L2_DXF2GERBER_H
