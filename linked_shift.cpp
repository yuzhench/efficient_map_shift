
#include <iostream>
#include <algorithm> 
#include <ctime>
#include <chrono>
#include <list>

using namespace std;

//constant 
const int length = 1000;
const int threshold = 50;
const int TOTAL_LENGTH = length*length;


//struct
struct Range {
    int start;
    int end;
};

struct voxel{
    int number;
    bool check;

    voxel()
        : number(1), check(true)
    {}

    voxel(int _n, bool _c)
        : number(_n), check(_c)
    {}
};

voxel new_volume[length*length];
voxel volume[length*length];


void array_copy (voxel volume[length*length], voxel new_volume[length*length]){
    for (int i = 0; i < length*length; i++){
        volume[i] = new_volume[i];
    }
}

//helper function 

//initialize the new_volume 
void initialize_array(voxel volume[length*length]){
    for (int i = 0; i < length*length; i++){
        volume[i].number = 1;
        volume[i].check = true;
    }
}
 
void move_right (){

    int delete_old_start = 0;
    int delete_old_end = length*(threshold);
    int keep_old_start = delete_old_end;
    int keep_old_end = length*length;

    int create_new_start = keep_old_end-keep_old_start;
    int create_new_end =  keep_old_end;
    int shift_new_start = 0;
    int shift_new_end =  create_new_start;



    Range old_removed_range = {delete_old_start,delete_old_end};
    Range old_keep_range = {keep_old_start,keep_old_end};

    Range new_shift_range = {shift_new_start,shift_new_end};
    Range new_create_range = {create_new_start,create_new_end};

    int i = new_shift_range.start;
    int j = old_keep_range.start;

    for (; i < new_shift_range.end && j < old_keep_range.end; i++, j++){
        new_volume[i] = volume[j];
    }

    for (int k = new_create_range.start; k < new_create_range.end; k++){
        new_volume[k].number = 0;
        new_volume[k].check = false;
    }
    std::cout<< "the map has been shifted in x_position : right direction------------------------------" << std::endl;
    // std::cout <<"the size of the volume is " << volume.size() << std::endl;
    // std::cout <<"the size of the new_volume is " << new_volume.size() << std::endl;
    array_copy(volume, new_volume);
}
 

class Map{
public:
    list<voxel> voxels;

    void createNRows(int N){
        for (int i = 0; i < N; i++)
            voxels.emplace_back(0, false);
    }

    void deleteRow(list<voxel>::iterator start_pointer){
        list<voxel>::iterator end_pointer(start_pointer);
        std::advance(end_pointer, length);
        voxels.erase(start_pointer, end_pointer);
    }

    void shiftSouth(){ 
        list<voxel>::iterator head = voxels.begin();
        std::advance(head, length);
        auto start = std::chrono::high_resolution_clock::now();
        deleteRow(voxels.begin());
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        cout << "delete " << duration.count() << " microseconds" << endl;

        start = std::chrono::high_resolution_clock::now();
        createNRows(length);
        stop = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        cout << "init " << duration.count() << " microseconds" << endl;
    }

    // Display the linked list in a table format
    void displayTable(int r, int c) {
        list<voxel>::iterator temp = voxels.begin();

        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (temp != voxels.end()) {
                    std::cout << temp->number << " ";
                    temp++;
                } else {
                    std::cout << "- ";
                }
            }
            std::cout << std::endl;
        }
    }
};



int main(){
 
    // initialize_array(volume);
    auto start = std::chrono::high_resolution_clock::now();
    // move_right();
    initialize_array(volume);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    cout << "Init ARRAY: " << duration.count() << " microseconds." << std::endl;

    Map map;
    start = std::chrono::high_resolution_clock::now();
    map.createNRows(TOTAL_LENGTH);
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    cout << "Init LINKED: " << duration.count() << " microseconds." << endl;

    // cout << "---> " << endl;
    // Map.displayTable(length, length);

    auto start1 = std::chrono::high_resolution_clock::now();
    map.shiftSouth();
    auto stop1 = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(stop1 - start1);
    cout << "Shift: " << duration1.count() << " microseconds." << endl;

    // cout << endl << endl << endl;

    // Map.displayTable(length, length);


    return 0 ;
}