
public class Record {
	
	//Variables
	private Key entry;
	private String data;
	
	/**
	 * Constructs a record with using a key, and data
	 * @param k is the key
	 * @param data	
	 */
	public Record(Key k, String data){
		this.entry = k;
		if ((k.getType() == 2) || (k.getType() == 3)){
			this.data = k.getWord();
		}
		else{
			this.data = data;	
		}
	}
	
	/**
	 * @return this key/entry
	 */
	public Key getKey(){
		return this.entry;
	}
	
	/**
	 * @return this data
	 */
	public String getData(){
		return this.data;
	}
}
