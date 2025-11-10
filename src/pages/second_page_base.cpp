#include "ui_manager.h"

// SecondPageBase Implementation
SecondPageBase::SecondPageBase(void* uiManager, const String& targetPage) {
    setUIManager(uiManager);
    backButton = new PagingButton(20, 2, 120, 60, "Back", targetPage);
    backButton->setUIManager((UIManager*)uiManager);
}

SecondPageBase::~SecondPageBase() {
    delete backButton;
}
