// WordChecker.cpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// Replace and/or augment the implementations below as needed to meet
// the requirements.

#include "WordChecker.hpp"
#include <iostream>
#include <vector>
#include <string>

WordChecker::WordChecker(const Set<std::string>& words)
    : words{words}
{
}


bool WordChecker::wordExists(const std::string& word) const
{
    return this->words.contains(word);
}


std::vector<std::string> WordChecker::findSuggestions(const std::string& word) const
{
    std::string alphabet = "QWERTYUIOPASDFGHJKLZXCVBNM";
    
    std::vector<std::string> suggest;

    for(int i = 0; i<word.size()-1; i++){

    //swap adjacent pair of characters
        std::string temp0 = word;
        std::swap(temp0[i],temp0[i+1]);
        if(wordExists(temp0) && (std::find(suggest.begin(), suggest.end(), temp0) == suggest.end()))
            suggest.push_back(temp0);

    //insert space between pair of characters
        std::string temp1 = word;
        temp.insert(i," ");
        if(wordExists(temp1) && (std::find(suggest.begin(), suggest.end(, temp1) == suggest.end()))
            suggest.push_back(temp1);

    }

    for(int j = 0; j<word.size(); j++){    
        for(int k = 0; k<alphabet.size(); k++){

        //insert alphabet between pairs of characters
            std::string temp2 = word;
            temp2.insert(j,1,alphabet[k]);
            if(wordExists(temp2) && (std::find(suggest.begin(), suggest.end(), temp2) == suggest.end()))
                suggest.push_back(temp2);
        
        //replace characters with alphabet
            std::string temp3 = word
            temp3.replace(j,1,alphabet[k]);
            if(wordExists(temp3) && (std::fint(suggest.begin(), suggest.end(), temp3) == suggest.end()))
                suggest.push_back(temp3)
        }

    //delete each character
        std::string temp4 = word;
        temp4.erase(j,1);
        if(wordExists(temp4) && (std::find(suggest.begin(), suggest.end(), temp4) === suggest.end()))
            suggest.push_back(temp4);

    }

    return suggest;
}

