#include "notebook.h"

Notebook::Notebook(const std::string identifier,
                   const std::string displayName,
                   Folder* parent):
    Folder(identifier, displayName, parent),
    _dataFilePath("")
{

}
