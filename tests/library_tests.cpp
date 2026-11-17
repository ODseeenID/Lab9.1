#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <vector>

#include "Book.h"
#include "IBookRepository.h"
#include "INotifier.h"
#include "Library.h"

namespace {

// спільний журнал викликів
using Log = std::vector<std::string>;

class FakeRepository : public IBookRepository {
public:
    explicit FakeRepository(Log& log) : log_(log) {}
    void save(const Book& book) override {
        log_.push_back("save:" + book.getTitle());
    }
private:
    Log& log_;
};

class FakeNotifier : public INotifier {
public:
    explicit FakeNotifier(Log& log) : log_(log) {}
    void notifyBookAdded(const Book& book) override {
        log_.push_back("notify:" + book.getTitle());
    }
private:
    Log& log_;
};

// ще одна реалізація інтерфейсів, про яку Library не знає
class CountingNotifier : public INotifier {
public:
    void notifyBookAdded(const Book&) override { ++count; }
    int count = 0;
};

}  // namespace

TEST(BookTest, ExposesDataThroughGetters) {
    Book book("Dune", "Frank Herbert");
    EXPECT_EQ(book.getTitle(), "Dune");
    EXPECT_EQ(book.getAuthor(), "Frank Herbert");
}

TEST(BookTest, StreamOutputMatchesOriginalFormat) {
    std::ostringstream out;
    out << Book("Dune", "Frank Herbert");
    EXPECT_EQ(out.str(), "Title: Dune, Author: Frank Herbert");
}

TEST(LibraryTest, AddBookStoresBook) {
    Log log;
    FakeRepository repo(log);
    FakeNotifier notifier(log);
    Library library(repo, notifier);

    library.addBook(Book("Dune", "Frank Herbert"));

    ASSERT_EQ(library.getBooks().size(), 1u);
    EXPECT_EQ(library.getBooks()[0].getTitle(), "Dune");
}

TEST(LibraryTest, AddBookSavesThenNotifiesInOrder) {
    Log log;
    FakeRepository repo(log);
    FakeNotifier notifier(log);
    Library library(repo, notifier);

    library.addBook(Book("Dune", "Frank Herbert"));

    Log expected = {"save:Dune", "notify:Dune"};
    EXPECT_EQ(log, expected);
}

TEST(LibraryTest, EachAddedBookIsSavedAndNotifiedOnce) {
    Log log;
    FakeRepository repo(log);
    FakeNotifier notifier(log);
    Library library(repo, notifier);

    library.addBook(Book("A", "x"));
    library.addBook(Book("B", "y"));

    Log expected = {"save:A", "notify:A", "save:B", "notify:B"};
    EXPECT_EQ(log, expected);
}

TEST(LibraryTest, DisplayBooksPrintsEveryBookInOrder) {
    Log log;
    FakeRepository repo(log);
    FakeNotifier notifier(log);
    Library library(repo, notifier);
    library.addBook(Book("The Catcher in the Rye", "J.D. Salinger"));
    library.addBook(Book("To Kill a Mockingbird", "Harper Lee"));

    std::ostringstream out;
    library.displayBooks(out);

    EXPECT_EQ(out.str(),
              "Title: The Catcher in the Rye, Author: J.D. Salinger\n"
              "Title: To Kill a Mockingbird, Author: Harper Lee\n");
}

TEST(LibraryTest, ImplementationsCanBeReplacedWithoutChangingLibrary) {
    Log log;
    FakeRepository repo(log);
    CountingNotifier notifier;
    Library library(repo, notifier);

    library.addBook(Book("A", "x"));
    library.addBook(Book("B", "y"));

    EXPECT_EQ(notifier.count, 2);
}
