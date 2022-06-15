#include "evaluate.h"

using namespace std;
float evaluate(string file, int gate_count)
{
    cout << "file: " << file << endl;
    string str;
    ifstream ifs(file, ifstream::in);

    string std_library[] = {
        "+",
        "-",
        "*",
        "/",
        "**",
        "%",
        "&&",
        "||",
        "&",
        "|",
        "^",
        "^~",
        "~^",
        "~&",
        "~|",
        ">>",
        "<<",
    };
    int assign_count = 0;
    int cost = 0;
    while (getline(ifs, str))
    {
        stringstream ss(str);
        // cout << "str: " << str << endl;

        while (ss.good())
        {
            string element;

            getline(ss, element, ' ');
            size_t found = element.find("~w");
            if (element == "assign")
            {
                assign_count++;
                //cout << "find assign!" << endl;
                //cout << "element: " << element << endl;
            }
            else if (find(begin(std_library), end(std_library), element) != end(std_library))
            {
                cost++;
            }
            else
            {
                if (found != string::npos)
                {
                    cost++;
                }
            }

            //cout << "element: " << element << endl;
        }
    }
    float reduction_rate = (1 - cost / gate_count);
    //cout << "cost: " << cost << endl;
    return reduction_rate;
}