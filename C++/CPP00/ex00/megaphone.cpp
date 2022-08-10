#include <iostream>
#include <string>

int main(int argc, char **argv){
    int i;
    int c;
    
    c = 1;
    if (argc == 1)
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
    else{
        while (argv[c]){
            i = -1;
            while(argv[c][++i])
                std::cout << char(toupper(argv[c][i]));
            c++;
        }
    }
    std::cout << std::endl;
    return (0);
}
