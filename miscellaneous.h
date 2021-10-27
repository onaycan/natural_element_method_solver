

//can:START DECLERATIONS OF CALCULATE FUNCTIONS OF MISCELLANEOUS
double Calculate_tetrahedravolume(double _Coord[]);
int InsideOutside_tetrahedra_simple(vector<Node*> &Nodes, 
                                    Delaunay *_tetrahedra,
                                    ublas::c_vector<double,3> _normal,
                                    int corner);
//can:END DECLERATIONS OF CALCULATE FUNCTIONS OF MISCELLANEOUS