/**
 \mainpage StorageWorks
 \brief ##Easy work with MoSync storages.##

 This project was created to simplify work with MoSync storages.

 It provides class to create, read, write, remove storages.
 **/

/**
 * \file StorageWorks.h
 * \brief Contains StorageWorks class.
 * \version 1.0
 */

#ifndef STORAGEWORKS_H_
#define STORAGEWORKS_H_

#include <ma.h>
#include <MAUtil/String.h>
#include <NativeUI/Widgets.h>
#include <conprint.h>

using namespace MAUtil;

#define VER "1.0"

/**
 \brief Class to maintain MoSync storages.

 Helps to create, remove, read, write storages.
 \version 1.0
 */
class StorageWorks {

private:
    MAHandle storage; /**< \brief Handle of storage*/
    String storageName; /**< \brief Name of storage*/
    NativeUI::Label* lbDbg;
    /**< \brief NativeUI label for debug purposes.
     \note if it is NULL as default, debug messages will flow to console
     */

    /**
     * \brief Function to print debug messages.
     * @param message Debug message.
     */
    void dbgLb(const String message);

    /**
     * \brief Close storage.
     */
    void closeStorage();

    /**
     * \brief Create new storage.
     * @return Result of operation.
     */
    bool createStorage();

public:
    /**\brief Constructor
     \param s Default storage name.
     \param l Pointer to label for debug.
     */
    StorageWorks(const String s = "store01", NativeUI::Label *l = NULL);

    /**
     * \brief Set NativeUI label for debug messages.
     * \note If l is NULL debug messages will be printed in console.
     * @param l Pointer to label.
     */
    void setDbgLabel(NativeUI::Label *l = NULL);

    /**
     * \brief Set storage name.
     * @param storageName Storage name.
     */
    void setStoreName(const String storageName);

    /**
     * \brief Prints hello message with version.
     */
    void test();

    /**
     * \brief Returns name of storage.
     * @return Storage name.
     */
    String getName();

    /**
     * \brief Return *true* if current storage exists on device.
     * @return Existence flag.
     */
    bool exists();

    /**
     * \brief Write data to storage.
     * @param data Data to write.
     * @return  **-1** if errors, **0** normal
     */
    int write(const String data);

    /**
     * \brief Read data from storage on device.
     * @return Data from storage.
     */
    String read();

    /**
     * \brief Remove storage from device.
     */
    void rm();

};

#endif /* STORAGEWORKS_H_ */
