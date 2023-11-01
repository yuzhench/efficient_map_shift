
#include <iostream>
#include <algorithm> 
#include <ctime>

using namespace std;

//constant 
const int length = 500;
const int threshold = 250;


//struct
struct Range {
    int start;
    int end;
};

struct voxel{
    int number;
    bool check; 
};

voxel new_volume[length*length*length];
voxel volume[length*length*length];


void array_copy (voxel volume[length*length*length], voxel new_volume[length*length*length]){
    for (int i = 0; i < length*length*length; i++){
        volume[i] = new_volume[i];
    }
}

//helper function 

//initialize the new_volume 
void initialize_array(voxel volume[length*length*length]){
    for (int i = 0; i < length*length*length; i++){
        volume[i].number = 1;
        volume[i].check = true;
    }
}
 


void move_right (){

    int delete_old_start = 0;
    int delete_old_end = length*length*(threshold);
    int keep_old_start = delete_old_end;
    int keep_old_end = length*length*length;

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
 




int main(){
    clock_t start, end;

    initialize_array(volume);
    start = clock();
    move_right();
    end = clock();
    cout << "the time is: " << end - start << endl; 
    return 0 ;
}