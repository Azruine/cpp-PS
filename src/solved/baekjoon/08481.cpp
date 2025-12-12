#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>
#include <bitset>
using namespace std;
unordered_map<size_t, uint64_t> fi;
constexpr static int64_t FUCK = 9099099909999099999;
auto fib(uint64_t i) {
    if (fi.contains(i)) {
        return fi[i];
    }
    fi[i] = (fib(i - 1) + fib(i - 2)) % FUCK;
    return fi[i];    
}
array<bool, 400010> isp = [](){
    array<bool, 400010> ret;
    ret.fill(true);
    ret[0] = false, ret[1] = false;
    for (int i = 2; i < 400010; i++) {
        if (ret[i]) {
            for (int j = i * 2; j < 400010; j += i) {
                ret[j] = false;
            }
        }
    }
    return ret;
}();
array one5 = {"","pierwszy","drugi","trzeci","czwarty","piaty","szosty","siodmy","osmy","dziewiaty","dziesiaty","jedenasty","dwunasty","trzynasty","czternasty","pietnasty","szesnasty","siedemnasty","osiemnasty","dziewietnasty"
};
array ten5 = {"","","dwudziesty","trzydziesty","czterdziesty","piecdziesiaty","szescdziesiaty","siedemdziesiaty","osiemdziesiaty","dziewiecdziesiaty"
};
array hun5 = {"","setny","dwusetny","trzysetny"
};
array hun2_5 = {"","sto","dwiescie","trzysta"
};
array mon5 = {"","stycznia","lutego","marca","kwietnia","maja","czerwca","lipca","sierpnia","wrzesnia","pazdziernika","listopada","grudnia"
};
array year5 = {"dwutysiecznego","tysiace pierwszego","tysiace drugiego","tysiace trzeciego","tysiace czwartego","tysiace piatego","tysiace szostego","tysiace siodmego","tysiace osmego","tysiace dziewiatego","tysiace dziesiatego","tysiace jedenastego","tysiace dwunastego","tysiace trzynastego","tysiace czternastego","tysiace pietnastego","tysiace szesnastego","tysiace siedemnastego","tysiace osiemnastego","tysiace dziewietnastego","tysiace dwudziestego"
};
array<string, 5> zero7 = {".####..", "##..##.", "##..##.", "##..##.", ".####.."};
array<string, 5> one7 = {"###.", ".##.", ".##.", ".##.", ".##."};
array<string, 5> two7 = {".####..", "##..##.", "...##..", ".##....", "######."};
array<string, 5> nine7 = {".####..", "##..##.", ".#####.", "....##.", ".####.."};
array<string, 5> com7 = {"......","......","......","##....",".#...."};
array<string, 5> per7 = {"......","......","......","##....","##...."};
array<string, 5> split7 = {".",".",".",".","."};
string ctod(int c) {
    if (c < 20) {
        return one5[c];
    }
    if (c < 100) {
        if (c % 10 == 0) {
            return ten5[c / 10];
        } else {
            string ret = ten5[c / 10];
            ret += " ";
            return ret + one5[c % 10];
        }
    }
    if (c % 100 == 0) {
        return hun5[c / 100];
    }
    string ret = hun2_5[c / 100];
    ret += " ";
    c %= 100;
    if (c < 20) {
        ret += one5[c];
    } else if (c % 10 == 0) {
        ret += ten5[c / 10];
    } else {
        ret += ten5[c / 10];
        ret += " ";
        ret += one5[c % 10];
    }
    return ret;
}
int64_t fact(int64_t x) {
    int64_t ret = 1;
    for (int i = 2; i <= x; i++) {
        ret *= i;
    }
    return ret;
}
string per(int64_t x) {
    if (x == 10000000000000000) {
        return "\"9099099909999099999\"\n";
    }
    int len = 1;
    string tm, ret = "\"";
    while (fact(len) < x) {
        x -= fact(len++);
    }
    for (int i = 0; i < len; i++) {
        tm.push_back(i + 'a');
    }
    for (int i = 0; i < len; i++) {
        int c = 1;
        while (c * fact(len - i - 1) < x) {
            c += 1;
        }
        ret += tm[c - 1];
        tm.erase(tm.begin() + c - 1);
        x -= (c - 1) * fact(len - i - 1);
    }
    return ret + "\"\n";
}
auto decom8(string& str, size_t cnt) {
    vector<uint8_t> dirs;
    for (char c : str) {
        int val = (c >= 'a') ? c - 'a' + 26 :
                  (c >= 'A') ? c - 'A' :
                  (c >= '0') ? c - '0' + 52 :
                  (c == '+') ? 62 : 63;
        dirs.push_back(val & 0x7);
        if (dirs.size() < cnt) {
            dirs.push_back((val >> 3) & 0x7);
        }
    }
    return dirs;
}
using Mat = array<bitset<70>, 70>;
Mat make(string& seq, int n) {
    array<bitset<70>, 70> ret;
    for (int i = 0; i < 70; i++) {
        ret[i].reset();
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ret[i][j] = seq[i * n + j] - '0';
        }
    }
    return ret;
}
Mat multiply(Mat& lhs, Mat& rhs) {
    Mat res;
    for (int i = 0; i < 70; i++) {
        res[i].reset();
    }
    Mat rhs_t;
    for (int i = 0; i < 70; i++) {
        for (int j = 0; j < 70; j++) {
            rhs_t[j][i] = rhs[i][j];
        }
    }
    
    for (int i = 0; i < 70; i++) {
        for (int j = 0; j < 70; j++) {
            res[i][j] = (lhs[i] & rhs_t[j]).count() & 1;
        }
    }
    return res;
}
Mat power(Mat M, int64_t exp) {
    Mat res;
    for (int i = 0; i < 70; i++) {
        res[i].reset();
        res[i][i] = 1;
    }
    
    while (exp > 0) {
        if (exp & 1) {
            res = multiply(res, M);
        }
        M = multiply(M, M);
        exp >>= 1;
    }
    return res;
}
int main() {
    int x;
    cin >> x;
    if (x == -1) {
        string str;
        cin >> str;
        cout << str.size();
    }
    if (x == 0) {
        cout << "ONTAK 2010";
    }
    if (x == 1) {
        string str = "Godzila terorizes Bajtoly lower again. Every day a monster comes out of the ocean, slow movement of marching through the city to some of the skyscrapers and eats it with people who are in it. Eating one skyscraper takes the whole day, at dusk, it returns to its hiding place hiden in the depths. To make maters worse, going through the city, Godzila wags its tail and destroys towers, near the pases. The prospect of becoming a meal for an underwater monster, to discourage some residents spent in uncomfort- tion in the city. During the night of each tower is derived as a resident and fles to the countryside. In Bajtogrodzie skyscrapers were built only at stret crosings. At each intersection there is exactly one building. Junctions are conected by two-way strets. In adition, a the junction is just above the ocean, this is where Godzila begins its destructive journey through the city. During the investigation, the monster moves only in the strets. Godzila noted that he must hury up with the consumption of residents and carefuly chose the skyscrapers devouring and strets, which reaches them. Of course, chosing never previously consumed or destroyed- wanego skyscraper. What is the maximum number of people who can eat before the city completely desolate? Entrance The first line of standard input contains two integers him (1 n 10 0, 0 50 0 m) respectively denoting the number of intersections in the city and the number of conecting strets. Crosroads numbers are numbered from 1 to n, junction 1 is located on the shores of the ocean. Next row contains a sequence of integers n s (0 s 10 0) to describe population skyscrapers at various intersections. In each of the next m rows are the two integers ai and bi (1 ai, bi n, ai = bi), which means that there is a road junction conecting ai and bi. The crosing number One can reach any other intersection in the city. Exit Write to stdout the number of people who eat Godzila for the optimum choice of meals and roads through the city every day. Example For input: the result is corect: 5 5 1 1 3 2 4 7 1 2 1 3 2 3 2 4 3 5";
        vector arr = {2932,2931,2928,2923,2916,5803,2883,2868,2851,2832,5599,2763,2736,2707,2676,2643,2608,2571,2532,2491,2448,2403,2356,2307,2256,2203,2148,2091,2032,1971,1908,1843,1776,1707,1636,1563,1488,1411,1332,1251,1168,1083,996,907,816,723,628,531,432,331,228,123,16,2839,2728,2615,2500,2383,2264,2143,2020,1895,1768,1639,1508,1375,1240,1103,964,823,680,535,388,239,88,2867,2712,2555,2396,2235,2072,1907,1740,1571,1400,1227,1052,875,696,515,332,147,2892,2703,2512,2319,2124,1927,1728,1527,1324,1119,912,703,492,279,64,2779,2560,2339,2116,1891,1664,1435,1204,971,736,499,260,19,2708,2463,2216,1967,1716,1463,1208,951,692,431,168,2835,2568,2299,2028,1755,1480,1203,924,643,360,75,2720,2431,2140,1847,1552,1255,956,655,352,47,2672,2363,2052,1739,1424,1107,788,467,144,2751,2424,2095,1764,1431,1096,759,420,79,2668,2323,1976,1627,1276,923,568,211,2784,2423,2060,1695,1328,959,588,215,2772,2395,2016,1635,1252,867,480,91,2632,2239,1844,1447,1048,647,244,2771,2364,1955,1544,1131,716,299,2812,2391,1968,1543,1116,687,256,2755,2320,1883,1444,1003,560,115,2600,2151,1700,1247,792,335,2808,2347,1884,1419,952,483,12,2471,1996,1519,1040,559,76,2523,2036,1547,1056,563,68,2503,2004,1503,1000,495,2920,2411,1900,1387,872,355,2768,2247,1724,1199,672,143,2544,2011,1476,939,400,2791,2248,1703,1156,607,56,2435,1880,2087,203,2572,2007,1440,871,300,2659,2084,1507,928,347,2696,2111,1524,935,344,2683,2088,1491,892,291,2620,2015,1408,799,188,2507,1892,1931,35,2344,1719,1092,463,2764,2131,1496,859,220,2511,1868,1223,576,2859,2208,1555,900,243,2516,1855,1192,527,2792,2123,1452,779,104,2359,1680,999,316,2563,1876,1187,496,2735,2040,1343,644,5047,1467,760,51,2272,1559,844,127,2340,1619,896,171,2376,1647,916,183,2380,1643,904,163,2352,1607,860,111,2292,1539,784,27,2200,1439,676,2843,2076,1307,536,2695,1920,1143,364,2515,1732,947,160,2303,1512,719,2856,2059,1260,3047,1783,976,167,2288,1475,660,2775,1956,1135,312,2419,1592,763,2864,2031,1196,359,2452,1611,768,2855,2008,1159,308,2387,1532,675,2748,1887,1024,159,2224,1355,484,2543,1668,791,2844,1963,1080,195,2240,1351,460,2499,1604,707,2740,1839,936,31,2056,1147,236,2255,1340,423,2436,1515,592,2599,1672,743,2744,1811,876,2871,1932,991,48,2035,1088,139,2120,1167,212,2187,1228,267,2236,1271,304,2267,1296,323,2280,1303,324,2275,1292,307,2252,1263,272,2211,1216,219,2152,1151,148,2075,1068,59,1980,967,2884,1867,848,2759,1736,711,2616,1587,556,2455,1420,383,2276,1235,192,2079,1032,2915,1864,811,2688,1631,572,2443,1380,315,2180,1111,40,1899,824,2679,1600,519,2368,1283,196,2039,948,2787,1692,595,2428,1327,224,2051,944,2767,1656,543,2360,1243,124,1935,812,2619,1492,363,2164,1031,2828,1691,552,2343,1200,55,1840,691,2472,1319,164,1939,780,2551,1388,223,1988,819,2580,1407,232,1987,808,2559,1376,191,1936,3235,1295,100,1835,636,2367,1164,2891,1684,475,2196,983,2700,1483,264,1975,752,2459,1232,3,1704,471,2168,931,2624,1383,140,1827,580,2263,1012,2691,1436,179,1852,591,2260,995,2660,1391,120,1779,504,2159,880,2531,1248,2895,1608,319,1960,667,2304,1007,2640,1339,36,1663,356,1979,668,2287,972,2587,1268,2879,1556,231,1836,507,2108,775,2372,3663,1287,2876,1531,184,1767,2411,640,2215,856,2427,1064,2631,1264,2827,1456,83,1640,263,1816,435,1984,599,2144,755,2296,903,2440,1043,2576,1175,2704,1299,2824,1415,4,1523,108,1623,204,1715,292,1799,372,1875,444,1943,508,2003,564,2055,612,2099,652,2135,684,2163,708,2183,724,2195,732,2199,732,2195,724,2183,708,2163,684,2135,652,2099,612,2055,564,2003,508,1943,444,1875,2171,292,1715,204,1623,108,1523,4,1415,2824,1299,2704,1175,2576,1043,2440,903,2296,755,2144,599,2419,1816,263,1640,83,1456,2827,1264,2631,3491,856,2215,640,1995,416,1767,184,1531,2876,1287,2628,1035,2372,775,2108,507,1836,231,1556,2879,1268,2587,972,2287,668,1979,356,1663,36,1339,2640,1007,2304,667,1960,319,1608,2895,1248,2531,880,2159,504,1779,120,1391,2660,995,2260,591,1852,179,1436,2691,1012,2263,580,1827,140,1383,2624,931,2168,471,1704,3,3691,752,1975,264,1483,2700,983,2196,475,1684,2891,1164,2367,636,1835,100,1295,2488,747,1936,191,1376,2559,808,1987,232,1407,2580,819,1988,223,1388,2551,780,1939,164,1319,2472,691,1840,55,1200,2343,552,1691,2828,1031,2164,363,1492,2619,812,1935,124,1243,2360,543,1656,2767,944,2051,224,1327,2428,595,1692,2787,948,2039,196,1283,2368,519,1600,2679,824,1899,40,1111,2180,315,1380,2443,572,1631,2688,811,1864,2915,1032,2079,192,1235,2276,383,1420,2455,556,1587,2616,711,1736,2759,848,1867,2884,967,1980,59,1068,2075,1299,2152,219,1216,2211,272,1263,2252,307,1292,2599,1303,2280,323,1296,2267,304,1271,2236,267,1228,2187,212,1167,2120,139,1088,2035,48,991,1932,2871,876,1811,3487,1672,2599,592,1515,2436,423,1340,2255,236,1147,2056,31,936,1839,2740,707,1604,2499,460,1351,2240,195,1080,1963,2844,791,1668,2543,484,1355,2224,159,1024,1887,2748,675,1532,2387,308,1159,2008,2855,768,1611,2452,359,1196,2031,2864,2355,2419,312,1135,1956,3435,1475,2288,167,976,1783,2588,459,1260,2059,2856,719,1512,2303,160,947,1732,2515,364,1143,1920,2695,536,1307,2076,2843,676,1439,2200,27,784,1539,2292,111,860,1607,2352,1067,1643,2380,183,916,1647,2376,171,896,1619,2340,127,844,1559,2272,51,760,1467,2172,2875,644,1343,2040,2735,496,1187,1876,2563,316,999,1680,2359,104,779,1452,2123,2792,527,3047,2516,243,900,1555,2208,2859,576,1223,1868,2511,220,859,1496,2131,2764,463,1092,1719,2344,35,656,1275,1892,2507,188,799,1408,2015,2620,291,892,1491,2088,2683,344,935,1524,2111,2696,347,928,1507,2084,2659,300,871,1440,2007,2572,203,764,1323,1880,2435,56,607,1156,1703,2248,2791,400,939,1476,2011,2544,143,672,1199,1724,2247,2768,355,872,1387,1900,2411,2920,495,1000,1503,2004,2503,68,563,1056,1547,2036,2523,76,559,1040,1519,1996,2471,12,483,952,1419,1884,2347,2808,335,792,1247,1700,2151,2600,115,560,1003,1444,1883,2320,2755,256,687,1116,1543,1968,2391,2812,299,716,1131,1544,1955,2364,2771,244,647,1048,1447,1844,2239,2632,91,480,867,1252,1635,2016,2395,2772,215,588,959,1328,1695,2060,2423,2784,211,568,923,1276,1627,1976,2323,2668,79,420,759,1096,1431,1764,2095,2424,2751,144,467,788,1107,1424,1739,2052,2363,2672,47,352,655,956,1255,1552,1847,2140,2431,2720,75,360,643,924,1203,1480,1755,2028,2299,2568,2835,168,431,692,951,1208,1463,1716,1967,2216,2463,2708,19,260,499,736,971,1204,1435,1664,1891,2116,2339,2560,2779,64,279,1195,912,3970,1728,1927,2124,2319,2512,5595,147,1543,875,1052,1227,1400,1571,1740,1907,2072,2235,2396,2555,2712,2867,88,239,388,535,680,823,964,1103,1240,1375,1508,1639,1768,1895,2020,2143,2264,2383,2500,2615,2728,2839,16,123,228,331,432,531,628,723,816,907,996,1083,1168,1251,1332,1411,1488,1563,1636,1707,1776,1843,1908,1971,2032,2091,2148,2203,2256,2307,2356,2403,2448,2491,2532,2571,2608,2643,2676,2707,2736,2763,2788,2811,2832,2851,2868,2883,2896,2907,2916,5851,2931,2932,2931,2928,2923,2916,2907,2896,2883,2868,5683,2811,2788,2763,2736,2707,2676,2643,5179,2532,2491,2448,2403,2356,2307,2256,2203,2148,2091,2032,1971,1908,1843,1776,1707,1636,1563,1488,1411,1332,1251,1168,1083,996,907,816,723,628,531,432,331,228,123,16,2839,2728,2615,2500,2383,2264,2143,2020,1895,1768,1639,1508,1375,1240,1103,964,823,680,535,388,239,88,2867,2712,2555,2396,2235,2072,1907,1740,1571,1400,1227,1052,875,696,515,332,147,2892,2703,2512,2319,2124,1927,1728,1527,1324,1119,912,703,492,279,64,2779,2560,2339,2116,1891,1664,1435,1204,971,736,499,260,19,2708,2463,2216,1967,1716,1463,1208,951,692,431,168,2835,2568,2299,2028,1755,1480,1203,924,643,360,75,2720,2431,2140,1847,1552,1255,956,655,352,47,2672,2363,2052,1739,1424,1107,788,611,2751,6283,1431,1096,759,420,79,2668,2323,1976,1627,1276,923,568,211,2784,2423,2060,1695,1328,959,588,215,2772,2395,2016,1635,1252,867,480,91,2632,2239,1844,1447,1048,647,244,2771,2364,1955,1544,1131,716,299,2812,2391,1968,1543,1116,687,256,2755,2320,1883,1444,1003,560,115,2600,2151,1700,1247,792,335,2808,2347,1884,1419,952,483,12,2471,1996,1519,1040,559,76,2523,2036,1547,1056,563,68,2503,2004,1503,1000,495,2920,2411,1900,1387,872,355,2768,2247,1724,1199,672,143,2544,2011,1476,939,400,2791,2248,1703,1156,607,56,2435,1880,1323,764,203,2572,2007,1440,871,300,2659,2084,1507,928,347,2696,2111,1524,935,344,2683,2088,1491,892,291,2620,2015,1408,799,188,2507,1892,1275,656,35,2344,1719,1092,463,2764,2131,1496,859,220,2511,1868,1223,576,2859,2208,1555,900,243,2516,1855,1192,527,2792,2123,1452,779,104,2359,1680,999,316,2563,1876,1187,496,2735,2040,1343,644,2875,2172,1467,760,2323,1559,844,127,2340,1619,896,171,2376,1647,916,183,2380,1643,904,163,2352,1607,860,111,2292,1539,784,27,2200,1439,3519,2076,1307,536,2695,1920,1143,364,2515,1732,947,160,2303,1512,719,2856,2059,1260,459,2588,1783,976,167,2288,1475,660,2775,1956,1135,312,2419,1592,763,2864,2031,1196,359,2452,1611,768,2855,2008,1159,308,2387,1532,675,2748,1887,1024,159,2224,1355,484,2543,1668,791,2844,1963,1080,195,2240,1351,460,2499,1604,707,2740,1839,936,31,2056,1147,236,2255,1340,423,2436,1515,592,2599,1672,743,2744,1811,876,2871,1932,991,48,2035,1088,139,2120,1167,212,2187,1228,267,2236,1271,304,2267,1296,323,2280,1303,324,2275,1292,307,2252,1263,272,2211,1216,219,3303,148,2075,1068,59,1980,967,2884,1867,848,2759,1736,711,2616,1587,556,2455,1420,383,2276,1235,192,2079,1032,2915,1864,811,2688,1631,572,2443,1380,315,2180,1111,40,1899,824,2679,1600,519,2368,1283,196,2039,948,2787,1692,595,2428,1327,224,2051,944,2767,1656,543,2360,1243,124,1935,812,2619,1492,363,2164,1031,2828,1691,552,2343,1200,55,1840,691,2472,1319,164,1939,780,2551,1388,223,1988,819,2580,1407,232,1987,808,2559,1376,191,1936,747,2488,1295,100,1835,636,2367,1164,2891,1684,475,2196,983,2700,1747,1975,752,2459,1232,3,1704,471,2168,931,4007,140,1827,580,2263,1012,2691,1436,179,1852,591,2260,995,2660,1391,120,1779,504,2159,880,2531,1248,2895,1608,319,1960,667,2304,1007,2640,1339};
        size_t len = str.length();
        for (size_t i = 0; i < len; i++) {
            string out;
            out.append(arr[i], str[i]);
            cout << out;
        }
        cout << '\n';
    }
    if (x == 2) {
        fi[0] = 1, fi[1] = 1;
        for (size_t i = 0; i < 10000; i++) {
            cout << fib(i) << ", ";
        }
        cout << "0.\n";
    }
    if (x == 3) {
        for (auto i = 0; i < 1024; i++) {
            for (auto j = 0; j < 1024 - i; j++) {
                if (i == 506 && ((j >= 450 && j <= 453) || j == 456 || j == 457 || j == 460 || j == 461 || (j >= 463 && j <= 468) || j == 471 || j == 472 || j == 476 || j == 477 || j == 480 || j == 481 || (j >= 487 && j <= 490) || (j >= 494 && j <= 497) || (j >= 500 && j <= 502) || (j >= 505 && j <= 508))) {
                    cout << '#';
                    continue;
                }
                if (i == 507 && (j == 449 || j == 450 || j == 453 || j == 454 || (j >= 456 && j <= 458) || j == 460 || j == 461 || j == 465 || j == 466 || (j >= 470 && j <= 473) || j == 476 || j == 477 || j == 479 || j == 480 || j == 486 || j == 487 || j == 490 || j == 491 || j == 493 || j == 494 || j == 497 || j == 498 || j == 501 || j == 502 || j == 504 || j == 505 || j == 508 || j == 509)) {
                    cout << '#';
                    continue;
                }
                if (i == 508 && (j == 449 || j == 450 || j == 453 || j == 454 || j == 456 || j == 457 || (j >= 459 && j <= 461) || j == 465 || j == 466 || j == 469 || j == 470 || j == 473 || j == 474 || (j >= 476 && j <= 479) || j == 489 || j == 490 || j == 493 || j == 494 || j == 497 || j == 498 || j == 501 || j == 502 || j == 504 || j == 505 || j == 508 || j == 509)) {
                    cout << '#';
                    continue;
                }
                if (i == 509 && (j == 449 || j == 450 || j == 453 || j == 454 || j == 456 || j == 457 || (j >= 460 && j <= 461) || j == 465 || j == 466 || (j >= 469 && j <= 474) || j == 476 || j == 477 || j == 479 || j == 480 || j == 487 || j == 488 || j == 493 || j == 494 || j == 497 || j == 498 || j == 501 || j == 502 || j == 504 || j == 505 || j == 508 || j == 509)) {
                    cout << '#';
                    continue;
                }
                if (i == 510 && ((j >= 450 && j <= 453) || j == 456 || j == 457 || (j >= 460 && j <= 461) || j == 465 || j == 466 || (j >= 469 && j <= 470) || (j >= 473 && j <= 474) || j == 476 || j == 477 || j == 480 || j == 481 || (j >= 486 && j <= 491) || (j >= 494 && j <= 497) || (j >= 501 && j <= 502) || (j >= 505 && j <= 508))) {
                    cout << '#';
                    continue;
                }
                cout << (i & j ? '.' : '#');
            }
            cout << '\n';
        }
    }
    if (x == 4) {
        for (int i = 0; i < 5000; i++) {
            if (i == 3333) {
                cout << "11111011909909990999909999911011111011101011101011111111111011111111101111111011\n";
                continue;
            }
            for (int j = 0; j < 80; j++) {
                cout << !isp[i * 80 + j + 2];
            }
            cout << '\n';
        }
    }
    if (x == 5) {
        int y = 2000, m = 1, d = 1, c = 1;
        while (1) {
            string tm;
            if (y == 2007 && m == 4 && d == 1) {
                tm = "Pierwszego kwietnia jest prima aprilis.\n";
            } else if (y == 2013 && m == 6 && d == 1) {
                tm = "Pierwszego czerwca jest dzien dziecka.\n";
            } else {
                tm = ctod(d) + " ";
                tm += mon5[m];
                tm += " to ";
                tm += ctod(c);
                tm += " dzien roku";
                tm += (y == 2000 ? " " : " dwa ");
                tm += year5[y - 2000];
                tm += ".\n";
            }
            tm.front() = toupper(tm.front());
            if (m == 12 && d == 31) {
                m = 1, d = 1, y += 1, c = 0;
            } else if (d == 31 || (d == 30 && (m == 4 || m == 6 || m == 9 || m == 11))) {
                m += 1, d = 1;
            } else if (m == 2 && (d == 29 || (d == 28 && (y % 4)))) {
                m += 1, d = 1;
            } else {
                d += 1;
            }
            c += 1;
            cout << tm;
            if (y == 2021) {
                break;
            }
        }
        cout << "Koniec.\n";
    }
    if (x == 6){
        for (int64_t i = 1; i <= 20000; i++) {
            cout << "T[" << i * i * i * i << "]=" << per(i * i * i * i);
        }
    }
    if (x == 7) {
        array<string, 4> end = {"01020102001020021020001020010200120000120001200102010200120120012001200102012001020102012001020102010102010201200120012012001220100200012002010201020102010200","120012012001200120012001200120012001200120012012001201002000102001201200020020010020102001200001020102000120002010200102020000102001202002102001200202010201","0201020010020201020201020200120010001200201200102012001200120102012002100002010200010200012022020012020102020102020102010909909990999909999902010200120012","0012010201020102012001201201020120102012002001020012001200120012000120012001200210200120000120012001201200120102001001001001010100101000020102010200102001020001"};
        string res = "1";
        string str1, str2;
        string line_split(1000, '.');
        str2 = "1";
        for (int _ = 1; _ < 171; _++) {
            str1 = std::move(str2);
            str2.resize(str1.length());
            int32_t carry = 0, cur = 0;
            for (size_t i = 0; i < str1.length(); i++) {
                cur = (str1[i] - '0') * 2 + carry;
                carry = cur / 3, cur %= 3;
                str2[i] = cur + '0';
            }
            while (carry > 0) {
                cur = carry % 3, carry /= 3;
                str2.push_back(cur + '0');
            }
            res = res + "," + str2;
        }
        res += ",0.";
        vector<array<string, 5>> out(1);
        auto get = [](char c) -> auto& {
            switch (c) {
                case '0': return zero7;
                case '1': return one7;
                case '2': return two7;
                case '9': return nine7;
                case '.': return per7;
                case ',': return com7;
            }
            unreachable();
        };
        constexpr static size_t MAX = 1000;
        size_t width = 0;
        size_t i = 0;
        while (i < res.size()) {
            size_t j = i;
            size_t chunk = 0;
            while (j < res.size()) {
                auto& font = get(res[j]);
                chunk += font[0].size();
                if (res[j] == ',' || res[j] == '.') {
                    j++;
                    break;
                }
                j++;
            }
            if (width > 0 && width + chunk > MAX) {
                out.emplace_back();
                width = 0;
            }
            while (i < j) {
                auto& font = get(res[i]);
                for (int r = 0; r < 5; r++) {
                    out.back()[r] += font[r];
                }
                i++;
            }
            width += chunk;
        }
        for (auto& line : out) {
            for (int r = 0; r < 5; r++) {
                cout << line[r] << string(MAX - line[r].size(), '.') << '\n';
            }
            cout << line_split << '\n';
        }
        for (auto& e : end) {
            cout << line_split << '\n';
            array<string, 5> line_out{};
            for (char c : e) {
                auto& font = get(c);
                for (int r = 0; r < 5; r++) {
                    line_out[r] += font[r];
                }
            }
            for (int r = 0; r < 5; r++) {
                cout << line_out[r] << string(MAX - line_out[r].size(), '.') << '\n';
            }
        }
    }
    if (x == 8) {
        string ds = "+233+++233333333333/+++3/++3/+/+/+/+/+//+///////////////n/////n////8///8///8///8///8///8///8//n///8//8/n//8/8/8/8n/n/8n/88nn/888nnnnnnnn8888knn8knn8kn8knkn8k8k8k8k8k8kknk8kknk8kk8kknkknkknkk8kk8kk8kkknkknkk8kk8kk8kkknkknkk8kkknkk8kkk8kkkk8kkkkknkkkkkkkkkkkkkkkkkkkkkkikkkkikkUkkUkkikUkkikiUkUkUkiUkiUkiUkiUUkiUUkiiUUkiiiUUUkiiiUUUkiiiUUUkiiiUUUUkiiiUUUkiiiiUUUUUkiiiiiiiiiiiiiiiiSUUiiSUUiSUiSUSUSUSUSSUSSSSSSSSSSRSSSKSSSRSKSKSKSKSKSKSRKSKSRKSKSRKSRKSRKSKSRKSRKSRKSKSRKSRKSRKSRKKSRKKSRKKKSRRRKKKKKKKKKKKKRRRJKKRJKRJKRJKRJRJKJKJRJRJJRJJKJJRJJJKJJJJKJJJJJKJJJJJJJKJJJJJJJJJJJRJJJJJJJJJJJJJJKJJJJJJJJJJJJJJJKJJJJJJJJJJJJJJJJJJIJJJJJJJBJJJJBJJJIJJBJJIJBJBJJIBJBJIJIBJIBBJIBBJIIIBBBBBBBBBBBBBBBBBIIIIABBBIIIABBIIIABBIIABBBIIABBBIIABBIIABBBIABBIIABIABIABIABABIAIAABAIAAAAAAAAAAAADAAADAYAYAYAYADYADYADDYYADDYYYYADDDDDYYYYYYYYYYYADDDDDDDDDDDDDDYYYYYYYYYYYYYYYYYYYYYYDDDDbYYYDDbYYDDbYDbYDbYbYDbDbDbbYbDbbYbbYbbbYbbbbDbbbbbbbbbbbbbbbbbbbbbbbrbbbbbbbdbbbbbdbbbbbdbbbbrbbbbbrbbbbbdbbbbbdbbbbdbbbbdbbbbdbbbdbbrbbrbbrbbdbrbbdbdbdbdrbdbdrrbdrbddrrrrbdddddddtrrrddtrrdtrdtrdtrtrdtdtdtrtrtdtdtdtdtdtdttrtrtrtrtrtdtdtdttrtrtdttdttdtttttttttttttttutt1ttututu1tu1tu11tuuu11111111111uuuu211uu211uu211u211uu21u211u211u211u211u21uu21uu21u211u21u21u21u21u21u2u212121212u2212u22u222u2222u22222222222222222232222+222+222322+2232232+2232+2232+223232+2232+2+2232+223232+223232+2+223232323232323+2+23+2++23+233+23333+++++++++333/+33/+/+3/3/3/3//3//3////3////////+//////////////////////////////////n/////8//n//8/8/8/8n/8n/88nn/8888888888knn88knn8kn8kn8kn8knkn8k8k8k8k8knk8k8k8k8k8k8kknknknknknk8k8k8k8k8k8kknknknk8kknknk8kk8kknkk8kkknkkk8kkkkkk8kkkkkkkkkkikkkkkUkkkkikkikkikUkkikikikikiUkUkiUkUkiUkiUkiUkiUkiUkiUkiUUkiUkiUkiUkiUkiUkiUUkiUkiUkiiUkiUUkiiUUkiiiUUUUUUUUUUUUUiiiSUiSUiSUSUSUSiSSSSSSSSSSSSSSSSRSSSRSSRSSRSSRSKSSRSKSSRSKSSRSKSSKSSRSKSSRSKSKSKSSRSRKSKSRKSRKSRRKKSRRRRKKKKRRRRRJKKRJKKRJKJKRJKJKJKJKJRJRJJRJJKJJKJJRJJJKJJJKJJJRJJJRJJJJKJJJRJJJJKJJJRJJJRJJJJKJJJRJJJJRJJJJJKJJJJJJRJJJJJJJJJJJJJJJIJJJJJIJJJIJJBJJIJBJBJJIBJBJIBJIBJIBJIIBBJIIBBBJIIIIIBBBBBBBBBBJIIIIIIIIIIIIIIIIBBBBBBBBBBBBBBBBBBBBBBBBBIIIABBBIABBIABIAIAIAIAAIAAAAAAAADAAAADAADAYAYAYAYADYADYADYADYYADYYADYYADYYADDYADDYADDYADDYADDYYADYYADDDYYYADDDDDYYYYYDDDDDbYYDDbYDbYDbYDbDbDbDbDbbYbbYbbYbbbYbbbbDbbbbbbbbbbDbbbbbbbbbbbbbbbbbbbrbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbdbbbbbbbdbbbbrbbbrbbrbbrbbdbdbdbdbdrbdrbdrbddrrrbddddddddddddtrrrddtrrddtrdtrrdtrdtrrdtrdtrrdtrdtrrdtrdtrrdtrdtrdtrdtrtrdtdtdttrtdttttttttttttutt1ttututu1tu1tu11tuuu1111111tuu21111111111uuuuuu2111111uuuuuuu21111111uuuuu21111uuu211uu211u21u21u21u2u21212u2u22u22u222u22222212222222222223222222+222223222+222+22232223222322+222+222+22232223222322+222322+22+22+2232+22323232323+23+23+233++233333333333/++3/++3/+/+3/3/3/3//+/3//+//+//+//+//+//+//+//+//+/3//3///+//3////////////n////8//8/8/8n/8n/8nnn/8888888888knnn88knn8knn8kn8kn8kn8kn8kn8kn8k8kn8kn8kn8kn8kn8kn8k8kn8kn8kn8k8kn8k8knknknknknk8kknkknkknkkk8kkkkkkk8kkkkkikkkkkkkikkkUkkkikkikUkkikUkkikikikikikikikikikikikiUkUkUkUkUkUkUkUkUkUkUkUkikikiUkUkikiUkiUkiUkiUUkiiUUUUkiiiiiSUUUiiSUiSUiSiSiSSUSSUSSSSSSSSSSSSSSRSSSSSSSSRSSSSSSSRSSSSSSSSKSSSSSSKSSSSRSSKSSRSKSKSKSRKSRKKSRRRRKKKKKRRRRJKKRJKRRJRJKRJKJKJKJKJKJKJRJRJJKJRJJKJRJJRJJKJRJJKJRJJRJJKJRJJKJRJJKJRJJKJJKJRJJRJJJKJJRJJJRJJJJJJKJJJJJJJJJJJJBJJJJJIJJJIJJIJBJJIJIJIJIBJBJIBJIBJIBBJIBJIIBBJIBBJIIBBJIIBBJIBBJIIBBJIBBJIIBJIIBBJIIBBJIIIBBBBJIIIIIIIIIABBBIABBIABABABAIAAAAAAAAAAAAAYAAADAADADAYAYAYAYAYAYADADADYAYAYAYAYAYADADADADADYAYADADYADYADDYADDYYYYYYYYYYYYYDDbYYDbYDbYDbDbDbDbbYbDbbYbbYbbbYbbbYbbbbDbbbbbbYbbbbbbYbbbbbbDbbbbbbDbbbbbbYbbbbbbYbbbbbbbYbbbbbbbbbbbbbbbbbbbbdbbbbdbbbdbbdbrbrbbdrbrbdrbdrbdrrbddrrrrbddddddddddddtrrrrrrdddddtrrrrrrdddddddtrrrrrrrdddddtrrrdddtrrdtrdtrdtrtrtrtdttttttttt1ttt1tt1t1t1tu1tu1tu11tuu11tuuu1111tuuuu111tuuuu111tuuu111tuuu1111tuuuuuu1111111uuuuu211uu21u21u2121u221212u22u2221222u222222222222222222222222222+22222222+22222222232222222222322222222+2222222322223222322+22+22323232323+23+23+2333++++++++++++333/+33/+3/+3/+/+3/+/+3/3/+/+3/3/+3/3/+3/3/+3/3/+3/3/3/+/+/3//+//+///////8////n//8/8/8n/8n/88nnnn/888888knnnnn888knnn88knnn88knn88knnn88knnn88knnn88knnn88knn88kn88kn8kn8kn8knknknknknk8kk8kkknkkkk8kkkkkkkkkkkkkkikkkkkikkkikkUkkkikkikkikkikUkkUkkikkikkikkikUkkUkkUkkUkkUkkUkkikkikUkkikikUkUkikiUkUkiUkiiUUkiiiUUUUUUiiiSUUiSUiSUSUSUSiSSUSSiSSSSUSSSSUSSSSSUSSSSiSSSSiSSSSUSSSSSSSSSSSSSSSSSSRSSKSSRSRSRKSRRKKSRRRRRRRRRRRJKKRRJKRJKRJKRJKJKRJKJKRJRJRJKJKJKRJRJRJKJKJKRJRJKJKRJRJKJKRJRJRJKJKJKJRJRJJKJRJJKJJRJJJRJJJJJJJJJKIJJJJJJJJBJJJBJJJIJBJJIJBJBJBJBJBJIJIBJBJIBJIJIBJIBJBJIBJBJIBJBJIBJBJIBJBJIJIBJIBJBJIBJIIBJIBBJIIBBBBJIIIIABBBIIABIABIAIAABAAAAAAAAAAAAAAADAAAYAAADAAYAAADAAYAAAYAAAYAAAYAAAYAAADAADAYAYAYAYADADDYADDYYYYYYYYYYDDbYYDbYDbYDbDbYbYbYbDbbYbDbbDbbDbbDbbbYbbDbbbYbbDbbbYbbYbbDbbDbbDbbbYbbYbbDbbbYbbbYbbbDbbbbbbDbbbbbbbbbbdbbbbbdbbbdbbdbrbrbrbrbdbdrbdrrbdrrbddrrbdddrrrrbddddrrrrbddddrrrrbdddrrrbdddrrrrbddddrrrrrrrrrrrrdddtrddtrtrdtdttdttttttutttttut1ttututu1t1tu1tu1tu1tu1tu1tu1tu1tu1t1tu1tu1tutu1tu1tuu1tuu11tuuuu11111uuuu211u21u21u2u2u2u2u22u22u222u2222u2222222212222222222222222222122222222222222u22222222222222222222222222232222322232+2232+2+2323+23+233+++233333333333/+++333/++33/++3/++33/++333/++333/++333/++33/++3/+33/3/+3/3//+////////////n//8/8/8n/8n/8nn/8888nnnnnnnnnnnnnnnnnnnnnnnnnn/8888888888888nnnnnnnnn888888knn88knn8kn8k8knknknk8kknkk8kkkk8kkkkkkkkkkkkkkkkkkikkkkkUkkkkkikkkUkkkkUkkkkkikkkkUkkkkkikkkkkikkkkUkkkkikkkikkUkkUkkikUkUkUkUkiUkiUkiiUUUUkiiiSUUUUiiSUiSUiSiSUSUSUSUSiSiSSUSiSiSSUSUSUSiSiSiSiSiSiSSUSUSSUSSUSSSSSSSSSRSSSRSKSKSRKSRKKSRRRRRRRRRRRRJKKRRJKKRJKKRJKRRJKRJKRJKKRJKRRJKRJKKRJKKRJKKRJKKRJKRRJKRJKRJRJKJKRJJKJKJRJJRJJJKJJJJJRJJJJJJJBJJJJJJIJJJIJJBJJBJJIJBJJIJIJBJBJJIJIJIJBJBJJIJBJBJJIJBJJIJIJBJJIJBJBJBJBJBJBJBJIBJBBJIBJIIBBBBBBBBBBBIIABIABABABAIAAIAAAAAABAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAYAAAAAAYAAYAADADADYADDYYYADDDDbYYYYDbYYDbYDbYbYDbDbDbDbDbDbDbbYbYbDbDbbYbYbDbDbDbDbbYbYbYbYbYbYbYbDbDbbYbDbbYbbYbbDbbbbDbbbbbbbbbbbbbrbbbbrbbrbbrbrbbdbdrbrbdbdrbdrbdrrbdrbdrrbdrbdrrbdrbdrbdrbddrbdrbdrbdrbdrbdrrbddrrbdddrrrrrrrrddtrrdtrtrtrtdtttttttutttt1tttut1ttut1t1ttutut1t1ttut1tt1ttut1ttut1ttutututu1tu1tuu11tuuuuuu2111uu21u2121u2u2u2212u22u22212221222u2222u2222u2222u2222u222u222212221222u222212222u222222222222222222+222232232+2+2+2+2323++23++2333+++++2333333333333333333333333333333333+++++++++++++++333/++3/++/+3//+///////////8/n//8/8n/8n/8n/88n/88nn/88nn/88nn/88nn/8nn/8nn/8n/88nn/88nn/88888888888knn88kn8kn8k8k8kknk8kk8kkkknkkkkkkk8kkkkkkkkkkUkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkUkkkkkkkkkkkkkkUkkkkUkkkUkkikUkUkUkUkiUkiUUkiiiUUUUUUUiiiSUUiiSUiSUiSUiSUiSUiSUiSUiSUUiSUiiSUiSUUiSUiSUiSUiSiSUSiSSSSSSSSSSSSSRSKSKSRKSRKKSRRRRRRKKRRRRRRRJKKKKRRRRJKKKKRRRRRJKKKKKKKRRRRRRRRJKKKKKRRRJKKRJKRRJRJKRJRJRJJKJJKJJRJJJJJJRJJJJJIJJJJJJJIJJJBJJJBJJJIJJBJJJIJJIJJBJJJIJJJIJJJIJJJIJJJIJJJIJJBJJJIJJIJBJJIJIJIBJBJIBJIIBBJIIIIIIABBBIABIABABABABAIAAIAAABAAABAAIAAABAABAABAIAAIAABAABAAAAAAAAAAAAAAADAYAYAYADYYADDDDDDDDDDbYYDDbYDbYDbYDbYDbDbYDbDbYDbDbYDbYDbYbYDbYDbYDbYDbYDbYDbYDbDbYbYbYbYbDbbYbbDbbbbYbbbbbbbbbbbdbbbbdbbrbbrbbdbdbdbdbdbdbdrbrbrbdbdrbrbrbrbdbdbdbdbdbdbdbdbdbdbdbdbdrbdbdrbddrbdddrrrrrrrrddtrdtrtrtrttttttttttttttt1tttttutttt1ttttttttuttttttttt1ttttuttututu1t11tuu11111111uu21uu2121u2u2u2u2u2212u22u2212212212212u22u2212u2212u2212u2212u22122122122u2222122222222222222+222+22+2232323+2+23+23++23++233++2333++2333++233++233+233+233+233++233++23333+++++333/++3/+3/3////////////8//8/8/8/8/8n/n/8n/n/8/8n/n/8/8/8/8/8/8/8/8/8/8n/8n/8n/888nnnnnnn88knn8kn8k8knk8kknk8kkknkkk8kkkkkk8kkkkkkkkk8kkkkkkkk8kkkkkk8kkkkkknkkkkknkkkkkkk8kkkkkkkkUkkkkkkikkUkkikUkUkUkiUkiUUkiiiUUUUUUUUUUiiiiSUUUUiiiSUUUiiiiiSUUUUUUUUUUiiiiiiiSUUUiiSUUiSUSUSUSSSSSSSSSSKSSKSKSRKSRKKSRRKKKSRRRRRRKKKKKKKSRRRRRKKKSRRRKKSRRRKKKSRRRRKKKKKKRRRJKKRRJKRJRJKJKJRJJRJJJKJJJJJJJRJJJIJJJJJJJJJBJJJJJJBJJJJJJBJJJJJJJJBJJJJJJJJJJJJIJJJJJJJBJJJJJIJJBJJBJBJJIJIBJIBJIIBBBJIIIABBBIIABIABIABABIAIAIAIAIAIABABABIABABIABIABABIABABIAIAABAAAAAAAAAADAADADYADYADDDYYYYYYDDDbYYYDDbYYDbYYDDbYDDbYYDDbYYYDDbYYYDDDbYYYDDDbYYDbYYDbYDbDbYbYbDbbYbbDbbbbbbYbbbbdbbbbbbdbbbdbbdbbdbrbbdbrbbdbrbbdbbdbrbbrbbrbbrbbrbbrbbbdbrbbrbbdbrbrbrbdbdrbddrrbdddddddtrrdtrdtdttrttrttttdtttttttttdttttttrtttdtttdttttttttttttttuttut1tu1tuu111111111uu21u21u21u2u2121212121212121212121u2u2121u2u2121u2121u2u2u2u2u2212u22212222122222222+2222322+2232+2+2323+2+23+23+23+23+23+23+2+23+2+23+2+232323+2323+23+23+233++23333333/++3/+/+/+/////////8///8//8//8/n//n//n///8///8///n////8//n//n/n/n/8n/8nnnn/knnnn88kn8knkn8kknknkknkknkknkkknkkknkkk8kkknkkknkk8kk8kk8kk8kk8kk8kk8kkk8kkkknkkkkkkkkkkkkkikkkikkikUkUkiUkUUkiUUkiiUUUUUkiiiiiiiiiUUUUUUkiiiiUUUkiiUUUkiiiUUUkiiiiiiiiiSUUiSUiSiSSSSSSSSSSKSSKSKSRSRKSRKKSRKSRRKSRRKSRKSRKSRKSKSRKSKSRKSRKSRKSRRKKKKKKKKKKRRJKRJKJKJKJKJJKJJRJJJJJRJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJRJJJJJJJJJJKJJJJJJJJJJJJJJBJJJJBJJJIJBJBJBJIBJIBBJIIIIIIIIIABBIIABBIABIABBIABBIABBIIIABBBIIIABBBIIIABIIABIABABABAAAAAAAYAAYAYAYADYYADDDDDDYYDDDDDDDDDbYYYYYYYYYYYYYYYYADDDDDDDYYYYYYYYDDDDbYDDbYDbDbDbDbbDbbbDbbbbbbbbbbbbbbdbbbbrbbbrbbbrbbbrbbbrbbbbrbbbbbrbbbbbbrbbbbbbdbbbrbbbdbbdbrbrbrbdrbddrrrbdtrrrrdtrdtrtrtrtdttrttrtdttdttrtdtdtdtdtdtdtrtrtrtdttttttttttttututu1tuu11111111uu211u21uu21u2u21u21u21u21uu21u211uu211u211uu21u211u2u212121212u222u222222222222+222+22+2232+2+2+2+2+2+2+2+2+2+223232+2+22+2232+2232+22323232323+23++2333+++333/+3/+/+////////////////////////////3////////////8////8/n/n/8n/88888888knn8kn8k8k8k8k8kknknk8kk8kknk8kknknk8k8k8k8k8k8k8k8k8k8k8k8kknkknkk8kkkkkkkkkkkkkkUkkUkkikUkUkiUkUUkiUkiiUkiiUUkiiUkiiUkiiUkiUkiUkUkiUkiUkiUkiUUkiiUUUkiiSUUUiSUiSiSSSSSSSSRSSKSSRSRSRSRSRSRKSKSSRSRSKSSKSSKSSKSSKSSRSRKSKSRRKKKKKKKKRRJKRJKJKJKJRJJRJJJKJJJJRJJJJJJRJJJJJJKJJJJRJJJJKJJJKJJRJJJRJJJRJJJJJKJJJJJJJJJIJJJBJJBJBJBJBJIBBJIIBBBBBBBBBBBBIIIIIIABBBBBBBBBBBBJIIIIIBBBBBBBBBBBBBIIABBABABAAAAAAADAADADYADYADDYYYADDDYYYYADDDYYADDYADDYADYADYYADYADDDYYYYYYYYYDDbYDbDbDbDbbDbbbbYbbbbbbbbbbbbbrbbbbbbbbrbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbdbbbrbbrbbdbdrbdrbddddrrdddtrrdtrdtrdtdtrtrdtdtrdtrdtrrdtrrddtrddtrdtrdtrtrttttttttut1t1tu11tuuuuuuu2111uuu211uu211uuu2111111uuuuuuuuuuuuuuu2111uu21u2121212u22u22222222222222+222+22+22+22+22322322322322+22223222+2222+222+22232+2232323+233+++++++++3/+/+/+/3///3//////+///3///+//+/3/3//+/3////////////8/8n/8nn/88knnn88kn8kn8k8knknkn8k8k8knkn8k8kn8kn8kn88kn8kn8kn8kn8knknknk8kkknkkkkkkkkkkkkUkkUkkUkUkUkUkiUkUkiUkiUkUkiUkUkUkikikUkUkUkkikikikUkikiUkiUkiUUUUUUUUUiSUSUSSSSSSSSSSKSSSRSSRSSKSSSSKSSSSSSSSSSSSSSSKSSSRSRKSRKKKKKKKKRRJKRJRJRJRJJKJJKJJRJJJKJJRJJJKJJKJJKJRJJKJKJRJRJRJJKJRJJKJJRJJJJJRJJJBJJJJJIJJIJIJIJIBBJIBBJIIIBBBBBJIIIIIBBBJIIBJIIBJIIBJIBJIBBJIIBBBJIIIABBBIAIAAAAAAAAAYAYAYAYADYADYADDYADYAYADADADADAYAYAADADADYADYADDDDDDDbYYDbYbYbYbbYbbbYbbbbbbbbbYbbbbbbbbbbbbbbbbYbbbbbYbbbDbbbbbYbbbbbbbbbbbbbbbdbbdbrbdbdrrbddrrrrrdddtrrddtrrdtrrdddtrrrrrrrrrrrrrrrrrrddddtrdtrtrttttttuttu1t11tuu111111111111111111111tuuu11tuu1tuu111tuuuuuu211uu2u2121221222u222222223222223222+222232222+222222222222222+222222222+22232232323+233++++++33/+3/3/3//+/3//+/3/3/3/+/+3/+3/++3/+3/3/+/+//////8//8/8nn/88888knn88kn88kn8kn8kn8knn8knnn888knnnnn8888knnn88kn8k8k8k8kk8kkkkkkkkkkkUkkkikkikUkUkUkUkUkkikikUkkikkikkikkUkkkUkkkikkikUkkiUkUkiUUUkiiSUUiSUSUSSSSSSSSSSSSSSSiSSSSSSUSSiSSiSSSSSSSSSSSKSKSKKSRRRRRJKKRJKRJRJRJRJJKJRJRJJKJRJRJRJRJKJKRJKRJKRJRJKRJRJKJKJRJJJKJJJJJJJJJJIJJIJBJBJIJIBJIIBJIIBJIIBJIBJIBJIBJBJBJIJIJIJIJIBJBJIBBJIIBBBIIIAIABAAAADAAAYAADAYAYAYAYAYAAYAAAYAAAAAAAYAAAYAADADYYADDDDbYYDbYbYbDbbYbbbYbbbbYbbbbbDbbbbDbbbYbbYbbYbDbbYbDbbDbbDbbbbbYbbbrbbbbrbbdbdrbrrbddrrrrrrrrrddddddddddddrrrbddrrbdrrbddrrrrbdtrrrdtrttttttt1t1t1tu11tuuu111tuu11tuu1tutu1t1t1t1t1tu1tuu111111uu2121212212222u22222232222222222223221222222222122222u222222222+222+22323+23+++2/+++33/+3/+/+3/+/+33/+33/+++++3333333/++3/+3////////n/8n/8nnnnnn888knnn88knnnn888888nnnn/888nnnn/888knnn8knknknkknkkkkkkkkkkUkkkUkkUkkUkkUkkUkkkUkkkkkikkkkkkkkkkikkkkUkkkikUkikiiUUUUUUUiSUSUSiSSSSUSSSSUSSiSiSiSiSUiSiSUiSiSSSSSSSSKSKSRRKKKKRRJKKRJRJKJKRJRJKJKRJKJKKRJKKRRJKKKRRRJKKRJKRJKJKJRJJJJKJJJBJJJJIJBJBJBJBJIBJBJIBJBJIJIJIJBJJBJJBJJBJJBJJIJBJBJIBJIBBBBBIIAIAAAAAAAADAAYAAAAAAAAAAAAAABAAAAAAAAAAYAADYYADDDbYYDbYbYbDbbYbbYbbDbbbYbbYbDbbYbYbYDbDbYDbDbYbYbDbbYbbbYbbbbdbbbrbrbrbdrbdrrrbdddddrrrbddrrbdrbdrbrbdbdbdrbdrbdrrrrrrrrdttttttttututu1tu1tu1tu1t1t1tt1ttttutttuttutu11tuu211u21212122u2222222222222u2222222u222u22u22u22u222122222222222+22323+233+++++33/++33/++333/+++23333++2333+++++++++3////////8/8nn/888888888888888nn/88n/n/8n/n/8n/888nn88kn8knk8kkkknkkkkikkkkkikkkUkkkkkikkkkkkkkknkkkkkkkkkkkkkkkkikkikiUkiiiiiiSUiSiSiSSUSiSiSiSiiSUiiiSUUUUiiSUUiSSSSSSSSKSRKKKKKKRRJKKRJKRJKRJKKRRJKKKKKKKSRRRRRRRRRRJKKRJRJJKJJJJJJJJJBJJBJJIJIJIJIJBJBJJBJJJIJJJJJIJJJJJJIJJJIJBJBJBBJIIIIABABAIAAAAAAAAAAAAAAIAABABIAIAIAAAAAAAAADYADDDDbYDbYbYbYbYbDbbYbDbDbDbYDbYDDbYYDDbYYDbYDbDbDbbbYbbbbdbbbdbdbdrbdrrbdrrbdrbdrbdbdbdbrbbdbbdbrbbdrbrbddrrrrdtttttttt1ttu1t1ttuttttttttttttttttt1t1tu1111u21u2u22u2222122222u222212212u2u2u2u2121212u22u2222222322323+23333333333333333333+23+23+2323+23++23333/+//////n/n/88nnn/888nn/8n/8/n//n///n//8n/8nnnnn8k8k8kkk8kkkkkkUkkkkkkkkkkkkkkkknkk8kkknkk8kkkkkkkkkkikUkiUkiiiiSUiSUiSiSUiSUiiSUUUUkiiiUUUUUUUUUiSSSSSSKSRKKKKKKKKRRJKKRRRRRRRRRKSRKSRKSRKSRRRRJKKJKJRJJJJJJJJJIJJBJJIJJIJJIJJJJBJJJJRJJJJJJJJJJJJIJJIJIBJIIIIABIAAIAAAAAABAABABIABBIIIABBIABAAAAAAYADDDDDbYYbYDbDbDbDbYDbYDDbYYYYYYYYADbYYYDbYDbbDbbbbbrbbrbbdrbrbdrbdrbrbrbbdbbrbbbbbbdbbbrbbdbdrbdddtrtttttttuttutttttdttdttrdtdttttttutu1111uu2u22122122u222u2212u21u21uu211u21u212u222222222323+23+++++233333+23+23232+2232+223+23+++++//////n/8n/8nn/8n/n/////////////n/8nnnn8knknkkknkkkkkkkkkkkkkk8kk8k8k8k8k8k8kknkkkkkkkikUkiUUUUUiiSUiSUUiiiiiiUkiUkiUkiUkiiUUUiSSSSSRSRRKKKKRRRRRRRRRKSRSRSSRSSRSKSRRRRJKRJJKJJJJJJIJJJIJJJIJJJJJJJJJKJJRJJJRJJJJJJJJIJIJIIIIABIAABAABAIAIABBBBBBBBJIIIIIABAAAADADDDDDbYDbYDbDbYYDDDDDDYYADADDYYAbYYDbYbbbbbbbbrbrbrbrbrbrbrbbbbrbbbDbbbbbbbbdbbrbdrrrrdttttttttttttdtdtrddtrrddttttttu1111u2u2u2212212u2u2uu211111111111u2121222222323+23++2333+23+2+22+222223222+2+2+++++////n/n/n/8n/////3//+/+//////8nnnn8knkk8kkkkkkkk8kkknknkn88knn8kn8kknkkkkkikiUkiiiSUUiiiiiiiUkikikUkkikUkiUkiSUSSSRSRKKKKKKKSRRKSSSSSSSSSSRSRKKKKJKJJJJJJJJJJBJJJJJJJRJJRJRJRJKJRJJJJJJJIJIIIIIAIAIAABIABBBBJIBJIBJIBJIABAAAADDYYDDbYDbYYDDDDDADAYAAADADDDDbYbDbbbdbbrbrbrbbdbbbbbbbbbYbbDbbbbbbbdbddddtdttttttttdtrrrrrrbddddtttt1tuu21u2u2212u2u21111tu1tu11tu21u222222323+233+23+2+2222222222222232+23//////n/8/////3/++333/+///n/888k8kkk8kkkkk8kkn8knnnn/88knnknkkkkUkiUUUUUUUiiUUkUkkkikkkkkikUkiiSSSSRKSRRRRKSSSSSSUiSSSSSKKKKRJJJJJJJJJJJJJJJJKRJKKRRJKRJJJJJJBJIIABIAABIABJIIJIJJIJBJBJIIAADADYYDDbYDDDDDAAAAAAAAYADDbDbbbbrbbdbrbbrbbDbbYbYDbDbbbbbbrbdtrttrttttddddrbdbdrbddtttu11u21212u2uu2tu1ttttutuu2u2222323++23+2+2222u22u22222223+/////8////3/+233++++///888kknkkkk8kk88888/8n/888kknikUkiiiiiiiiUkkkkkk8kkkUkUUUSKSKKKKSRSSSUUiiiiSSSKKKJKJJJJIJJJJRJRRRRKKSJKRJJBJBBBIAIAIIIIJJJIJJJJJIBBAYADDbYYDDDAAABIAAAAAbYbbbbbrbrbbbbbDbYYYYDbYbbrbtrttttdtrrbrbbbrbrbtt1111212u2uuutrtttt1t2122323++23+22u2uu212122++///n////++2+223++//n8kknkkkk8kn/////nn8kkiUUUUUiikUnk8k8kkkkUSSSRRRRSSiiiUkUUSSKKJJJJJJIJKJSRSSKSJRBJBBABAIIIJJJJKJJJJAADYDbYDDAABBJIAAAbYbrbrbrbbbYADADDbbbdtttttdrbbYbbbrtt1212212ttrrrrtu122++++2322tuu1122+/n/8//3222223+/8kkkkkkk/+3///nkkiSUiSkk88nn8kUSRRRJSSikkkkiSRJJJBJJJRiSSSKJBBAJJIJBJIIIIABAAADADYYYYDbDbbbbbbbbrbdrrrrtttttu1111212u2223223++++////8nnn8k8kkkkUkUUUUSSSRKKKRJJJJJIBJAAAYYYYbbbbrbtt1t2u2+2//8kkUKCA";
        auto dirs = decom8(ds, 30505);
        array dr = {-1, -1, -1, 0, 0, 1, 1, 1},
                           dc = {-1, 0, 1, -1, 1, -1, 0, 1};
        int32_t r = 717, c = 48;
        vector grid(1000, string(1000, '.'));
        grid[r][c] = '#';
        for (auto d : dirs) {
            r += dr[d], c += dc[d];
            grid[r][c] = '#';
        }
        for (auto& row : grid) {
            cout << row << '\n';
        }
    }
    if (x == 9) {
        array dr = {-1, -1, -1, 0};
        array dc = {-1, 0, 1, -1};
        vector<int64_t> lines = {12509123913,88906361875,8009333864,86801461845,90108810832,90806121818,97001221791,97005641764,78505061764,93709561759,36307543755,81504281751,99209433747,79908561723,83604841708,76906741658,60608953652,88808430629,90904541627,94604501622,65008401612,26109573602,87502652585,87102741570,87208590568,90708101563,75310023559,87703321557,87401652551,74400241550,57803442529,65205173518,79505701514,15709383511,58801241506,65008161502,69402361487,66809370468,85608253466,98305381466,52704613462,82603822459,76301021457,57607343457,88206610454,84004912451,67610020447,209863443,86006041438,48604863437,58501981428,64307801426,99410023420,53908981419,70308150415,64900002413,51810020413,69504070408,94804741397,59210023397,69603261385,94706181372,46804540371,71705913370,88601661368,28308983347,75302312341,32503393340,53503330334,75201742333,29810023333,37100761330,12410023325,74603613324,57807561323,74803212323,46610023317,17603143315,16709213311,56606582307,50302882305,55600002304,37108241303,47806961302,43605843301,69708720301,92202993300,36103602298,86505852297,6402963297,57807082295,52203481294,81408520291,56103533285,67410020279,34402461279,25710023279,93506493279,92602661273,18206173271,70201202265,39807341264,42603281264,61907093264,87808321259,34808990258,32904042258,50806042250,96008453245,53907582245,22705373236,29200002234,96608370232,62106403231,5509333231,77203761229,55004522226,63006321225,99407472223,25802213222,93503792219,41001752217,77906590216,52602133214,4710023213,24502961208,42102043205,62908001203,35208220203,18805763203,85607010200,65406460199,14305593198,89107641196,29106392193,91708773190,58707461188,48301921187,42704230186,56305902183,76606061183,63504840183,29901823183,90801800181,56100261177,28310020176,98301740175,85301740175,23600961175,52510023173,72501860171,85804653171,23802473164,36906633163,45908402163,78605070160,28903182160,90707010158,19404081153,71008512152,29400002152,77410020151,45507290150,6310023149,44804850148,83209213147,72310020145,67106570143,70503650142,97208981141,87804300137,20509033137,88605521136,60910020136,45506042136,90402232133,69806533131,13106822131,13508103131,48009670129,64305810128,43204380127,47403873127,52610023125,22607361124,42506922120,49303141118,2705043117,14109883117,89401150116,32410023116,60400062114,40800722112,27804533109,76008942109,63001070108,38408073102,78101000101,51400002100,98404352095,22508010095,46700943095,80402842094,20106701093,70300890090,63005022089,97901890087,24010020087,75400833084,47308583081,77004280080,52102442079,55306462074,28808222074,58409232073,48901452073,90603970071,92110023069,82101801067,11002581065,11503981062,36210023060,98404052059,99606830059,68405463059,55804242058,99902310058,52609581057,32007601057,28100002056,46807293056,7500562055,86601300055,83708470055,94501350052,56509542049,48109441048,1305353048,29000450046,99500453046,7104322045,14902021044,83609901043,13203961043,26809133040,74806101039,42010023037,59300353036,62008601034,60609641033,24107050030,19301782030,68000293030,57705423029,64505130025,19710020025,17510023025,94106522023,80410020023,38105861023,4800193020,91905840019,67205010019,97505241019,65110023016,85705383016,71004021013,51304893012,97708932011,7606450010,95904110009,12804603007,83402103007,9905113006,19403702004,69803912003,31401993003,};
        vector grid(1003, string(1003, '.'));
        for (auto line : lines) {
            int len = line % 1000; line /= 1000;
            int d = line % 10; line /= 10;
            int c = line % 10000; line /= 10000;
            int r = line;
            for (int i = 0; i < len; i++) {
                grid[r][c] = '#';
                r += dr[d], c += dc[d];
            }
        }
        for (auto& line : grid) {
            cout << line << '\n';
        }
    }
    if (x == 10) {
        string prev = "0", cur= "0 1";
        cout << "a_i = a_{i-1} . a_{i-2}\n\na_1 = 0\n\na_2 = 0 1\n\n";
        for (int idx = 3; idx <= 15; idx++) {
            auto temp = cur + " " + prev;
            prev = std::move(cur), cur = std::move(temp);
            cout << "a_" << idx << " = ";
            auto len = cur.length();
            for (auto i = 0U; i < len; i++) {
                cout << cur[i];
                if ((i + 1) % 80 == 0 && i + 1 < len) {
                    cout << (idx > 9 ? "\n       " : "\n      ");
                }
            }
            cout << "\n\n";
        }
        cout << '\n';
        prev = "0", cur = "01";
        while (cur.length() < 70 * 70) {
            auto temp = cur + prev;
            prev = std::move(cur);
            cur = std::move(temp);
        }
        cout << "(A_i)^n = B_i (mod 2)\n\n";
        for (int i = 1; i <= 70; i++) {
            auto a = make(cur, i);
            auto b = power(a, FUCK);
            for (int j = 0; j < i; j++) {
                if (i / 2 == j) {
                    cout << "A_" << i << " = ";
                } else {
                    cout << (i > 9 ? "       " : "      ");
                }
                for (int k = 0; k < i; k++) {
                    cout << a[j].test(k) << " ";
                }
                cout << "  ";
                if (i / 2 == j) {
                    cout << "B_" << i << " = ";
                } else {
                    cout << (i > 9 ? "       " : "      ");
                }
                for (int k = 0; k < i; k++) {
                    cout << b[j].test(k) << (k != i - 1 ? " " : "");
                }
                cout << '\n';
            }
            cout << '\n';
        }
    }
}
