#include <iostream>
#include <boost/filesystem.hpp>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>

using namespace boost::filesystem;


void dop_info(std::multimap<std::string, std::string> tmp){
     std::multimap<std::string, std::string> buf;
     std::multimap<std::string, std::string> buf2;
    while (!tmp.empty()) {
        if(tmp.empty()) break;
        auto it = tmp.begin();
        std::string srav;
        srav = (it->second).substr(8,8);
    for (auto it = tmp.begin(); it != tmp.end();) {
        if(it->second.substr(8,8) == srav){
            buf.insert(std::pair<std::string, std::string> (it->second , it->first));
            it = tmp.erase(it);
        }
        else ++it;
    }
        std::size_t size = buf.size();
        std::string account = (buf.begin()->first).substr(8,8);
        std::string lastdate = (std::next(buf.end(),-1)->first).substr(17,8);
        std::cout<<"broker: "<<buf.begin()->second<<" account: "<<account<<" files: "<<size<<" lastdate: "<<lastdate<<'\n';
        buf.clear();

    }
    /*for(const auto& x: buf){
        std::cout<<x.first<<"  "<<x.second<<'\n';
    }
    */
}

int main(int argc, char* argv[])
{
    if(argc >= 2){
        const path workdir = argv[1];
        try{
        if (exists(workdir))    // does path p actually exist?
        {
            if (is_directory(workdir)){      // is path p a directory?
                std::cout << workdir << " is a directory\n";
                recursive_directory_iterator begin(workdir);
                recursive_directory_iterator end;
                // Получаем список подкаталогов
                std::vector<path> subdirs;
                std::copy_if(begin, end, std::back_inserter(subdirs), [](const path& path) {
                    return is_directory(path) || is_symlink(path); //read symlink
                });
                std::cout << "-- subdirs --" << std::endl;
                for(const auto& x: subdirs) std::cout<<x.filename()<<'\n';
               
                std::multimap<std::string,std::string> data;
                
                for (auto & element : subdirs) {
                path dir (element);
                directory_iterator b (dir);
                directory_iterator e;
                std::vector<path> txtFiles;
                    
                std::copy_if(b, e, std::back_inserter(txtFiles), [](const path& path) {
                    std::string str = path.stem().string();
                    bool valid = true;
                    std::string example_str ("balance_XXXXXXXX_YYYYMMDD");
                
                    if(str.size() == example_str.size()){
                    std::stringstream buf (str);
                    for (int i = 8; i < 16; ++i) { //check substring "XXXXXXXX" on right type int
                        if(!std::isdigit(str[i])) {valid = false; break;}
                    }
                    for (int i = 17; i < 25; ++i) { //check substring "YYYYMMDD"
                        if(!std::isdigit(str[i])) {valid = false;break;}
                    }
                    if((str.compare(0,8,example_str,0,8))  && str.compare(16,1,example_str,16,1)) valid = false; //check substring "balance_ & _"
                    }
                    else valid = false;

                    return  is_regular_file(path) && (path.extension() == ".txt") && ( str.rfind(".old") == std::string::npos) && valid;
                });
                    
                // Выводим список файлов.
                    for(const auto& x: txtFiles){
                        std::cout<<element.filename()<<"  "<<x.filename()<<'\n';
                        data.insert(std::pair<std::string,std::string>(element.filename().string(),x.filename().string()));
                    }
                }
                dop_info(data);
            }
            else
                std::cout << workdir << " exists, but is not a regular file or directory\n";
        }
        else std::cout << workdir<< " does not exist\n";
    }
        catch (const filesystem_error& ex)
        {
            std::cout << ex.what() << '\n';
        }

    }
    if(argc < 2){
        const path workdir = current_path();
        try{
            if (exists(workdir))    // does path p actually exist?
            {
                if (is_directory(workdir)){      // is path p a directory?
                    std::cout << workdir << " is a directory\n";
                    recursive_directory_iterator begin(workdir);
                    recursive_directory_iterator end;
                    // Получаем список подкаталогов
                    std::vector<path> subdirs;
                    std::copy_if(begin, end, std::back_inserter(subdirs), [](const path& path) {
                        return is_directory(path) || is_symlink(path); //read symlink
                    });
                    std::cout << "-- subdirs --" << std::endl;
                    for(const auto& x: subdirs) std::cout<<x.filename()<<'\n';
                    
                    std::multimap<std::string,std::string> data;
                    
                    for (auto & element : subdirs) {
                        path dir (element);
                        directory_iterator b (dir);
                        directory_iterator e;
                        std::vector<path> txtFiles;
                        
                        std::copy_if(b, e, std::back_inserter(txtFiles), [](const path& path) {
                            std::string str = path.stem().string();
                            bool valid = true;
                            std::string example_str ("balance_XXXXXXXX_YYYYMMDD");
                            
                            if(str.size() == example_str.size()){
                                std::stringstream buf (str);
                                for (int i = 8; i < 16; ++i) { //check substring "XXXXXXXX" on right type int
                                    if(!std::isdigit(str[i])) {valid = false; break;}
                                }
                                for (int i = 17; i < 25; ++i) { //check substring "YYYYMMDD"
                                    if(!std::isdigit(str[i])) {valid = false;break;}
                                }
                                if((str.compare(0,8,example_str,0,8))  && str.compare(16,1,example_str,16,1)) valid = false; //check substring "balance_ & _"
                            }
                            else valid = false;
                            
                            return  is_regular_file(path) && (path.extension() == ".txt") && ( str.rfind(".old") == std::string::npos) && valid;
                        });
                        
                        // Выводим список файлов в cout.
                        for(const auto& x: txtFiles){
                            std::cout<<element.filename()<<"  "<<x.filename()<<'\n';
                            data.insert(std::pair<std::string,std::string>(element.filename().string(),x.filename().string()));
                        }
                    }
                    dop_info(data);
                }
                else
                    std::cout << workdir << " exists, but is not a regular file or directory\n";
            }
            else std::cout << workdir<< " does not exist\n";
        }
        catch (const filesystem_error& ex)
        {
            std::cout << ex.what() << '\n';
        }
    }
    return 0;
}
