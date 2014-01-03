module Main where
import System.Environment
import Criterion.Main
import Queues

main =
  let min = 128
      max = 4096*2
  in
   defaultMain [bgroup "insert-list" $ generateTest performPeekList min max
               ,bgroup "insert-pair" $ generateTest performPeekPair min max
               ,bgroup "insert-triple" $ generateTest performPeekTriple min max
               ,bgroup "insert-const" $ generateTest performPeekConst min max
               ,bgroup "delete-list" $ generateTestDel performInsertList performPeekDel min max
               ,bgroup "delete-pair" $ generateTestDel performInsertPair performPeekDel min max
               ,bgroup "delete-triple" $ generateTestDel performInsertTriple performPeekDel min max
               ,bgroup "delete-const" $ generateTestDel performInsertConst performPeekDel min max]

performInsertList n = let (q1,q2,q3,q4) = emptyQueues in
  foldr insert q1 [n,n-1..1]

performInsertPair n = let (q1,q2,q3,q4) = emptyQueues in
  foldr insert q2 [n,n-1..1]

performInsertTriple n = let (q1,q2,q3,q4) = emptyQueues in
  foldr insert q3 [n,n-1..1]

performInsertConst n = let (q1,q2,q3,q4) = emptyQueues in
  foldr insert q4 [n,n-1..1]


performDel q n =
    foldr (\ x y -> remove y) q [n,n-1..1]

performPeekList n =
  let q = performInsertList n in
  case peek q of Just x -> x
                 Nothing -> 0

performPeekPair n =
  let q = performInsertPair n in
  case peek q of Just x -> x
                 Nothing -> 0

performPeekTriple n =
  let q = performInsertTriple n in
  case peek q of Just x -> x
                 Nothing -> 0

performPeekConst n =
  let q = performInsertConst n in
  case peek q of Just x -> x
                 Nothing -> 0

performPeekDel qe n =
  let q = performDel qe n in
  case peek q of Just x -> x
                 Nothing -> 0

generateTest pfk min max
	| min >= max = [bench ("list-"++show min) $ nf pfk min]
	| otherwise  = (bench ("list-"++show min) $ nf pfk min) : (generateTest pfk (min*2) max)

generateTestDel               :: (Int -> a) -> (a -> Int -> Int) -> Int -> Int -> [Benchmark]
generateTestDel q pfk min max = 
  let qe = q $! min in  -- $! should force the function to strict evaluation instead of lazy
  case min >= max of True -> [bench ("list-"++show min) $ nf (pfk qe) min]
                     False -> (bench ("list-"++show min) $ nf (pfk qe) min) : (generateTestDel q pfk (min*2) max)
