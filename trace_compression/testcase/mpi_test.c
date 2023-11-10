#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // 确保总调用次数达到1000000次
    int total_calls = 10000;

    for (int i = 0; i < total_calls; i++) {
        // MPI_Send 和 MPI_Recv
        int send_data = rank;
        int recv_data;
        MPI_Send(&send_data, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
        MPI_Recv(&recv_data, 1, MPI_INT, (rank - 1 + size) % size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // MPI_Barrier
        MPI_Barrier(MPI_COMM_WORLD);

        // MPI_Allreduce
        int local_value = rank + 1;
        int global_sum;
        MPI_Allreduce(&local_value, &global_sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

        // MPI_Isend 和 MPI_Irecv
        MPI_Request request;
        MPI_Isend(&send_data, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD, &request);
        MPI_Irecv(&recv_data, 1, MPI_INT, (rank - 1 + size) % size, 0, MPI_COMM_WORLD, &request);

        // MPI_Sendrecv_replace
        MPI_Sendrecv_replace(&send_data, 1, MPI_INT, (rank + 1) % size, 0, (rank - 1 + size) % size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // MPI_Gather
        int gather_data[size];
        MPI_Gather(&send_data, 1, MPI_INT, gather_data, 1, MPI_INT, 0, MPI_COMM_WORLD);

        // MPI_Bcast
        MPI_Bcast(&send_data, 1, MPI_INT, 0, MPI_COMM_WORLD);

        // MPI_Scatter
        int sendbuf[size];
        int recvbuf;
        MPI_Scatter(sendbuf, 1, MPI_INT, &recvbuf, 1, MPI_INT, 0, MPI_COMM_WORLD);

        // MPI_Reduce
        int sum;
        int my_value = rank + 1;
        MPI_Reduce(&my_value, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

        // MPI_Allgather
        int allgather_data[size];
        MPI_Allgather(&send_data, 1, MPI_INT, allgather_data, 1, MPI_INT, MPI_COMM_WORLD);

        // MPI_Comm_split
        int color = rank % 2;
        MPI_Comm new_comm;
        MPI_Comm_split(MPI_COMM_WORLD, color, rank, &new_comm);

        // MPI_Comm_dup
        MPI_Comm new_comm_dup;
        MPI_Comm_dup(MPI_COMM_WORLD, &new_comm_dup);

        // MPI_Comm_free
        MPI_Comm_free(&new_comm);
        MPI_Comm_free(&new_comm_dup);
    }

    MPI_Finalize();
    return 0;
}