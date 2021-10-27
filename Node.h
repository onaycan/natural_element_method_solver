class Node 

{

private: 

int nodelabel; //can:label of the node 
int nodeborder; //can: the boolean determining the bordery of the node
int bsec; //can: boundary surface, edge and corner information of the node 
int nodefeatured;//can: a boolean which is used to determine if the node is featured or an original one 
int nodalyesgaussionno; //can: a boolean for determining if the node is nodal or gaussian

ublas::c_vector<double,3> X; //can: reference coordinates 
ublas::c_vector<double,3> nodenormal; //can: node normal of the current node 
vector<int> homedelaunays; //can:the delaunay tetrahedras having this node as connectivity

vector<int> brotherfacets; //can:the brother voronoi facets 
int nobrotherfacets; //can:the number of brother facets 
vector<int> brothernodes;//can: vector of brother nodes 
int nobrothernodes; //can:number of brother nodes 
vector<double> brothernodedist; //can:vector of distances to the brother nodes 

vector< ublas::c_vector<double,3> > nodenormals; //can: initial list of all node normals, 
//-can: which will be eliminated later on 

public: 
friend class Delaunay;
//can:START DECLERATIONS OF CONSTRUCTERS OF NODE 
//Default Constructer 
Node() {}
//can:full constructer
Node(int _nodelabel,ublas::c_vector<double,3> _X); 
//can:copy constructer (almost not in use)
Node(const Node& _N); 
//can: copy assignment (again almost not in usage)
Node& operator=(const Node& _N);
//can:END DECLERATIONS OF CONSTRUCTERS OF NODE 

//can:START DECLERATIONS OF PUSH FUNCTIONS OF NODE
void Push_homedelaunays(int _delaunaylabel);
void Push_nodenormal(ublas::c_vector<double,3> _nodenormal);
void Push_brotherfacets(int _brotherfacet);
void Push_brothernodes(int _brothernode);
void Push_brothernodedistances(Node* brotherN); 
//can:END DECLERATIONS OF PUSH FUNCTIONS OF NODE

//can:START DECLERATIONS OF SET FUNCTIONS OF NODE
void Set_nodeborder(int _nodeborder);
void Set_bsec();
void Set_nodefeatured(int _nodefeatured); 
void Set_nodalyesgaussionno(int _nodalyesgaussionno); 
//can:END DECLERATIONS OF SET FUNCTIONS OF NODE

//can:START DECLERATIONS OF GET FUNCTIONS OF NODE
int Get_nodelabel();
ublas::c_vector<double,3> Get_X();
int Get_nodeborder();
int Get_bsec();
int Get_nodefeatured();
int Get_nodalyesgaussionno();
ublas::c_vector<double,3> Get_nodenormal();
vector< ublas::c_vector<double,3> > Get_nodenormals();
//can:END DECLERATIONS OF GET FUNCTIONS OF NODE


//can: START DECLERATIONS OF CALCULATE FUNCTIONS OF THE NODE
void Eliminate_illnormals(vector<Delaunay*> Delaunays, vector<Node*> Nodes);
void Gather_nodenormals();
//can: END DECLERATIONS OF CALCULATE FUNCTIONS OF THE NODE

};