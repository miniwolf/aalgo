module Main where
import System.Environment
import Queues

main :: IO ()
main = do
	putStrLn("test " )

-- queues via simple lists
-- there are four datastructures:
	-- via simple lists -> ListQ
	-- via simple pairs -> PairQ
	-- via O(1) lists with worst case guarantee O(1) -> StrictQ (purely functional real time paper)
	-- via pair of lists, exploiting lazy evaluation -> LazyQ ( simple and efficient paper )
data Queue a =
	ListQ [a] | PairQ ([a],[a]) | LazyQ ([a],[a])

listMake = ListQ []

qLength :: Queue a -> Int
qLength (ListQ a) = length a
qLength (PairQ (l,r)) = length l + length r
qLength (LazyQ (l,r)) = length l + length r

qInsert :: a -> (Queue a) -> (Queue a)
qInsert e (ListQ a) = ListQ (e:a)
qInsert e (PairQ (l,r)) = PairQ (l,e:r)

-- when removing, we return element and new queue
qRemove :: (Queue a) -> (a ,(Queue a))
qRemove (ListQ a) = 
	let r = reverse a in
	let x:xs = r in
	(x , ListQ(reverse xs)) 
qRemove (PairQ (l,r)) =
	if length l > 0 then 
		 (head l,PairQ (tail l,r)) 
	else 
		qRemove(PairQ(reverse r, []))


listLength l = length l
listInsert e l = e:l

listRemove :: [a] -> (a,[a]) 
listRemove xs =
	let r = reverse xs in
	let a:as = r in
	(a, reverse as)	

-- queues via a pair of lists

pairMake = ([],[])
pairlength (a,b) = length a + length b 
pairInsert e (a,b) = (a,e:b)
pairRemove (a,b) = if length a > 0 then (head a, (tail a,b)) else pairRemove( reverse b, [])

-- O(1) bounds Okasaki


