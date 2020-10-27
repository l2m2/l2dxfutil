#include "l2_dxf2odb.h"
#include <QFile>
#include "../dxflib/dl_dxf.h"
#include "l2_creationadapter.h"

bool L2_Dxf2Odb::run(const QString &dxfPath, const QString &odbPath, QString *err)
{
    if (!QFile::exists(dxfPath)) {
        *err = "DXF file does not exist.";
        return false;
    }
    DL_Dxf *dxf = new DL_Dxf();
    L2_CreationAdapter *creation = new L2_CreationAdapter();
    bool ok = dxf->in(dxfPath.toStdString(), creation);
    return ok;
}
