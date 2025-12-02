let pos_mod n m =
  let r = n mod m in
  if r < 0 then r + m else r

let count_zeros c_pos n_pos turn =
  let partial_turn_zero = 
    if turn > 0 && c_pos != 0 && (pos_mod turn 100) > (100 - c_pos) then
      1
    else if turn < 0 && c_pos != 0 && (pos_mod (-1 * turn) 100) > c_pos then
      1
    else
      0
  in
  let full_turn_zeros = (abs turn) / 100 in
  let end_on_zero = match n_pos with
    | 0 -> 1
    | _ -> 0
  in
  partial_turn_zero + end_on_zero + full_turn_zeros

let zero_count lines = 
  let rec zero_counter acc cur_pos lines = match lines with
    | [] -> acc
    | l :: rest ->
      let turn = 
        let magnitude = (String.sub l 1 (String.length l - 1)) |> int_of_string in
        let dir_int = match l.[0] with
          | 'L' -> -1
          | 'R' -> 1
          | _ -> assert false
        in magnitude * dir_int
      in
      let next_pos = pos_mod (cur_pos + turn) 100 in 
      let line_zeros = count_zeros cur_pos next_pos turn in
      zero_counter (acc + line_zeros) next_pos rest
  in zero_counter 0 50 lines

let () =
  let input_text = In_channel.with_open_text "../input.txt" In_channel.input_all in 
  let split_lines = Str.split (Str.regexp "\n") input_text in 
  zero_count split_lines |> string_of_int |> fun x -> "Zeros: " ^ x |> print_endline