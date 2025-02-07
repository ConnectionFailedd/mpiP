#
#  Check.mak.  Generated from Check.mak.in by configure.
#
#  Make targets for dejagnu evaluation of test codes
#
#  $Id$
#

# Look for a local version of DejaGnu, otherwise use one in the path
RUNTEST = `if test -f $(top_srcdir)/../dejagnu/runtest; then \
	      echo $(top_srcdir) ../dejagnu/runtest; \
	   else \
	      echo runtest; \
	   fi`
	
# The flags to pass to runtest
RUNTESTFLAGS =
TEST = 	
# Execute the tests 
check: site.exp ${SHARED_C_TARGET} test
	DEJAGNU="./config/testing.exp" $(RUNTEST) $(RUNTESTFLAGS) \
	--tool testing --srcdir . $(TEST)
	
FAST_TEST=1-hot-potato
check1: site.exp ${SHARED_C_TARGET} test
	DEJAGNU="./config/testing.exp" $(RUNTEST) $(RUNTESTFLAGS) \
	--tool testing --srcdir . ${FAST_TEST}.exp
	
# Make the local config file
site.exp: ./config.status Makefile
	@echo "Making a new config file..."
	-@rm -f ./tmp?
	@touch site.exp
	
	-@mv site.exp site.bak
	@echo "## these variables are automatically\
	 generated by make ##" > ./tmp0
	@echo "# Do not edit here. If you wish to\
	 override these values" >> ./tmp0
	@echo "# add them to the last section" >> ./tmp0
	@echo "set host_os linux-gnu" >> ./tmp0
	@echo "set host_alias unreliable" >> ./tmp0
	@echo "set host_cpu x86_64" >> ./tmp0
	@echo "set host_vendor pc" >> ./tmp0
	@echo "set target_os linux-gnu" >> ./tmp0
	@echo "set target_alias " >> ./tmp0
	@echo "set target_cpu x86_64" >> ./tmp0
	@echo "set target_vendor pc" >> ./tmp0
	@echo "set host_triplet x86_64-pc-linux-gnu" >> ./tmp0
	@echo "set target_triplet x86_64-pc-linux-gnu">>./tmp0
	@echo "set tool binutils" >> ./tmp0
	@echo "set srcdir ." >> ./tmp0
	@echo "set objdir `pwd`" >> ./tmp0
	@echo "set launch mpirun" >> ./tmp0
	@echo "## All variables above are generated by\
	configure. Do Not Edit ##" >> ./tmp0
	@cat ./tmp0 > site.exp
	@sed < site.bak \
	-e '1,/^## All variables above are.*##/ d' \
	>> site.exp
	-@rm -f ./tmp?
##### EOF
