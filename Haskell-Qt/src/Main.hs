{-# LANGUAGE DeriveGeneric #-}
import GHC.Generics



sayMe :: (Integral a, Show a) => a -> String
sayMe 1 = "One!"
sayMe 2 = "Two!"
sayMe 3 = "Three!"
sayMe 4 = "Four!"
sayMe 5 = "Five!"
sayMe x = "Not between 1 and 5: " ++ (show x)

factorial :: (Integral a) => a -> a
factorial 0 = 1
factorial n = n * factorial (n - 1)

data Header = Header Char Int Bool

class Functor f where
    fmap :: (a -> b) -> f a -> f b

data TreeNode a = LeafNode a | InnerNode (TreeNode a) a (TreeNode a) deriving(Show, Generic)


ab = InnerNode (LeafNode 1) 2 (LeafNode 3)
abc = InnerNode (LeafNode "432") "432" (LeafNode "432")

main = do
        putStrLn $ show ab
        putStrLn $ show abc
        putStrLn $ sayMe $ factorial 32
        putStr "Hello"
        putStr " "
        putStr "world!"
        putStr "\n"
        putStr $ show $ f 1

f x =
    case x of
      0 -> 1
      1 -> 5
      2 -> 2
      _ -> (-1)