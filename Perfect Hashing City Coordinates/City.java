package hash341;
import java.io.*;

public class City implements Serializable {
	public String name; public float latitude, longitude;
	public City(String c, float la, float lo) {
	    name=c;
	    latitude=la;
	    longitude=lo;
	}
	
	public String getname() { return name; }
	public void setname(String city) { this.name = city; } 
	

	
	public float getlat() { return latitude; }
	public void setlat(float lat) { this.latitude = lat; } 
	
	public float getlongd() { return longitude; }
	public void setlongd(float longd) { this.longitude = longd; } 
	
	public String toString() {
		return name + " (" + latitude + ", " + longitude + ")" ;
	}
	

}
