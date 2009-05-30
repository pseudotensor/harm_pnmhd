///////////////////////////
//
// Reads in the grid files and dump files a la Jon's Zeus code
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

class DumpReader
{
 public:
  DumpReader();
  
  void read_grid(std::string grid_file);
  void read_dump(std::string dump_file);
  
  bool is_grid_read() const;
  bool is_dump_read() const;

  std::vector<double>& grid(unsigned int dir);
  std::vector<double>& density();
  std::vector<double>& internal_energy();
  std::vector<double>& velocity(unsigned int dir);

 private:
  bool _is_grid_read, _is_dump_read;
  std::vector<double> _x[3], _rho, _u, _v[3];
};
DumpReader::DumpReader()
  : _is_grid_read(false), _is_dump_read(false)
{
}
bool DumpReader::is_grid_read() const
{
  return _is_grid_read;
}
bool DumpReader::is_dump_read() const
{
  return _is_dump_read;
}
std::vector<double>& DumpReader::grid(unsigned int dir)
{
  return _x[dir];
} 
std::vector<double>& DumpReader::density()
{
  return _rho;
} 
std::vector<double>& DumpReader::internal_energy()
{
  return _u;
} 
std::vector<double>& DumpReader::velocity(unsigned int dir)
{
  return _v[dir];
} 

void DumpReader::read_grid(std::string grid_file)
{
  std::ifstream in(grid_file.c_str());
  if (!in.is_open())
  {
    std::cerr << "  Couldn't open " << grid_file << " in DumpReader\n";
    std::exit(1);
  }
  else
    std::cerr << "  Reading in grid file " << grid_file << '\n';

  // First kill the headers
  in.ignore(4096,'\n');
  in.ignore(4096,'\n');
  in.ignore(4096,'\n');

  // Now read in i, j, k and x1, x2, x3
  int ijunk;
  double djunk;
  std::vector<int> i, j, k;
  std::vector<double> x1, x2, x3;

  do {
    in >> ijunk;  // Grid #

    in >> ijunk;  // k
    k.push_back(ijunk);
    in >> ijunk;  // j
    j.push_back(ijunk);
    in >> ijunk;  // i
    i.push_back(ijunk);

    in >> djunk; // dx1
    in >> djunk; // dx2
    in >> djunk; // dx3

    in >> djunk; // x1
    x1.push_back(djunk);
    in >> djunk; // x2
    x2.push_back(djunk);
    in >> djunk; // x3
    x3.push_back(djunk);

    in.ignore(4096,'\n'); // Kill rest of line

  } while (!in.eof());


  // Get rid of last garbage value
  i.pop_back();
  j.pop_back();
  k.pop_back();
  x1.pop_back();
  x2.pop_back();
  x3.pop_back();

  // Reset the sizes of internal arrays
  _x[0].resize(i[i.size()-1]-i[0]+1);
  _x[1].resize(j[j.size()-1]-j[0]+1);
  _x[2].resize(k[k.size()-1]-k[0]+1);
  
  // Fill the arrays with dumb loop (to avoide issues with Fortran vs. C ordering)
  for (size_t index=0; index<i.size(); index++)
  {
    _x[0][i[index]-i[0]] = x1[index];
    _x[1][j[index]-j[0]] = x2[index];
    _x[2][k[index]-k[0]] = x3[index];
  }

  _is_grid_read = 0; //true;

  in.close();

  /*
  // DEBUGGING

  std::cerr << std::setw(15) << i[i.size()-1]
	    << std::setw(15) << j[j.size()-1]
	    << std::setw(15) << k[k.size()-1]
	    << std::setw(15) << x1[x1.size()-1]
	    << std::setw(15) << x2[x2.size()-1]
	    << std::setw(15) << x3[x3.size()-1]
	    << '\n';


  std::cerr << "N: " << _x[0].size() << ' ' << _x[1].size() << ' ' << _x[2].size() << '\n';
  for (size_t index=0; index<_x[0].size(); index++)
    std::cout << std::setw(5) << index
	      << std::setw(15) << _x[0][index]
	      << std::endl;
  std::cout << "\n\n";
  for (size_t index=0; index<_x[1].size(); index++)
    std::cout << std::setw(5) << index
	      << std::setw(15) << _x[1][index]
	      << std::endl;
  std::cout << "\n\n";
  for (size_t index=0; index<_x[2].size(); index++)
    std::cout << std::setw(5) << index
	      << std::setw(15) << _x[2][index]
	      << std::endl;
  std::cout << "\n\n";
  */
}

void DumpReader::read_dump(std::string dump_file)
{
  std::ifstream in(dump_file.c_str());
  if (!in.is_open())
  {
    std::cerr << "  Couldn't open " << dump_file << " in DumpReader\n";
    std::exit(1);
  }
  else
    std::cerr << "  Reading in dump file " << dump_file << '\n';

  _is_dump_read = true;


  // First kill the headers
  in.ignore(4096,'\n');
  in.ignore(4096,'\n');
  in.ignore(4096,'\n');
  in.ignore(4096,'\n');
  in.ignore(4096,'\n');
  in.ignore(4096,'\n');
  in.ignore(4096,'\n');

  // Now read in density, internal energy, velocities
  double djunk;
  _rho.resize(0);
  _u.resize(0);
  for (unsigned int dir=0; dir<3; dir++)
    _v[dir].resize(0);


  //djunk = 0;
  for (;!in.eof();)
  {
    in >> djunk; // rho
    _rho.push_back(djunk);
    in >> djunk; // u
    _u.push_back(djunk);

    in >> djunk; // pot

    for (unsigned int dir=0; dir<3; dir++)
    {
      in >> djunk; // v1
      _v[dir].push_back(djunk);
    }
    
    in.ignore(4096,'\n'); // Kill rest of line
  }

  // Get rid of last garbage value
  _rho.pop_back();
  _u.pop_back();
  for (unsigned int dir=0; dir<3; dir++)
    _v[dir].pop_back();

  in.close();


  /*
  // DEBUGGING
  std::cerr << std::setw(15) << _rho[_rho.size()-1]
	    << std::setw(15) << _u[_u.size()-1]
	    << std::setw(15) << _v[0][_v[0].size()-1]
	    << std::setw(15) << _v[1][_v[1].size()-1]
	    << std::setw(15) << _v[2][_v[2].size()-1]
	    << '\n';
  */
}
