
#include <iostream>
#include <algorithm> 
#include <ctime>
#include <chrono>
#include <vector>

using namespace std;

//constant 
const int length = 1000;
const int threshold = 2;
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
        volume[i].number = i;
        volume[i].check = true;
    }
}
 


// void move_right (){

//     int delete_old_start = 0;
//     int delete_old_end = length*(threshold);
//     int keep_old_start = delete_old_end;
//     int keep_old_end = length*length;

//     int create_new_start = keep_old_end-keep_old_start;
//     int create_new_end =  keep_old_end;
//     int shift_new_start = 0;
//     int shift_new_end =  create_new_start;



//     Range old_removed_range = {delete_old_start,delete_old_end};
//     Range old_keep_range = {keep_old_start,keep_old_end};

//     Range new_shift_range = {shift_new_start,shift_new_end};
//     Range new_create_range = {create_new_start,create_new_end};

//     int i = new_shift_range.start;
//     int j = old_keep_range.start;

//     for (; i < new_shift_range.end && j < old_keep_range.end; i++, j++){
//         new_volume[i] = volume[j];
//     }

//     for (int k = new_create_range.start; k < new_create_range.end; k++){
//         new_volume[k].number = 0;
//         new_volume[k].check = false;
//     }
//     std::cout<< "the map has been shifted in x_position : right direction------------------------------" << std::endl;
//     // std::cout <<"the size of the volume is " << volume.size() << std::endl;
//     // std::cout <<"the size of the new_volume is " << new_volume.size() << std::endl;
//     array_copy(volume, new_volume);
// }
 
 void move_east_old(int number_array [],bool check_array [], int size){
    for (int i = 0; i < length; i++){
        for (int j = 0; j < length-threshold; j++){
            int new_index = i * length + j;
            int old_index = i * length + j + threshold;
            new_volume[new_index] = volume[old_index];
        }
        for (int k = 0; k < threshold; k++){
            int new_index = i * length + length-threshold + k;
            new_volume[new_index].number = number_array[k];
            new_volume[new_index].check = check_array[k];
        }
    }
 }

 void print_array(voxel new_volume[], int size){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            int index = i * size + j;
            cout<< new_volume[index].number << " ";
        }
        cout << endl;
    }
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
   
    void delete_one_row(voxel_node* start_pointer, int size ){
        voxel_node* current = start_pointer;
        voxel_node* next_node; 
        for (int i = 0; i < size; i++){
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
        delete_one_row(old_head,length);
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

    //------------------------------------------------------
    //get the new start index 
    voxel_node* get_each_line_new_start_east(voxel_node* start_pointer){
        auto temp_node = start_pointer;
        for (int i = 0; i < threshold; i++){
            temp_node = temp_node->next;
        }
        return temp_node; 
    }
 
    void map_move_to_east(int new_number_array [],bool new_check_array [],int size){
        // int row_num = length;
        // int col_num = length;
      

        voxel_node* old_start_node = nullptr;
        voxel_node* new_start_node = nullptr;
        voxel_node* temp_node = nullptr;
        voxel_node* old_end = nullptr;
        voxel_node* new_end = nullptr;
   

        old_start_node = head;
        for (int row = 0; row < length; row++){
            new_start_node = get_each_line_new_start_east(old_start_node);

            // cout << "new_sart_node is: " << new_start_node->number << endl;

            temp_node = new_start_node;
            if (row == 0){
                head = new_start_node;
            }
            
            else {
                new_end -> next = temp_node;
            }

            // temp_node = new_start_node;
            for (int col = threshold; col < length; col++){

                //if the pointer is pointing to the last node in this row
                if (col == length-1){
                    old_end = temp_node;
                    // cout <<"old_end is: " << old_end->number << endl;
                    new_end = new voxel_node(new_number_array[row], new_check_array[row]);

                    temp_node = temp_node->next;

                    old_end ->next = new_end;
                }

                else {
                    //update the temp_node, which is the current pointer 
                    temp_node = temp_node->next;
                }
                 
            }
            //it's the last row of the map 
            if (row == length-1){
                tail = new_end;
            }

            else{
                // new_end -> next = temp_node;
                old_start_node = temp_node;
                // cout << "old_start_node is: " << old_start_node->number << endl;
            }
             
        
        }
        

    }

    vector <voxel_node*> row_old_starts;
    vector <voxel_node*> row_new_starts;

    vector <voxel_node*> row_old_ends;
    vector <voxel_node*> row_new_ends;

    vector <voxel_node*> new_map_starts;
    void initialize_the_map_and_remember(int number_array [],bool check_array [], int row_num, int col_num){
        voxel_node* current_node = new voxel_node(number_array[0], check_array[0]);
        for (int row = 0; row < row_num; row++){
            for (int col = 0; col < col_num; col++){
                int index = row*length +col; 
                if (index != 0){
                    voxel_node* temp_node = new voxel_node(number_array[index], check_array[index]);
                    current_node->next = temp_node;
                    current_node = temp_node;
                }
                //store the pointer in row_old_starts
                if (col == 0){
                    row_old_starts.push_back(current_node);
                }
                //store the pointer in row_old_ends
                else if (col == row_num - 1){
                    row_old_ends.push_back(current_node);
                }
            }
        }



        head = row_old_starts[0];
        tail = row_old_ends.back();
    }

    pair<voxel_node*, voxel_node*> initialize_new_part(int new_number[], bool new_check[], int start_index, int end_index){ //<------------------may can you the pointer to save the memory 
        pair<voxel_node*, voxel_node*> head_tail; 
        head_tail.first = new voxel_node(new_number[start_index], new_check[start_index]);
        head_tail.second = new voxel_node(new_number[end_index], new_check[end_index]);

        voxel_node* current_node = head_tail.first;
        for (int i = start_index+1; i < end_index; i++){
            voxel_node* temp_node = new voxel_node(new_number[i], new_check[i]);
            current_node->next = temp_node;
            current_node = temp_node;
        }
        current_node->next = head_tail.second;
        return head_tail; 
    }

    void map_move_to_east_faster(int col_num, int new_number[], bool new_check[]){
        cout << "--------------------------------------" << endl;

        //get the row-new_starts
        for (int col = 0; col < col_num; col++){
            row_new_starts.push_back(get_each_line_new_start_east(row_old_starts[col]));
        }

        cout << "--------------------------------------" << endl;
        //generate the new data 
        for (int col = 0; col < col_num; col++){ 
            int start_index = col*threshold;
            int end_index = start_index + threshold - 1;
            pair<voxel_node*, voxel_node*> tail_head = initialize_new_part(new_number, new_check,start_index, end_index);
            new_map_starts.push_back(tail_head.first);
            row_new_ends.push_back(tail_head.second);
        }

        //delte the old data 
        for (int col = 0; col < col_num; col++){
            voxel_node* start_index = row_old_starts[col];
            delete_one_row(start_index, threshold );
        }

        //connect the old_row_end with the new_map_starts
        for (int col = 0; col < col_num; col++){
            row_old_ends[col]->next = new_map_starts[col];
        }

        //connect the new_row_end with the new row 
        for (int col = 0; col < col_num-1; col++){
            row_new_ends[col]->next = row_new_starts[col+1];
        }
        //update the head and tail pointers

        head = row_new_starts[0];
        tail = row_new_ends.back();


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


    

    //create the new row 
    int new_number [length*threshold];
    bool new_check [length*threshold];
    for (int i = 0; i < length*threshold; i++){
        new_number[i] = 0;
        new_check[i] = false;
    }


    initialize_array(volume);
    // print_array(volume, length);
    auto start2 = std::chrono::high_resolution_clock::now();
    move_east_old(new_number, new_check, length);
    // print_array(new_volume, length);
    auto stop2 = std::chrono::high_resolution_clock::now();

    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);
    cout << "the time used to calculate the copy and past version is " << duration2.count() << " microseconds." << endl;





    // // cout<< "hollow world" << endl;

    //create an example array 
    int number [TOTAL_LENGTH]; 
    bool check [TOTAL_LENGTH];
    for (int i = 0; i < TOTAL_LENGTH; i++){
        number[i] = i;
        check [i] = true;
    }

    // //create the new row 
    // int new_number [length];
    // bool new_chceck [length];
    // for (int i = 0; i < length; i++){
    //     new_number[i] = 0;
    //     new_chceck[i] = false;
    // }

    // // cout<< "hollow world" << endl;



    //link_list_method 
    map_2D Map;
    auto start = std::chrono::high_resolution_clock::now();

    // pair<voxel_node*, voxel_node*> head_tail = Map.initialize_a_range(number,check,TOTAL_LENGTH);
    Map.initialize_the_map_and_remember(number,check,length,length);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    cout << "the time used to initialize the map is: " << duration.count() << " milliseconds." << endl;

    // Map.head = head_tail.first;
    // Map.tail = head_tail.second;
    // cout << "---> " << Map.tail->number << endl;
    // Map.displayTable(length, length);
    // cout << "the vector size is: " << Map.row_old_starts.size() << endl;
    // cout << "the vector size is: " << Map.row_old_ends.size() << endl;

    // auto start1 = std::chrono::high_resolution_clock::now();
    // Map.map_move_to_south(new_number,new_chceck, length);
    // auto stop1 = std::chrono::high_resolution_clock::now();
    // auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(stop1 - start1);
    // cout << "the time used update the new array is: " << duration1.count() << " microseconds." << endl;




    // cout << "hellow world"<< endl;
    // auto start1 = std::chrono::high_resolution_clock::now();
    // Map.map_move_to_east(new_number,new_chceck, length);
    // auto stop1 = std::chrono::high_resolution_clock::now();
    // auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(stop1 - start1);
    // cout << "the time used update the new array is: " << duration1.count() << " microseconds." << endl;
    // // Map.displayTable(length,length)
    


    // cout << "hellow world"<< endl;
    auto start1 = std::chrono::high_resolution_clock::now();

    Map.map_move_to_east_faster(length,new_number,new_check);

    auto stop1 = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(stop1 - start1);
    cout << "the time used update the new array is: " << duration1.count() << " microseconds." << endl;
    // // Map.displayTable(length,length);



    cout << endl << endl << endl;

    // Map.displayTable(length, length);


    return 0 ;
}