#include <MAUtil/Moblet.h>
#include "screens/ScreenMain.h"

using namespace MAUtil;
using namespace NativeUI;
using Shoplist455::ScreenMain;

class NativeUIMoblet: public Moblet {
public:
    NativeUIMoblet() {
        ScreenMain* screenMain = new ScreenMain(this);
        screenMain->show();
    }

    virtual ~NativeUIMoblet() {
    }

    void keyPressEvent(int keyCode, int nativeCode) {
    }

private:
};

/**
 * Main function that is called when the program starts.
 */
extern "C" int MAMain() {
    Moblet::run(new NativeUIMoblet());
    return 0;
}
