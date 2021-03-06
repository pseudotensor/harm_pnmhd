// compile using make -f makefile where makefile can be makefile or makefile.pp or makefile.ncsa, the first being the normal program, the second being the postprocess program, the 3rd the ncsa version of the normal program

/* Notes:
When memory is allocated for variables of size N I add the pointer address by NBND so the memory the pointer points to can be addressed with the index list: -NBND..-1 , N+1..N+NBND for Boundary zones and 0..N for active zones.

BE CAREFUL with macros, always add parethesis around non-singular defines in case used later with multiplations, etc.

To start mpich run, first do:

ssh-agent /bin/bash
ssh-add 

then do:

mpirun -np 4 ./twod

4 cpus using mpich:

rm nohup.out ; nohup sh -c 'mpirun -np 4 /usr/bin/time -v ./twod > 0_o.out' &

2 cpus using mpich:

rm nohup.out ; nohup sh -c 'mpirun -np 2 /usr/bin/time -v ./twod > 0_o.out' &


2 rainman cpus:
rm nohup.out ; nohup sh -c 'mpirun -machinefile /usr/local/share/rainman2.1 -np 2 ./twod > 0_o.out' &

2 photon cpus:
rm nohup.out ; nohup sh -c 'mpirun -machinefile /usr/local/share/photon2.1 -np 2 ./twod > 0_o.out' &

alphadog + wiseguy
rm nohup.out ; nohup sh -c 'mpirun -machinefile /usr/local/share/wisealpha.1 -np 2 ./twod > 0_o.out' &

1 processor:

rm nohup.out ; nohup sh -c  '/usr/bin/time -v ./twod > 0_o.out' &


Use program "nm" to list objects and symbols, or use objdump -axfhp 

A // MARK in the code means currently being tested as a modification
A // PRECISION in the code means there could be a precision problem(addition machine precision error)

*/

/*
  Generally, switches that are performance related are here, while others are in init with variable complements for flexibility during runtime.

  Not everything is in here so can compile quicker on simple changes.

*/

#include <errno.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//#include "nrutil.h"

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// whether in post processing mode or not
#define POSTPROC 0

// whether running at NCSA computers(SGI currently, or linux cluster)
// currently just forces DATADIR to local directory(needed for batch runs)
#define NCSA 0

#define LINUXCLUSTER 1 // fix for stupid pgCC compiler(uses extern-OMITTED method instead of COMMON-name method)

// whether doing a performance test(see: perftest.c)
#define PERFTEST 0
// number of wallseconds per perf run(see: main.c)
#define PERFWALLTIME 30
// 1 linux cluster cpu
//#define ZCPSESTIMATE (50000)
// 25 linux cluster cpu(550Mhz Xeon's connected via Myrinet)
//#define ZCPSESTIMATE (1250000)
// 36 linux cluster cpu(550Mhz Xeon's connected via Myrinet)
//#define ZCPSESTIMATE (1800000)
// 64 linux cluster cpu(550Mhz Xeon's connected via Myrinet)
//#define ZCPSESTIMATE (3200000)
// 121 linux cluster cpu(550Mhz Xeon's connected via Myrinet)
//#define ZCPSESTIMATE (6050000)
// photon MHD for one cpu alone
//#define ZCPSESTIMATE (265000)
// rainman MHD for one cpu alone
//#define ZCPSESTIMATE (220000)
// sgi r10000 for one cpu alone(195Mhz)
#define ZCPSESTIMATE (80000)
// 4cpu mpigm
//#define ZCPSESTIMATE (800000)
// 4cpu r10000
//#define ZCPSESTIMATE (343000)
// 9cpu r10000
//#define ZCPSESTIMATE (745000)
// 16cpu r10000
//#define ZCPSESTIMATE (1325000)
// 25cpu r10000
//#define ZCPSESTIMATE (1200000)
// 36cpu r10000
//#define ZCPSESTIMATE (1700000)
// 49cpu r10000
//#define ZCPSESTIMATE (4021000)
// 64 r10000's 64x64 tile
//#define ZCPSESTIMATE (4309000)
// 121 r10000's
//#define ZCPSESTIMATE (10943000)
// 256 r10000's
//#define ZCPSESTIMATE (20000000)

// whether to use MPI
// must change in makefile too!
#if(POSTPROC==0)
#define USEMPI 1 // choice
#else
#define USEMPI 0 // always 0
#endif

// whether to use MPI over GM
// must change in makefile too!
// This forces no forks to be called.  Can be used for non-gm too
#if(USEMPI==1)
#include "mpi.h"
#define USEGM 1 // choice
#else
#define USEGM 0 // always 0, can't have GM without MPI
#endif

#define COMPDIM 2 // how many computational dimensions(bounded directions)


// Under MPI use ./math/mpichmcpusgood.nb to get per cpu size and distribution that's optimal.  Too messy of an equation to do PER CPU to minimize transfered elements on NCPUX1
#if(POSTPROC==0)
//MARK
// grid size PER CPU
#define N1 512 // must be even for totally general consistency
#define N2 512 // must be even for totally general consistency
#define N3 1
#else
#define N1 5 // should be total size, or make small for postproc.h hack(combine only)
#define N2 5 // should be total size
#define N3 1
#endif

/* NBIG is bigger of N1 and N2 and N3 */
#define NBIG1 ((N1>N2) ? N1 : N2)
#define NBIG  ((NBIG1>N3) ? NBIG1 : N3)

#if(COMPDIM==3)
#define CPUGEOMPICK (0) // no choice
#else
#define CPUGEOMPICK (1)
// 0: computer pick geometry: see init_MPI, global problem size artibtrary
// 1: user pick geometry: make sure NCPUX1*NCPUX2=numprocs(i.e. mpirun -np $numprocs), assumes fixed global problem size wanted
// can run ./testmcpu.c which is same as init_optimalmpi() to check before running
#endif

#define CPUTXT ".%04d" // format for cpu data files

// only applies if CPUGEOMPICK==1, otherwise computer will determine
// only applies if numproc>1 and mpi is used
// MARK
#define NCPUX1 (2)
#define NCPUX2 (2)
#define NCPUX3 (1)

// whether to use TVDLF method
#define TVDLF 0
// only currently works for cartesian grid and periodic/outflow conditions

// make sure has trailing /
#if(POSTPROC==0)

#if(NCSA==1)
#define DATADIR "./"
#else
//#define DATADIR "./"
#define DATADIR "/us4/jon/mhdv9test1/"
#endif

#else
#define DATADIR "./"
#endif

#define CHECKCONT 1 // 1: check if user wants to continue run 0: don't

