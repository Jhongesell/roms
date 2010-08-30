#!/bin/csh
# @ job_type		= parallel
# @ environment		= COPY_ALL;MP_EUILIB=us
# @ job_name		= regtest.$(jobid)
# @ output		= regtest_out
# @ error		= regtest_err
# @ network.MPI		= csss,shared,us
# @ node_usage		= shared
# @ checkpoint		= no
# @ wall_clock_limit	= 21600
# @ node		= 1
# @ total_tasks		= 1
# @ class		= share
# @ ja_report		= yes
# @ queue

cd /ptmp/gill/restart/WRFV2/test/em_b_wave

cp namelist.input1 namelist.input
poe wrf.exe
mkdir 12h_1p
mv rsl* wrfo* 12h_1p

rm wrfr*
cp namelist.input2 namelist.input
poe wrf.exe
mkdir 6h_1p
mv rsl* wrfo* wrfr* 6h_1p

cp namelist.input3 namelist.input
ln -sf 6h_1p/wrfr* .
poe wrf.exe
mkdir next6h_1p
mv rsl* wrfo* next6h_1p
rm wrfr*