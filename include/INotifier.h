#pragma once
#include "Book.h"

// абстракція сповіщення про нову книгу
class INotifier {
public:
    virtual ~INotifier() = default;
    virtual void notifyBookAdded(const Book& book) = 0;
};
