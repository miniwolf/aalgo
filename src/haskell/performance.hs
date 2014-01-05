module Main where
import System.Environment
import Criterion.Main
import Queues

main =
  let min = 128
      max = 131072
      max2 = 4096
  in
   defaultMain [bgroup "insert-pair-repeat" $ generateTestDel performInsertPair performIns min max]

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
  foldl (\ q i -> insert i q) q [n, n-1..1]

performPeek qg n =
  let q = qg n in
  case peek q of Just x -> x
                 Nothing -> 0

performPeekList = performPeek performInsertList

performPeekPair = performPeek performInsertPair

performPeekTriple = performPeek performInsertTriple

performPeekConst = performPeek performInsertConst

performPeekDel qe = performPeek (\ n -> foldr (\ _ -> remove) qe [n,n-1..1])

performPeekDelRepeat qe = performPeek (\ _ -> remove qe )

performPeekInsertRepeat qe  = performPeek (\ n ->  insert (n+1) qe)

performDel qe n = 
	case peek $ remove qe of 
		Just x -> x
		Nothing -> 0

performIns qe n = 
	case peek $ insert 1 qe of 
		Just x -> x
		Nothing -> 0

generateTest pfk min max
	| min >= max = [bench ("list-"++show min) $ nf pfk min]
	| otherwise  = (bench ("list-"++show min) $ nf pfk min) : (generateTest pfk (min*1.5) max)

generateTest2 pfk min max =
  let fun min max acc = 
        case min >= max of True -> acc
                           False ->  (fun (min*2) max ((bench ("list-"++show min) $ nf pfk  min) : acc))
  in fun min max []


generateTestDel :: (Int -> a) -> (a -> Int -> Int) -> Int -> Int -> [Benchmark]



generateTestDel qg pfk min max =
  let qe = qg $! min in  -- $! should force the function to strict evaluation instead of lazy
  case min >= max of True -> [bench ("list-"++show min) $ nf (pfk qe) min]
                     False -> (bench ("list-"++show min) $ nf (pfk qe) min) : (generateTestDel qg pfk (min*2) max)

generateTestDel2 qg pfk min max =
  let fun min max acc = 
        let qe = qg $! min in  -- $! should force the function to strict evaluation instead of lazy
        case min >= max of True -> acc
                           False ->  (fun (min*2) max ((bench ("list-"++show min) $ nf (pfk qe) min) : acc))
  in fun min max []
