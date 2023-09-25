#include <iostream>
#include <vector>
#include <list>
#include <map>

using namespace std;
 
int main() {

    //  Vectors
    vector <int> vector;
 
    for (int i = 1; i <= 5; i++) {
        vector.push_back(i);
    }

    cout << "Vector output: \n";

    for (auto i = vector.begin(); i != vector.end(); ++i) {
        cout << *i << " ";
    }
    
    cout << "\n";


    //  Lists
    list <string> list;

    for (int y = 0; y < 5; y++) {
        list.push_back("Number" + to_string(y));
    }

    cout << "\nList output: \n";

    for(const auto& val : list) {
        cout << val << " ";
    }

    cout << "\n";


    //  Maps
    map <string, int> map;

    map["Joana"] = 2;
    map["Ana"] = 17;
    map["Jacinto"] = 25;
    map["Jorge"] = 742;
    map["Jeremias"] = 368;

    cout << "\nMap output: \n";

    for (auto const& entry : map) {
        std::cout << '[' << entry.first << "] -> " << entry.second << std::endl;
    }

    cout << "\n";

    return 0;
}