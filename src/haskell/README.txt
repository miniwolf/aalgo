how to run our program on linux.

Need to install the criterion framework first

 $ cabal install criterion

We compile with safe optimization and -rtsopts so we can change the stacksize
 $ ghc -O -rtsots performance.hs

We run with a bigger stackspace: 128mb, because otherwise the program would crash
Also, we can change the number of samples to save some time
 $ ./performance --samples=100 +RTS K128000000 -RTS > output.txt

We then use a simple script, to make the results more easy to work with.
 $ ./extractresults output.txt > extract.txt
