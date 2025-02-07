/* /work_dir/mpiP-wrappers.c */
/* DO NOT EDIT -- AUTOMATICALLY GENERATED! */
/* Timestamp: 13 November 2023 08:34  */
/* Location: dfa7d90d8eab posix */


#include <string.h>
#include "mpiPi.h"
#include "symbols.h"
#include "mpiPi_def.h"


#include <stdio.h>

static int nyaFlags[32];

typedef struct {
    MPI_Op op;
    const char * name;
} mpi_op_name_pair_t;
static mpi_op_name_pair_t mpi_op_name_map[] = {
    {MPI_MAX, "MPI_MAX"},
    {MPI_MIN, "MPI_MIN"},
    {MPI_SUM, "MPI_SUM"},
    {MPI_PROD, "MPI_PROD"},
    {MPI_LAND, "MPI_LAND"},
    {MPI_BAND, "MPI_BAND"},
    {MPI_LOR, "MPI_LOR"},
    {MPI_BOR, "MPI_BOR"},
    {MPI_LXOR, "MPI_LXOR"},
    {MPI_BXOR, "MPI_BXOR"},
    {MPI_MAXLOC, "MPI_MAXLOC"},
    {MPI_MINLOC, "MPI_MINLOC"}
};

const char * get_op_name(MPI_Op op) {
    for(int i = 0; i < 12; i ++) {
        if(op == mpi_op_name_map[i].op) {
            return mpi_op_name_map[i].name;
        }
    }
    return "USER_DEFINED";
}



/* --------------- MPI_Accumulate --------------- */

static int mpiPif_MPI_Accumulate( jmp_buf * base_jbuf, mpip_const_void_t  *origin_addr, int  * origin_count, MPI_Datatype  * origin_datatype, int  * target_rank, MPI_Aint  * target_disp, int  * target_count, MPI_Datatype  * target_datatype, MPI_Op  * op, MPI_Win  * win)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Accumulate( origin_addr,  * origin_count,  * origin_datatype,  * target_rank,  * target_disp,  * target_count,  * target_datatype,  * op,  * win);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Accumulate', ");
fprintf(nyaFp, "'arguments': {");
if(origin_addr == NULL) {
    fprintf(nyaFp, "'origin_addr': 0x0");
}
else {
    fprintf(nyaFp, "'origin_addr': %p", origin_addr);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'origin_count': %d", * origin_count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* origin_datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'origin_datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'origin_datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'target_rank': %d", * target_rank);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'target_disp': %ld", * target_disp);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'target_count': %d", * target_count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* target_datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'target_datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'target_datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'op': '%s'", get_op_name(* op));
