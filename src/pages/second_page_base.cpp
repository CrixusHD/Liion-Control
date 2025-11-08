#include "ui_manager.h"

// SecondPageBase Implementation
SecondPageBase::SecondPageBase(void* uiManager, const String& targetPage) {
    setUIManager(uiManager);
    backButton = new Button(20, 2, 100, 40, "Back", targetPage);
    backButton->setUIManager(uiManager);
}

SecondPageBase::~SecondPageBase() {
    delete backButton;
}
