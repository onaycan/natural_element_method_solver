//can:boost include files for small sized linear algebraic operations 
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/matrix_expression.hpp>
#include <boost/numeric/ublas/storage.hpp>


//can:intel mkl lapack header files for large sized & complicated linear operations 
#include "mkl.h" 
#include "mkl_lapack.h" 
#include "mkl_blas.h" 
#include "mkl_service.h"

//can:standard headers 
#include <complex> 
#include <cstdlib>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <algorithm>
#include <vector>
#include <fstream> 
#include <list>
#include <windows.h> 

//can: definitions of canstants and namespaces 
#define PI 3.14159265
using namespace std;
namespace ublas = boost::numeric::ublas;

