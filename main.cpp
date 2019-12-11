#include <iostream>
#include "Window.h"

int main() {
    Window window(1280, 720, "Title");

    while (window.isOpen()) {
        auto frame = window.newFrame();
    }

    return 0;
}