// size of data type used for all floats
// you must change all % f's to % lf's in global.h when using doubles
// you must change all % lf's to % f's in global.h when using floats!
#define FLOATTYPE 1 // 0: float 1: double (normal non-sensitive or performance critical datatypes)
#define SENSITIVE 1 // 0: float 1: double (non-perf critical or sensitive data types)
// need not change below datatype stuff
#if(FLOATTYPE==0)
#define FTYPE float
#define MPI_FTYPE MPI_FLOAT
#else
#define FTYPE double
#define MPI_FTYPE MPI_DOUBLE
#endif
#if(SENSITIVE==0) // for sensitive counters
#define SFTYPE float
#define MPI_SFTYPE MPI_FLOAT
#else
#define SFTYPE double
#define MPI_SFTYPE MPI_DOUBLE
#endif


// should be no smaller(and a bit greater) than machine precision!(i.e. more precisely, the round off of 1.0+DTOTLIMIT==1.0)
// lower limit upon which symmetry point is taken so no symmetry violation from machine precision interference
// really DTOTLIMIT/2 is size of region where sym-interp-fix occurs
#if(FLOATTYPE==1)
#define DTOTLIMIT (1.0E-6)
#define INVDTOTLIMIT (1.0E+6)
//#define DTOTLIMIT (1.0E-10) // 2.2204460492503131E-016 is round off epsilon(DBL_EPSILON)
#else
// 1.192092896E-7F is round off epsilon(FLT_EPSILON)
#define DTOTLIMIT (1.0E-3)
#define INVDTOTLIMIT (1.0E+3)
#endif


#define DEBUG 0 // (temp stuff, none right now, moved to real seperate defines)
// 0: no debug statements: real run
// 1: normal run with some checks/statements
// 2: as 1 but add output on changes to data
#define DEBUGMPI 0
// 0: no debug statements: real run
// 1: check if runtime mpich calls are synched across all cpus


// force flush of fail_file data each dt
#define FLUSHFAILDT 1

// with these memory flags, make sure you don't use mem if 0!!
#define MDOTMEM 0 // whether to allocate memory for injection
#define VISCMEM 0 // whether to allocate memory for viscosity tensors
// MARK
#define RESMEM 1 // whether to allocate memory for resistivity
#define MDOTMEMANAL 0 // whether to allocate memory for analytic mdot(see analsol.c)

// these pressure switches here for performance reasons
// check press==0/1 in init.c
#define PDEN                 1 // 0->no pressure 1->pressure from density/energy
#define PGRAV                1 // 0->no ext pot 1->ext pot
#define CURVE                1 // 0->no curvature terms 1-> do
#define PMAG                 1 // 0->no mag fields 1-> do mag fields

// special opts or new computes for pressure step
// MARK
#define GRAVACC              1 // 1->use analytic acceleration(see step.c and init.c) (must setup in analsol.c)
#define GRAVITOMAGNETIC      0 // 1->gravitomagnetic field 0->no (must setup in analsol.c)

// in bzsweepx/y:
#if(COMPDIM<3)
#define TORVX1    1 // bzsweepx v3-comp
#define TORVX2    1 // bzsweepy v3-comp
#define TORBX1    1 // bzsweepx b3-comp
#define TORBX2    1 // bzsweepy b3-comp
#else
#define TORVX1    0
#define TORVX2    0
#define TORBX1    0
#define TORBX2    0
#endif

#define RELIE      0 // 0-> Newtonian EOS 1-> Relativistic EOS

#define NUMSPECTRUM 20  // number of frequency bands
#define NUMFUNCOOL 5120  // number of samples of cooling function
#define NUMFUNRELIE (NUMFUNCOOL) // number of samples of relativistic step_ie function

#define VISC_LINEAR 0 // 0-> linear viscosity off/1=on
#define VISC_TENSOR 0 // 0-> vnr visc 1-> tensor visc

// turn on/off different terms (1 or 0)
#define VISCE11 1
#define VISCE22 1
#define VISCE33 1
#define VISCE12 1
#define VISCE21 VISCE12
#define VISCE13 1
#define VISCE31 VISCE13
#define VISCE23 1
#define VISCE32 VISCE23

// MARK
#define ALFVENLIMIT 0
// 0: normal newtonian EOM
// 1: rho->rho+b^2*(sol^{-2})=rho+(b*invsol)^2

// force floor on varibles
// MARK
#define FORCERHO 1 // 1: force DENSITYFLOOR on rho
#define FORCEIE 1 // 1: force IEFLOOR on ie(s2 really)
#define TS0CHECK 0 // 1: check if rho or ie<0 in timestep.c  not needed if forcing floor

// number of dt checks for timestep.c
#define NUMDTCHECKS 10
#define TRYSUBCYCLE 0 // whether to try to subcycle on viscosity or not

// max number of CPUS for various allocations
// if want beyond this need to change CPUTXT on myid outputs in *.c
#define MAXCPUS 1000

// number of ghost zones
// should either use 1 for all non-zero or 2 for all non-zero, don't mix 1 and 2.
#define N1BND 2
#define N2BND 2
#if(COMPDIM==3)
#define N3BND 2
#else
#define N3BND 0
#endif

#define NBIGBND1 ((N1BND>N2BND) ? N1BND : N2BND)
#define NBIGBND  ((NBIGBND1>N3BND) ? NBIGBND1 : N3BND)

/* allocated memory uses this for active zones 0-N1-1 and bc beyond that */
#define N1M (N1+N1BND*2)
#define N2M (N2+N2BND*2)
#define N3M (N3+N3BND*2)

/* NBIGM is bigger of N1M and N2M and N3M */
#define NBIG1M ((N1M>N2M) ? N1M : N2M)
#define NBIGM  ((NBIG1M>N3M) ? NBIG1M : N3M)

// maximal surface of boundary exchange
#if(COMPDIM==3)
#define NBIGS1M ((N1M*N2M>N1M*N3M) ? N1M*N2M : N1M*N3M)
#define NBIGSM ((NBIGS1M>N2M*N3M) ? NBIGS1M : N2M*N3M)
#else
#define NBIGSM (NBIGM)
#endif

#define CHECKDTLOW 1 // whether to check if dt went below critical value
#define DTLOWEST (1.E-10)
#define IDTLOWEST (1.0/DTLOWEST)
#define SQIDTLOWEST (1.0/(DTLOWEST*DTLOWEST)) // actually dt over cour then squared
#define DTLOWDUMP (DTLOWEST) // lowest dt to initiate dumping


#if(PERFTEST==0) // can choose
// 0: don't generate parameter output 1: do
#if(POSTPROC==0)
// MARKMARK
#define DOPARDIAG 0 // generally do want to overwrite when pp=0
#define DOGPARDIAG 1
#else
#define DOPARDIAG 0 // generally don't want to overwrite diag when pp=1, but can.
#define DOGPARDIAG 0
#endif
// 0: don't generate interpolated parameter output 1: do
#if(POSTPROC==0)
#define DOIPARDIAG 0 // should remain 0
#else
#define DOIPARDIAG 1 // need 1 if interp data in pp
#endif
// 0: don't output general diag 1: do output
#define DOGENDIAG 1
 // 0: don't output loss diag 1: do output/counting(required in general)
#define DOLOSSDIAG 1
 // 0: don't output avg diag 1: do output
