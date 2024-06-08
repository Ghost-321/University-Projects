import java.lang.Math;
public class Rectangle {    
    public static void main(String[] args){    

    }
    private int [] sides = new int [4];
        public Rectangle () {  
            this.sides[0] = 1;
            this.sides[1] = 1;
            this.sides[2] = 1;
            this.sides[3] = 1;
        }
        public Rectangle(int value) {
            this.sides[0] = value;
            this.sides[1] = value;
            this.sides[2] = value;
            this.sides[3] = value;
        }
        public Rectangle(int value0, int value1) {
            this.sides[0] = value0;
            this.sides[1] = value0;
            this.sides[2] = value1;
            this.sides[3] = value1;
        }
        public int getLongSide() {
            int len = 0;
            for (int side : sides){
                if (side > len) {
                    len=side;
                }
            }
                return len;
            }
        public int getShortSide() {
            int len = getLongSide();
            for (int side : sides){
                if (side < len) {
                    len=side;
                }
            }
         return len;
        }

        public boolean isSquare() {
            boolean square = true;
            int test_value = sides[0];
            for (int side: sides) {
                if (side != test_value){
                    square = false;
                }
            }
            return square;
        }
        public int area () {
            int area = sides[0] * sides[2];
            return area; 
        }
        public double diagonal () {
            double len = Math.sqrt((sides[0]*sides[0])+ (sides[2]*sides[2]));
            return len;
        }
    public boolean bigger(Rectangle rect) {
        int current = area();
        int compare = rect.area();
        if (current > compare) {
            return true;
        }
        else {
            return false;
        }
    }
}
