
//can::the determinant of a matrix of size 3 in static array form 
void Matrixdet(double M[][3], double& detM);
//can:determinant of a 3*3 matrix in ublas form 
void Matrixdet(ublas::c_matrix<double,3,3> M, double& detM);
//ca:inverse of a 3*3 matrix in array form 
int MatrixInv(double M[][3], double Minv[][3]);
//can:inversion of a 3*3 matrix in ublas form 
ublas::matrix<double> MatrixInv(ublas::c_matrix<double,3,3> M, double &_detM);
//can:length of a ublas vector 
double len(ublas::c_vector<double,3> v);
//can:returns the cross product of two ublas vector in 3d 
ublas::c_vector<double,3> cross(ublas::c_vector<double,3> v1,ublas::c_vector<double,3> v2);
//can: returns the sign of an integer 
int sign(int value);
