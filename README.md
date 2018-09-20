# randmst: Prim's Algorithm Benchmarking
A program analyzing the performance and reporting the outcomes of running Prim's algorithm on various types of randomly generated graphs.

## Contributors
Ethan Craigo, Peter Seung Min Lee

## Background
Prim's algorithm is an algorithm that efficiently finds minimum spanning trees for undirected graphs with various edge weights. We wanted to investigate its performance on randomly generated complete graphs with varying edge weights and numbers of vertices, and additionally wanted to find the sum of all of the edge weights in the minimum spanning trees that the algorithm returned.

## Detailed Description
We designed a program that, in a specified number of trials, efficiently generates complete graphs with an also specified number of vertices. A user can choose to generate graphs with uniformly random edge weights between 0 and 1. The user can also choose to generate graphs in which vertices are given random positions in one, two, three, or four-dimensional space (all coordinates between 0 and 1) and the edge weights are the Euclidean distances between them.

Once the graphs are generated, Prim's algorithm is run on them to find a minimum spanning tree. The length of time that it takes to generate this tree is recorded. The edge weights of the minimum spanning tree found with Prim's algorithm are summed up, and the resulting number is also recorded. After all of the trials have concluded, the average sum of the edge weights of the minimum spanning trees for each trial is reported to the user.

## Installation
The following instructions are for computers with both `make` and `g++` programs installed. Your version of `g++` must support the C++11 standard.

Clone this repository into a folder on your computer. Once you have cloned it, open a terminal, type `make` into it, and press Enter. An executable file called `randmst` should appear in the same folder.

`make clean` removes the executable `randmst` from the folder again.

## Usage
You can run this program by typing the following into your terminal and pressing Enter:

```
./randmst <debug-flag> <num-vertices> <num-trials> <dimension>
```

where all the arguments surrounded by angle brackets are replaced according to the following specifications:

- `<debug-flag>` is an integer between 0 and 4 that specifies the verbosity of the program's output:
  - If `<debug-flag>` is 0, only four numbers are reported to the user. The first of these is the average sum of the edge weights of the minimum spanning trees generated over each of the program's trials, and the last three are the same numbers `<num-vertices>`, `<num-trials>`, and `<dimension>` that you specified above.
  - If `<debug-flag>` is 4, the average time taken to build a minimum spanning tree over the program's trials is also reported.
  - If `<debug-flag>` is 3, in addition to all of the above, the program lists the time taken to generate the minimum spanning tree for each trial in sequence.
  - If `<debug-flag>` is 2, in addition to the above, the sums of the edge weights of the minimum spanning tree generated for each trial are also returned.
  - If `<debug-flag>` is 1, in addition to the above, a table of all of the edge lengths in the graph is printed, along with a list of the coordinates of all of the vertices in the graph. Note that this only occurs if `<dimension>` is set to a value greater than 0.
- `<num-vertices>` is the number of vertices in each of the complete graphs generated for each trial, upon which Prim's algorithm will be run. This must be an integer greater than 0 and less than 131073. Note that the program may be very slow with extremely large numbers of vertices.
- `<num-trials>` is the number of graphs to be generated, and thus also the total number of times that Prim's algorithm will be run on them. It must be an integer greater than 0.
- Finally, `<dimension>` is an integer between 0 and 4 inclusive indicating the methodology behind determining the edge weights between vertices on the graphs generated. If it is 0, the weights of each edge in the graph will be a uniformly chosen random number between 0 and 1. If it is a number *n* greater than 0, then each vertex will be given random *n*-dimensional coordinates, each coordinate ranging between 0 and 1 inclusive, and the edge weights will be the Euclidean distance between the coordinates of two vertices, as specified above.

The output of the program varies with the setting of the `<debug-flag>` parameter, as specified above.
