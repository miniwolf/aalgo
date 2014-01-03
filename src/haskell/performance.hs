module Main where
import System.Environment
import Criterion.Main
import Queues

main =  
  let min = 128 
      max = 4096 
  in
   defaultMain [bgroup "insert-list" $ generateTest performPeekList min max
               ,bgroup "insert-pair" $ generateTest performPeekPair min max
               ,bgroup "insert-triple" $ generateTest performPeekTriple min max
               ,bgroup "insert-const" $ generateTest performPeekConst min max
               ,bgroup "insert-list-repeat" $ generateTestDel performInsertList performPeekInsertRepeat min max
               ,bgroup "insert-pair-repeat" $ generateTestDel performInsertPair performPeekInsertRepeat min max
               ,bgroup "insert-triple-repeat" $ generateTestDel performInsertTriple performPeekInsertRepeat min max
               ,bgroup "insert-const-repeat" $ generateTestDel  performInsertConst performPeekInsertRepeat min max
               ,bgroup "delete-list" $ generateTestDel performInsertList performPeekDel min max
               ,bgroup "delete-pair" $ generateTestDel performInsertPair performPeekDel min max
               ,bgroup "delete-triple" $ generateTestDel performInsertTriple performPeekDel min max
               ,bgroup "delete-const" $ generateTestDel performInsertConst performPeekDel min max
               ,bgroup "delete-list-repeat" $ generateTestDel performInsertList performPeekDelRepeat min max
               ,bgroup "delete-pair-repeat" $ generateTestDel performInsertPair performPeekDelRepeat min max
               ,bgroup "delete-triple-repeat" $ generateTestDel performInsertTriple performPeekDelRepeat min max
               ,bgroup "delete-const-repeat" $ generateTestDel performInsertConst performPeekDelRepeat min max]

performInsertList = 
  let (q1,q2,q3,q4) = emptyQueues in
  performInsert q1
  
performInsertPair = 
  let (q1,q2,q3,q4) = emptyQueues in
  performInsert q2
 
performInsertTriple = 
  let (q1,q2,q3,q4) = emptyQueues in
  performInsert q3
  
performInsertConst = 
  let (q1,q2,q3,q4) = emptyQueues in
  performInsert q4
  

performInsert q n = 
  foldr insert q [n, n-1..1]
 
performPeek qg n = 
  let q = qg n in 
  case peek q of Just x -> x
                 Nothing -> 0

performPeekList = performPeek performInsertList

performPeekPair = performPeek performInsertPair

performPeekTriple = performPeek performInsertTriple 

performPeekConst = performPeek performInsertConst

performPeekDel qe = performPeek (\ n -> foldr (\ _ -> remove) qe [n,n-1..1])

performPeekDelRepeat qe = performPeek (\ n -> foldr (\ _ _ -> remove qe ) qe [n, n-1..1])

performPeekInsertRepeat qe  = performPeek (\ n -> foldr (\ _ _ -> insert (n+1) qe ) qe [n, n-1..1])


generateTest pfk min max
	| min >= max = [bench ("list-"++show min) $ nf pfk min]
	| otherwise  = (bench ("list-"++show min) $ nf pfk min) : (generateTest pfk (min*2) max)


generateTestDel :: (Int -> a) -> (a -> Int -> Int) -> Int -> Int -> [Benchmark]
generateTestDel qg pfk min max = 
  let qe = qg $! min in  -- $! should force the function to strict evaluation instead of lazy 
  case min >= max of True -> [bench ("list-"++show min) $ nf (pfk qe) min]
                     False -> (bench ("list-"++show min) $ nf (pfk qe) min) : (generateTestDel qg pfk (min*2) max)
