#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    int gender, age, activity;
    double height_cm, height_m, weight;
    double bmi, bmr, tdee;

    int foodNum;
    int total = 0;
    int foodCount = 0;

    double avg;
    double diff;

    double weekChange;
    double monthChange;
    double yearChange;

    char* foodName[30] = {
        "김치찌개 + 쌀밥",
        "된장찌개 + 쌀밥",
        "제육볶음 + 쌀밥",
        "불고기 + 쌀밥",
        "삼겹살 + 쌀밥",
        "돈까스 정식",
        "비빔밥",
        "김치볶음밥",
        "짜장면",
        "짬뽕",
        "라면",
        "칼국수",
        "냉면",
        "국밥",
        "치킨 1인분",
        "떡볶이",
        "순대",
        "샐러드",
        "햄버거 세트",
        "편의점 도시락",
        "과자 1봉지",
        "초콜릿 1개",
        "케이크 1조각",
        "아이스크림 1개",
        "아메리카노",
        "카페라떼",
        "탄산음료 1캔",
        "주스 1컵",
        "바나나 1개",
        "사과 1개"
    };

    int foodCal[30] = {
        700, 650, 900, 850, 1000,
        900, 700, 750, 800, 750,
        500, 600, 550, 700, 900,
        500, 350, 300, 800, 750,
        500, 230, 350, 250, 10,
        180, 150, 120, 90, 95
    };

    printf("성별을 입력하세요 (1: 남성, 2: 여성): ");
    scanf("%d", &gender);

    printf("나이를 입력하세요: ");
    scanf("%d", &age);

    printf("키(cm)를 입력하세요: ");
    scanf("%lf", &height_cm);

    printf("몸무게(kg)를 입력하세요: ");
    scanf("%lf", &weight);

    printf("\n활동 수준을 선택하세요.\n");
    printf("1. 거의 운동 안 함\n");
    printf("2. 가벼운 활동 / 주 1~3회 운동\n");
    printf("3. 보통 활동 / 주 3~5회 운동\n");
    printf("4. 활동 많음 / 매일 운동 또는 육체 활동\n");
    printf("선택: ");
    scanf("%d", &activity);

    height_m = height_cm / 100.0;
    bmi = weight / (height_m * height_m);

    if (gender == 1)
        bmr = 10 * weight + 6.25 * height_cm - 5 * age + 5;
    else
        bmr = 10 * weight + 6.25 * height_cm - 5 * age - 161;

    if (activity == 1)
        tdee = bmr * 1.2;
    else if (activity == 2)
        tdee = bmr * 1.375;
    else if (activity == 3)
        tdee = bmr * 1.55;
    else if (activity == 4)
        tdee = bmr * 1.725;
    else
    {
        printf("활동 수준 입력이 잘못되었습니다.\n");
        return 1;
    }

    printf("\n===== 음식 목록 =====\n");
    for (int i = 0; i < 30; i++)
    {
        printf("%2d. %s (%d kcal)\n", i + 1, foodName[i], foodCal[i]);
    }

    printf("\n먹은 음식 번호를 계속 입력하세요.\n");
    printf("간식도 포함해서 입력하면 됩니다.\n");
    printf("입력을 끝내려면 0을 입력하세요.\n\n");

    while (1)
    {
        printf("음식 번호 입력: ");
        scanf("%d", &foodNum);

        if (foodNum == 0)
            break;

        if (foodNum >= 1 && foodNum <= 30)
        {
            total += foodCal[foodNum - 1];
            foodCount++;

            printf("%s 추가됨! 현재 총 칼로리: %d kcal\n",
                foodName[foodNum - 1],
                total);
        }
        else
        {
            printf("잘못된 번호입니다. 1~30 사이 숫자를 입력하세요.\n");
        }
    }

    if (foodCount == 0)
    {
        printf("\n입력된 음식이 없습니다.\n");
        return 1;
    }

    avg = total / (double)foodCount;

    // 핵심 변경: BMR이 아니라 TDEE와 비교
    diff = total - tdee;

    weekChange = diff * 7 / 7700.0;
    monthChange = diff * 30 / 7700.0;
    yearChange = diff * 365 / 7700.0;

    printf("\n===== 오늘 결과 =====\n");
    printf("BMI: %.2f\n", bmi);
    printf("기초대사량(BMR): %.2f kcal\n", bmr);
    printf("하루 총소모 칼로리(TDEE): %.2f kcal\n", tdee);

    printf("\n총 섭취 칼로리: %d kcal\n", total);
    printf("먹은 음식 개수: %d개\n", foodCount);
    printf("음식 1개당 평균 칼로리: %.2f kcal\n", avg);

    if (diff > 0)
        printf("오늘은 총소모 칼로리보다 %.2f kcal 초과했습니다.\n", diff);
    else if (diff < 0)
        printf("오늘은 총소모 칼로리보다 %.2f kcal 부족합니다.\n", -diff);
    else
        printf("오늘은 총소모 칼로리와 섭취 칼로리가 같습니다.\n");

    printf("\n===== 이 식사 패턴이 계속된다면 =====\n");
    printf("1주일 예상 체지방 변화: %.2f kg\n", weekChange);
    printf("1개월 예상 체지방 변화: %.2f kg\n", monthChange);
    printf("1년 예상 체지방 변화: %.2f kg\n", yearChange);

    printf("\n===== 건강 경고 =====\n");

    if (yearChange >= 10)
        printf("경고: 이 식사 패턴이 지속되면 1년 후 체지방이 크게 증가할 수 있습니다.\n");
    else if (yearChange >= 5)
        printf("주의: 장기적으로 체지방 증가 가능성이 있습니다.\n");
    else if (yearChange <= -10)
        printf("경고: 이 식사 패턴이 지속되면 과도한 체중 감소 위험이 있습니다.\n");
    else if (yearChange <= -5)
        printf("주의: 장기적으로 체중이 줄어들 수 있습니다. 영양 부족을 조심하세요.\n");
    else
        printf("현재 패턴은 큰 체지방 변화 가능성이 비교적 낮습니다.\n");

    printf("\n※ 이 결과는 단순 추정치입니다.\n");
    printf("실제 변화는 운동량, 근육량, 수분, 수면, 호르몬, 식사 구성에 따라 달라질 수 있습니다.\n");

    return 0;
}


//
//
//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//
//int main(void)
//{
//    double dailyHour;
//    double unitHour;
//    double yearHour, tenYearHour, fiftyYearHour;
//    double yearResult, tenYearResult, fiftyYearResult;
//
//    printf("하루에 몇 시간 루틴을 실천하나요? ");
//    scanf("%lf", &dailyHour);
//
//    printf("성과 1개를 만드는 데 몇 시간이 걸리나요? ");
//    printf("(예: 책 1권 = 4시간이면 4 입력): ");
//    scanf("%lf", &unitHour);
//
//   
//    yearHour = dailyHour * 365;
//    tenYearHour = dailyHour * 365 * 10;
//    fiftyYearHour = dailyHour * 365 * 50;
//
//    yearResult = yearHour / unitHour;
//    tenYearResult = tenYearHour / unitHour;
//    fiftyYearResult = fiftyYearHour / unitHour;
//
//    printf("\n===== 루틴 누적 결과 =====\n");
//    printf("1년 누적 시간: %.1f시간 / 성과: %.1f개\n", yearHour, yearResult);
//    printf("10년 누적 시간: %.1f시간 / 성과: %.1f개\n", tenYearHour, tenYearResult);
//    printf("50년 누적 시간: %.1f시간 / 성과: %.1f개\n", fiftyYearHour, fiftyYearResult);
//
//    return 0;
//}