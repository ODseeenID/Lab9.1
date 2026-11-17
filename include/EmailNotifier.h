#pragma once
#include "INotifier.h"

class EmailNotifier : public INotifier {
public:
    void notifyBookAdded(const Book& book) override;
};
