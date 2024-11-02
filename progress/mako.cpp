#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

std::vector<double> closest_point_to_center(std::vector<std::vector<double>> points) {
    std::vector<double> center(points[0].size(), 0.0);
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
    std::vector<std::vector<double>> points = {
        {-3,10},
        {3,4},
        {8,2},
        {1,2},
        {-1,1},
        {2,-3}
    };
    std::vector<double> closest_point = closest_point_to_center(points);

    std::cout << "Point closest to the center: ";
    for (const auto& value : closest_point) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}