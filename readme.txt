Terry Ford Jr. - CS 4280 Compiler Project - P3 Static Semantics - 11/18/2023
git - https://github.com/tfordjr/scanner

Three options for invokation:
./P3                                      Read from stdin (stop input with Ctrl+D)
./P3 filename(exclude extention)          Read from file, .f23 file extention assumed
./P3 < filename(include extention)        Put file into stdin

implementation: 
main.cpp handles file input and stdin input
parser.cpp, parser.h handle parser function and full BNF
scanner.h handles scanner function and token definition
testTree.cpp, testTree.h, node.h handle node definition, tree traversal, semantics
testing files t1-t10 are good programs, tb1-tb10 are bad programs
simple makefile and readme included

Added static semantics (double declaration or use without declaration)
added it to testTree.cpp and testTree.h because the semantics are just another traversal

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