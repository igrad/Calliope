#include "notebook.h"

Notebook::Notebook()
    : displayName("")
    , dataFilePath("")
{

}

Notebook::Notebook(QUuid identifier,
                   const QString displayName,
                   Folder* parent)
    : Folder(identifier, displayName, parent)
    , dataFilePath("")
{

}
