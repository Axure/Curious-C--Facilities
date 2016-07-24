module Termios where
import Foreign.C

foreign import ccall "set_icanon" set_icanon :: CInt -> IO ()
foreign import ccall "unset_icanon" unset_icanon :: CInt -> IO ()
