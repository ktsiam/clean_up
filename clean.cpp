#include <fstream>
#include <iostream>
int main(int argc, char *argv[])
{
        if (argc == 1){
                std::cerr << "Please pass the files you want cleaned as parameters\n";
                return 1;
        }

        int count, temp_count;
        std::string newFile;
        std::ifstream inf;
        std::ofstream outf;

        for (int i = 1; i < argc; ++i){
                count = 0;
                temp_count = 1;

                while(temp_count != 0){
                        temp_count = 0;

                        inf.open(argv[i]);
                        if (!inf.is_open()){
                                std::cerr << "\"" << argv[i] << "\" could not be opened\n";
                                temp_count = 0;
                                goto newLoop;
                        }

                        //reading file
                        newFile = "";
                        std::string line;
                        while (std::getline(inf, line))
                        {
                                for (std::string::reverse_iterator it = line.rbegin(); it != line.rend(); ++it){
                                        if (*it != ' ')
                                                break;
                                        else{
                                                line = line.substr(0, line.size()-1);
                                                temp_count ++;
                                        }
                                }
                                newFile += line + '\n';
                        }
                        inf.close();

                        //rewriting file
                        outf.open(argv[i]);
                        outf << newFile;
                        outf.close();

                        count += temp_count;
                }
                std::cerr << "Done \"" << argv[i] << "\" (" << count << " spaces were removed)\n";
        newLoop:;
        }
}