#define DOAVGDIAG 0
 // 0: don't output floor diag 1: do output level 1 2: do full floor diag output (floor counters always active, this just controls diagnostics of counters)
#define DOFLOORDIAG 1 // output details on what algorithm caused most lows and how low values got
#define DOFLOORD2 0 // VERY DETAILED:  output where and what corrected in logfl_file
 //0: don't do dt diag 1: do
#define DODTDIAG 1 // output of dt constraints
#define DOTSTEPDIAG 1 // output of timescales(true global data of just above)
#define DOSPDIAG 1 // sonic point location check log output

#define DOLOGSTEP 1 // log the time step as per NDTCCHECK
#define DOLOGPERF 1 // log the performance as per NZCCHECK


#elif(PERFTEST==1)


#define DOPARDIAG 0
#define DOIPARDIAG 0
#define DOGENDIAG 0
#define DOLOSSDIAG 0
#define DOAVGDIAG 0
#define DOFLOORDIAG 0 
#define DOFLOORD2 0
#define DODTDIAG 0
#define DOTSTEPDIAG 0
#define DOSPDIAG 0
#define DOLOGSTEP 0
#define DOLOGPERF 0
#endif

// how often in steps to output step/dt/t data
// MARK 100 100 20 500
// MARK 10 10 1 100 for 1024x1024 vortex
// MARK 1D bondi: 10000 10000 1000 20000
// MARK 2D MHD Tori128128: 500 500 10 1000
#define NDTCCHECK 50
// how often in steps to check speed in zonecycles/sec
#define NZCCHECK 50
#define NDTDOTCCHECK 1 // how often in steps to check the go.go file to see if to continue running
#define NGOCHECK 100

// how many seconds, below which if logging is taking place could impact performance and so is reported to user in the perf file
// comment shows what the time check is based upon
// the number inside is the # of seconds, the divisor is a scale factor(see main.c)
#define NUMLOGCHECKS 7 // number of these log checks

// really want walltime(to do step)/dt << walltime(to do dump)/Dt
#define LOGLWTCHECK (1.0/DTl) // 0
#define LOGDWTCHECK (20.0/DTd) // 1
#define LOGIWTCHECK (20.0/DTi) // 2
#define LOGENERWTCHECK (2.0/DTener) // 3
#define LOGLOSSWTCHECK (2.0/DTloss) // 4
#define LOGTIMESTEPWTCHECK (60.0/DTtimestep) // 5
#define LOGSPWTCHECK (60.0/DTsp) // 6

#if(PERFTEST==0) // can choose
// MARKMARKMARKMARK
#define PDUMPFLAG 0 // 0: don't dump primitive on own grid for reentrance 1: do
#define DUMPFLAG 0 // 0: don't create dump files 1: do create
#if(VISCMEM==1)
#define NPDUMPFLAG 0 // 0: don't create np dump files 1: do create (just pp now!)
#else
#define NPDUMPFLAG 0 // no choice
#endif
#define FLOORDUMPFLAG 0 // 0: don't create floor dump files 1: do create
#define FLDUMPFLAG 1 // 0: don't create fieldline dump files 1: do create
#define ADUMPFLAG 0 // 0: don't create analytic dump files 1: do create -1: only create first one


#if(!((N2==1)||(N1==1)))
// MARKMARK
#define IMAGEFLAG 0 // choice: 0: don't create images 1: do create
#else
#define IMAGEFLAG 0 // assume don't want image if 1D
#endif


#elif(PERFTEST==1)


#define PDUMPFLAG 0 // 0: don't dump primitive on own grid for reentrance 1: do
#define DUMPFLAG 0 // 0: don't create dump files 1: do create
#define NPDUMPFLAG 0 // 0: don't create np dump files 1: do create (just pp now!)
#define FLOORDUMPFLAG 0 // 0: don't create floor dump files 1: do create
#define ADUMPFLAG 0 // 0: don't create analytic dump files 1: do create -1: only create first one
#define IMAGEFLAG 0 // choice: 0: don't create images 1: do create
#endif

#define OLDSCHOOL 0 // 0: assume as current data sets 1: use older format for data sets


#if(POSTPROC==0)
// only need first data set for image dump before pp
#define NUMOUTTYPE 1 // number of outtypes to do(see diag.c for how chosen)
#else
#define NUMOUTTYPE 3 // assume want all image outputs
#endif
#define OLDSCHOOL2 0 // 0: assume as current r8's 1: as old r8's

// generally, should use sm to grid data correctly, but if don't care about reentering at all, can do here.
#define DUMPSM 1 // 0: dump data where gridded 1: dump in center of zone for all
#define FULLOUTPUT 0 // 0: output data for active grid, 1: half bzones out 2: full grid output
// can only take fullinput on fulloutput data
#define FULLINPUT 0 // 0: input data for active grid, 1: half bzones 2: full grid input

// see diag.c and init.c for more image and dump options.
#if(POSTPROC==0)
 // 0=image raw rectangular grid data 1=point sample 2=plane interpolation
#define SAMPLEI 0 // should be 0 in general
#define SAMPLED 0 // should be 0 in general
#else
#define SAMPLEI 1
#define SAMPLED 2 // should choose 2 for pretty dumps, choose 1 for use as input data so no odd extrapolation at edges
#endif

// right now below 2 not used as all forced to be centered on a-grid
// only applies to interpolation
#define SAMEGRIDI 2 // 0=a-grid for sca b-grid for vec 1=all on a-grid 2=all on b-grid: Basis for where to interpolate to for image data
#define SAMEGRIDD 2 // 0=a-grid for sca b-grid for vec 1=all on a-grid 2=all on b-grid: Basis for where to interpolate to for dump data
#if(POSTPROC==0)

#if(SAMPLEI==0)
#define IMGN1 N1
#define IMGN2 N2
#define IMGN3 N3
#elif(SAMPLEI>0)
#define IMGN1 256 // size of image outputted in x-direction in image
#define IMGN2 512 // size of image outputted in y-direction in image
#define IMGN3 N3
#endif

#if(SAMPLED==0)
#define DUMN1 N1
#define DUMN2 N2
#define DUMN3 N3
#elif(SAMPLED>0)
#define DUMN1 256 // size of dump outputted in x-direction in image
#define DUMN2 512 // size of dump outputted in y-direction in image
#define DUMN3 N3
#endif

#else

#if(SAMPLEI==0)
#define IMGN1 N1 // no choice
#define IMGN2 N2 // no choice
#define IMGN3 N3 // no choice
#else
#define IMGN1 1024 // choice
#define IMGN2 1024 // choice
#define IMGN3 N3 // no choice
#endif
#if(SAMPLED==0)
#define DUMN1 N1 // no choice
#define DUMN2 N2 // no choice
#define DUMN3 N3 // no choice
#else
#define DUMN1 512 // choice
#define DUMN2 512 // choice
#define DUMN3 N3 // no choice
#endif

#endif

