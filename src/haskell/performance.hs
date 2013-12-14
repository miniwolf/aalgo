module Main where
import System.Environment
import Queues

main :: IO ()
main = do
	putStrLn("empty queues: " ++ (show $emptyQueues))
