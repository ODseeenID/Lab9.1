#pragma once
#include "IBookRepository.h"

class DatabaseBookRepository : public IBookRepository {
public:
    void save(const Book& book) override;
};
