
public class DictionaryNode {
	
	//Variables
	DictionaryNode leftChild = null;
	DictionaryNode rightChild = null;
	DictionaryNode parent = null;
	Record node;
	
	/**
	 * Constructor if there is no parent node
	 * @param info; a record of all information
	 */
	public DictionaryNode(Record info){
		this.node = info;
		this.leftChild = null;
		this.rightChild = null;
		this.parent = null;
	}
	
	/**
	 * Constructor if given a parent node in argument
	 * @param parent
	 * @param info
	 */
	public DictionaryNode(DictionaryNode parent, Record info){
		this.parent = parent;
		this.node = info;
		this.leftChild = null;
		this.rightChild = null;
	}
	
	//Getter and setter methods
	
	public DictionaryNode getLeftChild(){
		return leftChild;
	}
	
	public DictionaryNode getRightChild(){
		return rightChild;
	}
	
	public DictionaryNode getParent(){
		return parent;
	}
	
	public void setRoot(Record root){
		this.node = root;
	}
	
	public void setLeftChild(DictionaryNode leftChild){
		this.leftChild = leftChild;
	}
	
	public void setRightChild(DictionaryNode rightChild){
		this.rightChild = rightChild;
	}
	
	public void setParent(DictionaryNode parent){
		this.parent = parent;
	}
	
	public Record getRecord(){
		return node;
	}
	
}
