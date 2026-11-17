#include "Book.h"

#include <utility>

Book::Book(std::string title, std::string author)
    : title_(std::move(title)), author_(std::move(author)) {}

const std::string& Book::getTitle() const { return title_; }
const std::string& Book::getAuthor() const { return author_; }

std::ostream& operator<<(std::ostream& os, const Book& book) {
    return os << "Title: " << book.getTitle()
              << ", Author: " << book.getAuthor();
}
