#include "Display/ErrorHandler.h"
#include "Display/QDisplay.h"
#include "LFTPHandler.h"
#include <imgui_impl_glfw.h>
#include <memory>

int main() {

  std::srand(std::time(nullptr));

  while (!glfwWindowShouldClose(QDisplay::GetInstance().getWindow())) {

    // Clean OpenGL frame & imgui interface
    QDisplay::clearFrame();

    // Only render if no errors detected
    if (!ErrorHandler::GetInstance().hasError()) {
      // UI logic
      QDisplay::GetInstance().drawMenus();
    }

    LFTPHandler::GetInstance().update();

    // Display any captured errors as a modal popup over the top of the screen
    ErrorHandler::GetInstance().pollErrors();

    // Process and catch events, draw ui
    QDisplay::processFrameAndEvents();
  }

  return 0;
}
