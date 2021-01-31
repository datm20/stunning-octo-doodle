
#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <vector>

using namespace std;



std::vector<std::string> Rec_Find_Files (const std::string current_dir
,vector<string> File_list)
{
    DIR *pDir;
    struct dirent *pent;
    pDir = opendir(current_dir.c_str());
    if(pDir == NULL)
    {
        cout << "pDir was not initialized properly" << endl;
        //fixa avbryt sak
        
    }
    std::string compare = ".";
    std::string compare2 = "..";
    std::string compare3 = ".";
    std::string compare4 = ".";
    while(pent = readdir(pDir))
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

int main(int argc, char* argv[])
{
    std::vector<std::string> Files;
    Files = Rec_Find_Files(".", Files);
    for(int i = 0; i < Files.size(); i++)
    {
        cout << Files[i] << endl;
    }
    string help_call = "-help";
    cout << "Hello World!" << endl;
    cout << "Mängden argument: " << argc << endl;
    for(int i = 0; i < argc; i++)
    {
        cout << "Argumentet ["<< i<<"]: " << argv[i] << endl;
    }
    
    if (argc == 2)
    {
        cout << "Right amount of arguments" << endl;
        cout << argv[1] << endl;
        
        if (argv[1] == help_call)
        {
            
            cout << "Help called" << endl;
        }
    }
    
    


    return 0;
}