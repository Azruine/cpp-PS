#include <bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define pvi pair<vi, vi>
#define eb emplace_back
#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

ostream &operator<<(ostream &out, vector<int> &v)
{
    for (auto i : v) cout << i << " ";
    cout << "\n";
    return out;
}
vector<pvi> seedS = 
{
{{1,8,28,21,15,10,26,23,13,3,6,30,19,17,32,4,12,24,25,11,5,20,29,7,18,31,33,16,9,27,22,14,2,},{1,8,28,21,15,34,2,14,22,27,9,16,33,31,18,7,29,20,5,11,25,24,12,4,32,17,19,30,6,10,26,23,13,3,}},
{{1,3,13,23,26,10,6,19,30,34,15,21,28,8,17,32,4,12,24,25,11,5,20,29,35,14,22,27,9,16,33,31,18,7,2,},{1,8,17,32,4,5,11,25,24,12,13,36,28,21,15,34,30,19,6,10,26,23,2,14,35,29,20,16,33,31,18,7,9,27,22,3,}},
{{1,8,17,32,4,5,11,25,24,12,13,36,28,21,15,34,30,19,6,10,26,23,2,14,35,29,20,16,33,31,18,7,9,27,22,3,},{1,8,17,32,4,5,11,25,24,12,37,27,9,7,18,31,33,16,20,29,35,14,22,3,13,36,28,21,15,34,30,19,6,10,26,23,2,}},
{{1,3,22,14,35,29,20,5,11,38,26,23,13,36,28,8,17,32,4,21,15,34,30,19,6,10,39,25,24,12,37,27,9,16,33,31,18,7,2,},{1,8,17,32,4,5,11,38,26,23,2,14,35,29,20,16,33,31,18,7,9,40,24,25,39,10,6,19,30,34,15,21,28,36,13,12,37,27,22,3,}},
{{1,8,17,32,4,5,11,38,26,23,2,14,35,29,20,16,33,31,18,7,9,40,24,25,39,10,6,19,30,34,15,21,28,36,13,12,37,27,22,3,},{1,3,6,19,30,34,15,10,39,25,24,12,37,27,22,14,35,29,20,5,11,38,26,23,13,36,28,21,4,32,17,8,41,40,9,16,33,31,18,7,2,}},
};
string full = "";
string oddData = "";
vector<pvi> seed;
vector<char> oddFull;
map<int, pair<set<int>, set<int>>> overflow =
{
{1,{{585,629,639,679,719,727,746,748,768,780,781,787,796,801,804,810,812,818,824,825,829,830,834,862,868,883,886,913,944,945,947,950,953,963,966,972,974,979,986,1010,1013,},{639,645,677,686,727,774,780,783,786,792,814,815,818,819,827,862,874,875,876,880,883,884,911,937,941,946,947,955,956,958,959,965,967,970,971,986,}}},
{2,{{808,949,965,968,973,976,981,},{960,962,976,}}},
{3,{{814,820,911,953,964,969,971,},{826,912,970,980,}}},
{4,{{787,797,810,827,962,979,985,},{817,827,911,949,981,}}},
{5,{{646,682,807,940,951,},{815,946,965,}}},
{6,{{784,949,986,1012,},{809,943,967,1011,}}},
{7,{{643,670,872,965,},{723,818,940,941,947,955,966,980,983,}}},
{8,{{864,874,959,969,973,},{977,}}},
{9,{{770,836,878,963,},{732,807,814,880,1012,}}},
{10,{{938,947,},{772,822,865,911,953,}}},
{11,{{759,881,1012,},{658,962,}}},
{12,{{911,955,977,986,},{945,982,}}},
{13,{{868,880,882,939,982,},{}}},
{14,{{829,875,912,959,969,970,},{828,964,}}},
{15,{{721,785,805,825,965,1011,1013,},{781,879,968,969,975,977,}}},
{16,{{971,},{886,966,}}},
{17,{{827,862,944,969,},{697,875,}}},
{18,{{792,796,},{882,971,}}},
{19,{{775,911,947,1011,},{862,872,}}},
{20,{{744,910,981,},{670,876,}}},
{21,{{786,940,953,982,},{863,945,974,1010,}}},
{22,{{946,},{762,781,977,}}},
{23,{{799,878,973,},{864,910,950,952,}}},
{24,{{779,884,962,983,986,1010,},{821,965,970,}}},
{25,{{813,883,969,},{748,785,881,}}},
{26,{{970,},{956,}}},
{27,{{875,952,969,},{870,981,}}},
{28,{{742,798,820,912,978,985,1010,},{976,980,1013,}}},
{29,{{974,},{734,818,834,884,960,}}},
{30,{{952,959,980,},{879,953,}}},
{31,{{808,815,878,975,982,1011,},{947,954,963,}}},
{32,{{699,876,942,960,966,1013,},{912,}}},
{33,{{939,986,},{973,976,}}},
{34,{{807,862,940,985,},{965,1013,}}},
{35,{{766,965,1012,1013,},{880,976,}}},
{36,{{949,975,},{827,879,946,1013,}}},
{37,{{835,},{940,963,}}},
{38,{{943,},{836,872,965,967,970,}}},
{39,{{946,968,},{960,1011,}}},
{40,{{979,},{879,974,}}},
{41,{{834,981,},{834,973,975,}}},
{42,{{877,968,1011,},{815,865,976,981,}}},
{43,{{726,870,965,},{966,}}},
{44,{{817,879,},{826,}}},
{45,{{},{799,876,885,}}},
{46,{{861,863,978,},{968,}}},
{47,{{939,985,},{940,961,975,}}},
{48,{{957,},{1012,}}},
{49,{{910,942,962,973,977,979,},{948,}}},
{50,{{969,978,},{}}},
{51,{{780,},{827,835,949,}}},
{52,{{876,877,947,},{711,795,963,}}},
{53,{{},{945,1012,}}},
{54,{{954,},{984,}}},
{55,{{952,},{1013,}}},
{56,{{827,885,},{946,}}},
{57,{{790,947,},{860,}}},
{58,{{942,},{958,975,979,984,}}},
{59,{{946,963,981,},{1010,}}},
{60,{{863,},{874,878,}}},
{61,{{964,},{912,973,}}},
{62,{{910,981,},{871,979,1013,}}},
{63,{{965,},{}}},
{64,{{802,942,},{862,974,}}},
{65,{{},{964,}}},
{66,{{757,875,947,},{965,}}},
{67,{{883,},{}}},
{69,{{968,},{780,875,}}},
{70,{{979,},{1011,}}},
{72,{{961,},{912,952,}}},
{73,{{946,972,},{}}},
{74,{{},{980,}}},
{75,{{954,},{961,}}},
{76,{{971,},{775,986,}}},
{77,{{876,958,},{}}},
{78,{{813,},{}}},
{79,{{962,1010,},{911,}}},
{80,{{},{945,981,}}},
{81,{{},{910,}}},
{82,{{954,},{939,}}},
{83,{{},{983,}}},
{84,{{1010,},{939,952,}}},
{86,{{878,},{961,}}},
{87,{{984,},{964,}}},
{89,{{1011,},{}}},
{90,{{},{984,}}},
{92,{{},{872,}}},
{93,{{963,},{}}},
{94,{{954,},{}}},
{95,{{877,},{911,1013,}}},
{96,{{981,},{}}},
{97,{{},{960,984,}}},
{99,{{1012,},{967,}}},
{101,{{},{979,}}},
{102,{{1011,},{}}},
{103,{{972,},{}}},
{104,{{884,},{978,}}},
{105,{{815,979,},{986,}}},
{106,{{974,},{}}},
{107,{{1010,},{}}},
{109,{{},{1010,}}},
{111,{{939,},{}}},
{112,{{954,},{}}},
{116,{{941,},{}}},
{117,{{986,},{}}},
{121,{{962,978,983,},{}}},
{123,{{1011,},{}}},
{124,{{983,},{1011,}}},
{128,{{1013,},{}}},
{133,{{},{945,}}},
{134,{{},{952,}}},
{136,{{967,},{}}},
{137,{{},{939,}}},
{138,{{},{984,}}},
{142,{{},{965,}}},
{144,{{},{983,}}},
{172,{{1010,},{}}},
{177,{{},{981,}}},
{181,{{},{979,}}},
{211,{{},{958,}}},
};
const vector<pair<string, string>> recurS =
{
{{"18e79dku6:clt!fsmb!xp!j!v2!y!grna;5h4<!o!qwi3"},{"1!Y!g6!fsmb:clt79d!v!j3!i4<!o!qw!xanr!h5;!p8e!u!k2"}},
{{""},{""}},
{{"18e79dku6:cl!n!a3j!px!w!i4t!f!Y<!o!qh!rg!s!m!b;5!v2"},{"1lc!dhX!t45;bms!gr97!e8p!j!v2ku6:na!f!Y<!o!qwi3"}},
{{""},{""}},
{{"18e79dku6:cl!n!rv5hg!s!m!b2!jo<Yfi!qw4t!Xp;!a3"},{"18e79dk!oj!pX!t4<Yfi!qW!s!m;5!vr!h!g6!u3an!l!c:!b2"}},
{{"18e!A<l!t4i!wB!f7q!oy!g63j!vr!n:c!d9!px!h5;m!su!k2"},{"18e!A<l!t4i!wB!f!y!d9!px!h5;m!su!k27q!oj!vr!n:C!g63"}},
{{"18e79dku6g54<!oYfi3anr!hq:!bW!s!m;!pX!t!l!cvj2"},{"18e79d!cV!r6!u!k2!jb:!qhg54t!Xp;ms!W!i!f!Yo<l!n!a3"}},
{{"18e!A<l!t4i!wB!f!y!d9!px!h5;m!su!k27q!oj!vr!n:C!g63"},{"18e!A<l!t4i!wB!f7q!oy!g63j!vr!n:C!D9!px!h5;m!su!k2"}},
{{"18e79dk!oj2V!rg5h4t!Xp;mb:cl!n!a<Yfi!qW!su63"},{"18e79o!k!dU!qW!s!m;!pX!t4!h5!gr!Vcl!n!a<Yfi36:!bj2"}},
{{"18e!A<4t!lm!s5;!rg!yo!qw!iC9!px!hDk!u36:n7f!Bj!v2"},{"18!o9!px!hDk!us!m;54t!l!Ci!wq:6r!n!A<y!gE7f!B2v!j3"}},
{{"18p;54<anr9d!c!V!jb:6ghXe7!t!lms!Wq!U3!i!f!Yo!k2"},{"18p;54<!o9!r!n!a!T!lmb:6gYfiW!sU!qhXe72kd!c!V!j3"}},
{{"18E79!pi2v!jo!qwDk4t!l<yf!B!us!m;5h!xAn!rg!C:63"},{"18E!B!uDk4t!l<!s5h!xA!F!yo!qw!ip97!n:C!gr;m63j!v2"}},
{{"18p;54<lTanr!V!jo!k!d9!c:6gYfiW!s!m!b27!e!X!hq!U3"},{"18!d!W!i!f!Y!g6:c9o!kanr!V!j3U!qh45;bmS<lT!pXe72"}},
{{"18E79!pi!wq!oj!F!y<!s54t!lm63u!k!Dh!xA;B:n!rg!C!v2"},{"18E79!pi!wq!oj!F!y<!su!k2vC!Dh!xA;B:n!rG54t!lm63"}},
{{"18p;5hXe7q!US<4Tan!lmb:63jVc!d!W!i!f!Y!gr9o!k2"},{"18p!j!e!X!h5;!RgYfiWd!c!V2k!o97q!US<4Tan!lmb:63"}},
{{"18E79!pi2Bm!s5;!Ax!h!G6:n!rvCl!t4<yF!jo!qwDk!u3"},{"18p9!C:n7!E!xA;!rv!jo!qHG5s!m!BwDk!u36!F!y<l!t4i2"}},
{{"18p;mS!oYf!a!T!l<4i!qWdkUb:n!RVc972!j!e!X!h5!g63"},{"18p;!RVc97!e!X!h5!g63!i4Ta!f!Y<l!n:!QWdkUbmS!oj2"}},
{{"18p97q!oj3An!rGHxE!i!F!y<!su!k!D!wB:6!m;54t!l!C!v2"},{"18p97!E!xAn!r6:!B;5HGyFI!ml!t4<!su!k2vC!D!wq!oj3"}},
{{"18!d!WQ:6g5h4<lT!pXe!b!U!kanR;mS!oYfi3jVc972"},{"18!d!W!i!f!Yo!S!m;!R!n!a!T!l<4!h5!g6:!Q72kUb!e!XP9!c!V!j3"}},
{{"18p97q!oyF6:n!rGHxE!BwD!CI!m;!A!t45!l<!su!k2v!j3"},{"18p97q!oyFI3JvC!D!wB!E!x!H!Gr!n:6!m;!A!t45!l<!su!k2"}},
{{"18P!l<!S5hXe!b!U!k279oQ!m;!R!n:6gYf!a!T4iWd!c!V!j3"},{"18P!l<!S5hXejVc9O!k!d!W!i4Ta!f!Y!g63Ub:nR;m!Q72"}},
{{"18p97q!oyFI36:!BwD!C!v!J!E!x!H!Gr!n!A<l!t45;m!su!k2"},{"18!D!w!I!F!y!G!H5s!m;!rvCl!t4<An7q!o9!pxEJ2KuB:63"}},
{{"18P97Q:nR;!a!T!lmS<45hXe!b!U36gYfiWd!c!V!jO!k2"},{"18P97Q:N!jO!k2Vc!d!W!i!f!Y!g6R;!a!T!lmS<45hXe!b!U3"}},
{{"18p97q:6!F!y<A;5s!ml!t4IwD!C!v2!Jo!Kn!rGHxE!B!u3"},{"1!Kn!Jo8p97!E!x!H!Gr;!A!t!Lm!I45s<yF63uB:!qwD!C!v2"}},
{{"18P97Q:6!f!Y<!S!mlTa;54iWd!c!V2!jO!kN!RghXe!b!U3"},{"1!kN!jO8P97!e!X!h!gR;!a!T!lM!i45S<Yf63Ub:!QWd!c!V2"}},
{{"18p97!E!x!H!G63J!n:!qwD!C!vr;54I!m!B!us<LtA!F!yo!K2"},{"18p97q!M;!rGyF!A!t!L<!suB!E!x!H54IwD!C!v2K!oJ!n:63"}},
{{"18P97!e!X!hQ:N!j3UbM6!f!YO!k!d!W!i4<!S5!gR;!a!T!l!c!V2"},{"18P97!e!X!hQ:!b!US<L5!gR;M6!f!YO!k2Vc!d!W!i4TaN!j3"}},
{{"18p97q:6!F!y<!s!MLtAn!Jo!K2vC!D!w!I45;!rGHxE!B!u3"},{"18p97q:N!rGHxE!B!u36!F!y<!s!MLtA;54IwD!C!v!Jo!K2"}},
{{"18P97Q!Oj2kUb!e!X!h!g6:N!RVc!d!W!i!f!Y<4T!LM!S5;!a3"},{"18P97!e!Xa;5!g!hQ!OjVc!d!Wb:N!R63!i!f!Y<4T!LM!SU!K2"}},
{{"18p!L<!s5HxEJvC9o!K!D!w!I4tA!F!y!G63uB:Nr;M!q72"},{"18p!L<!s5HxE!B!u!K279Oq!M;!r!N:6GyF!A!t4IwD!C!v!J3"}},
{{"18P97Q!OYfi36!M;!aXejVc!d!Wb:N!Rg5h4T!L<!SU!K2"},{"18P97Q!OYf6!M;!aXeJ!V2K!US<L!T4!h5!gR!N:!bWd!ci3"}},
{{"18!D!w!I45;Ms<!OJ279!pxE!B!u!KN!rvCLtA!F!y!G!Hq:63"},{"18!D!w!I45;Ms<LtA!F!y!G!Hq:63uB!E!xP!JO!KN!rvC972"}},
{{"18P97Q!OJ!f!Y!gR!N:6!M;!a<!S5hXe!b2VcL!T4iWdK!U3"},{"18P97Q!OJ3U!Ka!f!Y!gR!N:6!M;5S<L!T4I!Wb!e!X!hd!c!V2"}},
{{"18P;!A!t!LMs<4IwDKuB!E!x!H5!Gr!N:!q!OyF63JvC972"},{"18P;!A!t!LMs<4IwDKu!Q!OyF6:N!rG5HxE!B279!C!v!J3"}},
{{"18P97Q!OJ36:N!RVc!dhg54T!L<YfI!Wb!e!Xa;M!SU!K2"},{"18e!bWd!c:N79!PI2K!US!M;!RV!JO!QH!Xa!f!Y<L!T45!g63"}},
{{"18P;5HxE79OQ!u!K!D!w!I4<!s!M!BJ2vCLtA!F!y!Gr!N:63"},{"18P!t!L!C!vR97!E!x!H5;Ms<4I36GyF!A!N:!BwDKu!Q!OJ2"}},
{{"18e79!PI2b:N!RVcL!T4<Yf!JO!QWdK!US!M;!aX!H5!g63"},{"18e79!PX!H5!L<4Ta!f!YO!QWdK!US!M;b:N!RV!J36G!cI2"}},
{{"18P;54<!su!QwDK!OyF!A!t!LMB:NR!v!J!E!x!H!G63!IC972"},{"18P!J!E!x!HDK!O9!CIw!Su!Q72v!R!N:!B!M;54<LtA!F!y!G63"}},
{{"18e79!PX!H54T!L<aN!RG!YO!QW!I!fS!M;b:63J!Vc!dU!K2"},{"18!OY!Ge79!PX!H5;b!FS!ML!T4<aN!R6:!QW!Ic!dU!K2V!J3"}},
{{"18P;54<yF6GHxEJv!R!N!A!t!LMS!w!IC!D9O!K27Q:!B!u3"},{"18P;54<yF6GHxEJv!R!N!A3uB:!Q7!T!LMS!w!IC!D9O!K2"}},
{{"18e79!PI2V!Jb!FS<4T!L!c:6!M;5H!XaN!RG!YO!QWdK!U3"},{"18E!a<!SF!bWdK!U3J!Vc9!PX!H5;!RG!YO!Q7!N:6!ML!T4I2"}},
{{"18E79D!C:N!L<4T!x!H5!GR!v!J36!F!yOQ!u!KA;!PIw!S!M!B2"},{"18E79D!C:N!L<!O!QHx!T45;!AKU6!F!y!GR!v2BMS!w!IP!J3"}},
{{"18E!a<L!T4I!Wb!F7Q!OY!G63J!VR!N:c!d9!PX!H5;M!SU!K2"},{"18E!a<L!T4I!Wb!F!Y!D9!PX!H5;M!SU!K27Q!OJ!VR!N:c!G63"}},
{{"18E79DKU6:!B2!JO<45HGyFI!Qw!S!M;!Px!T!L!Cv!R!N!A3"},{"18E79D!C:6RN!L<4T!xP;!A3UK!OJV5HGyFI!Qw!S!M!B2"}},
{{"18E!a<L!T4I!Wb!F!Y!D9!PX!H5;M!SU!K27Q!OJ!VR!N:c!G63"},{"18E!a<L!T4I!Wb!F7Q!OY!G63J!VR!N:C!D9!PX!H5;M!SU!K2"}},
{{"18E79DKU6:CLT!xP;5!V!J3!I4!H!GRNA!F!y<!O!Qw!S!M!B2"},{"18!S!M!B2KU6:CLT79D!V!J!E!xP;54!H!GRNA!F!y<!O!QWI3"}},
{{""},{""}},
{{"18E79DKU6:CL!N!RG!S!M!BJ2V5;!PIW4T!x!HQO<yF!A3"},{"18E79DKU6:CL!N!RG!S!M!BJ!PIW4T!F!y<!O!QHX3A;5!V2"}},
{{""},{""}},
{{"18E79DKU6:CL!N!A3J!PX!W!I4T!F!y<!O!QH!RG!S!M!B;5!V2"},{"18E79DKU6:CL!N!RG!S!M!BW!X!HQO<Y2VJ!PIF!T45;!A3"}},
};
const vector<pair<string, string>> recur =
{
{{"18ebx!udcw!vrh!l<y!t4!o9!j!pi!k2!q7f!n:6g!m;5s!a3"},{"18e!o!kn!f!t45s!ax!u36g!m;!Y<l79!j!pi:cdv!wb!r!hq2"}},
{{"18e6:c45;bh97flrgmsy!a<!kntiodj!px!u3!qw!v2"},{"18e6:cio!knt!y!A<45!s!m!g!r!l!f79!h!b;!j!du!xp2v!wq3"}},
{{"18eb!r6g!m;!h5s!axw!vc!q7!l<Y!u3j9d!pi:n!f!t4!o!k2"},{"18eu!Y<l72ko4tf!n:!ipj9dc!qw!vr!b;!h5s!aXm!g63"}},
{{"18e6:c45;bh9dj!piou7f!t!n!y!Axms!g!r!l<!k2v!wq3"},{"18e6:c45;B!f7!u!o!i!t!n!y!A3!qw9!hdj!pxms!g!r!l<!k!v2"}},
{{"18ebX:cw!vrh;5sg<aY!ud!pi!k2!q79!jo4tf!n!lm63"},{"1!a36!m!X!b!eg<ln!f!t4!oj97qi:cW!s5;!h!rvY!ud!p8!k2"}},
{{"18e6:c45;Bxms!gr!hd!v!p!j!u3!qw97!f!A!l<yntio!k2"},{"18e6:CwlAf!t!n!y<!k279d!v!p!j!u!o!i45;Bxms!gr!hq3"}},
{{"18ebX:6g!m;!h!rvdc!qW9!jo4tfa!s5!nk!ip3u!Y<l72"},{"1W9!jo4tfa!s5!nk!icdV8eu!Y<l72!qhr!b;m!g6:!Xp3"}},
{{"18e6:Cd54<Ay;Bxms!g!r!l!f79!w!qhntio!k!v2!p!j!u3"},{"18e6:C!g!r!l<Ay;Bxms54io!k!v!D9!w!qhnt!f7!u3jp2"}},
{{"18ebX:6g!m;5s!W!cV!r!hq279ok!i4tf!n!l<aY!ud!p!j3"},{"18ebX:6g!m;5s!W!ci!k!o97!l<4tf!n!Y!a3jp!dU!qhr!V2"}},
{{"18e6:CDvk<45;Bx!u!o!i!t!n!y!s!m!g!r!l!w!qh97!f!A3jp2"},{"18E!i45;Bx!u!o9!hqwlrgmsynt6:CDvk<Af72!p!j3"}},
{{"18ebX:63a!s54tf!n!Y<l79!W!ci!k!ojp!dU!qh;m!gr!V2"},{"18ebX:n!f!a<Y;m!g!s54T6r!V279d!p!jok!icWl!hq!U3"}},
{{"18EBx:6gms54t!f72!pi!qh!rv!w!C!D9o!kn!l<Ay;!j!u3"},{"18EBx:!i45;msh!rv!w!q7Ft!y!A<l!nk!o9DC!g63ujp2"}},
{{"18ebX:6g!m;54T!Y!a<ln!fs!W!cV!r!hq27!Ud!pi!k!o9!j3"},{"1!a<l7f!n!Y!S54Ti:!X!b;m!g63j9!W!cV!r!hq!Ud!p8e!o!k2"}},
{{"18EBx:63AFti!q79!h54<lrg!s!m;!yo!knCw!v!Dujp2"},{"18EBx:nCDv!w!q79!h5!s!m;!y<lr4ioujp2k!G6!t!F!A3"}},
{{"18ebX:63afTi!kn54<Y;!hd!p!j!US!o9!W!cV!rg!ml7q2"},{"18!VcW9o4!R!hd!p!j!US5;!Y<af!n:!X!b!eTi!k2!q7!lm!g63"}},
{{"18EBx:6G<45;msyn!l!w!C!Dujp279o!k!vr!hq!i!t!F!A3"},{"18EBx:63AFti!qHrG<45;msyn!l!w!C!Dujpvk!o972"}},
{{"18ebX:6g!m;54<afT!pi!k!V2!qhR!n!Yo!SU7!l!W!c!d9!j3"},{"18ebX:6g!m;54!R!hQ3jp!T!f!a<Ynl7!US!o9dV!W!ci!k2"}},
{{"18EBx:63Ay!t4<!G!rv!w!C!Duj!F79o!kn!lms5;!Hq!ip2"},{"18EBx!us5;!HqF!jo!kn!lm!Ip279Dv!w!C:6rG<4t!y!A3"}},
{{"18ebX:63afTiQ!m;54!o!k!VcW9d!p!j!UShRg<Ynl72"},{"1l72!P!j!UShR!nko45;m!Q!icW9dV8ebX:6g<Y!T!f!a3"}},
{{"18EBx:6G<4!rv!w!C!Dujp279o!kAyn!lm!I!t!Fs5;!Hq3"},{"18!v!px:63!q!I!t!Fs54<!G!r!l!w!C!DH;mBEuJ!n!y!Ak!o972"}},
{{"18ebX:6g<45;m!QhR!n!Yo!SUjP!l!W!c!d972Vk!i!T!f!a3"},{"18ebX:!i4<!g6!T!f!a3UjP!l!W!c!d97Q!m;5ShR!n!YO!k!V2"}},
{{"18EBx:63AFt!youJ97qw!v!D!C!nk<45;!H!s!G!r!lm!Ip2"},{"18!K2!pI!m!x!B!EGsH;54!r!l<AFt!youJ97qw!v!D!C!n:63"}},
{{"18ebX:63afTiQ!m;54<Yn!RgSh!l!W!c!dUjPVk!O972"},{"18!k!V279OdcWl!h5;m!Q!iPebX:6!T!f!a<4!RgSYN!j!U3"}},
{{"18EBx:6G<4!rv!w!C!D972!pI!mlAFt!yo!Kn!J!us5;!Hq3"},{"18EBx:6!t!F!A3!qH;!yo!Kn!J!us54<!G!rv!w!C!D97!Lm!Ip2"}},
{{"18ebX:6g<4!RV!W!c!d9OUj!Nk!iP27!lm!Qh;5SY!T!f!a3"},{"18ebX:cdV!W!Qh;54<!g!R63afT!Y!S!Ml79OUj!Nk!iP2"}},
{{"18EBx:63AFtI!KnCDv!w!qHrG<45;!y!s!mL79ouJp2"},{"18EBx:6rG<45sy;!Hq!ML72!p!J!u!o9Dv!w!C!nK!I!t!F!A3"}},
{{"18ebX:63afTi!kNcdV!W!QhRg<45;!Y!S!Ml79OUjP2"},{"1!a!f!Q!i!T!N:!X!b!e8!k279OUjPV!W!c!dh!LMSY;54<!g!R63"}},
{{"18EBx:6G<4!rvKou72!pIq!MLnt!y!A!Fs5;!HDCw9!J3"},{"18EBx:6rG<4t!y!A3J9!w!C!DH;5!sF!N!LM!q!IpvKou72"}},
{{"18ebX:6g<4!RV!W!c!d9O!kaYN!LM!i!T!f72!P!j!US5;!hQ3"},{"18ebX:63!Q!KaYN!LM!i!T!f79OdcW!VRg<45;!h!SUjP2"}},
{{"18EBx:63AFtIq!M;54<yN!rGsH!L!w!C!DuJpvK!o972"},{"18!K!v279O45;M6:!x!B!E!p!J!uDCwL!H!s!Gr!N!y<AFtIq3"}},
{{"18ebX:63afT!YOUj97QW!V!d!c!NK<45;!h!S!g!R!LM!iP2"},{"18ebXM!i45;!h!S!g!R!L<aY!T!f79OUJP2KQW!V!d!c!N:63"}},
{{"18EBx:6G<45;M!qHr!N!L!w!CI!K!v!D972!p!J!us!Oy!t!F!A3"},{"18EBx:6G<4!Oy!t!F!A3!P!J!us5;M!qHr!N!L!w!CI!K!v!D972"}},
{{"18ebX:6g<4!RVK!O9!W!c!dh;5!SUJP27QfTi!ML!N!Y!a3"},{"18ebX:6g<4!RVK!O!I!T!f!Q79!W!c!dh;5!S!ML!N!Y!a3UJP2"}},
{{"18EBx:63AFtIq!M;54!rG<yNL!HD!P!J!us!O!K!vCw972"},{"18EBx:6!M;54!rG<yNL!HD!P!J!us!O!K!vCw972!Q!I!t!F!A3"}},
{{"18ebX:63afTI!Q79dVK<!gR45;MSh!L!W!c!N!YOUJP2"},{"18ebX:6!T45;MSH!Rg<L!N!Y!a!f79dV!W!cIOUJP2KQ3"}},
{{"18EBx:6G!M;54<LN!r!HDCw!v2KO!su!Q!IPJ97Ft!y!A3"},{"1!R!H54<L79!J3AF!NK8P!D!CI:!x!B!Et6G!M;!yO!su!Qw!v2"}},
{{"18ebX:6g<45;MSH!RVKQ!I!T!f72!P!J!U!O9dcWL!N!Y!a3"},{"18ebX:!I!T!f7QWL!N!Y!a36RG!cVK<45;MSH!d9OUJP2"}},
{{"18EBx:63AFtI!KN54<L!HD!P!J!us!Oy;M!GR!vCw97Q2"},{"18EBx:6!t!F7Q2K!IP!DH!L<4!OyN5;M!GR!vCw9!J!uS!A3"}},
{{"18ebX:63aY;54<LRGMSH9dV!W!c!NKQ!I!T!f7!U!OJP2"},{"18eb!F7!U!OJP2V!W!Q!KNTI:6G!c!d9!H!S!M!X!R!L<45;!Y!a3"}},
{{"18EBx:6G!M;54tI!K!O9D!P!J!uS!w!Cv!R!HQ27!L<yN!F!A3"},{"18EBx:!I!QHR!vCw9D!P!J!u36G!M;5S!AKO4TF!N!y<L72"}},
{{"18ebX:6GMS54T!F72!PI!QH!R!L<!KNcW!V!d9OUJ;!Y!a3"},{"18EK<LR!HQF!T45!S!M!G63aY;!JbX:NcW!V!d97!U!O!IP2"}},
{{"18EBx:63AyN!F!T4<L7!uSG!M;5HR!vCD!PI!K!OJ9!wQ2"},{"18E!O!K2!QwLN!F79!JBx!T4<Ay!USG!M;5HR!vCD!PI:63"}},
{{"18E6:cdVK<45;bX!U!O9!WQ!IP!J3aY!T!N!H!S!M!G!R!L!F72"},{"18E6:cDJ;54<!K!V!PI!QW9OU!X!b27FLRGMSHNT!Y!a3"}},
{{"18EBx:6!M;!H5S!wQ!Cv!RG<LN!F!T4!OJ972K!IP!DU!y!A3"},{"1!A36!M;!H!RG<LN!F!T45S!wBx:!IP!DU!y!VC!Q79!JO!E8!K2"}},
{{"18E6:cD54<aYNTI!QWLRGMSH97F!b;!JO!K!V2!PX!U3"},{"1WLRG8E6:C4<aYNTIOD5;MSH97F!bJ!PX!U3!Q!K!V2"}},
{{"18EBx:63U!y<A!S5;!H!RG!MLN!F!T4!OJP!D!VCw97QI!K2"},{"18!K2VD!PI:6RH;5S!A<LN!F!T4!Oy!U!EG!M!x!BWC!Q79!J3"}},
{{"18E6:C45;bXMS!GR!HD!V!P!J!U3!QW97!F!a!L<YNTIO!K2"},{"18E6:C45;B!X!RG!S!MLaF72K<YNTIOUJPV!DH9!WQ3"}},
{{"18EB!R6:CWx!T45H;M!G!SU!y!A<LN!F7Q2VD!PI!K!O9!J3"},{"18!K!O9!J36R!B!ETF!N:!I45H;M!G!SU!y!A<L7Q!C!W!XP!D!V2"}},
{{"18E6:C45;MB!X!RG!SU7!F!a!L<Y!T!N!HQW9D!V2K!O!IP!J3"},{"18E6:C45;MBHNT!Y<LA!D9!W!Q7!FS!GRX!U3J!PIO!K!V2"}},
{{"18EBX!U36:N5SG!M;!y!A!F!T4<L!H!RV!WQ!CI!K!OJP!D972"},{"18EB!R6:!IC!QW!V!DU!XPJ972KO4<LN5H;M!G!SFT!Y!A3"}},
};
string de(const string &en)
{
    string de;
    int l = en.length();
    for (int i = 0; i < l;)
    {
        unsigned char c = en[i];
        if (c < 0x80) de += en[i++];
        else
        {
            int k = ((c & 0x1F) << 6) | (en[i + 1] & 0x3F);
            int cn = 130 - en[i + 2];
            while (cn--) de += k - 128;
            i += 3;
        }
    }
    return de;
}
void cvod()
{
    uint32_t v = 0;
    int cnt = 0, index = 0;
    for (char c : oddData)
    {
        if (c == 'z' && cnt == 0)
        {
            int p = 4;
            while (p--) oddFull.eb(0);
        }
        else
        {
            v = (v * 85) + (uint32_t(c) - 33);
            cnt++;
            if (cnt == 5)
            {
                for (int i = 0; i < 32; ++i) oddFull.eb((v >> (31 - i)) & 1);
                v = 0;
                cnt = 0;
            }
        }
    }
    oddData = "";
}
inline int toi(char c) { return 126 - c; };
inline bool isSquare(int n) { return ceil(sqrt(n)) == floor(sqrt(n)); };
inline pair<int, int> decompose(int n)
{
    int a = n / 25, b = n % 25;
    return ((b < 12) ? make_pair(a - 1, b + 25) : make_pair(a, b));
}
void T(vi &ans, const vi &s, int c, bool r, int dep, stringstream &ss)
{
    int l = s.size();
    int start = r ? (l - 1) : 0;
    int end = r ? -1 : l;
    int sign = r ? (l % 2 ? 1 : -1) : 1;
    for (int i = start; i != end; i += (r ? -1 : 1))
    {
        int value = 25 * s[i] + c * sign;
        int len = to_string(value).length();
        if (dep > 0) ans.eb(value);
        else ss << value << " ";
        sign *= -1;
    }
}
void prog(vi &ans, vi &S, vi &L, string &s, int dep, stringstream &ss)
{
    int l = s.size();
    for (int i = 0; i < l; i++)
    {
        char c = s[i];
        if (c >= '0' && c <= '<')
        {
            int len = to_string(int(c - '0')).length();
            if (dep > 0) ans.eb(c - '0');
            else ss << c - '0' << " ";
            continue;
        }
        string t = "";
        if (c == '!') t = "R", c = s[++i];
        if (c >= 'a' && c <= 'y') t += 'S' + to_string(c - 109);
        else if (c >= 'A' && c <= 'Y') t += 'L' + to_string(c - 77);
        if (t[0] == 'R') T(ans, (t[1] == 'S') ? S : L, stoi(t.substr(2)), true, dep, ss);
        else T(ans, (t[0] == 'S') ? S : L, stoi(t.substr(1)), false, dep, ss);
    }
}
pvi expd(vi &S, vi &L, int n, int dep, stringstream &ss, bool o = false)
{
    int a, b;
    vi ans1, ans2;
    string s, l;
    ans1.reserve(n), ans2.reserve(n + 1);
    tie(a, b) = decompose(n);
    auto it = recur[(b - 12) * 2 + ((a + 1) % 2)];
    if (a < 41) it = recurS[(b - 12) * 2 + ((a + 1) % 2)];
    tie(s, l) = it;
    prog(ans1, S, L, s, dep, ss);
    if (dep == 0) return {{}, {}};
    prog(ans2, S, L, l, dep, ss);
    if (o)
    {
        vi a1, a2;
        for (int i = 2; i < ans1.size(); i += 2) a1.eb(ans1[i]);
        for (int i = 2; i < ans2.size(); i += 2) a2.eb(ans2[i]);
        return {a1, a2};
    }
    return {ans1, ans2};
}
void cand(vi &a, int n, int m, vector<char> &odd, vector<char> &used, vector<vi> &total, int se)
{
    a.reserve(200);
    vi &nTotal = total[n];
    int len = nTotal.size();
    for (int i = 0; i < len; i++)
    {
        int j = nTotal[i];
        if (j > m + se) break;
        if (odd[j] || used[j] || n == j) continue;
        vi &jTotal = total[j];
        int lens = jTotal.size();
        for (int k = 0; k < lens; k++)
        {
            int l = jTotal[k];
            if (l > m + se) break;
            if (!odd[l] || used[l] || n == l || j == l) continue;
            a.eb(l);
        }
    }
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
}
void da()
{
    string dd = de(full);
    seed.reserve(1000);
    vector<vi> total(1038);
    for (int i = 1; i <= 1037; i++)
    {
        total[i].reserve(50);
        int lb = ceil(sqrt(i + 1)), ub = floor(sqrt(i + 1037));
        for (int j = lb; j <= ub; j++)
        {
            int k = j * j - i;
            if (i == k || i + k == 4) continue;
            total[i].eb(k);
        }
    }
    int index = 41, c = 0, iodd = 0;
    stringstream ss;
    while (index < 1037)
    {
        vi ans1, ans2, v1, v2;
        if ((index >= 837 && index <= 859) || (index >= 887 && index <= 909) || (index >= 914 && index <= 936) || (index >= 987 && index <= 1009) || (index >= 1014 && index <= 1036))
        {
            int k = (((index - 12) / 25 - 33) + 1) / 2;
            seed.eb(expd(seedS[k].first, seedS[k].second, index, 1, ss, 1));
            index++;
            continue;
        }
        vector<char> odd(index + 2);
        odd[1] = 1, odd[2] = 0, odd[3] = 1;
        if (!(index % 2)) odd[index + 1] = 1;
        for (int i = 4; i <= index; i++) oddFull[i - 4 + iodd] ? odd[i] = 1 : odd[i] = 0;
        iodd += index - 3;
        pair<int, int> p = {1, 1};
        vector<char> used1(index + 1), used2(index + 2);
        used1[1] = 1, used2[1] = 1;
        string_view sv(dd.c_str() + c, ((index - 1) / 2 - 1) * 2 - 1);
        c += ((index - 1) / 2 - 1) * 2;
        for (int i = 0; i < (index - 1) / 2 - 1; i++)
        {
            ans1.reserve(index / 2), ans2.reserve(index / 2);
            int a, b;
            tie(a, b) = p;
            cand(v1, a, index, odd, used1, total, 0), cand(v2, b, index, odd, used2, total, 1);
            int aindex = toi(sv[i * 2]), bindex = toi(sv[i * 2 + 1]);
            if (overflow[i + 1].first.find(index) != overflow[i + 1].first.end()) aindex += 95;
            if (overflow[i + 1].second.find(index) != overflow[i + 1].second.end()) bindex += 95;
            a = v1[aindex], b = v2[bindex];
            used1[a] = 1, used2[b] = 1;
            ans1.eb(a), ans2.eb(b);
            p = {a, b};
            vi().swap(v1), vi().swap(v2);
        }
        if (index % 2)
        {
            ans1.eb(3);
            for (int i = 4; i <= index; i++)
            {
                if (!used2[i] && odd[i])
                {
                    ans2.eb(i);
                    break;
                }
            }
        }
        else
        {
            for (int i = 4; i <= index; i++)
            {
                if (!used1[i] && odd[i])
                {
                    ans1.eb(i);
                    break;
                }
            }
            for (int i = 4; i <= index + 1; i++)
            {
                if (!used2[i] && odd[i])
                {
                    ans2.eb(i);
                    break;
                }
            }
            ans2.eb(3);
        }
        seed.eb(make_pair(ans1, ans2));
        index++;
    }
    full = "";
}
bool fill(vector<char> &vis, vi &ans, int n, int index)
{
    vector<vi> WTF(n);
    for (int index = 1; index < n; index += 2)
    {
        if (ans[index] != 0) break;
        int a = ans[index - 1];
        int b = ans[index + 1];
        if (a < b) swap(a, b);
        int lowerBound = ceil(sqrt(a + 1));
        int upperBound = floor(sqrt(a + n));
        for (int i = upperBound; i >= lowerBound; i--)
        {
            int temp = i * i - a;
            if (vis[temp]) continue;
            if (isSquare(temp + b) && temp <= n) WTF[index].eb(temp);
        }
    }
    while (true)
    {
        bool isOne = false;
        int minDegree = INT_MAX;
        while (true)
        {
            isOne = false;
            minDegree = INT_MAX;
            for (int i = 1; i < n; i += 2)
            {
                int a = WTF[i].size();
                if (a == 0) continue;
                if (a == 1)
                {
                    isOne = true;
                    ans[i] = WTF[i][0];
                    vis[WTF[i][0]] = 1;
                    WTF[i].clear();
                }
                else minDegree = min(minDegree, a);
            }
            for (int i = 1; i < WTF.size(); i += 2)
                if (WTF[i].size() != 0) WTF[i].erase(remove_if(WTF[i].begin(), WTF[i].end(), [&vis](const int &num) -> bool { return vis[num] == 1; }), WTF[i].end());
            if (minDegree != INT_MAX && !isOne) break;
            if (minDegree == INT_MAX)
            {
                for (auto i : vis) if (!i) break;
                return true;
            }
        }
        unordered_map<int, int> count;
        while (true)
        {
            bool flag = true;
            count.clear();
            for (auto i : WTF)
            {
                if (i.size() == 0) continue;
                for (auto j : i) count[j]++;
            }
            for (auto i : count)
            {
                if (i.second == 1)
                {
                    for (int j = 0; j < WTF.size(); j++)
                    {
                        if (WTF[j].size() == 0) continue;
                        auto it = find(WTF[j].begin(), WTF[j].end(), i.first);
                        if (it != WTF[j].end())
                        {
                            ans[j] = i.first;
                            vis[i.first] = 1;
                            WTF[j].clear();
                            break;
                        }
                    }
                    flag = false;
                }
            }
            if (flag) break;
        }
        while (true)
        {
            auto it = find(ans.begin(), ans.end(), 0);
            if (it == ans.end()) break;
            int index = it - ans.begin();
            for (auto i : WTF[index])
            {
                if (vis[i]) continue;
                else
                {
                    ans[index] = i;
                    vis[i] = 1;
                    WTF[index].clear();
                    break;
                }
            }
        }
        ans[0] = 1;
        return true;
    }
}
vi recon(vi odd, int n)
{
    vector<char> vis(n + 1, 0);
    vi ans(n);
    ans[0] = 1;
    for (int i = 2; i < n; i += 2) ans[i] = odd[(i - 1) / 2];
    vis[0] = 1, vis[1] = 1;
    for (int i = 0; i < n; i += 2) vis[ans[i]] = 1;
    if (n % 2 == 0)
    {
        ans[n - 1] = 2;
        vis[2] = 1;
    }
    fill(vis, ans, n, 1);
    return ans;
}
pvi seqGen(int a, int b, int dep, stringstream &ss)
{
    int n = 25 * a + b;
    if (n > 40 && n < 1037)
    {
        if (dep == 0)
        {
            vi temp = recon(seed[n - 41].first, n);
            for (auto i : temp) ss << i << " ";
            return {{}, {}};
        }
        else return {recon(seed[n - 41].first, n), recon(seed[n - 41].second, n + 1)};
    }
    vi S, L;
    if (a < 1037)
    {
        S = recon(seed[a - 41].first, a), L = recon(seed[a - 41].second, a + 1);
        return expd(S, L, n, dep, ss);
    }
    else
    {
        int aSub, bSub;
        tie(aSub, bSub) = decompose(a);
        tie(S, L) = seqGen(aSub, bSub, dep + 1, ss);
        return expd(S, L, n, dep, ss);
    }
}
bool input(int n)
{
    if (n >= 41) return true;
    if ((n >= 2 && n <= 14) || (n >= 18 && n <= 22) || n == 24) cout << "-1\n";
    string s = "8 1 15 10 6 3 13 12 4 5 11 14 2 7 9 ";
    if (n == 15) cout << s << "\n";
    if (n == 16) cout << s << "16\n";
    if (n == 17) cout << "17 " << s << "16\n";
    if (n == 23) cout << "2 23 13 12 4 21 15 10 6 19 17 8 1 3 22 14 11 5 20 16 9 7 18\n";
    if (n == 25) cout << "18 7 9 16 20 5 4 21 15 10 6 19 17 8 1 3 22 14 2 23 13 12 24 25 11\n";
    s = "18 7 9 16 20 5 11 25 24 1 8 17 19 6 3 13 12 4 21 15 10 26 23 2 14 22 ";
    if (n == 26) cout << s << "\n";
    if (n == 27) cout << s << "27\n";
    if (n == 28) cout << "18 7 2 14 11 25 24 12 4 5 20 16 9 27 22 3 13 23 26 10 6 19 17 8 1 15 21 28\n";
    s = "18 7 29 20 16 9 27 22 14 2 23 26 10 15 1 3 13 12 24 25 11 5 4 21 28 8 17 19 6 ";
    if (n == 29) cout << s << "\n";
    if (n == 30) cout << s << "30\n";
    s = "1 15 21 28 8 17 19 30 6 10 26 23 2 14 11 25 24 12 13 3 22 27 9 16 20 29 7 18 31 5 4 ";
    if (n == 31) cout << s << "\n";
    if (n == 32) cout << s << "32\n";
    if (n == 33) cout << seedS[0].first;
    if (n == 34) cout << seedS[0].second;
    if (n == 35) cout << seedS[1].first;
    if (n == 36) cout << seedS[1].second;
    if (n == 37) cout << seedS[2].second;
    if (n == 38) cout << "1 35 29 20 5 31 18 7 9 16 33 3 6 10 15 21 4 32 17 19 30 34 2 14 22 27 37 12 24 25 11 38 26 23 13 36 28 8\n";
    if (n == 39) cout << seedS[3].first;
    if (n == 40) cout << seedS[3].second;
    return false;
}
int main()
{
    fastio;
    cvod();
    da();
    int t, n;
    cin >> t;
    while (t--)
    {
        cin >> n;
        if (!input(n))
            continue;
        int a, b;
        tie(a, b) = decompose(n);
        stringstream ss;
        seqGen(a, b, 0, ss);
        cout << ss.str() << "\n";
    }
}