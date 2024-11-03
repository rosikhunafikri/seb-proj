#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
// #include "geometric_functions.h"

using namespace std;

//modified: finds the average point instead
vector<double> closest_point_to_center(vector<vector<double>> points) {
    vector<double> center(points[0].size(), 0.0);
    size_t num_points = points.size();

    //center calculations
    for (const auto& point : points) {
        for (size_t i = 0; i < point.size(); ++i) {
            center[i] += point[i];
        }
    }
    for (size_t i = 0; i < center.size(); ++i) {
        center[i] /= num_points;
    }

    return center; 
}

int main() {
    vector<vector<double>> points = {
        {-3,10},
        {3,4},
        {8,2},
        {1,2},
        {-1,1},
        {2,-3}
    };
    vector<double> closest_point = closest_point_to_center(points);

    cout << "Point closest to the center: ";
    for (const auto& value : closest_point) {
        cout << value << " ";
    }
    cout << endl;

    return 0;
}