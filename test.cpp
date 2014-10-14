#include "ini.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

int main() {
    Ini ini;

    ini.loadFile("config.ini");

    cout << ini.getValue<bool>("weipinhui_promo", "is_promo") << endl;
    cout << ini.getValue<double>("weipinhui_promo", "n_business_score") << endl;
    cout << ini.getString("weipinhui_promo", "n_business_score") << endl;

    vector<int> result;
    ini.getContainer("weipinhui_promo", "list", result);
    copy(result.begin(), result.end(), ostream_iterator<int>(cout, ","));
    cout << endl;

    return 0;
}
