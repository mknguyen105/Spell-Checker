// SpellCheckShell.hpp
//
// Main console-mode shell for interacting with the spell checker.

#ifndef SPELLCHECKSHELL_HPP
#define SPELLCHECKSHELL_HPP

#include <string>



class SpellCheckShell
{
public:
    void run();


    class ShellException
    {
    public:
        ShellException(const std::string& reason);

        std::string reason() const;

    private:
        std::string reason_;
    };
};



#endif // SPELLCHECKSHELL_HPP

