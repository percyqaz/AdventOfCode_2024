open System.IO

let raw_lines = File.ReadAllLines("input/07-input.txt")

let lines =
    raw_lines 
    |> Array.map (fun line -> 
        let s = line.Split(":", System.StringSplitOptions.TrimEntries)
        int64 s.[0], (s[1].Split() |> Array.map (_.Trim() >> int64) |> List.ofArray)
)

let cat (x: int64) (y: int64) = sprintf "%i%i" x y |> int64

let rec is_possible_rec (target: int64, remaining_nums: int64 list, accumulator: int64) : bool =
    match remaining_nums with
    | [] -> failwith "impossible"
    | x :: [] -> cat accumulator x = target || accumulator * x = target || accumulator + x = target
    | x :: xs ->
        if target >= cat accumulator x && is_possible_rec(target, xs, cat accumulator x) then
            true
        elif target >= accumulator * x && is_possible_rec(target, xs, accumulator * x) then
            true
        elif target >= accumulator + x && is_possible_rec(target, xs, accumulator + x) then
            true
        else
            false

let is_possible (target: int64, nums: int64 list) : bool =
    match nums with
    | x :: xs -> is_possible_rec(target, xs, x)
    | _ -> failwith "impossible"

lines 
|> Array.filter is_possible
|> Array.map (fun (target, nums) -> sprintf "%i: %s" target (String.concat " " (nums |> Seq.map (sprintf "%i"))))
|> fun a -> File.WriteAllLines("input/07-testcases.txt", a)