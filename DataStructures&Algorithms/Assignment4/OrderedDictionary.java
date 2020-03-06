
public class OrderedDictionary implements OrderedDictionaryADT{
	
	//Variables
	private Key tmpKey;
	private DictionaryNode root, node, child, parent, checker, deleteNode, tempNode, sNode, pNode, sParent, replace;
	private Record succNode, smallest, largest, findRec, type;

	String data;

	
	/**
	 * Constructor for empty tree
	 */
	public OrderedDictionary(){
		root = null;
		node = root;
	}
	
	/**
	 Returns the Record object with key k, or it returns null if such 
     a record is not in the dictionary. 
     */
	
	public Record find(Key k){
		//Used for Search in UI
		if (k.getType() == 0){
			//Returns the record of the searched word, because there is no type given, create type 0 for key
			return findType(k.getWord());
		}
		if (node == null){
			return null;
		}
		else if(node.getRecord().getKey().compareTo(k) == 0){
			return node.getRecord();
		}
		else if(node.getRecord().getKey().compareTo(k) >= 1){
			node = node.getLeftChild();
			findRec = find(k);
			node = root;
			return findRec;
		}
		else{
			node = node.getRightChild();
			findRec = find(k);
			node = root;
			return findRec;
		}
	}
	
	 /** Inserts r into the ordered dictionary. It throws a DictionaryException 
    if a record with the same key as r is already in the dictionary. */
	public void insert(Record r) throws DictionaryException{
		if (root == null){
			root = new DictionaryNode(r);
			node = root;
		}
		else if (node.getRecord().getKey().compareTo(r.getKey()) == 0){
			node = root;
			//throw error because it already exists
			throw new DictionaryException("Error: Record already exists!");
		}
		//check if it's on the left
		else if (node.getRecord().getKey().compareTo(r.getKey()) >= 1){
			//if left is leaf, then insert record in leaf
			if (node.getLeftChild() == null){
				node.setLeftChild(new DictionaryNode(r));
			}
			//Else continue recursively
			else {
				node = node.getLeftChild();
				insert(r);
				node = root; //reset root to node
			}
		}
		
		//Else, traverse right-side of tree
		else{
			//is it a leaf? then insert
			if (node.getRightChild() == null){
				node.setRightChild(new DictionaryNode(r));
			}
			//else, continue recursively on right-side of tree
			else{
				node = node.getRightChild();
				insert(r);
				node = root; //reset root to node
			}
		}
	}
	
	/**
	 * Returns the node that has key K in it, null if no key
	 * @param k
	 * @return node of k
	 */
	private DictionaryNode findNode(Key k){
		checker = root;
		//traversal through tree until key or leaf found
		while (checker!= null && checker.getRecord().getKey().compareTo(k) != 0){
			if (checker.getRecord().getKey().compareTo(k) >= 1){
				checker = checker.getLeftChild();
			}
			else{
				checker = checker.getRightChild();
			}
		}
		//return node with key in it, or null
		return checker;
	}
	
	/**  Removes the record with Key k from the dictionary. It throws a 
    DictionaryException if the record is not in the dictionary. */
	
	public void remove (Key k) throws DictionaryException{
		//find node of key
		deleteNode = findNode(k);
		//if it doesn't exist, throw exception
		if (deleteNode == null){
			throw new DictionaryException("Error: Record doesn't exist in the dictionary!");
		}
		else{
			//check if either node is a leaf, if so set tempNode to delete, setting it to itself
			if(deleteNode.getLeftChild() == null || deleteNode.getRightChild() == null){
				tempNode = deleteNode;
			}
			else{
				//else replace tempNode with successor
				succNode = successor(deleteNode.getRecord().getKey());
				tempNode = findNode(succNode.getKey());
			}
			//store the children
			if(tempNode.getLeftChild() != null){
				child = tempNode.getLeftChild();
			}
			else{
				child = tempNode.getRightChild();
			}
			//set replacement TempNode to it's grandparent
			if (child != null){
				child.setParent(tempNode.getParent());
			}
			//if root, set root to tempNode replacement
			if (tempNode.getParent() == null){
				root = child;
			}
			
			else{
				//replace node if left
				if (tempNode == tempNode.getParent().getLeftChild()){
					tempNode.getParent().setLeftChild(child);
				}
				//else replace right
				else{
					tempNode.getParent().setRightChild(child);
				}
			}
			// store tempNode in delete
			if (tempNode != deleteNode){
				deleteNode.setRoot(tempNode.getRecord());
			}
			
		}
	}
	
	
	 /**  Removes the record with Key k from the dictionary. It throws a 
    DictionaryException if the record is not in the dictionary. */
	/*
	public void remove(Key k) throws DictionaryException{
		deleteNode = findNode(k);
		if (deleteNode == null) throw new DictionaryException("Error: Record doesn't exist in the dictionary!");
		else{
			//check if children are leafs
			if(deleteNode.getLeftChild() == null || deleteNode.getRightChild() == null)
				//set it to itself
				replace = deleteNode;
			else
				//otherwise replace with successorNode
				replace = successorNode(deleteNode);
			//store left child if it exists
			if (replace.getLeftChild() != null)
				child = replace.getLeftChild();
			//else, store right
			else
				child = replace.getRightChild();
			//check if both nodes are null
			if (child != null) 
				child.setParent(replace.getParent());
			//else replace the node that needs to be deleted
			else{
				//replace left child of parent
				if(replace == replace.getParent().getLeftChild()) 
					replace.getParent().setLeftChild(child);
				//else replace right
				else
					replace.getParent().setRightChild(child);
			}	
			//store information of the replacing node, within the deleteNode
			if (replace != deleteNode) 
				deleteNode.setRoot(replace.getRecord());
		}
	}
	*/
	/*
	private void removeNode(Key k, DictionaryNode pos) throws DictionaryException{
		if (pos == null) throw new DictionaryException("Error: Record doesn't exist in the dictionary!");
		if (k.compareTo(pos.getRecord().getKey()) < 0){
			if(pos.getLeftChild() != null)
				removeNode(k,pos.getLeftChild());
		}
		else if (k.compareTo(pos.getRecord().getKey()) > 0){
			if (pos.getRightChild() != null)
				removeNode(k,pos.getRightChild());
		}
		else{
			if (pos.getLeftChild() != null && pos.getRightChild() != null){
				pos.setRoot(pos.getRightChild().getRecord());
				removeNode(pos.getRecord().getKey(), pos);
			}
			else if (pos.getParent().getLeftChild() == pos){
				if (pos.getLeftChild() != null)
					pos.getParent().setLeftChild(pos.getLeftChild());
				else
					pos.getParent().setLeftChild(pos.getRightChild());
			}
			else if (pos.getParent().getRightChild() == pos){
				if (pos.getLeftChild() != null)
					pos.getParent().setRightChild(pos.getLeftChild());
				else
					pos.getParent().setRightChild(pos.getRightChild());
			}
		}
	}
	*/
	
	
	
