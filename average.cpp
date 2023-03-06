#include <iostream>
#include <sstream>
#include <vector>
using namespace std;
int main(int argc, char *argv[]) {
    vector<double> nums;
    double sum = 0.0;

    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            istringstream ss(argv[i]);
            double num;
            if (ss >> num) {
                nums.push_back(num);
                sum += num;
            }
        }
    } else {
       cout << "Please input numbers to find average." << endl;
       string input;
       getline(cin, input);
       istringstream ss(input);
        double num;
        while (ss >> num) {
            nums.push_back(num);
            sum += num;
        }
    }
    int count = nums.size();
    if (count > 0) {
        double average = sum / count;
        cout << "---------------------------------" << endl;
        cout << "Average of " << count << " numbers = " << average <<endl;
        cout << "---------------------------------" << endl;


    return 0;
}
}

