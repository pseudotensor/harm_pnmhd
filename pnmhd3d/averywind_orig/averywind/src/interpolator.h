////////////////////////////////
//
// Class which encapsulates the interpolation functionality
//

#include <vector>
#include <algorithm>

template<class T>
class DiagonalInterpolator3D
{
 public:
  DiagonalInterpolator3D(std::vector<double>& x, std::vector<double>& y, std::vector<double>& z, std::vector<double>& f);

  double value(const double x[3]);

 private:
  T interp;
  
  std::vector<double> _x[3], _f;

  void get_lower_corner(const double x[3], size_t i[3]) const;

  // Assumes that it is ordered with z fastest
  size_t index(const size_t i[3]) const;
};

template<class T>
DiagonalInterpolator3D<T>::DiagonalInterpolator3D(std::vector<double>& x, std::vector<double>& y, std::vector<double>& z, std::vector<double>& f)
{
  if ( f.size() != x.size()*y.size()*z.size() )
  {
    std::cerr << "Interpolation array sizes are inconsistent in DiagonalInterpolator3D:\n"
	      << std::setw(20) << f.size()
	      << std::setw(10) << x.size()
	      << std::setw(10) << y.size()
	      << std::setw(10) << z.size()
	      << '\n';
    std::exit(0);
  }
  

  _x[0].resize( x.size() );
  for (size_t i=0; i<x.size(); i++)
    _x[0][i] = x[i];
  _x[1].resize( y.size() );
  for (size_t i=0; i<y.size(); i++)
    _x[1][i] = y[i];
  _x[2].resize( z.size() );
  for (size_t i=0; i<z.size(); i++)
    _x[2][i] = z[i];


  _f.resize( f.size() );
  for (size_t i=0; i<f.size(); i++)
    _f[i] = f[i];
}
template<class T>
inline void DiagonalInterpolator3D<T>::get_lower_corner(const double x[3], size_t i[3]) const
{
  for (unsigned int dir=0; dir<3; dir++)
  {
    std::vector<double>::const_iterator p = std::lower_bound(_x[dir].begin(),_x[dir].end(),x[dir]);
    int tmp = int(p-_x[dir].begin())-1;
    if (tmp>=int(_x[dir].size())-1)
      tmp = int(_x[dir].size())-2;
    if (tmp<0)
      tmp = 0;
    i[dir] = size_t(tmp);
  }
}
template<class T>
inline size_t DiagonalInterpolator3D<T>::index(const size_t i[3]) const
{
  // THIS MUST BE MATCHED WITH JON'S OUTPUT STRUCTURE (FASTEST ON X)
  return i[0] + _x[0].size()*( i[1] + _x[1].size() * i[2] );
}
template<class T>
double DiagonalInterpolator3D<T>::value(const double x[3])
{
  size_t ilc[3];
  get_lower_corner(x,ilc);

  size_t it[3], i[3];
  for (it[0]=0; it[0]<interp.size(0); it[0]++)
    for (it[1]=0; it[1]<interp.size(1); it[1]++)
      for (it[2]=0; it[2]<interp.size(2); it[2]++)
      {
	for (unsigned int dir=0; dir<3; ++dir)
	{
	  i[dir] = size_t( int(it[dir]) + int(ilc[dir]) + int(1 - int(interp.size(dir))/2) );
	  interp.x(dir,it) = _x[dir][i[dir]];
	}
	interp.f(it) = _f[ index(i) ];
      }

  return interp.value(x);
}







template<unsigned int DIM_>
class LinearInterpolator
{
 public:
  LinearInterpolator();
  ~LinearInterpolator();

  double& f(const size_t i[DIM_]);
  double& x(unsigned int dir, const size_t i[DIM_]);
  size_t size(unsigned int dir) const; 
  
  // The interpolation functionality
  double value(const double x[DIM_]);

 private:
  size_t stencil_index(const size_t i[DIM_]) const;
  void get_3Dindex(size_t index, size_t i[DIM_]) const;

  size_t _size[DIM_], _1Dsize;
  double *_f;
  double *_x[DIM_];
};


template<unsigned int DIM_>
LinearInterpolator<DIM_>::LinearInterpolator()
{
  _1Dsize = 1;
  for (unsigned int dir=0; dir<DIM_; dir++)
  {
    _size[dir] = 2;
    _1Dsize *= _size[dir];
  }
  _f = new double[_1Dsize];
  for (unsigned int dir=0; dir<DIM_; dir++)
    _x[dir] = new double[_1Dsize];
}
template<unsigned int DIM_>
LinearInterpolator<DIM_>::~LinearInterpolator()
{
  delete[] _f;
  for (unsigned int dir=0; dir<DIM_; dir++)
    delete[] _x[dir];
}

template<unsigned int DIM_>
inline size_t LinearInterpolator<DIM_>::stencil_index(const size_t i[DIM_]) const
{
  size_t index=i[0];
  for (unsigned int dir=1; dir<DIM_; dir++)
    index = _size[dir]*index + i[dir];
  return index;
}
template<unsigned int DIM_>
inline void LinearInterpolator<DIM_>::get_3Dindex(size_t index, size_t i[DIM_]) const
{
  for (int dir=int(DIM_)-1; dir>=0; dir--)
  {
    i[dir] = index%2;
    index /= 2;
  }
}

template<unsigned int DIM_>
inline double& LinearInterpolator<DIM_>::f(const size_t i[DIM_])
{
  return _f[stencil_index(i)];
}
template<unsigned int DIM_>
inline double& LinearInterpolator<DIM_>::x(unsigned int dir, const size_t i[DIM_])
{
  return _x[dir][stencil_index(i)];
}
template<unsigned int DIM_>
inline size_t LinearInterpolator<DIM_>::size(unsigned int dir) const
{
  return _size[dir];
}

////////////////////
//
//  Interpolation junk
//
template<unsigned int DIM_>
double LinearInterpolator<DIM_>::value(const double x0[DIM_])
{
  size_t i[DIM_], ip[DIM_];
  for (unsigned int dir=0; dir<DIM_; dir++)
    i[dir] = ip[dir] = 0;

  // Get the dx and 1-dx's
  double dx[DIM_][2];
  for (unsigned int dir=0; dir<DIM_; dir++)
  {
    ip[dir] = 1;
    dx[dir][1] = (x0[dir] - x(dir,i))/(x(dir,ip)-x(dir,i));
    dx[dir][0] = 1.0 - dx[dir][1];
    ip[dir] = 0;
  }

  double val = 0.0;
  double weight;
  for (size_t i1D=0; i1D<_1Dsize; i1D++)
  {
    get_3Dindex(i1D,i);
    weight=1;
    for (unsigned int dir=0; dir<DIM_; dir++)
      weight *= dx[dir][i[dir]];
    val += weight * f(i);
  }

  return val;
}