#define ITYPES 2 // number of types of image ranges, 0, 1
#define CTYPES 2 // number of types of computed image ranges, 0, 1

// determine largest interpolated grid sizes for memory allocation of working space
#define INTN1 ((DUMN1>IMGN1) ? DUMN1 : IMGN1)
#define INTN2 ((DUMN2>IMGN2) ? DUMN2 : IMGN2)
#define INTNBIG ((INTN1>INTN2) ? INTN1 : INTN2)

#if(POSTPROC==0)
#define IMAGEFORMAT 0 // should always be 0 for post processing ability
#define IMAGEFORMATINPUT 0 // dummy
#else
#define IMAGEFORMAT 1 // choose final format for post proc(only interp)
#define IMAGEFORMATINPUT 0 // must be 0 
#endif
// 0: r8(best in general except for immediate viewing)
// 1: ppm (best, esp. when used with gzip below)(can't be used during post process since can't reverse lookup easily, so don't use for now)
#if(POSTPROC==0)

#if(USEGM==1)
#define GZIPIMAGE 0 // can't gzip with GM
#else
#define GZIPIMAGE 3 // might as well always gzip otherwise
#endif

#define GZIPIMAGEINPUT 0 // dummy value since never input image normally

#else

#define GZIPIMAGE 3 // best to always use this when post proc
#define GZIPIMAGEINPUT 3 // choose was input type for post processing

#endif
// 0: don't gzip(best if need not zipped)(necessary for gm over mpich)
// 1: do gzip using system call(best for compatibility)
// 2: do gzip using fork call (best for small files)
// 3: do gzip using popen (best for large files)



//MARK
#define COORD 1
// 1 for cartesian coords
// 2 for cyl
// 3 for sph
// see init.c init_diffs() for usage



#define INNERBC 0 // whether to include inner zones in bound loop

#define DOBOUNDSCA 1
#define DOBOUNDVEC 1
#define SCABCCORNER 1
#define VECBCCORNER 1

// whether to bound potential(generally should be kept as analytic solution)
#define NOBOUNDPOT 1 // 0: bound potential like other scalars, 1: no bound of pot
#define BOUNDN1 1 // 0: don't do N1 layer bound, 1: do
// can use below if make N2==1 and don't care about theta structure.  Assumes many things, so could be nasty, but much faster for 1-D problems
#if(0&&(N2==1))
#define BOUNDN2 0 // 0: don't do N2 layer bound, 1: do (0 for speed on pure 1D-1D-vector problems)
#else
#define BOUNDN2 1 // generally this should be 1
#endif

#define BOUNDN3 0 // 0: don't do N3 layer bound, 1: do

#define IOBOUNDARY 0 // 0: normal boundary, 1: Inflow/outflow split outer x2-boundary
#define NUMBTRANS 4 // number of boundary transitions(see defs.h/init.c)

// Make sure boundary zones do not allow inflow on outflow boundary(see bound.c)
// only applies if outflow condition
#if(COORD==3)
#define INFLOWCHECKIX1 1 // inner x1-edge
#define INFLOWCHECKOX1 1 // outer x1-edge
#else // typically don't want inflow check in cart problems
#define INFLOWCHECKIX1 0 // inner x1-edge
#define INFLOWCHECKOX1 0 // outer x1-edge
#endif
#define INFLOWCHECKIX2 0 // inner x2-edge // only use in 2D+
#define INFLOWCHECKOX2 0 // outer x2-edge
#define INFLOWCHECKIX3 0 // inner x3-edge // only use in 3D+
#define INFLOWCHECKOX3 0 // outer x3-edge


#define HYDROBZFLUX 0
// 0: let magnetic_flux do bz flux calc
// 1: let hydro_flux do bz flux calc(not "working" right now)

// keep below at 1 or 2, not 0 for all version stuff to work
#define DETAILMLOSS 1 // 0=only show total massloss each time
// 1= show mass loss total and through each boundary(4 in 2D, 8 in 3D)
// 2= Do 1 but in a seperate file output each grid points output each time

#define LINEARINTERP 1
// 0: just choose local value (for major speed, but large diffusion)
// 1: simple average or truely correct for uniform grid (for speed or uniform grid) (sorta corresponds to how differencing is done for 1st derivative in sweep.c)
// 2: correct linear average for generaly nonuniform grid (slower)

#define LINEXT 0
// 0: just copy
// 1: do linear extrap based with nonuniform ability, but not setup for 2 bzones

// major constants below
#define NUMSCA 3
#define NUMVEC 2
#define REALNUMVEC 2 // can use if not using MHD
#define NUMSV (NUMSCA+NUMVEC)
#define NUMGRID (COMPDIM)
#define NUMMETRIC 4
#define NUMVOL (COMPDIM)
#define DIRVEC 1
#define NUMFLOORVAR 2 // 1: mass density 2: ie density
#define NUMFLOOROUT 7 // number of routines checked for floor
// 0 through 6 with 1 extra space

// number of time(space) averaged quantities
#define NUMAVG2_3 15 // only averaged over time
#define NUMAVG1_32 15 // time and x2
#define NUMAVG1_31 15 // time and x1
// 1: rho
// 2: en
// 3: Be
// 4: cs^2
// 5: entropy (Exp[S])
// 6: vx1
// 7: vx2
// 8: vx3
// 9: sig11
// 10: sig12
// 11: sig13
// 12: sig22
// 13: sig23
// 14: sig33
// 15: nu_real(nuvisc)

#define NUMPPCALCS 12
// see diag.c(dump())

#define NUMWORKIQ ((NUMPPCALCS>NUMAVG2_3) ? NUMPPCALCS : NUMAVG2_3)

#define NUMLOSSVAR (NUMSCA+NUMVEC*(3+1)+1)
// 1: mass
// 2: enthalpy
// 3: grav pot energy

// 4: kinE

// 5: s1
// 6: s2
// 7: s3

// 8: magE

// 9: B1
// 10: B2
// 11: B3

// 12: etot(visc)

// extention for data files
#define DATEXT ".dat"
#define PAREXT ".par"
#define INEXT ".in"
#define OUTEXT ".out"
#define PPEXT ".pp"

#define INPUTPAR "%lf"
#define INPUT2 "%lf "
#define INPUT2B "%lf "
#define INPUT3I "%lf"
#define INPUTIMGT "%lf"
// INPUT1/1old/4/5/6/7/avgh1 defines in i/i/diag.c/diag.c/diag.c/init.c/init.c respectivly because sensitive
#define INPUT7 "%lf" // this not sensitive for now
#define INPUTRAD "%lf"

#define ARGS 5
#define PARMTYPEARGS "%d %d %d %lf %lf"
#define MAXFILENAME 400

