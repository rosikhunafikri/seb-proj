#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include "geometric_functions.h"

using namespace std;
using namespace std::chrono;

int main(int argn,char **argv) {
    bool with_output = argn > 1 && std::string(argv[1]) == "output";
    vector<Point> points;
    ofstream outfile("output.txt");
    ofstream outdebug("debug.txt");
    if (!outfile) {
        cerr << "Error opening file for output" << endl;
        return 1;
    }

    loadPoints("data.txt", points);
    vector<Point> coordinate_placeholder(points.begin(), points.end());


    // OUTFILE POINTS
    
    if (with_output){
        outfile << fixed; //output number in fixed format, instead of scientific format
        for (auto &point: coordinate_placeholder) {
            //cout << point << ": " << point.segment() << endl;
            outfile << point << endl;
        }
    }

    //start clock
    auto start = high_resolution_clock::now();

    const Point avg = closest_point_to_center(coordinate_placeholder);
    cout << "average: " << avg << endl;
    outdebug << "average: " << avg << endl;
    vector<Point> sorted_coordinate_placeholder = point_sorter(coordinate_placeholder, avg);

    //supposedly contains max, 2nd, 3rd max points.
    vector<Point> three_points;

    //fill the first max point
    cout << "max point: " << sorted_coordinate_placeholder[0] << endl;
    three_points.push_back(sorted_coordinate_placeholder[0]);

    float closest = sorted_coordinate_placeholder[0].segment(); //segment/distance of max point --> radius of first center

    //line of average point, to max point
    Line First_A = eol_pp(avg, three_points[0]);
    Point intermediate_center;
    Point max2;

    for (int i = 0 ; i < sorted_coordinate_placeholder.size() ; i++) {
        //perpendicular bisector of point iterated
        Line Second_A = perpendicular_bisector_func(sorted_coordinate_placeholder[i], three_points[0]);

        //new center candidate, calculated for point iterated
        Point intersection = new_coordinate_func(First_A, Second_A);
        //find closest point to avg point, and store the result to three_points

        //check if iterated point is similar to max point and average point
        bool not_similar_to_max = !similarity_check(sorted_coordinate_placeholder[i], three_points[0]);
        //bool not_similar_to_avg = !similarity_check(sorted_coordinate_placeholder[i], avg);
        bool not_similar_gradient = abs(First_A.gradient - Second_A.gradient) > 0.000001;

        Point intersection_refers_to = intersection.refers_to();
        Point max_refers_to = three_points[0].refers_to();

        bool not_backward = intersection_refers_to.dot(max_refers_to) > 0;

        outdebug << sorted_coordinate_placeholder[i] << "; " << sorted_coordinate_placeholder[i].segment() << intersection << "; " << intersection.segment() << "; " << intersection_refers_to.dot(max_refers_to) << "; ";


        if (intersection.segment() < closest && not_similar_to_max && not_backward){
            //cout << "check closest " << sorted_coordinate_placeholder[i] << endl;            
            outdebug << "; CHOSEN";
            closest = intersection.segment();
            
            if (closest < 0.0000000001) { // safeguard - if alrdy then close to 0 then nothing else smaller
                //cout << "closest to 0" << endl;
                closest = 0;
                max2 = sorted_coordinate_placeholder[i];
                intermediate_center = avg;
                break;
            }
            //cout << "closest!" << closest << endl;
            max2 = sorted_coordinate_placeholder[i];
            intermediate_center = intersection;
        }
        outdebug << endl;
    }
    three_points.push_back(max2);
    cout << "center: " << intermediate_center <<  endl;
    cout << "max: " << three_points[0] << endl;
    cout << "radius max: "<< three_points[0].segment() << endl;
    cout << "2nd max: "<< three_points[1] << endl;
    cout << "radius max: "<< three_points[1].segment() << endl;

    //cout <<"sorting..... start" << endl;

    sorted_coordinate_placeholder = point_sorter(sorted_coordinate_placeholder, intermediate_center);

    //cout << "Two Points: " << endl;
    //for (const auto &point: two_points_plus_old_center) cout << point << endl;
    
    //cout << "sorted: " << endl;
    /*
    for (auto &point: sorted_coordinate_placeholder) {
        cout << point << ": " << point.segment() << endl;
    }
    */

    //begin search for 3rd max point.
    Point first_second_midpoint = midpoint_func(three_points[0], three_points[1]);
    closest = sorted_coordinate_placeholder[0].segment();
    Line First_B = eol_pp(intermediate_center, first_second_midpoint); //equation of line between old centre and midpoint between 1st and 2nd max points
    Point new_center;
    Point max3;

    for (int i = 0; i < sorted_coordinate_placeholder.size(); i++){
        //perpendicular bisector of point iterated
        Point p = sorted_coordinate_placeholder[i];
        Line Second_B = perpendicular_bisector_func(p, three_points[0]); //or three_points[1], the result will be the same

        //new center candidate, calculated for point iterated
        Point intersection = new_coordinate_func(First_B, Second_B);
        //find closest point to avg point, and store the result to three_points

        bool none_is_similar = none_of(three_points.begin(), three_points.end(), [&](Point tp) { return similarity_check(tp, p); });

        //purely for affine dependent check
        vector<Point> three_points_check;
        three_points_check.push_back(three_points[0]);
        three_points_check.push_back(three_points[1]);
        three_points_check.push_back(intersection);
        bool affine_dependent = affine_dependent_check(three_points_check);

        if (intersection.segment() < closest && none_is_similar && !affine_dependent ){
            //cout << "check closest " << sorted_coordinate_placeholder[i] << endl;
            closest = intersection.segment();
            if (closest < 0.0000000001) { // safeguard
                //cout << "closest to 0" << endl;
                closest = 0;
                new_center = intermediate_center;
                max3 = sorted_coordinate_placeholder[i];
                break;
            }
            //cout << "closest!" << closest << endl;
            max3 = sorted_coordinate_placeholder[i];
            new_center = intersection;
            //cout << "intersection: " << intersection << endl;
        }
    }
    three_points.push_back(max3);
    
    
    cout << "Three Points: " << endl;
    for (const auto &point: three_points) cout << point << endl;

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
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);

    // To get the value of duration use the count()
    // member function on the duration object
    cout << "duration: " << duration.count() << " s" << endl;

    return 0;
}
