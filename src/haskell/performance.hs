module Main where
import System.Environment
import Criterion.Main
import Control.DeepSeq
import Queues

main =
  let min = 1000
      max = 1000000
      min2 = 1000
      max2 = 10000
	in
   defaultMain [bgroup "insert-list" $ generateTest performInsertList min2 max2
               ,bgroup "insert-pair" $ generateTest performInsertPair min max
               ,bgroup "insert-triple" $ generateTest performInsertTriple min max
               ,bgroup "insert-const" $ generateTest performInsertConst min max
               ,bgroup "insert-list-repeat" $ generateTestDel makeListQueue performIns min max
               ,bgroup "insert-pair-repeat" $ generateTestDel performInsertPair performIns min max
               ,bgroup "insert-triple-repeat" $ generateTestDel performInsertTriple performIns min max
               ,bgroup "insert-const-repeat" $ generateTestDel  performInsertConst performIns min max
               ,bgroup "delete-list" $ generateTestDel makeListQueue performDeleteAll min max
               ,bgroup "delete-pair" $ generateTestDel performInsertPair performDeleteAll min max
               ,bgroup "delete-triple" $ generateTestDel performInsertTriple performDeleteAll2 min max
               ,bgroup "delete-const" $ generateTestDel performInsertConst performDeleteAll min max
               ,bgroup "delete-list-repeat" $ generateTestDel makeListQueue performDel min max
               ,bgroup "delete-pair-repeat" $ generateTestDel performInsertPair performDel min max
               ,bgroup "delete-triple-repeat" $ generateTestDel performInsertTriple performDel min max
               ,bgroup "delete-const-repeat" $ generateTestDel performInsertConst performDel min max]

foldl' f z [] = z
foldl' f z (x:xs) = (foldl' f $! f z x) xs

performInsertList =
  let (q1,q2,q3,q4) = emptyQueues in
  performInsert q1

makeListQueue n = -- lets be a little smart here... -.-
	make [n,n-1..1] ::ListQueue Int

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

performDeleteAll n qe =
	case size qe of
		0 -> ()
		otherwise -> let q2 = remove qe in
								 q2 `seq` performDeleteAll n q2

performDeleteAll2 n qe =
	case size qe of
		0 -> ()
		otherwise -> let q2 = remove qe in
								 performDeleteAll2 n q2

performDel n qe=
	remove qe

performIns n qe=
	insert n qe

generateTest pfk min max
	| min >= max = [bench ("list-"++show min) $ nf pfk min]
	| otherwise  = (bench ("list-"++show min) $ nf pfk min) : (generateTest pfk (round (fromIntegral min * 1.5)) max)

generateTest2 pfk min max =
  let fun min max acc = 
        case min >= max of True -> acc
                           False ->  (fun (round (fromIntegral min * 1.5)) max ((bench ("list-"++show min) $ nf pfk  min) : acc))
  in fun min max []

generateTestDel qg pfk min max =
  let qe = (qg min) in
  case min >= max of True -> [bench ("list-"++show min) $ nf (pfk min) qe]
                     False -> (bench ("list-"++show min) $ nf (pfk min) qe) : (generateTestDel qg pfk (round (fromIntegral min * 1.5)) max)

generateTestDel2 qg pfk min max =
  let fun min max acc = 
        let qe = (qg min) in
        case min >= max of True -> acc
                           False ->  (fun (round (fromIntegral min * 1.5)) max ((bench ("list-"++show min) $ nf (pfk min) qe) : acc))
  in fun min max []
