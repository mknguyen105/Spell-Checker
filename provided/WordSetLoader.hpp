// WordSetLoader.hpp
//
// A class that loads a word set from a file containing one word on each
// line.  The words are then added to the given Set<std::string>.

#ifndef WORDSETLOADER_HPP
#define WORDSETLOADER_HPP

#include <string>
#include "Set.hpp"



class WordSetLoader
{
public:
    void load(const std::string& wordFilePath, Set<std::string>& wordSet);
};



#endif // WORDSETLOADER_HPP

