/*itr = set_difference(a_triangles.begin(),a_triangles.end(),
	  b_triangles.begin(), b_triangles.end(),difference.begin());

  
  vertices_set vertices;

  for (itr = difference.begin(); itr != difference.end(); ++itr) {
	  for (int i = 0; i < 3; ++i) {
		  if ((*itr)->getVertex(i) != a || (*itr)->getVertex(i) != b) {
			  vertices.insert((*itr)->getVertex(i));
		  }
	  }
  }
*/

  //for (itr_t = a_triangles.begin(); itr_t != a_triangles.end();) {
	 // Triangle *t = *itr_t;
	 // vector<Vertex*> vex;

	 // if (t->HasVertex(a) && t->HasVertex(b)) {
		//  a_triangles.erase(itr_t++);
		//  continue;
	 // } else {
		//  ++itr_t;
	 // }
	 // 
	 // for (int i = 0; i < 3; ++i) {
		//  if (t->getVertex(i) != old) {
		//	  vex.push_back(t->getVertex(i));  
		//  }
	 // }
	 // if ( vex.size() == 2) {
		//AddTriangle(vex[0],vex[1],a);
	 // } else {
		//  continue;
	 // }
  //}
  //
  //

  //for (itr_t = b_triangles.begin(); itr_t != b_triangles.end();) {
	 // Triangle *t = *itr_t;
	 // vector<Vertex*> vex;

	 // if (t->HasVertex(a) && t->HasVertex(b)) {
		//  b_triangles.erase(itr_t++);
		//  continue;
	 // } else {
		//  ++itr_t;
	 // }
	 // 
	 // for (int i = 0; i < 3; ++i) {
		//  if (t->getVertex(i) != b) {
		//	  vex.push_back(t->getVertex(i));  
		//  }
	 // }
	 // if ( vex.size() == 2) {
		//AddTriangle(vex[0],vex[1],a);
	 // } else {
		//  continue;
	 // }
  //}
  //for (itr_t = a_triangles.begin(); itr_t != a_triangles.end();) {
	 // Triangle *t = *itr_t;
	 // RemoveTriangle(*itr_t);
	 // ++itr_t;
  //}
  //
  //for (itr_t = b_triangles.begin(); itr_t != b_triangles.end();) {
	 // Triangle *t = *itr_t;
	 // RemoveTriangle(*itr_t);
	 // ++itr_t;
	 // /*if (t->HasVertex(a) && t->HasVertex(b)) {
		//  RemoveTriangle(*itr_t);
		//  b_triangles.erase(itr_t++);
	 // } else {
		//  RemoveTriangle(*itr_t);
		//  ++itr_t;
	 // }*/
  //}
  //triangles_set copy_tri = triangles;
  //for (triangles_set::iterator itr = copy_tri.begin(); itr != copy_tri.end(); itr++) {
	 // Triangle *t = *itr;
	 // // remove the 1 or 2 triangles that touch this edge
	 // if (t->HasVertex(a) && t->HasVertex(b)) {
		//  RemoveTriangle(t);
		//  //b_triangles.erase(t);
	 // }
  //}
  //RemoveEdge(a,b);
  //set<Edge*> b_edges,a_edges;
  //set<Edge*>::iterator itr_e;
  //CollectEdgesWithVertex(b,b_edges);
  //CollectEdgesWithVertex(a,a_edges);

  //for (itr_e = b_edges.begin(); itr_e != b_edges.end(); ++itr_e) {
	 // Edge *e = *itr_e;
	 // RemoveEdge(e->getV1(),e->getV2());
	 // 
  //}
  //for (itr_e = a_edges.begin(); itr_e != a_edges.end(); ++itr_e) {
	 // Edge *e = *itr_e;
	 // //if ((e->getV1() == a || e->getV1() == b) && (e->getV2() == a || e->getV2() == b)) {
		// // continue;
	 // //}
	 // RemoveEdge(e->getV1(),e->getV2());
	 // 
  //}
  //
  //

  //RemoveVertex(b);

   //
  // we choose the vertex with the smaller id to be the averaged position.
  // the vertex with the larger id will be removed from the mesh.
  
  
  /*set<Triangle*> b_triangles = b->getTriangles();
  set<Triangle*> a_triangles = a->getTriangles();
  set<Triangle*>::iterator itr_t;*/
  
 
  
  

  /*for (itr_t = a_triangles.begin(); itr_t != a_triangles.end(); ++itr_t) {
	  Triangle *t = *itr_t;
	  
	  vector<Vertex*> vex;
	  for (int i = 0; i < 3; ++i) {
		  if (t->getVertex(i) != b) {
			  vex.push_back(t->getVertex(i));  
		  }
	  }
	  if ( vex.size() == 2) {
		  AddTriangle(vex[0],vex[1],a);
	  } 
  }*/

  


  

   /*for (itr_e = a_edges.begin(); itr_e != a_edges.end(); ++itr_e) {
	  Edge *e = *itr_e;
	  if (e->getV1() != a) {
		  vertices.insert(e->getV1());
	  } else if (e->getV2() != a) {
		  vertices.insert(e->getV2());
	  }
  }

  for (itr_e = b_edges.begin(); itr_e != b_edges.end(); ++itr_e) {
	  Edge *e = *itr_e;
	  if (e->getV1() != b) {
		  vertices.insert(e->getV1());
	  } else if (e->getV2() != b) {
		  vertices.insert(e->getV2());
	  }
  }
  
  for (itr_v = vertices.begin(); itr_v != vertices.end(); ) {
	  Vertex *v1 = *itr_v;
	  Vertex *v2 = *(++itr_v);

	  AddTriangle(v1,v2,a);
  }*/

  /*for (itr_t = a_triangles.begin(); itr_t != a_triangles.end(); ++itr_t) {
	  Triangle *t = *itr_t;
	  vector<Vertex*> vex;
	  
	  for (int i = 0; i < 3; ++i) {
		  if (t->getVertex(i) != a) {
			  vex.push_back(t->getVertex(i));  
		  }
	  }
	  if ( vex.size() == 2) {
		  AddTriangle(vex[0],vex[1],a);
	  } else {
		  continue;
	  }
  }*/

  /*for (itr_t = b_triangles.begin(); itr_t != b_triangles.end(); ++itr_t) {
	  Triangle *t = *itr_t;
	  vector<Vertex*> vex;
	  
	  for (int i = 0; i < 3; ++i) {
		  if (t->getVertex(i) != b) {
			  vex.push_back(t->getVertex(i));  
		  }
	  }
	  if ( vex.size() == 2) {
		  AddTriangle(vex[0],vex[1],a);
	  } else {
		  continue;
	  }
  }*/

 

  /*for (itr_t = a_triangles.begin(); itr_t != a_triangles.end(); ++itr_t) {
	  Triangle *t = *itr_t;
	  RemoveTriangle(t);
  }

  for (itr_e = a_edges.begin(); itr_e != a_edges.end(); ++itr_e) {
	  Edge *e = *itr_e;
	  RemoveEdge(e->getV1(),e->getV2());
  }*/

  //RemoveVertex(a);



  


  //// Remove triangles connected to b
  //for (itr_t = b_triangles.begin(); itr_t != b_triangles.end(); ++itr_t) {
	 // Triangle *t = *itr_t;
	 // RemoveTriangle(t);
  //}
  //
  //// Remove all the edges that connect to vertex b
  //for (itr_e = b_edges.begin(); itr_e != b_edges.end(); ++itr_e) {
	 // Edge *e = *itr_e;
	 // RemoveEdge(e->getV1(),e->getV2());
  //}
  ////
  ////// Remove b
  //RemoveVertex(b);