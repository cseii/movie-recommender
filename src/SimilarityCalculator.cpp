#include "SimilarityCalculator.h"
#include <cstdlib>   // std::abs (절대값 함수)를 사용하기 위함

// 두 사람의 평점 목록을 비교하여 유사도 점수를 계산하는 함수
int SimilarityCalculator::calculate(const std::vector<Rating>& ratingsA, const std::vector<Rating>& ratingsB) {
    int commonCount = 0;    // 두 사람이 공통으로 본 영화의 개수를 저장할 변수
    int scoreDiffSum = 0;   // 공통으로 본 영화들의 평점 차이(절대값)를 누적할 변수

    // 2중 for문으로 전체 알고리즘 시간 복잡도를 줄임
    // 사용자 A가 본 모든 평점을 하나씩 꺼냄
    for (const Rating& rA : ratingsA) {
        // 사용자 B가 본 모든 평점을 하나씩 꺼내어 비교
        for (const Rating& rB : ratingsB) {
            // 두 평점 데이터의 영화 ID가 같다면 (즉, 같은 영화를 둘 다 봤다면)
            if (rA.getMovieId() == rB.getMovieId()) {
                commonCount++;   // 공통 영화 수 1 증가

                // 두 유저의 평점 차이에 절대값(std::abs)을 씌워 누적합에 더함
                scoreDiffSum += std::abs(rA.getScore() - rB.getScore());
            }
        }
    }

    // 엣지 케이스: 공통으로 본 영화가 없는 경우 방어
    // 연산 중단하고, 예외 값인 -100 안전하게 반환
    if (commonCount == 0) {
        return -100; 
    }

    // 최종 유사도 점수 산출 가이드 공식
    // 같은 영화를 많이 볼수록 점수 커지고, 평점 취향 다를수록 점수 낮아짐
    return (commonCount * 10) - scoreDiffSum;
}