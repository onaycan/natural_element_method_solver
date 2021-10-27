class Delaunay 

{

private: 

int delaunaylabel; //can:label of the this* delaunay
int delaunayfeatured; //can:a boolean for determining if the delaunay is featured or not 
int delaunayfeasibility;//can: a boolean for determining the feasibility of the delaunay
int inversioninfo; //can: inversion info is zero for undeterminable (nonconforming) tetrahedras, 
//-can:which can be found in structured outputs of qhull

double delaunayvolume; //can:the delaunayvolume as read from the qhull output, not robust 
double delaunayvolume_calc;//can:the calculated delaunayvolume 
double delaunayradius; //can: the radius of the delaunay sphere 
double vertextocenter; //can:vertex to center distance of this delaunay
ublas::c_vector<double,3> delaunaygeocenter; //can: the geometric center of the delaunay tetrahedral
ublas::c_vector<double,3> delaunayorigin; //can: the spherical center of the delaunay


ublas::c_vector<int,4> delaunaynodes; //can:the connectivities of the delaunay 

public: 
//can:START DECLERATIONS OF CONSTRUCTERS OF DELAUNAY
//can:Default Constructer of delaunay
Delaunay() {} 
//can:main constructer
Delaunay(int _delaunaylabel,ublas::c_vector<int,4> _delaunaynodes);  
//can:copy constructer 
Delaunay(const Delaunay& _D);
//can:copy assignment
Delaunay& operator=(const Delaunay& _D); 
//can:END DECLERATIONS OF CONSTRUCTERS OF DELAUNAY


//can:START DECLERATIONS OF SET FUNCTIONS OF DELAUNAY
void Set_delaunayvolume(double _delaunayvolume);
void Set_delaunayvolume_calc(double _delaunayvolume_calc); 
void Set_delaunaygeocenter(ublas::c_vector<double,3> _delaunaygeocenter); 
void Set_delaunayorigin(ublas::c_vector<double,3> _delaunayorigin); 
void Set_inversioninfo(int _inversioninfo);
void Set_delaunayradius(double _delaunayradius); 
void Set_vertextocenter(double _vertextocenter);
void Set_delaunayfeatured(int _delaunayfeatured);
//can:END DECLERATIONS OF SET FUNCTIONS OF DELAUNAY


//can:START DECLERATIONS OF GET FUNCTIONS OF DELAUNAY
int Get_delaunayfeatured();
double Get_delaunayvolume(); 
ublas::c_vector<int,4> Get_delaunaynodes();
int Get_delaunayfeasibility(); 
//can:END DECLERATIONS OF GET FUNCTIONS OF DELAUNAY

//can: START DECLERATIONS OF THE CALCULATE TYPE FUNCTIONS 
void Delaunay_unfeasibilizer(vector<Node*> Nodes,
                             double _alpha_vertextocenter,
                             double _alpha_longesttwoedges,
                             double _alpha_cosangle);
void Delaunay_postunfeasibilizer();
void Calculate_NodeNormalsviaDelaunay(vector<Node*> Nodes);
//can: END DECLERATIONS OF THE CALCULATE TYPE FUNCTIONS 

};