// file versions numbers(use sm for backwards compat)
#define PVER 10
#define GRIDVER 2
#define DVER 1    // dumps same as for pdumps, adumps
#define FLVER 2
#define NPVER 2
#define AVG1DVER 2
#define AVG2DVER 2
#define ENERVER 5
#define LOSSVER 5
#define SPVER   1
#define TSVER   1
#define LOGDTVER 1
#define STEPVER 1
#define PERFVER 3
#define ADVER DVER
#define PDVER DVER
#define CALCVER 1
#define FLINEVER 1
// type designations for sm automagical read in correct format for similar things
#define PTYPE     1 // global par file
#define GRIDTYPE  2
#define DTYPE     3 // dump
#define FLTYPE    4 // floor
#define NPTYPE    5 // np
#define AVG2DTYPE 6
#define AVG1DTYPE 7
#define ENERTYPE  8
#define LOSSTYPE  9
#define SPTYPE    10
#define TSTYPE    11
#define LOGDTTYPE 12 
#define STEPTYPE  13
#define PERFTYPE  14
#define ADTYPE    15 // same as dump except filename
#define PDTYPE    16 // same as dump except filename
#define CALCTYPE  17 // arbitrary calcs during pp
#define FLINETYPE  18 // field line during pp
#define EXPANDTYPE 50 // used to signify doing pp expansion
#define NPCOMPUTETYPE 33 // used to signify want to compute np before output

#define ZER 0x30
#define DIGILEN 10  

// if you change these, make sure you know where they are used!!
#define ERR     1.e-6
#define SMALL	1.e-10
#define GMIN 	1.e-10
#define MIN	1.e-20	/* minimum density */
#define SSMALL  1.E-30

#define THIRD (0.3333333333333333333333333333333333333333333333333333333333333333333)

#define SCAHEADER(fp,ll,outtype,iii,cnt,t,nx,ny) \
	  fprintf(fp,"#scalar#: %d ot: %d mt: %d image#: %d t=%15.10g\n",ll,outtype,iii,im_cnts[outtype][ll],t); \
	  fprintf(fp,"%i %i\n", nx, ny); \
	  fprintf(fp,"255\n") 

#define VECHEADER(fp,ll,outtype,iii,q,cnt,t,nx,ny) \
	    fprintf(fp,"#vector#: %d outtype#: %d maptype#: %d comp#: %d image#: %d t=%15.10g\n",ll,outtype,iii,q,cnt,t); \
	    fprintf(fp,"%i %i\n", nx, ny); \
	    fprintf(fp,"255\n")

#define HEADER3_S0 "%d %d\n"
#define HEADER3_S1 "%d %d %d\n"
#define HEADER3_S10 "%d %d %d %d\n"
#define HEADER3_S11 "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n"
#define HEADER3_S12 "%d %d %d %d\n"
#define HEADER3_S13 "%d %d %d %d %d %d %d %d %d %d\n"
#define HEADER3_S14 "%d %d %d %d %d %d %d %d %d %d %d %d\n"
#define HEADER3_S15 "%d %d %d %d %d %d\n"
#define HEADER3_S16 "%d %d %d %d %d %d %d %d %d %d\n"

// version of file format
// N1, N2, N3
 // L11, L12, L13, L21, L22, L23
 // rg rgp cs coolfact gam alpha_real0 n_real
 // nu_vnr nu_l nu_ten cour cour2
 // gravc massbh invsol2 blackholejz
 // tstart tf tavgi tavgf numavg
 // dtl dtd dti dtloss dtfloor dttimestep dtpd dtener dtfld
 // resist nu_sh
 // vg1 vg2 vg3
// coord fullvec analoutput DYNAMICMM
// trans,transx1,transrhox1,transiex1,transv1x1,transv2x1,transv3x1,transmagx1,transx2,transrhox2,transiex2,transv1x2,transv2x2,transv3x2,transmagx2,transx3,transrhox3,transiex3,transv1x3,transv2x3,transv3x3
// press,pressx1,pressx2,pressx3
// mag,transbzx,transbzy,stepmocct,mocctvx1,mocctvx2,mocctvx3,mocctbx1,mocctbx2,mocctbx3
// ie,visc_art,visc_real,vreal,vischeat,mdotin,cool,res_real,rreal,resheat,advint,kever
// intix1,intox1,intix2,intox2,intix3,intox3
// nonunigridx1,nonunigridx2,nonunigridx3,simplebc,bcix1,bcox1,bcix2,bcox2,bcix3,bxoc3
#define HEADER3_P  "# %4s %4s\n"\
                   "  %4d %4d\n"\
                   "# %4s %4s %4s\n"\
                   "  %4d %4d %d\n"\
                   "# %21s %21s %21s %21s %21s %21s\n"\
                   "  %21.15g %21.15g %21.15g %21.15g %21.15g %21.15g\n"\
                   "# %21s %21s %21s %21s %21s %21s %21s\n"\
                   "  %21.15g %21.15g %21.15g %21.15g %21.15g %21.15g %21.15g\n"\
		   "# %21s %21s %21s %21s %21s\n"\
		   "  %21.15g %21.15g %21.15g %21.15g %21.15g\n"\
		   "# %21s %21s %21s %21s\n"\
		   "  %21.15g %21.15g %21.15g %21.15g\n"\
		   "# %21s %21s %21s %21s %21s %21s\n"\
		   "  %21.15g %21.15g %21.15g %21.15g %21d %21.15g\n"\
		   "# %21s %21s %21s %21s %21s %21s %21s %21s %21s\n"\
		   "  %21.15g %21.15g %21.15g %21.15g %21.15g %21.15g %21.15g %21.15g %21.15g\n"\
		   "# %21s %21s\n"\
		   "  %21.15g %21.15g\n"\
		   "# %21s %21s %21s\n"\
		   "  %21.15g %21.15g %21.15g\n"\
                   "# %21s %21s %21s %21s\n"\
                   "  %21d %21d %21d %21d\n"\
                   "# %21s %21s %21s %21s %21s %21s %21s %21s %21s %21s %21s %21s %21s %21s %21s %21s %21s %21s %21s %21s %21s\n"\
                   "  %21d %21d %21d %21d %21d %21d %21d %21d %21d %21d %21d %21d %21d %21d %21d %21d %21d %21d %21d %21d %21d\n"\
                   "# %21s %21s %21s %21s\n"\
                   "  %21d %21d %21d %21d\n"\
                   "# %21s %21s %21s %21s %21s %21s %21s %21s %21s %21s\n"\
                   "  %21d %21d %21d %21d %21d %21d %21d %21d %21d %21d\n"\
                   "# %21s %21s %21s %21s %21s %21s %21s %21s %21s %21s %21s %21s\n"\
                   "  %21d %21d %21d %21d %21d %21d %21d %21d %21d %21d %21d %21d\n"\
                   "# %21s %21s %21s %21s %21s %21s\n"\
                   "  %21d %21d %21d %21d %21d %21d\n"\
                   "# %21s %21s %21s %21s %21s %21s %21s %21s %21s %21s\n"\
                   "  %21d %21d %21d %21d %21d %21d %21d %21d %21d %21d\n"

