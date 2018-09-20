#include <chrono>
#include <cmath>
#include <random>
#include <iostream>
#include <vector>
#include <exception>
#include <iomanip>
#include <utility>
#include <time.h>

// No edge weight will be more than 2 in any config of this prgm.
#define INF 3.0

using namespace std;

// Class for 2,3,4-dimensional vertices
// Note that in the case where a coordinate does not matter, distance function still works
class Vertex{
public:
    double x;
    double y;
    double z;
    double w;

    void gen_coords_1(default_random_engine& val){
        uniform_real_distribution<double> random (0.0, 1.0);
        x = random(val);
        y = 0.0;
        z = 0.0;
        w = 0.0;
    }

    void gen_coords_2(default_random_engine& val){
        uniform_real_distribution<double> random (0.0, 1.0);
        x = random(val);
        y = random(val);
        z = 0.0;
        w = 0.0;
    }

    void gen_coords_3(default_random_engine& val){
        uniform_real_distribution<double> random (0.0, 1.0);
        x = random(val);
        y = random(val);
        z = random(val);
        w = 0.0;
    }

    void gen_coords_4(default_random_engine& val){
        uniform_real_distribution<double> random (0.0, 1.0);
        x = random(val);
        y = random(val);
        z = random(val);
        w = random(val);
    }

    double get_dist(Vertex v) {
        return sqrt(pow(v.x - x, 2) + pow(v.y - y, 2) + pow(v.z - z, 2) + pow(v.w - w, 2));
    }
};


class MyTuple{
public:
    int index;
    double distance;
    int parent;

    void set_val(int ind, double dist, int par){
        index = ind;
        distance = dist;
        parent = par;
    }
};


// Heap exception handling
class HeapEmptyException: public exception
{
    virtual const char* what() const noexcept
    {
        return "Cannot pop off of empty heap";
    }
} heap_empty;


// Class for binary min heap, adapted from CLRS
class MinHeap{
public:
    // tuple of index, distance, and parent
    vector<MyTuple> array;

    // Automatic floor division in C++
    int parent(int i) {return (i+1)/2 - 1;}
    int left(int i) {return 2*(i+1)-1;}
    int right(int i) {return 2*(i+1);}

    // Exchange the places of two vertices on the heap
    void swap(int a, int b) {
        MyTuple temp = array[b];
        array[b] = array[a];
        array[a] = temp;
    }

    int heap_size;

    // For debugging purposes
    void display_heap(){
        for(int i = 0; i < heap_size; i++){
            cout << setw(1) << i << ": (" << array[i].index << ", " << array[i].distance << ", "
                 << array[i].parent << ")    ";

            if(((i+2) & (i+1)) == 0){
                cout << endl;

            }

        }
        cout << endl << endl;
    }


    void update_val(int i, double dist, int par){
        array[i].set_val(array[i].index, dist, par);
    }

    bool check_empty() {
        if (heap_size == 0){
            return true;
        }
        else {
            return false;
        }
    }


    // extract min
    MyTuple extract_min() {
        if (heap_size < 1) {
            throw heap_empty;
        }
        MyTuple max = array[0];
        array[0] = array[heap_size-1];
        heap_size--;
        min_heapify(0);
        return max;
    };

    // Recursively fix the heap starting at index i after inserting to or
    // removing from it
    void min_heapify(int i) {
        int smallest;
        int l = left(i);
        int r = right(i);

        if (l < heap_size && array[l].distance < array[i].distance) {
            smallest = l;
        }
        else {
            smallest = i;
        }
        if (r < heap_size && array[r].distance < array[smallest].distance) {
            smallest = r;
        }
        if (smallest != i) {
            swap(i, smallest);
            min_heapify(smallest);
        }
    }


    // Put vertex v with priority p into the right place on the heap
    // not really used here
    void insert(int index, double p) {
        heap_size++;
        array[heap_size-1].index = index;
        array[heap_size-1].distance = p;
        array[heap_size-1].parent = -1;
        int n = heap_size - 1;
        while(n != 0 && array[n].distance < array[parent(n)].distance){
            swap(n, parent(n));
        }
    };

    void build_heap() {
        for (int i = heap_size/2 - 1; i >= 0; i--){
            min_heapify(i);
        }
    }

    MinHeap(vector<MyTuple> vect) {
        array.reserve(vect.size());
        array = vect;
        heap_size = vect.size();
    }

};

