#include "DatabaseBookRepository.h"

#include <iostream>

void DatabaseBookRepository::save(const Book&) {
    std::cout << "Saving book to database..." << std::endl;
}
