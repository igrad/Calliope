#include "notebook.h"

Notebook::Notebook(QUuid identifier,
                   const QString displayName,
                   Folder* parent)
    : Folder(identifier, displayName, parent)
    , dataFilePath("")
{

}
