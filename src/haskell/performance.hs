module Main where
import System.Environment
import Queues

main :: IO ()
main = do
	--putStrLn("empty queues: " ++ (show $emptyQueues))
	args <- getArgs
	if length args == 2
	then
		let (q1,q2,q3,q4) = emptyQueues in case args of
			[nstring,queue] -> case queue of 
				"List" -> let q = foldr insert [n,n-1..1] q1 in putStrLn ( (show $ peek q)	++ ", "++ (show $ size q))
				where n = read(nstring)	
			_ -> putStrLn "Something is wrong :/"
			
	else
		putStrLn "Not enough arguments, need 2"