#define HEADER4_P  " %4d %4d %4d %4d "\
                   "%21.15g %21.15g %21.15g "\
                   "%21.15g %21.15g %21.15g "\
                   "%21.15g %21.15g %21.15g %21.15g %21.15g %21.15g %21.15g %21.15g %21.15g "\
                   "%21.15g %21.15g %21.15g "

#define HEADER4_S  "%d %d %d %d "\
                   "%lf %lf %lf "\
                   "%lf %lf %lf "\
                   "%lf %lf %lf %lf %lf %lf %lf %lf %lf "\
                   "%lf %lf %lf "


/* Function defines */
int main(
	 int argc,
	 char *argv[],
	 char *envp[]
	 );
int myexit(int call_code);

extern int init(int argc,
		char *argv[],
		char*envp[]);
extern void init_checks(void);
extern void init_genfiles(int gopp);
extern void init_general(void);
extern int  init_MPI(int argc,char *argv[]);
extern void  init_MPIgroup(void);
extern void  init_placeongrid(void);
extern void  init_optimalmpi(int which);
extern void init_loss(void);
extern void init_compsave(void);
extern void init_visc(void);
extern void init_floor(void);
extern void init_inflows(void);
extern void init_radiations(void);
extern int init_mem(void);
extern int init_pointers(void);
extern int init_runpar(void);
extern int init_rundat(int dump_cnt,int which);
extern int init_runimage(int im_cnt,int wsca,int wvec,int call_code,int outtype);
#define PARAMETERPARLIST int seed, FTYPE beta, FTYPE nj
extern int init_paramstot(PARAMETERPARLIST);
extern int init_paramsphysics(PARAMETERPARLIST);
extern int init_paramsgeom(PARAMETERPARLIST);
extern int init_paramstime(PARAMETERPARLIST);
extern int init_paramsnumerical(PARAMETERPARLIST);
extern int init_paramspresets(PARAMETERPARLIST);
extern int init_reentrance(void);
extern int init_reentrance2(SFTYPE time, int which);
extern int init_otherparams(void);
extern int init_dx(int n1,int n2,int n3,int n1b,int n2b,int n3b, SFTYPE*sx, int which, int outtype);
extern int init_x(int n1,int n2,int n3,int n1b,int n2b,int n3b, SFTYPE*sx, int which, int outtype);
extern int init_diffs(void);
extern int init_data(void);
extern int init_bc(int simple,int ix1,int ox1,int ix2,int ox2,int ix3,int ox3);
extern int init_mainbc(int px1,int six1,int rix1,int rox1,int px2,int six2,int rix2,int rox2,int px3,int six3,int rix3,int rox3);
extern int init_outgparm(int which);

extern FTYPE ranc(int iseed);
extern void bound(FTYPE (*vars)[N2M][N1M],
		  FTYPE (*varv)[N3M][N2M][N1M],
		  int wsca,// which scalars to update: -1 for all or 1-NUMSCA for individual
		  int wvec,// which vectors to update: -1 for all or 1-NUMVEC for individual, and -2 for any scalar/vector
		  int wcom); // which component of vector, otherwise ignored for scalars
extern void diag(int call_code);
extern void diagavg(int call_code);
void divb0check(void);
void dump_header(FILE *fp,int which, int realsampled,int nogridchoice);
extern void dump_header2(FILE* fp, int which);
extern void dump(FILE *fp, int dump_cnt,int which,int outtype);
extern void analdump(FILE *fp);
extern void analsolve(int gopp);
extern void sodsol(int gopp);
extern void advsol(int gopp);
extern void gausssol(int gopp);
extern void bondisol(int gopp);
extern FILE * tori1sol(int gopp);
extern void injectsol(int gopp);
extern void accountstoreset(void);
extern void visctermtest(int gopp);
extern void pulsesol(int gopp);
extern void test1sol(int gopp);
extern void test2sol(int gopp);
extern void magbreaksol(int gopp);
extern void magvortex(int gopp);
extern void magcorona(int gopp);


extern void image(int im_cnt, int wsca,int wvec, int call_code, int outtype);
extern void spec_diag(void);

extern void stepvar_2d(void);
extern void stepvar_3d(void);
#if(COORD==1)
#define compute_sigma_gen compute_sigma_1
#elif(COORD==2)
#define compute_sigma_gen compute_sigma_2
#elif(COORD==3)
#define compute_sigma_gen compute_sigma_3
#endif
extern void compute_sigma_3(FTYPE (*sigma)[3][N3M][N2M][N1M],FTYPE (*rost)[3][N3M][N2M][N1M],FTYPE (*rostnu)[3][N3M][N2M][N1M],FTYPE (*nurho_real)[N2M][N1M],FTYPE (*delv)[N2M][N1M]);
extern void compute_sigma_1(FTYPE (*sigma)[3][N3M][N2M][N1M],FTYPE (*rost)[3][N3M][N2M][N1M],FTYPE (*rostnu)[3][N3M][N2M][N1M],FTYPE (*nurho_real)[N2M][N1M],FTYPE (*delv)[N2M][N1M]);
extern void timestep(void);
extern void idtcreate(FTYPE*idt,int k, int j, int i);
extern void timescale(void);
extern void timecheck(int failmode,FTYPE*idt,int k, int j, int i,int reall);
extern void magprepare(void) ;
extern void moc_ct_2d(void) ;
extern void moc_ct_3d(void) ;
extern void step_bz_2d(void) ;
extern void bzsweepx_2d(void);
extern void bzsweepy_2d(void);
extern void magnetic_flux(void);
extern void step_pgc(void) ;
extern void step_visc(void) ;
extern void step_visc_real(void);
extern void viscous_flux(void);
extern void tdep_compute(void);
extern void sp_compute(void);
extern void injection_2d(void);
extern void injection_3d(void);
extern void cooling(void);
extern void compute_funcool(FTYPE *fun,FTYPE *thetai,int num,FTYPE thetas,FTYPE thetaf,FTYPE *dthetap);
extern void compute_funrelie(FTYPE *fun,FTYPE *thetai,int num,FTYPE thetas,FTYPE thetaf,FTYPE *dthetap);
extern void nu_compute(void);
extern void init_res(void);
extern void nu_res_compute(void);
extern void current_compute(int wcom);
extern void step_ie(void) ;
extern void step_relie (void);
extern void step_res(void) ;

extern void step_trans_2d(void) ;
extern void step_trans_3d(void) ;
extern void sweepx(void);
extern void sweepy(void);
extern void sweepz(void);
extern void hydro_flux(int dir,int which,FTYPE (*fl)[N3M][N2M][N1M]);
extern void dqx_calc(FTYPE (*var)[N2M][N1M], FTYPE (*dq)[N2M][N1M]) ;
extern void dqvx_calc(int wcom, FTYPE (*var)[N3M][N2M][N1M],FTYPE (*dqv)[N3M][N2M][N1M]);
extern void dqy_calc(FTYPE (*var)[N2M][N1M], FTYPE (*dq)[N2M][N1M]) ;
extern void dqvy_calc(int wcom,FTYPE (*var)[N3M][N2M][N1M],FTYPE (*dqv)[N3M][N2M][N1M]);
extern void dqz_calc(FTYPE (*var)[N2M][N1M], FTYPE (*dq)[N2M][N1M]) ;
extern void dqvz_calc(int wcom,FTYPE (*var)[N3M][N2M][N1M],FTYPE (*dqv)[N3M][N2M][N1M]);



