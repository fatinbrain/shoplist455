#include "StorageWorks.h"

StorageWorks::StorageWorks(const String s, NativeUI::Label *l) :
        storageName(s), lbDbg(l) {
}

bool StorageWorks::exists() {
    bool rez = false;

    dbgLb("str checking");
    storage = maOpenStore(storageName.c_str(), 0);

    if (storage == STERR_NONEXISTENT) {
        dbgLb("no store detected");
    } else {
        rez = true;
        dbgLb("store exists");
    }

    return rez;
}

int StorageWorks::write(const String data) {
    dbgLb("str write");

    int ret = -1;

    if (!exists()) {
        createStorage();
    }

    MAHandle phData = maCreatePlaceholder();

    if (maCreateData(phData, data.length()) == RES_OK) {
        maWriteData(phData, data.c_str(), 0, data.length());

        int rc = maWriteStore(storage, phData);

        if (rc > 0) {
            closeStorage();
            dbgLb("data written");
            ret = 0;
        } else {
            dbgLb("data write FAULT");
        }
    } else {
        dbgLb("createData FAULT");
    }

    return ret;
}

String StorageWorks::getName() {
    return this->storageName;
}

String StorageWorks::read() {
    String rData = "";

    dbgLb("str read...");
    MAHandle phData = maCreatePlaceholder();
    storage = maOpenStore(storageName.c_str(), 0);
    if (storage != STERR_NONEXISTENT) {
        int rc = maReadStore(storage, phData);
        if (rc != RES_OUT_OF_MEMORY) {
            char data[maGetDataSize(phData)];
            maReadData(phData, &data, 0, maGetDataSize(phData));
            rData += data;
            rData = rData.substr(0, rData.length());
            dbgLb(rData.c_str());
        } else {
            dbgLb("out of mem");
        }
    } else {
        dbgLb("store not exists");
    }

    return rData;
}

void StorageWorks::setDbgLabel(NativeUI::Label *l) {
    lbDbg = l;
}

void StorageWorks::dbgLb(const String message) {
    if (lbDbg != NULL) {
        lbDbg->setText(message);
    } else {
        printf("  //%s\n", message.c_str());
    }
}

void StorageWorks::setStoreName(String storageName) {
    this->storageName = storageName;
}

void StorageWorks::test() {
    dbgLb("StorageWorks v" VER);
}

void StorageWorks::closeStorage() {
    if (exists()) {
        maCloseStore(storage, 0);
    }
}

bool StorageWorks::createStorage() {
    storage = maOpenStore(storageName.c_str(), MAS_CREATE_IF_NECESSARY);
    return exists();
}

void StorageWorks::rm() {
    if (exists()) {
        dbgLb("removing storage");
        maCloseStore(storage, 1);
    }
}

