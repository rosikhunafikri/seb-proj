#include <iostream>
#include <vector>
#include <fstream>
#include "geometric_functions.h"

using namespace std;

int main() {
    vector<Point> points;
    ofstream outfile("output.txt");
    if (!outfile) {
        cerr << "Error opening file for output" << endl;
        return 1;
    }

    loadPoints("data.txt", points);
    vector<Point> coordinate_placeholder(points.begin(), points.end());
    const Point avg = closest_point_to_center(coordinate_placeholder);
    cout << "average: " << avg << endl;


    for (auto &point: coordinate_placeholder) {
        cout << point << ": " << point.segment() << endl;
        outfile << point << endl;
    }

    // hard-code to find 2 points to update old center
    vector<Point> sorted_coordinate_placeholder = point_sorter(coordinate_placeholder, avg);
    vector<Point> two_points_plus_old_center;
    two_points_plus_old_center.push_back(avg);
    int i_two = 0;
    while (two_points_plus_old_center.size() < 3) {
        Point p = sorted_coordinate_placeholder[i_two++];
        if (none_of(two_points_plus_old_center.begin(), two_points_plus_old_center.end(), [&](Point tp) { return similarity_check(tp, p); })) {
            two_points_plus_old_center.push_back(p);
            if (two_points_plus_old_center.size() == 3 && affine_dependent_check(two_points_plus_old_center)) {
                cout << "result: affine dependent" << endl;
                two_points_plus_old_center.pop_back();
            }
        }
    }


    //find intermediate center using two farthest points + the old center
    Line First_A = perpendicular_bisector_func(two_points_plus_old_center[1], two_points_plus_old_center[2]);
    Line Second_A = eol_pp(avg, two_points_plus_old_center[1]);
    const Point intermediate_center = new_coordinate_func(First_A, Second_A);

    sorted_coordinate_placeholder = point_sorter(sorted_coordinate_placeholder, intermediate_center);

    cout << "Two Points: " << endl;
    for (const auto &point: two_points_plus_old_center) cout << point << endl;
    cout << "sorted: " << endl;
    for (auto &point: sorted_coordinate_placeholder) {
        cout << point << ": " << point.segment() << endl;
    }


    vector<Point> three_points;
    int i_three = 0;
    
    //we persist 1 or two points, and recalculate the rest
    three_points.push_back(two_points_plus_old_center[1]);

    while (three_points.size() < 3) {
        Point p = sorted_coordinate_placeholder[i_three++];
        if (none_of(three_points.begin(), three_points.end(), [&](Point tp) { return similarity_check(tp, p); })) {
            three_points.push_back(p);
            if (three_points.size() == 3 && affine_dependent_check(three_points)) {
                cout << "result: affine dependent" << endl;
                three_points.pop_back();
            }
        }
    }

    cout << "Three Points: " << endl;
    for (const auto &point: three_points) cout << point << endl;

    const Line First_B = perpendicular_bisector_func(three_points[0], three_points[1]);
    const Line Second_B = perpendicular_bisector_func(three_points[0], three_points[2]);
    const Point new_center = new_coordinate_func(First_B, Second_B);

    cout << "New coordinates are: " << new_center << endl;
    outfile << "New coordinates are: " << new_center << endl;

    //set ref to new coordinate
    Point::ref = new_center;
    cout << "final radius check from T" << endl;
    for (int i = 0; i < three_points.size(); i++) {
        Point p = three_points[i];
        cout << "radius from " << p << ": " << p.segment() << endl;
    }


    Point p = three_points[0];
    outfile << "radius is " << p.segment() << endl;


    return 0;
}
