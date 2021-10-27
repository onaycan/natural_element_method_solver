

class Hull
{

private: 
string Hull_name; //can:hull name, which can be specified by the user 
string Hull_commandtab; //can:command tab for the hull functions 

int griping_sequence; //can: determines the mshing order of this hull 
int Hull_nonodes;//can: number of nodes in the hull, irrespective of total=featured+original
int Hull_nonodes_original;//can: the number of hull nodes which are unfeatured, thus original 
int Hull_nodelaunays; //can: the number of delaunay tetrahedras of the hull as the output of the qhull
int Hull_novertices; //can: number of vertices in the hull
int Hull_nofacets; //can: number of facets in the hull

double averagedelaunayvolume; //can:the average delaunayvolume for feasibility check 
double averagevertextocenter; //can:the average value of vertex to the center of the delaunay
double featuringtolerance; //can:featuring tolerance of the hull 

ifstream Hull_cloudOriginalinput; //can: To read, it is opened as input file 
ifstream Hull_meshlessinput; //can:the meshless input as qhull output 
ifstream Hull_delaunayinput; //can:delaunay input as qhull output 
ifstream Hull_voronoiinput; //can:voronoiinput as qhull output 
ifstream Hull_Constrains; //can:the constrains of the hull, which is valid for the first gripe of first hull 

ofstream Hull_cloudFeaturedoutput; //can: The featured input is opened as an output file 
ofstream Hull_qhulltypeinput;//can:qhull type point cloud input which is internally prepareds
ofstream Hull_debugfile; //can:denugfile for manual dbugging 
ofstream Hull_GiDvoronoifile; //can:voronoi file for in the GiD ascii format
ofstream Hull_GiDvoronoifile_post;//can:post result file of the voronoi diagramm 
ofstream Hull_GiDdelaunayfile; //can:delaunay file 
ofstream Hull_GiDdelaunayfile_post; //can:post result delaunay file 
ofstream Hull_Gmshfile; //can:mesh in the Gmsh format
ofstream Hull_qhullrun; //can: a bat file which activates the qhull exe 

vector<Node*> Hull_Nodes; //can: vector of the nodes of the hull 
vector<Delaunay*> Hull_Delaunays; //can: delaunays of the hull
vector<VoronoiVertex*> Hull_VoronoiVertices; // can: voronoi vertices of the hull
vector<VoronoiFacet*> Hull_VoronoiFacets; //can: voronoi facets of the hull

public:
//can: very default constructer of the hull 
Hull (){}
//can: bearing hull acts as a long constructer 


//can: START DECLERATIONS OF BEARYOURSELF FUNCTIONS OF THE HULL
void Hull_Bear_Yourself(string _Hull_name);
//can::this function determines the input output and griping sequencial issues 
void Hull_Manipulate_Gripes();
//can::this function manipulates the input and output files 
void Hull_Manipulate_inoutfiles(string _CurrentCloudFileDirectory);
//can:converts the given file directory into the qhull input type
void Hull::Hull_convertintoqhullinput(string _CurrentCloudFileDirectory); 
//can:this file generates the qhull run bat file 
void Generate_qhullrunbat(ifstream &Directoryfile);
//can:this function gripes the hull once. It constrains delaunay & finds nodel normals
//-can:& preperas for the featured hull
void Hull_HaveInitialGripe();
//can:reads the nodes and delaunays from the qhull output 
void Hull_InitialNodeDelaunay_Reader();
//can:reads the vertices, does not generates objects, 
//-can:done for bordery and normal definitions for featuring of the initial Hull
void Hull_InitialVoronoi_Reader();
//can: this function generates the featured output 
void Hull_GenerateFeaturedInputNhull(string _CurrentCloudFileDirectory);
//can:The featured gripe of the hull
void Hull_HaveFeaturedGripe();
//can:the featured node and delaunay reader 
void Hull_FeaturedNodeDelaunay_Reader();
//can: The featured voronoi Reader
void Hull_FeaturedVoronoi_Reader();
//can: END DECLERATIONS OF BEARYOURSELF FUNCTIONS OF THE HULL

//can: START DECLERATIONS OF GET FUNCTIONS OF THE HULL
int Hull_Get_Hull_nonodes_original();
int Hull_Get_Hull_nonodes();
int Hull_Get_Hull_nofacets();
double Get_featuringtolerance();
vector<Node*> Hull_Get_Hull_Nodes();
vector<VoronoiFacet*> Hull_Get_Hull_VoronoiFacets();
//can: END DECLERATIONS OF GET FUNCTIONS OF THE HULL


//can: START DECLERATIONS OF CALCULATE FUNCTIONS OF THE HULL
void Hull_Calculate_DelaunayProperties();
void Hull_CalculateNodeNormalsviaDelaunay();
void Hull_Eliminate_illnormals();
void Hull_Gather_nodenormals();
void Hull_Set_bsec();
void Hull_Calculate_FacetProperties();
//can: END DECLERATIONS OF CALCULATE FUNCTIONS OF THE HULL


//can: START DECLERATIONS OF SHOWYOURSELF FUNCTIONS 
void Hull_ShowYourself(string outputtype);
void Hull_GiD_delaunaymesh();
void Hull_GiD_delaunaypost_static();
void Hull_GiD_voronoimesh();
//can: END DECLERATIONS OF SHOWYOURSELF FUNCTIONS 

};