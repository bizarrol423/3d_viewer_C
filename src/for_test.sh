#!/bin/bash
touch new_cube.obj

echo "v 0 0 0" > cube.obj
echo "v 0 1 0" >> cube.obj
echo "v 1 1 0" >> cube.obj
echo "v 1 0 0" >> cube.obj
echo "v 0 0 1" >> cube.obj
echo "v 0 1 1" >> cube.obj
echo "v 1 1 1" >> cube.obj
echo "v 1 0 1" >> cube.obj
echo "f 1 2 3 4" >> cube.obj
echo "f 8 7 6 5" >> cube.obj
echo "f 6 7 3 2" >> cube.obj
echo "f 1 4 8 5" >> cube.obj
echo "f 7 8 4 3" >> cube.obj
echo "f 5 6 2 1" >> cube.obj
