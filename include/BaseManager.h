#ifndef BASE_MANAGER_H
#define BASE_MANAGER_H

#include <string>

// 추상 클래스 선언
// 내부에 순수 가상 함수가 하나라도 존재하므로 basemanager는 추상 클래스
// 이 클래스는 직접 객체 생성 불가, 오직 상속용 뼈대로만 사용
class BaseManager {
public:
    virtual ~BaseManager() {} // 가상 소멸자. 메모리 누수 방지. 이거 없으면 자식 클래스 virtual 호출 불가

    // 순수 가상 함수: 실제 구현부를 갖지 않음
    // 문법: 함수 선언 뒤에 '= 0'을 붙여 구현부 { } 가 없음을 컴파일러에게 알립니다.
    // 역할: 이 클래스를 상속받는 자식 클래스들에게 이 함수들을 "반드시 구현(오버라이딩)하라"고 강제
   
    // 규칙 1: 지정된 파일명으로부터 데이터를 읽어와 컨테이너에 적재하는 함수 규격
    virtual bool loadFromFile(const std::string& filename) = 0;
    // 규칙 2: 현재 메모리에 있는 데이터를 다시 파일로 내보내는 함수 규격
    virtual bool saveToFile(const std::string& filename) const = 0;
    // 규칙 3: 현재 매니저가 관리하고 있는 데이터의 총 개수를 반환하는 함수 규격
    virtual int size() const = 0;
};

#endif 