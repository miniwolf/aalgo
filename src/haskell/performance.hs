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
				"list" -> let q = foldr insert q1 [n,n-1..1] in putStrLn $ show $ peek q
				"pair" -> let q = foldr insert q2 [n,n-1..1] in putStrLn $ show $ peek q
				"triple" -> let q = foldr insert q3 [n,n-1..1] in putStrLn $ show $ peek q
				"const" -> let q = foldr insert q4 [n,n-1..1] in putStrLn $ show $ peek q
				where n = read(nstring)	
			_ -> putStrLn "Something is wrong :/"
	else
		putStrLn "Not enough arguments, need 2"
