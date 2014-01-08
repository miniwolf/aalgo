module Main where
import System.Environment
import Criterion.Main
import Queues

main =
  let min = 1
      max = 1
      min2 = 100000
      max2 = 1000000
	in
   defaultMain [bgroup "insert-list" $ generateTest performInsertList min2 max2
               ,bgroup "insert-pair" $ generateTest performInsertPair min max
               ,bgroup "insert-triple" $ generateTest performInsertTriple min max
               ,bgroup "insert-const" $ generateTest performInsertConst min max
               ,bgroup "insert-list-repeat" $ generateTestDel performInsertList performIns min2 max2
               ,bgroup "insert-pair-repeat" $ generateTestDel performInsertPair performIns min max
               ,bgroup "insert-triple-repeat" $ generateTestDel performInsertTriple performIns min max
               ,bgroup "insert-const-repeat" $ generateTestDel  performInsertConst performIns min max
               ,bgroup "delete-list" $ generateTestDel performInsertList performPeekDel min2 max2
               ,bgroup "delete-pair" $ generateTestDel performInsertPair performPeekDel min max
               ,bgroup "delete-triple" $ generateTestDel performInsertTriple performPeekDel min max
               ,bgroup "delete-const" $ generateTestDel performInsertConst performPeekDel min max
               ,bgroup "delete-list-repeat" $ generateTestDel performInsertList performDel min2 max2
               ,bgroup "delete-pair-repeat" $ generateTestDel performInsertPair performDel min max
               ,bgroup "delete-triple-repeat" $ generateTestDel performInsertTriple performDel min max
               ,bgroup "delete-const-repeat" $ generateTestDel performInsertConst performDel min max]

foldl' f z [] = z
foldl' f z (x:xs) = (foldl' f $! f z x) xs

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
  foldl' (\ i q-> insert q i ) q [n, n-1..1]

performPeek qg n =
  let q = qg n in
  case peek q of Just x -> x
                 Nothing -> 0

performPeekDel qe = performPeek (\ n -> foldl' (\ q _ -> remove q) qe [n,n-1..1])

performPeekDelRepeat qe = performPeek (\ _ -> remove qe )

performPeekInsertRepeat qe  = performPeek (\ n ->  insert (n+1) qe)

performDel qe n = 
	remove qe

performIns qe n = 
	insert 1 qe

generateTest pfk min max
	| min >= max = [bench ("list-"++show min) $ nf pfk min]
	| otherwise  = (bench ("list-"++show min) $ nf pfk min) : (generateTest pfk (round (fromIntegral min * 1.5)) max)

generateTest2 pfk min max =
  let fun min max acc = 
        case min >= max of True -> acc
                           False ->  (fun (round (fromIntegral min * 1.5)) max ((bench ("list-"++show min) $ nf pfk  min) : acc))
  in fun min max []


generateTestDel qg pfk min max =
  let qe = qg $! min in  -- $! should force the function to strict evaluation instead of lazy
  case min >= max of True -> [bench ("list-"++show min) $ nf (pfk qe) min]
                     False -> (bench ("list-"++show min) $ nf (pfk qe) min) : (generateTestDel qg pfk (round (fromIntegral min * 1.5)) max)

generateTestDel2 qg pfk min max =
  let fun min max acc = 
        let qe = qg $! min in  -- $! should force the function to strict evaluation instead of lazy
        case min >= max of True -> acc
                           False ->  (fun (round (fromIntegral min * 1.5)) max ((bench ("list-"++show min) $ nf (pfk qe) min) : acc))
  in fun min max []
