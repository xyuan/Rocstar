/* Generated by Together */

#ifndef FACE_H
#define FACE_H
#include "Node.hpp"
class Element;
class MVec;

/**
 * The Face class is an abstract base class that supplies implemented general
 * methods, as well as a vew virtual interface methods to child classes. It
 * represents one face of a mesh element. It knows the nodes that make it up,
 * and the elements that it is a part of.  It knows whether or not it is on the
 * surface of the mesh.
 * @author Mark Brandyberry
 * @version 1.0
 * @since 2001 
 */
class Face {
public:    
	//face types
    enum Type {e_tri,e_quad,e_MAX_TYPE};
    
  	enum eType {
        e_tet,      // 0
        e_hex,      // 1
        e_tri_cohesive,  // 2
        e_quad_cohesive,  // 3
        e_MAX_ELEMENT_TYPE
  	};
    //	static int numFaceNodes(Type type);

    /**
     * Constructor: set type & reset params
     */
    Face(Type type);
     
    Face();

    /**
     * Destructor. 
     *  when here face should not be in any element
     */
    ~Face();
    
    
  	static Face* create(eType type);
  	
  	static void setMesh( Mesh* emesh );

    /**
     * Sets the serial ID for the face. 
     */
    void setID(int theID);

    /**
     * Returns the serial ID of the face.  Will return -1 if it was not set. 
     */
    int getID() const;

     
    /**
     * Sets the flag for the face.  Will return -1 if it was not set. 
     */
	void Face::setFlag(int theFlag);
	
    /**
     * Gets the flag for the face.  Will return -1 if it was not set. 
     */
	int Face::getFlag() const;


    /**
     * Retrieves the number of nodes that make up the face.  Will be either
     * three or four depending upon the face type.
     */
     virtual int getNumNodes() const =0;

    /**
     * Returns the array of nodes
     */
    Node** getNodes();


    /**
     * Sets the pointer to the first element that this face is associated with. 
     */
    void setElement1(Element* elem1);

    /**
     * Get the pointer to the first element that this face is associated with. 
     */
    Element* getElement1();

    /**
     * Sets the pointer to the second element that this face is associated with. 
     */
    void setElement2(Element* elem2);


    /**
     * Get the pointer to the second element that this face is associated with. 
     */
    Element* getElement2();


    void addElement(Element * theElement);    

    void removeElement(Element * theElement);    

    /**
     * Returns the face type of this face (see the Type attribute of the Face
     * class).
     */
    Type getFaceType() const;

    boolean isExterior() const;    

    virtual Element* buildCohesive( Element* side_elem, Node* node, 
				    Node* new_node ) = 0;

    void replaceNode (Node *node, Node *new_node );

    boolean containsNode( Node* node ) const;
    
  	friend istream& operator>>(istream& stream, Face& face);
  
  	friend ostream& operator<<(ostream& stream, Face& face);


protected:

    /**
     * Serial ID assigned to this face. 
     */
    int d_ID;
    
     /**
     * User-defined integer flag assigned to this face. 
     */
    int d_flag;

    /**
     * Pointer to the first element that this face is associated with.  A face
     * will always have at least one element.
     */
    Element* d_E1;

    /**
     * The second element that this face is associated with.  This element will
     * be Null if the face is an exterior face.  This face will have a normal opposite
     * of the one for the element in E2.
     */
    Element* d_E2;


    /**
     * Array of nodes assigned to this face.  The number of nodes will depend
     * on the type of face.
     */
    Node ** d_nodes;

    /**
     * The Type of face (triangular or square for now). 
     */
    Type d_eType;
    
    static Mesh* s_mesh;
};

#include "Element.hpp"

inline void Face::setID(int theID)
{ d_ID = theID; }

inline int Face::getID() const
{ return d_ID; }

inline void Face::setFlag(int theFlag)
{ d_flag = theFlag; }

inline int Face::getFlag() const
{ return d_flag; }

inline Node** Face::getNodes()
{ return d_nodes; }

inline void Face::setElement1(Element* elem1)
{ d_E1 = elem1; }

inline Element* Face::getElement1()
{ return d_E1; }

inline void Face::setElement2(Element* elem2)
{ d_E2 = elem2; }

inline Element* Face::getElement2() 
{ return d_E2; }

inline void Face::addElement(Element * theElement){ 
  if( d_E1 ){
    d_E2 = theElement;
  }
  else {
    d_E1 = theElement;
  }
}

inline Face::Type Face::getFaceType() const
{ return d_eType; }

inline boolean Face::isExterior() const
{ return (d_E2 == 0 ? TRUE : FALSE); }

inline void Face::setMesh( Mesh* fmesh ) 
{ s_mesh =  fmesh; }

#endif //FACE_H


