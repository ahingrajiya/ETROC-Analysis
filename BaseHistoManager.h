/**
 * @file BaseHistoManager.h
 * @author Abhishek Hingrajiya (ahingr2@uic.edu)
 * @brief Base class for histogram managers
 * @version 0.1
 * @date 2024-08-20
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef BaseHistoManager_h
#define BaseHistoManager_h

// ROOT headers
#include "TList.h"

//________________
class BaseHistoManager
{
public:
    /// @brief Constructor
    BaseHistoManager() { /* empty */ }
    /// @brief Destructor
    virtual ~BaseHistoManager() { /* empty */ }

    // // @brief Return list of objects (histograms, profiles, graphs, etc...)
    // virtual TList *getOutputList() = 0;

    ClassDef(BaseHistoManager, 0)
};

#endif // #define BaseHistoManager_h