fprintf(nyaFp, ", ");
MPI_Win_get_info(* win, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'win': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

PMPI_Type_size(*target_datatype, &tsize);
rmaSize = (double)(tsize * *target_count);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Accumulate");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Accumulate, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Accumulate */



extern int MPI_Accumulate ( mpip_const_void_t *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Accumulate( &jbuf, origin_addr,  & origin_count,  & origin_datatype,  & target_rank,  & target_disp,  & target_count,  & target_datatype,  & op,  & win );

return rc;
} /* MPI_Accumulate */


extern void F77_MPI_ACCUMULATE(mpip_const_void_t  *origin_addr, int  * origin_count, MPI_Fint  * origin_datatype, int  * target_rank, MPI_Aint  * target_disp, int  * target_count, MPI_Fint  * target_datatype, MPI_Fint  * op, MPI_Win  * win , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_origin_datatype;
MPI_Datatype c_target_datatype;
MPI_Op c_op;

c_origin_datatype = MPI_Type_f2c(*origin_datatype);
c_target_datatype = MPI_Type_f2c(*target_datatype);
c_op = MPI_Op_f2c(*op);

rc = mpiPif_MPI_Accumulate( &jbuf, origin_addr, origin_count, &c_origin_datatype, target_rank, target_disp, target_count, &c_target_datatype, &c_op, win );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_accumulate */



/* --------------- MPI_Allgather --------------- */

static int mpiPif_MPI_Allgather( jmp_buf * base_jbuf, mpip_const_void_t  *sendbuf, int  * sendcount, MPI_Datatype  * sendtype, void  *recvbuf, int  * recvcount, MPI_Datatype  * recvtype, MPI_Comm  * comm)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Allgather( sendbuf,  * sendcount,  * sendtype, recvbuf,  * recvcount,  * recvtype,  * comm);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Allgather', ");
fprintf(nyaFp, "'arguments': {");
if(sendbuf == NULL) {
    fprintf(nyaFp, "'sendbuf': 0x0");
}
else {
    fprintf(nyaFp, "'sendbuf': %p", sendbuf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'sendcount': %d", * sendcount);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* sendtype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'sendtype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'sendtype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
if(recvbuf == NULL) {
    fprintf(nyaFp, "'recvbuf': 0x0");
}
else {
    fprintf(nyaFp, "'recvbuf': %p", recvbuf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'recvcount': %d", * recvcount);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* recvtype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'recvtype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'recvtype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( *sendtype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*sendtype, &tsize);
messSize = (double)(tsize * *sendcount);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Allgather");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Allgather, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(hndl, mpiPi_MPI_Allgather, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Allgather */



extern int MPI_Allgather ( mpip_const_void_t *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Allgather( &jbuf, sendbuf,  & sendcount,  & sendtype, recvbuf,  & recvcount,  & recvtype,  & comm );

return rc;
} /* MPI_Allgather */


extern void F77_MPI_ALLGATHER(mpip_const_void_t  *sendbuf, int  * sendcount, MPI_Fint  * sendtype, void  *recvbuf, int  * recvcount, MPI_Fint  * recvtype, MPI_Fint  * comm , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_sendtype;
MPI_Datatype c_recvtype;
MPI_Comm c_comm;

c_sendtype = MPI_Type_f2c(*sendtype);
c_recvtype = MPI_Type_f2c(*recvtype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Allgather( &jbuf, sendbuf, sendcount, &c_sendtype, recvbuf, recvcount, &c_recvtype, &c_comm );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_allgather */



/* --------------- MPI_Allgatherv --------------- */

static int mpiPif_MPI_Allgatherv( jmp_buf * base_jbuf, mpip_const_void_t  *sendbuf, int  * sendcount, MPI_Datatype  * sendtype, void  *recvbuf, mpip_const_int_t  *recvcounts, mpip_const_int_t  *displs, MPI_Datatype  * recvtype, MPI_Comm  * comm)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Allgatherv( sendbuf,  * sendcount,  * sendtype, recvbuf, recvcounts, displs,  * recvtype,  * comm);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Allgatherv', ");
fprintf(nyaFp, "'arguments': {");
if(sendbuf == NULL) {
    fprintf(nyaFp, "'sendbuf': 0x0");
}
else {
    fprintf(nyaFp, "'sendbuf': %p", sendbuf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'sendcount': %d", * sendcount);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* sendtype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'sendtype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'sendtype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
if(recvbuf == NULL) {
    fprintf(nyaFp, "'recvbuf': 0x0");
}
else {
    fprintf(nyaFp, "'recvbuf': %p", recvbuf);
}
fprintf(nyaFp, ", ");
if(recvcounts == NULL) {
    fprintf(nyaFp, "'recvcounts': 0x0");
}
else {
    fprintf(nyaFp, "'recvcounts': %p", recvcounts);
}
fprintf(nyaFp, ", ");
if(displs == NULL) {
    fprintf(nyaFp, "'displs': 0x0");
}
else {
    fprintf(nyaFp, "'displs': %p", displs);
}
fprintf(nyaFp, ", ");
MPI_Type_get_name(* recvtype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'recvtype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'recvtype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( *sendtype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*sendtype, &tsize);
messSize = (double)(tsize * *sendcount);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Allgatherv");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Allgatherv, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(hndl, mpiPi_MPI_Allgatherv, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Allgatherv */



extern int MPI_Allgatherv ( mpip_const_void_t *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, mpip_const_int_t *recvcounts, mpip_const_int_t *displs, MPI_Datatype recvtype, MPI_Comm comm )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Allgatherv( &jbuf, sendbuf,  & sendcount,  & sendtype, recvbuf, recvcounts, displs,  & recvtype,  & comm );

return rc;
} /* MPI_Allgatherv */


extern void F77_MPI_ALLGATHERV(mpip_const_void_t  *sendbuf, int  * sendcount, MPI_Fint  * sendtype, void  *recvbuf, mpip_const_int_t  *recvcounts, mpip_const_int_t  *displs, MPI_Fint  * recvtype, MPI_Fint  * comm , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_sendtype;
MPI_Datatype c_recvtype;
MPI_Comm c_comm;

c_sendtype = MPI_Type_f2c(*sendtype);
c_recvtype = MPI_Type_f2c(*recvtype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Allgatherv( &jbuf, sendbuf, sendcount, &c_sendtype, recvbuf, recvcounts, displs, &c_recvtype, &c_comm );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_allgatherv */



/* --------------- MPI_Allreduce --------------- */

static int mpiPif_MPI_Allreduce( jmp_buf * base_jbuf, mpip_const_void_t  *sendbuf, void  *recvbuf, int  * count, MPI_Datatype  * datatype, MPI_Op  * op, MPI_Comm  * comm)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Allreduce( sendbuf, recvbuf,  * count,  * datatype,  * op,  * comm);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Allreduce', ");
fprintf(nyaFp, "'arguments': {");
if(sendbuf == NULL) {
    fprintf(nyaFp, "'sendbuf': 0x0");
}
else {
    fprintf(nyaFp, "'sendbuf': %p", sendbuf);
}
fprintf(nyaFp, ", ");
if(recvbuf == NULL) {
    fprintf(nyaFp, "'recvbuf': 0x0");
}
else {
    fprintf(nyaFp, "'recvbuf': %p", recvbuf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'count': %d", * count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'op': '%s'", get_op_name(* op));
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( *datatype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*datatype, &tsize);
messSize = (double)(tsize * *count);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Allreduce");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Allreduce, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(hndl, mpiPi_MPI_Allreduce, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Allreduce */



extern int MPI_Allreduce ( mpip_const_void_t *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Allreduce( &jbuf, sendbuf, recvbuf,  & count,  & datatype,  & op,  & comm );

return rc;
} /* MPI_Allreduce */


extern void F77_MPI_ALLREDUCE(mpip_const_void_t  *sendbuf, void  *recvbuf, int  * count, MPI_Fint  * datatype, MPI_Fint  * op, MPI_Fint  * comm , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Op c_op;
MPI_Comm c_comm;

c_datatype = MPI_Type_f2c(*datatype);
c_op = MPI_Op_f2c(*op);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Allreduce( &jbuf, sendbuf, recvbuf, count, &c_datatype, &c_op, &c_comm );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_allreduce */



/* --------------- MPI_Alltoall --------------- */

static int mpiPif_MPI_Alltoall( jmp_buf * base_jbuf, mpip_const_void_t  *sendbuf, int  * sendcount, MPI_Datatype  * sendtype, void  *recvbuf, int  * recvcnt, MPI_Datatype  * recvtype, MPI_Comm  * comm)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Alltoall( sendbuf,  * sendcount,  * sendtype, recvbuf,  * recvcnt,  * recvtype,  * comm);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Alltoall', ");
fprintf(nyaFp, "'arguments': {");
if(sendbuf == NULL) {
    fprintf(nyaFp, "'sendbuf': 0x0");
}
else {
    fprintf(nyaFp, "'sendbuf': %p", sendbuf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'sendcount': %d", * sendcount);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* sendtype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'sendtype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'sendtype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
if(recvbuf == NULL) {
    fprintf(nyaFp, "'recvbuf': 0x0");
}
else {
    fprintf(nyaFp, "'recvbuf': %p", recvbuf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'recvcnt': %d", * recvcnt);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* recvtype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'recvtype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'recvtype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( *sendtype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*sendtype, &tsize);
messSize = (double)(tsize * *sendcount);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Alltoall");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Alltoall, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(hndl, mpiPi_MPI_Alltoall, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Alltoall */



extern int MPI_Alltoall ( mpip_const_void_t *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcnt, MPI_Datatype recvtype, MPI_Comm comm )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Alltoall( &jbuf, sendbuf,  & sendcount,  & sendtype, recvbuf,  & recvcnt,  & recvtype,  & comm );

return rc;
} /* MPI_Alltoall */


extern void F77_MPI_ALLTOALL(mpip_const_void_t  *sendbuf, int  * sendcount, MPI_Fint  * sendtype, void  *recvbuf, int  * recvcnt, MPI_Fint  * recvtype, MPI_Fint  * comm , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_sendtype;
MPI_Datatype c_recvtype;
MPI_Comm c_comm;

c_sendtype = MPI_Type_f2c(*sendtype);
c_recvtype = MPI_Type_f2c(*recvtype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Alltoall( &jbuf, sendbuf, sendcount, &c_sendtype, recvbuf, recvcnt, &c_recvtype, &c_comm );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_alltoall */



/* --------------- MPI_Alltoallv --------------- */

static int mpiPif_MPI_Alltoallv( jmp_buf * base_jbuf, mpip_const_void_t  *sendbuf, mpip_const_int_t  *sendcnts, mpip_const_int_t  *sdispls, MPI_Datatype  * sendtype, void  *recvbuf, mpip_const_int_t  *recvcnts, mpip_const_int_t  *rdispls, MPI_Datatype  * recvtype, MPI_Comm  * comm)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Alltoallv( sendbuf, sendcnts, sdispls,  * sendtype, recvbuf, recvcnts, rdispls,  * recvtype,  * comm);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Alltoallv', ");
fprintf(nyaFp, "'arguments': {");
if(sendbuf == NULL) {
    fprintf(nyaFp, "'sendbuf': 0x0");
}
else {
    fprintf(nyaFp, "'sendbuf': %p", sendbuf);
}
fprintf(nyaFp, ", ");
if(sendcnts == NULL) {
    fprintf(nyaFp, "'sendcnts': 0x0");
}
else {
    fprintf(nyaFp, "'sendcnts': %p", sendcnts);
}
fprintf(nyaFp, ", ");
if(sdispls == NULL) {
    fprintf(nyaFp, "'sdispls': 0x0");
}
else {
    fprintf(nyaFp, "'sdispls': %p", sdispls);
}
fprintf(nyaFp, ", ");
MPI_Type_get_name(* sendtype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'sendtype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'sendtype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
if(recvbuf == NULL) {
    fprintf(nyaFp, "'recvbuf': 0x0");
}
else {
    fprintf(nyaFp, "'recvbuf': %p", recvbuf);
}
fprintf(nyaFp, ", ");
if(recvcnts == NULL) {
    fprintf(nyaFp, "'recvcnts': 0x0");
}
else {
    fprintf(nyaFp, "'recvcnts': %p", recvcnts);
}
fprintf(nyaFp, ", ");
if(rdispls == NULL) {
    fprintf(nyaFp, "'rdispls': 0x0");
}
else {
    fprintf(nyaFp, "'rdispls': %p", rdispls);
}
fprintf(nyaFp, ", ");
MPI_Type_get_name(* recvtype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'recvtype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'recvtype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Alltoallv");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Alltoallv, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(hndl, mpiPi_MPI_Alltoallv, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Alltoallv */



extern int MPI_Alltoallv ( mpip_const_void_t *sendbuf, mpip_const_int_t *sendcnts, mpip_const_int_t *sdispls, MPI_Datatype sendtype, void *recvbuf, mpip_const_int_t *recvcnts, mpip_const_int_t *rdispls, MPI_Datatype recvtype, MPI_Comm comm )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Alltoallv( &jbuf, sendbuf, sendcnts, sdispls,  & sendtype, recvbuf, recvcnts, rdispls,  & recvtype,  & comm );

return rc;
} /* MPI_Alltoallv */


extern void F77_MPI_ALLTOALLV(mpip_const_void_t  *sendbuf, mpip_const_int_t  *sendcnts, mpip_const_int_t  *sdispls, MPI_Fint  * sendtype, void  *recvbuf, mpip_const_int_t  *recvcnts, mpip_const_int_t  *rdispls, MPI_Fint  * recvtype, MPI_Fint  * comm , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_sendtype;
MPI_Datatype c_recvtype;
MPI_Comm c_comm;

c_sendtype = MPI_Type_f2c(*sendtype);
c_recvtype = MPI_Type_f2c(*recvtype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Alltoallv( &jbuf, sendbuf, sendcnts, sdispls, &c_sendtype, recvbuf, recvcnts, rdispls, &c_recvtype, &c_comm );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_alltoallv */



/* --------------- MPI_Barrier --------------- */

static int mpiPif_MPI_Barrier( jmp_buf * base_jbuf, MPI_Comm  * comm)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Barrier(  * comm);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Barrier', ");
fprintf(nyaFp, "'arguments': {");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Barrier");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Barrier, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(hndl, mpiPi_MPI_Barrier, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Barrier */



extern int MPI_Barrier ( MPI_Comm comm )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Barrier( &jbuf,  & comm );

return rc;
} /* MPI_Barrier */


extern void F77_MPI_BARRIER(MPI_Fint  * comm , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Barrier( &jbuf, &c_comm );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_barrier */



/* --------------- MPI_Bcast --------------- */

static int mpiPif_MPI_Bcast( jmp_buf * base_jbuf, void  *buffer, int  * count, MPI_Datatype  * datatype, int  * root, MPI_Comm  * comm)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Bcast( buffer,  * count,  * datatype,  * root,  * comm);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Bcast', ");
fprintf(nyaFp, "'arguments': {");
if(buffer == NULL) {
    fprintf(nyaFp, "'buffer': 0x0");
}
else {
    fprintf(nyaFp, "'buffer': %p", buffer);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'count': %d", * count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'root': %d", * root);
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( *datatype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*datatype, &tsize);
messSize = (double)(tsize * *count);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Bcast");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Bcast, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(hndl, mpiPi_MPI_Bcast, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Bcast */



extern int MPI_Bcast ( void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Bcast( &jbuf, buffer,  & count,  & datatype,  & root,  & comm );

return rc;
} /* MPI_Bcast */


extern void F77_MPI_BCAST(void  *buffer, int  * count, MPI_Fint  * datatype, int  * root, MPI_Fint  * comm , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Comm c_comm;

c_datatype = MPI_Type_f2c(*datatype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Bcast( &jbuf, buffer, count, &c_datatype, root, &c_comm );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_bcast */



/* --------------- MPI_Bsend --------------- */

static int mpiPif_MPI_Bsend( jmp_buf * base_jbuf, mpip_const_void_t  *buf, int  * count, MPI_Datatype  * datatype, int  * dest, int  * tag, MPI_Comm  * comm)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Bsend( buf,  * count,  * datatype,  * dest,  * tag,  * comm);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Bsend', ");
fprintf(nyaFp, "'arguments': {");
if(buf == NULL) {
    fprintf(nyaFp, "'buf': 0x0");
}
else {
    fprintf(nyaFp, "'buf': %p", buf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'count': %d", * count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'dest': %d", * dest);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'tag': %d", * tag);
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( *datatype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*datatype, &tsize);
messSize = (double)(tsize * *count);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Bsend");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Bsend, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_pt2pt_stats_report) { mpiPi_update_pt2pt_stats(hndl, mpiPi_MPI_Bsend, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Bsend */



extern int MPI_Bsend ( mpip_const_void_t *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Bsend( &jbuf, buf,  & count,  & datatype,  & dest,  & tag,  & comm );

return rc;
} /* MPI_Bsend */


extern void F77_MPI_BSEND(mpip_const_void_t  *buf, int  * count, MPI_Fint  * datatype, int  * dest, int  * tag, MPI_Fint  * comm , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Comm c_comm;

c_datatype = MPI_Type_f2c(*datatype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Bsend( &jbuf, buf, count, &c_datatype, dest, tag, &c_comm );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_bsend */



/* --------------- MPI_Bsend_init --------------- */

static int mpiPif_MPI_Bsend_init( jmp_buf * base_jbuf, mpip_const_void_t  *buf, int  * count, MPI_Datatype  * datatype, int  * dest, int  * tag, MPI_Comm  * comm, MPI_Request  *request)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Bsend_init( buf,  * count,  * datatype,  * dest,  * tag,  * comm, request);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Bsend_init', ");
fprintf(nyaFp, "'arguments': {");
if(buf == NULL) {
    fprintf(nyaFp, "'buf': 0x0");
}
else {
    fprintf(nyaFp, "'buf': %p", buf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'count': %d", * count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'dest': %d", * dest);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'tag': %d", * tag);
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(request == NULL) {
    fprintf(nyaFp, "'request': 0x0");
}
else {
    fprintf(nyaFp, "'request': %p", request);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Bsend_init");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Bsend_init, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Bsend_init */



extern int MPI_Bsend_init ( mpip_const_void_t *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Bsend_init( &jbuf, buf,  & count,  & datatype,  & dest,  & tag,  & comm, request );

return rc;
} /* MPI_Bsend_init */


extern void F77_MPI_BSEND_INIT(mpip_const_void_t  *buf, int  * count, MPI_Fint  * datatype, int  * dest, int  * tag, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Comm c_comm;
MPI_Request c_request;

c_datatype = MPI_Type_f2c(*datatype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Bsend_init( &jbuf, buf, count, &c_datatype, dest, tag, &c_comm, &c_request );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_bsend_init */



/* --------------- MPI_Buffer_attach --------------- */

static int mpiPif_MPI_Buffer_attach( jmp_buf * base_jbuf, void  *buffer, int  * size)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Buffer_attach( buffer,  * size);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Buffer_attach', ");
fprintf(nyaFp, "'arguments': {");
if(buffer == NULL) {
    fprintf(nyaFp, "'buffer': 0x0");
}
else {
    fprintf(nyaFp, "'buffer': %p", buffer);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'size': %d", * size);
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Buffer_attach");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Buffer_attach, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Buffer_attach */



extern int MPI_Buffer_attach ( void *buffer, int size )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Buffer_attach( &jbuf, buffer,  & size );

return rc;
} /* MPI_Buffer_attach */


extern void F77_MPI_BUFFER_ATTACH(void  *buffer, int  * size , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Buffer_attach( &jbuf, buffer, size );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_buffer_attach */



/* --------------- MPI_Buffer_detach --------------- */

static int mpiPif_MPI_Buffer_detach( jmp_buf * base_jbuf, void  *bufferptr, int  *size)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Buffer_detach( bufferptr, size);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Buffer_detach', ");
fprintf(nyaFp, "'arguments': {");
if(bufferptr == NULL) {
    fprintf(nyaFp, "'bufferptr': 0x0");
}
else {
    fprintf(nyaFp, "'bufferptr': %p", bufferptr);
}
fprintf(nyaFp, ", ");
if(size == NULL) {
    fprintf(nyaFp, "'size': 0x0");
}
else {
    fprintf(nyaFp, "'size': %p", size);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Buffer_detach");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Buffer_detach, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Buffer_detach */



extern int MPI_Buffer_detach ( void *bufferptr, int *size )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Buffer_detach( &jbuf, bufferptr, size );

return rc;
} /* MPI_Buffer_detach */


extern void F77_MPI_BUFFER_DETACH(void  *bufferptr, int  *size , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Buffer_detach( &jbuf, bufferptr, size );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_buffer_detach */



/* --------------- MPI_Cancel --------------- */

static int mpiPif_MPI_Cancel( jmp_buf * base_jbuf, MPI_Request  *request)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Cancel( request);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Cancel', ");
fprintf(nyaFp, "'arguments': {");
if(request == NULL) {
    fprintf(nyaFp, "'request': 0x0");
}
else {
    fprintf(nyaFp, "'request': %p", request);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Cancel");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Cancel, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Cancel */



extern int MPI_Cancel ( MPI_Request *request )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Cancel( &jbuf, request );

return rc;
} /* MPI_Cancel */


extern void F77_MPI_CANCEL(MPI_Fint  *request , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Request c_request;

c_request = MPI_Request_f2c(*request);

rc = mpiPif_MPI_Cancel( &jbuf, &c_request );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_cancel */



/* --------------- MPI_Cart_coords --------------- */

static int mpiPif_MPI_Cart_coords( jmp_buf * base_jbuf, MPI_Comm  * comm, int  * rank, int  * maxdims, int  *coords)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Cart_coords(  * comm,  * rank,  * maxdims, coords);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Cart_coords', ");
fprintf(nyaFp, "'arguments': {");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'rank': %d", * rank);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'maxdims': %d", * maxdims);
fprintf(nyaFp, ", ");
if(coords == NULL) {
    fprintf(nyaFp, "'coords': 0x0");
}
else {
    fprintf(nyaFp, "'coords': %p", coords);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Cart_coords");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Cart_coords, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Cart_coords */



extern int MPI_Cart_coords ( MPI_Comm comm, int rank, int maxdims, int *coords )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Cart_coords( &jbuf,  & comm,  & rank,  & maxdims, coords );

return rc;
} /* MPI_Cart_coords */


extern void F77_MPI_CART_COORDS(MPI_Fint  * comm, int  * rank, int  * maxdims, int  *coords , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Cart_coords( &jbuf, &c_comm, rank, maxdims, coords );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_cart_coords */



/* --------------- MPI_Cart_create --------------- */

static int mpiPif_MPI_Cart_create( jmp_buf * base_jbuf, MPI_Comm  * comm_old, int  * ndims, mpip_const_int_t  *dims, mpip_const_int_t  *periods, int  * reorder, MPI_Comm  *comm_cart)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Cart_create(  * comm_old,  * ndims, dims, periods,  * reorder, comm_cart);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Cart_create', ");
fprintf(nyaFp, "'arguments': {");
MPI_Comm_rank(* comm_old, &nyaRank);
fprintf(nyaFp, "'comm_old': %d", nyaRank);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'ndims': %d", * ndims);
fprintf(nyaFp, ", ");
if(dims == NULL) {
    fprintf(nyaFp, "'dims': 0x0");
}
else {
    fprintf(nyaFp, "'dims': %p", dims);
}
fprintf(nyaFp, ", ");
if(periods == NULL) {
    fprintf(nyaFp, "'periods': 0x0");
}
else {
    fprintf(nyaFp, "'periods': %p", periods);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'reorder': %d", * reorder);
fprintf(nyaFp, ", ");
if(comm_cart == NULL) {
    fprintf(nyaFp, "'comm_cart': 0x0");
}
else {
    fprintf(nyaFp, "'comm_cart': %p", comm_cart);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Cart_create");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Cart_create, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Cart_create */



extern int MPI_Cart_create ( MPI_Comm comm_old, int ndims, mpip_const_int_t *dims, mpip_const_int_t *periods, int reorder, MPI_Comm *comm_cart )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Cart_create( &jbuf,  & comm_old,  & ndims, dims, periods,  & reorder, comm_cart );

return rc;
} /* MPI_Cart_create */


extern void F77_MPI_CART_CREATE(MPI_Fint  * comm_old, int  * ndims, mpip_const_int_t  *dims, mpip_const_int_t  *periods, int  * reorder, MPI_Fint  *comm_cart , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm_old;
MPI_Comm c_comm_cart;

c_comm_old = MPI_Comm_f2c(*comm_old);

rc = mpiPif_MPI_Cart_create( &jbuf, &c_comm_old, ndims, dims, periods, reorder, &c_comm_cart );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*comm_cart = MPI_Comm_c2f(c_comm_cart);
}
return;
} /* mpi_cart_create */



/* --------------- MPI_Cart_get --------------- */

static int mpiPif_MPI_Cart_get( jmp_buf * base_jbuf, MPI_Comm  * comm, int  * maxdims, int  *dims, int  *periods, int  *coords)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Cart_get(  * comm,  * maxdims, dims, periods, coords);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Cart_get', ");
fprintf(nyaFp, "'arguments': {");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'maxdims': %d", * maxdims);
fprintf(nyaFp, ", ");
if(dims == NULL) {
    fprintf(nyaFp, "'dims': 0x0");
}
else {
    fprintf(nyaFp, "'dims': %p", dims);
}
fprintf(nyaFp, ", ");
if(periods == NULL) {
    fprintf(nyaFp, "'periods': 0x0");
}
else {
    fprintf(nyaFp, "'periods': %p", periods);
}
fprintf(nyaFp, ", ");
if(coords == NULL) {
    fprintf(nyaFp, "'coords': 0x0");
}
else {
    fprintf(nyaFp, "'coords': %p", coords);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Cart_get");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Cart_get, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Cart_get */



extern int MPI_Cart_get ( MPI_Comm comm, int maxdims, int *dims, int *periods, int *coords )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Cart_get( &jbuf,  & comm,  & maxdims, dims, periods, coords );

return rc;
} /* MPI_Cart_get */


extern void F77_MPI_CART_GET(MPI_Fint  * comm, int  * maxdims, int  *dims, int  *periods, int  *coords , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Cart_get( &jbuf, &c_comm, maxdims, dims, periods, coords );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_cart_get */



/* --------------- MPI_Cart_map --------------- */

static int mpiPif_MPI_Cart_map( jmp_buf * base_jbuf, MPI_Comm  * comm_old, int  * ndims, mpip_const_int_t  *dims, mpip_const_int_t  *periods, int  *newrank)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Cart_map(  * comm_old,  * ndims, dims, periods, newrank);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Cart_map', ");
fprintf(nyaFp, "'arguments': {");
MPI_Comm_rank(* comm_old, &nyaRank);
fprintf(nyaFp, "'comm_old': %d", nyaRank);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'ndims': %d", * ndims);
fprintf(nyaFp, ", ");
if(dims == NULL) {
    fprintf(nyaFp, "'dims': 0x0");
}
else {
    fprintf(nyaFp, "'dims': %p", dims);
}
fprintf(nyaFp, ", ");
if(periods == NULL) {
    fprintf(nyaFp, "'periods': 0x0");
}
else {
    fprintf(nyaFp, "'periods': %p", periods);
}
fprintf(nyaFp, ", ");
if(newrank == NULL) {
    fprintf(nyaFp, "'newrank': 0x0");
}
else {
    fprintf(nyaFp, "'newrank': %p", newrank);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Cart_map");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Cart_map, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Cart_map */



extern int MPI_Cart_map ( MPI_Comm comm_old, int ndims, mpip_const_int_t *dims, mpip_const_int_t *periods, int *newrank )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Cart_map( &jbuf,  & comm_old,  & ndims, dims, periods, newrank );

return rc;
} /* MPI_Cart_map */


extern void F77_MPI_CART_MAP(MPI_Fint  * comm_old, int  * ndims, mpip_const_int_t  *dims, mpip_const_int_t  *periods, int  *newrank , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm_old;

c_comm_old = MPI_Comm_f2c(*comm_old);

rc = mpiPif_MPI_Cart_map( &jbuf, &c_comm_old, ndims, dims, periods, newrank );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_cart_map */



/* --------------- MPI_Cart_rank --------------- */

static int mpiPif_MPI_Cart_rank( jmp_buf * base_jbuf, MPI_Comm  * comm, mpip_const_int_t  *coords, int  *rank)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Cart_rank(  * comm, coords, rank);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Cart_rank', ");
fprintf(nyaFp, "'arguments': {");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(coords == NULL) {
    fprintf(nyaFp, "'coords': 0x0");
}
else {
    fprintf(nyaFp, "'coords': %p", coords);
}
fprintf(nyaFp, ", ");
if(rank == NULL) {
    fprintf(nyaFp, "'rank': 0x0");
}
else {
    fprintf(nyaFp, "'rank': %p", rank);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Cart_rank");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Cart_rank, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Cart_rank */



extern int MPI_Cart_rank ( MPI_Comm comm, mpip_const_int_t *coords, int *rank )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Cart_rank( &jbuf,  & comm, coords, rank );

return rc;
} /* MPI_Cart_rank */


extern void F77_MPI_CART_RANK(MPI_Fint  * comm, mpip_const_int_t  *coords, int  *rank , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Cart_rank( &jbuf, &c_comm, coords, rank );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_cart_rank */



/* --------------- MPI_Cart_shift --------------- */

static int mpiPif_MPI_Cart_shift( jmp_buf * base_jbuf, MPI_Comm  * comm, int  * direction, int  * displ, int  *source, int  *dest)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Cart_shift(  * comm,  * direction,  * displ, source, dest);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Cart_shift', ");
fprintf(nyaFp, "'arguments': {");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'direction': %d", * direction);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'displ': %d", * displ);
fprintf(nyaFp, ", ");
if(source == NULL) {
    fprintf(nyaFp, "'source': 0x0");
}
else {
    fprintf(nyaFp, "'source': %p", source);
}
fprintf(nyaFp, ", ");
if(dest == NULL) {
    fprintf(nyaFp, "'dest': 0x0");
}
else {
    fprintf(nyaFp, "'dest': %p", dest);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Cart_shift");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Cart_shift, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Cart_shift */



extern int MPI_Cart_shift ( MPI_Comm comm, int direction, int displ, int *source, int *dest )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Cart_shift( &jbuf,  & comm,  & direction,  & displ, source, dest );

return rc;
} /* MPI_Cart_shift */


extern void F77_MPI_CART_SHIFT(MPI_Fint  * comm, int  * direction, int  * displ, int  *source, int  *dest , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Cart_shift( &jbuf, &c_comm, direction, displ, source, dest );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_cart_shift */



/* --------------- MPI_Cart_sub --------------- */

static int mpiPif_MPI_Cart_sub( jmp_buf * base_jbuf, MPI_Comm  * comm, mpip_const_int_t  *remain_dims, MPI_Comm  *comm_new)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Cart_sub(  * comm, remain_dims, comm_new);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Cart_sub', ");
fprintf(nyaFp, "'arguments': {");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(remain_dims == NULL) {
    fprintf(nyaFp, "'remain_dims': 0x0");
}
else {
    fprintf(nyaFp, "'remain_dims': %p", remain_dims);
}
fprintf(nyaFp, ", ");
if(comm_new == NULL) {
    fprintf(nyaFp, "'comm_new': 0x0");
}
else {
    fprintf(nyaFp, "'comm_new': %p", comm_new);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Cart_sub");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Cart_sub, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Cart_sub */



extern int MPI_Cart_sub ( MPI_Comm comm, mpip_const_int_t *remain_dims, MPI_Comm *comm_new )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Cart_sub( &jbuf,  & comm, remain_dims, comm_new );

return rc;
} /* MPI_Cart_sub */


extern void F77_MPI_CART_SUB(MPI_Fint  * comm, mpip_const_int_t  *remain_dims, MPI_Fint  *comm_new , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;
MPI_Comm c_comm_new;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Cart_sub( &jbuf, &c_comm, remain_dims, &c_comm_new );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*comm_new = MPI_Comm_c2f(c_comm_new);
}
return;
} /* mpi_cart_sub */



/* --------------- MPI_Cartdim_get --------------- */

static int mpiPif_MPI_Cartdim_get( jmp_buf * base_jbuf, MPI_Comm  * comm, int  *ndims)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Cartdim_get(  * comm, ndims);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Cartdim_get', ");
fprintf(nyaFp, "'arguments': {");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(ndims == NULL) {
    fprintf(nyaFp, "'ndims': 0x0");
}
else {
    fprintf(nyaFp, "'ndims': %p", ndims);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Cartdim_get");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Cartdim_get, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Cartdim_get */



extern int MPI_Cartdim_get ( MPI_Comm comm, int *ndims )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Cartdim_get( &jbuf,  & comm, ndims );

return rc;
} /* MPI_Cartdim_get */


extern void F77_MPI_CARTDIM_GET(MPI_Fint  * comm, int  *ndims , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Cartdim_get( &jbuf, &c_comm, ndims );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_cartdim_get */



/* --------------- MPI_Comm_create --------------- */

static int mpiPif_MPI_Comm_create( jmp_buf * base_jbuf, MPI_Comm  * comm, MPI_Group  * group, MPI_Comm  *comm_out)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Comm_create(  * comm,  * group, comm_out);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Comm_create', ");
fprintf(nyaFp, "'arguments': {");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
MPI_Group_size(* group, &nyaGroupSize);MPI_Group_rank(* group, &nyaGroupRank);fprintf(nyaFp, "'group': {");
fprintf(nyaFp, "'group_size': %d, ", nyaGroupSize);
fprintf(nyaFp, "'group_rank': %d", nyaGroupRank);
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
if(comm_out == NULL) {
    fprintf(nyaFp, "'comm_out': 0x0");
}
else {
    fprintf(nyaFp, "'comm_out': %p", comm_out);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Comm_create");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Comm_create, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Comm_create */



extern int MPI_Comm_create ( MPI_Comm comm, MPI_Group group, MPI_Comm *comm_out )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Comm_create( &jbuf,  & comm,  & group, comm_out );

return rc;
} /* MPI_Comm_create */


extern void F77_MPI_COMM_CREATE(MPI_Fint  * comm, MPI_Fint  * group, MPI_Fint  *comm_out , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;
MPI_Group c_group;
MPI_Comm c_comm_out;

c_comm = MPI_Comm_f2c(*comm);
c_group = MPI_Group_f2c(*group);

rc = mpiPif_MPI_Comm_create( &jbuf, &c_comm, &c_group, &c_comm_out );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*comm_out = MPI_Comm_c2f(c_comm_out);
}
return;
} /* mpi_comm_create */



/* --------------- MPI_Comm_create_keyval --------------- */

static int mpiPif_MPI_Comm_create_keyval( jmp_buf * base_jbuf, MPI_Comm_copy_attr_function  *comm_copy_attr_fn, MPI_Comm_delete_attr_function  *comm_delete_attr_fn, int  *comm_keyval, void  *extra_state)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Comm_create_keyval( comm_copy_attr_fn, comm_delete_attr_fn, comm_keyval, extra_state);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Comm_create_keyval', ");
fprintf(nyaFp, "'arguments': {");
if(comm_copy_attr_fn == NULL) {
    fprintf(nyaFp, "'comm_copy_attr_fn': 0x0");
}
else {
    fprintf(nyaFp, "'comm_copy_attr_fn': %p", comm_copy_attr_fn);
}
fprintf(nyaFp, ", ");
if(comm_delete_attr_fn == NULL) {
    fprintf(nyaFp, "'comm_delete_attr_fn': 0x0");
}
else {
    fprintf(nyaFp, "'comm_delete_attr_fn': %p", comm_delete_attr_fn);
}
fprintf(nyaFp, ", ");
if(comm_keyval == NULL) {
    fprintf(nyaFp, "'comm_keyval': 0x0");
}
else {
    fprintf(nyaFp, "'comm_keyval': %p", comm_keyval);
}
fprintf(nyaFp, ", ");
if(extra_state == NULL) {
    fprintf(nyaFp, "'extra_state': 0x0");
}
else {
    fprintf(nyaFp, "'extra_state': %p", extra_state);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Comm_create_keyval");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Comm_create_keyval, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Comm_create_keyval */



extern int MPI_Comm_create_keyval ( MPI_Comm_copy_attr_function *comm_copy_attr_fn, MPI_Comm_delete_attr_function *comm_delete_attr_fn, int *comm_keyval, void *extra_state )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Comm_create_keyval( &jbuf, comm_copy_attr_fn, comm_delete_attr_fn, comm_keyval, extra_state );

return rc;
} /* MPI_Comm_create_keyval */


extern void F77_MPI_COMM_CREATE_KEYVAL(MPI_Comm_copy_attr_function  *comm_copy_attr_fn, MPI_Comm_delete_attr_function  *comm_delete_attr_fn, int  *comm_keyval, void  *extra_state , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Comm_create_keyval( &jbuf, comm_copy_attr_fn, comm_delete_attr_fn, comm_keyval, extra_state );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_comm_create_keyval */



/* --------------- MPI_Comm_delete_attr --------------- */

static int mpiPif_MPI_Comm_delete_attr( jmp_buf * base_jbuf, MPI_Comm  * comm, int  * comm_keyval)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Comm_delete_attr(  * comm,  * comm_keyval);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Comm_delete_attr', ");
fprintf(nyaFp, "'arguments': {");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'comm_keyval': %d", * comm_keyval);
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Comm_delete_attr");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Comm_delete_attr, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Comm_delete_attr */



extern int MPI_Comm_delete_attr ( MPI_Comm comm, int comm_keyval )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Comm_delete_attr( &jbuf,  & comm,  & comm_keyval );

return rc;
} /* MPI_Comm_delete_attr */


extern void F77_MPI_COMM_DELETE_ATTR(MPI_Fint  * comm, int  * comm_keyval , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Comm_delete_attr( &jbuf, &c_comm, comm_keyval );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_comm_delete_attr */



/* --------------- MPI_Comm_dup --------------- */

static int mpiPif_MPI_Comm_dup( jmp_buf * base_jbuf, MPI_Comm  * comm, MPI_Comm  *comm_out)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Comm_dup(  * comm, comm_out);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Comm_dup', ");
fprintf(nyaFp, "'arguments': {");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(comm_out == NULL) {
    fprintf(nyaFp, "'comm_out': 0x0");
}
else {
    fprintf(nyaFp, "'comm_out': %p", comm_out);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Comm_dup");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Comm_dup, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Comm_dup */



extern int MPI_Comm_dup ( MPI_Comm comm, MPI_Comm *comm_out )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Comm_dup( &jbuf,  & comm, comm_out );

return rc;
} /* MPI_Comm_dup */


extern void F77_MPI_COMM_DUP(MPI_Fint  * comm, MPI_Fint  *comm_out , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;
MPI_Comm c_comm_out;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Comm_dup( &jbuf, &c_comm, &c_comm_out );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*comm_out = MPI_Comm_c2f(c_comm_out);
}
return;
} /* mpi_comm_dup */



/* --------------- MPI_Comm_free --------------- */

static int mpiPif_MPI_Comm_free( jmp_buf * base_jbuf, MPI_Comm  *commp)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Comm_free( commp);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Comm_free', ");
fprintf(nyaFp, "'arguments': {");
if(commp == NULL) {
    fprintf(nyaFp, "'commp': 0x0");
}
else {
    fprintf(nyaFp, "'commp': %p", commp);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Comm_free");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Comm_free, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Comm_free */



extern int MPI_Comm_free ( MPI_Comm *commp )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Comm_free( &jbuf, commp );

return rc;
} /* MPI_Comm_free */


extern void F77_MPI_COMM_FREE(MPI_Fint  *commp , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Comm c_commp;

c_commp = MPI_Comm_f2c(*commp);

rc = mpiPif_MPI_Comm_free( &jbuf, &c_commp );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*commp = MPI_Comm_c2f(c_commp);
}
return;
} /* mpi_comm_free */



/* --------------- MPI_Comm_free_keyval --------------- */

static int mpiPif_MPI_Comm_free_keyval( jmp_buf * base_jbuf, int  *keyval)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Comm_free_keyval( keyval);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Comm_free_keyval', ");
fprintf(nyaFp, "'arguments': {");
if(keyval == NULL) {
    fprintf(nyaFp, "'keyval': 0x0");
}
else {
    fprintf(nyaFp, "'keyval': %p", keyval);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Comm_free_keyval");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Comm_free_keyval, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Comm_free_keyval */



extern int MPI_Comm_free_keyval ( int *keyval )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Comm_free_keyval( &jbuf, keyval );

return rc;
} /* MPI_Comm_free_keyval */


extern void F77_MPI_COMM_FREE_KEYVAL(int  *keyval , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Comm_free_keyval( &jbuf, keyval );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_comm_free_keyval */



/* --------------- MPI_Comm_get_attr --------------- */

static int mpiPif_MPI_Comm_get_attr( jmp_buf * base_jbuf, MPI_Comm  * comm, int  * comm_keyval, void  *attribute_value, int  *flag)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Comm_get_attr(  * comm,  * comm_keyval, attribute_value, flag);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Comm_get_attr', ");
fprintf(nyaFp, "'arguments': {");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'comm_keyval': %d", * comm_keyval);
fprintf(nyaFp, ", ");
if(attribute_value == NULL) {
    fprintf(nyaFp, "'attribute_value': 0x0");
}
else {
    fprintf(nyaFp, "'attribute_value': %p", attribute_value);
}
fprintf(nyaFp, ", ");
if(flag == NULL) {
    fprintf(nyaFp, "'flag': 0x0");
}
else {
    fprintf(nyaFp, "'flag': %p", flag);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Comm_get_attr");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Comm_get_attr, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Comm_get_attr */



extern int MPI_Comm_get_attr ( MPI_Comm comm, int comm_keyval, void *attribute_value, int *flag )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Comm_get_attr( &jbuf,  & comm,  & comm_keyval, attribute_value, flag );

return rc;
} /* MPI_Comm_get_attr */


extern void F77_MPI_COMM_GET_ATTR(MPI_Fint  * comm, int  * comm_keyval, void  *attribute_value, int  *flag , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Comm_get_attr( &jbuf, &c_comm, comm_keyval, attribute_value, flag );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_comm_get_attr */



/* --------------- MPI_Comm_group --------------- */

static int mpiPif_MPI_Comm_group( jmp_buf * base_jbuf, MPI_Comm  * comm, MPI_Group  *group)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Comm_group(  * comm, group);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Comm_group', ");
fprintf(nyaFp, "'arguments': {");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(group == NULL) {
    fprintf(nyaFp, "'group': 0x0");
}
else {
    fprintf(nyaFp, "'group': %p", group);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Comm_group");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Comm_group, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Comm_group */



extern int MPI_Comm_group ( MPI_Comm comm, MPI_Group *group )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Comm_group( &jbuf,  & comm, group );

return rc;
} /* MPI_Comm_group */


extern void F77_MPI_COMM_GROUP(MPI_Fint  * comm, MPI_Fint  *group , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;
MPI_Group c_group;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Comm_group( &jbuf, &c_comm, &c_group );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*group = MPI_Group_c2f(c_group);
}
return;
} /* mpi_comm_group */



/* --------------- MPI_Comm_remote_group --------------- */

static int mpiPif_MPI_Comm_remote_group( jmp_buf * base_jbuf, MPI_Comm  * comm, MPI_Group  *group)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Comm_remote_group(  * comm, group);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Comm_remote_group', ");
fprintf(nyaFp, "'arguments': {");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(group == NULL) {
    fprintf(nyaFp, "'group': 0x0");
}
else {
    fprintf(nyaFp, "'group': %p", group);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Comm_remote_group");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Comm_remote_group, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Comm_remote_group */



extern int MPI_Comm_remote_group ( MPI_Comm comm, MPI_Group *group )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Comm_remote_group( &jbuf,  & comm, group );

return rc;
} /* MPI_Comm_remote_group */


extern void F77_MPI_COMM_REMOTE_GROUP(MPI_Fint  * comm, MPI_Fint  *group , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;
MPI_Group c_group;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Comm_remote_group( &jbuf, &c_comm, &c_group );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*group = MPI_Group_c2f(c_group);
}
return;
} /* mpi_comm_remote_group */



/* --------------- MPI_Comm_remote_size --------------- */

static int mpiPif_MPI_Comm_remote_size( jmp_buf * base_jbuf, MPI_Comm  * comm, int  *size)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Comm_remote_size(  * comm, size);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Comm_remote_size', ");
fprintf(nyaFp, "'arguments': {");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(size == NULL) {
    fprintf(nyaFp, "'size': 0x0");
}
else {
    fprintf(nyaFp, "'size': %p", size);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Comm_remote_size");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Comm_remote_size, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Comm_remote_size */



extern int MPI_Comm_remote_size ( MPI_Comm comm, int *size )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Comm_remote_size( &jbuf,  & comm, size );

return rc;
} /* MPI_Comm_remote_size */


extern void F77_MPI_COMM_REMOTE_SIZE(MPI_Fint  * comm, int  *size , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Comm_remote_size( &jbuf, &c_comm, size );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_comm_remote_size */



/* --------------- MPI_Comm_set_attr --------------- */

static int mpiPif_MPI_Comm_set_attr( jmp_buf * base_jbuf, MPI_Comm  * comm, int  * comm_keyval, void  *attribute_value)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Comm_set_attr(  * comm,  * comm_keyval, attribute_value);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Comm_set_attr', ");
fprintf(nyaFp, "'arguments': {");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'comm_keyval': %d", * comm_keyval);
fprintf(nyaFp, ", ");
if(attribute_value == NULL) {
    fprintf(nyaFp, "'attribute_value': 0x0");
}
else {
    fprintf(nyaFp, "'attribute_value': %p", attribute_value);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Comm_set_attr");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Comm_set_attr, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Comm_set_attr */



extern int MPI_Comm_set_attr ( MPI_Comm comm, int comm_keyval, void *attribute_value )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Comm_set_attr( &jbuf,  & comm,  & comm_keyval, attribute_value );

return rc;
} /* MPI_Comm_set_attr */


extern void F77_MPI_COMM_SET_ATTR(MPI_Fint  * comm, int  * comm_keyval, void  *attribute_value , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Comm_set_attr( &jbuf, &c_comm, comm_keyval, attribute_value );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_comm_set_attr */



/* --------------- MPI_Comm_split --------------- */

static int mpiPif_MPI_Comm_split( jmp_buf * base_jbuf, MPI_Comm  * comm, int  * color, int  * key, MPI_Comm  *comm_out)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Comm_split(  * comm,  * color,  * key, comm_out);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Comm_split', ");
fprintf(nyaFp, "'arguments': {");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'color': %d", * color);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'key': %d", * key);
fprintf(nyaFp, ", ");
if(comm_out == NULL) {
    fprintf(nyaFp, "'comm_out': 0x0");
}
else {
    fprintf(nyaFp, "'comm_out': %p", comm_out);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Comm_split");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Comm_split, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Comm_split */



extern int MPI_Comm_split ( MPI_Comm comm, int color, int key, MPI_Comm *comm_out )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Comm_split( &jbuf,  & comm,  & color,  & key, comm_out );

return rc;
} /* MPI_Comm_split */


extern void F77_MPI_COMM_SPLIT(MPI_Fint  * comm, int  * color, int  * key, MPI_Fint  *comm_out , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;
MPI_Comm c_comm_out;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Comm_split( &jbuf, &c_comm, color, key, &c_comm_out );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*comm_out = MPI_Comm_c2f(c_comm_out);
}
return;
} /* mpi_comm_split */



/* --------------- MPI_Comm_test_inter --------------- */

static int mpiPif_MPI_Comm_test_inter( jmp_buf * base_jbuf, MPI_Comm  * comm, int  *flag)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Comm_test_inter(  * comm, flag);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Comm_test_inter', ");
fprintf(nyaFp, "'arguments': {");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(flag == NULL) {
    fprintf(nyaFp, "'flag': 0x0");
}
else {
    fprintf(nyaFp, "'flag': %p", flag);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Comm_test_inter");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Comm_test_inter, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Comm_test_inter */



extern int MPI_Comm_test_inter ( MPI_Comm comm, int *flag )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Comm_test_inter( &jbuf,  & comm, flag );

return rc;
} /* MPI_Comm_test_inter */


extern void F77_MPI_COMM_TEST_INTER(MPI_Fint  * comm, int  *flag , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Comm_test_inter( &jbuf, &c_comm, flag );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_comm_test_inter */



/* --------------- MPI_Compare_and_swap --------------- */

static int mpiPif_MPI_Compare_and_swap( jmp_buf * base_jbuf, mpip_const_void_t  *origin_addr, mpip_const_void_t  *compare_addr, void  *result_addr, MPI_Datatype  * datatype, int  * target_rank, MPI_Aint  * target_disp, MPI_Win  * win)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Compare_and_swap( origin_addr, compare_addr, result_addr,  * datatype,  * target_rank,  * target_disp,  * win);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Compare_and_swap', ");
fprintf(nyaFp, "'arguments': {");
if(origin_addr == NULL) {
    fprintf(nyaFp, "'origin_addr': 0x0");
}
else {
    fprintf(nyaFp, "'origin_addr': %p", origin_addr);
}
fprintf(nyaFp, ", ");
if(compare_addr == NULL) {
    fprintf(nyaFp, "'compare_addr': 0x0");
}
else {
    fprintf(nyaFp, "'compare_addr': %p", compare_addr);
}
fprintf(nyaFp, ", ");
if(result_addr == NULL) {
    fprintf(nyaFp, "'result_addr': 0x0");
}
else {
    fprintf(nyaFp, "'result_addr': %p", result_addr);
}
fprintf(nyaFp, ", ");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'target_rank': %d", * target_rank);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'target_disp': %ld", * target_disp);
fprintf(nyaFp, ", ");
MPI_Win_get_info(* win, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'win': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Compare_and_swap");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Compare_and_swap, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Compare_and_swap */



extern int MPI_Compare_and_swap ( mpip_const_void_t *origin_addr, mpip_const_void_t *compare_addr, void *result_addr, MPI_Datatype datatype, int target_rank, MPI_Aint target_disp, MPI_Win win )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Compare_and_swap( &jbuf, origin_addr, compare_addr, result_addr,  & datatype,  & target_rank,  & target_disp,  & win );

return rc;
} /* MPI_Compare_and_swap */


extern void F77_MPI_COMPARE_AND_SWAP(mpip_const_void_t  *origin_addr, mpip_const_void_t  *compare_addr, void  *result_addr, MPI_Fint  * datatype, int  * target_rank, MPI_Aint  * target_disp, MPI_Win  * win , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;

c_datatype = MPI_Type_f2c(*datatype);

rc = mpiPif_MPI_Compare_and_swap( &jbuf, origin_addr, compare_addr, result_addr, &c_datatype, target_rank, target_disp, win );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_compare_and_swap */



/* --------------- MPI_Dims_create --------------- */

static int mpiPif_MPI_Dims_create( jmp_buf * base_jbuf, int  * nnodes, int  * ndims, int  *dims)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Dims_create(  * nnodes,  * ndims, dims);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Dims_create', ");
fprintf(nyaFp, "'arguments': {");
fprintf(nyaFp, "'nnodes': %d", * nnodes);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'ndims': %d", * ndims);
fprintf(nyaFp, ", ");
if(dims == NULL) {
    fprintf(nyaFp, "'dims': 0x0");
}
else {
    fprintf(nyaFp, "'dims': %p", dims);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Dims_create");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Dims_create, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Dims_create */



extern int MPI_Dims_create ( int nnodes, int ndims, int *dims )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Dims_create( &jbuf,  & nnodes,  & ndims, dims );

return rc;
} /* MPI_Dims_create */


extern void F77_MPI_DIMS_CREATE(int  * nnodes, int  * ndims, int  *dims , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Dims_create( &jbuf, nnodes, ndims, dims );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_dims_create */



/* --------------- MPI_Error_class --------------- */

static int mpiPif_MPI_Error_class( jmp_buf * base_jbuf, int  * errorcode, int  *errorclass)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Error_class(  * errorcode, errorclass);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Error_class', ");
fprintf(nyaFp, "'arguments': {");
fprintf(nyaFp, "'errorcode': %d", * errorcode);
fprintf(nyaFp, ", ");
if(errorclass == NULL) {
    fprintf(nyaFp, "'errorclass': 0x0");
}
else {
    fprintf(nyaFp, "'errorclass': %p", errorclass);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Error_class");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Error_class, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Error_class */



extern int MPI_Error_class ( int errorcode, int *errorclass )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Error_class( &jbuf,  & errorcode, errorclass );

return rc;
} /* MPI_Error_class */


extern void F77_MPI_ERROR_CLASS(int  * errorcode, int  *errorclass , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Error_class( &jbuf, errorcode, errorclass );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_error_class */



/* --------------- MPI_Fetch_and_op --------------- */

static int mpiPif_MPI_Fetch_and_op( jmp_buf * base_jbuf, mpip_const_void_t  *origin_addr, void  *result_addr, MPI_Datatype  * datatype, int  * target_rank, MPI_Aint  * target_disp, MPI_Op  * op, MPI_Win  * win)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Fetch_and_op( origin_addr, result_addr,  * datatype,  * target_rank,  * target_disp,  * op,  * win);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Fetch_and_op', ");
fprintf(nyaFp, "'arguments': {");
if(origin_addr == NULL) {
    fprintf(nyaFp, "'origin_addr': 0x0");
}
else {
    fprintf(nyaFp, "'origin_addr': %p", origin_addr);
}
fprintf(nyaFp, ", ");
if(result_addr == NULL) {
    fprintf(nyaFp, "'result_addr': 0x0");
}
else {
    fprintf(nyaFp, "'result_addr': %p", result_addr);
}
fprintf(nyaFp, ", ");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'target_rank': %d", * target_rank);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'target_disp': %ld", * target_disp);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'op': '%s'", get_op_name(* op));
fprintf(nyaFp, ", ");
MPI_Win_get_info(* win, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'win': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Fetch_and_op");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Fetch_and_op, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Fetch_and_op */



extern int MPI_Fetch_and_op ( mpip_const_void_t *origin_addr, void *result_addr, MPI_Datatype datatype, int target_rank, MPI_Aint target_disp, MPI_Op op, MPI_Win win )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Fetch_and_op( &jbuf, origin_addr, result_addr,  & datatype,  & target_rank,  & target_disp,  & op,  & win );

return rc;
} /* MPI_Fetch_and_op */


extern void F77_MPI_FETCH_AND_OP(mpip_const_void_t  *origin_addr, void  *result_addr, MPI_Fint  * datatype, int  * target_rank, MPI_Aint  * target_disp, MPI_Fint  * op, MPI_Win  * win , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Op c_op;

c_datatype = MPI_Type_f2c(*datatype);
c_op = MPI_Op_f2c(*op);

rc = mpiPif_MPI_Fetch_and_op( &jbuf, origin_addr, result_addr, &c_datatype, target_rank, target_disp, &c_op, win );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_fetch_and_op */



/* --------------- MPI_File_close --------------- */

static int mpiPif_MPI_File_close( jmp_buf * base_jbuf, MPI_File  *fh)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_File_close( fh);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_File_close', ");
fprintf(nyaFp, "'arguments': {");
if(fh == NULL) {
    fprintf(nyaFp, "'fh': 0x0");
}
else {
    fprintf(nyaFp, "'fh': %p", fh);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_File_close");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_File_close, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_File_close */



extern int MPI_File_close (MPI_File *fh)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_File_close( &jbuf, fh );

return rc;
} /* MPI_File_close */


extern void F77_MPI_FILE_CLOSE(MPI_Fint  *fh , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_File c_fh;

c_fh = MPI_File_f2c(*fh);

rc = mpiPif_MPI_File_close( &jbuf, &c_fh );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*fh = MPI_File_c2f(c_fh);
}
return;
} /* mpi_file_close */



/* --------------- MPI_File_delete --------------- */

static int mpiPif_MPI_File_delete( jmp_buf * base_jbuf, mpip_const_char_t  *filename, MPI_Info  * info)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_File_delete( filename,  * info);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_File_delete', ");
fprintf(nyaFp, "'arguments': {");
if(filename == NULL) {
    fprintf(nyaFp, "'filename': 0x0");
}
else {
    fprintf(nyaFp, "'filename': %p", filename);
}
fprintf(nyaFp, ", ");
MPI_Info_get_nkeys(* info, &nyaNKeys);
fprintf(nyaFp, "'info': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(* info, i, nyaKey);
    MPI_Info_get(* info, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_File_delete");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_File_delete, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_File_delete */



extern int MPI_File_delete (mpip_const_char_t *filename, MPI_Info info)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_File_delete( &jbuf, filename,  & info );

return rc;
} /* MPI_File_delete */


extern void F77_MPI_FILE_DELETE(mpip_const_char_t  *filename, MPI_Fint  * info , MPI_Fint *ierr , int filename_len) {
int rc;
jmp_buf jbuf;
  char *c_filename = NULL;
MPI_Info c_info;

  for(; filename_len > 0; filename_len--){
    if( filename[filename_len] != ' '){
      filename_len++; // The nyaLength is last symbol index + 1
      break;
    }
  }
  c_filename = calloc( filename_len + 1, sizeof(char));
  memcpy( c_filename, filename, filename_len);
c_info = MPI_Info_f2c(*info);

rc = mpiPif_MPI_File_delete( &jbuf, c_filename, &c_info );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_file_delete */



/* --------------- MPI_File_get_amode --------------- */

static int mpiPif_MPI_File_get_amode( jmp_buf * base_jbuf, MPI_File  * fh, int  *amode)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_File_get_amode(  * fh, amode);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_File_get_amode', ");
fprintf(nyaFp, "'arguments': {");
MPI_File_get_info(* fh, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'fh': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
if(amode == NULL) {
    fprintf(nyaFp, "'amode': 0x0");
}
else {
    fprintf(nyaFp, "'amode': %p", amode);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_File_get_amode");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_File_get_amode, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_File_get_amode */



extern int MPI_File_get_amode (MPI_File fh, int *amode)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_File_get_amode( &jbuf,  & fh, amode );

return rc;
} /* MPI_File_get_amode */


extern void F77_MPI_FILE_GET_AMODE(MPI_Fint  * fh, int  *amode , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_File c_fh;

c_fh = MPI_File_f2c(*fh);

rc = mpiPif_MPI_File_get_amode( &jbuf, &c_fh, amode );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_file_get_amode */



/* --------------- MPI_File_get_byte_offset --------------- */

static int mpiPif_MPI_File_get_byte_offset( jmp_buf * base_jbuf, MPI_File  * fh, MPI_Offset  * offset, MPI_Offset  *disp)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_File_get_byte_offset(  * fh,  * offset, disp);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_File_get_byte_offset', ");
fprintf(nyaFp, "'arguments': {");
MPI_File_get_info(* fh, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'fh': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'offset': %lld", * offset);
fprintf(nyaFp, ", ");
if(disp == NULL) {
    fprintf(nyaFp, "'disp': 0x0");
}
else {
    fprintf(nyaFp, "'disp': %p", disp);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_File_get_byte_offset");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_File_get_byte_offset, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_File_get_byte_offset */



extern int MPI_File_get_byte_offset (MPI_File fh, MPI_Offset offset, MPI_Offset *disp)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_File_get_byte_offset( &jbuf,  & fh,  & offset, disp );

return rc;
} /* MPI_File_get_byte_offset */


extern void F77_MPI_FILE_GET_BYTE_OFFSET(MPI_Fint  * fh, MPI_Offset  * offset, MPI_Offset  *disp , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_File c_fh;

c_fh = MPI_File_f2c(*fh);

rc = mpiPif_MPI_File_get_byte_offset( &jbuf, &c_fh, offset, disp );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_file_get_byte_offset */



/* --------------- MPI_File_get_group --------------- */

static int mpiPif_MPI_File_get_group( jmp_buf * base_jbuf, MPI_File  * fh, MPI_Group  *group)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_File_get_group(  * fh, group);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_File_get_group', ");
fprintf(nyaFp, "'arguments': {");
MPI_File_get_info(* fh, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'fh': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
if(group == NULL) {
    fprintf(nyaFp, "'group': 0x0");
}
else {
    fprintf(nyaFp, "'group': %p", group);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_File_get_group");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_File_get_group, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_File_get_group */



extern int MPI_File_get_group (MPI_File fh, MPI_Group *group)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_File_get_group( &jbuf,  & fh, group );

return rc;
} /* MPI_File_get_group */


extern void F77_MPI_FILE_GET_GROUP(MPI_Fint  * fh, MPI_Fint  *group , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_File c_fh;
MPI_Group c_group;

c_fh = MPI_File_f2c(*fh);

rc = mpiPif_MPI_File_get_group( &jbuf, &c_fh, &c_group );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*group = MPI_Group_c2f(c_group);
}
return;
} /* mpi_file_get_group */



/* --------------- MPI_File_get_info --------------- */

static int mpiPif_MPI_File_get_info( jmp_buf * base_jbuf, MPI_File  * fh, MPI_Info  *info)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_File_get_info(  * fh, info);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_File_get_info', ");
fprintf(nyaFp, "'arguments': {");
MPI_File_get_info(* fh, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'fh': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
if(info == NULL) {
    fprintf(nyaFp, "'info': 0x0");
}
else {
    fprintf(nyaFp, "'info': %p", info);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_File_get_info");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_File_get_info, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_File_get_info */



extern int MPI_File_get_info (MPI_File fh, MPI_Info *info)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_File_get_info( &jbuf,  & fh, info );

return rc;
} /* MPI_File_get_info */


extern void F77_MPI_FILE_GET_INFO(MPI_Fint  * fh, MPI_Fint  *info , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_File c_fh;
MPI_Info c_info;

c_fh = MPI_File_f2c(*fh);

rc = mpiPif_MPI_File_get_info( &jbuf, &c_fh, &c_info );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*info = MPI_Info_c2f(c_info);
}
return;
} /* mpi_file_get_info */



/* --------------- MPI_File_get_position --------------- */

static int mpiPif_MPI_File_get_position( jmp_buf * base_jbuf, MPI_File  * fh, MPI_Offset  *offset)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_File_get_position(  * fh, offset);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_File_get_position', ");
fprintf(nyaFp, "'arguments': {");
MPI_File_get_info(* fh, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'fh': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
if(offset == NULL) {
    fprintf(nyaFp, "'offset': 0x0");
}
else {
    fprintf(nyaFp, "'offset': %p", offset);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_File_get_position");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_File_get_position, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_File_get_position */



extern int MPI_File_get_position (MPI_File fh, MPI_Offset *offset)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_File_get_position( &jbuf,  & fh, offset );

return rc;
} /* MPI_File_get_position */


extern void F77_MPI_FILE_GET_POSITION(MPI_Fint  * fh, MPI_Offset  *offset , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_File c_fh;

c_fh = MPI_File_f2c(*fh);

rc = mpiPif_MPI_File_get_position( &jbuf, &c_fh, offset );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_file_get_position */



/* --------------- MPI_File_get_size --------------- */

static int mpiPif_MPI_File_get_size( jmp_buf * base_jbuf, MPI_File  * fh, MPI_Offset  *size)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_File_get_size(  * fh, size);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_File_get_size', ");
fprintf(nyaFp, "'arguments': {");
MPI_File_get_info(* fh, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'fh': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
if(size == NULL) {
    fprintf(nyaFp, "'size': 0x0");
}
else {
    fprintf(nyaFp, "'size': %p", size);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_File_get_size");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_File_get_size, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_File_get_size */



extern int MPI_File_get_size (MPI_File fh, MPI_Offset *size)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_File_get_size( &jbuf,  & fh, size );

return rc;
} /* MPI_File_get_size */


extern void F77_MPI_FILE_GET_SIZE(MPI_Fint  * fh, MPI_Offset  *size , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_File c_fh;

c_fh = MPI_File_f2c(*fh);

rc = mpiPif_MPI_File_get_size( &jbuf, &c_fh, size );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_file_get_size */



/* --------------- MPI_File_get_view --------------- */

static int mpiPif_MPI_File_get_view( jmp_buf * base_jbuf, MPI_File  * fh, MPI_Offset  *disp, MPI_Datatype  *etype, MPI_Datatype  *filetype, char  *datarep)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_File_get_view(  * fh, disp, etype, filetype, datarep);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_File_get_view', ");
fprintf(nyaFp, "'arguments': {");
MPI_File_get_info(* fh, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'fh': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
if(disp == NULL) {
    fprintf(nyaFp, "'disp': 0x0");
}
else {
    fprintf(nyaFp, "'disp': %p", disp);
}
fprintf(nyaFp, ", ");
if(etype == NULL) {
    fprintf(nyaFp, "'etype': 0x0");
}
else {
    fprintf(nyaFp, "'etype': %p", etype);
}
fprintf(nyaFp, ", ");
if(filetype == NULL) {
    fprintf(nyaFp, "'filetype': 0x0");
}
else {
    fprintf(nyaFp, "'filetype': %p", filetype);
}
fprintf(nyaFp, ", ");
if(datarep == NULL) {
    fprintf(nyaFp, "'datarep': 0x0");
}
else {
    fprintf(nyaFp, "'datarep': %p", datarep);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_File_get_view");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_File_get_view, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_File_get_view */



extern int MPI_File_get_view (MPI_File fh, MPI_Offset *disp, MPI_Datatype *etype, MPI_Datatype *filetype, char *datarep)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_File_get_view( &jbuf,  & fh, disp, etype, filetype, datarep );

return rc;
} /* MPI_File_get_view */


extern void F77_MPI_FILE_GET_VIEW(MPI_Fint  * fh, MPI_Offset  *disp, MPI_Fint  *etype, MPI_Fint  *filetype, char  *datarep , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_File c_fh;
MPI_Datatype c_etype;
MPI_Datatype c_filetype;

c_fh = MPI_File_f2c(*fh);

rc = mpiPif_MPI_File_get_view( &jbuf, &c_fh, disp, &c_etype, &c_filetype, datarep );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_file_get_view */



/* --------------- MPI_File_open --------------- */

static int mpiPif_MPI_File_open( jmp_buf * base_jbuf, MPI_Comm  * comm, mpip_const_char_t  *filename, int  * amode, MPI_Info  * info, MPI_File  *fh)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_File_open(  * comm, filename,  * amode,  * info, fh);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_File_open', ");
fprintf(nyaFp, "'arguments': {");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(filename == NULL) {
    fprintf(nyaFp, "'filename': 0x0");
}
else {
    fprintf(nyaFp, "'filename': %p", filename);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'amode': %d", * amode);
fprintf(nyaFp, ", ");
MPI_Info_get_nkeys(* info, &nyaNKeys);
fprintf(nyaFp, "'info': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(* info, i, nyaKey);
    MPI_Info_get(* info, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
if(fh == NULL) {
    fprintf(nyaFp, "'fh': 0x0");
}
else {
    fprintf(nyaFp, "'fh': %p", fh);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_File_open");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_File_open, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_File_open */



extern int MPI_File_open (MPI_Comm comm, mpip_const_char_t *filename, int amode, MPI_Info info, MPI_File *fh)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_File_open( &jbuf,  & comm, filename,  & amode,  & info, fh );

return rc;
} /* MPI_File_open */


extern void F77_MPI_FILE_OPEN(MPI_Fint  * comm, mpip_const_char_t  *filename, int  * amode, MPI_Fint  * info, MPI_Fint  *fh , MPI_Fint *ierr , int filename_len) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;
  char *c_filename = NULL;
MPI_Info c_info;
MPI_File c_fh;

  for(; filename_len > 0; filename_len--){
    if( filename[filename_len] != ' '){
      filename_len++; // The nyaLength is last symbol index + 1
      break;
    }
  }
  c_filename = calloc( filename_len + 1, sizeof(char));
  memcpy( c_filename, filename, filename_len);
c_comm = MPI_Comm_f2c(*comm);
c_info = MPI_Info_f2c(*info);

rc = mpiPif_MPI_File_open( &jbuf, &c_comm, c_filename, amode, &c_info, &c_fh );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*fh = MPI_File_c2f(c_fh);
}
return;
} /* mpi_file_open */



/* --------------- MPI_File_preallocate --------------- */

static int mpiPif_MPI_File_preallocate( jmp_buf * base_jbuf, MPI_File  * fh, MPI_Offset  * size)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_File_preallocate(  * fh,  * size);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_File_preallocate', ");
fprintf(nyaFp, "'arguments': {");
MPI_File_get_info(* fh, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'fh': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'size': %lld", * size);
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_File_preallocate");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_File_preallocate, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_File_preallocate */



extern int MPI_File_preallocate (MPI_File fh, MPI_Offset size)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_File_preallocate( &jbuf,  & fh,  & size );

return rc;
} /* MPI_File_preallocate */


extern void F77_MPI_FILE_PREALLOCATE(MPI_Fint  * fh, MPI_Offset  * size , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_File c_fh;

c_fh = MPI_File_f2c(*fh);

rc = mpiPif_MPI_File_preallocate( &jbuf, &c_fh, size );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_file_preallocate */



/* --------------- MPI_File_read --------------- */

static int mpiPif_MPI_File_read( jmp_buf * base_jbuf, MPI_File  * fh, void  *buf, int  * count, MPI_Datatype  * datatype, MPI_Status  *status)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_File_read(  * fh, buf,  * count,  * datatype, status);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_File_read', ");
fprintf(nyaFp, "'arguments': {");
MPI_File_get_info(* fh, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'fh': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
if(buf == NULL) {
    fprintf(nyaFp, "'buf': 0x0");
}
else {
    fprintf(nyaFp, "'buf': %p", buf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'count': %d", * count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
if(status == NULL) {
    fprintf(nyaFp, "'status': 0x0");
}
else {
    fprintf(nyaFp, "'status': %p", status);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

PMPI_Type_size(*datatype, &tsize);
ioSize = (double)(tsize * *count);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_File_read");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_File_read, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_File_read */



extern int MPI_File_read (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_File_read( &jbuf,  & fh, buf,  & count,  & datatype, status );

return rc;
} /* MPI_File_read */


extern void F77_MPI_FILE_READ(MPI_Fint  * fh, void  *buf, int  * count, MPI_Fint  * datatype, MPI_Status  *status , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_File c_fh;
MPI_Datatype c_datatype;

c_fh = MPI_File_f2c(*fh);
c_datatype = MPI_Type_f2c(*datatype);

rc = mpiPif_MPI_File_read( &jbuf, &c_fh, buf, count, &c_datatype, status );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_file_read */



/* --------------- MPI_File_read_all --------------- */

static int mpiPif_MPI_File_read_all( jmp_buf * base_jbuf, MPI_File  * fh, void  *buf, int  * count, MPI_Datatype  * datatype, MPI_Status  *status)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_File_read_all(  * fh, buf,  * count,  * datatype, status);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_File_read_all', ");
fprintf(nyaFp, "'arguments': {");
MPI_File_get_info(* fh, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'fh': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
if(buf == NULL) {
    fprintf(nyaFp, "'buf': 0x0");
}
else {
    fprintf(nyaFp, "'buf': %p", buf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'count': %d", * count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
if(status == NULL) {
    fprintf(nyaFp, "'status': 0x0");
}
else {
    fprintf(nyaFp, "'status': %p", status);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

PMPI_Type_size(*datatype, &tsize);
ioSize = (double)(tsize * *count);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_File_read_all");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_File_read_all, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_File_read_all */



extern int MPI_File_read_all (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_File_read_all( &jbuf,  & fh, buf,  & count,  & datatype, status );

return rc;
} /* MPI_File_read_all */


extern void F77_MPI_FILE_READ_ALL(MPI_Fint  * fh, void  *buf, int  * count, MPI_Fint  * datatype, MPI_Status  *status , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_File c_fh;
MPI_Datatype c_datatype;

c_fh = MPI_File_f2c(*fh);
c_datatype = MPI_Type_f2c(*datatype);

rc = mpiPif_MPI_File_read_all( &jbuf, &c_fh, buf, count, &c_datatype, status );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_file_read_all */



/* --------------- MPI_File_read_at --------------- */

static int mpiPif_MPI_File_read_at( jmp_buf * base_jbuf, MPI_File  * fh, MPI_Offset  * offset, void  *buf, int  * count, MPI_Datatype  * datatype, MPI_Status  *status)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_File_read_at(  * fh,  * offset, buf,  * count,  * datatype, status);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_File_read_at', ");
fprintf(nyaFp, "'arguments': {");
MPI_File_get_info(* fh, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'fh': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'offset': %lld", * offset);
fprintf(nyaFp, ", ");
if(buf == NULL) {
    fprintf(nyaFp, "'buf': 0x0");
}
else {
    fprintf(nyaFp, "'buf': %p", buf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'count': %d", * count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
if(status == NULL) {
    fprintf(nyaFp, "'status': 0x0");
}
else {
    fprintf(nyaFp, "'status': %p", status);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

PMPI_Type_size(*datatype, &tsize);
ioSize = (double)(tsize * *count);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_File_read_at");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_File_read_at, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_File_read_at */



extern int MPI_File_read_at (MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_File_read_at( &jbuf,  & fh,  & offset, buf,  & count,  & datatype, status );

return rc;
} /* MPI_File_read_at */


extern void F77_MPI_FILE_READ_AT(MPI_Fint  * fh, MPI_Offset  * offset, void  *buf, int  * count, MPI_Fint  * datatype, MPI_Status  *status , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_File c_fh;
MPI_Datatype c_datatype;

c_fh = MPI_File_f2c(*fh);
c_datatype = MPI_Type_f2c(*datatype);

rc = mpiPif_MPI_File_read_at( &jbuf, &c_fh, offset, buf, count, &c_datatype, status );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_file_read_at */



/* --------------- MPI_File_read_at_all --------------- */

static int mpiPif_MPI_File_read_at_all( jmp_buf * base_jbuf, MPI_File  * fh, MPI_Offset  * offset, void  *buf, int  * count, MPI_Datatype  * datatype, MPI_Status  *status)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_File_read_at_all(  * fh,  * offset, buf,  * count,  * datatype, status);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_File_read_at_all', ");
fprintf(nyaFp, "'arguments': {");
MPI_File_get_info(* fh, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'fh': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'offset': %lld", * offset);
fprintf(nyaFp, ", ");
if(buf == NULL) {
    fprintf(nyaFp, "'buf': 0x0");
}
else {
    fprintf(nyaFp, "'buf': %p", buf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'count': %d", * count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
if(status == NULL) {
    fprintf(nyaFp, "'status': 0x0");
}
else {
    fprintf(nyaFp, "'status': %p", status);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_File_read_at_all");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_File_read_at_all, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_File_read_at_all */



extern int MPI_File_read_at_all (MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_File_read_at_all( &jbuf,  & fh,  & offset, buf,  & count,  & datatype, status );

return rc;
} /* MPI_File_read_at_all */


extern void F77_MPI_FILE_READ_AT_ALL(MPI_Fint  * fh, MPI_Offset  * offset, void  *buf, int  * count, MPI_Fint  * datatype, MPI_Status  *status , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_File c_fh;
MPI_Datatype c_datatype;

c_fh = MPI_File_f2c(*fh);
c_datatype = MPI_Type_f2c(*datatype);

rc = mpiPif_MPI_File_read_at_all( &jbuf, &c_fh, offset, buf, count, &c_datatype, status );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_file_read_at_all */



/* --------------- MPI_File_seek --------------- */

static int mpiPif_MPI_File_seek( jmp_buf * base_jbuf, MPI_File  * fh, MPI_Offset  * offset, int  * whence)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_File_seek(  * fh,  * offset,  * whence);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_File_seek', ");
fprintf(nyaFp, "'arguments': {");
MPI_File_get_info(* fh, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'fh': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'offset': %lld", * offset);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'whence': %d", * whence);
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_File_seek");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_File_seek, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_File_seek */



extern int MPI_File_seek (MPI_File fh, MPI_Offset offset, int whence)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_File_seek( &jbuf,  & fh,  & offset,  & whence );

return rc;
} /* MPI_File_seek */


extern void F77_MPI_FILE_SEEK(MPI_Fint  * fh, MPI_Offset  * offset, int  * whence , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_File c_fh;

c_fh = MPI_File_f2c(*fh);

rc = mpiPif_MPI_File_seek( &jbuf, &c_fh, offset, whence );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_file_seek */



/* --------------- MPI_File_set_info --------------- */

static int mpiPif_MPI_File_set_info( jmp_buf * base_jbuf, MPI_File  * fh, MPI_Info  * info)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_File_set_info(  * fh,  * info);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_File_set_info', ");
fprintf(nyaFp, "'arguments': {");
MPI_File_get_info(* fh, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'fh': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
MPI_Info_get_nkeys(* info, &nyaNKeys);
fprintf(nyaFp, "'info': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(* info, i, nyaKey);
    MPI_Info_get(* info, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_File_set_info");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_File_set_info, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_File_set_info */



extern int MPI_File_set_info (MPI_File fh, MPI_Info info)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_File_set_info( &jbuf,  & fh,  & info );

return rc;
} /* MPI_File_set_info */


extern void F77_MPI_FILE_SET_INFO(MPI_Fint  * fh, MPI_Fint  * info , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_File c_fh;
MPI_Info c_info;

c_fh = MPI_File_f2c(*fh);
c_info = MPI_Info_f2c(*info);

rc = mpiPif_MPI_File_set_info( &jbuf, &c_fh, &c_info );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_file_set_info */



/* --------------- MPI_File_set_size --------------- */

static int mpiPif_MPI_File_set_size( jmp_buf * base_jbuf, MPI_File  * fh, MPI_Offset  * size)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_File_set_size(  * fh,  * size);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_File_set_size', ");
fprintf(nyaFp, "'arguments': {");
MPI_File_get_info(* fh, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'fh': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'size': %lld", * size);
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_File_set_size");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_File_set_size, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_File_set_size */



extern int MPI_File_set_size (MPI_File fh, MPI_Offset size)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_File_set_size( &jbuf,  & fh,  & size );

return rc;
} /* MPI_File_set_size */


extern void F77_MPI_FILE_SET_SIZE(MPI_Fint  * fh, MPI_Offset  * size , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_File c_fh;

c_fh = MPI_File_f2c(*fh);

rc = mpiPif_MPI_File_set_size( &jbuf, &c_fh, size );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_file_set_size */



/* --------------- MPI_File_set_view --------------- */

static int mpiPif_MPI_File_set_view( jmp_buf * base_jbuf, MPI_File  * fh, MPI_Offset  * disp, MPI_Datatype  * etype, MPI_Datatype  * filetype, mpip_const_char_t  *datarep, MPI_Info  * info)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_File_set_view(  * fh,  * disp,  * etype,  * filetype, datarep,  * info);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_File_set_view', ");
fprintf(nyaFp, "'arguments': {");
MPI_File_get_info(* fh, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'fh': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'disp': %lld", * disp);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* etype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'etype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'etype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
MPI_Type_get_name(* filetype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'filetype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'filetype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
if(datarep == NULL) {
    fprintf(nyaFp, "'datarep': 0x0");
}
else {
    fprintf(nyaFp, "'datarep': %p", datarep);
}
fprintf(nyaFp, ", ");
MPI_Info_get_nkeys(* info, &nyaNKeys);
fprintf(nyaFp, "'info': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(* info, i, nyaKey);
    MPI_Info_get(* info, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_File_set_view");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_File_set_view, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_File_set_view */



extern int MPI_File_set_view (MPI_File fh, MPI_Offset disp, MPI_Datatype etype, MPI_Datatype filetype, mpip_const_char_t *datarep, MPI_Info info)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_File_set_view( &jbuf,  & fh,  & disp,  & etype,  & filetype, datarep,  & info );

return rc;
} /* MPI_File_set_view */


extern void F77_MPI_FILE_SET_VIEW(MPI_Fint  * fh, MPI_Offset  * disp, MPI_Fint  * etype, MPI_Fint  * filetype, mpip_const_char_t  *datarep, MPI_Fint  * info , MPI_Fint *ierr , int datarep_len) {
int rc;
jmp_buf jbuf;
MPI_File c_fh;
MPI_Datatype c_etype;
MPI_Datatype c_filetype;
  char *c_datarep = NULL;
MPI_Info c_info;

  for(; datarep_len > 0; datarep_len--){
    if( datarep[datarep_len] != ' '){
      datarep_len++; // The nyaLength is last symbol index + 1
      break;
    }
  }
  c_datarep = calloc( datarep_len + 1, sizeof(char));
  memcpy( c_datarep, datarep, datarep_len);
c_fh = MPI_File_f2c(*fh);
c_etype = MPI_Type_f2c(*etype);
c_filetype = MPI_Type_f2c(*filetype);
c_info = MPI_Info_f2c(*info);

rc = mpiPif_MPI_File_set_view( &jbuf, &c_fh, disp, &c_etype, &c_filetype, c_datarep, &c_info );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_file_set_view */



/* --------------- MPI_File_sync --------------- */

static int mpiPif_MPI_File_sync( jmp_buf * base_jbuf, MPI_File  * fh)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_File_sync(  * fh);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_File_sync', ");
fprintf(nyaFp, "'arguments': {");
MPI_File_get_info(* fh, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'fh': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_File_sync");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_File_sync, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_File_sync */



extern int MPI_File_sync (MPI_File fh)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_File_sync( &jbuf,  & fh );

return rc;
} /* MPI_File_sync */


extern void F77_MPI_FILE_SYNC(MPI_Fint  * fh , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_File c_fh;

c_fh = MPI_File_f2c(*fh);

rc = mpiPif_MPI_File_sync( &jbuf, &c_fh );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_file_sync */



/* --------------- MPI_File_write --------------- */

static int mpiPif_MPI_File_write( jmp_buf * base_jbuf, MPI_File  * fh, mpip_const_void_t  *buf, int  * count, MPI_Datatype  * datatype, MPI_Status  *status)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_File_write(  * fh, buf,  * count,  * datatype, status);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_File_write', ");
fprintf(nyaFp, "'arguments': {");
MPI_File_get_info(* fh, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'fh': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
if(buf == NULL) {
    fprintf(nyaFp, "'buf': 0x0");
}
else {
    fprintf(nyaFp, "'buf': %p", buf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'count': %d", * count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
if(status == NULL) {
    fprintf(nyaFp, "'status': 0x0");
}
else {
    fprintf(nyaFp, "'status': %p", status);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

PMPI_Type_size(*datatype, &tsize);
ioSize = (double)(tsize * *count);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_File_write");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_File_write, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_File_write */



extern int MPI_File_write (MPI_File fh, mpip_const_void_t *buf, int count, MPI_Datatype datatype, MPI_Status *status)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_File_write( &jbuf,  & fh, buf,  & count,  & datatype, status );

return rc;
} /* MPI_File_write */


extern void F77_MPI_FILE_WRITE(MPI_Fint  * fh, mpip_const_void_t  *buf, int  * count, MPI_Fint  * datatype, MPI_Status  *status , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_File c_fh;
MPI_Datatype c_datatype;

c_fh = MPI_File_f2c(*fh);
c_datatype = MPI_Type_f2c(*datatype);

rc = mpiPif_MPI_File_write( &jbuf, &c_fh, buf, count, &c_datatype, status );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_file_write */



/* --------------- MPI_File_write_all --------------- */

static int mpiPif_MPI_File_write_all( jmp_buf * base_jbuf, MPI_File  * fh, mpip_const_void_t  *buf, int  * count, MPI_Datatype  * datatype, MPI_Status  *status)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_File_write_all(  * fh, buf,  * count,  * datatype, status);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_File_write_all', ");
fprintf(nyaFp, "'arguments': {");
MPI_File_get_info(* fh, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'fh': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
if(buf == NULL) {
    fprintf(nyaFp, "'buf': 0x0");
}
else {
    fprintf(nyaFp, "'buf': %p", buf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'count': %d", * count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
if(status == NULL) {
    fprintf(nyaFp, "'status': 0x0");
}
else {
    fprintf(nyaFp, "'status': %p", status);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

PMPI_Type_size(*datatype, &tsize);
ioSize = (double)(tsize * *count);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_File_write_all");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_File_write_all, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_File_write_all */



extern int MPI_File_write_all (MPI_File fh, mpip_const_void_t *buf, int count, MPI_Datatype datatype, MPI_Status *status)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_File_write_all( &jbuf,  & fh, buf,  & count,  & datatype, status );

return rc;
} /* MPI_File_write_all */


extern void F77_MPI_FILE_WRITE_ALL(MPI_Fint  * fh, mpip_const_void_t  *buf, int  * count, MPI_Fint  * datatype, MPI_Status  *status , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_File c_fh;
MPI_Datatype c_datatype;

c_fh = MPI_File_f2c(*fh);
c_datatype = MPI_Type_f2c(*datatype);

rc = mpiPif_MPI_File_write_all( &jbuf, &c_fh, buf, count, &c_datatype, status );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_file_write_all */



/* --------------- MPI_File_write_at --------------- */

static int mpiPif_MPI_File_write_at( jmp_buf * base_jbuf, MPI_File  * fh, MPI_Offset  * offset, mpip_const_void_t  *buf, int  * count, MPI_Datatype  * datatype, MPI_Status  *status)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_File_write_at(  * fh,  * offset, buf,  * count,  * datatype, status);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_File_write_at', ");
fprintf(nyaFp, "'arguments': {");
MPI_File_get_info(* fh, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'fh': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'offset': %lld", * offset);
fprintf(nyaFp, ", ");
if(buf == NULL) {
    fprintf(nyaFp, "'buf': 0x0");
}
else {
    fprintf(nyaFp, "'buf': %p", buf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'count': %d", * count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
if(status == NULL) {
    fprintf(nyaFp, "'status': 0x0");
}
else {
    fprintf(nyaFp, "'status': %p", status);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

PMPI_Type_size(*datatype, &tsize);
ioSize = (double)(tsize * *count);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_File_write_at");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_File_write_at, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_File_write_at */



extern int MPI_File_write_at (MPI_File fh, MPI_Offset offset, mpip_const_void_t *buf, int count, MPI_Datatype datatype, MPI_Status *status)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_File_write_at( &jbuf,  & fh,  & offset, buf,  & count,  & datatype, status );

return rc;
} /* MPI_File_write_at */


extern void F77_MPI_FILE_WRITE_AT(MPI_Fint  * fh, MPI_Offset  * offset, mpip_const_void_t  *buf, int  * count, MPI_Fint  * datatype, MPI_Status  *status , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_File c_fh;
MPI_Datatype c_datatype;

c_fh = MPI_File_f2c(*fh);
c_datatype = MPI_Type_f2c(*datatype);

rc = mpiPif_MPI_File_write_at( &jbuf, &c_fh, offset, buf, count, &c_datatype, status );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_file_write_at */



/* --------------- MPI_File_write_at_all --------------- */

static int mpiPif_MPI_File_write_at_all( jmp_buf * base_jbuf, MPI_File  * fh, MPI_Offset  * offset, mpip_const_void_t  *buf, int  * count, MPI_Datatype  * datatype, MPI_Status  *status)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_File_write_at_all(  * fh,  * offset, buf,  * count,  * datatype, status);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_File_write_at_all', ");
fprintf(nyaFp, "'arguments': {");
MPI_File_get_info(* fh, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'fh': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'offset': %lld", * offset);
fprintf(nyaFp, ", ");
if(buf == NULL) {
    fprintf(nyaFp, "'buf': 0x0");
}
else {
    fprintf(nyaFp, "'buf': %p", buf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'count': %d", * count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
if(status == NULL) {
    fprintf(nyaFp, "'status': 0x0");
}
else {
    fprintf(nyaFp, "'status': %p", status);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_File_write_at_all");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_File_write_at_all, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_File_write_at_all */



extern int MPI_File_write_at_all (MPI_File fh, MPI_Offset offset, mpip_const_void_t *buf, int count, MPI_Datatype datatype, MPI_Status *status)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_File_write_at_all( &jbuf,  & fh,  & offset, buf,  & count,  & datatype, status );

return rc;
} /* MPI_File_write_at_all */


extern void F77_MPI_FILE_WRITE_AT_ALL(MPI_Fint  * fh, MPI_Offset  * offset, mpip_const_void_t  *buf, int  * count, MPI_Fint  * datatype, MPI_Status  *status , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_File c_fh;
MPI_Datatype c_datatype;

c_fh = MPI_File_f2c(*fh);
c_datatype = MPI_Type_f2c(*datatype);

rc = mpiPif_MPI_File_write_at_all( &jbuf, &c_fh, offset, buf, count, &c_datatype, status );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_file_write_at_all */



/* --------------- MPI_Gather --------------- */

static int mpiPif_MPI_Gather( jmp_buf * base_jbuf, mpip_const_void_t  *sendbuf, int  * sendcnt, MPI_Datatype  * sendtype, void  *recvbuf, int  * recvcount, MPI_Datatype  * recvtype, int  * root, MPI_Comm  * comm)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Gather( sendbuf,  * sendcnt,  * sendtype, recvbuf,  * recvcount,  * recvtype,  * root,  * comm);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Gather', ");
fprintf(nyaFp, "'arguments': {");
if(sendbuf == NULL) {
    fprintf(nyaFp, "'sendbuf': 0x0");
}
else {
    fprintf(nyaFp, "'sendbuf': %p", sendbuf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'sendcnt': %d", * sendcnt);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* sendtype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'sendtype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'sendtype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
if(recvbuf == NULL) {
    fprintf(nyaFp, "'recvbuf': 0x0");
}
else {
    fprintf(nyaFp, "'recvbuf': %p", recvbuf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'recvcount': %d", * recvcount);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* recvtype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'recvtype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'recvtype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'root': %d", * root);
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( *sendtype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*sendtype, &tsize);
messSize = (double)(tsize * *sendcnt);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Gather");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Gather, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(hndl, mpiPi_MPI_Gather, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Gather */



extern int MPI_Gather ( mpip_const_void_t *sendbuf, int sendcnt, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Gather( &jbuf, sendbuf,  & sendcnt,  & sendtype, recvbuf,  & recvcount,  & recvtype,  & root,  & comm );

return rc;
} /* MPI_Gather */


extern void F77_MPI_GATHER(mpip_const_void_t  *sendbuf, int  * sendcnt, MPI_Fint  * sendtype, void  *recvbuf, int  * recvcount, MPI_Fint  * recvtype, int  * root, MPI_Fint  * comm , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_sendtype;
MPI_Datatype c_recvtype;
MPI_Comm c_comm;

c_sendtype = MPI_Type_f2c(*sendtype);
c_recvtype = MPI_Type_f2c(*recvtype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Gather( &jbuf, sendbuf, sendcnt, &c_sendtype, recvbuf, recvcount, &c_recvtype, root, &c_comm );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_gather */



/* --------------- MPI_Gatherv --------------- */

static int mpiPif_MPI_Gatherv( jmp_buf * base_jbuf, mpip_const_void_t  *sendbuf, int  * sendcnt, MPI_Datatype  * sendtype, void  *recvbuf, mpip_const_int_t  *recvcnts, mpip_const_int_t  *displs, MPI_Datatype  * recvtype, int  * root, MPI_Comm  * comm)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Gatherv( sendbuf,  * sendcnt,  * sendtype, recvbuf, recvcnts, displs,  * recvtype,  * root,  * comm);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Gatherv', ");
fprintf(nyaFp, "'arguments': {");
if(sendbuf == NULL) {
    fprintf(nyaFp, "'sendbuf': 0x0");
}
else {
    fprintf(nyaFp, "'sendbuf': %p", sendbuf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'sendcnt': %d", * sendcnt);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* sendtype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'sendtype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'sendtype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
if(recvbuf == NULL) {
    fprintf(nyaFp, "'recvbuf': 0x0");
}
else {
    fprintf(nyaFp, "'recvbuf': %p", recvbuf);
}
fprintf(nyaFp, ", ");
if(recvcnts == NULL) {
    fprintf(nyaFp, "'recvcnts': 0x0");
}
else {
    fprintf(nyaFp, "'recvcnts': %p", recvcnts);
}
fprintf(nyaFp, ", ");
if(displs == NULL) {
    fprintf(nyaFp, "'displs': 0x0");
}
else {
    fprintf(nyaFp, "'displs': %p", displs);
}
fprintf(nyaFp, ", ");
MPI_Type_get_name(* recvtype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'recvtype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'recvtype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'root': %d", * root);
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( *sendtype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*sendtype, &tsize);
messSize = (double)(tsize * *sendcnt);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Gatherv");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Gatherv, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(hndl, mpiPi_MPI_Gatherv, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Gatherv */



extern int MPI_Gatherv ( mpip_const_void_t *sendbuf, int sendcnt, MPI_Datatype sendtype, void *recvbuf, mpip_const_int_t *recvcnts, mpip_const_int_t *displs, MPI_Datatype recvtype, int root, MPI_Comm comm )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Gatherv( &jbuf, sendbuf,  & sendcnt,  & sendtype, recvbuf, recvcnts, displs,  & recvtype,  & root,  & comm );

return rc;
} /* MPI_Gatherv */


extern void F77_MPI_GATHERV(mpip_const_void_t  *sendbuf, int  * sendcnt, MPI_Fint  * sendtype, void  *recvbuf, mpip_const_int_t  *recvcnts, mpip_const_int_t  *displs, MPI_Fint  * recvtype, int  * root, MPI_Fint  * comm , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_sendtype;
MPI_Datatype c_recvtype;
MPI_Comm c_comm;

c_sendtype = MPI_Type_f2c(*sendtype);
c_recvtype = MPI_Type_f2c(*recvtype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Gatherv( &jbuf, sendbuf, sendcnt, &c_sendtype, recvbuf, recvcnts, displs, &c_recvtype, root, &c_comm );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_gatherv */



/* --------------- MPI_Get --------------- */

static int mpiPif_MPI_Get( jmp_buf * base_jbuf, void  *origin_addr, int  * origin_count, MPI_Datatype  * origin_datatype, int  * target_rank, MPI_Aint  * target_disp, int  * target_count, MPI_Datatype  * target_datatype, MPI_Win  * win)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Get( origin_addr,  * origin_count,  * origin_datatype,  * target_rank,  * target_disp,  * target_count,  * target_datatype,  * win);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Get', ");
fprintf(nyaFp, "'arguments': {");
if(origin_addr == NULL) {
    fprintf(nyaFp, "'origin_addr': 0x0");
}
else {
    fprintf(nyaFp, "'origin_addr': %p", origin_addr);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'origin_count': %d", * origin_count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* origin_datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'origin_datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'origin_datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'target_rank': %d", * target_rank);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'target_disp': %ld", * target_disp);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'target_count': %d", * target_count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* target_datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'target_datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'target_datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
MPI_Win_get_info(* win, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'win': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Get");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Get, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Get */



extern int MPI_Get ( void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Get( &jbuf, origin_addr,  & origin_count,  & origin_datatype,  & target_rank,  & target_disp,  & target_count,  & target_datatype,  & win );

return rc;
} /* MPI_Get */


extern void F77_MPI_GET(void  *origin_addr, int  * origin_count, MPI_Fint  * origin_datatype, int  * target_rank, MPI_Aint  * target_disp, int  * target_count, MPI_Fint  * target_datatype, MPI_Win  * win , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_origin_datatype;
MPI_Datatype c_target_datatype;

c_origin_datatype = MPI_Type_f2c(*origin_datatype);
c_target_datatype = MPI_Type_f2c(*target_datatype);

rc = mpiPif_MPI_Get( &jbuf, origin_addr, origin_count, &c_origin_datatype, target_rank, target_disp, target_count, &c_target_datatype, win );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_get */



/* --------------- MPI_Get_accumulate --------------- */

static int mpiPif_MPI_Get_accumulate( jmp_buf * base_jbuf, mpip_const_void_t  *origin_addr, int  * origin_count, MPI_Datatype  * origin_datatype, void  *result_addr, int  * result_count, MPI_Datatype  * result_datatype, int  * target_rank, MPI_Aint  * target_disp, int  * target_count, MPI_Datatype  * target_datatype, MPI_Op  * op, MPI_Win  * win)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Get_accumulate( origin_addr,  * origin_count,  * origin_datatype, result_addr,  * result_count,  * result_datatype,  * target_rank,  * target_disp,  * target_count,  * target_datatype,  * op,  * win);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Get_accumulate', ");
fprintf(nyaFp, "'arguments': {");
if(origin_addr == NULL) {
    fprintf(nyaFp, "'origin_addr': 0x0");
}
else {
    fprintf(nyaFp, "'origin_addr': %p", origin_addr);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'origin_count': %d", * origin_count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* origin_datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'origin_datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'origin_datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
if(result_addr == NULL) {
    fprintf(nyaFp, "'result_addr': 0x0");
}
else {
    fprintf(nyaFp, "'result_addr': %p", result_addr);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'result_count': %d", * result_count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* result_datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'result_datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'result_datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'target_rank': %d", * target_rank);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'target_disp': %ld", * target_disp);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'target_count': %d", * target_count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* target_datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'target_datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'target_datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'op': '%s'", get_op_name(* op));
fprintf(nyaFp, ", ");
MPI_Win_get_info(* win, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'win': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

PMPI_Type_size(*target_datatype, &tsize);
rmaSize = (double)(tsize * *target_count);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Get_accumulate");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Get_accumulate, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Get_accumulate */



extern int MPI_Get_accumulate ( mpip_const_void_t *origin_addr, int origin_count, MPI_Datatype origin_datatype, void *result_addr, int result_count, MPI_Datatype result_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Get_accumulate( &jbuf, origin_addr,  & origin_count,  & origin_datatype, result_addr,  & result_count,  & result_datatype,  & target_rank,  & target_disp,  & target_count,  & target_datatype,  & op,  & win );

return rc;
} /* MPI_Get_accumulate */


extern void F77_MPI_GET_ACCUMULATE(mpip_const_void_t  *origin_addr, int  * origin_count, MPI_Fint  * origin_datatype, void  *result_addr, int  * result_count, MPI_Fint  * result_datatype, int  * target_rank, MPI_Aint  * target_disp, int  * target_count, MPI_Fint  * target_datatype, MPI_Fint  * op, MPI_Win  * win , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_origin_datatype;
MPI_Datatype c_result_datatype;
MPI_Datatype c_target_datatype;
MPI_Op c_op;

c_origin_datatype = MPI_Type_f2c(*origin_datatype);
c_result_datatype = MPI_Type_f2c(*result_datatype);
c_target_datatype = MPI_Type_f2c(*target_datatype);
c_op = MPI_Op_f2c(*op);

rc = mpiPif_MPI_Get_accumulate( &jbuf, origin_addr, origin_count, &c_origin_datatype, result_addr, result_count, &c_result_datatype, target_rank, target_disp, target_count, &c_target_datatype, &c_op, win );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_get_accumulate */



/* --------------- MPI_Graph_create --------------- */

static int mpiPif_MPI_Graph_create( jmp_buf * base_jbuf, MPI_Comm  * comm_old, int  * nnodes, mpip_const_int_t  *index, mpip_const_int_t  *edges, int  * reorder, MPI_Comm  *comm_graph)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Graph_create(  * comm_old,  * nnodes, index, edges,  * reorder, comm_graph);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Graph_create', ");
fprintf(nyaFp, "'arguments': {");
MPI_Comm_rank(* comm_old, &nyaRank);
fprintf(nyaFp, "'comm_old': %d", nyaRank);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'nnodes': %d", * nnodes);
fprintf(nyaFp, ", ");
if(index == NULL) {
    fprintf(nyaFp, "'index': 0x0");
}
else {
    fprintf(nyaFp, "'index': %p", index);
}
fprintf(nyaFp, ", ");
if(edges == NULL) {
    fprintf(nyaFp, "'edges': 0x0");
}
else {
    fprintf(nyaFp, "'edges': %p", edges);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'reorder': %d", * reorder);
fprintf(nyaFp, ", ");
if(comm_graph == NULL) {
    fprintf(nyaFp, "'comm_graph': 0x0");
}
else {
    fprintf(nyaFp, "'comm_graph': %p", comm_graph);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Graph_create");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Graph_create, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Graph_create */



extern int MPI_Graph_create ( MPI_Comm comm_old, int nnodes, mpip_const_int_t *index, mpip_const_int_t *edges, int reorder, MPI_Comm *comm_graph )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Graph_create( &jbuf,  & comm_old,  & nnodes, index, edges,  & reorder, comm_graph );

return rc;
} /* MPI_Graph_create */


extern void F77_MPI_GRAPH_CREATE(MPI_Fint  * comm_old, int  * nnodes, mpip_const_int_t  *index, mpip_const_int_t  *edges, int  * reorder, MPI_Fint  *comm_graph , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm_old;
MPI_Comm c_comm_graph;

c_comm_old = MPI_Comm_f2c(*comm_old);

rc = mpiPif_MPI_Graph_create( &jbuf, &c_comm_old, nnodes, index, edges, reorder, &c_comm_graph );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*comm_graph = MPI_Comm_c2f(c_comm_graph);
}
return;
} /* mpi_graph_create */



/* --------------- MPI_Graph_get --------------- */

static int mpiPif_MPI_Graph_get( jmp_buf * base_jbuf, MPI_Comm  * comm, int  * maxindex, int  * maxedges, int  *index, int  *edges)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Graph_get(  * comm,  * maxindex,  * maxedges, index, edges);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Graph_get', ");
fprintf(nyaFp, "'arguments': {");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'maxindex': %d", * maxindex);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'maxedges': %d", * maxedges);
fprintf(nyaFp, ", ");
if(index == NULL) {
    fprintf(nyaFp, "'index': 0x0");
}
else {
    fprintf(nyaFp, "'index': %p", index);
}
fprintf(nyaFp, ", ");
if(edges == NULL) {
    fprintf(nyaFp, "'edges': 0x0");
}
else {
    fprintf(nyaFp, "'edges': %p", edges);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Graph_get");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Graph_get, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Graph_get */



extern int MPI_Graph_get ( MPI_Comm comm, int maxindex, int maxedges, int *index, int *edges )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Graph_get( &jbuf,  & comm,  & maxindex,  & maxedges, index, edges );

return rc;
} /* MPI_Graph_get */


extern void F77_MPI_GRAPH_GET(MPI_Fint  * comm, int  * maxindex, int  * maxedges, int  *index, int  *edges , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Graph_get( &jbuf, &c_comm, maxindex, maxedges, index, edges );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_graph_get */



/* --------------- MPI_Graph_map --------------- */

static int mpiPif_MPI_Graph_map( jmp_buf * base_jbuf, MPI_Comm  * comm_old, int  * nnodes, mpip_const_int_t  *index, mpip_const_int_t  *edges, int  *newrank)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Graph_map(  * comm_old,  * nnodes, index, edges, newrank);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Graph_map', ");
fprintf(nyaFp, "'arguments': {");
MPI_Comm_rank(* comm_old, &nyaRank);
fprintf(nyaFp, "'comm_old': %d", nyaRank);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'nnodes': %d", * nnodes);
fprintf(nyaFp, ", ");
if(index == NULL) {
    fprintf(nyaFp, "'index': 0x0");
}
else {
    fprintf(nyaFp, "'index': %p", index);
}
fprintf(nyaFp, ", ");
if(edges == NULL) {
    fprintf(nyaFp, "'edges': 0x0");
}
else {
    fprintf(nyaFp, "'edges': %p", edges);
}
fprintf(nyaFp, ", ");
if(newrank == NULL) {
    fprintf(nyaFp, "'newrank': 0x0");
}
else {
    fprintf(nyaFp, "'newrank': %p", newrank);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Graph_map");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Graph_map, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Graph_map */



extern int MPI_Graph_map ( MPI_Comm comm_old, int nnodes, mpip_const_int_t *index, mpip_const_int_t *edges, int *newrank )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Graph_map( &jbuf,  & comm_old,  & nnodes, index, edges, newrank );

return rc;
} /* MPI_Graph_map */


extern void F77_MPI_GRAPH_MAP(MPI_Fint  * comm_old, int  * nnodes, mpip_const_int_t  *index, mpip_const_int_t  *edges, int  *newrank , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm_old;

c_comm_old = MPI_Comm_f2c(*comm_old);

rc = mpiPif_MPI_Graph_map( &jbuf, &c_comm_old, nnodes, index, edges, newrank );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_graph_map */



/* --------------- MPI_Graph_neighbors --------------- */

static int mpiPif_MPI_Graph_neighbors( jmp_buf * base_jbuf, MPI_Comm  * comm, int  * rank, int  * maxneighbors, int  *neighbors)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Graph_neighbors(  * comm,  * rank,  * maxneighbors, neighbors);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Graph_neighbors', ");
fprintf(nyaFp, "'arguments': {");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'rank': %d", * rank);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'maxneighbors': %d", * maxneighbors);
fprintf(nyaFp, ", ");
if(neighbors == NULL) {
    fprintf(nyaFp, "'neighbors': 0x0");
}
else {
    fprintf(nyaFp, "'neighbors': %p", neighbors);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Graph_neighbors");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Graph_neighbors, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Graph_neighbors */



extern int MPI_Graph_neighbors ( MPI_Comm comm, int rank, int maxneighbors, int *neighbors )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Graph_neighbors( &jbuf,  & comm,  & rank,  & maxneighbors, neighbors );

return rc;
} /* MPI_Graph_neighbors */


extern void F77_MPI_GRAPH_NEIGHBORS(MPI_Fint  * comm, int  * rank, int  * maxneighbors, int  *neighbors , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Graph_neighbors( &jbuf, &c_comm, rank, maxneighbors, neighbors );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_graph_neighbors */



/* --------------- MPI_Graph_neighbors_count --------------- */

static int mpiPif_MPI_Graph_neighbors_count( jmp_buf * base_jbuf, MPI_Comm  * comm, int  * rank, int  *nneighbors)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Graph_neighbors_count(  * comm,  * rank, nneighbors);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Graph_neighbors_count', ");
fprintf(nyaFp, "'arguments': {");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'rank': %d", * rank);
fprintf(nyaFp, ", ");
if(nneighbors == NULL) {
    fprintf(nyaFp, "'nneighbors': 0x0");
}
else {
    fprintf(nyaFp, "'nneighbors': %p", nneighbors);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Graph_neighbors_count");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Graph_neighbors_count, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Graph_neighbors_count */



extern int MPI_Graph_neighbors_count ( MPI_Comm comm, int rank, int *nneighbors )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Graph_neighbors_count( &jbuf,  & comm,  & rank, nneighbors );

return rc;
} /* MPI_Graph_neighbors_count */


extern void F77_MPI_GRAPH_NEIGHBORS_COUNT(MPI_Fint  * comm, int  * rank, int  *nneighbors , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Graph_neighbors_count( &jbuf, &c_comm, rank, nneighbors );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_graph_neighbors_count */



/* --------------- MPI_Graphdims_get --------------- */

static int mpiPif_MPI_Graphdims_get( jmp_buf * base_jbuf, MPI_Comm  * comm, int  *nnodes, int  *nedges)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Graphdims_get(  * comm, nnodes, nedges);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Graphdims_get', ");
fprintf(nyaFp, "'arguments': {");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(nnodes == NULL) {
    fprintf(nyaFp, "'nnodes': 0x0");
}
else {
    fprintf(nyaFp, "'nnodes': %p", nnodes);
}
fprintf(nyaFp, ", ");
if(nedges == NULL) {
    fprintf(nyaFp, "'nedges': 0x0");
}
else {
    fprintf(nyaFp, "'nedges': %p", nedges);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Graphdims_get");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Graphdims_get, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Graphdims_get */



extern int MPI_Graphdims_get ( MPI_Comm comm, int *nnodes, int *nedges )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Graphdims_get( &jbuf,  & comm, nnodes, nedges );

return rc;
} /* MPI_Graphdims_get */


extern void F77_MPI_GRAPHDIMS_GET(MPI_Fint  * comm, int  *nnodes, int  *nedges , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Graphdims_get( &jbuf, &c_comm, nnodes, nedges );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_graphdims_get */



/* --------------- MPI_Group_compare --------------- */

static int mpiPif_MPI_Group_compare( jmp_buf * base_jbuf, MPI_Group  * group1, MPI_Group  * group2, int  *result)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Group_compare(  * group1,  * group2, result);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Group_compare', ");
fprintf(nyaFp, "'arguments': {");
MPI_Group_size(* group1, &nyaGroupSize);MPI_Group_rank(* group1, &nyaGroupRank);fprintf(nyaFp, "'group1': {");
fprintf(nyaFp, "'group_size': %d, ", nyaGroupSize);
fprintf(nyaFp, "'group_rank': %d", nyaGroupRank);
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
MPI_Group_size(* group2, &nyaGroupSize);MPI_Group_rank(* group2, &nyaGroupRank);fprintf(nyaFp, "'group2': {");
fprintf(nyaFp, "'group_size': %d, ", nyaGroupSize);
fprintf(nyaFp, "'group_rank': %d", nyaGroupRank);
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
if(result == NULL) {
    fprintf(nyaFp, "'result': 0x0");
}
else {
    fprintf(nyaFp, "'result': %p", result);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Group_compare");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Group_compare, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Group_compare */



extern int MPI_Group_compare ( MPI_Group group1, MPI_Group group2, int *result )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Group_compare( &jbuf,  & group1,  & group2, result );

return rc;
} /* MPI_Group_compare */


extern void F77_MPI_GROUP_COMPARE(MPI_Fint  * group1, MPI_Fint  * group2, int  *result , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Group c_group1;
MPI_Group c_group2;

c_group1 = MPI_Group_f2c(*group1);
c_group2 = MPI_Group_f2c(*group2);

rc = mpiPif_MPI_Group_compare( &jbuf, &c_group1, &c_group2, result );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_group_compare */



/* --------------- MPI_Group_difference --------------- */

static int mpiPif_MPI_Group_difference( jmp_buf * base_jbuf, MPI_Group  * group1, MPI_Group  * group2, MPI_Group  *group_out)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Group_difference(  * group1,  * group2, group_out);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Group_difference', ");
fprintf(nyaFp, "'arguments': {");
MPI_Group_size(* group1, &nyaGroupSize);MPI_Group_rank(* group1, &nyaGroupRank);fprintf(nyaFp, "'group1': {");
fprintf(nyaFp, "'group_size': %d, ", nyaGroupSize);
fprintf(nyaFp, "'group_rank': %d", nyaGroupRank);
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
MPI_Group_size(* group2, &nyaGroupSize);MPI_Group_rank(* group2, &nyaGroupRank);fprintf(nyaFp, "'group2': {");
fprintf(nyaFp, "'group_size': %d, ", nyaGroupSize);
fprintf(nyaFp, "'group_rank': %d", nyaGroupRank);
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
if(group_out == NULL) {
    fprintf(nyaFp, "'group_out': 0x0");
}
else {
    fprintf(nyaFp, "'group_out': %p", group_out);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Group_difference");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Group_difference, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Group_difference */



extern int MPI_Group_difference ( MPI_Group group1, MPI_Group group2, MPI_Group *group_out )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Group_difference( &jbuf,  & group1,  & group2, group_out );

return rc;
} /* MPI_Group_difference */


extern void F77_MPI_GROUP_DIFFERENCE(MPI_Fint  * group1, MPI_Fint  * group2, MPI_Fint  *group_out , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Group c_group1;
MPI_Group c_group2;
MPI_Group c_group_out;

c_group1 = MPI_Group_f2c(*group1);
c_group2 = MPI_Group_f2c(*group2);

rc = mpiPif_MPI_Group_difference( &jbuf, &c_group1, &c_group2, &c_group_out );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*group_out = MPI_Group_c2f(c_group_out);
}
return;
} /* mpi_group_difference */



/* --------------- MPI_Group_excl --------------- */

static int mpiPif_MPI_Group_excl( jmp_buf * base_jbuf, MPI_Group  * group, int  * n, mpip_const_int_t  *ranks, MPI_Group  *newgroup)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Group_excl(  * group,  * n, ranks, newgroup);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Group_excl', ");
fprintf(nyaFp, "'arguments': {");
MPI_Group_size(* group, &nyaGroupSize);MPI_Group_rank(* group, &nyaGroupRank);fprintf(nyaFp, "'group': {");
fprintf(nyaFp, "'group_size': %d, ", nyaGroupSize);
fprintf(nyaFp, "'group_rank': %d", nyaGroupRank);
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'n': %d", * n);
fprintf(nyaFp, ", ");
if(ranks == NULL) {
    fprintf(nyaFp, "'ranks': 0x0");
}
else {
    fprintf(nyaFp, "'ranks': %p", ranks);
}
fprintf(nyaFp, ", ");
if(newgroup == NULL) {
    fprintf(nyaFp, "'newgroup': 0x0");
}
else {
    fprintf(nyaFp, "'newgroup': %p", newgroup);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Group_excl");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Group_excl, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Group_excl */



extern int MPI_Group_excl ( MPI_Group group, int n, mpip_const_int_t *ranks, MPI_Group *newgroup )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Group_excl( &jbuf,  & group,  & n, ranks, newgroup );

return rc;
} /* MPI_Group_excl */


extern void F77_MPI_GROUP_EXCL(MPI_Fint  * group, int  * n, mpip_const_int_t  *ranks, MPI_Fint  *newgroup , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Group c_group;
MPI_Group c_newgroup;

c_group = MPI_Group_f2c(*group);

rc = mpiPif_MPI_Group_excl( &jbuf, &c_group, n, ranks, &c_newgroup );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*newgroup = MPI_Group_c2f(c_newgroup);
}
return;
} /* mpi_group_excl */



/* --------------- MPI_Group_free --------------- */

static int mpiPif_MPI_Group_free( jmp_buf * base_jbuf, MPI_Group  *group)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Group_free( group);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Group_free', ");
fprintf(nyaFp, "'arguments': {");
if(group == NULL) {
    fprintf(nyaFp, "'group': 0x0");
}
else {
    fprintf(nyaFp, "'group': %p", group);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Group_free");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Group_free, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Group_free */



extern int MPI_Group_free ( MPI_Group *group )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Group_free( &jbuf, group );

return rc;
} /* MPI_Group_free */


extern void F77_MPI_GROUP_FREE(MPI_Fint  *group , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Group c_group;

c_group = MPI_Group_f2c(*group);

rc = mpiPif_MPI_Group_free( &jbuf, &c_group );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*group = MPI_Group_c2f(c_group);
}
return;
} /* mpi_group_free */



/* --------------- MPI_Group_incl --------------- */

static int mpiPif_MPI_Group_incl( jmp_buf * base_jbuf, MPI_Group  * group, int  * n, mpip_const_int_t  *ranks, MPI_Group  *group_out)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Group_incl(  * group,  * n, ranks, group_out);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Group_incl', ");
fprintf(nyaFp, "'arguments': {");
MPI_Group_size(* group, &nyaGroupSize);MPI_Group_rank(* group, &nyaGroupRank);fprintf(nyaFp, "'group': {");
fprintf(nyaFp, "'group_size': %d, ", nyaGroupSize);
fprintf(nyaFp, "'group_rank': %d", nyaGroupRank);
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'n': %d", * n);
fprintf(nyaFp, ", ");
if(ranks == NULL) {
    fprintf(nyaFp, "'ranks': 0x0");
}
else {
    fprintf(nyaFp, "'ranks': %p", ranks);
}
fprintf(nyaFp, ", ");
if(group_out == NULL) {
    fprintf(nyaFp, "'group_out': 0x0");
}
else {
    fprintf(nyaFp, "'group_out': %p", group_out);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Group_incl");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Group_incl, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Group_incl */



extern int MPI_Group_incl ( MPI_Group group, int n, mpip_const_int_t *ranks, MPI_Group *group_out )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Group_incl( &jbuf,  & group,  & n, ranks, group_out );

return rc;
} /* MPI_Group_incl */


extern void F77_MPI_GROUP_INCL(MPI_Fint  * group, int  * n, mpip_const_int_t  *ranks, MPI_Fint  *group_out , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Group c_group;
MPI_Group c_group_out;

c_group = MPI_Group_f2c(*group);

rc = mpiPif_MPI_Group_incl( &jbuf, &c_group, n, ranks, &c_group_out );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*group_out = MPI_Group_c2f(c_group_out);
}
return;
} /* mpi_group_incl */



/* --------------- MPI_Group_intersection --------------- */

static int mpiPif_MPI_Group_intersection( jmp_buf * base_jbuf, MPI_Group  * group1, MPI_Group  * group2, MPI_Group  *group_out)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Group_intersection(  * group1,  * group2, group_out);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Group_intersection', ");
fprintf(nyaFp, "'arguments': {");
MPI_Group_size(* group1, &nyaGroupSize);MPI_Group_rank(* group1, &nyaGroupRank);fprintf(nyaFp, "'group1': {");
fprintf(nyaFp, "'group_size': %d, ", nyaGroupSize);
fprintf(nyaFp, "'group_rank': %d", nyaGroupRank);
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
MPI_Group_size(* group2, &nyaGroupSize);MPI_Group_rank(* group2, &nyaGroupRank);fprintf(nyaFp, "'group2': {");
fprintf(nyaFp, "'group_size': %d, ", nyaGroupSize);
fprintf(nyaFp, "'group_rank': %d", nyaGroupRank);
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
if(group_out == NULL) {
    fprintf(nyaFp, "'group_out': 0x0");
}
else {
    fprintf(nyaFp, "'group_out': %p", group_out);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Group_intersection");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Group_intersection, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Group_intersection */



extern int MPI_Group_intersection ( MPI_Group group1, MPI_Group group2, MPI_Group *group_out )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Group_intersection( &jbuf,  & group1,  & group2, group_out );

return rc;
} /* MPI_Group_intersection */


extern void F77_MPI_GROUP_INTERSECTION(MPI_Fint  * group1, MPI_Fint  * group2, MPI_Fint  *group_out , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Group c_group1;
MPI_Group c_group2;
MPI_Group c_group_out;

c_group1 = MPI_Group_f2c(*group1);
c_group2 = MPI_Group_f2c(*group2);

rc = mpiPif_MPI_Group_intersection( &jbuf, &c_group1, &c_group2, &c_group_out );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*group_out = MPI_Group_c2f(c_group_out);
}
return;
} /* mpi_group_intersection */



/* --------------- MPI_Group_translate_ranks --------------- */

static int mpiPif_MPI_Group_translate_ranks( jmp_buf * base_jbuf, MPI_Group  * group_a, int  * n, mpip_const_int_t  *ranks_a, MPI_Group  * group_b, int  *ranks_b)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Group_translate_ranks(  * group_a,  * n, ranks_a,  * group_b, ranks_b);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Group_translate_ranks', ");
fprintf(nyaFp, "'arguments': {");
MPI_Group_size(* group_a, &nyaGroupSize);MPI_Group_rank(* group_a, &nyaGroupRank);fprintf(nyaFp, "'group_a': {");
fprintf(nyaFp, "'group_size': %d, ", nyaGroupSize);
fprintf(nyaFp, "'group_rank': %d", nyaGroupRank);
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'n': %d", * n);
fprintf(nyaFp, ", ");
if(ranks_a == NULL) {
    fprintf(nyaFp, "'ranks_a': 0x0");
}
else {
    fprintf(nyaFp, "'ranks_a': %p", ranks_a);
}
fprintf(nyaFp, ", ");
MPI_Group_size(* group_b, &nyaGroupSize);MPI_Group_rank(* group_b, &nyaGroupRank);fprintf(nyaFp, "'group_b': {");
fprintf(nyaFp, "'group_size': %d, ", nyaGroupSize);
fprintf(nyaFp, "'group_rank': %d", nyaGroupRank);
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
if(ranks_b == NULL) {
    fprintf(nyaFp, "'ranks_b': 0x0");
}
else {
    fprintf(nyaFp, "'ranks_b': %p", ranks_b);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Group_translate_ranks");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Group_translate_ranks, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Group_translate_ranks */



extern int MPI_Group_translate_ranks ( MPI_Group group_a, int n, mpip_const_int_t *ranks_a, MPI_Group group_b, int *ranks_b )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Group_translate_ranks( &jbuf,  & group_a,  & n, ranks_a,  & group_b, ranks_b );

return rc;
} /* MPI_Group_translate_ranks */


extern void F77_MPI_GROUP_TRANSLATE_RANKS(MPI_Fint  * group_a, int  * n, mpip_const_int_t  *ranks_a, MPI_Fint  * group_b, int  *ranks_b , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Group c_group_a;
MPI_Group c_group_b;

c_group_a = MPI_Group_f2c(*group_a);
c_group_b = MPI_Group_f2c(*group_b);

rc = mpiPif_MPI_Group_translate_ranks( &jbuf, &c_group_a, n, ranks_a, &c_group_b, ranks_b );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_group_translate_ranks */



/* --------------- MPI_Group_union --------------- */

static int mpiPif_MPI_Group_union( jmp_buf * base_jbuf, MPI_Group  * group1, MPI_Group  * group2, MPI_Group  *group_out)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Group_union(  * group1,  * group2, group_out);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Group_union', ");
fprintf(nyaFp, "'arguments': {");
MPI_Group_size(* group1, &nyaGroupSize);MPI_Group_rank(* group1, &nyaGroupRank);fprintf(nyaFp, "'group1': {");
fprintf(nyaFp, "'group_size': %d, ", nyaGroupSize);
fprintf(nyaFp, "'group_rank': %d", nyaGroupRank);
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
MPI_Group_size(* group2, &nyaGroupSize);MPI_Group_rank(* group2, &nyaGroupRank);fprintf(nyaFp, "'group2': {");
fprintf(nyaFp, "'group_size': %d, ", nyaGroupSize);
fprintf(nyaFp, "'group_rank': %d", nyaGroupRank);
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
if(group_out == NULL) {
    fprintf(nyaFp, "'group_out': 0x0");
}
else {
    fprintf(nyaFp, "'group_out': %p", group_out);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Group_union");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Group_union, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Group_union */



extern int MPI_Group_union ( MPI_Group group1, MPI_Group group2, MPI_Group *group_out )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Group_union( &jbuf,  & group1,  & group2, group_out );

return rc;
} /* MPI_Group_union */


extern void F77_MPI_GROUP_UNION(MPI_Fint  * group1, MPI_Fint  * group2, MPI_Fint  *group_out , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Group c_group1;
MPI_Group c_group2;
MPI_Group c_group_out;

c_group1 = MPI_Group_f2c(*group1);
c_group2 = MPI_Group_f2c(*group2);

rc = mpiPif_MPI_Group_union( &jbuf, &c_group1, &c_group2, &c_group_out );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*group_out = MPI_Group_c2f(c_group_out);
}
return;
} /* mpi_group_union */



/* --------------- MPI_Iallgather --------------- */

static int mpiPif_MPI_Iallgather( jmp_buf * base_jbuf, const void  *sendbuf, int  * sendcount, MPI_Datatype  * sendtype, void  *recvbuf, int  * recvcount, MPI_Datatype  * recvtype, MPI_Comm  * comm, MPI_Request  *request)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Iallgather( sendbuf,  * sendcount,  * sendtype, recvbuf,  * recvcount,  * recvtype,  * comm, request);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Iallgather', ");
fprintf(nyaFp, "'arguments': {");
if(sendbuf == NULL) {
    fprintf(nyaFp, "'sendbuf': 0x0");
}
else {
    fprintf(nyaFp, "'sendbuf': %p", sendbuf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'sendcount': %d", * sendcount);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* sendtype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'sendtype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'sendtype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
if(recvbuf == NULL) {
    fprintf(nyaFp, "'recvbuf': 0x0");
}
else {
    fprintf(nyaFp, "'recvbuf': %p", recvbuf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'recvcount': %d", * recvcount);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* recvtype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'recvtype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'recvtype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(request == NULL) {
    fprintf(nyaFp, "'request': 0x0");
}
else {
    fprintf(nyaFp, "'request': %p", request);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( *sendtype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*sendtype, &tsize);
messSize = (double)(tsize * *sendcount);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Iallgather");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Iallgather, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(hndl, mpiPi_MPI_Iallgather, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Iallgather */



extern int MPI_Iallgather ( const void* sendbuf, int sendcount, MPI_Datatype sendtype, void* recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request ) 
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Iallgather( &jbuf, sendbuf,  & sendcount,  & sendtype, recvbuf,  & recvcount,  & recvtype,  & comm, request );

return rc;
} /* MPI_Iallgather */


extern void F77_MPI_IALLGATHER(const void  *sendbuf, int  * sendcount, MPI_Fint  * sendtype, void  *recvbuf, int  * recvcount, MPI_Fint  * recvtype, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_sendtype;
MPI_Datatype c_recvtype;
MPI_Comm c_comm;
MPI_Request c_request;

c_sendtype = MPI_Type_f2c(*sendtype);
c_recvtype = MPI_Type_f2c(*recvtype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Iallgather( &jbuf, sendbuf, sendcount, &c_sendtype, recvbuf, recvcount, &c_recvtype, &c_comm, &c_request );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_iallgather */



/* --------------- MPI_Iallgatherv --------------- */

static int mpiPif_MPI_Iallgatherv( jmp_buf * base_jbuf, const void  *sendbuf, int  * sendcount, MPI_Datatype  * sendtype, void  *recvbuf, mpip_const_int_t recvcounts[], mpip_const_int_t displs[], MPI_Datatype  * recvtype, MPI_Comm  * comm, MPI_Request  *request)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Iallgatherv( sendbuf,  * sendcount,  * sendtype, recvbuf, recvcounts, displs,  * recvtype,  * comm, request);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Iallgatherv', ");
fprintf(nyaFp, "'arguments': {");
if(sendbuf == NULL) {
    fprintf(nyaFp, "'sendbuf': 0x0");
}
else {
    fprintf(nyaFp, "'sendbuf': %p", sendbuf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'sendcount': %d", * sendcount);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* sendtype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'sendtype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'sendtype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
if(recvbuf == NULL) {
    fprintf(nyaFp, "'recvbuf': 0x0");
}
else {
    fprintf(nyaFp, "'recvbuf': %p", recvbuf);
}
fprintf(nyaFp, ", ");
if(recvcounts == NULL) {
    fprintf(nyaFp, "'recvcounts': 0x0");
}
else {
    fprintf(nyaFp, "'recvcounts': %p", recvcounts);
}
fprintf(nyaFp, ", ");
if(displs == NULL) {
    fprintf(nyaFp, "'displs': 0x0");
}
else {
    fprintf(nyaFp, "'displs': %p", displs);
}
fprintf(nyaFp, ", ");
MPI_Type_get_name(* recvtype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'recvtype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'recvtype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(request == NULL) {
    fprintf(nyaFp, "'request': 0x0");
}
else {
    fprintf(nyaFp, "'request': %p", request);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( *sendtype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*sendtype, &tsize);
messSize = (double)(tsize * *sendcount);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Iallgatherv");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Iallgatherv, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(hndl, mpiPi_MPI_Iallgatherv, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Iallgatherv */



extern int MPI_Iallgatherv ( const void* sendbuf, int sendcount, MPI_Datatype sendtype, void* recvbuf, mpip_const_int_t recvcounts[], mpip_const_int_t displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request* request )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Iallgatherv( &jbuf, sendbuf,  & sendcount,  & sendtype, recvbuf, recvcounts, displs,  & recvtype,  & comm, request );

return rc;
} /* MPI_Iallgatherv */


extern void F77_MPI_IALLGATHERV(const void  *sendbuf, int  * sendcount, MPI_Fint  * sendtype, void  *recvbuf, mpip_const_int_t recvcounts[], mpip_const_int_t displs[], MPI_Fint  * recvtype, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_sendtype;
MPI_Datatype c_recvtype;
MPI_Comm c_comm;
MPI_Request c_request;

c_sendtype = MPI_Type_f2c(*sendtype);
c_recvtype = MPI_Type_f2c(*recvtype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Iallgatherv( &jbuf, sendbuf, sendcount, &c_sendtype, recvbuf, recvcounts, displs, &c_recvtype, &c_comm, &c_request );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_iallgatherv */



/* --------------- MPI_Iallreduce --------------- */

static int mpiPif_MPI_Iallreduce( jmp_buf * base_jbuf, const void  *sendbuf, void  *recvbuf, int  * count, MPI_Datatype  * datatype, MPI_Op  * op, MPI_Comm  * comm, MPI_Request  *request)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Iallreduce( sendbuf, recvbuf,  * count,  * datatype,  * op,  * comm, request);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Iallreduce', ");
fprintf(nyaFp, "'arguments': {");
if(sendbuf == NULL) {
    fprintf(nyaFp, "'sendbuf': 0x0");
}
else {
    fprintf(nyaFp, "'sendbuf': %p", sendbuf);
}
fprintf(nyaFp, ", ");
if(recvbuf == NULL) {
    fprintf(nyaFp, "'recvbuf': 0x0");
}
else {
    fprintf(nyaFp, "'recvbuf': %p", recvbuf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'count': %d", * count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'op': '%s'", get_op_name(* op));
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(request == NULL) {
    fprintf(nyaFp, "'request': 0x0");
}
else {
    fprintf(nyaFp, "'request': %p", request);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( *datatype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*datatype, &tsize);
messSize = (double)(tsize * *count);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Iallreduce");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Iallreduce, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(hndl, mpiPi_MPI_Iallreduce, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Iallreduce */



extern int MPI_Iallreduce ( const void* sendbuf, void* recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request )  
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Iallreduce( &jbuf, sendbuf, recvbuf,  & count,  & datatype,  & op,  & comm, request );

return rc;
} /* MPI_Iallreduce */


extern void F77_MPI_IALLREDUCE(const void  *sendbuf, void  *recvbuf, int  * count, MPI_Fint  * datatype, MPI_Fint  * op, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Op c_op;
MPI_Comm c_comm;
MPI_Request c_request;

c_datatype = MPI_Type_f2c(*datatype);
c_op = MPI_Op_f2c(*op);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Iallreduce( &jbuf, sendbuf, recvbuf, count, &c_datatype, &c_op, &c_comm, &c_request );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_iallreduce */



/* --------------- MPI_Ialltoall --------------- */

static int mpiPif_MPI_Ialltoall( jmp_buf * base_jbuf, const void  *sendbuf, int  * sendcount, MPI_Datatype  * sendtype, void  *recvbuf, int  * recvcount, MPI_Datatype  * recvtype, MPI_Comm  * comm, MPI_Request  *request)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Ialltoall( sendbuf,  * sendcount,  * sendtype, recvbuf,  * recvcount,  * recvtype,  * comm, request);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Ialltoall', ");
fprintf(nyaFp, "'arguments': {");
if(sendbuf == NULL) {
    fprintf(nyaFp, "'sendbuf': 0x0");
}
else {
    fprintf(nyaFp, "'sendbuf': %p", sendbuf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'sendcount': %d", * sendcount);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* sendtype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'sendtype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'sendtype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
if(recvbuf == NULL) {
    fprintf(nyaFp, "'recvbuf': 0x0");
}
else {
    fprintf(nyaFp, "'recvbuf': %p", recvbuf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'recvcount': %d", * recvcount);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* recvtype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'recvtype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'recvtype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(request == NULL) {
    fprintf(nyaFp, "'request': 0x0");
}
else {
    fprintf(nyaFp, "'request': %p", request);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( *sendtype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*sendtype, &tsize);
messSize = (double)(tsize * *sendcount);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Ialltoall");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Ialltoall, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(hndl, mpiPi_MPI_Ialltoall, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Ialltoall */



extern int MPI_Ialltoall ( const void* sendbuf, int sendcount, MPI_Datatype sendtype, void* recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request )  
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Ialltoall( &jbuf, sendbuf,  & sendcount,  & sendtype, recvbuf,  & recvcount,  & recvtype,  & comm, request );

return rc;
} /* MPI_Ialltoall */


extern void F77_MPI_IALLTOALL(const void  *sendbuf, int  * sendcount, MPI_Fint  * sendtype, void  *recvbuf, int  * recvcount, MPI_Fint  * recvtype, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_sendtype;
MPI_Datatype c_recvtype;
MPI_Comm c_comm;
MPI_Request c_request;

c_sendtype = MPI_Type_f2c(*sendtype);
c_recvtype = MPI_Type_f2c(*recvtype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Ialltoall( &jbuf, sendbuf, sendcount, &c_sendtype, recvbuf, recvcount, &c_recvtype, &c_comm, &c_request );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_ialltoall */



/* --------------- MPI_Ialltoallv --------------- */

static int mpiPif_MPI_Ialltoallv( jmp_buf * base_jbuf, const void  *sendbuf, mpip_const_int_t sendcounts[], mpip_const_int_t sdispls[], MPI_Datatype  * sendtype, void  *recvbuf, mpip_const_int_t recvcounts[], mpip_const_int_t rdispls[], MPI_Datatype  * recvtype, MPI_Comm  * comm, MPI_Request  *request)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Ialltoallv( sendbuf, sendcounts, sdispls,  * sendtype, recvbuf, recvcounts, rdispls,  * recvtype,  * comm, request);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Ialltoallv', ");
fprintf(nyaFp, "'arguments': {");
if(sendbuf == NULL) {
    fprintf(nyaFp, "'sendbuf': 0x0");
}
else {
    fprintf(nyaFp, "'sendbuf': %p", sendbuf);
}
fprintf(nyaFp, ", ");
if(sendcounts == NULL) {
    fprintf(nyaFp, "'sendcounts': 0x0");
}
else {
    fprintf(nyaFp, "'sendcounts': %p", sendcounts);
}
fprintf(nyaFp, ", ");
if(sdispls == NULL) {
    fprintf(nyaFp, "'sdispls': 0x0");
}
else {
    fprintf(nyaFp, "'sdispls': %p", sdispls);
}
fprintf(nyaFp, ", ");
MPI_Type_get_name(* sendtype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'sendtype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'sendtype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
if(recvbuf == NULL) {
    fprintf(nyaFp, "'recvbuf': 0x0");
}
else {
    fprintf(nyaFp, "'recvbuf': %p", recvbuf);
}
fprintf(nyaFp, ", ");
if(recvcounts == NULL) {
    fprintf(nyaFp, "'recvcounts': 0x0");
}
else {
    fprintf(nyaFp, "'recvcounts': %p", recvcounts);
}
fprintf(nyaFp, ", ");
if(rdispls == NULL) {
    fprintf(nyaFp, "'rdispls': 0x0");
}
else {
    fprintf(nyaFp, "'rdispls': %p", rdispls);
}
fprintf(nyaFp, ", ");
MPI_Type_get_name(* recvtype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'recvtype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'recvtype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(request == NULL) {
    fprintf(nyaFp, "'request': 0x0");
}
else {
    fprintf(nyaFp, "'request': %p", request);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( *sendtype != MPI_DATATYPE_NULL ) { 
  int loc_comm_size, i;
  int loc_sent = 0;

  PMPI_Comm_size(*comm, &loc_comm_size);
  PMPI_Type_size(*sendtype, &tsize);
  for ( i = 0; i<loc_comm_size; i++) 
    loc_sent += sendcounts[i];
  messSize = (double)(tsize * loc_sent);
}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Ialltoallv");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Ialltoallv, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(hndl, mpiPi_MPI_Ialltoallv, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Ialltoallv */



extern int MPI_Ialltoallv ( const void* sendbuf, mpip_const_int_t sendcounts[], mpip_const_int_t sdispls[], MPI_Datatype sendtype, void* recvbuf, mpip_const_int_t recvcounts[], mpip_const_int_t rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Ialltoallv( &jbuf, sendbuf, sendcounts, sdispls,  & sendtype, recvbuf, recvcounts, rdispls,  & recvtype,  & comm, request );

return rc;
} /* MPI_Ialltoallv */


extern void F77_MPI_IALLTOALLV(const void  *sendbuf, mpip_const_int_t sendcounts[], mpip_const_int_t sdispls[], MPI_Fint  * sendtype, void  *recvbuf, mpip_const_int_t recvcounts[], mpip_const_int_t rdispls[], MPI_Fint  * recvtype, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_sendtype;
MPI_Datatype c_recvtype;
MPI_Comm c_comm;
MPI_Request c_request;

c_sendtype = MPI_Type_f2c(*sendtype);
c_recvtype = MPI_Type_f2c(*recvtype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Ialltoallv( &jbuf, sendbuf, sendcounts, sdispls, &c_sendtype, recvbuf, recvcounts, rdispls, &c_recvtype, &c_comm, &c_request );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_ialltoallv */



/* --------------- MPI_Ialltoallw --------------- */

static int mpiPif_MPI_Ialltoallw( jmp_buf * base_jbuf, const void  *sendbuf, mpip_const_int_t sendcounts[], mpip_const_int_t sdispls[], mpip_const_datatype_t sendtypes[], void  *recvbuf, mpip_const_int_t recvcounts[], mpip_const_int_t rdispls[], mpip_const_datatype_t recvtypes[], MPI_Comm  * comm, MPI_Request  *request)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Ialltoallw( sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes,  * comm, request);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Ialltoallw', ");
fprintf(nyaFp, "'arguments': {");
if(sendbuf == NULL) {
    fprintf(nyaFp, "'sendbuf': 0x0");
}
else {
    fprintf(nyaFp, "'sendbuf': %p", sendbuf);
}
fprintf(nyaFp, ", ");
if(sendcounts == NULL) {
    fprintf(nyaFp, "'sendcounts': 0x0");
}
else {
    fprintf(nyaFp, "'sendcounts': %p", sendcounts);
}
fprintf(nyaFp, ", ");
if(sdispls == NULL) {
    fprintf(nyaFp, "'sdispls': 0x0");
}
else {
    fprintf(nyaFp, "'sdispls': %p", sdispls);
}
fprintf(nyaFp, ", ");
if(sendtypes == NULL) {
    fprintf(nyaFp, "'sendtypes': 0x0");
}
else {
    fprintf(nyaFp, "'sendtypes': %p", sendtypes);
}
fprintf(nyaFp, ", ");
if(recvbuf == NULL) {
    fprintf(nyaFp, "'recvbuf': 0x0");
}
else {
    fprintf(nyaFp, "'recvbuf': %p", recvbuf);
}
fprintf(nyaFp, ", ");
if(recvcounts == NULL) {
    fprintf(nyaFp, "'recvcounts': 0x0");
}
else {
    fprintf(nyaFp, "'recvcounts': %p", recvcounts);
}
fprintf(nyaFp, ", ");
if(rdispls == NULL) {
    fprintf(nyaFp, "'rdispls': 0x0");
}
else {
    fprintf(nyaFp, "'rdispls': %p", rdispls);
}
fprintf(nyaFp, ", ");
if(recvtypes == NULL) {
    fprintf(nyaFp, "'recvtypes': 0x0");
}
else {
    fprintf(nyaFp, "'recvtypes': %p", recvtypes);
}
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(request == NULL) {
    fprintf(nyaFp, "'request': 0x0");
}
else {
    fprintf(nyaFp, "'request': %p", request);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

  int loc_comm_size, i;
  int loc_sent = 0;

  PMPI_Comm_size(*comm, &loc_comm_size);

  for ( i = 0; i<loc_comm_size; i++) { 
    if ( sendtypes[i] != MPI_DATATYPE_NULL ) { 
      PMPI_Type_size(sendtypes[i], &tsize);
      loc_sent = sendcounts[i];
      messSize += (double)(tsize * loc_sent);
    }
    else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
     mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}
}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Ialltoallw");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Ialltoallw, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(hndl, mpiPi_MPI_Ialltoallw, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Ialltoallw */



extern int MPI_Ialltoallw ( const void* sendbuf, mpip_const_int_t sendcounts[], mpip_const_int_t sdispls[], mpip_const_datatype_t sendtypes[], void* recvbuf, mpip_const_int_t recvcounts[], mpip_const_int_t rdispls[], mpip_const_datatype_t recvtypes[], MPI_Comm comm, MPI_Request *request )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Ialltoallw( &jbuf, sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes,  & comm, request );

return rc;
} /* MPI_Ialltoallw */


extern void F77_MPI_IALLTOALLW(const void  *sendbuf, mpip_const_int_t sendcounts[], mpip_const_int_t sdispls[], mpip_const_datatype_t sendtypes[], void  *recvbuf, mpip_const_int_t recvcounts[], mpip_const_int_t rdispls[], mpip_const_datatype_t recvtypes[], MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;
MPI_Request c_request;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Ialltoallw( &jbuf, sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, &c_comm, &c_request );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_ialltoallw */



/* --------------- MPI_Ibarrier --------------- */

static int mpiPif_MPI_Ibarrier( jmp_buf * base_jbuf, MPI_Comm  * comm, MPI_Request  *request)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Ibarrier(  * comm, request);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Ibarrier', ");
fprintf(nyaFp, "'arguments': {");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(request == NULL) {
    fprintf(nyaFp, "'request': 0x0");
}
else {
    fprintf(nyaFp, "'request': %p", request);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Ibarrier");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Ibarrier, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(hndl, mpiPi_MPI_Ibarrier, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Ibarrier */



extern int MPI_Ibarrier ( MPI_Comm comm, MPI_Request *request )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Ibarrier( &jbuf,  & comm, request );

return rc;
} /* MPI_Ibarrier */


extern void F77_MPI_IBARRIER(MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;
MPI_Request c_request;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Ibarrier( &jbuf, &c_comm, &c_request );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_ibarrier */



/* --------------- MPI_Ibcast --------------- */

static int mpiPif_MPI_Ibcast( jmp_buf * base_jbuf, void  *buffer, int  * count, MPI_Datatype  * datatype, int  * root, MPI_Comm  * comm, MPI_Request  *request)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Ibcast( buffer,  * count,  * datatype,  * root,  * comm, request);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Ibcast', ");
fprintf(nyaFp, "'arguments': {");
if(buffer == NULL) {
    fprintf(nyaFp, "'buffer': 0x0");
}
else {
    fprintf(nyaFp, "'buffer': %p", buffer);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'count': %d", * count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'root': %d", * root);
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(request == NULL) {
    fprintf(nyaFp, "'request': 0x0");
}
else {
    fprintf(nyaFp, "'request': %p", request);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( *datatype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*datatype, &tsize);
messSize = (double)(tsize * *count);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Ibcast");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Ibcast, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(hndl, mpiPi_MPI_Ibcast, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Ibcast */



extern int MPI_Ibcast ( void* buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm, MPI_Request *request ) 
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Ibcast( &jbuf, buffer,  & count,  & datatype,  & root,  & comm, request );

return rc;
} /* MPI_Ibcast */


extern void F77_MPI_IBCAST(void  *buffer, int  * count, MPI_Fint  * datatype, int  * root, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Comm c_comm;
MPI_Request c_request;

c_datatype = MPI_Type_f2c(*datatype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Ibcast( &jbuf, buffer, count, &c_datatype, root, &c_comm, &c_request );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_ibcast */



/* --------------- MPI_Ibsend --------------- */

static int mpiPif_MPI_Ibsend( jmp_buf * base_jbuf, mpip_const_void_t  *buf, int  * count, MPI_Datatype  * datatype, int  * dest, int  * tag, MPI_Comm  * comm, MPI_Request  *request)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Ibsend( buf,  * count,  * datatype,  * dest,  * tag,  * comm, request);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Ibsend', ");
fprintf(nyaFp, "'arguments': {");
if(buf == NULL) {
    fprintf(nyaFp, "'buf': 0x0");
}
else {
    fprintf(nyaFp, "'buf': %p", buf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'count': %d", * count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'dest': %d", * dest);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'tag': %d", * tag);
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(request == NULL) {
    fprintf(nyaFp, "'request': 0x0");
}
else {
    fprintf(nyaFp, "'request': %p", request);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( *datatype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*datatype, &tsize);
messSize = (double)(tsize * *count);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Ibsend");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Ibsend, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_pt2pt_stats_report) { mpiPi_update_pt2pt_stats(hndl, mpiPi_MPI_Ibsend, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Ibsend */



extern int MPI_Ibsend ( mpip_const_void_t *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Ibsend( &jbuf, buf,  & count,  & datatype,  & dest,  & tag,  & comm, request );

return rc;
} /* MPI_Ibsend */


extern void F77_MPI_IBSEND(mpip_const_void_t  *buf, int  * count, MPI_Fint  * datatype, int  * dest, int  * tag, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Comm c_comm;
MPI_Request c_request;

c_datatype = MPI_Type_f2c(*datatype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Ibsend( &jbuf, buf, count, &c_datatype, dest, tag, &c_comm, &c_request );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_ibsend */



/* --------------- MPI_Iexscan --------------- */

static int mpiPif_MPI_Iexscan( jmp_buf * base_jbuf, const void  *sendbuf, void  *recvbuf, int  * count, MPI_Datatype  * datatype, MPI_Op  * op, MPI_Comm  * comm, MPI_Request  *request)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Iexscan( sendbuf, recvbuf,  * count,  * datatype,  * op,  * comm, request);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Iexscan', ");
fprintf(nyaFp, "'arguments': {");
if(sendbuf == NULL) {
    fprintf(nyaFp, "'sendbuf': 0x0");
}
else {
    fprintf(nyaFp, "'sendbuf': %p", sendbuf);
}
fprintf(nyaFp, ", ");
if(recvbuf == NULL) {
    fprintf(nyaFp, "'recvbuf': 0x0");
}
else {
    fprintf(nyaFp, "'recvbuf': %p", recvbuf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'count': %d", * count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'op': '%s'", get_op_name(* op));
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(request == NULL) {
    fprintf(nyaFp, "'request': 0x0");
}
else {
    fprintf(nyaFp, "'request': %p", request);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( *datatype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*datatype, &tsize);
messSize = (double)(tsize * *count);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Iexscan");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Iexscan, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(hndl, mpiPi_MPI_Iexscan, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Iexscan */



extern int MPI_Iexscan ( const void* sendbuf, void* recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request )  
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Iexscan( &jbuf, sendbuf, recvbuf,  & count,  & datatype,  & op,  & comm, request );

return rc;
} /* MPI_Iexscan */


extern void F77_MPI_IEXSCAN(const void  *sendbuf, void  *recvbuf, int  * count, MPI_Fint  * datatype, MPI_Fint  * op, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Op c_op;
MPI_Comm c_comm;
MPI_Request c_request;

c_datatype = MPI_Type_f2c(*datatype);
c_op = MPI_Op_f2c(*op);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Iexscan( &jbuf, sendbuf, recvbuf, count, &c_datatype, &c_op, &c_comm, &c_request );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_iexscan */



/* --------------- MPI_Igather --------------- */

static int mpiPif_MPI_Igather( jmp_buf * base_jbuf, const void  *sendbuf, int  * sendcount, MPI_Datatype  * sendtype, void  *recvbuf, int  * recvcount, MPI_Datatype  * recvtype, int  * root, MPI_Comm  * comm, MPI_Request  *request)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Igather( sendbuf,  * sendcount,  * sendtype, recvbuf,  * recvcount,  * recvtype,  * root,  * comm, request);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Igather', ");
fprintf(nyaFp, "'arguments': {");
if(sendbuf == NULL) {
    fprintf(nyaFp, "'sendbuf': 0x0");
}
else {
    fprintf(nyaFp, "'sendbuf': %p", sendbuf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'sendcount': %d", * sendcount);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* sendtype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'sendtype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'sendtype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
if(recvbuf == NULL) {
    fprintf(nyaFp, "'recvbuf': 0x0");
}
else {
    fprintf(nyaFp, "'recvbuf': %p", recvbuf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'recvcount': %d", * recvcount);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* recvtype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'recvtype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'recvtype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'root': %d", * root);
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(request == NULL) {
    fprintf(nyaFp, "'request': 0x0");
}
else {
    fprintf(nyaFp, "'request': %p", request);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( *sendtype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*sendtype, &tsize);
messSize = (double)(tsize * *sendcount);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Igather");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Igather, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(hndl, mpiPi_MPI_Igather, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Igather */



extern int MPI_Igather ( const void* sendbuf, int sendcount, MPI_Datatype sendtype, void* recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request) 
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Igather( &jbuf, sendbuf,  & sendcount,  & sendtype, recvbuf,  & recvcount,  & recvtype,  & root,  & comm, request );

return rc;
} /* MPI_Igather */


extern void F77_MPI_IGATHER(const void  *sendbuf, int  * sendcount, MPI_Fint  * sendtype, void  *recvbuf, int  * recvcount, MPI_Fint  * recvtype, int  * root, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_sendtype;
MPI_Datatype c_recvtype;
MPI_Comm c_comm;
MPI_Request c_request;

c_sendtype = MPI_Type_f2c(*sendtype);
c_recvtype = MPI_Type_f2c(*recvtype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Igather( &jbuf, sendbuf, sendcount, &c_sendtype, recvbuf, recvcount, &c_recvtype, root, &c_comm, &c_request );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_igather */



/* --------------- MPI_Igatherv --------------- */

static int mpiPif_MPI_Igatherv( jmp_buf * base_jbuf, const void  *sendbuf, int  * sendcount, MPI_Datatype  * sendtype, void  *recvbuf, mpip_const_int_t recvcounts[], mpip_const_int_t displs[], MPI_Datatype  * recvtype, int  * root, MPI_Comm  * comm, MPI_Request  *request)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Igatherv( sendbuf,  * sendcount,  * sendtype, recvbuf, recvcounts, displs,  * recvtype,  * root,  * comm, request);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Igatherv', ");
fprintf(nyaFp, "'arguments': {");
if(sendbuf == NULL) {
    fprintf(nyaFp, "'sendbuf': 0x0");
}
else {
    fprintf(nyaFp, "'sendbuf': %p", sendbuf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'sendcount': %d", * sendcount);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* sendtype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'sendtype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'sendtype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
if(recvbuf == NULL) {
    fprintf(nyaFp, "'recvbuf': 0x0");
}
else {
    fprintf(nyaFp, "'recvbuf': %p", recvbuf);
}
fprintf(nyaFp, ", ");
if(recvcounts == NULL) {
    fprintf(nyaFp, "'recvcounts': 0x0");
}
else {
    fprintf(nyaFp, "'recvcounts': %p", recvcounts);
}
fprintf(nyaFp, ", ");
if(displs == NULL) {
    fprintf(nyaFp, "'displs': 0x0");
}
else {
    fprintf(nyaFp, "'displs': %p", displs);
}
fprintf(nyaFp, ", ");
MPI_Type_get_name(* recvtype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'recvtype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'recvtype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'root': %d", * root);
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(request == NULL) {
    fprintf(nyaFp, "'request': 0x0");
}
else {
    fprintf(nyaFp, "'request': %p", request);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( *sendtype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*sendtype, &tsize);
messSize = (double)(tsize * *sendcount);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Igatherv");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Igatherv, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(hndl, mpiPi_MPI_Igatherv, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Igatherv */



extern int MPI_Igatherv ( const void* sendbuf, int sendcount, MPI_Datatype sendtype, void* recvbuf, mpip_const_int_t recvcounts[], mpip_const_int_t displs[], MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Igatherv( &jbuf, sendbuf,  & sendcount,  & sendtype, recvbuf, recvcounts, displs,  & recvtype,  & root,  & comm, request );

return rc;
} /* MPI_Igatherv */


extern void F77_MPI_IGATHERV(const void  *sendbuf, int  * sendcount, MPI_Fint  * sendtype, void  *recvbuf, mpip_const_int_t recvcounts[], mpip_const_int_t displs[], MPI_Fint  * recvtype, int  * root, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_sendtype;
MPI_Datatype c_recvtype;
MPI_Comm c_comm;
MPI_Request c_request;

c_sendtype = MPI_Type_f2c(*sendtype);
c_recvtype = MPI_Type_f2c(*recvtype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Igatherv( &jbuf, sendbuf, sendcount, &c_sendtype, recvbuf, recvcounts, displs, &c_recvtype, root, &c_comm, &c_request );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_igatherv */



/* --------------- MPI_Intercomm_create --------------- */

static int mpiPif_MPI_Intercomm_create( jmp_buf * base_jbuf, MPI_Comm  * local_comm, int  * local_leader, MPI_Comm  * peer_comm, int  * remote_leader, int  * tag, MPI_Comm  *comm_out)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Intercomm_create(  * local_comm,  * local_leader,  * peer_comm,  * remote_leader,  * tag, comm_out);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Intercomm_create', ");
fprintf(nyaFp, "'arguments': {");
MPI_Comm_rank(* local_comm, &nyaRank);
fprintf(nyaFp, "'local_comm': %d", nyaRank);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'local_leader': %d", * local_leader);
fprintf(nyaFp, ", ");
MPI_Comm_rank(* peer_comm, &nyaRank);
fprintf(nyaFp, "'peer_comm': %d", nyaRank);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'remote_leader': %d", * remote_leader);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'tag': %d", * tag);
fprintf(nyaFp, ", ");
if(comm_out == NULL) {
    fprintf(nyaFp, "'comm_out': 0x0");
}
else {
    fprintf(nyaFp, "'comm_out': %p", comm_out);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Intercomm_create");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Intercomm_create, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Intercomm_create */



extern int MPI_Intercomm_create ( MPI_Comm local_comm, int local_leader, MPI_Comm peer_comm, int remote_leader, int tag, MPI_Comm *comm_out )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Intercomm_create( &jbuf,  & local_comm,  & local_leader,  & peer_comm,  & remote_leader,  & tag, comm_out );

return rc;
} /* MPI_Intercomm_create */


extern void F77_MPI_INTERCOMM_CREATE(MPI_Fint  * local_comm, int  * local_leader, MPI_Fint  * peer_comm, int  * remote_leader, int  * tag, MPI_Fint  *comm_out , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Comm c_local_comm;
MPI_Comm c_peer_comm;
MPI_Comm c_comm_out;

c_local_comm = MPI_Comm_f2c(*local_comm);
c_peer_comm = MPI_Comm_f2c(*peer_comm);

rc = mpiPif_MPI_Intercomm_create( &jbuf, &c_local_comm, local_leader, &c_peer_comm, remote_leader, tag, &c_comm_out );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*comm_out = MPI_Comm_c2f(c_comm_out);
}
return;
} /* mpi_intercomm_create */



/* --------------- MPI_Intercomm_merge --------------- */

static int mpiPif_MPI_Intercomm_merge( jmp_buf * base_jbuf, MPI_Comm  * comm, int  * high, MPI_Comm  *comm_out)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Intercomm_merge(  * comm,  * high, comm_out);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Intercomm_merge', ");
fprintf(nyaFp, "'arguments': {");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'high': %d", * high);
fprintf(nyaFp, ", ");
if(comm_out == NULL) {
    fprintf(nyaFp, "'comm_out': 0x0");
}
else {
    fprintf(nyaFp, "'comm_out': %p", comm_out);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Intercomm_merge");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Intercomm_merge, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Intercomm_merge */



extern int MPI_Intercomm_merge ( MPI_Comm comm, int high, MPI_Comm *comm_out )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Intercomm_merge( &jbuf,  & comm,  & high, comm_out );

return rc;
} /* MPI_Intercomm_merge */


extern void F77_MPI_INTERCOMM_MERGE(MPI_Fint  * comm, int  * high, MPI_Fint  *comm_out , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;
MPI_Comm c_comm_out;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Intercomm_merge( &jbuf, &c_comm, high, &c_comm_out );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*comm_out = MPI_Comm_c2f(c_comm_out);
}
return;
} /* mpi_intercomm_merge */



/* --------------- MPI_Iprobe --------------- */

static int mpiPif_MPI_Iprobe( jmp_buf * base_jbuf, int  * source, int  * tag, MPI_Comm  * comm, int  *flag, MPI_Status  *status)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Iprobe(  * source,  * tag,  * comm, flag, status);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Iprobe', ");
fprintf(nyaFp, "'arguments': {");
fprintf(nyaFp, "'source': %d", * source);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'tag': %d", * tag);
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(flag == NULL) {
    fprintf(nyaFp, "'flag': 0x0");
}
else {
    fprintf(nyaFp, "'flag': %p", flag);
}
fprintf(nyaFp, ", ");
if(status == NULL) {
    fprintf(nyaFp, "'status': 0x0");
}
else {
    fprintf(nyaFp, "'status': %p", status);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Iprobe");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Iprobe, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Iprobe */



extern int MPI_Iprobe ( int source, int tag, MPI_Comm comm, int *flag, MPI_Status *status )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Iprobe( &jbuf,  & source,  & tag,  & comm, flag, status );

return rc;
} /* MPI_Iprobe */


extern void F77_MPI_IPROBE(int  * source, int  * tag, MPI_Fint  * comm, int  *flag, MPI_Status  *status , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Iprobe( &jbuf, source, tag, &c_comm, flag, status );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_iprobe */



/* --------------- MPI_Irecv --------------- */

static int mpiPif_MPI_Irecv( jmp_buf * base_jbuf, void  *buf, int  * count, MPI_Datatype  * datatype, int  * source, int  * tag, MPI_Comm  * comm, MPI_Request  *request)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Irecv( buf,  * count,  * datatype,  * source,  * tag,  * comm, request);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Irecv', ");
fprintf(nyaFp, "'arguments': {");
if(buf == NULL) {
    fprintf(nyaFp, "'buf': 0x0");
}
else {
    fprintf(nyaFp, "'buf': %p", buf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'count': %d", * count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'source': %d", * source);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'tag': %d", * tag);
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(request == NULL) {
    fprintf(nyaFp, "'request': 0x0");
}
else {
    fprintf(nyaFp, "'request': %p", request);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Irecv");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Irecv, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Irecv */



extern int MPI_Irecv ( void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Irecv( &jbuf, buf,  & count,  & datatype,  & source,  & tag,  & comm, request );

return rc;
} /* MPI_Irecv */


extern void F77_MPI_IRECV(void  *buf, int  * count, MPI_Fint  * datatype, int  * source, int  * tag, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Comm c_comm;
MPI_Request c_request;

c_datatype = MPI_Type_f2c(*datatype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Irecv( &jbuf, buf, count, &c_datatype, source, tag, &c_comm, &c_request );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_irecv */



/* --------------- MPI_Ireduce --------------- */

static int mpiPif_MPI_Ireduce( jmp_buf * base_jbuf, const void  *sendbuf, void  *recvbuf, int  * count, MPI_Datatype  * datatype, MPI_Op  * op, int  * root, MPI_Comm  * comm, MPI_Request  *request)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Ireduce( sendbuf, recvbuf,  * count,  * datatype,  * op,  * root,  * comm, request);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Ireduce', ");
fprintf(nyaFp, "'arguments': {");
if(sendbuf == NULL) {
    fprintf(nyaFp, "'sendbuf': 0x0");
}
else {
    fprintf(nyaFp, "'sendbuf': %p", sendbuf);
}
fprintf(nyaFp, ", ");
if(recvbuf == NULL) {
    fprintf(nyaFp, "'recvbuf': 0x0");
}
else {
    fprintf(nyaFp, "'recvbuf': %p", recvbuf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'count': %d", * count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'op': '%s'", get_op_name(* op));
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'root': %d", * root);
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(request == NULL) {
    fprintf(nyaFp, "'request': 0x0");
}
else {
    fprintf(nyaFp, "'request': %p", request);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( *datatype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*datatype, &tsize);
messSize = (double)(tsize * *count);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Ireduce");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Ireduce, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(hndl, mpiPi_MPI_Ireduce, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Ireduce */



extern int MPI_Ireduce ( const void* sendbuf, void* recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm, MPI_Request *request )  
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Ireduce( &jbuf, sendbuf, recvbuf,  & count,  & datatype,  & op,  & root,  & comm, request );

return rc;
} /* MPI_Ireduce */


extern void F77_MPI_IREDUCE(const void  *sendbuf, void  *recvbuf, int  * count, MPI_Fint  * datatype, MPI_Fint  * op, int  * root, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Op c_op;
MPI_Comm c_comm;
MPI_Request c_request;

c_datatype = MPI_Type_f2c(*datatype);
c_op = MPI_Op_f2c(*op);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Ireduce( &jbuf, sendbuf, recvbuf, count, &c_datatype, &c_op, root, &c_comm, &c_request );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_ireduce */



/* --------------- MPI_Ireduce_scatter --------------- */

static int mpiPif_MPI_Ireduce_scatter( jmp_buf * base_jbuf, const void  *sendbuf, void  *recvbuf, mpip_const_int_t recvcounts[], MPI_Datatype  * datatype, MPI_Op  * op, MPI_Comm  * comm, MPI_Request  *request)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Ireduce_scatter( sendbuf, recvbuf, recvcounts,  * datatype,  * op,  * comm, request);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Ireduce_scatter', ");
fprintf(nyaFp, "'arguments': {");
if(sendbuf == NULL) {
    fprintf(nyaFp, "'sendbuf': 0x0");
}
else {
    fprintf(nyaFp, "'sendbuf': %p", sendbuf);
}
fprintf(nyaFp, ", ");
if(recvbuf == NULL) {
    fprintf(nyaFp, "'recvbuf': 0x0");
}
else {
    fprintf(nyaFp, "'recvbuf': %p", recvbuf);
}
fprintf(nyaFp, ", ");
if(recvcounts == NULL) {
    fprintf(nyaFp, "'recvcounts': 0x0");
}
else {
    fprintf(nyaFp, "'recvcounts': %p", recvcounts);
}
fprintf(nyaFp, ", ");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'op': '%s'", get_op_name(* op));
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(request == NULL) {
    fprintf(nyaFp, "'request': 0x0");
}
else {
    fprintf(nyaFp, "'request': %p", request);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( *datatype != MPI_DATATYPE_NULL ) { 
  int loc_comm_size, i;
  int loc_sent = 0;

  PMPI_Comm_size(*comm, &loc_comm_size);
  PMPI_Type_size(*datatype, &tsize);
  for ( i = 0; i<loc_comm_size; i++) 
    loc_sent += recvcounts[i];
  messSize = (double)(tsize * loc_sent);
}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Ireduce_scatter");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Ireduce_scatter, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(hndl, mpiPi_MPI_Ireduce_scatter, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Ireduce_scatter */



extern int MPI_Ireduce_scatter ( const void* sendbuf, void* recvbuf, mpip_const_int_t recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request )  
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Ireduce_scatter( &jbuf, sendbuf, recvbuf, recvcounts,  & datatype,  & op,  & comm, request );

return rc;
} /* MPI_Ireduce_scatter */


extern void F77_MPI_IREDUCE_SCATTER(const void  *sendbuf, void  *recvbuf, mpip_const_int_t recvcounts[], MPI_Fint  * datatype, MPI_Fint  * op, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Op c_op;
MPI_Comm c_comm;
MPI_Request c_request;

c_datatype = MPI_Type_f2c(*datatype);
c_op = MPI_Op_f2c(*op);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Ireduce_scatter( &jbuf, sendbuf, recvbuf, recvcounts, &c_datatype, &c_op, &c_comm, &c_request );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_ireduce_scatter */



/* --------------- MPI_Ireduce_scatter_block --------------- */

static int mpiPif_MPI_Ireduce_scatter_block( jmp_buf * base_jbuf, const void  *sendbuf, void  *recvbuf, int  * recvcount, MPI_Datatype  * datatype, MPI_Op  * op, MPI_Comm  * comm, MPI_Request  *request)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Ireduce_scatter_block( sendbuf, recvbuf,  * recvcount,  * datatype,  * op,  * comm, request);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Ireduce_scatter_block', ");
fprintf(nyaFp, "'arguments': {");
if(sendbuf == NULL) {
    fprintf(nyaFp, "'sendbuf': 0x0");
}
else {
    fprintf(nyaFp, "'sendbuf': %p", sendbuf);
}
fprintf(nyaFp, ", ");
if(recvbuf == NULL) {
    fprintf(nyaFp, "'recvbuf': 0x0");
}
else {
    fprintf(nyaFp, "'recvbuf': %p", recvbuf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'recvcount': %d", * recvcount);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'op': '%s'", get_op_name(* op));
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(request == NULL) {
    fprintf(nyaFp, "'request': 0x0");
}
else {
    fprintf(nyaFp, "'request': %p", request);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( *datatype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*datatype, &tsize);
messSize = (double)(tsize * *recvcount);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Ireduce_scatter_block");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Ireduce_scatter_block, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(hndl, mpiPi_MPI_Ireduce_scatter_block, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Ireduce_scatter_block */



extern int MPI_Ireduce_scatter_block ( const void* sendbuf, void* recvbuf, int recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request )  
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Ireduce_scatter_block( &jbuf, sendbuf, recvbuf,  & recvcount,  & datatype,  & op,  & comm, request );

return rc;
} /* MPI_Ireduce_scatter_block */


extern void F77_MPI_IREDUCE_SCATTER_BLOCK(const void  *sendbuf, void  *recvbuf, int  * recvcount, MPI_Fint  * datatype, MPI_Fint  * op, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Op c_op;
MPI_Comm c_comm;
MPI_Request c_request;

c_datatype = MPI_Type_f2c(*datatype);
c_op = MPI_Op_f2c(*op);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Ireduce_scatter_block( &jbuf, sendbuf, recvbuf, recvcount, &c_datatype, &c_op, &c_comm, &c_request );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_ireduce_scatter_block */



/* --------------- MPI_Irsend --------------- */

static int mpiPif_MPI_Irsend( jmp_buf * base_jbuf, mpip_const_void_t  *buf, int  * count, MPI_Datatype  * datatype, int  * dest, int  * tag, MPI_Comm  * comm, MPI_Request  *request)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Irsend( buf,  * count,  * datatype,  * dest,  * tag,  * comm, request);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Irsend', ");
fprintf(nyaFp, "'arguments': {");
if(buf == NULL) {
    fprintf(nyaFp, "'buf': 0x0");
}
else {
    fprintf(nyaFp, "'buf': %p", buf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'count': %d", * count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'dest': %d", * dest);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'tag': %d", * tag);
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(request == NULL) {
    fprintf(nyaFp, "'request': 0x0");
}
else {
    fprintf(nyaFp, "'request': %p", request);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( *datatype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*datatype, &tsize);
messSize = (double)(tsize * *count);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Irsend");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Irsend, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_pt2pt_stats_report) { mpiPi_update_pt2pt_stats(hndl, mpiPi_MPI_Irsend, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Irsend */



extern int MPI_Irsend ( mpip_const_void_t *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Irsend( &jbuf, buf,  & count,  & datatype,  & dest,  & tag,  & comm, request );

return rc;
} /* MPI_Irsend */


extern void F77_MPI_IRSEND(mpip_const_void_t  *buf, int  * count, MPI_Fint  * datatype, int  * dest, int  * tag, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Comm c_comm;
MPI_Request c_request;

c_datatype = MPI_Type_f2c(*datatype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Irsend( &jbuf, buf, count, &c_datatype, dest, tag, &c_comm, &c_request );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_irsend */



/* --------------- MPI_Iscan --------------- */

static int mpiPif_MPI_Iscan( jmp_buf * base_jbuf, const void  *sendbuf, void  *recvbuf, int  * count, MPI_Datatype  * datatype, MPI_Op  * op, MPI_Comm  * comm, MPI_Request  *request)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Iscan( sendbuf, recvbuf,  * count,  * datatype,  * op,  * comm, request);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Iscan', ");
fprintf(nyaFp, "'arguments': {");
if(sendbuf == NULL) {
    fprintf(nyaFp, "'sendbuf': 0x0");
}
else {
    fprintf(nyaFp, "'sendbuf': %p", sendbuf);
}
fprintf(nyaFp, ", ");
if(recvbuf == NULL) {
    fprintf(nyaFp, "'recvbuf': 0x0");
}
else {
    fprintf(nyaFp, "'recvbuf': %p", recvbuf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'count': %d", * count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'op': '%s'", get_op_name(* op));
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(request == NULL) {
    fprintf(nyaFp, "'request': 0x0");
}
else {
    fprintf(nyaFp, "'request': %p", request);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( *datatype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*datatype, &tsize);
messSize = (double)(tsize * *count);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Iscan");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Iscan, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(hndl, mpiPi_MPI_Iscan, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Iscan */



extern int MPI_Iscan ( const void* sendbuf, void* recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request )  
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Iscan( &jbuf, sendbuf, recvbuf,  & count,  & datatype,  & op,  & comm, request );

return rc;
} /* MPI_Iscan */


extern void F77_MPI_ISCAN(const void  *sendbuf, void  *recvbuf, int  * count, MPI_Fint  * datatype, MPI_Fint  * op, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Op c_op;
MPI_Comm c_comm;
MPI_Request c_request;

c_datatype = MPI_Type_f2c(*datatype);
c_op = MPI_Op_f2c(*op);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Iscan( &jbuf, sendbuf, recvbuf, count, &c_datatype, &c_op, &c_comm, &c_request );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_iscan */



/* --------------- MPI_Iscatter --------------- */

static int mpiPif_MPI_Iscatter( jmp_buf * base_jbuf, const void  *sendbuf, int  * sendcount, MPI_Datatype  * sendtype, void  *recvbuf, int  * recvcount, MPI_Datatype  * recvtype, int  * root, MPI_Comm  * comm, MPI_Request  *request)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Iscatter( sendbuf,  * sendcount,  * sendtype, recvbuf,  * recvcount,  * recvtype,  * root,  * comm, request);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Iscatter', ");
fprintf(nyaFp, "'arguments': {");
if(sendbuf == NULL) {
    fprintf(nyaFp, "'sendbuf': 0x0");
}
else {
    fprintf(nyaFp, "'sendbuf': %p", sendbuf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'sendcount': %d", * sendcount);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* sendtype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'sendtype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'sendtype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
if(recvbuf == NULL) {
    fprintf(nyaFp, "'recvbuf': 0x0");
}
else {
    fprintf(nyaFp, "'recvbuf': %p", recvbuf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'recvcount': %d", * recvcount);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* recvtype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'recvtype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'recvtype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'root': %d", * root);
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(request == NULL) {
    fprintf(nyaFp, "'request': 0x0");
}
else {
    fprintf(nyaFp, "'request': %p", request);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( *sendtype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*sendtype, &tsize);
messSize = (double)(tsize * *sendcount);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Iscatter");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Iscatter, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(hndl, mpiPi_MPI_Iscatter, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Iscatter */



extern int MPI_Iscatter ( const void* sendbuf, int sendcount, MPI_Datatype sendtype, void* recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request )  
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Iscatter( &jbuf, sendbuf,  & sendcount,  & sendtype, recvbuf,  & recvcount,  & recvtype,  & root,  & comm, request );

return rc;
} /* MPI_Iscatter */


extern void F77_MPI_ISCATTER(const void  *sendbuf, int  * sendcount, MPI_Fint  * sendtype, void  *recvbuf, int  * recvcount, MPI_Fint  * recvtype, int  * root, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_sendtype;
MPI_Datatype c_recvtype;
MPI_Comm c_comm;
MPI_Request c_request;

c_sendtype = MPI_Type_f2c(*sendtype);
c_recvtype = MPI_Type_f2c(*recvtype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Iscatter( &jbuf, sendbuf, sendcount, &c_sendtype, recvbuf, recvcount, &c_recvtype, root, &c_comm, &c_request );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_iscatter */



/* --------------- MPI_Iscatterv --------------- */

static int mpiPif_MPI_Iscatterv( jmp_buf * base_jbuf, const void  *sendbuf, mpip_const_int_t sendcounts[], mpip_const_int_t displs[], MPI_Datatype  * sendtype, void  *recvbuf, int  * recvcount, MPI_Datatype  * recvtype, int  * root, MPI_Comm  * comm, MPI_Request  *request)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Iscatterv( sendbuf, sendcounts, displs,  * sendtype, recvbuf,  * recvcount,  * recvtype,  * root,  * comm, request);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Iscatterv', ");
fprintf(nyaFp, "'arguments': {");
if(sendbuf == NULL) {
    fprintf(nyaFp, "'sendbuf': 0x0");
}
else {
    fprintf(nyaFp, "'sendbuf': %p", sendbuf);
}
fprintf(nyaFp, ", ");
if(sendcounts == NULL) {
    fprintf(nyaFp, "'sendcounts': 0x0");
}
else {
    fprintf(nyaFp, "'sendcounts': %p", sendcounts);
}
fprintf(nyaFp, ", ");
if(displs == NULL) {
    fprintf(nyaFp, "'displs': 0x0");
}
else {
    fprintf(nyaFp, "'displs': %p", displs);
}
fprintf(nyaFp, ", ");
MPI_Type_get_name(* sendtype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'sendtype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'sendtype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
if(recvbuf == NULL) {
    fprintf(nyaFp, "'recvbuf': 0x0");
}
else {
    fprintf(nyaFp, "'recvbuf': %p", recvbuf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'recvcount': %d", * recvcount);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* recvtype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'recvtype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'recvtype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'root': %d", * root);
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(request == NULL) {
    fprintf(nyaFp, "'request': 0x0");
}
else {
    fprintf(nyaFp, "'request': %p", request);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( *sendtype != MPI_DATATYPE_NULL ) { 
  int loc_comm_size, i;
  int loc_sent = 0;

  PMPI_Comm_size(*comm, &loc_comm_size);
  PMPI_Type_size(*sendtype, &tsize);
  for ( i = 0; i<loc_comm_size; i++) 
    loc_sent += sendcounts[i];
  messSize = (double)(tsize * loc_sent);
}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Iscatterv");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Iscatterv, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(hndl, mpiPi_MPI_Iscatterv, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Iscatterv */



extern int MPI_Iscatterv ( const void* sendbuf, mpip_const_int_t sendcounts[], mpip_const_int_t displs[], MPI_Datatype sendtype, void* recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Iscatterv( &jbuf, sendbuf, sendcounts, displs,  & sendtype, recvbuf,  & recvcount,  & recvtype,  & root,  & comm, request );

return rc;
} /* MPI_Iscatterv */


extern void F77_MPI_ISCATTERV(const void  *sendbuf, mpip_const_int_t sendcounts[], mpip_const_int_t displs[], MPI_Fint  * sendtype, void  *recvbuf, int  * recvcount, MPI_Fint  * recvtype, int  * root, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_sendtype;
MPI_Datatype c_recvtype;
MPI_Comm c_comm;
MPI_Request c_request;

c_sendtype = MPI_Type_f2c(*sendtype);
c_recvtype = MPI_Type_f2c(*recvtype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Iscatterv( &jbuf, sendbuf, sendcounts, displs, &c_sendtype, recvbuf, recvcount, &c_recvtype, root, &c_comm, &c_request );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_iscatterv */



/* --------------- MPI_Isend --------------- */

static int mpiPif_MPI_Isend( jmp_buf * base_jbuf, mpip_const_void_t  *buf, int  * count, MPI_Datatype  * datatype, int  * dest, int  * tag, MPI_Comm  * comm, MPI_Request  *request)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Isend( buf,  * count,  * datatype,  * dest,  * tag,  * comm, request);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Isend', ");
fprintf(nyaFp, "'arguments': {");
if(buf == NULL) {
    fprintf(nyaFp, "'buf': 0x0");
}
else {
    fprintf(nyaFp, "'buf': %p", buf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'count': %d", * count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'dest': %d", * dest);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'tag': %d", * tag);
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(request == NULL) {
    fprintf(nyaFp, "'request': 0x0");
}
else {
    fprintf(nyaFp, "'request': %p", request);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( *datatype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*datatype, &tsize);
messSize = (double)(tsize * *count);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Isend");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Isend, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_pt2pt_stats_report) { mpiPi_update_pt2pt_stats(hndl, mpiPi_MPI_Isend, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Isend */



extern int MPI_Isend ( mpip_const_void_t *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Isend( &jbuf, buf,  & count,  & datatype,  & dest,  & tag,  & comm, request );

return rc;
} /* MPI_Isend */


extern void F77_MPI_ISEND(mpip_const_void_t  *buf, int  * count, MPI_Fint  * datatype, int  * dest, int  * tag, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Comm c_comm;
MPI_Request c_request;

c_datatype = MPI_Type_f2c(*datatype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Isend( &jbuf, buf, count, &c_datatype, dest, tag, &c_comm, &c_request );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_isend */



/* --------------- MPI_Issend --------------- */

static int mpiPif_MPI_Issend( jmp_buf * base_jbuf, mpip_const_void_t  *buf, int  * count, MPI_Datatype  * datatype, int  * dest, int  * tag, MPI_Comm  * comm, MPI_Request  *request)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Issend( buf,  * count,  * datatype,  * dest,  * tag,  * comm, request);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Issend', ");
fprintf(nyaFp, "'arguments': {");
if(buf == NULL) {
    fprintf(nyaFp, "'buf': 0x0");
}
else {
    fprintf(nyaFp, "'buf': %p", buf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'count': %d", * count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'dest': %d", * dest);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'tag': %d", * tag);
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(request == NULL) {
    fprintf(nyaFp, "'request': 0x0");
}
else {
    fprintf(nyaFp, "'request': %p", request);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( *datatype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*datatype, &tsize);
messSize = (double)(tsize * *count);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Issend");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Issend, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_pt2pt_stats_report) { mpiPi_update_pt2pt_stats(hndl, mpiPi_MPI_Issend, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Issend */



extern int MPI_Issend ( mpip_const_void_t *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Issend( &jbuf, buf,  & count,  & datatype,  & dest,  & tag,  & comm, request );

return rc;
} /* MPI_Issend */


extern void F77_MPI_ISSEND(mpip_const_void_t  *buf, int  * count, MPI_Fint  * datatype, int  * dest, int  * tag, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Comm c_comm;
MPI_Request c_request;

c_datatype = MPI_Type_f2c(*datatype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Issend( &jbuf, buf, count, &c_datatype, dest, tag, &c_comm, &c_request );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_issend */



/* --------------- MPI_Pack --------------- */

static int mpiPif_MPI_Pack( jmp_buf * base_jbuf, mpip_const_void_t  *inbuf, int  * incount, MPI_Datatype  * datatype, void  *outbuf, int  * count, int  *position, MPI_Comm  * comm)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Pack( inbuf,  * incount,  * datatype, outbuf,  * count, position,  * comm);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Pack', ");
fprintf(nyaFp, "'arguments': {");
if(inbuf == NULL) {
    fprintf(nyaFp, "'inbuf': 0x0");
}
else {
    fprintf(nyaFp, "'inbuf': %p", inbuf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'incount': %d", * incount);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
if(outbuf == NULL) {
    fprintf(nyaFp, "'outbuf': 0x0");
}
else {
    fprintf(nyaFp, "'outbuf': %p", outbuf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'count': %d", * count);
fprintf(nyaFp, ", ");
if(position == NULL) {
    fprintf(nyaFp, "'position': 0x0");
}
else {
    fprintf(nyaFp, "'position': %p", position);
}
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Pack");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Pack, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Pack */



extern int MPI_Pack ( mpip_const_void_t *inbuf, int incount, MPI_Datatype datatype, void *outbuf, int count, int *position, MPI_Comm comm )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Pack( &jbuf, inbuf,  & incount,  & datatype, outbuf,  & count, position,  & comm );

return rc;
} /* MPI_Pack */


extern void F77_MPI_PACK(mpip_const_void_t  *inbuf, int  * incount, MPI_Fint  * datatype, void  *outbuf, int  * count, int  *position, MPI_Fint  * comm , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Comm c_comm;

c_datatype = MPI_Type_f2c(*datatype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Pack( &jbuf, inbuf, incount, &c_datatype, outbuf, count, position, &c_comm );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_pack */



/* --------------- MPI_Probe --------------- */

static int mpiPif_MPI_Probe( jmp_buf * base_jbuf, int  * source, int  * tag, MPI_Comm  * comm, MPI_Status  *status)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Probe(  * source,  * tag,  * comm, status);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Probe', ");
fprintf(nyaFp, "'arguments': {");
fprintf(nyaFp, "'source': %d", * source);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'tag': %d", * tag);
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(status == NULL) {
    fprintf(nyaFp, "'status': 0x0");
}
else {
    fprintf(nyaFp, "'status': %p", status);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Probe");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Probe, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Probe */



extern int MPI_Probe ( int source, int tag, MPI_Comm comm, MPI_Status *status )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Probe( &jbuf,  & source,  & tag,  & comm, status );

return rc;
} /* MPI_Probe */


extern void F77_MPI_PROBE(int  * source, int  * tag, MPI_Fint  * comm, MPI_Status  *status , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Probe( &jbuf, source, tag, &c_comm, status );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_probe */



/* --------------- MPI_Put --------------- */

static int mpiPif_MPI_Put( jmp_buf * base_jbuf, mpip_const_void_t  *origin_addr, int  * origin_count, MPI_Datatype  * origin_datatype, int  * target_rank, MPI_Aint  * target_disp, int  * target_count, MPI_Datatype  * target_datatype, MPI_Win  * win)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Put( origin_addr,  * origin_count,  * origin_datatype,  * target_rank,  * target_disp,  * target_count,  * target_datatype,  * win);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Put', ");
fprintf(nyaFp, "'arguments': {");
if(origin_addr == NULL) {
    fprintf(nyaFp, "'origin_addr': 0x0");
}
else {
    fprintf(nyaFp, "'origin_addr': %p", origin_addr);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'origin_count': %d", * origin_count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* origin_datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'origin_datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'origin_datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'target_rank': %d", * target_rank);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'target_disp': %ld", * target_disp);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'target_count': %d", * target_count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* target_datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'target_datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'target_datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
MPI_Win_get_info(* win, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'win': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

PMPI_Type_size(*origin_datatype, &tsize);
rmaSize = (double)(tsize * *origin_count);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Put");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Put, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Put */



extern int MPI_Put ( mpip_const_void_t *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Put( &jbuf, origin_addr,  & origin_count,  & origin_datatype,  & target_rank,  & target_disp,  & target_count,  & target_datatype,  & win );

return rc;
} /* MPI_Put */


extern void F77_MPI_PUT(mpip_const_void_t  *origin_addr, int  * origin_count, MPI_Fint  * origin_datatype, int  * target_rank, MPI_Aint  * target_disp, int  * target_count, MPI_Fint  * target_datatype, MPI_Win  * win , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_origin_datatype;
MPI_Datatype c_target_datatype;

c_origin_datatype = MPI_Type_f2c(*origin_datatype);
c_target_datatype = MPI_Type_f2c(*target_datatype);

rc = mpiPif_MPI_Put( &jbuf, origin_addr, origin_count, &c_origin_datatype, target_rank, target_disp, target_count, &c_target_datatype, win );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_put */



/* --------------- MPI_Raccumulate --------------- */

static int mpiPif_MPI_Raccumulate( jmp_buf * base_jbuf, mpip_const_void_t  *origin_addr, int  * origin_count, MPI_Datatype  * origin_datatype, int  * target_rank, MPI_Aint  * target_disp, int  * target_count, MPI_Datatype  * target_datatype, MPI_Op  * op, MPI_Win  * win, MPI_Request  *request)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Raccumulate( origin_addr,  * origin_count,  * origin_datatype,  * target_rank,  * target_disp,  * target_count,  * target_datatype,  * op,  * win, request);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Raccumulate', ");
fprintf(nyaFp, "'arguments': {");
if(origin_addr == NULL) {
    fprintf(nyaFp, "'origin_addr': 0x0");
}
else {
    fprintf(nyaFp, "'origin_addr': %p", origin_addr);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'origin_count': %d", * origin_count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* origin_datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'origin_datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'origin_datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'target_rank': %d", * target_rank);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'target_disp': %ld", * target_disp);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'target_count': %d", * target_count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* target_datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'target_datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'target_datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'op': '%s'", get_op_name(* op));
fprintf(nyaFp, ", ");
MPI_Win_get_info(* win, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'win': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
if(request == NULL) {
    fprintf(nyaFp, "'request': 0x0");
}
else {
    fprintf(nyaFp, "'request': %p", request);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

PMPI_Type_size(*target_datatype, &tsize);
rmaSize = (double)(tsize * *target_count);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Raccumulate");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Raccumulate, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Raccumulate */



extern int MPI_Raccumulate ( mpip_const_void_t *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, MPI_Request *request )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Raccumulate( &jbuf, origin_addr,  & origin_count,  & origin_datatype,  & target_rank,  & target_disp,  & target_count,  & target_datatype,  & op,  & win, request );

return rc;
} /* MPI_Raccumulate */


extern void F77_MPI_RACCUMULATE(mpip_const_void_t  *origin_addr, int  * origin_count, MPI_Fint  * origin_datatype, int  * target_rank, MPI_Aint  * target_disp, int  * target_count, MPI_Fint  * target_datatype, MPI_Fint  * op, MPI_Win  * win, MPI_Fint  *request , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_origin_datatype;
MPI_Datatype c_target_datatype;
MPI_Op c_op;
MPI_Request c_request;

c_origin_datatype = MPI_Type_f2c(*origin_datatype);
c_target_datatype = MPI_Type_f2c(*target_datatype);
c_op = MPI_Op_f2c(*op);
c_request = MPI_Request_f2c(*request);

rc = mpiPif_MPI_Raccumulate( &jbuf, origin_addr, origin_count, &c_origin_datatype, target_rank, target_disp, target_count, &c_target_datatype, &c_op, win, &c_request );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_raccumulate */



/* --------------- MPI_Recv --------------- */

static int mpiPif_MPI_Recv( jmp_buf * base_jbuf, void  *buf, int  * count, MPI_Datatype  * datatype, int  * source, int  * tag, MPI_Comm  * comm, MPI_Status  *status)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Recv( buf,  * count,  * datatype,  * source,  * tag,  * comm, status);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Recv', ");
fprintf(nyaFp, "'arguments': {");
if(buf == NULL) {
    fprintf(nyaFp, "'buf': 0x0");
}
else {
    fprintf(nyaFp, "'buf': %p", buf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'count': %d", * count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'source': %d", * source);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'tag': %d", * tag);
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(status == NULL) {
    fprintf(nyaFp, "'status': 0x0");
}
else {
    fprintf(nyaFp, "'status': %p", status);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Recv");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Recv, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Recv */



extern int MPI_Recv ( void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Recv( &jbuf, buf,  & count,  & datatype,  & source,  & tag,  & comm, status );

return rc;
} /* MPI_Recv */


extern void F77_MPI_RECV(void  *buf, int  * count, MPI_Fint  * datatype, int  * source, int  * tag, MPI_Fint  * comm, MPI_Status  *status , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Comm c_comm;

c_datatype = MPI_Type_f2c(*datatype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Recv( &jbuf, buf, count, &c_datatype, source, tag, &c_comm, status );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_recv */



/* --------------- MPI_Recv_init --------------- */

static int mpiPif_MPI_Recv_init( jmp_buf * base_jbuf, void  *buf, int  * count, MPI_Datatype  * datatype, int  * source, int  * tag, MPI_Comm  * comm, MPI_Request  *request)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Recv_init( buf,  * count,  * datatype,  * source,  * tag,  * comm, request);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Recv_init', ");
fprintf(nyaFp, "'arguments': {");
if(buf == NULL) {
    fprintf(nyaFp, "'buf': 0x0");
}
else {
    fprintf(nyaFp, "'buf': %p", buf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'count': %d", * count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'source': %d", * source);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'tag': %d", * tag);
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(request == NULL) {
    fprintf(nyaFp, "'request': 0x0");
}
else {
    fprintf(nyaFp, "'request': %p", request);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Recv_init");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Recv_init, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Recv_init */



extern int MPI_Recv_init ( void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Recv_init( &jbuf, buf,  & count,  & datatype,  & source,  & tag,  & comm, request );

return rc;
} /* MPI_Recv_init */


extern void F77_MPI_RECV_INIT(void  *buf, int  * count, MPI_Fint  * datatype, int  * source, int  * tag, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Comm c_comm;
MPI_Request c_request;

c_datatype = MPI_Type_f2c(*datatype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Recv_init( &jbuf, buf, count, &c_datatype, source, tag, &c_comm, &c_request );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_recv_init */



/* --------------- MPI_Reduce --------------- */

static int mpiPif_MPI_Reduce( jmp_buf * base_jbuf, mpip_const_void_t  *sendbuf, void  *recvbuf, int  * count, MPI_Datatype  * datatype, MPI_Op  * op, int  * root, MPI_Comm  * comm)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Reduce( sendbuf, recvbuf,  * count,  * datatype,  * op,  * root,  * comm);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Reduce', ");
fprintf(nyaFp, "'arguments': {");
if(sendbuf == NULL) {
    fprintf(nyaFp, "'sendbuf': 0x0");
}
else {
    fprintf(nyaFp, "'sendbuf': %p", sendbuf);
}
fprintf(nyaFp, ", ");
if(recvbuf == NULL) {
    fprintf(nyaFp, "'recvbuf': 0x0");
}
else {
    fprintf(nyaFp, "'recvbuf': %p", recvbuf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'count': %d", * count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'op': '%s'", get_op_name(* op));
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'root': %d", * root);
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( *datatype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*datatype, &tsize);
messSize = (double)(tsize * *count);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Reduce");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Reduce, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(hndl, mpiPi_MPI_Reduce, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Reduce */



extern int MPI_Reduce ( mpip_const_void_t *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Reduce( &jbuf, sendbuf, recvbuf,  & count,  & datatype,  & op,  & root,  & comm );

return rc;
} /* MPI_Reduce */


extern void F77_MPI_REDUCE(mpip_const_void_t  *sendbuf, void  *recvbuf, int  * count, MPI_Fint  * datatype, MPI_Fint  * op, int  * root, MPI_Fint  * comm , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Op c_op;
MPI_Comm c_comm;

c_datatype = MPI_Type_f2c(*datatype);
c_op = MPI_Op_f2c(*op);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Reduce( &jbuf, sendbuf, recvbuf, count, &c_datatype, &c_op, root, &c_comm );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_reduce */



/* --------------- MPI_Reduce_scatter --------------- */

static int mpiPif_MPI_Reduce_scatter( jmp_buf * base_jbuf, mpip_const_void_t  *sendbuf, void  *recvbuf, mpip_const_int_t  *recvcnts, MPI_Datatype  * datatype, MPI_Op  * op, MPI_Comm  * comm)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Reduce_scatter( sendbuf, recvbuf, recvcnts,  * datatype,  * op,  * comm);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Reduce_scatter', ");
fprintf(nyaFp, "'arguments': {");
if(sendbuf == NULL) {
    fprintf(nyaFp, "'sendbuf': 0x0");
}
else {
    fprintf(nyaFp, "'sendbuf': %p", sendbuf);
}
fprintf(nyaFp, ", ");
if(recvbuf == NULL) {
    fprintf(nyaFp, "'recvbuf': 0x0");
}
else {
    fprintf(nyaFp, "'recvbuf': %p", recvbuf);
}
fprintf(nyaFp, ", ");
if(recvcnts == NULL) {
    fprintf(nyaFp, "'recvcnts': 0x0");
}
else {
    fprintf(nyaFp, "'recvcnts': %p", recvcnts);
}
fprintf(nyaFp, ", ");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'op': '%s'", get_op_name(* op));
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Reduce_scatter");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Reduce_scatter, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(hndl, mpiPi_MPI_Reduce_scatter, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Reduce_scatter */



extern int MPI_Reduce_scatter ( mpip_const_void_t *sendbuf, void *recvbuf, mpip_const_int_t *recvcnts, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Reduce_scatter( &jbuf, sendbuf, recvbuf, recvcnts,  & datatype,  & op,  & comm );

return rc;
} /* MPI_Reduce_scatter */


extern void F77_MPI_REDUCE_SCATTER(mpip_const_void_t  *sendbuf, void  *recvbuf, mpip_const_int_t  *recvcnts, MPI_Fint  * datatype, MPI_Fint  * op, MPI_Fint  * comm , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Op c_op;
MPI_Comm c_comm;

c_datatype = MPI_Type_f2c(*datatype);
c_op = MPI_Op_f2c(*op);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Reduce_scatter( &jbuf, sendbuf, recvbuf, recvcnts, &c_datatype, &c_op, &c_comm );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_reduce_scatter */



/* --------------- MPI_Request_free --------------- */

static int mpiPif_MPI_Request_free( jmp_buf * base_jbuf, MPI_Request  *request)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Request_free( request);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Request_free', ");
fprintf(nyaFp, "'arguments': {");
if(request == NULL) {
    fprintf(nyaFp, "'request': 0x0");
}
else {
    fprintf(nyaFp, "'request': %p", request);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Request_free");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Request_free, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Request_free */



extern int MPI_Request_free ( MPI_Request *request )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Request_free( &jbuf, request );

return rc;
} /* MPI_Request_free */


extern void F77_MPI_REQUEST_FREE(MPI_Fint  *request , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Request c_request;

c_request = MPI_Request_f2c(*request);

rc = mpiPif_MPI_Request_free( &jbuf, &c_request );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_request_free */



/* --------------- MPI_Rget --------------- */

static int mpiPif_MPI_Rget( jmp_buf * base_jbuf, void  *origin_addr, int  * origin_count, MPI_Datatype  * origin_datatype, int  * target_rank, MPI_Aint  * target_disp, int  * target_count, MPI_Datatype  * target_datatype, MPI_Win  * win, MPI_Request  *request)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Rget( origin_addr,  * origin_count,  * origin_datatype,  * target_rank,  * target_disp,  * target_count,  * target_datatype,  * win, request);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Rget', ");
fprintf(nyaFp, "'arguments': {");
if(origin_addr == NULL) {
    fprintf(nyaFp, "'origin_addr': 0x0");
}
else {
    fprintf(nyaFp, "'origin_addr': %p", origin_addr);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'origin_count': %d", * origin_count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* origin_datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'origin_datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'origin_datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'target_rank': %d", * target_rank);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'target_disp': %ld", * target_disp);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'target_count': %d", * target_count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* target_datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'target_datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'target_datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
MPI_Win_get_info(* win, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'win': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
if(request == NULL) {
    fprintf(nyaFp, "'request': 0x0");
}
else {
    fprintf(nyaFp, "'request': %p", request);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

PMPI_Type_size(*origin_datatype, &tsize);
rmaSize = (double)(tsize * *origin_count);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Rget");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Rget, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Rget */



extern int MPI_Rget ( void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win, MPI_Request *request )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Rget( &jbuf, origin_addr,  & origin_count,  & origin_datatype,  & target_rank,  & target_disp,  & target_count,  & target_datatype,  & win, request );

return rc;
} /* MPI_Rget */


extern void F77_MPI_RGET(void  *origin_addr, int  * origin_count, MPI_Fint  * origin_datatype, int  * target_rank, MPI_Aint  * target_disp, int  * target_count, MPI_Fint  * target_datatype, MPI_Win  * win, MPI_Fint  *request , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_origin_datatype;
MPI_Datatype c_target_datatype;
MPI_Request c_request;

c_origin_datatype = MPI_Type_f2c(*origin_datatype);
c_target_datatype = MPI_Type_f2c(*target_datatype);
c_request = MPI_Request_f2c(*request);

rc = mpiPif_MPI_Rget( &jbuf, origin_addr, origin_count, &c_origin_datatype, target_rank, target_disp, target_count, &c_target_datatype, win, &c_request );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_rget */



/* --------------- MPI_Rget_accumulate --------------- */

static int mpiPif_MPI_Rget_accumulate( jmp_buf * base_jbuf, mpip_const_void_t  *origin_addr, int  * origin_count, MPI_Datatype  * origin_datatype, void  *result_addr, int  * result_count, MPI_Datatype  * result_datatype, int  * target_rank, MPI_Aint  * target_disp, int  * target_count, MPI_Datatype  * target_datatype, MPI_Op  * op, MPI_Win  * win, MPI_Request  *request)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Rget_accumulate( origin_addr,  * origin_count,  * origin_datatype, result_addr,  * result_count,  * result_datatype,  * target_rank,  * target_disp,  * target_count,  * target_datatype,  * op,  * win, request);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Rget_accumulate', ");
fprintf(nyaFp, "'arguments': {");
if(origin_addr == NULL) {
    fprintf(nyaFp, "'origin_addr': 0x0");
}
else {
    fprintf(nyaFp, "'origin_addr': %p", origin_addr);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'origin_count': %d", * origin_count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* origin_datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'origin_datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'origin_datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
if(result_addr == NULL) {
    fprintf(nyaFp, "'result_addr': 0x0");
}
else {
    fprintf(nyaFp, "'result_addr': %p", result_addr);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'result_count': %d", * result_count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* result_datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'result_datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'result_datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'target_rank': %d", * target_rank);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'target_disp': %ld", * target_disp);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'target_count': %d", * target_count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* target_datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'target_datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'target_datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'op': '%s'", get_op_name(* op));
fprintf(nyaFp, ", ");
MPI_Win_get_info(* win, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'win': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
if(request == NULL) {
    fprintf(nyaFp, "'request': 0x0");
}
else {
    fprintf(nyaFp, "'request': %p", request);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

PMPI_Type_size(*target_datatype, &tsize);
rmaSize = (double)(tsize * *target_count);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Rget_accumulate");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Rget_accumulate, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Rget_accumulate */



extern int MPI_Rget_accumulate ( mpip_const_void_t *origin_addr, int origin_count, MPI_Datatype origin_datatype, void *result_addr, int result_count, MPI_Datatype result_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, MPI_Request *request )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Rget_accumulate( &jbuf, origin_addr,  & origin_count,  & origin_datatype, result_addr,  & result_count,  & result_datatype,  & target_rank,  & target_disp,  & target_count,  & target_datatype,  & op,  & win, request );

return rc;
} /* MPI_Rget_accumulate */


extern void F77_MPI_RGET_ACCUMULATE(mpip_const_void_t  *origin_addr, int  * origin_count, MPI_Fint  * origin_datatype, void  *result_addr, int  * result_count, MPI_Fint  * result_datatype, int  * target_rank, MPI_Aint  * target_disp, int  * target_count, MPI_Fint  * target_datatype, MPI_Fint  * op, MPI_Win  * win, MPI_Fint  *request , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_origin_datatype;
MPI_Datatype c_result_datatype;
MPI_Datatype c_target_datatype;
MPI_Op c_op;
MPI_Request c_request;

c_origin_datatype = MPI_Type_f2c(*origin_datatype);
c_result_datatype = MPI_Type_f2c(*result_datatype);
c_target_datatype = MPI_Type_f2c(*target_datatype);
c_op = MPI_Op_f2c(*op);
c_request = MPI_Request_f2c(*request);

rc = mpiPif_MPI_Rget_accumulate( &jbuf, origin_addr, origin_count, &c_origin_datatype, result_addr, result_count, &c_result_datatype, target_rank, target_disp, target_count, &c_target_datatype, &c_op, win, &c_request );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_rget_accumulate */



/* --------------- MPI_Rput --------------- */

static int mpiPif_MPI_Rput( jmp_buf * base_jbuf, mpip_const_void_t  *origin_addr, int  * origin_count, MPI_Datatype  * origin_datatype, int  * target_rank, MPI_Aint  * target_disp, int  * target_count, MPI_Datatype  * target_datatype, MPI_Win  * win, MPI_Request  *request)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Rput( origin_addr,  * origin_count,  * origin_datatype,  * target_rank,  * target_disp,  * target_count,  * target_datatype,  * win, request);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Rput', ");
fprintf(nyaFp, "'arguments': {");
if(origin_addr == NULL) {
    fprintf(nyaFp, "'origin_addr': 0x0");
}
else {
    fprintf(nyaFp, "'origin_addr': %p", origin_addr);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'origin_count': %d", * origin_count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* origin_datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'origin_datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'origin_datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'target_rank': %d", * target_rank);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'target_disp': %ld", * target_disp);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'target_count': %d", * target_count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* target_datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'target_datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'target_datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
MPI_Win_get_info(* win, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'win': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
if(request == NULL) {
    fprintf(nyaFp, "'request': 0x0");
}
else {
    fprintf(nyaFp, "'request': %p", request);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

PMPI_Type_size(*origin_datatype, &tsize);
rmaSize = (double)(tsize * *origin_count);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Rput");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Rput, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Rput */



extern int MPI_Rput ( mpip_const_void_t *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win, MPI_Request *request )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Rput( &jbuf, origin_addr,  & origin_count,  & origin_datatype,  & target_rank,  & target_disp,  & target_count,  & target_datatype,  & win, request );

return rc;
} /* MPI_Rput */


extern void F77_MPI_RPUT(mpip_const_void_t  *origin_addr, int  * origin_count, MPI_Fint  * origin_datatype, int  * target_rank, MPI_Aint  * target_disp, int  * target_count, MPI_Fint  * target_datatype, MPI_Win  * win, MPI_Fint  *request , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_origin_datatype;
MPI_Datatype c_target_datatype;
MPI_Request c_request;

c_origin_datatype = MPI_Type_f2c(*origin_datatype);
c_target_datatype = MPI_Type_f2c(*target_datatype);
c_request = MPI_Request_f2c(*request);

rc = mpiPif_MPI_Rput( &jbuf, origin_addr, origin_count, &c_origin_datatype, target_rank, target_disp, target_count, &c_target_datatype, win, &c_request );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_rput */



/* --------------- MPI_Rsend --------------- */

static int mpiPif_MPI_Rsend( jmp_buf * base_jbuf, mpip_const_void_t  *buf, int  * count, MPI_Datatype  * datatype, int  * dest, int  * tag, MPI_Comm  * comm)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Rsend( buf,  * count,  * datatype,  * dest,  * tag,  * comm);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Rsend', ");
fprintf(nyaFp, "'arguments': {");
if(buf == NULL) {
    fprintf(nyaFp, "'buf': 0x0");
}
else {
    fprintf(nyaFp, "'buf': %p", buf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'count': %d", * count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'dest': %d", * dest);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'tag': %d", * tag);
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( *datatype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*datatype, &tsize);
messSize = (double)(tsize * *count);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Rsend");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Rsend, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_pt2pt_stats_report) { mpiPi_update_pt2pt_stats(hndl, mpiPi_MPI_Rsend, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Rsend */



extern int MPI_Rsend ( mpip_const_void_t *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Rsend( &jbuf, buf,  & count,  & datatype,  & dest,  & tag,  & comm );

return rc;
} /* MPI_Rsend */


extern void F77_MPI_RSEND(mpip_const_void_t  *buf, int  * count, MPI_Fint  * datatype, int  * dest, int  * tag, MPI_Fint  * comm , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Comm c_comm;

c_datatype = MPI_Type_f2c(*datatype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Rsend( &jbuf, buf, count, &c_datatype, dest, tag, &c_comm );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_rsend */



/* --------------- MPI_Rsend_init --------------- */

static int mpiPif_MPI_Rsend_init( jmp_buf * base_jbuf, mpip_const_void_t  *buf, int  * count, MPI_Datatype  * datatype, int  * dest, int  * tag, MPI_Comm  * comm, MPI_Request  *request)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Rsend_init( buf,  * count,  * datatype,  * dest,  * tag,  * comm, request);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Rsend_init', ");
fprintf(nyaFp, "'arguments': {");
if(buf == NULL) {
    fprintf(nyaFp, "'buf': 0x0");
}
else {
    fprintf(nyaFp, "'buf': %p", buf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'count': %d", * count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'dest': %d", * dest);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'tag': %d", * tag);
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(request == NULL) {
    fprintf(nyaFp, "'request': 0x0");
}
else {
    fprintf(nyaFp, "'request': %p", request);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Rsend_init");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Rsend_init, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Rsend_init */



extern int MPI_Rsend_init ( mpip_const_void_t *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Rsend_init( &jbuf, buf,  & count,  & datatype,  & dest,  & tag,  & comm, request );

return rc;
} /* MPI_Rsend_init */


extern void F77_MPI_RSEND_INIT(mpip_const_void_t  *buf, int  * count, MPI_Fint  * datatype, int  * dest, int  * tag, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Comm c_comm;
MPI_Request c_request;

c_datatype = MPI_Type_f2c(*datatype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Rsend_init( &jbuf, buf, count, &c_datatype, dest, tag, &c_comm, &c_request );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_rsend_init */



/* --------------- MPI_Scan --------------- */

static int mpiPif_MPI_Scan( jmp_buf * base_jbuf, mpip_const_void_t  *sendbuf, void  *recvbuf, int  * count, MPI_Datatype  * datatype, MPI_Op  * op, MPI_Comm  * comm)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Scan( sendbuf, recvbuf,  * count,  * datatype,  * op,  * comm);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Scan', ");
fprintf(nyaFp, "'arguments': {");
if(sendbuf == NULL) {
    fprintf(nyaFp, "'sendbuf': 0x0");
}
else {
    fprintf(nyaFp, "'sendbuf': %p", sendbuf);
}
fprintf(nyaFp, ", ");
if(recvbuf == NULL) {
    fprintf(nyaFp, "'recvbuf': 0x0");
}
else {
    fprintf(nyaFp, "'recvbuf': %p", recvbuf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'count': %d", * count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'op': '%s'", get_op_name(* op));
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( *datatype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*datatype, &tsize);
messSize = (double)(tsize * *count);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Scan");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Scan, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Scan */



extern int MPI_Scan ( mpip_const_void_t *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Scan( &jbuf, sendbuf, recvbuf,  & count,  & datatype,  & op,  & comm );

return rc;
} /* MPI_Scan */


extern void F77_MPI_SCAN(mpip_const_void_t  *sendbuf, void  *recvbuf, int  * count, MPI_Fint  * datatype, MPI_Fint  * op, MPI_Fint  * comm , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Op c_op;
MPI_Comm c_comm;

c_datatype = MPI_Type_f2c(*datatype);
c_op = MPI_Op_f2c(*op);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Scan( &jbuf, sendbuf, recvbuf, count, &c_datatype, &c_op, &c_comm );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_scan */



/* --------------- MPI_Scatter --------------- */

static int mpiPif_MPI_Scatter( jmp_buf * base_jbuf, mpip_const_void_t  *sendbuf, int  * sendcnt, MPI_Datatype  * sendtype, void  *recvbuf, int  * recvcnt, MPI_Datatype  * recvtype, int  * root, MPI_Comm  * comm)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Scatter( sendbuf,  * sendcnt,  * sendtype, recvbuf,  * recvcnt,  * recvtype,  * root,  * comm);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Scatter', ");
fprintf(nyaFp, "'arguments': {");
if(sendbuf == NULL) {
    fprintf(nyaFp, "'sendbuf': 0x0");
}
else {
    fprintf(nyaFp, "'sendbuf': %p", sendbuf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'sendcnt': %d", * sendcnt);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* sendtype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'sendtype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'sendtype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
if(recvbuf == NULL) {
    fprintf(nyaFp, "'recvbuf': 0x0");
}
else {
    fprintf(nyaFp, "'recvbuf': %p", recvbuf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'recvcnt': %d", * recvcnt);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* recvtype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'recvtype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'recvtype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'root': %d", * root);
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( *sendtype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*sendtype, &tsize);
messSize = (double)(tsize * *sendcnt);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Scatter");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Scatter, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(hndl, mpiPi_MPI_Scatter, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Scatter */



extern int MPI_Scatter ( mpip_const_void_t *sendbuf, int sendcnt, MPI_Datatype sendtype, void *recvbuf, int recvcnt, MPI_Datatype recvtype, int root, MPI_Comm comm )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Scatter( &jbuf, sendbuf,  & sendcnt,  & sendtype, recvbuf,  & recvcnt,  & recvtype,  & root,  & comm );

return rc;
} /* MPI_Scatter */


extern void F77_MPI_SCATTER(mpip_const_void_t  *sendbuf, int  * sendcnt, MPI_Fint  * sendtype, void  *recvbuf, int  * recvcnt, MPI_Fint  * recvtype, int  * root, MPI_Fint  * comm , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_sendtype;
MPI_Datatype c_recvtype;
MPI_Comm c_comm;

c_sendtype = MPI_Type_f2c(*sendtype);
c_recvtype = MPI_Type_f2c(*recvtype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Scatter( &jbuf, sendbuf, sendcnt, &c_sendtype, recvbuf, recvcnt, &c_recvtype, root, &c_comm );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_scatter */



/* --------------- MPI_Scatterv --------------- */

static int mpiPif_MPI_Scatterv( jmp_buf * base_jbuf, mpip_const_void_t  *sendbuf, mpip_const_int_t  *sendcnts, mpip_const_int_t  *displs, MPI_Datatype  * sendtype, void  *recvbuf, int  * recvcnt, MPI_Datatype  * recvtype, int  * root, MPI_Comm  * comm)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Scatterv( sendbuf, sendcnts, displs,  * sendtype, recvbuf,  * recvcnt,  * recvtype,  * root,  * comm);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Scatterv', ");
fprintf(nyaFp, "'arguments': {");
if(sendbuf == NULL) {
    fprintf(nyaFp, "'sendbuf': 0x0");
}
else {
    fprintf(nyaFp, "'sendbuf': %p", sendbuf);
}
fprintf(nyaFp, ", ");
if(sendcnts == NULL) {
    fprintf(nyaFp, "'sendcnts': 0x0");
}
else {
    fprintf(nyaFp, "'sendcnts': %p", sendcnts);
}
fprintf(nyaFp, ", ");
if(displs == NULL) {
    fprintf(nyaFp, "'displs': 0x0");
}
else {
    fprintf(nyaFp, "'displs': %p", displs);
}
fprintf(nyaFp, ", ");
MPI_Type_get_name(* sendtype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'sendtype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'sendtype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
if(recvbuf == NULL) {
    fprintf(nyaFp, "'recvbuf': 0x0");
}
else {
    fprintf(nyaFp, "'recvbuf': %p", recvbuf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'recvcnt': %d", * recvcnt);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* recvtype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'recvtype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'recvtype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'root': %d", * root);
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Scatterv");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Scatterv, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(hndl, mpiPi_MPI_Scatterv, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Scatterv */



extern int MPI_Scatterv ( mpip_const_void_t *sendbuf, mpip_const_int_t *sendcnts, mpip_const_int_t *displs, MPI_Datatype sendtype, void *recvbuf, int recvcnt, MPI_Datatype recvtype, int root, MPI_Comm comm )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Scatterv( &jbuf, sendbuf, sendcnts, displs,  & sendtype, recvbuf,  & recvcnt,  & recvtype,  & root,  & comm );

return rc;
} /* MPI_Scatterv */


extern void F77_MPI_SCATTERV(mpip_const_void_t  *sendbuf, mpip_const_int_t  *sendcnts, mpip_const_int_t  *displs, MPI_Fint  * sendtype, void  *recvbuf, int  * recvcnt, MPI_Fint  * recvtype, int  * root, MPI_Fint  * comm , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_sendtype;
MPI_Datatype c_recvtype;
MPI_Comm c_comm;

c_sendtype = MPI_Type_f2c(*sendtype);
c_recvtype = MPI_Type_f2c(*recvtype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Scatterv( &jbuf, sendbuf, sendcnts, displs, &c_sendtype, recvbuf, recvcnt, &c_recvtype, root, &c_comm );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_scatterv */



/* --------------- MPI_Send --------------- */

static int mpiPif_MPI_Send( jmp_buf * base_jbuf, mpip_const_void_t  *buf, int  * count, MPI_Datatype  * datatype, int  * dest, int  * tag, MPI_Comm  * comm)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Send( buf,  * count,  * datatype,  * dest,  * tag,  * comm);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Send', ");
fprintf(nyaFp, "'arguments': {");
if(buf == NULL) {
    fprintf(nyaFp, "'buf': 0x0");
}
else {
    fprintf(nyaFp, "'buf': %p", buf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'count': %d", * count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'dest': %d", * dest);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'tag': %d", * tag);
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( *datatype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*datatype, &tsize);
messSize = (double)(tsize * *count);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Send");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Send, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_pt2pt_stats_report) { mpiPi_update_pt2pt_stats(hndl, mpiPi_MPI_Send, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Send */



extern int MPI_Send ( mpip_const_void_t *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Send( &jbuf, buf,  & count,  & datatype,  & dest,  & tag,  & comm );

return rc;
} /* MPI_Send */


extern void F77_MPI_SEND(mpip_const_void_t  *buf, int  * count, MPI_Fint  * datatype, int  * dest, int  * tag, MPI_Fint  * comm , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Comm c_comm;

c_datatype = MPI_Type_f2c(*datatype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Send( &jbuf, buf, count, &c_datatype, dest, tag, &c_comm );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_send */



/* --------------- MPI_Send_init --------------- */

static int mpiPif_MPI_Send_init( jmp_buf * base_jbuf, mpip_const_void_t  *buf, int  * count, MPI_Datatype  * datatype, int  * dest, int  * tag, MPI_Comm  * comm, MPI_Request  *request)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Send_init( buf,  * count,  * datatype,  * dest,  * tag,  * comm, request);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Send_init', ");
fprintf(nyaFp, "'arguments': {");
if(buf == NULL) {
    fprintf(nyaFp, "'buf': 0x0");
}
else {
    fprintf(nyaFp, "'buf': %p", buf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'count': %d", * count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'dest': %d", * dest);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'tag': %d", * tag);
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(request == NULL) {
    fprintf(nyaFp, "'request': 0x0");
}
else {
    fprintf(nyaFp, "'request': %p", request);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Send_init");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Send_init, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Send_init */



extern int MPI_Send_init ( mpip_const_void_t *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Send_init( &jbuf, buf,  & count,  & datatype,  & dest,  & tag,  & comm, request );

return rc;
} /* MPI_Send_init */


extern void F77_MPI_SEND_INIT(mpip_const_void_t  *buf, int  * count, MPI_Fint  * datatype, int  * dest, int  * tag, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Comm c_comm;
MPI_Request c_request;

c_datatype = MPI_Type_f2c(*datatype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Send_init( &jbuf, buf, count, &c_datatype, dest, tag, &c_comm, &c_request );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_send_init */



/* --------------- MPI_Sendrecv --------------- */

static int mpiPif_MPI_Sendrecv( jmp_buf * base_jbuf, mpip_const_void_t  *sendbuf, int  * sendcount, MPI_Datatype  * sendtype, int  * dest, int  * sendtag, void  *recvbuf, int  * recvcount, MPI_Datatype  * recvtype, int  * source, int  * recvtag, MPI_Comm  * comm, MPI_Status  *status)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Sendrecv( sendbuf,  * sendcount,  * sendtype,  * dest,  * sendtag, recvbuf,  * recvcount,  * recvtype,  * source,  * recvtag,  * comm, status);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Sendrecv', ");
fprintf(nyaFp, "'arguments': {");
if(sendbuf == NULL) {
    fprintf(nyaFp, "'sendbuf': 0x0");
}
else {
    fprintf(nyaFp, "'sendbuf': %p", sendbuf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'sendcount': %d", * sendcount);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* sendtype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'sendtype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'sendtype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'dest': %d", * dest);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'sendtag': %d", * sendtag);
fprintf(nyaFp, ", ");
if(recvbuf == NULL) {
    fprintf(nyaFp, "'recvbuf': 0x0");
}
else {
    fprintf(nyaFp, "'recvbuf': %p", recvbuf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'recvcount': %d", * recvcount);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* recvtype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'recvtype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'recvtype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'source': %d", * source);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'recvtag': %d", * recvtag);
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(status == NULL) {
    fprintf(nyaFp, "'status': 0x0");
}
else {
    fprintf(nyaFp, "'status': %p", status);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( *sendtype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*sendtype, &tsize);
messSize = (double)(tsize * *sendcount);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Sendrecv");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Sendrecv, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_pt2pt_stats_report) { mpiPi_update_pt2pt_stats(hndl, mpiPi_MPI_Sendrecv, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Sendrecv */



extern int MPI_Sendrecv ( mpip_const_void_t *sendbuf, int sendcount, MPI_Datatype sendtype, int dest, int sendtag, void *recvbuf, int recvcount, MPI_Datatype recvtype, int source, int recvtag, MPI_Comm comm, MPI_Status *status )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Sendrecv( &jbuf, sendbuf,  & sendcount,  & sendtype,  & dest,  & sendtag, recvbuf,  & recvcount,  & recvtype,  & source,  & recvtag,  & comm, status );

return rc;
} /* MPI_Sendrecv */


extern void F77_MPI_SENDRECV(mpip_const_void_t  *sendbuf, int  * sendcount, MPI_Fint  * sendtype, int  * dest, int  * sendtag, void  *recvbuf, int  * recvcount, MPI_Fint  * recvtype, int  * source, int  * recvtag, MPI_Fint  * comm, MPI_Status  *status , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_sendtype;
MPI_Datatype c_recvtype;
MPI_Comm c_comm;

c_sendtype = MPI_Type_f2c(*sendtype);
c_recvtype = MPI_Type_f2c(*recvtype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Sendrecv( &jbuf, sendbuf, sendcount, &c_sendtype, dest, sendtag, recvbuf, recvcount, &c_recvtype, source, recvtag, &c_comm, status );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_sendrecv */



/* --------------- MPI_Sendrecv_replace --------------- */

static int mpiPif_MPI_Sendrecv_replace( jmp_buf * base_jbuf, void  *buf, int  * count, MPI_Datatype  * datatype, int  * dest, int  * sendtag, int  * source, int  * recvtag, MPI_Comm  * comm, MPI_Status  *status)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Sendrecv_replace( buf,  * count,  * datatype,  * dest,  * sendtag,  * source,  * recvtag,  * comm, status);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Sendrecv_replace', ");
fprintf(nyaFp, "'arguments': {");
if(buf == NULL) {
    fprintf(nyaFp, "'buf': 0x0");
}
else {
    fprintf(nyaFp, "'buf': %p", buf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'count': %d", * count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'dest': %d", * dest);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'sendtag': %d", * sendtag);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'source': %d", * source);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'recvtag': %d", * recvtag);
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(status == NULL) {
    fprintf(nyaFp, "'status': 0x0");
}
else {
    fprintf(nyaFp, "'status': %p", status);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( *datatype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*datatype, &tsize);
messSize = (double)(tsize * *count);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Sendrecv_replace");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Sendrecv_replace, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_pt2pt_stats_report) { mpiPi_update_pt2pt_stats(hndl, mpiPi_MPI_Sendrecv_replace, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Sendrecv_replace */



extern int MPI_Sendrecv_replace ( void *buf, int count, MPI_Datatype datatype, int dest, int sendtag, int source, int recvtag, MPI_Comm comm, MPI_Status *status )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Sendrecv_replace( &jbuf, buf,  & count,  & datatype,  & dest,  & sendtag,  & source,  & recvtag,  & comm, status );

return rc;
} /* MPI_Sendrecv_replace */


extern void F77_MPI_SENDRECV_REPLACE(void  *buf, int  * count, MPI_Fint  * datatype, int  * dest, int  * sendtag, int  * source, int  * recvtag, MPI_Fint  * comm, MPI_Status  *status , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Comm c_comm;

c_datatype = MPI_Type_f2c(*datatype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Sendrecv_replace( &jbuf, buf, count, &c_datatype, dest, sendtag, source, recvtag, &c_comm, status );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_sendrecv_replace */



/* --------------- MPI_Ssend --------------- */

static int mpiPif_MPI_Ssend( jmp_buf * base_jbuf, mpip_const_void_t  *buf, int  * count, MPI_Datatype  * datatype, int  * dest, int  * tag, MPI_Comm  * comm)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Ssend( buf,  * count,  * datatype,  * dest,  * tag,  * comm);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Ssend', ");
fprintf(nyaFp, "'arguments': {");
if(buf == NULL) {
    fprintf(nyaFp, "'buf': 0x0");
}
else {
    fprintf(nyaFp, "'buf': %p", buf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'count': %d", * count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'dest': %d", * dest);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'tag': %d", * tag);
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( *datatype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*datatype, &tsize);
messSize = (double)(tsize * *count);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Ssend");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Ssend, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_pt2pt_stats_report) { mpiPi_update_pt2pt_stats(hndl, mpiPi_MPI_Ssend, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Ssend */



extern int MPI_Ssend ( mpip_const_void_t *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Ssend( &jbuf, buf,  & count,  & datatype,  & dest,  & tag,  & comm );

return rc;
} /* MPI_Ssend */


extern void F77_MPI_SSEND(mpip_const_void_t  *buf, int  * count, MPI_Fint  * datatype, int  * dest, int  * tag, MPI_Fint  * comm , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Comm c_comm;

c_datatype = MPI_Type_f2c(*datatype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Ssend( &jbuf, buf, count, &c_datatype, dest, tag, &c_comm );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_ssend */



/* --------------- MPI_Ssend_init --------------- */

static int mpiPif_MPI_Ssend_init( jmp_buf * base_jbuf, mpip_const_void_t  *buf, int  * count, MPI_Datatype  * datatype, int  * dest, int  * tag, MPI_Comm  * comm, MPI_Request  *request)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Ssend_init( buf,  * count,  * datatype,  * dest,  * tag,  * comm, request);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Ssend_init', ");
fprintf(nyaFp, "'arguments': {");
if(buf == NULL) {
    fprintf(nyaFp, "'buf': 0x0");
}
else {
    fprintf(nyaFp, "'buf': %p", buf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'count': %d", * count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'dest': %d", * dest);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'tag': %d", * tag);
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(request == NULL) {
    fprintf(nyaFp, "'request': 0x0");
}
else {
    fprintf(nyaFp, "'request': %p", request);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Ssend_init");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Ssend_init, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Ssend_init */



extern int MPI_Ssend_init ( mpip_const_void_t *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Ssend_init( &jbuf, buf,  & count,  & datatype,  & dest,  & tag,  & comm, request );

return rc;
} /* MPI_Ssend_init */


extern void F77_MPI_SSEND_INIT(mpip_const_void_t  *buf, int  * count, MPI_Fint  * datatype, int  * dest, int  * tag, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Comm c_comm;
MPI_Request c_request;

c_datatype = MPI_Type_f2c(*datatype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Ssend_init( &jbuf, buf, count, &c_datatype, dest, tag, &c_comm, &c_request );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_ssend_init */



/* --------------- MPI_Start --------------- */

static int mpiPif_MPI_Start( jmp_buf * base_jbuf, MPI_Request  *request)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Start( request);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Start', ");
fprintf(nyaFp, "'arguments': {");
if(request == NULL) {
    fprintf(nyaFp, "'request': 0x0");
}
else {
    fprintf(nyaFp, "'request': %p", request);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Start");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Start, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Start */



extern int MPI_Start ( MPI_Request *request )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Start( &jbuf, request );

return rc;
} /* MPI_Start */


extern void F77_MPI_START(MPI_Fint  *request , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Request c_request;

c_request = MPI_Request_f2c(*request);

rc = mpiPif_MPI_Start( &jbuf, &c_request );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_start */



/* --------------- MPI_Startall --------------- */

static int mpiPif_MPI_Startall( jmp_buf * base_jbuf, int  * count, MPI_Request  *array_of_requests)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Startall(  * count, array_of_requests);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Startall', ");
fprintf(nyaFp, "'arguments': {");
fprintf(nyaFp, "'count': %d", * count);
fprintf(nyaFp, ", ");
if(array_of_requests == NULL) {
    fprintf(nyaFp, "'array_of_requests': 0x0");
}
else {
    fprintf(nyaFp, "'array_of_requests': %p", array_of_requests);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Startall");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Startall, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Startall */



extern int MPI_Startall ( int count, MPI_Request *array_of_requests )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Startall( &jbuf,  & count, array_of_requests );

return rc;
} /* MPI_Startall */


extern void F77_MPI_STARTALL(int  * count, MPI_Fint  *array_of_requests , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Request *c_array_of_requests;

c_array_of_requests = (MPI_Request*)malloc(sizeof(MPI_Request)*(*count));
if ( c_array_of_requests == NULL ) mpiPi_abort("Failed to allocate memory in MPI_Startall");
{
  int i; 
  for (i = 0; i < *count; i++) { 
    c_array_of_requests[i] = MPI_Request_f2c(array_of_requests[i]);
  }
}

rc = mpiPif_MPI_Startall( &jbuf, count, c_array_of_requests );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
{
  int i; 
  for (i = 0; i < *count; i++) { 
    array_of_requests[i] = MPI_Request_c2f(c_array_of_requests[i]);
  }
}
}
free(c_array_of_requests);
return;
} /* mpi_startall */



/* --------------- MPI_Test --------------- */

static int mpiPif_MPI_Test( jmp_buf * base_jbuf, MPI_Request  *request, int  *flag, MPI_Status  *status)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Test( request, flag, status);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Test', ");
fprintf(nyaFp, "'arguments': {");
if(request == NULL) {
    fprintf(nyaFp, "'request': 0x0");
}
else {
    fprintf(nyaFp, "'request': %p", request);
}
fprintf(nyaFp, ", ");
if(flag == NULL) {
    fprintf(nyaFp, "'flag': 0x0");
}
else {
    fprintf(nyaFp, "'flag': %p", flag);
}
fprintf(nyaFp, ", ");
if(status == NULL) {
    fprintf(nyaFp, "'status': 0x0");
}
else {
    fprintf(nyaFp, "'status': %p", status);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Test");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Test, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Test */



extern int MPI_Test ( MPI_Request *request, int *flag, MPI_Status *status )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Test( &jbuf, request, flag, status );

return rc;
} /* MPI_Test */


extern void F77_MPI_TEST(MPI_Fint  *request, int  *flag, MPI_Status  *status , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Request c_request;

c_request = MPI_Request_f2c(*request);

rc = mpiPif_MPI_Test( &jbuf, &c_request, flag, status );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_test */



/* --------------- MPI_Testall --------------- */

static int mpiPif_MPI_Testall( jmp_buf * base_jbuf, int  * count, MPI_Request  *array_of_requests, int  *flag, MPI_Status  *array_of_statuses)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Testall(  * count, array_of_requests, flag, array_of_statuses);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Testall', ");
fprintf(nyaFp, "'arguments': {");
fprintf(nyaFp, "'count': %d", * count);
fprintf(nyaFp, ", ");
if(array_of_requests == NULL) {
    fprintf(nyaFp, "'array_of_requests': 0x0");
}
else {
    fprintf(nyaFp, "'array_of_requests': %p", array_of_requests);
}
fprintf(nyaFp, ", ");
if(flag == NULL) {
    fprintf(nyaFp, "'flag': 0x0");
}
else {
    fprintf(nyaFp, "'flag': %p", flag);
}
fprintf(nyaFp, ", ");
if(array_of_statuses == NULL) {
    fprintf(nyaFp, "'array_of_statuses': 0x0");
}
else {
    fprintf(nyaFp, "'array_of_statuses': %p", array_of_statuses);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Testall");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Testall, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Testall */



extern int MPI_Testall ( int count, MPI_Request *array_of_requests, int *flag, MPI_Status *array_of_statuses )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Testall( &jbuf,  & count, array_of_requests, flag, array_of_statuses );

return rc;
} /* MPI_Testall */


extern void F77_MPI_TESTALL(int  * count, MPI_Fint  *array_of_requests, int  *flag, MPI_Status  *array_of_statuses , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Request *c_array_of_requests;

c_array_of_requests = (MPI_Request*)malloc(sizeof(MPI_Request)*(*count));
if ( c_array_of_requests == NULL ) mpiPi_abort("Failed to allocate memory in MPI_Testall");
{
  int i; 
  for (i = 0; i < *count; i++) { 
    c_array_of_requests[i] = MPI_Request_f2c(array_of_requests[i]);
  }
}

rc = mpiPif_MPI_Testall( &jbuf, count, c_array_of_requests, flag, array_of_statuses );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
{
  int i; 
  for (i = 0; i < *count; i++) { 
    array_of_requests[i] = MPI_Request_c2f(c_array_of_requests[i]);
  }
}
}
free(c_array_of_requests);
return;
} /* mpi_testall */



/* --------------- MPI_Testany --------------- */

static int mpiPif_MPI_Testany( jmp_buf * base_jbuf, int  * count, MPI_Request  *array_of_requests, int  *index, int  *flag, MPI_Status  *status)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Testany(  * count, array_of_requests, index, flag, status);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Testany', ");
fprintf(nyaFp, "'arguments': {");
fprintf(nyaFp, "'count': %d", * count);
fprintf(nyaFp, ", ");
if(array_of_requests == NULL) {
    fprintf(nyaFp, "'array_of_requests': 0x0");
}
else {
    fprintf(nyaFp, "'array_of_requests': %p", array_of_requests);
}
fprintf(nyaFp, ", ");
if(index == NULL) {
    fprintf(nyaFp, "'index': 0x0");
}
else {
    fprintf(nyaFp, "'index': %p", index);
}
fprintf(nyaFp, ", ");
if(flag == NULL) {
    fprintf(nyaFp, "'flag': 0x0");
}
else {
    fprintf(nyaFp, "'flag': %p", flag);
}
fprintf(nyaFp, ", ");
if(status == NULL) {
    fprintf(nyaFp, "'status': 0x0");
}
else {
    fprintf(nyaFp, "'status': %p", status);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Testany");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Testany, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Testany */



extern int MPI_Testany ( int count, MPI_Request *array_of_requests, int *index, int *flag, MPI_Status *status )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Testany( &jbuf,  & count, array_of_requests, index, flag, status );

return rc;
} /* MPI_Testany */


extern void F77_MPI_TESTANY(int  * count, MPI_Fint  *array_of_requests, int  *index, int  *flag, MPI_Status  *status , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Request *c_array_of_requests;

c_array_of_requests = (MPI_Request*)malloc(sizeof(MPI_Request)*(*count));
if ( c_array_of_requests == NULL ) mpiPi_abort("Failed to allocate memory in MPI_Testany");
{
  int i; 
  for (i = 0; i < *count; i++) { 
    c_array_of_requests[i] = MPI_Request_f2c(array_of_requests[i]);
  }
}

rc = mpiPif_MPI_Testany( &jbuf, count, c_array_of_requests, index, flag, status );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
array_of_requests[*index] = MPI_Request_c2f(c_array_of_requests[*index]);
if ( *index >= 0 ) (*index)++;
}
free(c_array_of_requests);
return;
} /* mpi_testany */



/* --------------- MPI_Testsome --------------- */

static int mpiPif_MPI_Testsome( jmp_buf * base_jbuf, int  * incount, MPI_Request  *array_of_requests, int  *count, int  *array_of_indices, MPI_Status  *array_of_statuses)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Testsome(  * incount, array_of_requests, count, array_of_indices, array_of_statuses);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Testsome', ");
fprintf(nyaFp, "'arguments': {");
fprintf(nyaFp, "'incount': %d", * incount);
fprintf(nyaFp, ", ");
if(array_of_requests == NULL) {
    fprintf(nyaFp, "'array_of_requests': 0x0");
}
else {
    fprintf(nyaFp, "'array_of_requests': %p", array_of_requests);
}
fprintf(nyaFp, ", ");
if(count == NULL) {
    fprintf(nyaFp, "'count': 0x0");
}
else {
    fprintf(nyaFp, "'count': %p", count);
}
fprintf(nyaFp, ", ");
if(array_of_indices == NULL) {
    fprintf(nyaFp, "'array_of_indices': 0x0");
}
else {
    fprintf(nyaFp, "'array_of_indices': %p", array_of_indices);
}
fprintf(nyaFp, ", ");
if(array_of_statuses == NULL) {
    fprintf(nyaFp, "'array_of_statuses': 0x0");
}
else {
    fprintf(nyaFp, "'array_of_statuses': %p", array_of_statuses);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Testsome");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Testsome, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Testsome */



extern int MPI_Testsome ( int incount, MPI_Request *array_of_requests, int *count, int *array_of_indices, MPI_Status *array_of_statuses )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Testsome( &jbuf,  & incount, array_of_requests, count, array_of_indices, array_of_statuses );

return rc;
} /* MPI_Testsome */


extern void F77_MPI_TESTSOME(int  * incount, MPI_Fint  *array_of_requests, int  *count, int  *array_of_indices, MPI_Status  *array_of_statuses , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Request *c_array_of_requests;

c_array_of_requests = (MPI_Request*)malloc(sizeof(MPI_Request)*(*incount));
if ( c_array_of_requests == NULL ) mpiPi_abort("Failed to allocate memory in MPI_Testsome");
{
  int i; 
  for (i = 0; i < *incount; i++) { 
    c_array_of_requests[i] = MPI_Request_f2c(array_of_requests[i]);
  }
}

rc = mpiPif_MPI_Testsome( &jbuf, incount, c_array_of_requests, count, array_of_indices, array_of_statuses );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
{
  int i; 
  for (i = 0; i < *incount; i++) { 
    array_of_requests[i] = MPI_Request_c2f(c_array_of_requests[i]);
  }
}
{ int i; for ( i = 0; i < *count; i++)  array_of_indices[i]++;}
}
free(c_array_of_requests);
return;
} /* mpi_testsome */



/* --------------- MPI_Topo_test --------------- */

static int mpiPif_MPI_Topo_test( jmp_buf * base_jbuf, MPI_Comm  * comm, int  *top_type)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Topo_test(  * comm, top_type);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Topo_test', ");
fprintf(nyaFp, "'arguments': {");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(top_type == NULL) {
    fprintf(nyaFp, "'top_type': 0x0");
}
else {
    fprintf(nyaFp, "'top_type': %p", top_type);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Topo_test");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Topo_test, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Topo_test */



extern int MPI_Topo_test ( MPI_Comm comm, int *top_type )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Topo_test( &jbuf,  & comm, top_type );

return rc;
} /* MPI_Topo_test */


extern void F77_MPI_TOPO_TEST(MPI_Fint  * comm, int  *top_type , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Topo_test( &jbuf, &c_comm, top_type );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_topo_test */



/* --------------- MPI_Type_commit --------------- */

static int mpiPif_MPI_Type_commit( jmp_buf * base_jbuf, MPI_Datatype  *datatype)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Type_commit( datatype);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Type_commit', ");
fprintf(nyaFp, "'arguments': {");
if(datatype == NULL) {
    fprintf(nyaFp, "'datatype': 0x0");
}
else {
    fprintf(nyaFp, "'datatype': %p", datatype);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Type_commit");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Type_commit, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Type_commit */



extern int MPI_Type_commit ( MPI_Datatype *datatype )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Type_commit( &jbuf, datatype );

return rc;
} /* MPI_Type_commit */


extern void F77_MPI_TYPE_COMMIT(MPI_Fint  *datatype , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;

c_datatype = MPI_Type_f2c(*datatype);

rc = mpiPif_MPI_Type_commit( &jbuf, &c_datatype );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*datatype = MPI_Type_c2f(c_datatype);
}
return;
} /* mpi_type_commit */



/* --------------- MPI_Type_free --------------- */

static int mpiPif_MPI_Type_free( jmp_buf * base_jbuf, MPI_Datatype  *datatype)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Type_free( datatype);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Type_free', ");
fprintf(nyaFp, "'arguments': {");
if(datatype == NULL) {
    fprintf(nyaFp, "'datatype': 0x0");
}
else {
    fprintf(nyaFp, "'datatype': %p", datatype);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Type_free");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Type_free, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Type_free */



extern int MPI_Type_free ( MPI_Datatype *datatype )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Type_free( &jbuf, datatype );

return rc;
} /* MPI_Type_free */


extern void F77_MPI_TYPE_FREE(MPI_Fint  *datatype , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;

c_datatype = MPI_Type_f2c(*datatype);

rc = mpiPif_MPI_Type_free( &jbuf, &c_datatype );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*datatype = MPI_Type_c2f(c_datatype);
}
return;
} /* mpi_type_free */



/* --------------- MPI_Type_get_contents --------------- */

static int mpiPif_MPI_Type_get_contents( jmp_buf * base_jbuf, MPI_Datatype  * datatype, int  * max_integers, int  * max_addresses, int  * max_datatypes, int  *array_of_integers, MPI_Aint  *array_of_addresses, MPI_Datatype  *array_of_datatypes)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Type_get_contents(  * datatype,  * max_integers,  * max_addresses,  * max_datatypes, array_of_integers, array_of_addresses, array_of_datatypes);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Type_get_contents', ");
fprintf(nyaFp, "'arguments': {");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'max_integers': %d", * max_integers);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'max_addresses': %d", * max_addresses);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'max_datatypes': %d", * max_datatypes);
fprintf(nyaFp, ", ");
if(array_of_integers == NULL) {
    fprintf(nyaFp, "'array_of_integers': 0x0");
}
else {
    fprintf(nyaFp, "'array_of_integers': %p", array_of_integers);
}
fprintf(nyaFp, ", ");
if(array_of_addresses == NULL) {
    fprintf(nyaFp, "'array_of_addresses': 0x0");
}
else {
    fprintf(nyaFp, "'array_of_addresses': %p", array_of_addresses);
}
fprintf(nyaFp, ", ");
if(array_of_datatypes == NULL) {
    fprintf(nyaFp, "'array_of_datatypes': 0x0");
}
else {
    fprintf(nyaFp, "'array_of_datatypes': %p", array_of_datatypes);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Type_get_contents");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Type_get_contents, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Type_get_contents */



extern int MPI_Type_get_contents ( MPI_Datatype datatype, int max_integers, int max_addresses, int max_datatypes, int *array_of_integers, MPI_Aint *array_of_addresses, MPI_Datatype *array_of_datatypes )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Type_get_contents( &jbuf,  & datatype,  & max_integers,  & max_addresses,  & max_datatypes, array_of_integers, array_of_addresses, array_of_datatypes );

return rc;
} /* MPI_Type_get_contents */


extern void F77_MPI_TYPE_GET_CONTENTS(MPI_Fint  * datatype, int  * max_integers, int  * max_addresses, int  * max_datatypes, int  *array_of_integers, MPI_Aint  *array_of_addresses, MPI_Fint  *array_of_datatypes , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Datatype *c_array_of_datatypes;

c_array_of_datatypes = (MPI_Datatype*)malloc(sizeof(MPI_Datatype)*(*max_integers));
if ( c_array_of_datatypes == NULL ) mpiPi_abort("Failed to allocate memory in MPI_Type_get_contents");
c_datatype = MPI_Type_f2c(*datatype);

rc = mpiPif_MPI_Type_get_contents( &jbuf, &c_datatype, max_integers, max_addresses, max_datatypes, array_of_integers, array_of_addresses, c_array_of_datatypes );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
{
  int i; 
  for (i = 0; i < *max_integers; i++) { 
    array_of_datatypes[i] = MPI_Type_c2f(c_array_of_datatypes[i]);
  }
}
}
free(c_array_of_datatypes);
return;
} /* mpi_type_get_contents */



/* --------------- MPI_Type_get_envelope --------------- */

static int mpiPif_MPI_Type_get_envelope( jmp_buf * base_jbuf, MPI_Datatype  * datatype, int  *num_integers, int  *num_addresses, int  *num_datatypes, int  *combiner)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Type_get_envelope(  * datatype, num_integers, num_addresses, num_datatypes, combiner);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Type_get_envelope', ");
fprintf(nyaFp, "'arguments': {");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
if(num_integers == NULL) {
    fprintf(nyaFp, "'num_integers': 0x0");
}
else {
    fprintf(nyaFp, "'num_integers': %p", num_integers);
}
fprintf(nyaFp, ", ");
if(num_addresses == NULL) {
    fprintf(nyaFp, "'num_addresses': 0x0");
}
else {
    fprintf(nyaFp, "'num_addresses': %p", num_addresses);
}
fprintf(nyaFp, ", ");
if(num_datatypes == NULL) {
    fprintf(nyaFp, "'num_datatypes': 0x0");
}
else {
    fprintf(nyaFp, "'num_datatypes': %p", num_datatypes);
}
fprintf(nyaFp, ", ");
if(combiner == NULL) {
    fprintf(nyaFp, "'combiner': 0x0");
}
else {
    fprintf(nyaFp, "'combiner': %p", combiner);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Type_get_envelope");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Type_get_envelope, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Type_get_envelope */



extern int MPI_Type_get_envelope ( MPI_Datatype datatype, int *num_integers, int *num_addresses, int *num_datatypes, int *combiner )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Type_get_envelope( &jbuf,  & datatype, num_integers, num_addresses, num_datatypes, combiner );

return rc;
} /* MPI_Type_get_envelope */


extern void F77_MPI_TYPE_GET_ENVELOPE(MPI_Fint  * datatype, int  *num_integers, int  *num_addresses, int  *num_datatypes, int  *combiner , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;

c_datatype = MPI_Type_f2c(*datatype);

rc = mpiPif_MPI_Type_get_envelope( &jbuf, &c_datatype, num_integers, num_addresses, num_datatypes, combiner );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_type_get_envelope */



/* --------------- MPI_Unpack --------------- */

static int mpiPif_MPI_Unpack( jmp_buf * base_jbuf, mpip_const_void_t  *inbuf, int  * insize, int  *position, void  *outbuf, int  * count, MPI_Datatype  * datatype, MPI_Comm  * comm)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Unpack( inbuf,  * insize, position, outbuf,  * count,  * datatype,  * comm);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Unpack', ");
fprintf(nyaFp, "'arguments': {");
if(inbuf == NULL) {
    fprintf(nyaFp, "'inbuf': 0x0");
}
else {
    fprintf(nyaFp, "'inbuf': %p", inbuf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'insize': %d", * insize);
fprintf(nyaFp, ", ");
if(position == NULL) {
    fprintf(nyaFp, "'position': 0x0");
}
else {
    fprintf(nyaFp, "'position': %p", position);
}
fprintf(nyaFp, ", ");
if(outbuf == NULL) {
    fprintf(nyaFp, "'outbuf': 0x0");
}
else {
    fprintf(nyaFp, "'outbuf': %p", outbuf);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'count': %d", * count);
fprintf(nyaFp, ", ");
MPI_Type_get_name(* datatype, nyaBuf, &nyaLength);
if(nyaBuf[0]) {
    fprintf(nyaFp, "'datatype': '%s'", nyaBuf);
}
else {
    fprintf(nyaFp, "'datatype': 'USER_DEFINED'");
}
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Unpack");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Unpack, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Unpack */



extern int MPI_Unpack ( mpip_const_void_t *inbuf, int insize, int *position, void *outbuf, int count, MPI_Datatype datatype, MPI_Comm comm )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Unpack( &jbuf, inbuf,  & insize, position, outbuf,  & count,  & datatype,  & comm );

return rc;
} /* MPI_Unpack */


extern void F77_MPI_UNPACK(mpip_const_void_t  *inbuf, int  * insize, int  *position, void  *outbuf, int  * count, MPI_Fint  * datatype, MPI_Fint  * comm , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Comm c_comm;

c_datatype = MPI_Type_f2c(*datatype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Unpack( &jbuf, inbuf, insize, position, outbuf, count, &c_datatype, &c_comm );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_unpack */



/* --------------- MPI_Wait --------------- */

static int mpiPif_MPI_Wait( jmp_buf * base_jbuf, MPI_Request  *request, MPI_Status  *status)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Wait( request, status);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Wait', ");
fprintf(nyaFp, "'arguments': {");
if(request == NULL) {
    fprintf(nyaFp, "'request': 0x0");
}
else {
    fprintf(nyaFp, "'request': %p", request);
}
fprintf(nyaFp, ", ");
if(status == NULL) {
    fprintf(nyaFp, "'status': 0x0");
}
else {
    fprintf(nyaFp, "'status': %p", status);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Wait");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Wait, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Wait */



extern int MPI_Wait ( MPI_Request *request, MPI_Status *status )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Wait( &jbuf, request, status );

return rc;
} /* MPI_Wait */


extern void F77_MPI_WAIT(MPI_Fint  *request, MPI_Status  *status , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Request c_request;

c_request = MPI_Request_f2c(*request);

rc = mpiPif_MPI_Wait( &jbuf, &c_request, status );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_wait */



/* --------------- MPI_Waitall --------------- */

static int mpiPif_MPI_Waitall( jmp_buf * base_jbuf, int  * count, MPI_Request  *array_of_requests, MPI_Status  *array_of_statuses)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Waitall(  * count, array_of_requests, array_of_statuses);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Waitall', ");
fprintf(nyaFp, "'arguments': {");
fprintf(nyaFp, "'count': %d", * count);
fprintf(nyaFp, ", ");
if(array_of_requests == NULL) {
    fprintf(nyaFp, "'array_of_requests': 0x0");
}
else {
    fprintf(nyaFp, "'array_of_requests': %p", array_of_requests);
}
fprintf(nyaFp, ", ");
if(array_of_statuses == NULL) {
    fprintf(nyaFp, "'array_of_statuses': 0x0");
}
else {
    fprintf(nyaFp, "'array_of_statuses': %p", array_of_statuses);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Waitall");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Waitall, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Waitall */



extern int MPI_Waitall ( int count, MPI_Request *array_of_requests, MPI_Status *array_of_statuses )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Waitall( &jbuf,  & count, array_of_requests, array_of_statuses );

return rc;
} /* MPI_Waitall */


extern void F77_MPI_WAITALL(int  * count, MPI_Fint  *array_of_requests, MPI_Status  *array_of_statuses , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Request *c_array_of_requests;

c_array_of_requests = (MPI_Request*)malloc(sizeof(MPI_Request)*(*count));
if ( c_array_of_requests == NULL ) mpiPi_abort("Failed to allocate memory in MPI_Waitall");
{
  int i; 
  for (i = 0; i < *count; i++) { 
    c_array_of_requests[i] = MPI_Request_f2c(array_of_requests[i]);
  }
}

rc = mpiPif_MPI_Waitall( &jbuf, count, c_array_of_requests, array_of_statuses );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
{
  int i; 
  for (i = 0; i < *count; i++) { 
    array_of_requests[i] = MPI_Request_c2f(c_array_of_requests[i]);
  }
}
}
free(c_array_of_requests);
return;
} /* mpi_waitall */



/* --------------- MPI_Waitany --------------- */

static int mpiPif_MPI_Waitany( jmp_buf * base_jbuf, int  * count, MPI_Request  *array_of_requests, int  *index, MPI_Status  *status)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Waitany(  * count, array_of_requests, index, status);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Waitany', ");
fprintf(nyaFp, "'arguments': {");
fprintf(nyaFp, "'count': %d", * count);
fprintf(nyaFp, ", ");
if(array_of_requests == NULL) {
    fprintf(nyaFp, "'array_of_requests': 0x0");
}
else {
    fprintf(nyaFp, "'array_of_requests': %p", array_of_requests);
}
fprintf(nyaFp, ", ");
if(index == NULL) {
    fprintf(nyaFp, "'index': 0x0");
}
else {
    fprintf(nyaFp, "'index': %p", index);
}
fprintf(nyaFp, ", ");
if(status == NULL) {
    fprintf(nyaFp, "'status': 0x0");
}
else {
    fprintf(nyaFp, "'status': %p", status);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Waitany");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Waitany, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Waitany */



extern int MPI_Waitany ( int count, MPI_Request *array_of_requests, int *index, MPI_Status *status )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Waitany( &jbuf,  & count, array_of_requests, index, status );

return rc;
} /* MPI_Waitany */


extern void F77_MPI_WAITANY(int  * count, MPI_Fint  *array_of_requests, int  *index, MPI_Status  *status , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Request *c_array_of_requests;

c_array_of_requests = (MPI_Request*)malloc(sizeof(MPI_Request)*(*count));
if ( c_array_of_requests == NULL ) mpiPi_abort("Failed to allocate memory in MPI_Waitany");
{
  int i; 
  for (i = 0; i < *count; i++) { 
    c_array_of_requests[i] = MPI_Request_f2c(array_of_requests[i]);
  }
}

rc = mpiPif_MPI_Waitany( &jbuf, count, c_array_of_requests, index, status );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
array_of_requests[*index] = MPI_Request_c2f(c_array_of_requests[*index]);
if ( *index >= 0 ) (*index)++;
}
free(c_array_of_requests);
return;
} /* mpi_waitany */



/* --------------- MPI_Waitsome --------------- */

static int mpiPif_MPI_Waitsome( jmp_buf * base_jbuf, int  * incount, MPI_Request  *array_of_requests, int  *count, int  *array_of_indices, MPI_Status  *array_of_statuses)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Waitsome(  * incount, array_of_requests, count, array_of_indices, array_of_statuses);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Waitsome', ");
fprintf(nyaFp, "'arguments': {");
fprintf(nyaFp, "'incount': %d", * incount);
fprintf(nyaFp, ", ");
if(array_of_requests == NULL) {
    fprintf(nyaFp, "'array_of_requests': 0x0");
}
else {
    fprintf(nyaFp, "'array_of_requests': %p", array_of_requests);
}
fprintf(nyaFp, ", ");
if(count == NULL) {
    fprintf(nyaFp, "'count': 0x0");
}
else {
    fprintf(nyaFp, "'count': %p", count);
}
fprintf(nyaFp, ", ");
if(array_of_indices == NULL) {
    fprintf(nyaFp, "'array_of_indices': 0x0");
}
else {
    fprintf(nyaFp, "'array_of_indices': %p", array_of_indices);
}
fprintf(nyaFp, ", ");
if(array_of_statuses == NULL) {
    fprintf(nyaFp, "'array_of_statuses': 0x0");
}
else {
    fprintf(nyaFp, "'array_of_statuses': %p", array_of_statuses);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Waitsome");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Waitsome, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Waitsome */



extern int MPI_Waitsome ( int incount, MPI_Request *array_of_requests, int *count, int *array_of_indices, MPI_Status *array_of_statuses )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Waitsome( &jbuf,  & incount, array_of_requests, count, array_of_indices, array_of_statuses );

return rc;
} /* MPI_Waitsome */


extern void F77_MPI_WAITSOME(int  * incount, MPI_Fint  *array_of_requests, int  *count, int  *array_of_indices, MPI_Status  *array_of_statuses , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Request *c_array_of_requests;

c_array_of_requests = (MPI_Request*)malloc(sizeof(MPI_Request)*(*incount));
if ( c_array_of_requests == NULL ) mpiPi_abort("Failed to allocate memory in MPI_Waitsome");
{
  int i; 
  for (i = 0; i < *incount; i++) { 
    c_array_of_requests[i] = MPI_Request_f2c(array_of_requests[i]);
  }
}

rc = mpiPif_MPI_Waitsome( &jbuf, incount, c_array_of_requests, count, array_of_indices, array_of_statuses );

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
{
  int i; 
  for (i = 0; i < *incount; i++) { 
    array_of_requests[i] = MPI_Request_c2f(c_array_of_requests[i]);
  }
}
{ int i; for ( i = 0; i < *count; i++)  array_of_indices[i]++;}
}
free(c_array_of_requests);
return;
} /* mpi_waitsome */



/* --------------- MPI_Win_allocate --------------- */

static int mpiPif_MPI_Win_allocate( jmp_buf * base_jbuf, MPI_Aint  * size, int  * disp_unit, MPI_Info  * info, MPI_Comm  * comm, void  *baseptr, MPI_Win  *win)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Win_allocate(  * size,  * disp_unit,  * info,  * comm, baseptr, win);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Win_allocate', ");
fprintf(nyaFp, "'arguments': {");
fprintf(nyaFp, "'size': %ld", * size);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'disp_unit': %d", * disp_unit);
fprintf(nyaFp, ", ");
MPI_Info_get_nkeys(* info, &nyaNKeys);
fprintf(nyaFp, "'info': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(* info, i, nyaKey);
    MPI_Info_get(* info, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(baseptr == NULL) {
    fprintf(nyaFp, "'baseptr': 0x0");
}
else {
    fprintf(nyaFp, "'baseptr': %p", baseptr);
}
fprintf(nyaFp, ", ");
if(win == NULL) {
    fprintf(nyaFp, "'win': 0x0");
}
else {
    fprintf(nyaFp, "'win': %p", win);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_allocate");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Win_allocate, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_allocate */



extern int MPI_Win_allocate ( MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, void *baseptr, MPI_Win *win )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_allocate( &jbuf,  & size,  & disp_unit,  & info,  & comm, baseptr, win );

return rc;
} /* MPI_Win_allocate */


extern void F77_MPI_WIN_ALLOCATE(MPI_Aint  * size, int  * disp_unit, MPI_Fint  * info, MPI_Fint  * comm, void  *baseptr, MPI_Win  *win , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Info c_info;
MPI_Comm c_comm;

c_info = MPI_Info_f2c(*info);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Win_allocate( &jbuf, size, disp_unit, &c_info, &c_comm, baseptr, win );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_allocate */



/* --------------- MPI_Win_allocate_shared --------------- */

static int mpiPif_MPI_Win_allocate_shared( jmp_buf * base_jbuf, MPI_Aint  * size, int  * disp_unit, MPI_Info  * info, MPI_Comm  * comm, void  *baseptr, MPI_Win  *win)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Win_allocate_shared(  * size,  * disp_unit,  * info,  * comm, baseptr, win);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Win_allocate_shared', ");
fprintf(nyaFp, "'arguments': {");
fprintf(nyaFp, "'size': %ld", * size);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'disp_unit': %d", * disp_unit);
fprintf(nyaFp, ", ");
MPI_Info_get_nkeys(* info, &nyaNKeys);
fprintf(nyaFp, "'info': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(* info, i, nyaKey);
    MPI_Info_get(* info, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(baseptr == NULL) {
    fprintf(nyaFp, "'baseptr': 0x0");
}
else {
    fprintf(nyaFp, "'baseptr': %p", baseptr);
}
fprintf(nyaFp, ", ");
if(win == NULL) {
    fprintf(nyaFp, "'win': 0x0");
}
else {
    fprintf(nyaFp, "'win': %p", win);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_allocate_shared");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Win_allocate_shared, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_allocate_shared */



extern int MPI_Win_allocate_shared ( MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, void *baseptr, MPI_Win *win )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_allocate_shared( &jbuf,  & size,  & disp_unit,  & info,  & comm, baseptr, win );

return rc;
} /* MPI_Win_allocate_shared */


extern void F77_MPI_WIN_ALLOCATE_SHARED(MPI_Aint  * size, int  * disp_unit, MPI_Fint  * info, MPI_Fint  * comm, void  *baseptr, MPI_Win  *win , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Info c_info;
MPI_Comm c_comm;

c_info = MPI_Info_f2c(*info);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Win_allocate_shared( &jbuf, size, disp_unit, &c_info, &c_comm, baseptr, win );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_allocate_shared */



/* --------------- MPI_Win_attach --------------- */

static int mpiPif_MPI_Win_attach( jmp_buf * base_jbuf, MPI_Win  * win, void  *base, MPI_Aint  * size)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Win_attach(  * win, base,  * size);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Win_attach', ");
fprintf(nyaFp, "'arguments': {");
MPI_Win_get_info(* win, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'win': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
if(base == NULL) {
    fprintf(nyaFp, "'base': 0x0");
}
else {
    fprintf(nyaFp, "'base': %p", base);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'size': %ld", * size);
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_attach");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Win_attach, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_attach */



extern int MPI_Win_attach ( MPI_Win win, void *base, MPI_Aint size )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_attach( &jbuf,  & win, base,  & size );

return rc;
} /* MPI_Win_attach */


extern void F77_MPI_WIN_ATTACH(MPI_Win  * win, void  *base, MPI_Aint  * size , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Win_attach( &jbuf, win, base, size );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_attach */



/* --------------- MPI_Win_complete --------------- */

static int mpiPif_MPI_Win_complete( jmp_buf * base_jbuf, MPI_Win  * win)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Win_complete(  * win);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Win_complete', ");
fprintf(nyaFp, "'arguments': {");
MPI_Win_get_info(* win, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'win': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_complete");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Win_complete, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_complete */



extern int MPI_Win_complete ( MPI_Win win )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_complete( &jbuf,  & win );

return rc;
} /* MPI_Win_complete */


extern void F77_MPI_WIN_COMPLETE(MPI_Win  * win , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Win_complete( &jbuf, win );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_complete */



/* --------------- MPI_Win_create --------------- */

static int mpiPif_MPI_Win_create( jmp_buf * base_jbuf, void  *base, MPI_Aint  * size, int  * disp_unit, MPI_Info  * info, MPI_Comm  * comm, MPI_Win  *win)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Win_create( base,  * size,  * disp_unit,  * info,  * comm, win);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Win_create', ");
fprintf(nyaFp, "'arguments': {");
if(base == NULL) {
    fprintf(nyaFp, "'base': 0x0");
}
else {
    fprintf(nyaFp, "'base': %p", base);
}
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'size': %ld", * size);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'disp_unit': %d", * disp_unit);
fprintf(nyaFp, ", ");
MPI_Info_get_nkeys(* info, &nyaNKeys);
fprintf(nyaFp, "'info': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(* info, i, nyaKey);
    MPI_Info_get(* info, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(win == NULL) {
    fprintf(nyaFp, "'win': 0x0");
}
else {
    fprintf(nyaFp, "'win': %p", win);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_create");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Win_create, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_create */



extern int MPI_Win_create ( void *base, MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, MPI_Win *win )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_create( &jbuf, base,  & size,  & disp_unit,  & info,  & comm, win );

return rc;
} /* MPI_Win_create */


extern void F77_MPI_WIN_CREATE(void  *base, MPI_Aint  * size, int  * disp_unit, MPI_Fint  * info, MPI_Fint  * comm, MPI_Win  *win , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Info c_info;
MPI_Comm c_comm;

c_info = MPI_Info_f2c(*info);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Win_create( &jbuf, base, size, disp_unit, &c_info, &c_comm, win );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_create */



/* --------------- MPI_Win_create_dynamic --------------- */

static int mpiPif_MPI_Win_create_dynamic( jmp_buf * base_jbuf, MPI_Info  * info, MPI_Comm  * comm, MPI_Win  *win)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Win_create_dynamic(  * info,  * comm, win);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Win_create_dynamic', ");
fprintf(nyaFp, "'arguments': {");
MPI_Info_get_nkeys(* info, &nyaNKeys);
fprintf(nyaFp, "'info': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(* info, i, nyaKey);
    MPI_Info_get(* info, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
MPI_Comm_rank(* comm, &nyaRank);
fprintf(nyaFp, "'comm': %d", nyaRank);
fprintf(nyaFp, ", ");
if(win == NULL) {
    fprintf(nyaFp, "'win': 0x0");
}
else {
    fprintf(nyaFp, "'win': %p", win);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_create_dynamic");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Win_create_dynamic, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_create_dynamic */



extern int MPI_Win_create_dynamic ( MPI_Info info, MPI_Comm comm, MPI_Win *win )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_create_dynamic( &jbuf,  & info,  & comm, win );

return rc;
} /* MPI_Win_create_dynamic */


extern void F77_MPI_WIN_CREATE_DYNAMIC(MPI_Fint  * info, MPI_Fint  * comm, MPI_Win  *win , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Info c_info;
MPI_Comm c_comm;

c_info = MPI_Info_f2c(*info);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Win_create_dynamic( &jbuf, &c_info, &c_comm, win );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_create_dynamic */



/* --------------- MPI_Win_detach --------------- */

static int mpiPif_MPI_Win_detach( jmp_buf * base_jbuf, MPI_Win  * win, mpip_const_void_t  *base)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Win_detach(  * win, base);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Win_detach', ");
fprintf(nyaFp, "'arguments': {");
MPI_Win_get_info(* win, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'win': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
if(base == NULL) {
    fprintf(nyaFp, "'base': 0x0");
}
else {
    fprintf(nyaFp, "'base': %p", base);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_detach");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Win_detach, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_detach */



extern int MPI_Win_detach ( MPI_Win win, mpip_const_void_t *base )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_detach( &jbuf,  & win, base );

return rc;
} /* MPI_Win_detach */


extern void F77_MPI_WIN_DETACH(MPI_Win  * win, mpip_const_void_t  *base , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Win_detach( &jbuf, win, base );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_detach */



/* --------------- MPI_Win_fence --------------- */

static int mpiPif_MPI_Win_fence( jmp_buf * base_jbuf, int  * assert, MPI_Win  * win)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Win_fence(  * assert,  * win);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Win_fence', ");
fprintf(nyaFp, "'arguments': {");
fprintf(nyaFp, "'assert': %d", * assert);
fprintf(nyaFp, ", ");
MPI_Win_get_info(* win, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'win': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_fence");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Win_fence, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_fence */



extern int MPI_Win_fence ( int assert, MPI_Win win )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_fence( &jbuf,  & assert,  & win );

return rc;
} /* MPI_Win_fence */


extern void F77_MPI_WIN_FENCE(int  * assert, MPI_Win  * win , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Win_fence( &jbuf, assert, win );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_fence */



/* --------------- MPI_Win_flush --------------- */

static int mpiPif_MPI_Win_flush( jmp_buf * base_jbuf, int  * rank, MPI_Win  * win)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Win_flush(  * rank,  * win);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Win_flush', ");
fprintf(nyaFp, "'arguments': {");
fprintf(nyaFp, "'rank': %d", * rank);
fprintf(nyaFp, ", ");
MPI_Win_get_info(* win, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'win': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_flush");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Win_flush, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_flush */



extern int MPI_Win_flush ( int rank, MPI_Win win )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_flush( &jbuf,  & rank,  & win );

return rc;
} /* MPI_Win_flush */


extern void F77_MPI_WIN_FLUSH(int  * rank, MPI_Win  * win , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Win_flush( &jbuf, rank, win );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_flush */



/* --------------- MPI_Win_flush_all --------------- */

static int mpiPif_MPI_Win_flush_all( jmp_buf * base_jbuf, MPI_Win  * win)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Win_flush_all(  * win);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Win_flush_all', ");
fprintf(nyaFp, "'arguments': {");
MPI_Win_get_info(* win, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'win': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_flush_all");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Win_flush_all, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_flush_all */



extern int MPI_Win_flush_all ( MPI_Win win )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_flush_all( &jbuf,  & win );

return rc;
} /* MPI_Win_flush_all */


extern void F77_MPI_WIN_FLUSH_ALL(MPI_Win  * win , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Win_flush_all( &jbuf, win );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_flush_all */



/* --------------- MPI_Win_flush_local --------------- */

static int mpiPif_MPI_Win_flush_local( jmp_buf * base_jbuf, int  * rank, MPI_Win  * win)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Win_flush_local(  * rank,  * win);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Win_flush_local', ");
fprintf(nyaFp, "'arguments': {");
fprintf(nyaFp, "'rank': %d", * rank);
fprintf(nyaFp, ", ");
MPI_Win_get_info(* win, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'win': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_flush_local");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Win_flush_local, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_flush_local */



extern int MPI_Win_flush_local ( int rank, MPI_Win win )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_flush_local( &jbuf,  & rank,  & win );

return rc;
} /* MPI_Win_flush_local */


extern void F77_MPI_WIN_FLUSH_LOCAL(int  * rank, MPI_Win  * win , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Win_flush_local( &jbuf, rank, win );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_flush_local */



/* --------------- MPI_Win_flush_local_all --------------- */

static int mpiPif_MPI_Win_flush_local_all( jmp_buf * base_jbuf, MPI_Win  * win)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Win_flush_local_all(  * win);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Win_flush_local_all', ");
fprintf(nyaFp, "'arguments': {");
MPI_Win_get_info(* win, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'win': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_flush_local_all");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Win_flush_local_all, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_flush_local_all */



extern int MPI_Win_flush_local_all ( MPI_Win win )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_flush_local_all( &jbuf,  & win );

return rc;
} /* MPI_Win_flush_local_all */


extern void F77_MPI_WIN_FLUSH_LOCAL_ALL(MPI_Win  * win , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Win_flush_local_all( &jbuf, win );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_flush_local_all */



/* --------------- MPI_Win_free --------------- */

static int mpiPif_MPI_Win_free( jmp_buf * base_jbuf, MPI_Win  *win)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Win_free( win);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Win_free', ");
fprintf(nyaFp, "'arguments': {");
if(win == NULL) {
    fprintf(nyaFp, "'win': 0x0");
}
else {
    fprintf(nyaFp, "'win': %p", win);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_free");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Win_free, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_free */



extern int MPI_Win_free ( MPI_Win *win )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_free( &jbuf, win );

return rc;
} /* MPI_Win_free */


extern void F77_MPI_WIN_FREE(MPI_Win  *win , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Win_free( &jbuf, win );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_free */



/* --------------- MPI_Win_get_group --------------- */

static int mpiPif_MPI_Win_get_group( jmp_buf * base_jbuf, MPI_Win  * win, MPI_Group  *group)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Win_get_group(  * win, group);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Win_get_group', ");
fprintf(nyaFp, "'arguments': {");
MPI_Win_get_info(* win, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'win': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
if(group == NULL) {
    fprintf(nyaFp, "'group': 0x0");
}
else {
    fprintf(nyaFp, "'group': %p", group);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_get_group");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Win_get_group, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_get_group */



extern int MPI_Win_get_group ( MPI_Win win, MPI_Group *group )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_get_group( &jbuf,  & win, group );

return rc;
} /* MPI_Win_get_group */


extern void F77_MPI_WIN_GET_GROUP(MPI_Win  * win, MPI_Fint  *group , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Group c_group;

c_group = MPI_Group_f2c(*group);

rc = mpiPif_MPI_Win_get_group( &jbuf, win, &c_group );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_get_group */



/* --------------- MPI_Win_get_info --------------- */

static int mpiPif_MPI_Win_get_info( jmp_buf * base_jbuf, MPI_Win  * win, MPI_Info  *info_used)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Win_get_info(  * win, info_used);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Win_get_info', ");
fprintf(nyaFp, "'arguments': {");
MPI_Win_get_info(* win, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'win': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
if(info_used == NULL) {
    fprintf(nyaFp, "'info_used': 0x0");
}
else {
    fprintf(nyaFp, "'info_used': %p", info_used);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_get_info");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Win_get_info, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_get_info */



extern int MPI_Win_get_info ( MPI_Win win, MPI_Info *info_used )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_get_info( &jbuf,  & win, info_used );

return rc;
} /* MPI_Win_get_info */


extern void F77_MPI_WIN_GET_INFO(MPI_Win  * win, MPI_Fint  *info_used , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Info c_info_used;

c_info_used = MPI_Info_f2c(*info_used);

rc = mpiPif_MPI_Win_get_info( &jbuf, win, &c_info_used );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_get_info */



/* --------------- MPI_Win_lock --------------- */

static int mpiPif_MPI_Win_lock( jmp_buf * base_jbuf, int  * lock_type, int  * rank, int  * assert, MPI_Win  * win)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Win_lock(  * lock_type,  * rank,  * assert,  * win);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Win_lock', ");
fprintf(nyaFp, "'arguments': {");
fprintf(nyaFp, "'lock_type': %d", * lock_type);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'rank': %d", * rank);
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'assert': %d", * assert);
fprintf(nyaFp, ", ");
MPI_Win_get_info(* win, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'win': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_lock");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Win_lock, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_lock */



extern int MPI_Win_lock ( int lock_type, int rank, int assert, MPI_Win win )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_lock( &jbuf,  & lock_type,  & rank,  & assert,  & win );

return rc;
} /* MPI_Win_lock */


extern void F77_MPI_WIN_LOCK(int  * lock_type, int  * rank, int  * assert, MPI_Win  * win , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Win_lock( &jbuf, lock_type, rank, assert, win );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_lock */



/* --------------- MPI_Win_lock_all --------------- */

static int mpiPif_MPI_Win_lock_all( jmp_buf * base_jbuf, int  * assert, MPI_Win  * win)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Win_lock_all(  * assert,  * win);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Win_lock_all', ");
fprintf(nyaFp, "'arguments': {");
fprintf(nyaFp, "'assert': %d", * assert);
fprintf(nyaFp, ", ");
MPI_Win_get_info(* win, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'win': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_lock_all");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Win_lock_all, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_lock_all */



extern int MPI_Win_lock_all ( int assert, MPI_Win win )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_lock_all( &jbuf,  & assert,  & win );

return rc;
} /* MPI_Win_lock_all */


extern void F77_MPI_WIN_LOCK_ALL(int  * assert, MPI_Win  * win , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Win_lock_all( &jbuf, assert, win );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_lock_all */



/* --------------- MPI_Win_post --------------- */

static int mpiPif_MPI_Win_post( jmp_buf * base_jbuf, MPI_Group  * group, int  * assert, MPI_Win  * win)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Win_post(  * group,  * assert,  * win);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Win_post', ");
fprintf(nyaFp, "'arguments': {");
MPI_Group_size(* group, &nyaGroupSize);MPI_Group_rank(* group, &nyaGroupRank);fprintf(nyaFp, "'group': {");
fprintf(nyaFp, "'group_size': %d, ", nyaGroupSize);
fprintf(nyaFp, "'group_rank': %d", nyaGroupRank);
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'assert': %d", * assert);
fprintf(nyaFp, ", ");
MPI_Win_get_info(* win, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'win': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_post");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Win_post, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_post */



extern int MPI_Win_post ( MPI_Group group, int assert, MPI_Win win )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_post( &jbuf,  & group,  & assert,  & win );

return rc;
} /* MPI_Win_post */


extern void F77_MPI_WIN_POST(MPI_Fint  * group, int  * assert, MPI_Win  * win , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Group c_group;

c_group = MPI_Group_f2c(*group);

rc = mpiPif_MPI_Win_post( &jbuf, &c_group, assert, win );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_post */



/* --------------- MPI_Win_set_info --------------- */

static int mpiPif_MPI_Win_set_info( jmp_buf * base_jbuf, MPI_Win  * win, MPI_Info  * info)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Win_set_info(  * win,  * info);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Win_set_info', ");
fprintf(nyaFp, "'arguments': {");
MPI_Win_get_info(* win, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'win': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
MPI_Info_get_nkeys(* info, &nyaNKeys);
fprintf(nyaFp, "'info': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(* info, i, nyaKey);
    MPI_Info_get(* info, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_set_info");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Win_set_info, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_set_info */



extern int MPI_Win_set_info ( MPI_Win win, MPI_Info info )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_set_info( &jbuf,  & win,  & info );

return rc;
} /* MPI_Win_set_info */


extern void F77_MPI_WIN_SET_INFO(MPI_Win  * win, MPI_Fint  * info , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Info c_info;

c_info = MPI_Info_f2c(*info);

rc = mpiPif_MPI_Win_set_info( &jbuf, win, &c_info );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_set_info */



/* --------------- MPI_Win_shared_query --------------- */

static int mpiPif_MPI_Win_shared_query( jmp_buf * base_jbuf, MPI_Win  * win, int  * rank, MPI_Aint  *size, int  *disp_unit, void  *baseptr)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Win_shared_query(  * win,  * rank, size, disp_unit, baseptr);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Win_shared_query', ");
fprintf(nyaFp, "'arguments': {");
MPI_Win_get_info(* win, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'win': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'rank': %d", * rank);
fprintf(nyaFp, ", ");
if(size == NULL) {
    fprintf(nyaFp, "'size': 0x0");
}
else {
    fprintf(nyaFp, "'size': %p", size);
}
fprintf(nyaFp, ", ");
if(disp_unit == NULL) {
    fprintf(nyaFp, "'disp_unit': 0x0");
}
else {
    fprintf(nyaFp, "'disp_unit': %p", disp_unit);
}
fprintf(nyaFp, ", ");
if(baseptr == NULL) {
    fprintf(nyaFp, "'baseptr': 0x0");
}
else {
    fprintf(nyaFp, "'baseptr': %p", baseptr);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_shared_query");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Win_shared_query, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_shared_query */



extern int MPI_Win_shared_query ( MPI_Win win, int rank, MPI_Aint *size, int *disp_unit, void *baseptr)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_shared_query( &jbuf,  & win,  & rank, size, disp_unit, baseptr );

return rc;
} /* MPI_Win_shared_query */


extern void F77_MPI_WIN_SHARED_QUERY(MPI_Win  * win, int  * rank, MPI_Aint  *size, int  *disp_unit, void  *baseptr , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Win_shared_query( &jbuf, win, rank, size, disp_unit, baseptr );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_shared_query */



/* --------------- MPI_Win_start --------------- */

static int mpiPif_MPI_Win_start( jmp_buf * base_jbuf, MPI_Group  * group, int  * assert, MPI_Win  * win)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Win_start(  * group,  * assert,  * win);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Win_start', ");
fprintf(nyaFp, "'arguments': {");
MPI_Group_size(* group, &nyaGroupSize);MPI_Group_rank(* group, &nyaGroupRank);fprintf(nyaFp, "'group': {");
fprintf(nyaFp, "'group_size': %d, ", nyaGroupSize);
fprintf(nyaFp, "'group_rank': %d", nyaGroupRank);
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
fprintf(nyaFp, "'assert': %d", * assert);
fprintf(nyaFp, ", ");
MPI_Win_get_info(* win, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'win': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_start");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Win_start, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_start */



extern int MPI_Win_start ( MPI_Group group, int assert, MPI_Win win )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_start( &jbuf,  & group,  & assert,  & win );

return rc;
} /* MPI_Win_start */


extern void F77_MPI_WIN_START(MPI_Fint  * group, int  * assert, MPI_Win  * win , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;
MPI_Group c_group;

c_group = MPI_Group_f2c(*group);

rc = mpiPif_MPI_Win_start( &jbuf, &c_group, assert, win );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_start */



/* --------------- MPI_Win_sync --------------- */

static int mpiPif_MPI_Win_sync( jmp_buf * base_jbuf, MPI_Win  * win)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Win_sync(  * win);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Win_sync', ");
fprintf(nyaFp, "'arguments': {");
MPI_Win_get_info(* win, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'win': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_sync");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Win_sync, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_sync */



extern int MPI_Win_sync ( MPI_Win win )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_sync( &jbuf,  & win );

return rc;
} /* MPI_Win_sync */


extern void F77_MPI_WIN_SYNC(MPI_Win  * win , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Win_sync( &jbuf, win );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_sync */



/* --------------- MPI_Win_test --------------- */

static int mpiPif_MPI_Win_test( jmp_buf * base_jbuf, MPI_Win  * win, int  *flag)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Win_test(  * win, flag);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Win_test', ");
fprintf(nyaFp, "'arguments': {");
MPI_Win_get_info(* win, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'win': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, ", ");
if(flag == NULL) {
    fprintf(nyaFp, "'flag': 0x0");
}
else {
    fprintf(nyaFp, "'flag': %p", flag);
}
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_test");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Win_test, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_test */



extern int MPI_Win_test ( MPI_Win win, int *flag)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_test( &jbuf,  & win, flag );

return rc;
} /* MPI_Win_test */


extern void F77_MPI_WIN_TEST(MPI_Win  * win, int  *flag , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Win_test( &jbuf, win, flag );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_test */



/* --------------- MPI_Win_unlock --------------- */

static int mpiPif_MPI_Win_unlock( jmp_buf * base_jbuf, int  * rank, MPI_Win  * win)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Win_unlock(  * rank,  * win);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Win_unlock', ");
fprintf(nyaFp, "'arguments': {");
fprintf(nyaFp, "'rank': %d", * rank);
fprintf(nyaFp, ", ");
MPI_Win_get_info(* win, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'win': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_unlock");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Win_unlock, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_unlock */



extern int MPI_Win_unlock ( int rank, MPI_Win win )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_unlock( &jbuf,  & rank,  & win );

return rc;
} /* MPI_Win_unlock */


extern void F77_MPI_WIN_UNLOCK(int  * rank, MPI_Win  * win , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Win_unlock( &jbuf, rank, win );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_unlock */



/* --------------- MPI_Win_unlock_all --------------- */

static int mpiPif_MPI_Win_unlock_all( jmp_buf * base_jbuf, MPI_Win  * win)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Win_unlock_all(  * win);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Win_unlock_all', ");
fprintf(nyaFp, "'arguments': {");
MPI_Win_get_info(* win, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'win': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_unlock_all");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Win_unlock_all, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_unlock_all */



extern int MPI_Win_unlock_all ( MPI_Win win )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_unlock_all( &jbuf,  & win );

return rc;
} /* MPI_Win_unlock_all */


extern void F77_MPI_WIN_UNLOCK_ALL(MPI_Win  * win , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Win_unlock_all( &jbuf, win );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_unlock_all */



/* --------------- MPI_Win_wait --------------- */

static int mpiPif_MPI_Win_wait( jmp_buf * base_jbuf, MPI_Win  * win)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };
  mpiPi_mt_stat_tls_t *hndl;

  hndl = mpiPi_stats_mt_gettls(&mpiPi.task_stats);

if (mpiPi_stats_mt_is_on(hndl)) {
mpiPi_GETTIME (&start);
if ( mpiPi.reportStackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, mpiPi.fullStackDepth);
}

mpiPi_stats_mt_enter(hndl);

rc = PMPI_Win_wait(  * win);

mpiPi_stats_mt_exit(hndl);
if (mpiPi_stats_mt_is_on(hndl)) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);


FILE * nyaFp;
char nyaFileName[256];
int nyaRank;
MPI_Comm_rank(MPI_COMM_WORLD, &nyaRank);
sprintf(nyaFileName, "trace/trace_%d", nyaRank);
if(!nyaFlags[nyaRank]) {
    nyaFp = fopen(nyaFileName, "w");
    fprintf(nyaFp, "[\n");
    fprintf(nyaFp, "    {");
}
else {
    nyaFp = fopen(nyaFileName, "r+");
    fseek(nyaFp, -2, SEEK_END);
    fprintf(nyaFp, ",\n");
    fprintf(nyaFp, "    {");
}
nyaFlags[nyaRank] ++;

char nyaBuf[256];
MPI_Info nyaInfo;
int nyaLength;
int nyaFlags;
int nyaNKeys;
char nyaKey[256];
char nyaValue[256];
int nyaGroupRank;
int nyaGroupSize;
fprintf(nyaFp, "'function': 'MPI_Win_wait', ");
fprintf(nyaFp, "'arguments': {");
MPI_Win_get_info(* win, &nyaInfo);
MPI_Info_get_nkeys(nyaInfo, &nyaNKeys);
fprintf(nyaFp, "'win': {");
for(int i = 0; i < nyaNKeys; i ++) {    MPI_Info_get_nthkey(nyaInfo, i, nyaKey);
    MPI_Info_get(nyaInfo, nyaKey, MPI_MAX_INFO_VAL, nyaValue, &nyaFlags);
    if(i != nyaNKeys - 1) {
        fprintf(nyaFp, "'%s': '%s', ", nyaKey, nyaValue);
    }
    else {
        fprintf(nyaFp, "'%s': '%s'", nyaKey, nyaValue);
    }
}
fprintf(nyaFp, "}");
fprintf(nyaFp, "}");

fprintf(nyaFp, "}\n");
fprintf(nyaFp, "]");
fflush(nyaFp);
fclose(nyaFp);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_wait");
else
  mpiPi_update_callsite_stats(hndl, mpiPi_MPI_Win_wait, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_wait */



extern int MPI_Win_wait ( MPI_Win win )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_wait( &jbuf,  & win );

return rc;
} /* MPI_Win_wait */


extern void F77_MPI_WIN_WAIT(MPI_Win  * win , MPI_Fint *ierr) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Win_wait( &jbuf, win );

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_wait */


/* eof */
