#include "CGIUtil.h"

using namespace std;
int main(){


    //test find_substr
    cout << "================test find_substr =====================" << endl;

    const char* full_data = "This is a simple example string.";
    const char* substr = "simple";
    size_t full_data_len = std::strlen(full_data);

    const char* result = find_substr(full_data, full_data_len, substr);
    if (result) {
        std::cout << "The substring '" << substr << "' is found at position " << (result - full_data) << " in the full string." << std::endl;
    } else {
        std::cout << "The substring '" << substr << "' is not found in the full string." << std::endl;
    }

    //test getValueFromQuery
    cout << "================test getValueFromQuery =====================" << endl;
    std::string query = "abc=123&bbb=456&ccc=789";
    std::string key = "bbb";
    std::string value = "";  
    int ret = getValueFromQuery(query, key,value);
    if (ret == -1) {
        std::cout << "The value for key '" << key << "' is: " << value << std::endl;
    } else {
        std::cout << "Key '" << key << "' not found in the query string." << std::endl;
    }

    return 0;
}
