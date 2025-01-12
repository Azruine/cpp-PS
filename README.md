# CPP로 백준 풀기

이게 뭘까

DP랑 그리디, 그래프 풀어보기

## 세팅
  
|**Software**|**Version**|
|---|---|
|**OS**|**Debian 13 Trixie**|
|**C++**|**C++23**|
|**GCC**|**14.2.0**|
|**CMAKE**|**3.31.3**|

src의 cpp 파일에 코드를 작성한 뒤 옵션을 선택하고 f5를 누르면 io/(코드파일명).input.txt 에 있는 내용을 stdin으로 입력받은 뒤, (코드파일명).output.txt에 stdout으로 출력한다.

txt 파일을 자동 생성하지는 않는다.

### 도커 관련 자잘한 문제들

Devcontainer를 쓰면서 도커를 처음 사용했는데, 문제가 생겼다.

제일 가벼운 리눅스를 사용하기 위해 alpine을 사용했는데, 여기선 pretty printer가 동작하지 않았다. 찾아보니 alpine gdb는 musl libc 라는걸 써서 glibc 기반 기능이 동작하지 않는다고 한다.

그래서 glibc를 지원하는 debian으로 갈아탔는데, bullseye 에서는 gcc 기본 버전이 무려 10이다. C++23을 지원하지 않아 trixie로 결정했다.

또 문제가 생겼다. [Cmake](./CMakeLists.txt)에 정의되지 않은 cpp 파일에서는 C++23 기능이 제대로 인식되지 않는다.

그래서 [devcontainer 설정 파일](./.devcontainer/devcontainer.json#L14) 에 관련 설정을 추가해서 C++23 기능을 제대로 인식할 수 있도록 해주었다.

## CPP 입출력

```cpp
#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define fastio                             \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

int main()
{
    fastio;
    std::cout << "Hello World!" << std::endl;
    return 0;
}
```