int main(int argc, char* argv[]){
    // check for appropriate number of arguments
    if (argc != 5){
        cout << "Please enter the appropriate number of arguments (4)." << endl;
        return 1;
    }

    // random number generator
    long long seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine gen((unsigned)seed);
    uniform_real_distribution<double> random (0.0, 1.0);

    int debug = stoi(argv[1]);
    if (debug < 0 || debug > 4) {
        cout << "The debug flag must be set to a number between 0 and 4 inclusive. Please try again." << endl;
        return 1;
    }
    
    unsigned int n = (unsigned int) stoi(argv[2]);
    if (n > 131072 || n == 0) {
        cout << "The number of vertices must be an integer greater than 0 and less than 131073. Please try again." << endl;
        return 1;
    }
    
    int numtrials = stoi(argv[3]);
    if (numtrials < 1) {
        cout << "The number of trials must be an integer greater than 0. Please try again." << endl;
        return 1;
    }
    
    if (numtrials < 1) {
        cout << "Must run at least one trial." << endl;
        return 1;
    }
    
    int dimensions = stoi(argv[4]);

    // initialize the n vertices
    Vertex ver[n];

    // fill the matrix with vertices with coords
    double total = 0.0;
    double time_taken = 0.0;
    // initialize sum of edges in MST
    double edge_sum;
    clock_t t1, t2;


    for(int k = 0; k < numtrials; k++){
        t1 = clock();
        edge_sum = 0.0;

        if(dimensions == 1){
            for(int i = 0; i < n; i++){
                ver[i].gen_coords_1(gen);
            }
        }
        else if(dimensions == 2){
            for(int i = 0; i < n; i++){
                ver[i].gen_coords_2(gen);
            }
        }
        else if(dimensions == 3){
            for(int i = 0; i < n; i++){
                ver[i].gen_coords_3(gen);
            }
        }
        else if(dimensions == 4){
            for(int i = 0; i < n; i++){
                ver[i].gen_coords_4(gen);
            }
        }

        // temporary vertex to become heap
        vector<MyTuple> temp_heap;
        // create root
        MyTuple root;
        root.set_val(0, 0.0, -1);
        // insert root into temp heap
        temp_heap.push_back(root);
        // fill rest of temp heap with vertex info
        for (int i = 1; i < n; i++){
            MyTuple temp;
            temp.set_val(i, INF, -1);
            temp_heap.push_back(temp);
        }

        // initialize heap of size n
        MinHeap heap = MinHeap(temp_heap);
        heap.build_heap();


        // initialize counter for sum of edges
        int counter = 0;
        double dist = 0.0;

        // Prim's algorithm
        while (!heap.check_empty()) {


            MyTuple u = heap.extract_min();

            int from_index = u.index;

            for (int i = 0; i < heap.heap_size; i++){

                int to_index = heap.array[i].index;

                if (dimensions == 1 || dimensions == 2 || dimensions == 3 || dimensions == 4) {
                    dist = ver[from_index].get_dist(ver[to_index]);
                }
                else if (dimensions == 0){
                    dist = random(gen);
                }
                else {
                    cout << "The number of dimensions can only be an integer between 0 and 4 inclusive. Please try again." << endl;
                    return 1;
                }

                if (dist < (heap.array[i]).distance) {

                    heap.array[i].distance = dist;
                    heap.array[i].parent = from_index;

                }

            }
            edge_sum = edge_sum + u.distance;

            counter++;

            // fix heap order
            heap.build_heap();
        }

        t2 = clock();

        time_taken += double(t2-t1)/CLOCKS_PER_SEC;
        total += edge_sum;

        // report time taken per trial
        if(debug > 0 && debug < 4){
            cout << "The time taken to generate the minimum spanning tree in trial #" << k + 1 << " is " << double(t2-t1)/CLOCKS_PER_SEC << endl;
        }

        // report mst edge weight sums per trial
        if(debug > 0 && debug < 3){
            cout << "The sum of the edges of the minimum spanning tree over " << n << " vertices for trial #"
                 << k + 1 << " is " << edge_sum << endl;
        }

        // report all edge lengths in a table, if relevant
        if (debug > 0 && debug < 2 && dimensions > 0) {
            for (int i = 0; i < n; i++){
                for (int j = 0; j < n; j++){
                    cout << setw(10) << ver[i].get_dist(ver[j]);
                }
                cout << endl;
            }
            
            // report all coordinates of vertices
            cout << "[";
            for (int i = 0; i < n; i++) {
                if (dimensions == 1) {
                    cout << ver[i].x << ", ";
                }
                else if (dimensions == 2) {
                    cout << "(" << ver[i].x << ", " << ver[i].y << "), ";
                }
                else if (dimensions == 3) {
                    cout << "(" << ver[i].x << ", " << ver[i].y << ", " << ver[i].z << "), ";
                }
                else {
                    cout << "(" << ver[i].x << ", " << ver[i].y << ", " << ver[i].z << ", " << ver[i].w << "), ";
                }
            }
            cout << "]" << endl;
        }
    }

    if(debug > 0 && debug < 5){
        cout << "The average time taken to build a minimum spanning tree per trial is " <<  time_taken / numtrials << " seconds" << endl;
    }
    cout << total / numtrials << " " << n << " " << numtrials
         << " " << dimensions << endl;

    return 0;
}
