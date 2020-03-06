
public class ConfigData {
	private String configeration;
	private int score;
	
	//constructor
	public ConfigData(String config, int score){
			this.configeration = config;
			this.score = score;
	}
	
	// getter method for key
	public String getConfig(){
		return this.configeration;
	}
	
	// getter method for score
	public int getScore(){
		return this.score;
	}
}
