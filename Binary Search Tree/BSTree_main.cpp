#include <iostream>
#include <string>
#include <fstream>
#include "BSTree.h"

BSTree read_file(std::string file_name) {      
    BSTree new_tree;
    std::ifstream infile(file_name); 
    if (infile.fail())
        throw "Error while attempting to read file: " + file_name;
    infile >> new_tree;
    return new_tree;
}

int main() {
    try {
        std::string file;
        for(int d = 0; d < 12; d++) {
            file = "data-files/" + std::to_string(d + 1);

            BSTree l = read_file(file + "l");
            std::cout << d << ", " <<  l.get_average_search_time();

            BSTree p = read_file(file + "p");
            std::cout << ", " << p.get_average_search_time();

            BSTree r = read_file(file + "r");
            std::cout << ", " << r.get_average_search_time() << std::endl;
        }
    } catch (std::string& error) {
        std::cout << error << std::endl;
    }
}