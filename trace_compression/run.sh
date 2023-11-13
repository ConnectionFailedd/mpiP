
# cd trace_compression

# mpicc -g  testcase/mpi_test.c  -o testcase/mpi_test.exe -L.. -lmpiP -lm  -lunwind

# export LD_LIBRARY_PATH=$(pwd)/..
# export MPIP="-f $(pwd)/report"
# mpirun testcase/mpi_test.exe

cd trace_compression

# mpicc -g  testcase/mpi_test.c  -o testcase/mpi_test.exe -L.. -lmpiP -lm  -lunwind

export LD_LIBRARY_PATH=$(pwd)/..
export MPIP="-f $(pwd)/report"
mpirun testcase/mytest.exe


#export MPIP="-f /home/ubuntu/Desktop/mpiP/testing/output"
