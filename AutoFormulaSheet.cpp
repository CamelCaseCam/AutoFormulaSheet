#include <iostream>
#include <fstream>
#include <filesystem>

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cout << "You must provide a equation tag and output file" << std::endl;
        return -1;
    }

    std::string Tag = argv[1];
    std::string OutputName = argv[2];
    std::filesystem::path PathToFiles = std::filesystem::current_path();

    std::ofstream Output(PathToFiles.string() + "/" + OutputName);
    for (std::filesystem::path path : std::filesystem::recursive_directory_iterator(PathToFiles))
    {
        //Read the file
        std::ifstream t(path.c_str());
        std::stringstream ss;
        ss << t.rdbuf();
        std::string txt = ss.str();
        if (txt == "" || txt.length() < 3)
            continue;

        std::string Formula;

        for (int i = 0; i < txt.length() - 4; ++i)
        {
            //Find the tag
            if (txt[i] == '<' && txt[i + 1] == 'e' && txt[i + 2] == 'q' && txt[i + 3] == ' ')
            {
                i += 4;
                std::string localTag = "";
                //My own substr, because substr wasn't working
                for (i; i < txt.length(); ++i)
                {
                    if (txt[i] == '>')
                        break;
                    localTag += txt[i];
                }

                if (localTag == Tag)
                {
                    ++i;
                    for (i; i < txt.length() - 5; ++i)
                    {
                        //Closing tag
                        if (txt[i] == '<' && txt[i + 1] == '/' && txt[i + 2] == 'e' && txt[i + 3] == 'q' && txt[i + 4] == '>')
                            break;
                        Formula += txt[i];
                    }
                    Output << Formula << "\n";
                    Formula = "";
                }
            }
        }
    }
}
