#include "notebook.h"

Notebook::Notebook(QUuid identifier,
                   const std::string displayName,
                   Folder* parent)
    : Folder(identifier, displayName, parent)
    , _dataFilePath("")
{

}
