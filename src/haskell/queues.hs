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
	remove :: q a -> q a
	make :: [a] -> q a 
	make = foldr insert empty -- default implementation
	peek :: q a -> Maybe a

-- queues from lists
instance Queue [] where
	empty = []
	size = length
	insert x xs = case xs of
		[] -> [x]
		(y:xs') -> y : insert x xs'
	remove xs = case xs of
		[] -> []
		x:xs' -> xs'
	make xs = reverse xs
	peek xs = case xs of
		[] -> Nothing
		x:xs -> Just x

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
	remove (POL (xs,ys)) = case xs of
		x:xs' -> POL ( xs', ys)
		[] -> case ys of
			y:ys' -> remove( POL ( reverse  ys, []))
			[] -> empty
	peek (POL (xs, ys)) = case xs of
		[] -> case ys of
			[] -> Nothing
			ys -> Just $ last ys
		x:xs -> Just x

-- okasaki queue.
newtype TripleOfList a = TOL { unTOL :: ([a],[a],[a]) }

instance Show a => Show(TripleOfList a) where
	show q | size q > 0 = (show $ peek q) ++ ", " ++ (show $ remove q)
	show _ = " "

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
	remove (TOL (ls, rs, ts)) = case ls of
		l:ls' -> makeq (TOL (ls', rs, ts))
		[] -> empty
	peek (TOL (ls,rs,ts)) = case ls of
		(x:_) -> Just x
		[] -> Nothing

-- constant time worst case queues.
newtype RealTimePair a = RTP { unRT :: (Int, Int, [a], [a], [a], [a], [a], [a], Int) }

instance Show a => Show(RealTimePair a) where
	show q@(RTP (d, s, fs, as, bs, cs, ds, es ,_)) | size q > 0 = (show $ peek q) ++ ", " ++ (show $ remove q)
	show _ = ""

f:: RealTimePair a -> RealTimePair a
f(RTP(d, 0, fs,     [],     bs, (x:cs), ds, es , length)) = RTP(d, 0 ,fs, [], bs, cs, x:ds, es, length)
f(RTP(d, s, fs,     as, (x:bs),     [], ds, es , length)) = RTP(d, s+1, fs, x:as, bs, [], ds, es, length)
f(RTP(d, s, fs, (x:as),     [],     [], ds, es , length)) | s > d = RTP(d, s-1, fs, as, [], [], (x:ds), es , length)
f(RTP(d, s, fs,     as,     [],     [], ds, es , length)) | s == d = RTP(0, 0, ds, [], ds, es, [], [], length)

instance Queue RealTimePair where
	empty = RTP (0,0, [], [], [], [], [], [], 0)
	size (RTP (d, s, fs, as, bs, cs, ds, es, length)) = length
	insert x (RTP (d, s, fs, as, bs, cs, ds, es, length)) = f(f(f(RTP(d, s, fs, as, bs, cs, ds, x:es, length +1))))
	remove q@(RTP (d, s, fs, as, bs, cs , ds, es, length)) =
		case fs of
			[] -> q
			(_:fs') -> case f q of
				q@(RTP (d, s, _, _, _, _, _, _, _)) | d == s -> remove q
				_ -> f ( f ( f ( f (RTP(d+1, s, fs', as, bs, cs, ds, es, length-1)))))

	peek (RTP (d, s, [], _, [], [], (x:_), _, _)) | d == s = Just x
	peek (RTP (_, _, (x:_), _, _, _, _, _, _)) = Just x
	peek _ = Nothing

-- Real time queue 2, paper : http://ecommons.library.cornell.edu/handle/1813/6273
-- 	Real Time Queue Operations in Pure LISP

-- we implement size in constant time !!! this implementation has apparently an error too... !!!

newtype RealTimePair2 a = RTP2 { unRTP2 :: (Bool, Int, Int, [a], [a], [a], [a], [a], [a], Int) }

instance Show a => Show(RealTimePair2 a) where
	{-show q
		| size q == 0 = ""
		| size q > 1  =
			let (e,qs) = remove q in
			show e ++ ", " ++ show qs
		| size q == 1 =
			let (e,qs) = remove q in
			show e
	-}
	show (RTP2(recopy, lendiff, nrcopy, hS, tS, hs, hS', tS', hr, size)) = "(" ++ show recopy ++ ", " ++ show lendiff ++ ", " ++ show nrcopy ++ ", " ++ show hS ++ ", " ++ show tS ++ ", " ++ show hS' ++ ", " ++ show tS' ++ ", " ++ show hr ++ ", " ++ show size ++ ")"

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
		| recopy 		     						 = onestep( onestep( RTP2 (True, lendiff -1, nrcopy, hS, tS, hs, hS', v:tS, hr, size+1)))
	remove (RTP2( recopy, lendiff, nrcopy, hS, tS, hs, hS', tS', hr, size))
		| not recopy && lendiff > 0  = RTP2 (False, lendiff-1, 0, tail hS, tS, [], [], [], [], size-1)
		| not recopy && lendiff == 0 = onestep $ onestep (RTP2 (True, 0, 0, tail hS, tS, tail hS, [], [], [], size-1))
		| recopy		     = onestep $ onestep (RTP2 (True, lendiff-1,nrcopy, hS, tS, tail hs, hS', tS', hr, size-1))
	size (RTP2( _, _, _, _, _, _, _, _, _, size')) = size'
	peek (RTP2( recopy, lendiff, nrcopy, hS, tS, hs, hS', tS', hr, size))
		| not recopy && lendiff > 0  = Just $ head hS
		| not recopy && lendiff == 0 = Just $ head hS
		| recopy		     = Just $ head hs
