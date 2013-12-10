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
	make = foldr insert empty -- default implementation
	peek :: q a -> a
	peek q = fst $ remove q -- default implementation

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
	peek xs = head xs

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
	remove (POL (xs,ys))
		| size xs > 0 = (head xs, (POL (tail xs, ys)))
		| otherwise   = remove (POL (reverse ys, []))
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

-- constant time worst case queues. !!! These are apparently incorrect !!!
newtype RealTimePair a = RTP { unRT :: (Int, Int, [a], [a], [a], [a], [a], [a]) }

f:: RealTimePair a -> RealTimePair a
f(RTP(d, 0, fs, [], bs, x:cs, ds, es)) = RTP(d, 0 ,fs, [], bs, cs, x:ds, es)
f(RTP(d, s, fs, as, x:bs, [], ds, es)) = RTP(d, s+1, fs, x:as, bs, [], ds, es)
f(RTP(d, s, fs, as, [], [], ds, es)) =
	if s > d then
		let x:as' = as in
		RTP(d, s-1, fs, as', [], [], x:ds, es)
	else
 		RTP(0, 0, ds, [], ds, es, [], [])

instance Queue RealTimePair where
	empty = RTP (0,0, [], [], [], [], [], [])
	size (RTP (d, s, fs, as, bs, cs, ds, es)) = length fs + length cs + length ds + length es 
	insert x (RTP (d, s, fs, as, bs, cs, ds, es)) = f(f(f(RTP(d, s, fs, as, bs, cs, ds, x:es))))
	remove (RTP (d, s, fs, as, bs, cs , ds, es)) =
		if d == s && length fs == 0 && length bs == 0 && length cs == 0 then
			let x:ds' = ds in
			(x,f(f(f(f(RTP(0, 0, ds', [], ds', es, [], []))))))
		else
			let x:fs' = fs in
			(x, f(f(f(f(RTP( d+1, s, fs', as, bs, cs, ds, es))))))

-- Real time queue 2, paper : http://ecommons.library.cornell.edu/handle/1813/6273
-- 	Real Time Queue Operations in Pure LISP

-- we implement size in constant time

newtype RealTimePair2 a = RTP2 { unRTP2 :: (Bool, Int, Int, [a], [a], [a], [a], [a], [a], Int) }

onestep :: RealTimePair2 a -> RealTimePair2 a
onestep q
	| not recopy = q
	| recopy && length hS > 0 && length tS > 0  =
		RTP2 (True, lendiff+1, nrcopy+1, tail hS, tail tS, hs, head tS : hS', tS', head hS : hr, size)
	| recopy && length hS == 0 && length tS > 0 =
		RTP2 (True, lendiff+1, nrcopy, [], [], hs, head tS : hS', tS', hr, size)
	| recopy && length hS == 0 && length tS == 0 && nrcopy > 1 =
		RTP2 (True, lendiff+1, nrcopy-1, [], [], hs, head hr : hS', tS', tail hr, size)
	| recopy && length hS == 0 && length tS == 0 && nrcopy == 1 =
		RTP2 (False, lendiff+1, 0, head hr : hS', tS', [], [], [], [], size)
	where RTP2(recopy, lendiff, nrcopy, hS, tS, hs, hS', tS', hr, size) = q

instance Queue RealTimePair2 where
	empty = RTP2 (False, 0, 0, [], [], [], [], [], [], 0)
	insert v (RTP2( recopy, lendiff, nrcopy, hS, tS, hs, hS', tS', hr, size))
		| not recopy && lendiff > 0  = RTP2( False, lendiff-1, 0, hS, v:tS, [], [], [], [], size+1)
		| not recopy && lendiff == 0 = onestep( onestep( RTP2 (True, 0, 0, hS, v:tS, hS, [], [], [], size+1)))
		| recopy 		     = onestep( onestep( RTP2 (True, lendiff -1, nrcopy, hS, tS, hs, hS', v:tS, hr, size+1)))
	remove (RTP2( recopy, lendiff, nrcopy, hS, tS, hs, hS', tS', hr, size))
		| not recopy && lendiff > 0  = ( head hS, RTP2 (False, lendiff-1, 0, tail hS, tS, [], [], [], [], size-1))
		| not recopy && lendiff == 0 = ( head hS, onestep $ onestep (RTP2 (True, 0, 0, tail hS, tS, tail hS, [], [], [], size-1)))
		| recopy		     = ( head hs, onestep $ onestep (RTP2 (True, lendiff-1,nrcopy, hS, tS, tail hs, hS', tS', hr, size-1)))
	size (RTP2( _, _, _, _, _, _, _, _, _, size')) = size'
