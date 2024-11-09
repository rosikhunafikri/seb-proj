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

    
    vector<Point> sorted_coordinate_placeholder = point_sorter(coordinate_placeholder, avg);

    //supposedly contains max, 2nd, 3rd max points.
    vector<Point> three_points;
    cout << "max point: " << sorted_coordinate_placeholder[0] << endl;
    three_points.push_back(sorted_coordinate_placeholder[0]);
    float closest = sorted_coordinate_placeholder[0].segment(); //segment/distance of max point --> radius of first center

    //line of average point, to max point
    Line First_A = eol_pp(avg, three_points[0]);
    Point intermediate_center;

    for (int i = 1 ; i < sorted_coordinate_placeholder.size() ; i++) {
        //perpendicular bisector of point iterated
        Line Second_A = perpendicular_bisector_func(sorted_coordinate_placeholder[i], three_points[0]);

        //new center candidate, calculated for point iterated
        Point intersection = new_coordinate_func(First_A, Second_A);

        //find closest point to avg point, and store the result to three_points

        if (intersection.segment() < closest){
            cout << "check closest " << sorted_coordinate_placeholder[i] << endl;            
            closest = intersection.segment();
            if (closest < 0.0001) {
                cout << "closest to 0" << endl;
                intermediate_center = avg;
                break;
            }
            cout << "closest!" << closest << endl;
            three_points[1] = sorted_coordinate_placeholder[i];
            intermediate_center = intersection;
            cout << "intersection: " << intersection << endl;
        }
    }
    cout << "center: " << intermediate_center <<  endl;
    cout << "max: " << three_points[0] << endl;
    cout << "radius max: "<< three_points[0].segment() << endl;
    cout << "2nd max: "<< three_points[1] << endl;
    cout << "radius max: "<< three_points[1].segment() << endl;

    cout <<"sorting..... start" << endl;
    sorted_coordinate_placeholder = point_sorter(sorted_coordinate_placeholder, intermediate_center);

    //cout << "Two Points: " << endl;
    //for (const auto &point: two_points_plus_old_center) cout << point << endl;
    cout << "sorted: " << endl;
    for (auto &point: sorted_coordinate_placeholder) {
        cout << point << ": " << point.segment() << endl;
    }


    int i_three = 0;
    
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
