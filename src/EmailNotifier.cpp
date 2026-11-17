#include "EmailNotifier.h"

#include <iostream>

void EmailNotifier::notifyBookAdded(const Book&) {
    std::cout << "Sending email notification about the new book..."
              << std::endl;
}
