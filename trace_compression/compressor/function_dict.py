functionDict = {
    'MPI_Accumulate': {'id': 0, 'arguments': {'origin_addr': 'ptr', 'origin_count': 'int', 'origin_datatype': 'MPI_Datatype', 'target_rank': 'int', 'target_disp': 'int', 'target_count': 'int', 'target_datatype': 'MPI_Datatype', 'op': 'MPI_Op', 'win': 'MPI_Group'}},
    'MPI_Allgather': {'id': 1, 'arguments': {'sendbuf': 'ptr', 'sendcount': 'int', 'sendtype': 'MPI_Datatype', 'recvbuf': 'ptr', 'recvcount': 'int', 'recvtype': 'MPI_Datatype', 'comm': 'int'}},
    'MPI_Allgatherv': {'id': 2, 'arguments': {'sendbuf': 'ptr', 'sendcount': 'int', 'sendtype': 'MPI_Datatype', 'recvbuf': 'ptr', 'recvcounts': 'ptr', 'displs': 'ptr', 'recvtype': 'MPI_Datatype', 'comm': 'int'}},
    'MPI_Allreduce': {'id': 3, 'arguments': {'sendbuf': 'ptr', 'recvbuf': 'ptr', 'count': 'int', 'datatype': 'MPI_Datatype', 'op': 'MPI_Op', 'comm': 'int'}},
    'MPI_Alltoall': {'id': 4, 'arguments': {'sendbuf': 'ptr', 'sendcount': 'int', 'sendtype': 'MPI_Datatype', 'recvbuf': 'ptr', 'recvcnt': 'int', 'recvtype': 'MPI_Datatype', 'comm': 'int'}},
    'MPI_Alltoallv': {'id': 5, 'arguments': {'sendbuf': 'ptr', 'sendcnts': 'ptr', 'sdispls': 'ptr', 'sendtype': 'MPI_Datatype', 'recvbuf': 'ptr', 'recvcnts': 'ptr', 'rdispls': 'ptr', 'recvtype': 'MPI_Datatype', 'comm': 'int'}},
    'MPI_Barrier': {'id': 6, 'arguments': {'comm': 'int'}},
    'MPI_Bcast': {'id': 7, 'arguments': {'buffer': 'ptr', 'count': 'int', 'datatype': 'MPI_Datatype', 'root': 'int', 'comm': 'int'}},
    'MPI_Bsend': {'id': 8, 'arguments': {'buf': 'ptr', 'count': 'int', 'datatype': 'MPI_Datatype', 'dest': 'int', 'tag': 'int', 'comm': 'int'}},
    'MPI_Bsend_init': {'id': 9, 'arguments': {'buf': 'ptr', 'count': 'int', 'datatype': 'MPI_Datatype', 'dest': 'int', 'tag': 'int', 'comm': 'int', 'request': 'ptr'}},
    'MPI_Buffer_attach': {'id': 10, 'arguments': {'buffer': 'ptr', 'size': 'int'}},
    'MPI_Buffer_detach': {'id': 11, 'arguments': {'bufferptr': 'ptr', 'size': 'ptr'}},
    'MPI_Cancel': {'id': 12, 'arguments': {'request': 'ptr'}},
    'MPI_Cart_coords': {'id': 13, 'arguments': {'comm': 'int', 'rank': 'int', 'maxdims': 'int', 'coords': 'ptr'}},
    'MPI_Cart_create': {'id': 14, 'arguments': {'comm_old': 'int', 'ndims': 'int', 'dims': 'ptr', 'periods': 'ptr', 'reorder': 'int', 'comm_cart': 'ptr'}},
    'MPI_Cart_get': {'id': 15, 'arguments': {'comm': 'int', 'maxdims': 'int', 'dims': 'ptr', 'periods': 'ptr', 'coords': 'ptr'}},
    'MPI_Cart_map': {'id': 16, 'arguments': {'comm_old': 'int', 'ndims': 'int', 'dims': 'ptr', 'periods': 'ptr', 'newrank': 'ptr'}},
    'MPI_Cart_rank': {'id': 17, 'arguments': {'comm': 'int', 'coords': 'ptr', 'rank': 'ptr'}},
    'MPI_Cart_shift': {'id': 18, 'arguments': {'comm': 'int', 'direction': 'int', 'displ': 'int', 'source': 'ptr', 'dest': 'ptr'}},
    'MPI_Cart_sub': {'id': 19, 'arguments': {'comm': 'int', 'remain_dims': 'ptr', 'comm_new': 'ptr'}},
    'MPI_Cartdim_get': {'id': 20, 'arguments': {'comm': 'int', 'ndims': 'ptr'}},
    'MPI_Comm_create': {'id': 21, 'arguments': {'comm': 'int', 'group': 'MPI_Group', 'comm_out': 'ptr'}},
    'MPI_Comm_create_keyval': {'id': 22, 'arguments': {'comm_copy_attr_fn': 'ptr', 'comm_delete_attr_fn': 'ptr', 'comm_keyval': 'ptr', 'extra_state': 'ptr'}},
    'MPI_Comm_delete_attr': {'id': 23, 'arguments': {'comm': 'int', 'comm_keyval': 'int'}},
    'MPI_Comm_dup': {'id': 24, 'arguments': {'comm': 'int', 'comm_out': 'ptr'}},
    'MPI_Comm_free': {'id': 25, 'arguments': {'commp': 'ptr'}},
    'MPI_Comm_free_keyval': {'id': 26, 'arguments': {'keyval': 'ptr'}},
    'MPI_Comm_get_attr': {'id': 27, 'arguments': {'comm': 'int', 'comm_keyval': 'int', 'attribute_value': 'ptr', 'flag': 'ptr'}},
    'MPI_Comm_group': {'id': 28, 'arguments': {'comm': 'int', 'group': 'ptr'}},
    'MPI_Comm_remote_group': {'id': 29, 'arguments': {'comm': 'int', 'group': 'ptr'}},
    'MPI_Comm_remote_size': {'id': 30, 'arguments': {'comm': 'int', 'size': 'ptr'}},
    'MPI_Comm_set_attr': {'id': 31, 'arguments': {'comm': 'int', 'comm_keyval': 'int', 'attribute_value': 'ptr'}},
    'MPI_Comm_split': {'id': 32, 'arguments': {'comm': 'int', 'color': 'int', 'key': 'int', 'comm_out': 'ptr'}},
    'MPI_Comm_test_inter': {'id': 33, 'arguments': {'comm': 'int', 'flag': 'ptr'}},
    'MPI_Compare_and_swap': {'id': 34, 'arguments': {'origin_addr': 'ptr', 'compare_addr': 'ptr', 'result_addr': 'ptr', 'datatype': 'MPI_Datatype', 'target_rank': 'int', 'target_disp': 'int', 'win': 'MPI_Group'}},
    'MPI_Dims_create': {'id': 35, 'arguments': {'nnodes': 'int', 'ndims': 'int', 'dims': 'ptr'}},
    'MPI_Error_class': {'id': 36, 'arguments': {'errorcode': 'int', 'errorclass': 'ptr'}},
    'MPI_Fetch_and_op': {'id': 37, 'arguments': {'origin_addr': 'ptr', 'result_addr': 'ptr', 'datatype': 'MPI_Datatype', 'target_rank': 'int', 'target_disp': 'int', 'op': 'MPI_Op', 'win': 'MPI_Group'}},
    'MPI_File_close': {'id': 38, 'arguments': {'fh': 'ptr'}},
    'MPI_File_delete': {'id': 39, 'arguments': {'filename': 'ptr', 'info': 'MPI_Info'}},
    'MPI_File_get_amode': {'id': 40, 'arguments': {'fh': 'MPI_File', 'amode': 'ptr'}},
    'MPI_File_get_byte_offset': {'id': 41, 'arguments': {'fh': 'MPI_File', 'offset': 'int', 'disp': 'ptr'}},
    'MPI_File_get_group': {'id': 42, 'arguments': {'fh': 'MPI_File', 'group': 'ptr'}},
    'MPI_File_get_info': {'id': 43, 'arguments': {'fh': 'MPI_File', 'info': 'ptr'}},
    'MPI_File_get_position': {'id': 44, 'arguments': {'fh': 'MPI_File', 'offset': 'ptr'}},
    'MPI_File_get_size': {'id': 45, 'arguments': {'fh': 'MPI_File', 'size': 'ptr'}},
    'MPI_File_get_view': {'id': 46, 'arguments': {'fh': 'MPI_File', 'disp': 'ptr', 'etype': 'ptr', 'filetype': 'ptr', 'datarep': 'ptr'}},
    'MPI_File_open': {'id': 47, 'arguments': {'comm': 'int', 'filename': 'ptr', 'amode': 'int', 'info': 'MPI_Info', 'fh': 'ptr'}},
    'MPI_File_preallocate': {'id': 48, 'arguments': {'fh': 'MPI_File', 'size': 'int'}},
    'MPI_File_read': {'id': 49, 'arguments': {'fh': 'MPI_File', 'buf': 'ptr', 'count': 'int', 'datatype': 'MPI_Datatype', 'status': 'ptr'}},
    'MPI_File_read_all': {'id': 50, 'arguments': {'fh': 'MPI_File', 'buf': 'ptr', 'count': 'int', 'datatype': 'MPI_Datatype', 'status': 'ptr'}},
    'MPI_File_read_at': {'id': 51, 'arguments': {'fh': 'MPI_File', 'offset': 'int', 'buf': 'ptr', 'count': 'int', 'datatype': 'MPI_Datatype', 'status': 'ptr'}},
    'MPI_File_read_at_all': {'id': 52, 'arguments': {'fh': 'MPI_File', 'offset': 'int', 'buf': 'ptr', 'count': 'int', 'datatype': 'MPI_Datatype', 'status': 'ptr'}},
    'MPI_File_seek': {'id': 53, 'arguments': {'fh': 'MPI_File', 'offset': 'int', 'whence': 'int'}},
    'MPI_File_set_info': {'id': 54, 'arguments': {'fh': 'MPI_File', 'info': 'MPI_Info'}},
    'MPI_File_set_size': {'id': 55, 'arguments': {'fh': 'MPI_File', 'size': 'int'}},
    'MPI_File_set_view': {'id': 56, 'arguments': {'fh': 'MPI_File', 'disp': 'int', 'etype': 'MPI_Datatype', 'filetype': 'MPI_Datatype', 'datarep': 'ptr', 'info': 'MPI_Info'}},
    'MPI_File_sync': {'id': 57, 'arguments': {'fh': 'MPI_File'}},
    'MPI_File_write': {'id': 58, 'arguments': {'fh': 'MPI_File', 'buf': 'ptr', 'count': 'int', 'datatype': 'MPI_Datatype', 'status': 'ptr'}},
    'MPI_File_write_all': {'id': 59, 'arguments': {'fh': 'MPI_File', 'buf': 'ptr', 'count': 'int', 'datatype': 'MPI_Datatype', 'status': 'ptr'}},
    'MPI_File_write_at': {'id': 60, 'arguments': {'fh': 'MPI_File', 'offset': 'int', 'buf': 'ptr', 'count': 'int', 'datatype': 'MPI_Datatype', 'status': 'ptr'}},
    'MPI_File_write_at_all': {'id': 61, 'arguments': {'fh': 'MPI_File', 'offset': 'int', 'buf': 'ptr', 'count': 'int', 'datatype': 'MPI_Datatype', 'status': 'ptr'}},
    'MPI_Gather': {'id': 62, 'arguments': {'sendbuf': 'ptr', 'sendcnt': 'int', 'sendtype': 'MPI_Datatype', 'recvbuf': 'ptr', 'recvcount': 'int', 'recvtype': 'MPI_Datatype', 'root': 'int', 'comm': 'int'}},
    'MPI_Gatherv': {'id': 63, 'arguments': {'sendbuf': 'ptr', 'sendcnt': 'int', 'sendtype': 'MPI_Datatype', 'recvbuf': 'ptr', 'recvcnts': 'ptr', 'displs': 'ptr', 'recvtype': 'MPI_Datatype', 'root': 'int', 'comm': 'int'}},
    'MPI_Get': {'id': 64, 'arguments': {'origin_addr': 'ptr', 'origin_count': 'int', 'origin_datatype': 'MPI_Datatype', 'target_rank': 'int', 'target_disp': 'int', 'target_count': 'int', 'target_datatype': 'MPI_Datatype', 'win': 'MPI_Group'}},
    'MPI_Get_accumulate': {'id': 65, 'arguments': {'origin_addr': 'ptr', 'origin_count': 'int', 'origin_datatype': 'MPI_Datatype', 'result_addr': 'ptr', 'result_count': 'int', 'result_datatype': 'MPI_Datatype', 'target_rank': 'int', 'target_disp': 'int', 'target_count': 'int', 'target_datatype': 'MPI_Datatype', 'op': 'MPI_Op', 'win': 'MPI_Group'}},
    'MPI_Graph_create': {'id': 66, 'arguments': {'comm_old': 'int', 'nnodes': 'int', 'index': 'ptr', 'edges': 'ptr', 'reorder': 'int', 'comm_graph': 'ptr'}},
    'MPI_Graph_get': {'id': 67, 'arguments': {'comm': 'int', 'maxindex': 'int', 'maxedges': 'int', 'index': 'ptr', 'edges': 'ptr'}},
    'MPI_Graph_map': {'id': 68, 'arguments': {'comm_old': 'int', 'nnodes': 'int', 'index': 'ptr', 'edges': 'ptr', 'newrank': 'ptr'}},
    'MPI_Graph_neighbors': {'id': 69, 'arguments': {'comm': 'int', 'rank': 'int', 'maxneighbors': 'int', 'neighbors': 'ptr'}},
    'MPI_Graph_neighbors_count': {'id': 70, 'arguments': {'comm': 'int', 'rank': 'int', 'nneighbors': 'ptr'}},
    'MPI_Graphdims_get': {'id': 71, 'arguments': {'comm': 'int', 'nnodes': 'ptr', 'nedges': 'ptr'}},
    'MPI_Group_compare': {'id': 72, 'arguments': {'group1': 'MPI_Group', 'group2': 'MPI_Group', 'result': 'ptr'}},
    'MPI_Group_difference': {'id': 73, 'arguments': {'group1': 'MPI_Group', 'group2': 'MPI_Group', 'group_out': 'ptr'}},
    'MPI_Group_excl': {'id': 74, 'arguments': {'group': 'MPI_Group', 'n': 'int', 'ranks': 'ptr', 'newgroup': 'ptr'}},
    'MPI_Group_free': {'id': 75, 'arguments': {'group': 'ptr'}},
    'MPI_Group_incl': {'id': 76, 'arguments': {'group': 'MPI_Group', 'n': 'int', 'ranks': 'ptr', 'group_out': 'ptr'}},
    'MPI_Group_intersection': {'id': 77, 'arguments': {'group1': 'MPI_Group', 'group2': 'MPI_Group', 'group_out': 'ptr'}},
    'MPI_Group_translate_ranks': {'id': 78, 'arguments': {'group_a': 'MPI_Group', 'n': 'int', 'ranks_a': 'ptr', 'group_b': 'MPI_Group', 'ranks_b': 'ptr'}},
    'MPI_Group_union': {'id': 79, 'arguments': {'group1': 'MPI_Group', 'group2': 'MPI_Group', 'group_out': 'ptr'}},
    'MPI_Iallgather': {'id': 80, 'arguments': {'sendbuf': 'ptr', 'sendcount': 'int', 'sendtype': 'MPI_Datatype', 'recvbuf': 'ptr', 'recvcount': 'int', 'recvtype': 'MPI_Datatype', 'comm': 'int', 'request': 'ptr'}},
    'MPI_Iallgatherv': {'id': 81, 'arguments': {'sendbuf': 'ptr', 'sendcount': 'int', 'sendtype': 'MPI_Datatype', 'recvbuf': 'ptr', 'recvcounts': 'ptr', 'displs': 'ptr', 'recvtype': 'MPI_Datatype', 'comm': 'int', 'request': 'ptr'}},
    'MPI_Iallreduce': {'id': 82, 'arguments': {'sendbuf': 'ptr', 'recvbuf': 'ptr', 'count': 'int', 'datatype': 'MPI_Datatype', 'op': 'MPI_Op', 'comm': 'int', 'request': 'ptr'}},
    'MPI_Ialltoall': {'id': 83, 'arguments': {'sendbuf': 'ptr', 'sendcount': 'int', 'sendtype': 'MPI_Datatype', 'recvbuf': 'ptr', 'recvcount': 'int', 'recvtype': 'MPI_Datatype', 'comm': 'int', 'request': 'ptr'}},
    'MPI_Ialltoallv': {'id': 84, 'arguments': {'sendbuf': 'ptr', 'sendcounts': 'ptr', 'sdispls': 'ptr', 'sendtype': 'MPI_Datatype', 'recvbuf': 'ptr', 'recvcounts': 'ptr', 'rdispls': 'ptr', 'recvtype': 'MPI_Datatype', 'comm': 'int', 'request': 'ptr'}},
    'MPI_Ialltoallw': {'id': 85, 'arguments': {'sendbuf': 'ptr', 'sendcounts': 'ptr', 'sdispls': 'ptr', 'sendtypes': 'ptr', 'recvbuf': 'ptr', 'recvcounts': 'ptr', 'rdispls': 'ptr', 'recvtypes': 'ptr', 'comm': 'int', 'request': 'ptr'}},
    'MPI_Ibarrier': {'id': 86, 'arguments': {'comm': 'int', 'request': 'ptr'}},
    'MPI_Ibcast': {'id': 87, 'arguments': {'buffer': 'ptr', 'count': 'int', 'datatype': 'MPI_Datatype', 'root': 'int', 'comm': 'int', 'request': 'ptr'}},
    'MPI_Ibsend': {'id': 88, 'arguments': {'buf': 'ptr', 'count': 'int', 'datatype': 'MPI_Datatype', 'dest': 'int', 'tag': 'int', 'comm': 'int', 'request': 'ptr'}},
    'MPI_Iexscan': {'id': 89, 'arguments': {'sendbuf': 'ptr', 'recvbuf': 'ptr', 'count': 'int', 'datatype': 'MPI_Datatype', 'op': 'MPI_Op', 'comm': 'int', 'request': 'ptr'}},
    'MPI_Igather': {'id': 90, 'arguments': {'sendbuf': 'ptr', 'sendcount': 'int', 'sendtype': 'MPI_Datatype', 'recvbuf': 'ptr', 'recvcount': 'int', 'recvtype': 'MPI_Datatype', 'root': 'int', 'comm': 'int', 'request': 'ptr'}},
    'MPI_Igatherv': {'id': 91, 'arguments': {'sendbuf': 'ptr', 'sendcount': 'int', 'sendtype': 'MPI_Datatype', 'recvbuf': 'ptr', 'recvcounts': 'ptr', 'displs': 'ptr', 'recvtype': 'MPI_Datatype', 'root': 'int', 'comm': 'int', 'request': 'ptr'}},
    'MPI_Intercomm_create': {'id': 92, 'arguments': {'local_comm': 'int', 'local_leader': 'int', 'peer_comm': 'int', 'remote_leader': 'int', 'tag': 'int', 'comm_out': 'ptr'}},
    'MPI_Intercomm_merge': {'id': 93, 'arguments': {'comm': 'int', 'high': 'int', 'comm_out': 'ptr'}},
    'MPI_Iprobe': {'id': 94, 'arguments': {'source': 'int', 'tag': 'int', 'comm': 'int', 'flag': 'ptr', 'status': 'ptr'}},
    'MPI_Irecv': {'id': 95, 'arguments': {'buf': 'ptr', 'count': 'int', 'datatype': 'MPI_Datatype', 'source': 'int', 'tag': 'int', 'comm': 'int', 'request': 'ptr'}},
    'MPI_Ireduce': {'id': 96, 'arguments': {'sendbuf': 'ptr', 'recvbuf': 'ptr', 'count': 'int', 'datatype': 'MPI_Datatype', 'op': 'MPI_Op', 'root': 'int', 'comm': 'int', 'request': 'ptr'}},
    'MPI_Ireduce_scatter': {'id': 97, 'arguments': {'sendbuf': 'ptr', 'recvbuf': 'ptr', 'recvcounts': 'ptr', 'datatype': 'MPI_Datatype', 'op': 'MPI_Op', 'comm': 'int', 'request': 'ptr'}},
    'MPI_Ireduce_scatter_block': {'id': 98, 'arguments': {'sendbuf': 'ptr', 'recvbuf': 'ptr', 'recvcount': 'int', 'datatype': 'MPI_Datatype', 'op': 'MPI_Op', 'comm': 'int', 'request': 'ptr'}},
    'MPI_Irsend': {'id': 99, 'arguments': {'buf': 'ptr', 'count': 'int', 'datatype': 'MPI_Datatype', 'dest': 'int', 'tag': 'int', 'comm': 'int', 'request': 'ptr'}},
    'MPI_Iscan': {'id': 100, 'arguments': {'sendbuf': 'ptr', 'recvbuf': 'ptr', 'count': 'int', 'datatype': 'MPI_Datatype', 'op': 'MPI_Op', 'comm': 'int', 'request': 'ptr'}},
    'MPI_Iscatter': {'id': 101, 'arguments': {'sendbuf': 'ptr', 'sendcount': 'int', 'sendtype': 'MPI_Datatype', 'recvbuf': 'ptr', 'recvcount': 'int', 'recvtype': 'MPI_Datatype', 'root': 'int', 'comm': 'int', 'request': 'ptr'}},
    'MPI_Iscatterv': {'id': 102, 'arguments': {'sendbuf': 'ptr', 'sendcounts': 'ptr', 'displs': 'ptr', 'sendtype': 'MPI_Datatype', 'recvbuf': 'ptr', 'recvcount': 'int', 'recvtype': 'MPI_Datatype', 'root': 'int', 'comm': 'int', 'request': 'ptr'}},
    'MPI_Isend': {'id': 103, 'arguments': {'buf': 'ptr', 'count': 'int', 'datatype': 'MPI_Datatype', 'dest': 'int', 'tag': 'int', 'comm': 'int', 'request': 'ptr'}},
    'MPI_Issend': {'id': 104, 'arguments': {'buf': 'ptr', 'count': 'int', 'datatype': 'MPI_Datatype', 'dest': 'int', 'tag': 'int', 'comm': 'int', 'request': 'ptr'}},
    'MPI_Pack': {'id': 105, 'arguments': {'inbuf': 'ptr', 'incount': 'int', 'datatype': 'MPI_Datatype', 'outbuf': 'ptr', 'count': 'int', 'position': 'ptr', 'comm': 'int'}},
    'MPI_Probe': {'id': 106, 'arguments': {'source': 'int', 'tag': 'int', 'comm': 'int', 'status': 'ptr'}},
    'MPI_Put': {'id': 107, 'arguments': {'origin_addr': 'ptr', 'origin_count': 'int', 'origin_datatype': 'MPI_Datatype', 'target_rank': 'int', 'target_disp': 'int', 'target_count': 'int', 'target_datatype': 'MPI_Datatype', 'win': 'MPI_Group'}},
    'MPI_Raccumulate': {'id': 108, 'arguments': {'origin_addr': 'ptr', 'origin_count': 'int', 'origin_datatype': 'MPI_Datatype', 'target_rank': 'int', 'target_disp': 'int', 'target_count': 'int', 'target_datatype': 'MPI_Datatype', 'op': 'MPI_Op', 'win': 'MPI_Group', 'request': 'ptr'}},
    'MPI_Recv': {'id': 109, 'arguments': {'buf': 'ptr', 'count': 'int', 'datatype': 'MPI_Datatype', 'source': 'int', 'tag': 'int', 'comm': 'int', 'status': 'ptr'}},
    'MPI_Recv_init': {'id': 110, 'arguments': {'buf': 'ptr', 'count': 'int', 'datatype': 'MPI_Datatype', 'source': 'int', 'tag': 'int', 'comm': 'int', 'request': 'ptr'}},
    'MPI_Reduce': {'id': 111, 'arguments': {'sendbuf': 'ptr', 'recvbuf': 'ptr', 'count': 'int', 'datatype': 'MPI_Datatype', 'op': 'MPI_Op', 'root': 'int', 'comm': 'int'}},
    'MPI_Reduce_scatter': {'id': 112, 'arguments': {'sendbuf': 'ptr', 'recvbuf': 'ptr', 'recvcnts': 'ptr', 'datatype': 'MPI_Datatype', 'op': 'MPI_Op', 'comm': 'int'}},
    'MPI_Request_free': {'id': 113, 'arguments': {'request': 'ptr'}},
    'MPI_Rget': {'id': 114, 'arguments': {'origin_addr': 'ptr', 'origin_count': 'int', 'origin_datatype': 'MPI_Datatype', 'target_rank': 'int', 'target_disp': 'int', 'target_count': 'int', 'target_datatype': 'MPI_Datatype', 'win': 'MPI_Group', 'request': 'ptr'}},
    'MPI_Rget_accumulate': {'id': 115, 'arguments': {'origin_addr': 'ptr', 'origin_count': 'int', 'origin_datatype': 'MPI_Datatype', 'result_addr': 'ptr', 'result_count': 'int', 'result_datatype': 'MPI_Datatype', 'target_rank': 'int', 'target_disp': 'int', 'target_count': 'int', 'target_datatype': 'MPI_Datatype', 'op': 'MPI_Op', 'win': 'MPI_Group', 'request': 'ptr'}},
    'MPI_Rput': {'id': 116, 'arguments': {'origin_addr': 'ptr', 'origin_count': 'int', 'origin_datatype': 'MPI_Datatype', 'target_rank': 'int', 'target_disp': 'int', 'target_count': 'int', 'target_datatype': 'MPI_Datatype', 'win': 'MPI_Group', 'request': 'ptr'}},
    'MPI_Rsend': {'id': 117, 'arguments': {'buf': 'ptr', 'count': 'int', 'datatype': 'MPI_Datatype', 'dest': 'int', 'tag': 'int', 'comm': 'int'}},
    'MPI_Rsend_init': {'id': 118, 'arguments': {'buf': 'ptr', 'count': 'int', 'datatype': 'MPI_Datatype', 'dest': 'int', 'tag': 'int', 'comm': 'int', 'request': 'ptr'}},
    'MPI_Scan': {'id': 119, 'arguments': {'sendbuf': 'ptr', 'recvbuf': 'ptr', 'count': 'int', 'datatype': 'MPI_Datatype', 'op': 'MPI_Op', 'comm': 'int'}},
    'MPI_Scatter': {'id': 120, 'arguments': {'sendbuf': 'ptr', 'sendcnt': 'int', 'sendtype': 'MPI_Datatype', 'recvbuf': 'ptr', 'recvcnt': 'int', 'recvtype': 'MPI_Datatype', 'root': 'int', 'comm': 'int'}},
    'MPI_Scatterv': {'id': 121, 'arguments': {'sendbuf': 'ptr', 'sendcnts': 'ptr', 'displs': 'ptr', 'sendtype': 'MPI_Datatype', 'recvbuf': 'ptr', 'recvcnt': 'int', 'recvtype': 'MPI_Datatype', 'root': 'int', 'comm': 'int'}},
    'MPI_Send': {'id': 122, 'arguments': {'buf': 'ptr', 'count': 'int', 'datatype': 'MPI_Datatype', 'dest': 'int', 'tag': 'int', 'comm': 'int'}},
    'MPI_Send_init': {'id': 123, 'arguments': {'buf': 'ptr', 'count': 'int', 'datatype': 'MPI_Datatype', 'dest': 'int', 'tag': 'int', 'comm': 'int', 'request': 'ptr'}},
    'MPI_Sendrecv': {'id': 124, 'arguments': {'sendbuf': 'ptr', 'sendcount': 'int', 'sendtype': 'MPI_Datatype', 'dest': 'int', 'sendtag': 'int', 'recvbuf': 'ptr', 'recvcount': 'int', 'recvtype': 'MPI_Datatype', 'source': 'int', 'recvtag': 'int', 'comm': 'int', 'status': 'ptr'}},
    'MPI_Sendrecv_replace': {'id': 125, 'arguments': {'buf': 'ptr', 'count': 'int', 'datatype': 'MPI_Datatype', 'dest': 'int', 'sendtag': 'int', 'source': 'int', 'recvtag': 'int', 'comm': 'int', 'status': 'ptr'}},
    'MPI_Ssend': {'id': 126, 'arguments': {'buf': 'ptr', 'count': 'int', 'datatype': 'MPI_Datatype', 'dest': 'int', 'tag': 'int', 'comm': 'int'}},
    'MPI_Ssend_init': {'id': 127, 'arguments': {'buf': 'ptr', 'count': 'int', 'datatype': 'MPI_Datatype', 'dest': 'int', 'tag': 'int', 'comm': 'int', 'request': 'ptr'}},
    'MPI_Start': {'id': 128, 'arguments': {'request': 'ptr'}},
    'MPI_Startall': {'id': 129, 'arguments': {'count': 'int', 'array_of_requests': 'ptr'}},
    'MPI_Test': {'id': 130, 'arguments': {'request': 'ptr', 'flag': 'ptr', 'status': 'ptr'}},
    'MPI_Testall': {'id': 131, 'arguments': {'count': 'int', 'array_of_requests': 'ptr', 'flag': 'ptr', 'array_of_statuses': 'ptr'}},
    'MPI_Testany': {'id': 132, 'arguments': {'count': 'int', 'array_of_requests': 'ptr', 'index': 'ptr', 'flag': 'ptr', 'status': 'ptr'}},
    'MPI_Testsome': {'id': 133, 'arguments': {'incount': 'int', 'array_of_requests': 'ptr', 'count': 'ptr', 'array_of_indices': 'ptr', 'array_of_statuses': 'ptr'}},
    'MPI_Topo_test': {'id': 134, 'arguments': {'comm': 'int', 'top_type': 'ptr'}},
    'MPI_Type_commit': {'id': 135, 'arguments': {'datatype': 'ptr'}},
    'MPI_Type_free': {'id': 136, 'arguments': {'datatype': 'ptr'}},
    'MPI_Type_get_contents': {'id': 137, 'arguments': {'datatype': 'MPI_Datatype', 'max_integers': 'int', 'max_addresses': 'int', 'max_datatypes': 'int', 'array_of_integers': 'ptr', 'array_of_addresses': 'ptr', 'array_of_datatypes': 'ptr'}},
    'MPI_Type_get_envelope': {'id': 138, 'arguments': {'datatype': 'MPI_Datatype', 'num_integers': 'ptr', 'num_addresses': 'ptr', 'num_datatypes': 'ptr', 'combiner': 'ptr'}},
    'MPI_Unpack': {'id': 139, 'arguments': {'inbuf': 'ptr', 'insize': 'int', 'position': 'ptr', 'outbuf': 'ptr', 'count': 'int', 'datatype': 'MPI_Datatype', 'comm': 'int'}},
    'MPI_Wait': {'id': 140, 'arguments': {'request': 'ptr', 'status': 'ptr'}},
    'MPI_Waitall': {'id': 141, 'arguments': {'count': 'int', 'array_of_requests': 'ptr', 'array_of_statuses': 'ptr'}},
    'MPI_Waitany': {'id': 142, 'arguments': {'count': 'int', 'array_of_requests': 'ptr', 'index': 'ptr', 'status': 'ptr'}},
    'MPI_Waitsome': {'id': 143, 'arguments': {'incount': 'int', 'array_of_requests': 'ptr', 'count': 'ptr', 'array_of_indices': 'ptr', 'array_of_statuses': 'ptr'}},
    'MPI_Win_allocate': {'id': 144, 'arguments': {'size': 'int', 'disp_unit': 'int', 'info': 'MPI_Info', 'comm': 'int', 'baseptr': 'ptr', 'win': 'ptr'}},
    'MPI_Win_allocate_shared': {'id': 145, 'arguments': {'size': 'int', 'disp_unit': 'int', 'info': 'MPI_Info', 'comm': 'int', 'baseptr': 'ptr', 'win': 'ptr'}},
    'MPI_Win_attach': {'id': 146, 'arguments': {'win': 'MPI_Group', 'base': 'ptr', 'size': 'int'}},
    'MPI_Win_complete': {'id': 147, 'arguments': {'win': 'MPI_Group'}},
    'MPI_Win_create': {'id': 148, 'arguments': {'base': 'ptr', 'size': 'int', 'disp_unit': 'int', 'info': 'MPI_Info', 'comm': 'int', 'win': 'ptr'}},
    'MPI_Win_create_dynamic': {'id': 149, 'arguments': {'info': 'MPI_Info', 'comm': 'int', 'win': 'ptr'}},
    'MPI_Win_detach': {'id': 150, 'arguments': {'win': 'MPI_Group', 'base': 'ptr'}},
    'MPI_Win_fence': {'id': 151, 'arguments': {'assert': 'int', 'win': 'MPI_Group'}},
    'MPI_Win_flush': {'id': 152, 'arguments': {'rank': 'int', 'win': 'MPI_Group'}},
    'MPI_Win_flush_all': {'id': 153, 'arguments': {'win': 'MPI_Group'}},
    'MPI_Win_flush_local': {'id': 154, 'arguments': {'rank': 'int', 'win': 'MPI_Group'}},
    'MPI_Win_flush_local_all': {'id': 155, 'arguments': {'win': 'MPI_Group'}},
    'MPI_Win_free': {'id': 156, 'arguments': {'win': 'ptr'}},
    'MPI_Win_get_group': {'id': 157, 'arguments': {'win': 'MPI_Group', 'group': 'ptr'}},
    'MPI_Win_get_info': {'id': 158, 'arguments': {'win': 'MPI_Group', 'info_used': 'ptr'}},
    'MPI_Win_lock': {'id': 159, 'arguments': {'lock_type': 'int', 'rank': 'int', 'assert': 'int', 'win': 'MPI_Group'}},
    'MPI_Win_lock_all': {'id': 160, 'arguments': {'assert': 'int', 'win': 'MPI_Group'}},
    'MPI_Win_post': {'id': 161, 'arguments': {'group': 'MPI_Group', 'assert': 'int', 'win': 'MPI_Group'}},
    'MPI_Win_set_info': {'id': 162, 'arguments': {'win': 'MPI_Group', 'info': 'MPI_Info'}},
    'MPI_Win_shared_query': {'id': 163, 'arguments': {'win': 'MPI_Group', 'rank': 'int', 'size': 'ptr', 'disp_unit': 'ptr', 'baseptr': 'ptr'}},
    'MPI_Win_start': {'id': 164, 'arguments': {'group': 'MPI_Group', 'assert': 'int', 'win': 'MPI_Group'}},
    'MPI_Win_sync': {'id': 165, 'arguments': {'win': 'MPI_Group'}},
    'MPI_Win_test': {'id': 166, 'arguments': {'win': 'MPI_Group', 'flag': 'ptr'}},
    'MPI_Win_unlock': {'id': 167, 'arguments': {'rank': 'int', 'win': 'MPI_Group'}},
    'MPI_Win_unlock_all': {'id': 168, 'arguments': {'win': 'MPI_Group'}},
    'MPI_Win_wait': {'id': 169, 'arguments': {'win': 'MPI_Group'}},
}
functionList = [key for (key, value) in sorted(functionDict.items(), key=lambda x: x[1]['id'], reverse=False)]