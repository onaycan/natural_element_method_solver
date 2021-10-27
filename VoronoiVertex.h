class VoronoiVertex

{

private: 

int voronoivertexlabel; //label of the this voronoi vertex 
ublas::c_vector<double,3> Vertex_X; //vertex coordinates 



public: 
//Constructers 
VoronoiVertex() {} //Default Constructer 
VoronoiVertex(int _voronoivertexlabel,ublas::c_vector<double,3> _Vertex_X);   
VoronoiVertex& operator=(const VoronoiVertex& _VV);//copy assignment 


//can:START DECLERATIONS OF GET FUNCTIONS OF VORONOIVERTEX
int Get_voronoivertexlabel();
ublas::c_vector<double,3> Get_Vertex_X();
//can:END DECLERATIONS OF GET FUNCTIONS OF VORONOIVERTEX
}; 