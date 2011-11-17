h1. JsonBenchmarkCpp 

JsonBenchmarkCpp is a small program to compare perfomance of different json libs available

Currently supporting following libs,

# Cajun
# json_spirit
# libjson

h2. Building

# Install "git":http://git-scm.com
# @git clone git://github.com/@
# Edit main.cpp to suit your requirements
# Edit Makefile accordingly
# make

h2. Sample output

$./JsonBenchmarkCpp > results.dat
$ cat results.dat
#library                 parsing                  writing                  
cajun                    1660                     114                      
json_spirit              8854                     499                      
libjson                  19                       3    

NOTE: Nos are in micro seconds.

Use the gnuplot script results/graph.p to draw bar diagram out of this data
$ ./graph.p > graph.jpg