//extern FTYPE z2e_1(FTYPE (* var)[N1M],int j,int i);
//extern FTYPE z2e_2(FTYPE (*var)[N1M],int j,int i);
//extern FTYPE e2z_1(FTYPE (*var)[N1M],int j,int i);
//extern FTYPE e2z_2(FTYPE (*var)[N1M],int j,int i);
//extern FTYPE e2e_v2(FTYPE (*var)[N1M],int j, int i);
//extern FTYPE e2e_v1(FTYPE (*var)[N1M],int j, int i);
extern void ex_v(int dim,int dir,FTYPE (*var)[N1M], int k, int j, int i,int which);
extern void ex_s(int dim,int dir,FTYPE (*var)[N1M],int k, int j, int i, int which);
extern void ex_s_p(int dim,int dir,FTYPE (*var)[N1M],int k, int j, int i);
extern void ex_v_p(int dim,int dir,FTYPE (*var)[N1M],int k, int j, int i);

extern void interpolate(int wtype, int wsv, int stype, int whichg, int inn1, int inn2, int outn1, int outn2, FTYPE in[N2M][N1M], FTYPE out[INTN2][INTN1], FTYPE outerdef,int outtype);

extern FTYPE alnfact(FTYPE N);
extern void itoa(int x,char*p);
extern int mysys(char*com1, char*com2);
extern int fork2(void);
extern void ptraddr(int nstep);

// Macros

// note: LOOPF goes over corner zones.  I init corners to 1 or correctly in analsol.c so if I divide this useless data it does no harm.  Just for speed.  Could put ifs in to avoid corner zones, but slower.

// for compatibility with 1 bnd zone force no such H vs F to exist
#if(NBIGBND==2)
#define LOOPH3 for(k=-N3BND/2;k<N3+N3BND/2;k++)
#define LOOPH2 for(j=-N2BND/2;j<N2+N2BND/2;j++)
#define LOOPH1 for(i=-N1BND/2;i<N1+N1BND/2;i++)

#define LOOPFMHP3 for(k=-N3BND;k<N3+N3BND/2;k++)
#define LOOPFMHP2 for(j=-N2BND;j<N2+N2BND/2;j++)
#define LOOPFMHP1 for(i=-N1BND;i<N1+N1BND/2;i++)

#define LOOPHMFP3 for(k=-N3BND/2;k<N3+N3BND;k++)
#define LOOPHMFP2 for(j=-N2BND/2;j<N2+N2BND;j++)
#define LOOPHMFP1 for(i=-N1BND/2;i<N1+N1BND;i++)

#define LOOPHP3 for(k=0;k<N3+N3BND/2;k++)
#define LOOPHP2 for(j=0;j<N2+N2BND/2;j++)
#define LOOPHP1 for(i=0;i<N1+N1BND/2;i++)

#define LOOPHM3 for(k=-N3BND/2;k<N3;k++)
#define LOOPHM2 for(j=-N2BND/2;j<N2;j++)
#define LOOPHM1 for(i=-N1BND/2;i<N1;i++)

#else

#define LOOPH3 for(k=-N3BND;k<N3+N3BND;k++)
#define LOOPH2 for(j=-N2BND;j<N2+N2BND;j++)
#define LOOPH1 for(i=-N1BND;i<N1+N1BND;i++)

#define LOOPFMHP3 for(k=-N3BND;k<N3;k++)
#define LOOPFMHP2 for(j=-N2BND;j<N2;j++)
#define LOOPFMHP1 for(i=-N1BND;i<N1;i++)

#define LOOPHMFP3 for(k=-N3BND;k<N3+N3BND;k++)
#define LOOPHMFP2 for(j=-N2BND;j<N2+N2BND;j++)
#define LOOPHMFP1 for(i=-N1BND;i<N1+N1BND;i++)

#define LOOPHP3 for(k=0;k<N3+N3BND;k++)
#define LOOPHP2 for(j=0;j<N2+N2BND;j++)
#define LOOPHP1 for(i=0;i<N1+N1BND;i++)

#define LOOPHM3 for(k=-N3BND;k<N3;k++)
#define LOOPHM2 for(j=-N2BND;j<N2;j++)
#define LOOPHM1 for(i=-N1BND;i<N1;i++)


#endif



#define LOOPC3 for(k=0;k<N3;k++)
#define LOOPC2 for(j=0;j<N2;j++)
#define LOOPC1 for(i=0;i<N1;i++)

#define LOOPF3 for(k=-N3BND;k<N3+N3BND;k++)
#define LOOPF2 for(j=-N2BND;j<N2+N2BND;j++)
#define LOOPF1 for(i=-N1BND;i<N1+N1BND;i++)

#define LOOPH LOOPH3 LOOPH2 LOOPH1
#define LOOPHP LOOPHP3 LOOPHP2 LOOPHP1
#define LOOPHM LOOPHM3 LOOPHM2 LOOPHM1
#define LOOPF LOOPF3 LOOPF2 LOOPF1
#define LOOPFMHP LOOPFMHP3 LOOPFMHP2 LOOPFMHP1
#define LOOPHMFP LOOPHMFP3 LOOPHMFP2 LOOPHMFP1

#define LOOPINT3 for(k=intix3;k<intox3;k++)
#define LOOPINT2 for(j=intix2;j<intox2;j++)
#define LOOPINT1 for(i=intix1;i<intox1;i++)

#define LOOPINT LOOPINT3 LOOPINT2 LOOPINT1

#define LOOP LOOPC3 LOOPC2 LOOPC1

#define LOOPSK3 for(k=skipix3;k<N3;k++)
#define LOOPSK2 for(j=skipix2;j<N2;j++)
#define LOOPSK1 for(i=skipix1;i<N1;i++)

// used for velocity calculations in step.c since when reflecting r/theta your metric components are 0 and floating point exception will occur, so just let bound do the work
// can either use below 2 loops to seperate x1/x2-directions or use LOOP above then have conditions using defines/ifs in loop
#define LOOPV1  LOOPC3 LOOPC2 LOOPSK1
#define LOOPV2  LOOPC3 LOOPSK2 LOOPC1
#define LOOPV3  LOOPSK3 LOOPC2 LOOPC1

#define LOOPINJ for(k=tagik;k<tagfk;k++) for(j=tagij;j<tagfj;j++) for(i=tagii;i<tagfi;i++)
#define LOOPFINJ for(k=t2gik;k<t2gfk;k++) for(j=t2gij;j<t2gfj;j++) for(i=t2gii;i<t2gfi;i++)
#define LOOPRINJ for(k=t3gik;k<t3gfk;k++) for(j=t3gij;j<t3gfj;j++) for(i=t3gii;i<t3gfi;i++)
#define LOOPVINJ for(k=t4gik;k<t4gfk;k++) for(j=t4gij;j<t4gfj;j++) for(i=t4gii;i<t4gfi;i++)



