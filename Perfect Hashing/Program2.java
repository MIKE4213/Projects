package hash341;

import hash341.City;
import hash341.CityTable;
import java.util.Scanner;
import java.awt.Desktop ;
import java.net.URI ;
public class Program2 {
     
	static Scanner sc = new Scanner(System.in);
	
	public static void printCity(City aCity, String n) {
	      if (aCity == null) {
	         System.out.println("Could not find " + n) ;
	      } else {
	         System.out.println( "Found " + aCity.name + " (" + aCity.latitude + "," + aCity.longitude + ")" ) ;
	         System.out.println( "http://www.google.com/maps?z=10&q=" + aCity.latitude + "," + aCity.longitude ) ;
	         String option;
	         System.out.print("Do you want to open in Google Maps? Yes or No: ");
	         option= sc.nextLine();
	         if(option.equals("Yes")) {
	        	 openURL("http://www.google.com/maps?z=10&q=" + aCity.latitude + "," + aCity.longitude);
	         }
	         
	      }
	   }
	
	static void openURL (String url) {
		// cribbed from:
		// http://java-hamster.blogspot.com/2007/06/troubles-with-javaawtdesktop-browse.html
		try {
		if (Desktop.isDesktopSupported()) {
		Desktop desktop = Desktop.getDesktop();
		if (desktop.isSupported(Desktop.Action.BROWSE)) {
		desktop.browse(new URI(url));
		} else {
		System.out.println("No browser. URL = " + url) ;
		}
		} else {
		System.out.println("No desktop. URL = " + url) ; }
		} catch (Exception e) { e.printStackTrace(); }
		}
	
	public static void main(String[] args) {
		
		
		String q= "quit";
		
		CityTable Cities ;
	      String Name ;

	      Cities = CityTable.readFromFile("US_Cities_LL.ser") ;
	      System.out.print("Enter City, State (or 'quit'): ");
	      
	      Name = sc.nextLine();
	      
	    
	      
	      while(!Name.equals(q)) {
	      
	      City found = Cities.find(Name);
	      
	      printCity(found, Name);
	      
	      System.out.print("Enter City, State (or 'quit'): ");
	      Name = sc.nextLine();
	      
	      }
	   
	      
	      

	}

}
