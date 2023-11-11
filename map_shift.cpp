
#include <iostream>
#include <algorithm> 
#include <ctime>
#include <chrono>

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
 

class voxel_node{
public:
    int number;
    bool check; 
    voxel_node* next; 

    //constructor 
    voxel_node(int number_in, bool check_in) : number(number_in), check(check_in),next(nullptr){}

};

class map_2D {
public:
    voxel_node* head;
    voxel_node* tail;

    void append(int number_in, int check_in) {
        voxel_node* newNode = new voxel_node(number_in, check_in);
        if (head == nullptr) {
            // If the list is empty, make the new node the head
            head = newNode;
        } else {
            // Traverse the list to find the last node
            voxel_node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            // Add the new node at the end
            temp->next = newNode;
        }
    }


    pair<voxel_node*, voxel_node*> initialize_a_range(int number_array [],bool check_array [], int size){
        pair<voxel_node*, voxel_node*> head_tail; 
        head_tail.first = new voxel_node(number_array[0], check_array[0]);
        head_tail.second = new voxel_node(number_array[size-1], check_array[size-1]);
        voxel_node* current_node = head_tail.first;
        for (int i = 1; i < size-1; i++){
            voxel_node* temp_node = new voxel_node(number_array[i], check_array[i]);
            current_node->next = temp_node;
            current_node = temp_node;
        }
        current_node->next = head_tail.second;
        return head_tail; 
    }
   
    void delete_one_row(voxel_node* start_pointer){
        voxel_node* current = start_pointer;
        voxel_node* next_node; 
        for (int i = 0; i < length; i++){
            next_node = current->next;
            delete current;
            current = next_node;
        }
    }

 

    voxel_node* get_new_head(){
        voxel_node* new_head = head;

        for (int i = 0; i < length; i++){
            new_head = new_head->next;
        }
        return new_head;
    }

    void map_move_to_south(int new_number_array [],bool new_check_array [],int size){ 
        voxel_node* old_head = head;
        head = get_new_head();
        delete_one_row(old_head);
        pair<voxel_node*, voxel_node*> head_tail;
        head_tail = initialize_a_range(new_number_array,new_check_array,length);
        //store the address of the old tail address
        voxel_node* old_tail = tail;
        //upddate the new tail 
        tail=head_tail.second;
        //connect the new row to the old map
        old_tail->next = head_tail.first;
    }

    // Display the linked list in a table format
    void displayTable(int numRows, int numCols) {
        voxel_node* temp = head;

        for (int i = 0; i < numRows; ++i) {
            for (int j = 0; j < numCols; ++j) {
                if (temp != nullptr) {
                    std::cout << temp->number << "\t";
                    temp = temp->next;
                } else {
                    // If the linked list is shorter than expected, print a placeholder
                    std::cout << "N/A\t";
                }
            }
            std::cout << std::endl;
        }
    }
};



int main(){
 

    // // initialize_array(volume);


    // auto start = std::chrono::high_resolution_clock::now();
    // // move_right();
    // initialize_array(volume);
    // auto stop = std::chrono::high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    // cout << "the time is: " << duration.count() << " milliseconds." << std::endl;








    cout<< "hollow world" << endl;

    //create an example array 
    int number [TOTAL_LENGTH]; 
    bool check [TOTAL_LENGTH];
    for (int i = 0; i < TOTAL_LENGTH; i++){
        number[i] = i;
        check [i] = true;
    }

    //create the new row 
    int new_number [length];
    bool new_chceck [length];
    for (int i = 0; i < length; i++){
        new_number[i] = 0;
        new_chceck[i] = false;
    }

    // cout<< "hollow world" << endl;



    // //link_list_method 
    // map_2D Map;
    // auto start = std::chrono::high_resolution_clock::now();
    // pair<voxel_node*, voxel_node*> head_tail = Map.initialize_a_range(number,check,TOTAL_LENGTH);
    // auto stop = std::chrono::high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    // cout << "the time used to initialize the mao is: " << duration.count() << " milliseconds." << endl;

    // Map.head = head_tail.first;
    // Map.tail = head_tail.second;
    // // cout << "---> " << Map.tail->number << endl;
    // // Map.displayTable(length, length);

    // auto start1 = std::chrono::high_resolution_clock::now();
    // Map.map_move_to_south(new_number,new_chceck, length);
    // auto stop1 = std::chrono::high_resolution_clock::now();
    // auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(stop1 - start1);
    // cout << "the time used update the new array is: " << duration1.count() << " milliseconds." << endl;

    // // cout << endl << endl << endl;

    // // Map.displayTable(length, length);


    return 0 ;
}