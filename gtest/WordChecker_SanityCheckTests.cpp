// WordChecker_SanityCheckTests.cpp
//
// This is a set of "sanity checking" unit tests for your WordChecker
// implementation, provided primarily as a mechanism for ensuring that
// your implementation is compatible with the unit tests we'll be using
// to test it.  The goal here is to ensure that you have all of the
// necessary member functions, that their type declarations are as they
// should be, and that you've organized your code correctly as a template
// so that these tests will compile and link.  These tests don't verify
// the functionality; that'll be up to you to test on your own.

#include <string>
#include <vector>
#include <gtest/gtest.h>
#include "ListSet.hpp"
#include "WordChecker.hpp"


TEST(WordChecker_SanityCheckTests, canCreateWithSetOfStrings)
{
    WordChecker w{ListSet<std::string>{}};
}


TEST(WordChecker_SanityCheckTests, canCheckIfWordExists)
{
    WordChecker w{ListSet<std::string>{}};
    bool b = w.wordExists("Boo");
    b = false;
}


TEST(WordChecker_SanityCheckTests, canFindSuggestions)
{
    WordChecker w{ListSet<std::string>{}};
    std::vector<std::string> suggestions = w.findSuggestions("Boo");
    suggestions.clear();
}

