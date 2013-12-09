module Main where
import System.Environment

main :: IO()
main = putStrLn . show . size $ insert 3 $insert 1 (empty :: PairOfList Int) 

class Queue q where
	empty :: q a
	size :: q a -> Int
	insert :: a -> q a -> q a
	remove :: q a -> ( a, q a )


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

-- queues from simple pairs
	-- this defines a constructor for a pair of lists, and is used to disambiguate other pairs of lists.
newtype PairOfList a = POL { unPOL :: ([a],[a]) }

instance Queue PairOfList where
	empty = POL ([],[])
	size (POL (xs, ys)) = length xs + length ys
	insert x (POL (xs, ys)) = (POL ( xs, x:ys))
	remove (POL (xs,ys)) = 
		if size xs > 0 then
			(head xs, (POL (tail xs, ys)))
		else
			remove (POL (reverse ys, []))
	

