README
Ece Yaykiran
101101184

Files Included:
  fishingSimulator.c
  dynamicVersion.c

Instructions to compile:
  Open terminal
  gcc -o fishingSimulator fishingSimulator.c (for fishingSimulator program)
  gcc -o dynamicVersion dynamicVersion.c (for dynamicVersion program)

Instructions to run:
  ./fishingSimulator
  ./dynamicVersion
 
Instructions to run w/ Valgrind:
valgrind ./dynamicVersion (test for leaks)
valgrind --leak-check=yes ./dynamicVersion (to test for leaks and show in detail where 										they appear)
