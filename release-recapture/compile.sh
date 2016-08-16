# Script to compile the binaries
# Notes:
# Open X libraries required for CImg: -lX11 -lpthread
# -g gives more debug info for gdb

#echo "Compiling Background_subtract..."
#g++ -o Background_subtract Background_subtract.cc -lX11 -lpthread

echo "Compiling Background_subtract (AOI)..."
g++ -o Background_subtract_aoi Background_subtract_aoi.cc -lX11 -lpthread

echo "Compiling sum_brightness..."
g++ -o sum_brightness sum_brightness.cc -lX11 -lpthread

echo "Compiling project_to_axis..."
g++ -o project_to_axis project_to_axis.cc -lX11 -lpthread
