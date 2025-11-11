#include "ui_manager.h"

// SecondPageBase Implementation
SecondPageBase::SecondPageBase(UIManager* uiManager, const String& targetPage) {
    setUIManager(uiManager);
    backButton = new PagingButton(20, 2, 120, 60, "Back", targetPage, uiManager);
}

SecondPageBase::~SecondPageBase() {
    delete backButton;
}
