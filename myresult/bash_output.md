```bash
(base) majx@mlsys-Rack-Server:~$ cd PrIDE/security/
(base) majx@mlsys-Rack-Server:~/PrIDE/security$ ./run_security_analysis.sh
echo "Compiling Analytical Model"; cd analytical; make; ./loss_probability_analytical > output/output.txt; cat output/output.txt; cd -
Compiling Analytical Model
make[1]: Entering directory '/data/home/majx/PrIDE/security/0_loss_probability/analytical'
g++ -o loss_probability_analytical loss_probability_analytical.cpp
make[1]: Leaving directory '/data/home/majx/PrIDE/security/0_loss_probability/analytical'

***********Printing Table-III***********

***** LossProbability for Window-Size: 79 ******
Capacity: 1     LossProb: 0.6298         TRH*(TIF+TRF):  8287 
Capacity: 2     LossProb: 0.3048         TRH*(TIF+TRF):  4404 
Capacity: 4     LossProb: 0.1192         TRH*(TIF+TRF):  3472 
Capacity: 8     LossProb: 0.0601         TRH*(TIF+TRF):  3252 
Capacity: 16    LossProb: 0.0304         TRH*(TIF+TRF):  3152 

/data/home/majx/PrIDE/security/0_loss_probability
echo ""

echo "Compiling Monte Carlo Model"; cd monte_carlo; make;  ./sim > output/output.txt; cat output/output.txt; cd -
Compiling Monte Carlo Model
make[1]: Entering directory '/data/home/majx/PrIDE/security/0_loss_probability/monte_carlo'
g++ -lz -O3 -lm  -W -Wall -Wno-deprecated -Wno-unused-parameter -Wno-unused-but-set-variable tracker.cpp sim.cpp  -o ./sim
In file included from tracker.h:5,
                 from tracker.cpp:4:
mtrand.h: In member function ‘void MTRand::initialize(uint32)’:
mtrand.h:173:26: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  173 |         register uint32 *s = state;
      |                          ^
mtrand.h:174:26: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  174 |         register uint32 *r = state;
      |                          ^
mtrand.h:175:22: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  175 |         register int i = 1;
      |                      ^
mtrand.h: In member function ‘void MTRand::reload()’:
mtrand.h:189:26: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  189 |         register uint32 *p = state;
      |                          ^
mtrand.h:190:22: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  190 |         register int i;
      |                      ^
mtrand.h: In member function ‘void MTRand::seed(uint32*, uint32)’:
mtrand.h:216:22: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  216 |         register int i = 1;
      |                      ^
mtrand.h:217:25: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  217 |         register uint32 j = 0;
      |                         ^
mtrand.h:218:43: warning: enumerated and non-enumerated type in conditional expression [-Wextra]
  218 |         register int k = ( N > seedLength ? N : seedLength );
      |                            ~~~~~~~~~~~~~~~^~~~~~~~~~~~~~~~
mtrand.h:218:22: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  218 |         register int k = ( N > seedLength ? N : seedLength );
      |                      ^
mtrand.h: In member function ‘void MTRand::seed()’:
mtrand.h:252:34: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  252 |                 register uint32 *s = bigSeed;
      |                                  ^
mtrand.h:253:30: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  253 |                 register int i = N;
      |                              ^
mtrand.h:254:31: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  254 |                 register bool success = true;
      |                               ^~~~~~~
mtrand.h: In copy constructor ‘MTRand::MTRand(const MTRand&)’:
mtrand.h:276:32: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  276 |         register const uint32 *t = o.state;
      |                                ^
mtrand.h:277:26: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  277 |         register uint32 *s = state;
      |                          ^
mtrand.h:278:22: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  278 |         register int i = N;
      |                      ^
mtrand.h: In member function ‘MTRand::uint32 MTRand::randInt()’:
mtrand.h:292:25: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  292 |         register uint32 s1;
      |                         ^~
mtrand.h: In member function ‘void MTRand::save(uint32*) const’:
mtrand.h:366:32: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  366 |         register const uint32 *s = state;
      |                                ^
mtrand.h:367:26: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  367 |         register uint32 *sa = saveArray;
      |                          ^~
mtrand.h:368:22: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  368 |         register int i = N;
      |                      ^
mtrand.h: In member function ‘void MTRand::load(uint32*)’:
mtrand.h:375:26: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  375 |         register uint32 *s = state;
      |                          ^
mtrand.h:376:26: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  376 |         register uint32 *la = loadArray;
      |                          ^~
mtrand.h:377:22: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  377 |         register int i = N;
      |                      ^
mtrand.h: In function ‘std::ostream& operator<<(std::ostream&, const MTRand&)’:
mtrand.h:385:40: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  385 |         register const MTRand::uint32 *s = mtrand.state;
      |                                        ^
mtrand.h:386:22: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  386 |         register int i = mtrand.N;
      |                      ^
mtrand.h: In function ‘std::istream& operator>>(std::istream&, MTRand&)’:
mtrand.h:393:34: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  393 |         register MTRand::uint32 *s = mtrand.state;
      |                                  ^
mtrand.h:394:22: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  394 |         register int i = mtrand.N;
      |                      ^
mtrand.h: In member function ‘MTRand& MTRand::operator=(const MTRand&)’:
mtrand.h:404:32: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  404 |         register const uint32 *t = o.state;
      |                                ^
mtrand.h:405:26: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  405 |         register uint32 *s = state;
      |                          ^
mtrand.h:406:22: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  406 |         register int i = N;
      |                      ^
In file included from sim.cpp:5:
mtrand.h: In member function ‘void MTRand::initialize(uint32)’:
mtrand.h:173:26: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  173 |         register uint32 *s = state;
      |                          ^
mtrand.h:174:26: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  174 |         register uint32 *r = state;
      |                          ^
mtrand.h:175:22: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  175 |         register int i = 1;
      |                      ^
mtrand.h: In member function ‘void MTRand::reload()’:
mtrand.h:189:26: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  189 |         register uint32 *p = state;
      |                          ^
mtrand.h:190:22: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  190 |         register int i;
      |                      ^
mtrand.h: In member function ‘void MTRand::seed(uint32*, uint32)’:
mtrand.h:216:22: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  216 |         register int i = 1;
      |                      ^
mtrand.h:217:25: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  217 |         register uint32 j = 0;
      |                         ^
mtrand.h:218:43: warning: enumerated and non-enumerated type in conditional expression [-Wextra]
  218 |         register int k = ( N > seedLength ? N : seedLength );
      |                            ~~~~~~~~~~~~~~~^~~~~~~~~~~~~~~~
mtrand.h:218:22: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  218 |         register int k = ( N > seedLength ? N : seedLength );
      |                      ^
mtrand.h: In member function ‘void MTRand::seed()’:
mtrand.h:252:34: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  252 |                 register uint32 *s = bigSeed;
      |                                  ^
mtrand.h:253:30: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  253 |                 register int i = N;
      |                              ^
mtrand.h:254:31: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  254 |                 register bool success = true;
      |                               ^~~~~~~
mtrand.h: In copy constructor ‘MTRand::MTRand(const MTRand&)’:
mtrand.h:276:32: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  276 |         register const uint32 *t = o.state;
      |                                ^
mtrand.h:277:26: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  277 |         register uint32 *s = state;
      |                          ^
mtrand.h:278:22: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  278 |         register int i = N;
      |                      ^
mtrand.h: In member function ‘MTRand::uint32 MTRand::randInt()’:
mtrand.h:292:25: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  292 |         register uint32 s1;
      |                         ^~
mtrand.h: In member function ‘void MTRand::save(uint32*) const’:
mtrand.h:366:32: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  366 |         register const uint32 *s = state;
      |                                ^
mtrand.h:367:26: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  367 |         register uint32 *sa = saveArray;
      |                          ^~
mtrand.h:368:22: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  368 |         register int i = N;
      |                      ^
mtrand.h: In member function ‘void MTRand::load(uint32*)’:
mtrand.h:375:26: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  375 |         register uint32 *s = state;
      |                          ^
mtrand.h:376:26: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  376 |         register uint32 *la = loadArray;
      |                          ^~
mtrand.h:377:22: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  377 |         register int i = N;
      |                      ^
mtrand.h: In function ‘std::ostream& operator<<(std::ostream&, const MTRand&)’:
mtrand.h:385:40: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  385 |         register const MTRand::uint32 *s = mtrand.state;
      |                                        ^
mtrand.h:386:22: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  386 |         register int i = mtrand.N;
      |                      ^
mtrand.h: In function ‘std::istream& operator>>(std::istream&, MTRand&)’:
mtrand.h:393:34: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  393 |         register MTRand::uint32 *s = mtrand.state;
      |                                  ^
mtrand.h:394:22: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  394 |         register int i = mtrand.N;
      |                      ^
mtrand.h: In member function ‘MTRand& MTRand::operator=(const MTRand&)’:
mtrand.h:404:32: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  404 |         register const uint32 *t = o.state;
      |                                ^
mtrand.h:405:26: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  405 |         register uint32 *s = state;
      |                          ^
mtrand.h:406:22: warning: ISO C++17 does not allow ‘register’ storage class specifier [-Wregister]
  406 |         register int i = N;
      |                      ^
make[1]: Leaving directory '/data/home/majx/PrIDE/security/0_loss_probability/monte_carlo'
***** LossProbability for Window-Size: 79 ******
Capacity: 1     LossProb: 0.6298
Capacity: 2     LossProb: 0.3011
Capacity: 4     LossProb: 0.1181
Capacity: 8     LossProb: 0.0601
Capacity: 16    LossProb: 0.0306


/data/home/majx/PrIDE/security/0_loss_probability
echo ""

/data/home/majx/PrIDE/security
Traceback (most recent call last):
  File "/data/home/majx/PrIDE/security/0_loss_probability/analytical/loss_1entry.py", line 2, in <module>
    import matplotlib.pyplot as plt
ModuleNotFoundError: No module named 'matplotlib'
/data/home/majx/PrIDE/security
g++ -o sim-reliability sim-reliability.cpp
./sim-reliability


***********Printing Data for Fig-9***********
Bufsize: 1       TRH_STAR(NoTardy): 8288         TRH_STAR(Tardy): 8366
Bufsize: 2       TRH_STAR(NoTardy): 4404         TRH_STAR(Tardy): 4561
Bufsize: 3       TRH_STAR(NoTardy): 3678         TRH_STAR(Tardy): 3914
Bufsize: 4       TRH_STAR(NoTardy): 3472         TRH_STAR(Tardy): 3787
Bufsize: 5       TRH_STAR(NoTardy): 3379         TRH_STAR(Tardy): 3773
Bufsize: 6       TRH_STAR(NoTardy): 3322         TRH_STAR(Tardy): 3795
Bufsize: 7       TRH_STAR(NoTardy): 3282         TRH_STAR(Tardy): 3834
Bufsize: 8       TRH_STAR(NoTardy): 3252         TRH_STAR(Tardy): 3883
Bufsize: 9       TRH_STAR(NoTardy): 3230         TRH_STAR(Tardy): 3940
Bufsize: 10      TRH_STAR(NoTardy): 3212         TRH_STAR(Tardy): 4001
Bufsize: 11      TRH_STAR(NoTardy): 3197         TRH_STAR(Tardy): 4065
Bufsize: 12      TRH_STAR(NoTardy): 3185         TRH_STAR(Tardy): 4132
Bufsize: 13      TRH_STAR(NoTardy): 3175         TRH_STAR(Tardy): 4201
Bufsize: 14      TRH_STAR(NoTardy): 3166         TRH_STAR(Tardy): 4271
Bufsize: 15      TRH_STAR(NoTardy): 3159         TRH_STAR(Tardy): 4343
Bufsize: 16      TRH_STAR(NoTardy): 3152         TRH_STAR(Tardy): 4415


***********Printing Table-IV***********
PARA-DRFM               TRH_STAR: 16963  
PARA-DRFM+              TRH_STAR: 8471   
PRIDE                   TRH_STAR: 3831   




***********Printing Table-V***********
PRIDE (0.5x)            TRH_STAR-S: 7514
PRIDE           TRH_STAR-S: 3831
PRIDE+RFM40     TRH_STAR-S: 1981
PRIDE+RFM16     TRH_STAR-S: 822




***********Printing Table-VI***********
PRIDE           TRH_STAR-S: 3831         TRH_STAR-D: 1915
PRIDE+RFM40     TRH_STAR-S: 1981         TRH_STAR-D: 990
PRIDE+RFM16     TRH_STAR-S: 822          TRH_STAR-D: 411




***********Printing Table-VIII***********
100 Years       4.55 Years       TRH_STAR-S: 3415        TRH_STAR-D: 1707
1000 Years      45.45 Years      TRH_STAR-S: 3623        TRH_STAR-D: 1811
10000 Years     454.55 Years     TRH_STAR-S: 3831        TRH_STAR-D: 1915
100000 Years    4545.45 Years    TRH_STAR-S: 4039        TRH_STAR-D: 2019
1000000 Years   45454.55 Years   TRH_STAR-S: 4247        TRH_STAR-D: 2123




***********Printing Table-IX***********
TRDH-D: 4800    >1 mil_years    >1 mil_years    >1 mil_years
TRDH-D: 2000    2936 years      >1 mil_years    >1 mil_years
TRDH-D: 1800    36 years        >1 mil_years    >1 mil_years
TRDH-D: 1600    153 days        >1 mil_years    >1 mil_years
TRDH-D: 1400    2 days  >1 mil_years    >1 mil_years
TRDH-D: 1200    32 min  >1 mil_years    >1 mil_years
TRDH-D: 1000    23 sec  674 years       >1 mil_years
TRDH-D: 800     <1 sec  42 days >1 mil_years
TRDH-D: 600     <1 sec  10 min  >1 mil_years
TRDH-D: 400     <1 sec  <1 sec  140 years
TRDH-D: 200     <1 sec  <1 sec  3 sec


```

