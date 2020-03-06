import java.io.BufferedReader;
import java.io.FileReader;
import java.util.StringTokenizer;

public class UI {
	public static void main(String[] args){
		//variables
		String word, info;
		
		
		//dictionary
		OrderedDictionary dictionary = new OrderedDictionary();
		
		try{
			// read 1 line at a time
			BufferedReader inFile = new BufferedReader(new FileReader(args[0]));
			//read first word
			word = inFile.readLine();
			//loop until done file
			while(word != null){
				word = word.toLowerCase();
				//read data on word
				info = inFile.readLine();
				//is it a picture?
				
				if (info.endsWith(".jpg") || info.endsWith(".gif")){
					//make a key with it
					Key k = new Key(word,3);
					//make a record of it
					Record r = new Record(k,info);
					//insert it into the dictionary
					dictionary.insert(r);
				}
				
				//is it an audio file?
				else if(info.endsWith(".mid")||info.endsWith(".wav")){
					Key k = new Key(word,2);
					Record r = new Record(k,info);
					dictionary.insert(r);
				}
				
				//else must be text
				else{
					Key k = new Key(word,1);
					Record r = new Record(k,info);
					dictionary.insert(r);
				}
				//next line
				word = inFile.readLine();
				
					
			}
		} catch (Exception e){
			//show error and stop execution
			System.out.println(e.getMessage());
			return;
		}
		
		// String reader for user commands
		StringReader keyboard = new StringReader();
		//how to exit
		boolean flag = true;
		
		while(flag){
			String input, arg, type, data;
			//User prompt
			StringTokenizer prompt = new StringTokenizer(keyboard.read("Enter a command: "));
			//did user input?
			if (prompt.hasMoreElements()){
				//if has more elements divide them
				input = prompt.nextToken();
				input = input.toLowerCase();
			}
			
			//else no entry
			else
				input = "";
			
			//check input for argument 1
			if(prompt.hasMoreElements()){
				arg = prompt.nextToken();
				arg = arg.toLowerCase();
			}
			//else blank
			else arg = null;
			
			//check input for argument 2
			if(prompt.hasMoreElements()){
				type = prompt.nextToken();
				type = type.toLowerCase();
			}
			else type = null;
			
			//does the input work?
			
			if (prompt.hasMoreElements()){
				data = prompt.nextToken();
				while (prompt.hasMoreElements()){
					//put it all together
					data = data.concat(" " + prompt.nextToken());
				}
			}
			//else blank
			else 
				data = null;
			
			
			//search command
			if (input.compareTo("search") == 0){
				//create key so that word can be searched
				Key k = new Key(arg,0);
				//error if no argument
				if(arg == null){
					System.out.println("Error: needs argument name");
				}
				//is it image??
				//Give find method argument and "fake" type 0, finds the record using word
				else if (dictionary.find(k).getKey().getType() == 3){
					try{
						PictureViewer picture = new PictureViewer();
						picture.show(dictionary.find(k).getData());
					} catch (MultimediaException e){
						System.out.println("Error: no picture data");
					}
				}
				//is it audio?
				else if (dictionary.find(k).getKey().getType() == 2){
					try{
						SoundPlayer music = new SoundPlayer();
						music.play(dictionary.find(k).getData());
					} catch (MultimediaException e){
						System.out.println("Error: no audio data");
					}
				}
				
				//check for normal text
				else if (dictionary.find(k).getKey().getType() == 1){
					System.out.println(dictionary.find(k).getData());
				}
				
				//else not in dictionary
				else{
					System.out.println("Error: Word argument doesn't exist in dictionary!");
				}
			}
			
			//remove command
			else if (input.compareTo("remove") == 0){
				//create key using arg=word and parsing type to integer
				Key k = new Key(arg,Integer.parseInt(type));
				if(arg == null || type == null)
					System.out.println("Error: command REMOVE needs name and type in argument");
				//try to remove
				else{
					try{
						dictionary.remove(k);
						//print error message if key is not in dictionary
					}catch (DictionaryException e){
						System.out.println(e.getMessage());
					}
				}
			}
			
			//insert command
			else if (input.compareTo("insert") == 0){
				//create key, then record
				Key k = new Key(arg,Integer.parseInt(type));
				Record r = new Record(k,data);
				if (arg == null || type == null || data == null)
					System.out.println("Error: command INSERT needs arguments word,type,data");
				//try to add
				else{
					try{
						dictionary.insert(r);
						//error if already in dictionary
					}catch (DictionaryException e){
						System.out.println(e.getMessage());
					}
				}
			}
		
			// next
			else if (input.compareTo("next") == 0){
				Key k = new Key(arg,Integer.parseInt(type));
				if (arg == null || type == null)
					System.out.println("Error: input NEXT needs argument and type");
				//check for successor
				else if (dictionary.successor(k) == null){
					//last key?
					if (dictionary.find(k) != null)
						System.out.println("This is the last word, no next");
					//else, doesn't exist
					else
						System.out.println("Error: word doesn't exist in dictionary");
				}
				//Else show successor's key 
				else
					System.out.println(dictionary.successor(k).getKey());				
			}
			
			// prev
			else if (input.compareTo("prev") == 0){				
				if (arg == null || type == null)
					System.out.println("Error: input PREV needs argument and type");
				Key k = new Key(arg,Integer.parseInt(type));
				if (dictionary.predecessor(k) == null){
					//first key?
					if (dictionary.find(k) != null)
						System.out.println("This is the first word, no previous");	
					else
						System.out.println("Error: word doesn't exist in dictionary");
				}
				else
					System.out.println(dictionary.predecessor(k).getKey());
			}
			//prints smallest key in dictionary
			else if (input.compareTo("first") == 0)
				System.out.println(dictionary.smallest().getKey());
			//prints largest key in dictionary
			else if (input.compareTo("last") == 0)
				System.out.println(dictionary.largest().getKey());
			
			//ends the loop and UI
			else if (input.compareTo("end") == 0){
				System.out.println("Exiting UI");
				//while loop exit
				flag = false;
			}
	
			//invalid command was inputed,  error message
			else {
				System.out.println("Error: input a valid command; search, remove, insert, next, prev, first, last, end");
			}
			//new line so it doesn't get too cluttered
			System.out.println("");
		}
		return;
	}	
}
