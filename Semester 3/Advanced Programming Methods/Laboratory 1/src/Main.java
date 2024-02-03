// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Main {
    public static void main(String[] args) {
        // Press Alt+Enter with your caret at the highlighted text to see how
        // IntelliJ IDEA suggests fixing it.
        System.out.println("Hello and welcome!");
        int sum = 0;
        for (String arg: args )
        {
            sum = sum + Integer.parseInt(arg);
        }
        int average;
        average = sum / args.length;
        System.out.println(average);
    }
}