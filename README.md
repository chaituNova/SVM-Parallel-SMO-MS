# SVM-Parallel-SMO-MS
This code base is part of the final group project of High Peformance Computing Systems
The contributors to this code base are [shankar](https://github.com/shankar1224),[koutilya](https://github.com/koutilya40192),[vishal](https://github.com/kkvishal01),[chaitanya](https://github.com/chaituNova)

## Sources
The MPI SMO algorithm was implemented with the help from papers [1](http://keerthis.com/parallel_SMO_IEEE.pdf), [2](http://web.cs.iastate.edu/~honavar/keerthi-svm.pdf)

## Report
The report describing the performance improvements by parallelizing the SMO and MS is [here](https://drive.google.com/open?id=0B2Shb2I8kvJPeUZwaWZkWElkOGc).

## Usage
Requirements:
The following should be installed in your computer (preferably linux)
1) OpenMPI (for MPI cluster)
2) OpenMP 

Clone/download the repository. Then 'make' in each folder seperately.
Datasets folder is required to run each parallel algorithm. Download it from [here](https://drive.google.com/open?id=0B2Shb2I8kvJPU2kxUHphNEtUWjg). 
Then, untar it and place a copy in each algorithm folder. 
Usage of the compiled binary (smo) is self explanatory.
