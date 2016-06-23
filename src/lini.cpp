#include "lini.h"

Lini::Lini(std::string filename)
{
    //We initialize our variable.
    this->filename = filename;
    this->error = false;

    //Open our current file

    this->file.open(filename);


    std::string actual_line,actual_section,key,value;

    bool in_section = false;

    //To save our current section.
    std::unordered_map<std::string,std::string> section;

    //Check if the file is good
    if(this->file.is_open())
    {
        //Read everyline
        while(std::getline(file,actual_line))
        {
            // Line is empty? Skip the line.
            if(!actual_line.size())
                continue;

            // section found
            if(actual_line[0] == '[' && actual_line[actual_line.size() - 1] == ']')
            {
                if(actual_section != this->S_Get_section(actual_line))
                {
                    //Not empty section or first section/line
                    if(!section.empty() && !actual_section.empty())
                    {
                        //We add to our file the finished section.
                        config[actual_section] = section;

                        // Clear the current section
                        section.clear();
                    }
                    //Set new section
                    actual_section = this->S_Get_section(actual_line);
                }
                in_section = true;
            }
            else
            {
                //in_section

                if(in_section)
                {
                    //Get our line
                    if(this->Get_Line(actual_line,key,value))
                    {
                        section[key] = value;
                    }
                    else
                    {
                        //this is a commentary? do nothing.
                    }
                }
            }
        }
        //Add our last section
        if(!section.empty())
        {
            config[actual_section] = section;
            section.clear();
        }


        //don't need the file anymore.
        file.close();
    }
    else
    {
        // Some random error.
        this->error = true;
    }
}

void Lini::Close()
{
    //Safe check for our current file
    if(filename.size() == 0)
        return;
    // We already have our file in the buffer, so we delete the content of our file.
    this->file.open(filename, std::ofstream::out | std::ofstream::trunc);

    // Here, we set up the content for the ending of file. Plus, handling the last empty line in the file.
    std::size_t count = 0,total_section = config.size(),total_key,key_count = 0;



    //We start to go through every section
    for(auto section: config)
    {
        ++count;
        key_count = 0;

        file << '[' + section.first + ']' << std::endl;
        total_key = section.second.size();
        //We start to go through every key
        for(auto key : section.second)
        {
            ++key_count;
            if(key_count != total_key)
            {
                file << key.first + " = " + key.second << std::endl;
            }
            else
            {
                file << key.first + " = " + key.second;
            }

        }
        if(count != total_section)
        {
            file << std::endl << std::endl;
        }
    }


    //We clear the old content.
    this->config.clear();
    this->filename.clear();
    this->file.close();
}


 bool Lini::Error()
 {
     return this->error;
 }



//Set functions



void Lini::Set(std::string section,std::string key,std::string value)
{
    config[section][key] = value;
}

void Lini::Set_Int(std::string section,std::string key,unsigned long long value)
{
    this->Set(section,key,std::to_string(value));
}

void Lini::Set_Real(std::string section,std::string key,double value)
{
    this->Set(section,key,std::to_string(value));
}

void Lini::Set_Boolean(std::string section,std::string key,bool value)
{
    if(value)
        this->Set(section,key,"True");
    else
        this->Set(section,key,"False");
}


// Get functions



std::string Lini::Get(std::string section,std::string key)
{
    if(!this->config.count(section) || !this->config[section].count(key))
    {
        return "";
    }
    return this->config[section][key];
}

unsigned long long Lini::Get_Int(std::string section,std::string key)
{
    std::string::size_type sz = 0;
    const std::string str = this->Get(section,key);

    return str.size() ? std::stoull(str,&sz,0) : 0;
}

double Lini::Get_Real(std::string section,std::string key)
{
    std::string::size_type sz;
    const std::string str = this->Get(section,key);

    return str.size() ? std::stod(str,&sz) : 0;
}

bool Lini::Get_Boolean(std::string section,std::string key)
{
    const std::string str = this->Get(section,key);
    return str == "True" ? true : false;
}



std::set<std::string> Lini::Get_Section() const
{
    std::set<std::string> buffer;
    for(auto section: config)
    {
        buffer.insert(section.first);
    }
    return buffer;
}

 std::set<std::string> Lini::Get_Fields(std::string section)
 {
     std::set<std::string> buffer;

     if(!config.count(section))
         return buffer;


     for(auto key : config[section] )
     {
         buffer.insert(key.first);
     }
     return buffer;
 }




//Delete functions


bool Lini::Del_Key(std::string section,std::string key)
{
    return config[section].erase(key);
}

bool Lini::Del_Section(std::string section)
{
    return config.erase(section);
}






//SNIPPETS



inline std::string Lini::S_Get_section(std::string line) const
{
    line.erase(line.begin());
    line.erase(line.end() - 1);

    return line;
}




bool Lini::Get_Line(const std::string line, std::string &key,std::string &value)
{
    auto found = line.find('=');
    if(found)
    {
        //This is valid.

        key = line.substr(0,found - 1);
        value = line.substr(found + 2, line.size() - 1);


        return true;
    }
    //This is a commentary? do nothing.
    return false;
}
