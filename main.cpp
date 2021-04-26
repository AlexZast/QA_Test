#include <iostream>
#include <xml3all.h> //https://github.com/WindowsNT/xml
#include <fstream>
#include <filesystem>
#include <sys/types.h>
#include <sys/stat.h>

struct stat info;
const static int BUF_SIZE = 4096;

using namespace std;
using namespace XML3;

bool isDirectory(string);

int main()
{
    //Проверка наличия файла xml
    ifstream file;
    file.open("test.xml");
    if(!file)
    {
        cerr << "Cant find this file: " << "test.xml" << endl;
        return 1;
    } else {
        cerr << "Success: " << "test.xml" << endl;
    }
    file.close();
    // Парсер XML
    XML xml("test.xml");
    auto&root = xml.GetRootElement();
    int num = root.GetChildrenNum();

    for (int i = 0; i < num ; ++i){ // Проходим все элементы списка XML
        if(isDirectory(root[i].v(0))){
            string in_file = root[i].v(0) + "\\" + root[i].v(2);
            string out_file = root[i].v(1) + "\\" + root[i].v(2);
            ifstream in(in_file , ios_base::in | ios_base::binary);
            ofstream out(out_file, ios_base::out | ios_base::binary);
            if(out.is_open() & in.is_open()){
                char buf[BUF_SIZE];
                do {
                    in.read(&buf[0], BUF_SIZE);
                    out.write(&buf[0], in.gcount());
                } while (in.gcount() > 0);
                 in.close();
                 out.close();
                 cout << "File " << root[i].v(2) << " copied." << endl;
                } else {
                cerr << "Access error." << endl;
                }
            }

       }
    system("pause");
    return 0;
}

bool isDirectory(string path){
    char _path[255] = "\0";
    strcpy(_path, path.c_str() );
    if(stat(_path, &info ) != 0 ){
        cerr << "Directory \"" << _path << "\" not found." << endl;
        return false;
    }
    else if(info.st_mode & S_IFDIR ){
        //cerr << _path << " is a directory."  << endl;
        return true;
    }
    else {
        //cerr << _path <<  " is no directory." << endl;
        return false;
    }
}


