
cd trace_compression

mpicc -g  testcase/mpi_test.c  -o testcase/mpi_test.exe -L.. -lmpiP -lm  -lunwind

export LD_LIBRARY_PATH=$(pwd)/..
export MPIP="-f $(pwd)/report"
mpirun testcase/mpi_test.exe
#export MPIP="-f /home/ubuntu/Desktop/mpiP/testing/output"
# cd testing

# mpicc -g  1-hot-potato.c  -o 1-hot-potato.exe -L.. -lmpiP -lm  -lunwind

# export MPIP="-f /home/ubuntu/Desktop/mpiP/testing/output"
# export LD_LIBRARY_PATH=$(pwd)/..
# cd ../trace_compression
# mpirun ../testing/1-hot-potato.exe