#define LOOP2  LOOPC2 LOOPC1


// sweepx

#define LOOPT1i LOOPC3 LOOPC2 for(i=0;i<N1+1;i++)

#if(NBIGBND==2)
// used for fluxes which never have i=-1 accessed
#define LOOPT0i for(k=0;k<N3;k++) for(j=skipix2-1;j<N2;j++) for(i=skipix1-1;i<N1+1;i++)
#else
#define LOOPT0i for(k=0;k<N3;k++) for(j=-1;j<N2;j++) for(i=0;i<N1+1;i++)
#endif

// used for fluxes which never have i=N1-1+1 accessed
// unless SKIPIX1==1, so that vx(0) is boundary zone so don't need fl(-1) for vx advection in x1-dir
#define LOOPT2i for(k=0;k<N3;k++) for(j=0;j<N2;j++) for(i=skipix1-1;i<N1;i++) 
// used for fluxes which never have i=-1 accessed, and don't need j=-1 or 0 accessed for non-periodic bcs
// below used on sweepx(vy)
#define LOOPT3i for(k=0;k<N3;k++) for(j=skipix2;j<N2;j++) for(i=0;i<N1+1;i++)
// below used on sweepx(vz)
#define LOOPT4i for(k=skipix3;k<N3;k++) for(j=0;j<N2;j++) for(i=0;i<N1+1;i++)


// sweepy:

// used for fluxes which never have i=-1 accessed
#define LOOPT1j LOOPC3 for(j=0;j<N2+1;j++) LOOPC1

#if(NBIGBND==2)
#define LOOPT0j for(k=0;k<N3;k++) for(j=-1+skipix2;j<N2+1;j++) for(i=-1;i<N1;i++)
#else
#define LOOPT0j for(k=0;k<N3;k++) for(j=0;j<N2+1;j++) for(i=-1;i<N1;i++)
#endif

// used for fluxes which never have i=N2-1+1 accessed
#define LOOPT2j for(k=0;k<N3;k++) for(j=skipix2-1;j<N2;j++) for(i=0;i<N1;i++) 

// used for fluxes which never have i=-1 accessed
// below used on sweepy(vx)
#define LOOPT3j for(k=0;k<N3;k++) for(j=0;j<N2+1;j++) for(i=skipix1;i<N1;i++)
// below used on sweepy(vz)
#define LOOPT4j for(k=skipix3;k<N3;k++) for(j=0;j<N2+1;j++) for(i=0;i<N1;i++)



// sweepz

// used for fluxes which never have i=-1 accessed
#define LOOPT1k for(k=0;k<N3+1;k++) LOOPC2 LOOPC1

#if(NBIGBND==2)
#define LOOPT0k for(k=-1+skipix3;k<N3+1;k++) for(j=-1;j<N2;j++) for(i=-1;i<N1;i++)
#else
#define LOOPT0k for(k=0;k<N3+1;k++) for(j=-1;j<N2;j++) for(i=-1;i<N1;i++)
#endif

// used for fluxes which never have i=N3-1+1 accessed
// below used on sweepz(vz)
#define LOOPT2k for(k=skipix3-1;k<N3;k++) for(j=0;j<N2;j++) for(i=0;i<N1;i++) 

// used for fluxes which never have i=-1 accessed
// below used on sweepz(vx)
#define LOOPT3k for(k=0;k<N3+1;k++) for(j=0;j<N2;j++) for(i=skipix1;i<N1;i++)

// below used on sweepz(vy)
#define LOOPT4k for(k=0;k<N3+1;k++) for(j=skipix2;j<N2;j++) for(i=0;i<N1;i++)



// loops over more i for j and more j for i than needed, but faster to do all in one lump
#define LOOPVISC for(k=0;k<N3;k++) for(j=-1;j<N2;j++) for(i=-1;i<N1;i++) 

// use for starting grid in upper left corner
#define LOOPI for(j=0;j<IMGN2;j++) for(i=0;i<IMGN1;i++)
#define LOOPICART #define LOOPI for(j=IMGN2-1;j>=0;j--) for(i=0;i<IMGN1;i++)
#define LOOPINI for(j=0;j<N2;j++) for(i=0;i<N1;i++) // used for post process 
#define LOOPD for(j=0;j<DUMN1;j++) for(i=0;i<DUMN2;i++)


// boundary loops over only 1st layer of bc, bound.c takes care of rest
#if( (BOUNDN2==1)&&(BOUNDN1==1) )
#define LOOPBOUND LOOPH
#elif( (BOUNDN2==1)&&(BOUNDN1==0) )
#define LOOPBOUND k=0; i=0; LOOPH2
#elif( (BOUNDN2==0)&&(BOUNDN1==1) )
#define LOOPBOUND k=0; j=0; LOOPH1
#endif


#define DEBUGP1 \
printf("\n\n\n\n"); \
  LOOPF{ \
printf("j: %2d i: %2d x1a: %21.15g x1b: %21.15g x2a: %21.15g x2b: %21.15g rho: %20.15g e: %21.15g pot: %21.15g Bx: %21.15g By: %21.15g Bz: %21.15g vx: %20.15g vy: %21.15g vz: %21.15g\n",j,i,x[1][1][i],x[2][1][i],x[1][2][j],x[2][2][j],s[1][k][j][i],s[2][k][j][i],s[3][k][j][i],v[2][1][k][j][i],v[2][2][k][j][i],v[2][3][k][j][i],v[1][1][k][j][i],v[1][2][k][j][i],v[1][3][k][j][i]); \
  }


#define BOUNDBUG printf("k: %d j: %d i: %d ll: %d kk: %d jj: %d ii: %d\n",k,j,i,ll,kk,jj,ii); printf("bcd1: %d bcd2: %d bcdir: %d\n",bcd1,bcd2,bcdir);



#define NP      8       /* number of primitive variables */

#define RHO     0       /* mnemonics for primitive vars */
#define UX      1
#define UY      2
#define UZ      3
#define BX      4
#define BY      5
#define BZ      6
#define UU      7 
#define LOOPP for(k=0;k<NP;k++)
#define LOOPTVDLF for(i=0;i<N1;i++)for(j=0;j<N2;j++)
extern void zeus2tvdlf(void);
extern void tvdlf2zeus(void);
extern void steptvdlf(void);
extern void step_ch(void);
extern void init_tvdlfgrid(void);


// seperate for now (combine loops later, but make new interp for 1d/2d/3d
#if(COMPDIM==1)
#include "global1dsup.h"
#elif(COMPDIM==2)
#include "global2dsup.h"
#elif(COMPDIM==3)
#include "global3dsup.h"
#endif
