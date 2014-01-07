#include <vector>
#include <iostream>
using namespace std;

int main()
{
#if defined(__sgi)
    cout << "__sgi" << endl;
#endif

#if defined(__GNUC__)
    cout << "__GNUC__" << endl;
    cout << __GNUC__ << ' ' << __GNUC_MINOR__ << endl;
#endif

#ifdef __STL_STATIC_TEMPLATE_MEMBER_BUG
    cout << "__STL_STATIC_TEMPLATE_MEMBER_BUG defined" << endl;
#else
    cout << "__STL_STATIC_TEMPLATE_MEMBER_BUG undefined" << endl;
#endif

    return 0;
}
