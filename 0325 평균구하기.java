public class 평균구하기 {
  public static void main(String[] args) {
    
    int[] scores = {90, 80, 70, 100, 85}; // 예시로 5개의 숫자를 평균내는 경우
    int sum = 0;

    for (int i = 0; i < scores.length; i++) {
      sum += scores[i]; // 예시로 1부터 5까지의 합을 구하는 경우
    }

    double average = (double) sum / scores.length; // 평균 계산
    System.out.println("평균: " + average);
    System.out.println("총합: " + sum);
  }
}
