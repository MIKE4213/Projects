package hash341;
import java.util.* ;
import java.io.* ;
import hash341.City ;
import hash341.CityTable ;

public class Program1 {


	public static void main(String[] args) {
		// TODO Auto-generated method stub
		CityTable b1 = new CityTable("US_Cities_LL.txt", 16000);
		b1.writeToFile("US_Cities_LL.ser");

	}

}
