module Main where
import System.Environment
import Data.List hiding (insert)
-- import qualified Data.List (insert)   -- use Data.List.insert when using THAT particular insert.
-- import qualified Data.List as List

main :: IO()
main = putStrLn . show $ insert 3 $insert 1 (make [1,2,3,4,5]::PairOfList Int) 

class Queue q where
	empty :: q a
	size :: q a -> Int
	insert :: a -> q a -> q a
	remove :: q a -> ( a, q a )
	make :: [a] -> q a 
	make = foldr insert empty
	
-- queues from lists
instance Queue [] where
	empty = []
	size = length
	insert x xs = case xs of
		[] -> [x]
		(y:xs') -> y : insert x xs'
	remove xs = 
		let x:xs' = xs in
		(x, xs')
	make xs = xs

-- queues from simple pairs
	-- this defines a constructor for a pair of lists, and is used to disambiguate other pairs of lists.
newtype PairOfList a = POL { unPOL :: ([a],[a]) }

--instance Show a => Show(PairOfList a)
	--where show (POL (xs,ys)) = (show xs) ++ ", " ++ (show ys)

instance Show a => Show(PairOfList a) where	
	show (POL (xs, ys)) = brackets . concat . intersperse "," . map show $ xs ++ reverse ys where 
		brackets = (++"]") . ("["++)

instance Queue PairOfList where
	empty = POL ([],[])
	size (POL (xs, ys)) = length xs + length ys
	insert x (POL (xs, ys)) = (POL ( xs, x:ys))
	remove (POL (xs,ys)) = 
		if size xs > 0 then
			(head xs, (POL (tail xs, ys)))
		else
			remove (POL (reverse ys, []))
	make xs = POL ([],xs)

-- okasaki queue.
newtype TripleOfList a = TOL { unTOL :: ([a],[a],[a]) }

rotate :: TripleOfList a -> [a]
rotate (TOL (ls, rs, as)) =
	if size ls == 0 then
		head rs : as
	else
		head ls : rotate (TOL (tail ls, tail rs, head rs : as))

makeq :: TripleOfList a -> TripleOfList a
makeq (TOL (xs, ys, zs)) = 
	if size zs > 0 then
		TOL (xs, ys, tail zs)
	else
		let zs' = rotate (TOL (xs,ys,[])) in
		TOL (zs', [] , zs')

instance Queue TripleOfList where
	empty = TOL ([],[],[])
	size (TOL (ls, rs, ls')) = length ls + length rs
	insert x (TOL (ls, rs, ts)) = makeq (TOL (ls, x:rs, ts))
	remove (TOL (ls, rs, ts)) = (head ls, makeq (TOL (tail ls, rs, ts)))

-- constant time worst case queues.
newtype RealTime a = RT { unRT :: (Int,Int,[a],[a],[a],[a],[a]) }
