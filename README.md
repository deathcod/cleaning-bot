# cleaning-bot 

This is an implementation of graph traversal of the bot through points in 2d plane in optimal moves using different geometric algorithm

### details

Suppose that there is a x-y plane and set of points are listed on that plane.Now suppose a bot is placed in this plane and condition is imposed that the bot has to travel through these set of points such that the count of the moves is optimal.

**My first implementation**

Earlier implementation included 


* creating a vector of vector of points(x,y) and thus mapping.
```(vpp v)```
* now creating another vector to store distance between the points and there indexes ```std::vector< ss >save```
(purpose was to get the weight of all the edges on the graph, a start for creating a minimum spanning tree but this costed me **n^2^** )
* now sorting all the edges according to there distance costed **n^2^logn^2^**
* now used minimum spanning tree using disjoint set and path compression to get the required tree structure 
* but still there is an issue suppose that there are two paths available for the bot now one point is close then the other but this path will cost bot more as a whole then the other path, thus now used dp tree on minimum spanning tree to get the moves count in all the vertices such that the bot will have the clear idea about all the moves now the bot will choose the vertices which has least move and thus creating move in most optimal way.
* this implementation fails for larger n 
* thus created a new implementation.

>hr clean bot difficult.cpp

***second implementation***

This uses euclidean minimum spanning tree using delanuary triangulation and robust point find algorithm and serves my purpose in **nlogn** time.

To do this suppose first I create delanuary triangulation for that 
* find point in the exsisting triangle```triangle find_triangle(line z,point y)``` this checks whether a point lies left of the line or right of the line, for this I used vector cross product to get the sign (+) left (-) right.

checks if all the three side returns + then point lies inside the given triangle thus return that triangle 
``` 
if(!rightof(*a) && !rightof(*b) && !rightof(*c))
		return x
```
using robust point location algorithm to find the triangle
```
Function: BF Locate
In: X: Point whose location is to be found
T: Triangulation in which point is to be located
Out: e: Edge on which X lies, or which has the triangle containing X
on its left.
begin
    e := some edge of T
    if RightOf(X, e) then e := e.Sym endif
    while (true)
        if X = e.Org or X = e.Dest then
            return e
        else
            whichop := 0
            if not RightOf(X, e.Onext) then whichop += 1 endif
            if not RightOf(X, e.Dprev) then whichop += 2 endif
            case whichop of
                when 0: return e
                when 1: e := e.Onext
                when 2: e := e.Dprev
                when 3:
                    if dist(e.Onext,X) < dist(e.Dprev,X) then
                    e := e.Onext
                else
                    e := e.Dprev
                endif
            endcase
        endif
    endwhile
end
```

 as soon as I get the triangle I delete the outer triangle and create three inner triangle
+ ```void delete_triangle(line *x,triangle tt);```  to delete the triangle
+ ```void add_triangle(point *a,point *b,point *c);``` to add the three triangles
+ ```void delete_add_triangle(triangle tt,point *e);``` calls the above triangles to perform the task.

now to implement delanuary triangulation I use bfs to traverse through the edges of quadrilatral, the one which does not follow
+ ``` bool isdelaunary(point *a,point *b,point *c,point *d)``` 

and if it returns true then swapping of the egdes is done and the add and delete of the triangle is done,and the unvisited edges of the quadrilateral is inserted into the queue.Thus reconstructing the graph till no edges is in the queue.

Once all the points are placed and traingulation is done it means that each vertices is now connected to its closest vertice and thus now apply the minimum spanning tree on the sorted edges vs distance and repeat the previous process on this and then the overall time will be reduced to O(NlogN).

* bot-modified.cpp
* radar-modified.h
