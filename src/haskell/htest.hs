doubleMe x = x+x

doubleSmallNumber = if x > 100
	then x
	else x*2

misterO'Who = "it's a-e Doctor!" -- comment?

----------------------------------------------------------
--list:
-- head,tail, init,last
-- length
-- null test if a list is empty
-- reverse esrever
-- take , take x elements from a list
-- drop. drop the first x elements
-- maximum, minimum

let x = 10 in
	[x..20]


let abc = [a..z]

let steppingNumbers = [1,3..19]

let decreasingNumbers = [20,19..1]

-- infinite lazy lists
-- take x [1,5..]

let someCycle = take 10 (cycle [1,2,4])

-- list comprehensions
[ x*2 | x <- [1..10], x*2 >= 12]

[ x*y | x <- [1..3], y <- [1,5..20]]

removeNonUppercase st = [c | c <- st, c `elem` ['A'..'Z']]

-- incomprehensions :D
onlyEvenInside xxs = [ [ x | x <- xs, even x ] | xs <- xxs]


----------------------------------------------------------------------
-- tuples
((1,2),(3,4))

--fst , snd

zip [1,2,3] ['a','b','c']

----------------------------------------------------------------------

--- => is a class constraint
--- see :t (==)

-- multiple typeclasses:
fromIntegral :: (Num b, Integral a) => a -> b

--- typeclasses : Eq, Ord -> equality and ordering
"test" < "zebrea"
"test" `compare` "hello"
--- Show and Read
--- read does not know what to type to use, use type annotations
read "5" :: Int
read "5" :: Float
read "(3,'a')" ::(Int,Char)
--- Enum for ranges and predecessor/ successor
['a'..'e']
--- bounded for maxBound,minBound :: Bounded
--- Num acts like numbers

--- Integral numbers like Int and Integer

--- Floating numbers like Float and Double, has fromIntegral
