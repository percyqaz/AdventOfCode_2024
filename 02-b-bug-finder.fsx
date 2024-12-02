open System.IO

let raw_lines = File.ReadAllLines("input/02-input.txt")

let lines =
    raw_lines 
    |> Array.map (fun line -> 
        line.Split() 
        |> Array.map (_.Trim() >> int) 
        |> List.ofArray
)

let rec is_safe_ascending (xs: int list) =
    match xs with
    | x :: y :: xs -> 
        (y - x >= 1 && y - x <= 3) && is_safe_ascending (y :: xs)
    | _ -> true

let rec is_safe_descending (xs: int list) =
    match xs with
    | x :: y :: xs -> 
        (x - y >= 1 && x - y <= 3) && is_safe_descending (y :: xs)
    | _ -> true

let combos (xs: int list) : int list seq =
    seq {
        yield xs
        for n in 0 .. List.length xs - 1 do
            yield (List.take n xs) @ (List.skip (n + 1) xs)
    }

let is_safe (xs: int list) =
    combos xs
    |> Seq.exists (fun c -> is_safe_ascending c || is_safe_descending c)

lines 
|> Array.filter is_safe
|> Array.map (List.map string >> String.concat " ")
|> String.concat "\n"
|> fun c -> File.WriteAllText("input/02-testcases.txt", c)