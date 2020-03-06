import java.util.LinkedList;

public class Dictionary implements DictionaryADT{
	private int size;
	private LinkedList<ConfigData>[] collisionList;			//not the greatest name in hindsight
	
	// 33 was used in the lecture slides for English words
	// integer used for hashFunc
	private int constant = 33;
	
	// insert method for ConfigData
	public int insert(ConfigData pair) throws DictionaryException{
		// getter gets config key
		String config = pair.getConfig();
		int key = hashFunc(config,constant);
		//if pair already exists, throw exception
		if (find(config) != -1){
			throw new DictionaryException("Pair already exists in dictionary");
		}else{	
			// insert into collisionList
			if (collisionList[key].size() > 0){
				collisionList[key].add(pair);
				return 1; 								// return 1 if it collides in hashtable, 0 otherwise
			}else{
				collisionList[key].add(pair);
				return 0;
			}
		}
	}
	
	// remove method
	public void remove(String config) throws DictionaryException {
		//compute key
		int key = hashFunc(config,constant);
		//if empty throw exception
		if (collisionList[key].size() == 0){
			throw new DictionaryException("Does not exist in the dictionary");
			
		} else {
			collisionList[key].remove(config);
		}
	}
	
	//find method
	public int find(String config) {
		// computer code again
		int key = hashFunc(config,constant);
		// loop through spot
		for (int i = 0; i < collisionList[key].size(); i++){
			if (collisionList[key].get(i).getConfig().equals(config)){
				return collisionList[key].get(i).getScore();			// if found return score
			}
		}
		return -1;														// if not found, return -1
	}
	
	// hash method, returns hash # of key
	public int hashFunc(String config, int y){
		int a = (int) config.charAt(0);
		for (int i = 1; i < config.length(); i++){
			int b = config.charAt(i);
			// the formula from the lecture slides
			a = (a * y + b) % size;
		}
		return a;														// return hash code
	}
	
	// constructor method
	public Dictionary(int size){
		// set variable to size
		this.size = size;
		// dictionary of size
		collisionList = new LinkedList[size];
		// Put a list in every spot of the collisionList
		for (int i = 0; i < size; i++){
			collisionList[i] = new LinkedList<ConfigData>();
		}
	}

	
}
