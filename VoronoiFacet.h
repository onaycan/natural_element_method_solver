class VoronoiFacet

{

private: 

int voronoifacetlabel; //the label of this 
int facetborder; //can: the border facet is a facet where two sides are borders 
int sidenodes[2]; //can: nodes on the sides of the face 

double facetarea; //can: the area of the facet 
ublas::c_vector<double,3> facetcentroid; //can: the facet centroid is not neccessarily overlapping
//-can: with the midpoint of connective nodes 
ublas::c_vector<double,3> facetleftnormal; //can; the normal according to the left node 

vector<int> polyvoronoivertices; //connective vertices




public: 
    //decleration of class node as friend 
friend class Node;
//Constructers 
VoronoiFacet() {} //Default Constructer 
VoronoiFacet(int _voronoifacetlabel,
             int _sidenodes[],
             vector<int> _polyvoronoivertices); //main constructer 
VoronoiFacet& operator=(const VoronoiFacet& _VF);//copy assignment 

//can:START DECLERATIONS OF SET FUNCTIONS OF VORONOIFACET
void Set_facetborder(int _facetborder); 
//can:END DECLERATIONS OF SET FUNCTIONS OF VORONOIFACET


//can:START DECLERATIONS OF GET FUNCTIONS OF VORONOIFACET
vector<int> Get_polyvoronoivertices();
int Get_facetborder(); 
ublas::c_vector<double,3> Get_facetcentroid();
int* Get_sidenodes();
//can:END DECLERATIONS OF GET FUNCTIONS OF VORONOIFACET

//can: START DECLERATIONS OF CALCULATE FUNCTIONS OF VORONOIFACET
void Calculate_FacetProperties(vector<VoronoiVertex*> VoronoiVertices,
                               vector<Node*> Nodes);
//can: END DECLERATIONS OF CALCULATE FUNCTIONS OF VORONOIFACET


}; 