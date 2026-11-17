#pragma once
#include <iostream>
#include <vector>

#include "Book.h"
#include "IBookRepository.h"
#include "INotifier.h"

// Library керує колекцією книг
// Збереження й сповіщення отримує через інтерфейси, тому 
// заміна реалізацій не вимагає змін у цьому класі
class Library {
public:
    Library(IBookRepository& repository, INotifier& notifier);

    void addBook(const Book& book);
    void displayBooks(std::ostream& out = std::cout) const;
    const std::vector<Book>& getBooks() const;

private:
    std::vector<Book> books_;
    IBookRepository& repository_;
    INotifier& notifier_;
};
