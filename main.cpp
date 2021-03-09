
#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

//Gjord av David Tammpere och Melker Månsson
//Davids email: tammperedavid@gmail.com
//Melkers email: melkermansson@gmail.com


std::vector<std::string> Rec_Find_Files (const std::string current_dir
,vector<string> File_list)
{
    DIR *pDir;
    struct dirent *pent;
    pDir = opendir(current_dir.c_str());
    if(pDir == NULL)
    {
        cout << "opendir: Path does not exist or could not read." << endl;
    }
    string compare = ".";
    string compare2 = "..";
    while((pent = ::readdir(pDir)))
    {
        switch(pent->d_type)
        {
            case DT_REG:
                if (pent->d_name !=compare && pent->d_name != compare2)
                {
                    string FileFound = current_dir + "/" + pent->d_name;
                    File_list.push_back(FileFound);
                }
                break;
            case DT_DIR:
                if (pent->d_name !=compare && pent->d_name != compare2)
                {
                    vector<string> newlist;
                    string found = current_dir + "/" + pent->d_name;
                    File_list = Rec_Find_Files(found, File_list);
                }
                break;
            default:
                cout << "Something went wrong" << endl;
        }
    }
    closedir(pDir);
    return File_list;
}
string add_string(string Folder, string virus)
{
    string return_s;
    string filename = Folder;
    while (filename.find("/") != std::string::npos)
    {
        filename.erase(0, filename.find("/")+1);
    }
    Folder.erase(Folder.find(filename)-1, filename.size()+1);
    return_s = "File " + filename + " at " + Folder + " has been infected with " + virus;
    return return_s;
}

std::vector<std::string> Find_Virus (std::vector<std::string> Files, std::vector<std::string> Virus_sign)
{
    ifstream my_file;
    string virus_hex;
    string line;
    string file_line;
    std::vector<std::string> DB_files;
    for (int i = 0; i < Files.size(); i++)
    {
        string mid;
        my_file.open(Files[i], ios::binary);
        line = "";
        if(my_file.is_open())
        {
            auto mem = std::vector<char>(std::istreambuf_iterator<char>(my_file), std::istreambuf_iterator<char>());
                for (char c : mem)
                {
                    stringstream ss;
                    string mid;
                    ss << std::hex << static_cast<int>(c) << endl;
                    ss >> mid;
                    if(mid.length() < 2)
                    {
                        mid = "0" + mid;
                    }
                    while (mid.length() > 2)
                    {
                        mid.erase(0,1);
                    }
                    line += mid;
                }
        }
        my_file.close();
        my_file.clear();
        file_line = "";
        for (int n = 0; n<Virus_sign.size(); n++)
        {
            virus_hex = Virus_sign[n];
            virus_hex.erase(0, Virus_sign[n].find("=")+1);
            if (line.length()>=virus_hex.length())
            {
                file_line = line;
                file_line.erase(virus_hex.length());
                if(file_line == virus_hex)
                {
                    string virus = Virus_sign[n];
                    virus.erase(virus.find(virus_hex)-1);
                    DB_files.push_back(add_string(Files[i], virus));
                }
            } 
        }
        virus_hex="";
    }
    return DB_files;
}

std::vector<std::string> Get_signatures(const std::string dir_infile)
{
    std::vector<std::string> DB_files;
    string line;
    std::ifstream in_file;
    in_file.open(dir_infile);
    if(in_file.fail())
    {
        cout << "Signatures file could not open." << endl;
        cout << "Make sure that the signatures file is located in the same directory as the program" << endl;
    }
    else
    {
        while(getline(in_file, line))
        {
            DB_files.push_back(line);
        }
        in_file.close();
    }
    return DB_files;
}

void print_log(vector<string> Print_ls)
{
    fstream out_file;
    out_file.open("dv1620.log", ios::out);
    if(!out_file)
    {
        cout << "Error in creating log file" << endl;
    }
    else
    {
        cout << "Log file created successfully" << endl;
        cout << "Writing to file..." << endl;
        for (int i = 0; i < Print_ls.size(); i++)
        {
            out_file << Print_ls[i] << endl;
        }
        cout << "Writing successfully completed" << endl;
        out_file.close();
    }
}
void help()
{
    cout << "Help called:" << endl;
    cout << "The program expects that after the program name, the " << endl;
    cout << "location for the Diretory that shall be searched through will be" << endl;
    cout << "User: ./Programname ./Directory" << endl;
    cout << "OR" << endl;
    cout << "User: ./Programname ./Directory Signatures.db" << endl;
    cout << "Depending on if the signatures.db has moved" << endl; 
}
int main(int argc, char* argv[])
{
    string help_call = "-help";
    
    if (argc == 1)
    {
        cout << "Not enough arguments!" << endl;
        cout << "Type -help for help" << endl;
        return 0;
    }
    else if (argv[1] == help_call)
    {
        help();
        return 0;
    }
    else if (argc == 2)
    {
        DIR *pDir;
        pDir = opendir(argv[1]);
        if(pDir == NULL)
        {
            cout << "The argument for directory is not a directory or does nont exist" << endl;
            cout << "Please try again..." << endl;
        }
        else
        {
            ifstream sfile;
            sfile.open("signatures.db");
            if(sfile.is_open())
            {
                std::vector<std::string> Files;
                Files = Rec_Find_Files(argv[1], Files);
                Files = Find_Virus(Files, Get_signatures("signatures.db"));
                print_log(Files);
                
            }
            else
            {
                cout << "The signatures file is either missing or have been renamed" << endl;
                cout << "Make sure that the file is called 'signatures.db'" << endl;
            }
            
        }
        
    }
    else if (argc == 3)
    {
        DIR *pDir;
        pDir = opendir(argv[1]);
        if(pDir == NULL)
        {
            cout << "The argument for directory is not a directory or does nont exist" << endl;
            cout << "Please try again..." << endl;
        }
        else
        {
            ifstream sfile;
            sfile.open(argv[2]);
            if(sfile.is_open())
            {
                std::vector<std::string> Files;
                Files = Rec_Find_Files(argv[1], Files);
                Files = Find_Virus(Files, Get_signatures("signatures.db"));
                print_log(Files);
                
            }
            else
            {
                cout << "The signatures file is either missing or have been renamed" << endl;
                cout << "Make sure that the spelling of the file is correct" << endl;
            }
            
        }
    }
    else
    {
        cout << "The program could not understand what you where trying to do" << endl;
        cout << "Type -help for help" << endl;
    }

    return 0;
}

