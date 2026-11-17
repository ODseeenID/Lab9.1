#include "DatabaseBookRepository.h"
#include "EmailNotifier.h"
#include "Library.h"

int main() {
    //composition root
    DatabaseBookRepository repository;
    EmailNotifier notifier;
    Library library(repository, notifier);

    Book book1{"The Catcher in the Rye", "J.D. Salinger"};
    Book book2{"To Kill a Mockingbird", "Harper Lee"};

    library.addBook(book1);
    library.addBook(book2);
    library.displayBooks();
    return 0;
}
