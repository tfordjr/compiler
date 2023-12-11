Terry Ford Jr. - CS 4280 Compiler Project - P4 ASM Code Generation - 12/09/2023
git - https://github.com/tfordjr/scanner

Three options for invokation:
./comp                                      Read from stdin (stop input with Ctrl+D)
./comp filename(exclude extention)          Read from file, .f23 file extention assumed
./comp < filename(include extention)        Put file into stdin

implementation: 
main.cpp handles file input and stdin input
parser.cpp, parser.h handle parser function and full BNF
scanner.h handles scanner function and token definition
testTree.cpp, testTree.h, tree traversal, semantics, code generation traversal
node.h handle node definition
testing files t1-t10 are good programs, tb1-tb10 are bad programs
simple makefile and readme included

Added static semantics (double declaration or use without declaration)
added it to testTree.cpp and testTree.h because the semantics are just another traversal

All 7 testfiles (testfiles k1-k7) compiled and ran!
I use the ASM stack as a storage space as opposed to creating new temp vars,
and especially with k7 program (nested loops) the stack became very full very fast.
This never causes the wrong var to be popped and used, but can overfill the stack in 
larger programs. 

I used a mix of preserving given vars, creating temp vars, and utilizing the stack
to avoid creating too many vars. This led to me learning about all 3 implementations 
and seeing the merits and challenges of each. 

Full BNF:
<program>     ->      <vars> xopen <stats> xclose
<vars>        ->      empty | xdata <varList>
<varList>     ->      identifier : integer ; | identifier : integer <varList>
<exp>         ->      <M> / <exp> | <M> * <exp> | <M>
<M>           ->      <N> + <M> | <N>      
<N>           ->       <R> - <N> | ~ <N> |  <R>
<R>           ->      ( <exp> )  | identifier | integer
<stats>       ->      <stat>  <mStat>
<mStat>       ->      empty |  <stat>  <mStat>
<stat>        ->      <in>   | <out>   | <block> | <if>  | <loop>  | <assign>
<block>       ->      { <vars> <stats> }
<in>          ->      xin >> identifier ;
<out>         ->      xout << <exp> ;
<if>          ->      xcond [ <exp> <RO> <exp> ] <stat>
<loop>        ->      xloop [ <exp> <RO> <exp> ]  <stat>
<assign>      ->      xlet  identifier  <exp> ;
<RO>          ->      << (one token)  | >>  (one token)  | < | > | = | % 