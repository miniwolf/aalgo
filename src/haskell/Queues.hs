module Queues where
import System.Environment
import Data.List hiding (insert)
import Control.DeepSeq
-- import qualified Data.List (insert)   -- use Data.List.insert when using THAT particular insert.
-- import qualified Data.List as List

--main :: IO()
--main = putStrLn . show $ insert 3 $insert 1 (make [1,2,3,4,5]::PairOfList Int)

emptyQueues = (empty :: ListQueue Int, empty ::PairOfList Int, empty :: TripleOfList Int, empty::RealTimePair Int)

class Queue q where
	empty :: q a
	size :: q a -> Int
	insert :: a -> q a -> q a
	remove :: q a -> q a
	make :: [a] -> q a 
	make = foldr insert empty -- default implementation
	peek :: q a -> Maybe a
	toList :: q a -> [a]
	toList queue = case peek queue of
		Just x -> x : (toList $ remove queue)
		Nothing -> []
	removeAll :: q a -> q a
	removeAll queue = case peek queue of
		Nothing -> queue
		Just x -> removeAll queue

-- queues from lists
newtype ListQueue a = LQ { unLQ :: ([a],Int) }

instance Show a => Show(ListQueue a) where
	show (LQ(xs,size)) = show $ reverse xs

instance NFData a => NFData (ListQueue a) where
	rnf (LQ(xs,l)) = l `deepseq` xs `deepseq` ()

instance Queue ListQueue where
	empty = LQ ([],0)
	size (LQ(xs,l)) = l
	insert x (LQ(xs,l)) = case xs of
		[] -> LQ ([x],1)
		xs' -> LQ( xs ++ [x], l+1)
	remove (LQ(xs,l)) = case xs of
		[] -> LQ ([],l)
		x:xs' -> LQ(xs',l-1)
	make xs = LQ(reverse xs, length xs)
	peek (LQ(xs, l)) = case xs of
		[] -> Nothing
		x:xs -> Just x

-- queues from simple pairs
	-- this defines a constructor for a pair of lists, and is used to disambiguate other pairs of lists.
newtype PairOfList a = POL { unPOL :: ([a],[a], Int) }

--instance Show a => Show(PairOfList a)
	--where show (POL (xs,ys)) = (show xs) ++ ", " ++ (show ys)

instance Show a => Show(PairOfList a) where
	show (POL (xs, ys, length)) = brackets . concat . intersperse "," . map show $ xs ++ reverse ys where
		brackets = (++"]") . ("["++)

instance NFData a => NFData (PairOfList a) where
	rnf (POL (xs, ys, length)) = xs `seq` ys `seq` length `seq` ()

instance Queue PairOfList where
	empty = POL ([],[],0)
	size (POL (xs, ys, length)) = length
	insert x (POL (xs, ys, length)) = (POL ( xs, x:ys, length+1))
	remove (POL (xs,ys, length)) = case xs of
		x:xs' -> POL ( xs', ys , length -1)
		[] -> case ys of
			y:ys' -> remove( POL ( reverse  ys, [], length))
			[] -> empty
	peek (POL (xs, ys, _)) = case xs of
		[] -> case ys of
			[] -> Nothing
			ys -> Just $ last ys
		x:xs -> Just x

-- okasaki queue.
newtype TripleOfList a = TOL { unTOL :: ([a],[a],[a]) }

instance Show a => Show(TripleOfList a) where
	show queue = show(toList queue)

instance NFData a => NFData (TripleOfList a) where
	rnf (TOL (ls, rs, as)) = () -- no forced evaluation.

rotate :: TripleOfList a -> [a]
rotate (TOL (ls, rs, as)) = case ls of
	[] -> head rs : as
	l:ls' -> l : rotate (TOL (ls', tail rs, head rs : as))

makeq :: TripleOfList a -> TripleOfList a
makeq (TOL (xs, ys, zs)) = case zs of
	[] -> let zs' = rotate (TOL (xs,ys,[])) in
		TOL (zs', [] , zs')
	(z:zs') -> TOL (xs, ys, zs')

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
	show queue = show(toList queue)

instance NFData a => NFData (RealTimePair a) where
	rnf (RTP (d, s, fs, as, bs, cs , ds, es, length)) = fs `seq` ()

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

instance NFData (RealTimePair2 a) where
	rnf (RTP2( recopy, lendiff, nrcopy, hS, tS, hs, hS', tS', hr, size)) = hS `seq` ()

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
