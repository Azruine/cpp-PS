# CPP로 백준 풀기

이게 뭘까

DP랑 그리디, 그래프 풀어보기

## 세팅
  
|**Software**|**Version**|
|---|---|
|**OS**|**Alpine Linux 3.20**|
|**C++**|**C++23**|
|**GCC**|**13.2.1**|
|**CMAKE**|**3.29.3**|

src의 cpp 파일에 코드를 작성한 뒤 옵션을 선택하고 f5를 누르면 io/(코드파일명).input.txt 에 있는 내용을 stdin으로 입력받은 뒤, (코드파일명).output.txt에 stdout으로 출력한다.

txt 파일을 자동 생성하지는 않는다.

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
