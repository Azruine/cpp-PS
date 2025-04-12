# CPP로 백준 풀기

이게 뭘까

DP랑 그리디, 그래프 풀어보기

[힘주고 쓴거 1](./src/solved/baekjoon/01080.md)

[힘주고 쓴거 2](./src/solved/baekjoon/02025.md)

## 세팅
  
|**Software**|**Version**|
|---|---|
|**OS**|**Debian 13 Trixie**|
|**C++**|**C++23**|
|**GCC**|**14.2.0**|
|**CMAKE**|**3.31.6**|

src의 cpp 파일에 코드를 작성한 뒤 옵션을 선택하고 f5를 누르면 io/(코드파일명).input.txt 에 있는 내용을 stdin으로 입력받은 뒤, (코드파일명).output.txt에 stdout으로 출력한다.

txt 파일을 자동 생성하지는 않는다.

## 도커 관련 자잘한 문제들

Devcontainer를 쓰면서 도커를 처음 사용했는데, 문제가 생겼다.

제일 가벼운 리눅스를 사용하기 위해 alpine을 사용했는데, 여기선 pretty printer가 동작하지 않았다. 찾아보니 alpine gdb는 musl libc 라는걸 써서 glibc 기반 기능이 동작하지 않는다고 한다.

그래서 glibc를 지원하는 debian으로 갈아탔는데, bullseye 에서는 gcc 기본 버전이 무려 10이다. C++23을 지원하지 않아 trixie로 결정했다.

또 문제가 생겼다. [Cmake](./CMakeLists.txt)에 정의되지 않은 cpp 파일에서는 C++23 기능이 제대로 인식되지 않는다.

그래서 [devcontainer 설정 파일](./.devcontainer/devcontainer.json#L14) 에 관련 설정을 추가해서 C++23 기능을 제대로 인식할 수 있도록 해주었다.

또또 문제가 생겼다. 이번엔 도커 볼륨 마운트 관련 문제다.

기존에는 다음처럼 볼륨을 마운트했다.

```compose
    volumes:
      - ../..:/workspaces:cached
```

근데 이러면 다른 도커 폴더들까지 싸그리 마운트가 되어버린다. 그래서 처음에는 [devcontainer 설정 파일](./.devcontainer/devcontainer.json#L5)처럼 환경 변수로 폴더 이름을 집어오게 했다. 물론 당연히 거기서 해결이 안 됐다 ^^.

그래서 좀 더 찾아보니, 아예 initializeCommand 옵션으로 환경 변수를 새로 만들어주더라. 하지만 생각해보니 굳이 ps용 C++ 환경에서 docker compose 가 필요한가 하는 생각이 들었고, 결국 docker-compose.yml을 삭제했다. 메데타시 메데타시.

## CPP 정적 분석

Rust나 Python 등의 다른 언어에서 정적 분석을 조금 맛보고 나니, CPP에도 도입하고 싶어졌다.

그래서 여러모로 찾아본 결과 clang-tidy와 cppcheck 투 트랙으로 가기로 했다.

물론 clang-tidy가 cppcheck에서 잡아주는 것들을 거의 다 잡아주는 것 같고, cppcheck는 기능을 추가하려면 돈을 내야 하지만... 혹시 아는가. 내가 나중에 MISRA를 써야 할 지.

그래서 겸사겸사 cppcheck 익스텐션도 조금 수정해서 추가했다.

## CPP 입출력

```cpp
#include <iostream>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

using std::cin, std::cout;

#define fastio                             \
    std::ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                         \
    cout.tie(NULL);

int main() {
    fastio;
    cout << "Hello World!" << endl;
    return 0;
}
```
