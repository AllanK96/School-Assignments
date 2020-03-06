
public class Key {
	
	//Variables
	private String word;
	private int type;
	
	/**
	 * Constructor
	 * @param word
	 * @param type
	 */
	public Key(String word, int type){
		this.word = word;
		this.type = type;
	}
	
	/**
	 * @return this key's word
	 */
	public String getWord(){
		return this.word;
	}
	
	/**
	 * @return this key's type
	 */
	public int getType(){
		return this.type;
	}
	
	/**
	 * Compares this key to key k
	 * @param Key k
	 * @return 0 if the two keys are equal, -1 if this key is < k, and 1 otherwise
	 */
	public int compareTo(Key k){
		if (this.getType() == (k.getType()) && this.getWord().compareTo(k.getWord())==0){
			return 0;
		}
		if ((this.getType() < (k.getType()) && (this.getWord().compareTo(k.getWord())==0)) || (this.getWord().compareTo(k.getWord()) < 0)){
			return -1;
		}
		else{
			return 1;
		}
	}
}
