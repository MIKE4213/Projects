package hash341;
import java.io.*;
import java.util.*;
import java.util.ArrayList;

//Miguel Bocard UIN:229000140

public class CityTable implements Serializable{
 
	private String fname;
	private int tsize;
	private Hash24[] secondh;
	private Hash24 h1;
	private ArrayList<City>[] primary;
	private City[][] secondary;
	
	public CityTable(String fname, int tsize) {
			
			 this.fname=fname;
			 this.tsize=tsize;
			 h1 = new Hash24();
		     //System.out.println(h1);
		     boolean debug = true;
		     //ArrayList<ArrayList<City> > r1 =  new ArrayList<ArrayList<City>>(tsize);
		      primary = new ArrayList[tsize];
		     
		     //////////////////////////////////////////////////////
		     Scanner infile = null;
				try
				{
				infile = new Scanner(new FileReader(fname));
				} 
				catch (FileNotFoundException e) 
				{
					System.out.println("File not found");
					e.printStackTrace(); // prints error(s)
					System.exit(0); // Exits entire program
				}
				String city; float lat;
				float longd;
				int i = 0; // i is used to place data into the correct array element (index)
				int numb=0;
				int nonlist=0;
				while(infile.hasNextLine())
				{
					 city = infile.nextLine();
					//StringTokenizer tokenizer = new StringTokenizer(line);

					// You should know what you are reading in

					//city = tokenizer.nextToken();
					//state = tokenizer.nextToken();
					
					String line2 = infile.nextLine();
					StringTokenizer tokenizer2 = new StringTokenizer(line2);
					lat = Float.parseFloat(tokenizer2.nextToken());
					longd = Float.parseFloat(tokenizer2.nextToken());
                    i = (h1.hash(city))%(tsize);
		                 // r1.add( i ,ArrayList<new City(city, lat, longd)>);
                          //r1.get(i).add(new City(city, lat, longd));
                           if(primary[i]==null) {
                        	   primary[i]= new ArrayList<City>();
                        	   nonlist=i;
                           }
                           primary[i].add(new City(city, lat, longd));
		                  numb++; 
					//if(debug)
					//{
						//System.out.println("Employees name: " + city);
						//System.out.println("Employees title: " + lat);
						//System.out.println("Employees salary: " + longd);
					//}
				}
      
				infile.close( );
				////////////////////////////////////////////////
				int total=primary[nonlist].size();
				int max= nonlist;//primary[0].size();
				for(int j = 0; j<primary.length; j++) {
					if((primary[j]!= null)&&(primary[j].size()>primary[max].size())) {
						total=primary[j].size();
						max=j;
					}
				}
				h1.dump();
				System.out.print("\n");
				System.out.println("Primary hash table statistics:");
				System.out.println("Number of cities: " + numb);
				System.out.println("Table size: " + tsize);
				System.out.println("Max collisions: " + total);
				/////////////////////////////////////////////////////////
				
	
					int nonc=0;
					for(int k = 0; k<primary.length; k++){
					
						if(primary[k]==null) {
							nonc++;
						}
					}
					System.out.println("# of primary slots with" + " 0" + " cities = " + nonc);
				
				
				
				int cityn=1;
				for(int j = 0; j<24; j++) {
					int count=0;
					for(int k = 0; k<primary.length; k++){
						if((primary[k]!=null)&&(primary[k].size()==cityn)) {
							count++;
						}
					}
					System.out.println("# of primary slots with " + cityn + " cities = " + count);
					cityn++;
				}
				
				////////////////////////////////////////////////////////////////////////
				System.out.print("\n");
				System.out.println("*** Cities in the slot with most collisions ***");
				for(int j = 0; j<primary[max].size(); j++) {
					System.out.println(primary[max].get(j));
				}
				////////////////////////////////////////////////////////////////////////
				
				System.out.print("\n");
				System.out.println("Secondary hash table statistics:");
				//ArrayList<City>[] secondary = new ArrayList[tsize];
				secondary = new City[tsize][];
				
				Hash24 h2 = new Hash24();
				secondh = new Hash24[tsize];
				int[] numt = new int[21];
				int tries=0;
				int index=0;
				float totsech=0;
				//////////////////////////////////////////////////////////////////////////
				
				
				for(int k = 0; k<secondary.length; k++){
					if((secondary[k]==null) && (primary[k]!=null)) {
                 	   secondary[k] = new City[(primary[k].size()) * (primary[k].size())];
                 	   
                 	  // System.out.println(primary[k]);
                    }
					tries = 1;
	                if((secondary[k]!= null) && (primary[k].size() != 1)) {
					
	                	for(int p = 0 ; p<primary[k].size(); p++ ) {
						
						index = (h2.hash(primary[k].get(p).getname())) % ((primary[k].size()) * (primary[k].size()));
						//System.out.println(secondary[k][index]);
						if(secondary[k][index] == null) {
							secondary[k][index]=primary[k].get(p);
							secondh[k] = h2; 
						}
						else {
						
						  p=-1;
					      //secondary[k].clear();
					      Arrays.fill( secondary[k], null );
					      h2= new Hash24();
					      tries++;
						}
					 }
					   
					   numt[tries]++;
					   tries=1;
					   totsech++;
					
	                }
	                else if(((secondary[k]!= null)) && (primary[k].size() == 1)) {
	                	secondary[k][0]=primary[k].get(0);
	                }
					
				}
			     
				float totav = 0;
				for(int j=1;j<numt.length;j++){
					//numt[j]++;
					System.out.println("# of secondary hash tables trying " + j + " hash functions = " + numt[j]);
					
					totav = (totav) + ((j) * (numt[j])); 
					
				}
				
				System.out.println("Number of secondary hash tables with more than 1 item = " + totsech);
				float average = (totav) / (totsech);
				System.out.println("Average # of hash functions tried = " + average);
				
				
	}
	
	public City find(String cName) {
		int first = (h1.hash(cName)) % (tsize);
		if((primary[first] != null) && (primary[first].size() != 1)) {
			int second = (secondh[first].hash(cName)) % (secondary[first].length);
			return secondary[first][second];
		}
		
		else if((primary[first] != null) && (primary[first].size() == 1)) {
			return secondary[first][0];
		}
		
		else {
			return null;
		}
		
	}
	
	
	public void writeToFile(String fName) {
		
		 try {
	         // create a new file with an ObjectOutputStream
	         FileOutputStream out = new FileOutputStream(fName);
	         ObjectOutputStream oout = new ObjectOutputStream(out);

	         // write something in the file
	         //for(int i=0 ; i<secondary.length;i++) {
	        	 //if(secondary[i]!=null) {
	        	 //for(int k=0; k<secondary[i].length; k++) {
	        		 //if(secondary[i][k]!=null) {
	        		 //oout.writeObject(secondary[i][k]);
	        		// }
	        	// }
	        	 
	        	// }
	         
	        // }
	         
	         oout.writeObject(this);

	         // close the stream
	         oout.close();

	         // create an ObjectInputStream for the file we created before
	         //ObjectInputStream ois = new ObjectInputStream(new FileInputStream("test.txt"));

	      } catch (Exception ex) {
	         ex.printStackTrace();
	      }
       
	}
	
	
	public static CityTable readFromFile(String fName) {
	CityTable one = null;
		
	     try {  
              
           ObjectInputStream objinstream = new ObjectInputStream(new FileInputStream(fName));  
           
            one =(CityTable) objinstream.readObject();

           // read and print an object and cast it as the string  
            
            } 
		         catch (Exception ex) {  
                   ex.printStackTrace();  
                 }
		  
		 return one;
	}


	
	

		     	     
}

