import java.util.Scanner;

public class 홀짝판별 {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);

    System.out.print("숫자를 입력하세요: ");
    int num = sc.nextInt();

    if (num % 2 == 0) {
      System.out.println(num + "는 짝수입니다.");
    } else {
      System.out.println(num + "는 홀수입니다.");
    }
    sc.close(); 
  }
}
