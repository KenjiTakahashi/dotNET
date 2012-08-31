module Fibonacci

let fib2 n =
    let an = (abs n) - 1 in
    let cache = Array.create (an + 1) (0) in
    let rec f i =
        match i with
        | 0 -> 0
        | 1 -> 1
        | n -> if cache.[n] = 0
               then cache.[n] <- f (n - 1) + f (n - 2);
               cache.[n]
    in (f an) |> ignore;
    cache

let list n =
    fib2 n