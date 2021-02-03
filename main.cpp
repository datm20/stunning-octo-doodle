
#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <vector>
#include <string>
#include <fstream>

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
    std::string compare3 = "createdir.sh";
    std::string compare4 = "h4x0r.pdf";
    while(pent = readdir(pDir))
    {
        switch(pent->d_type)
        {
            case DT_REG:
                if (pent->d_name !=compare && pent->d_name != compare2
                && pent->d_name != compare3 && pent->d_name != compare4)
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

std::vector<std::string> Find_Virus (std::vector<std::string> Files, std::vector<std::string> Virus_sign)
{
    char hex[]={'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    ifstream my_file;
    std::vector<std::string> DB_files;
    for (int i = 0; i < Files.size(); i++)
    {
        my_file.open(Files[i]);
        string line = "";
        string file_line = "";
        if(my_file.is_open())
        {
            while(my_file>>line)
            {
                file_line += line + " ";
            }
            
        }
        my_file.close();
        my_file.clear();
        line = "";
        for (int k = 0; k< file_line.length();k++)
        {
            int a =(int)(file_line.at(k));
            cout << a << endl;
            while (a>0)
            {
                int dec_num = a%16;
                line = hex[dec_num] +line;
                a = a/16;
            }
        }
        cout << line << endl;
        
        for (int n = 0; n<Files[i].length(); n++)
        {
            
            
        }
    }




    return DB_files;
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
    cout << Folder << endl;
    return_s = "File " + filename + " at " + Folder + " has been infected with " + virus;
    return return_s;
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
            //line.erase(0, line.find("=")+1);
            DB_files.push_back(line);
        }
        in_file.close();
    }
    return DB_files;
}
int main(int argc, char* argv[])
{
    std::vector<std::string> Files;
    Files = Rec_Find_Files("./TestDir", Files);
    Files = Find_Virus(Files, Get_signatures("signatures.db"));
    string test = add_string("./Testdir/testmap/map2/apa", "12345678");
    cout << test << endl;
   





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