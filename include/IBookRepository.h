#pragma once
#include "Book.h"

//абстракція сховища книг, від якої тепер залежить Library 
class IBookRepository {
public:
    virtual ~IBookRepository() = default;
    virtual void save(const Book& book) = 0;
};
