#ifndef LINI_H

#define LINI_H

//#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <set>




class Lini
{
public:
    Lini(std::string filename);
    ~Lini()
    {
        this->Close();
    }

    //Will return true if an error occurred.
    bool Error();


    // Set functions

    // Set will create/modify a section/key/value, same for the similar functions.
    void Set(std::string section,std::string key,std::string value);
    void Set_Int(std::string section,std::string key,unsigned long long value);
    void Set_Real(std::string section,std::string key,double value);
    void Set_Boolean(std::string section,std::string key,bool value);

    // Read functions.

    //This function will return a empty string, if there is no section or key.
    std::string Get(std::string section,std::string key);

    //This will return 0, if there is no section or key.
    unsigned long long Get_Int(std::string section,std::string key);

    //This will return 0, if there is no section or key.
    double Get_Real(std::string section,std::string key);

    //This will return 0, if there is no section or key.
    bool Get_Boolean(std::string section,std::string key);

    //Section func

    //This function will return a set of unique strings.
    std::set<std::string> Get_Section() const;

    //This function will return a set of unique strings;
    std::set<std::string> Get_Fields(std::string section);

    // Delete/close function

    //This function will return true if is sucessful.
    bool Del_Key(std::string section,std::string key);

    //This function will return true if is sucessful.
    bool Del_Section(std::string section);

    //Will add the new content to the file.
    void Close();

private:
    // Variables
    std::string filename;
    std::fstream file;
    std::unordered_map<std::string, std::unordered_map<std::string,std::string>> config;
    bool error;


    // snippets

    //function to get the current section;
    inline std::string S_Get_section(std::string line) const;

    //function to get the current key and its value;
    bool Get_Line(const std::string line, std::string &key,std::string &value);
};

#endif // LINI_H
