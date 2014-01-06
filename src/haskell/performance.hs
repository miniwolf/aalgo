module Main where
import System.Environment
import Criterion.Main
import Queues


map' f l = case l of [] -> []
                     x:xs -> (f $! x) : (map' f $! xs)
  
list_gen min max = if min >= max then [] else min:list_gen (round (fromIntegral min * 1.5)) max
a_fun min max generator = map generator (list_gen min max)


main =
  let min = 256
      max = 500000
      max2 = 10000
      llist = a_fun  min max2 $! performInsertList 
      lpair = a_fun  min max $! performInsertPair 
      ltriple = a_fun  min max $! performInsertTriple 
      lconst = a_fun  min max $! performInsertConst
   in
   defaultMain [bgroup "insert-list" $ generateTest performPeekList min max2
               ,bgroup "insert-pair" $ generateTest performPeekPair min max
               ,bgroup "insert-triple" $ generateTest performPeekTriple min max
               ,bgroup "insert-const" $ generateTest performPeekConst min max
               ,bgroup "insert-list-repeat" $ generateTestDel llist performIns min
               ,bgroup "insert-pair-repeat" $ generateTestDel lpair performIns min 
               ,bgroup "insert-triple-repeat" $ generateTestDel ltriple performIns min
               ,bgroup "insert-const-repeat" $ generateTestDel  lconst performIns min
               ,bgroup "delete-list" $ generateTestDel llist performPeekDel min
               ,bgroup "delete-pair" $ generateTestDel lpair performPeekDel min
               ,bgroup "delete-triple" $ generateTestDel ltriple performPeekDel min
               ,bgroup "delete-const" $ generateTestDel lconst performPeekDel min
               ,bgroup "delete-list-repeat" $ generateTestDel llist performDel min
               ,bgroup "delete-pair-repeat" $ generateTestDel lpair performDel min
               ,bgroup "delete-triple-repeat" $ generateTestDel ltriple performDel min
               ,bgroup "delete-const-repeat" $ generateTestDel lconst performDel min]

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

performPeekList = performPeek performInsertList

performPeekPair = performPeek performInsertPair

performPeekTriple = performPeek performInsertTriple

performPeekConst = performPeek performInsertConst

performPeekDel qe = performPeek (\ n -> foldl' (\ q _ -> remove q) qe [n,n-1..1])

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
	| otherwise  = (bench ("list-"++show min) $ nf pfk min) : (generateTest pfk (round (fromIntegral min * 1.5)) max)

generateTest2 pfk min max =
  let fun min max acc = 
        case min >= max of True -> acc
                           False ->  (fun (round (fromIntegral min * 1.5)) max ((bench ("list-"++show min) $ nf pfk  min) : acc))
  in fun min max []


generateTestDel ql pfk min =
  case ql of [] -> []
             x:xs -> (bench ("list-"++show min) $ nf (pfk x) min): (generateTestDel xs pfk (round (fromIntegral min * 1.5)))
