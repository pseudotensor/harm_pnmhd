////////////////////////////////////
//
// Reads in output dumps from Jon's Zeus code and
// interpolates them to a uniform grid.  This assumes
// that the nonuniform grid is diagonal with a Cartesian
// grid.
//
// g++ -O3 -o dump_interp main.cpp

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <sstream>

#include "interpolator.h"
#include "dump_reader.h"

int main(int argc, char* argv[])
{
  // Limits
  bool xmin_set[3], xmax_set[3];
  double xmin[3], xmax[3], dx[3];

  // Number of interpolation points
  bool Nx_set[3];
  int Nx[3];

  for (int dir=0; dir<3; dir++)
    xmin_set[dir] = xmax_set[dir] = Nx_set[dir] = false;

  // Original File Directory
  std::string input_prefix="";

  // Interpolated file prefix
  std::string output_prefix="";
  bool use_interpolated_file_names=false;
  
  // Dump files
  std::string dump_file = "Data/dump0000.dat";
  int fibegin=0, fiend=1;

  // Skip stuff
  bool skip_dumps=false, skip_gparam=false, skip_grids=false;

  ///// THIS IS WHERE WE PUT IN THE COMMAND LINE ARGS STUFF
  ///// FOR NOW JUST USE THE DEFAULTS
  
  for (int ia=0; ia<argc; ia++) // Loop over arguments
  {
    // Make argument into string for easy parsing
    std::string arg(argv[ia]);
    // Get option name and value, if any
    unsigned int index = arg.find_first_of('=');
    std::string opt = arg.substr(0,index);
    std::string val = arg.substr(index+1);
    // Check against list of options
    // Help
    if (opt == "-h" || opt == "--help" || argc==1)
    {
      std::cerr << "Usage: dump_interp [OPTIONS] -i=[INPUT FILE DIRECTORY]\n"
		<< "where available options are:\n\n"
		<< "  -i=<DIRECTORY/>\n"
		<< "    Provides the directory of the 0_gparam.par, 0_gridact1.par,\n"
		<< "    0_gridact2.par and dump????.dat files.  If this is not given\n"
		<< "    the -uin will be set and output file names will be tagged.\n"
		<< "    (see below)\n\n"
		<< "  -o=<string>\n"
		<< "    Provides a prefix for the output files: 0_gparam.par,\n"
		<< "    0_gridact1.par, 0_gridact2.par and dump????.dat.  By default\n"
		<< "    these are generated in the current directory.\n\n"
		<< "  -is=<index>\n"
		<< "    Defines a single dump file to be interpolated, dump<index>.dat.\n\n"
		<< "  -if=<index>\n"
		<< "    Sets the first dump index in a loop over dumps to be interpolated.\n"
		<< "    By default this is 0\n\n"
		<< "  -il=<index>\n"
		<< "    Sets the last (inclusive) dump index in a loop over dumps to be\n"
		<< "    interpolated.  This is set to 0 by default, so only dump0000.dat\n"
		<< "    is interpolated.\n\n"
		<< "  -Na=<index>\n"
		<< "    Sets the number of grid points in all directions to interpolate the\n"
		<< "    dumps to.  By default these are the same as those given in\n"
		<< "    0_gparam.par.\n\n"
		<< "  -Nx=<index>, -Ny=<index>, -Nz=<index>\n"
		<< "    Sets the number of grid points in each direction separately.\n\n"
		<< "  -amin=<value>, -amax=<value>\n"
		<< "    Sets the minimum/maximum range of the interpolation area of all\n"
		<< "    dimensions to <value>.  This must be contained within the range\n"
		<< "    of the raw dumps.\n\n"
		<< "  -xmin=<value>, -ymin=<value>, -zmin=<value>\n"
		<< "  -xmax=<value>, -ymax=<value>, -zmax=<value>\n"
		<< "    Sets the minimum/maximum range of the interpolation area of each\n"
		<< "    dimension separately.  This must be contained within the range of\n"
		<< "    the raw dumps.\n\n"
		<< "  -nodumps\n"
		<< "    Supresses the output of interpolated dump files.\n\n"
		<< "  -nogparam\n"
		<< "    Supresses the output of new 0_gparam.par file.\n\n"
		<< "  -nogrids\n"
		<< "    Supresses the output of new 0_gridact1,2.par files.\n\n"
                << "  -uin, -useinames\n"
                << "    Uses interpolated file names (0_igparam.par, 0_igridact?.par,\n"
                << "    idump????.dat  instead of 0_gparam.par, 0_gridact?.par,\n"
		<< "    dump????.dat).\n\n";
      std::exit(0);
    }
    if(ia==0) continue; // skip argv[0]
    if (opt == "-i")
    {
      input_prefix=val;
    }
    if (opt == "-o")
    {
      output_prefix=val;
    }
    if (opt == "-is")
    {
      fibegin = atoi(val.c_str());
      fiend = atoi(val.c_str())+1;
    }
    if (opt == "-if")
    {
      fibegin = atoi(val.c_str());
    }
    if (opt == "-il")
    {
      fiend = atoi(val.c_str())+1;
    }
    if (opt == "-Na")
    {
      for (unsigned int dir=0; dir<3; dir++)
      {
	Nx[dir] = atoi(val.c_str());
	Nx_set[dir] = true;
      }
    }
    if (opt == "-Nx")
    {
      Nx[0] = atoi(val.c_str());
      Nx_set[0] = true;
    }
    if (opt == "-Ny")
    {
      Nx[1] = atoi(val.c_str());
      Nx_set[1] = true;
    }
    if (opt == "-Nz")
    {
      Nx[2] = atoi(val.c_str());
      Nx_set[2] = true;
    }
    if (opt == "-amin")
    {
      for (unsigned int dir=0; dir<3; dir++)
      {
	xmin[dir] = atof(val.c_str());
	xmin_set[dir] = true;
      }
    }
    if (opt == "-xmin")
    {
      xmin[0] = atof(val.c_str());
      xmin_set[0] = true;
    }
    if (opt == "-ymin")
    {
      xmin[1] = atof(val.c_str());
      xmin_set[1] = true;
    }
    if (opt == "-zmin")
    {
      xmin[2] = atof(val.c_str());
      xmin_set[2] = true;
    }
    if (opt == "-amax")
    {
      for (unsigned int dir=0; dir<3; dir++)
      {
	xmax[dir] = atof(val.c_str());
	xmax_set[dir] = true;
      }
    }
    if (opt == "-xmax")
    {
      xmax[0] = atof(val.c_str());
      xmax_set[0] = true;
    }
    if (opt == "-ymax")
    {
      xmax[1] = atof(val.c_str());
      xmax_set[1] = true;
    }
    if (opt == "-zmax")
    {
      xmax[2] = atof(val.c_str());
      xmax_set[2] = true;
    }
    if (opt == "-nodumps")
    {
      skip_dumps = true;
    }
    if (opt == "-nogparam")
    {
      skip_gparam = true;
    }
    if (opt == "-nogrids")
    {
      skip_grids = true;
    }
    if (opt == "-uin" || opt == "-useinames")
    {
      use_interpolated_file_names = true;
    }
  }

  // Check to make sure input prefix was defined
  if (input_prefix=="")
  {
    std::cerr << "  To provide an input directory, use the -i option.\n"
	      << "  Type dump_interp --help for more.\n"
	      << "  Using interpolated names (-uin) for in place interpolation.\n\n";
    use_interpolated_file_names = true;
  }


  //////////////////////////// 0_gparams.h stuff ///////////////////////////////////////
  // Read in the grid_params file and output the appropriate new file
  char buff[4096];
  int ijunk;
  double djunk;
  std::stringstream gpi_file;
  gpi_file << input_prefix << "0_gparam.par";
  std::ifstream gpin(gpi_file.str().c_str());
  if (!gpin.is_open())
  {
    std::cerr << "  Couldn't open " << gpi_file.str() << "\n";
    std::exit(1);
  }
  std::stringstream gpo_file;
  if (use_interpolated_file_names)
    gpo_file << output_prefix << "0_igparam.par";
  else
    gpo_file << output_prefix << "0_gparam.par";
  std::ofstream gpout;
  if (!skip_gparam)
  {
    gpout.open(gpo_file.str().c_str());
    if (!gpout.is_open())
    {
      std::cerr << "  Couldn't open " << gpo_file.str() << '\n';
      std::exit(1);
    }
  }
  //  Output first headers (PVER TYPE, etc.)
  for (int j=0; j<3; j++)
  {
    gpin.getline(buff,4096,'\n');
    if (!skip_gparam)
      gpout << buff << '\n';
  }
  //  Output the new/old number cells in each direction
  if (!skip_gparam)
    gpout << ' ';
  for (int dir=0; dir<3; dir++)
  {
    gpin >> ijunk;
    if (!Nx_set[dir])
      Nx[dir] = ijunk;
    if (!skip_gparam)
      gpout << std::setw(5) << Nx[dir];
  }
  if (!skip_gparam)
    gpout << '\n';
  gpin.ignore(4096,'\n'); // Get end of line
  //  Get the next header (x1-start ...)
  gpin.getline(buff,4096,'\n');
  if (!skip_gparam)
    gpout << buff << '\n';
  //  Read in, and output the new/old dimensions
  gpin.precision(18);
  if (!skip_gparam)
    gpout << ' ';
  for (int dir=0; dir<3; dir++)
  {
    gpin >> djunk;
    if (!xmin_set[dir])
      xmin[dir] = djunk;
    if (xmin[dir]<djunk)
    {
      std::cerr << "xmin[" << dir << "] = " << xmin[dir] << "  is less than that in the raw dump files.\n"
		<< "The dump file value will be used.\n";
      xmin[dir] = djunk;
    }
    if (!skip_gparam)
      gpout << std::setw(22) << xmin[dir];
  }
  for (int dir=0; dir<3; dir++)
  {
    gpin >> djunk;
    if (!xmax_set[dir])
      xmax[dir] = djunk;
    if (xmax[dir]>djunk)
    {
      std::cerr << "xmax[" << dir << "] = " << xmin[dir] << "  is greater than that in the raw dump files.\n"
		<< "The dump file value will be used.\n";
      xmax[dir] = djunk;
    }
    if (!skip_gparam)
      gpout << std::setw(22) << xmax[dir];
  }
  if (!skip_gparam)
    gpout << '\n';
  gpin.ignore(4096,'\n');
  // Now just copy the rest
  if (!skip_gparam)
    for (;!gpin.eof();)
    {
      gpin.getline(buff,4096,'\n');
      gpout << buff << '\n';
    }
  gpin.close();
  if (!skip_gparam)
    gpout.close();

  if (!skip_gparam)
    std::cerr << "\tFinished writing new " << gpo_file.str() << " file.\n";

  ///////////////////////////////////////////////////////////////////////////////////

  
  ////////////// 0_gridact1.par & 0_gridact2.par ////////////////////////////////////
  DumpReader dr1, dr2;
  int grid_number[2];
  for (int grid=0; grid<2; grid++)
  {
    // Read in grid file
    std::stringstream gi_file, go_file;
    if (grid==0)
    {
      gi_file << input_prefix << "0_gridact1.par";
      if (use_interpolated_file_names)
	go_file << output_prefix << "0_igridact1.par";
      else
	go_file << output_prefix << "0_gridact1.par";
      dr1.read_grid(gi_file.str().c_str());
    }
    else if (grid==1)
    {
      gi_file << input_prefix << "0_gridact2.par";
      if (use_interpolated_file_names)
	go_file << output_prefix << "0_igridact2.par";
      else
	go_file << output_prefix << "0_gridact2.par";
      dr2.read_grid(gi_file.str().c_str());
    }

    // Create new grid file
    std::ifstream gin(gi_file.str().c_str());
    if (!gin.is_open())
    {
      std::cerr << "  Couldn't open " << gi_file.str() << '\n';
      std::exit(1);
    }
    std::ofstream gout;
    if (!skip_grids)
    {
      gout.open(go_file.str().c_str());
      if (!gout.is_open())
      {
	std::cerr << "  Couldn't open " << go_file.str() << '\n';
	std::exit(2);
      }
    }
    gin.getline(buff,4096,'\n');
    if (!skip_grids)
      gout << buff << '\n';
    gin.getline(buff,4096,'\n'); 
    if (!skip_grids)
      gout << buff << '\n';
    gin.getline(buff,4096,'\n');
    if (!skip_grids)
      gout << buff << '\n';

    // Get some values
    gin >> grid_number[grid];
    for (int j=0; j<3; j++)
      gin >> ijunk;
    for (int j=0; j<6; j++)
      gin >> djunk;
    gin.getline(buff,4096,'\n'); // This contains the remaining line
    for (int dir=0; dir<3; dir++)
      dx[dir] = (xmax[dir]-xmin[dir])/Nx[dir];
    int i[3];
    // LOOP ORDER SHOULD BE CONSISTENT WITH THE ORIGINAL ORDERING
    if (!skip_grids)
      for (i[2]=0; i[2]<Nx[2]; i[2]++)
	for (i[1]=0; i[1]<Nx[1]; i[1]++)
	  for (i[0]=0; i[0]<Nx[0]; i[0]++)
	  {
	    gout << std::setw(5) << grid_number[grid];
	    for (int dir=2; dir>=0; dir--)
	      gout << std::setw(5) << i[dir];
	    gout.precision(15);
	    for (int dir=0; dir<3; dir++)
	      gout << std::setw(22) << dx[dir];
	    for (int dir=0; dir<3; dir++)
	      gout << std::setw(22) << xmin[dir] + dx[dir]*i[dir] + (grid_number[grid]==1 ? 0.0 : 0.5*dx[dir]); // Offset for center cells
	    gout << buff << '\n'; // Just copy the rest of the line
	  }
    gin.close();
    if (!skip_grids)
      gout.close();

    if (!skip_grids)
      std::cerr << "\tFinished writing new " << go_file.str() << " file.\n";
  }

  // Loop over dump files
  for (int fi=fibegin; fi<fiend && !skip_dumps; fi++)
  {
    // Now read in dump file, construct name from dump_root
    std::stringstream dfname;
    dfname << input_prefix << "dump" << std::setfill('0') << std::setw(4) << fi << ".dat";
    dump_file = dfname.str();

    // Open output file (prefix with an i the dump file)
    std::stringstream outfile;
    if (use_interpolated_file_names)
      outfile << output_prefix << "idump" << std::setfill('0') << std::setw(4) << fi << ".dat";
    else
      outfile << output_prefix << "dump" << std::setfill('0') << std::setw(4) << fi << ".dat";
    std::ofstream out(outfile.str().c_str());
    if (!out.is_open())
    {
      std::cerr << "  Couldn't open " << outfile.str() << '\n';
      std::exit(2);
    }

    // Output standard dump header shit
    std::ifstream din(dump_file.c_str());
    din.getline(buff,4096,'\n');
    out << buff << '\n';
    din.getline(buff,4096,'\n');
    out << buff << '\n';
    din.getline(buff,4096,'\n');
    out << buff << '\n';
    din >> djunk;
    out.precision(15);
    out << std::setw(22) << djunk;
    din >> ijunk;
    out << std::setw(7) << 1;
    din >> ijunk;
    int grid = ijunk;  // Determines which grid to use (1 or 2)
    out << std::setw(7) << ijunk << '\n';
    din.ignore(4096,'\n');
    din.getline(buff,4096,'\n');
    out << buff << '\n';
    out << std::setw(7) << Nx[0]
	<< std::setw(7) << Nx[1]
	<< std::setw(7) << Nx[2]
	<< '\n';
    din.ignore(4096,'\n');
    din.getline(buff,4096,'\n');
    out << buff << '\n';
    din.close();

    // SCREWINESS ASSOCIATED WITH HAVING A PROPER ARRAY OF DumpReader OBJECTS, WHICH I DON'T UNDERSTAND.
    DumpReader* drptr;
    if (grid==0)
      drptr = &dr1;
    else
      drptr = &dr2;

    drptr->read_dump(dump_file);

    // Construct interpolators for each variable of interest
    DiagonalInterpolator3D< LinearInterpolator<3> > irho( drptr->grid(0),drptr->grid(1),drptr->grid(2) , drptr->density() );
    DiagonalInterpolator3D< LinearInterpolator<3> >   iu( drptr->grid(0),drptr->grid(1),drptr->grid(2) , drptr->internal_energy() );
    DiagonalInterpolator3D< LinearInterpolator<3> >  ivx( drptr->grid(0),drptr->grid(1),drptr->grid(2) , drptr->velocity(0) );
    DiagonalInterpolator3D< LinearInterpolator<3> >  ivy( drptr->grid(0),drptr->grid(1),drptr->grid(2) , drptr->velocity(1) );
    DiagonalInterpolator3D< LinearInterpolator<3> >  ivz( drptr->grid(0),drptr->grid(1),drptr->grid(2) , drptr->velocity(2) );


    double x0[3];
    out.precision(15);
    int i[3];
    x0[0] = 0.0;
    x0[1] = 0.0;
    x0[2] = 0.0;
    for (i[2]=0; i[2]<Nx[2]; i[2]++)
      for (i[1]=0; i[1]<Nx[1]; i[1]++)
	for (i[0]=0; i[0]<Nx[0]; i[0]++)
	{
      	  for (int dir=0; dir<3; dir++)
	    x0[dir] = xmin[dir] + dx[dir]*i[dir] + (grid_number[grid]==1 ? 0.0 : 0.5*dx[dir]); // Offset for center cells

	  //out << std::setw(22) << x0[0] << std::setw(22) << x0[1] << std::setw(22) << x0[2];

	  out << std::setw(22) << irho.value(x0)
	      << std::setw(22) << iu.value(x0)
	      << std::setw(22) << 0.0 // pot
	      << std::setw(22) << ivx.value(x0)
	      << std::setw(22) << ivy.value(x0)
	      << std::setw(22) << ivz.value(x0)
	      << std::setw(22) << 0.0 // bx1
	      << std::setw(22) << 0.0 // bx2
	      << std::setw(22) << 0.0 // bx3
	      << '\n';
	}
    out.close();

    std::cerr << "\tFinished writing new " << outfile.str() << '\n';
  }

  return 0;
}
