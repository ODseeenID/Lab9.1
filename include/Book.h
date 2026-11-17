#pragma once
#include <ostream>
#include <string>

class Book {
public:
    Book(std::string title, std::string author);

    const std::string& getTitle() const;
    const std::string& getAuthor() const;

private:
    std::string title_;
    std::string author_;
};

std::ostream& operator<<(std::ostream& os, const Book& book);
