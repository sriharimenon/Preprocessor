Greetings!

The preprocessor application reads a mesh file and interprets:
1. The neighboring nodes to each node;
2. The closest non-boundary node to each boundary node;
3. The boundary elements and the side of the element that's on the boundary.
4. The mesh file in another format compatible with an in-house software "visual 2d" for pictorial depiction of mesh.

These results are written in four different files, namely, grid.dat, bc.in, be.in and visual.dat, respectively.

The format of the mesh file is to be as follows:

<number of nodes> <number of elements>

//list of nodes 
<node> <x co-ord.> <y co-ord.>

//list of elements
<element><dummy><dummy> <n1> <n2> <n3>

//list of boundary nodes by boundary type
<number of boundary nodes of given boundary> <boundary type number>

NOTE:
1. The boundary type number is a numerical representation of the type of boundary condition to be imposed on the accompanying set of boundary nodes.
This app uses the following notation:

supersonic inflow: 1
subsonic inflow: 2
outflow: 3
symmetry: 4
wall: 5

2. Statements starting with a // are comments for the user's comprehension. It is absolutely  necessary  that the file be devoid of any alphabetical/special characters.

3. The side of the element which rests againt the boudary is denoted by 1, 2 or 3. A side is differentiated by the nodes on its ends. 
For example, the side made by joining n1 and n2 is denoted as 1. n2 and n3 is denoted by 2. n3 and n1 by 3.

LIMITS OF THE APP:
1. Coded only for 2D linear trinagular elements.
2. Maximum limit: 400000 nodes and 500000 elements.
3. Can only accomodate 11 neighbor nodes per node.