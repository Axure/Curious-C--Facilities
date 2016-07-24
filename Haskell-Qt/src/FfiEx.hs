module FfiEx where
import Control.Exception
import System.IO
import qualified Termios
import Control.Monad (when)

main = bracket_ (Termios.unset_icanon 0) (Termios.set_icanon 0)
    (while_true prompt)

while_true op = do
    continue <- op
    when continue (while_true op)

prompt = do
    putStr "? "
    hFlush stdout
    c <- getChar
    putStrLn $ "you typed " ++ [c]
    return (c /= 'q')