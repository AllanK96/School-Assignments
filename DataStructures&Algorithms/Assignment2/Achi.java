
public class Achi {
	private char[][] gameBoard;
	private int boardSize;
	private int dSize = 9929;		//Dctionary Size: 9929 is prime
	
	// constructor
	public Achi (int board_size, int max_levels){
		this.boardSize = board_size;
		gameBoard = new char[board_size][board_size];
		for (int y = 0; y < board_size; y++){
			for (int x = 0; x < board_size; x ++){
				gameBoard[x][y] = ' ';
			}
		}
	}
	
	//creates empty dictionary
	public Dictionary createDictionary(){
		return new Dictionary(dSize);
	}
	
	/*
	 This method first represents the content of gameBoard as a string; 
	 then it checks whether the string representing the gameBoard is in 
	 the configurations dictionary: If it is in the dictionary this method 
	 returns its associated score, otherwise it returns the value -1.
	 */
	public int repeatedConfig(Dictionary configurations){
		String config = "";
		for (int y = 0; y < boardSize; y++){
			for (int x = 0; x < boardSize; x++){
				config += gameBoard[x][y];
			}
		}
		return configurations.find(config);
	}
	
	/*
	 * This method first represents the content of gameBoard 
	 * as a string; then it inserts this string and score in
	 * the configurations dictionary
	 */
	
	public void insertConfig(Dictionary configurations, int score){
		String config = "";
		for (int y = 0; y < boardSize; y++){
			for (int x = 0; x < boardSize; x++){
				config += gameBoard[x][y];
			}
		}
		
		try{
			// try inserting the pair into the dictionary
			configurations.insert(new ConfigData(config, score));
		} catch (DictionaryException e){			
		}
	
	}
	
	//Stores symbol in gameBoard[row][col]
	public void storePlay(int row, int col, char symbol){
		gameBoard[row][col] = symbol;
	}
	
	//Returns true if gameBoard[row][col] is ’ ’; otherwise it returns false
	public boolean tileIsEmpty (int row, int col){
		if (gameBoard[row][col] == (' ')){
			return true;
		} else {
			return false;
		}
	}
	
	//Returns true if the gameBoard[row][col] is 'O'; otherwise it returns false
	public boolean tileIsComputer (int row, int col){
		if (gameBoard[row][col] == ('O')){
			return true;
		} else {
			return false;
		}
	}
	
	//Returns true if gameBoard[row][col] is ’X’; otherwise it returns false
	public boolean tileIsHuman (int row, int col){
		if (gameBoard[row][col] == ('X')){
			return true;
		} else {
			return false;
		}
	}
	
	/*
	 * Returns true if there are n adjacent tiles of type
	 * symbol in the same row, column, or diagonal of gameBoard, 
	 * where n is the size of the game board
	 */
	public boolean wins (char symbol){
		int win = 0;		//adjacent symbols, an 'n' sequence of a symbol means a win
		
		// row win check	
		for ( int y = 0; y < boardSize; y++){
			win = 0;
			for (int x = 0; x < boardSize; x++){
				if (gameBoard[x][y] == symbol){
					win += 1;
				} else 
					win = 0;
				if (win == boardSize){
					return true;
				}
			}
		}
		
		// column win check
		win = 0;
		for ( int x = 0; x < boardSize; x++){
			win = 0;
			for (int y = 0; y < boardSize; y++){
				if (gameBoard[x][y] == symbol){
					win += 1;
				} else 
					win = 0;
				if (win == boardSize){
					return true;
				}
			}
		}
		
		// diagonal down-right win check
		win = 0;
		for ( int i = 0; i < boardSize; i++){
			if(gameBoard[i][i] == symbol){
				win += 1;
			}else
				win = 0;
			if (win == boardSize){
				return true;
			}
			
			
		}
		// diagonal down-left win check
		win = 0;
		for (int i = 0; i < boardSize; i++){
			if(gameBoard[boardSize-1-i][0+i] == symbol){
				win += 1;
			} else
				win = 0;
			if (win == boardSize){
				return true;
			}
		}
		
		return false;
	}
	
	
	// Returns true if the game has only 1 blank space left, indicating a draw
	// False if there is more than 1 blank space
	// No need to use symbol, but it said to have it as argument
	public boolean isDraw(char symbol){
		int blankSpaces = 0;
		for (int y = 0; y < boardSize; y++){
			for (int x = 0; x < boardSize; x++){
				if (gameBoard[x][y] == ' '){
					blankSpaces += 1;
				}
			}
		}
		if (blankSpaces == 1){
			return true;		//Game is a draw
		}else{
			return false;		//Game needs to continue
		}
	}
	
	// Returns 3 if computer has won
	// 0 if human won
	// 2 if it's a draw
	// 1 if the game is still undecided
	public int evalBoard(char symbol){
		if (wins(symbol) == true)
			return 3;
		
		if (wins(symbol))
			return 0;
		
		if (isDraw(symbol) == true){
			return 2;
		}else
			return 1;
		
	}
}
