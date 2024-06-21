public class NumberToWords {

    public static String intToWords(int num) {
		//Write your code here 
    String text = "";
    String [] ones = new String[] {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    String [] tens = new String[]{"", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
    if (num == -1){
    return "Done";
    }
    if (num == 0) {
      return "zero";
    }
    if ((num / 100) > 0) {
      text += intToWords(num / 100) +" " + "hundred";{
        if (num%100==0)
        text += "";
        else 
        text += " and " + intToWords(num%100);
      }
      return text;
    }

    if (num > 0) {
      if (num < 20) {
        text += ones[num];
      }
      else {
        text += tens[num /10];
        if ((num % 10) > 0) {
          text += " " + ones[num % 10];
        }
      }
    }
    return text;
        }

    public static String intToRoman(int num) {
       //Write your code here 
       String[] units = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
       String[] tens = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
       String[] hundreds = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
    String text = "";
    if (num == -1){
      return "";
    }
    if (num > -1){
    return hundreds[(num%1000)/100] + tens[(num%100)/10] + units[num%10];
    }
    return text;
  }

    public static void main(String[] args) {
		//Write your code here 
    int num = 0;
    while(num > -1 && num < 1000){
      System.out.println("Enter a number between 0-999, or -1 to exit: ");
      num = In.nextInt();
      System.out.println(intToWords(num));
      System.out.println(intToRoman(num));
    }
	}
}