	/** Returns the successor of k (the record from the ordered dictionary 
    with smallest key larger than k); it returns null if the given key has
    no successor. The given key DOES NOT need to be in the dictionary. */
	
	public Record successor(Key k){
		//find successor node with key
		sNode = successorNode(findNode(k));
		if (sNode != null){
			//return it's record if not null
			return sNode.getRecord();
		}
		else{
			return null;
		}
	}

	/**
	 * Finds the successor node, null if it doesn't exist
	 * @param root
	 * @return successor node
	 */
	
	private DictionaryNode successorNode(DictionaryNode root){
		//checks to see if exists
		if (root == null)
			return null;
		//check right
		if (root.getRightChild() != null){
			root = root.getRightChild();
			//find the farthest left node, the smallest key larger that root key
			while(root.getLeftChild() != null){
				root = root.getLeftChild();
			}
			return root;
		}
		//check parents
		else{
			parent = root.getParent();
			//loop until found left child or root
			while(parent != null && root == parent.getRightChild()){
				root = parent;
				parent = parent.getParent();
			}
			return parent;
		}
	}
	
	/**
	 * Finds the predecessor node, null if it doesn't exist
	 * @param root
	 * @return predecessor node
	 */
	private DictionaryNode predecessorNode(DictionaryNode root){
		//checks to see if exists
		if (root == null)
			return null;
		//check left
		if (root.getLeftChild() != null){
			root = root.getLeftChild();
			//find the farthest left node, the smallest key larger that root key
			while(root.getRightChild() != null){
				root = root.getRightChild();
			}
			return root;
		}
		//check parents
		else{
			parent = root.getParent();
			//loop until found right child or root
			while(parent != null && root == parent.getLeftChild()){
				root = parent;
				parent = parent.getParent();
			}
			return parent;
		}
	}
	
	/**Returns the predecessor of k (the record from the ordered dictionary 
    with largest key smaller than k; it returns null if the given key has 
    no predecessor. The given key DOES NOT need to be in the dictionary.  */
	
	public Record predecessor(Key k){
		//find predecessor node with key
		pNode = predecessorNode(findNode(k));
		if(pNode != null)
			//return the record of the predecessor
			return pNode.getRecord();
		else
			return null;
	}
	
	/** Returns the record with smallest key in the ordered dictionary. Returns null
	if the dictionary is empty. */

	public Record smallest(){
		//return null if empty tree
		if (root == null) return null;
		if (root.getLeftChild() == null)
			return root.getRecord();
		else
			root = root.getLeftChild();
			//recursively go through the left side of the tree, because it has the smallest value
			return largest();
	}
	
	/**
	 * Largest, returns record of farthest right node. Null if dictionary is empty
	 */
	public Record largest(){
		//same as smallest, just right side of the tree this time
		if (root == null) return null;
		if (root.getRightChild() == null)
			return root.getRecord();
		else
			root = root.getRightChild();
			return largest();
		

	}
	
	/**
	 * Returns record of word if found
	 * @param word
	 * @return 
	 */
	
	private Record findType(String word){
		//if it doesn't exist, it's empty
		if (node == null)
			return null;
		//does current node have word?
		else if (node.getRecord().getData().compareTo(word) == 0){
			return node.getRecord();
		}
		//check left
		else if (node.getRecord().getKey().getWord().compareTo(word) >= 1){
			node = node.getLeftChild();
			//recursive
			type = findType(word);
			//reset root
			node = root;
			return type;
		}
		
		//else right
		else{
			node = node.getRightChild();
			type = findType(word);
			node = root;
			return type;
		}
		
		
	}
	

}
