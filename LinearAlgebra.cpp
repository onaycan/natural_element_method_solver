#include "stdafx.h"
#include "Nem3dCan.h"
#include "ClassHeaders.h"

void Matrixdet(double M[][3], double& detM)
{
detM=M[0][0]*(M[1][1]*M[2][2]-M[2][1]*M[1][2])+
     M[0][1]*(M[2][0]*M[1][2]-M[1][0]*M[2][2])+
     M[0][2]*(M[1][0]*M[2][1]-M[2][0]*M[1][1]);
}

void Matrixdet(ublas::c_matrix<double,3,3> M, double& detM)
{
detM=M(0,0)*(M(1,1)*M(2,2)-M(2,1)*M(1,2))+
     M(0,1)*(M(2,0)*M(1,2)-M(1,0)*M(2,2))+
     M(0,2)*(M(1,0)*M(2,1)-M(2,0)*M(1,1));
}


int MatrixInv(double M[][3], double Minv[][3])
{
int success=0; 
double detM; 
Minv[0][0]=M[1][1]*M[2][2]-M[2][1]*M[1][2];
Minv[0][1]=M[0][2]*M[2][1]-M[2][2]*M[0][1];
Minv[0][2]=M[0][1]*M[1][2]-M[1][1]*M[0][2];


Minv[1][0]=M[1][2]*M[2][0]-M[2][2]*M[1][0];
Minv[1][1]=M[0][0]*M[2][2]-M[2][0]*M[0][2];
Minv[1][2]=M[0][2]*M[1][0]-M[1][2]*M[0][0];


Minv[2][0]=M[1][0]*M[2][1]-M[2][0]*M[1][1];
Minv[2][1]=M[0][1]*M[2][0]-M[2][1]*M[0][0];
Minv[2][2]=M[0][0]*M[1][1]-M[1][0]*M[0][1]; 
Matrixdet(M,detM);
if(detM!=0)
success=1; 
for(int r=0;r<3;r++)
for(int c=0;c<3;c++)
Minv[r][c]=Minv[r][c]/detM;  
return success; 
}


ublas::matrix<double> MatrixInv(ublas::c_matrix<double,3,3> M, double &_detM)
{
ublas::c_matrix<double,3,3> Minv; 
Minv(0,0)=M(1,1)*M(2,2)-M(2,1)*M(1,2);
Minv(0,1)=M(0,2)*M(2,1)-M(2,2)*M(0,1);
Minv(0,2)=M(0,1)*M(1,2)-M(1,1)*M(0,2);


Minv(1,0)=M(1,2)*M(2,0)-M(2,2)*M(1,0);
Minv(1,1)=M(0,0)*M(2,2)-M(2,0)*M(0,2);
Minv(1,2)=M(0,2)*M(1,0)-M(1,2)*M(0,0);

Minv(2,0)=M(1,0)*M(2,1)-M(2,0)*M(1,1);
Minv(2,1)=M(0,1)*M(2,0)-M(2,1)*M(0,0);
Minv(2,2)=M(0,0)*M(1,1)-M(1,0)*M(0,1); 

Matrixdet(M,_detM);
Minv=Minv/_detM;
return Minv; 
}

//can: returns the length of a ublas vector
double len(ublas::c_vector<double,3> v)
{
return sqrt(prec_inner_prod(v,v));
}


//can:returns the cross product of two ublas vector in 3d 
ublas::c_vector<double,3> cross(ublas::c_vector<double,3> v1,ublas::c_vector<double,3> v2)
{
ublas::c_vector<double,3> result; 

result[0]=v1[1]*v2[2]-v2[1]*v1[2];
result[1]=-v1[0]*v2[2]+v2[0]*v1[2];
result[2]=v1[0]*v2[1]-v2[0]*v1[1];

return result; 
}


int sign(int value)
{
int result=0;
if(value>0)
result=1;
if(value<0)
result=-1; 
return result;
}

